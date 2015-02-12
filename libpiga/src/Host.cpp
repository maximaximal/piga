#include <piga/Host.hpp>
#include <piga/Status.hpp>
#include <piga/GameHost.hpp>
#include <piga/Definitions.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <yaml-cpp/yaml.h>

#include <google/protobuf/message_lite.h>
#include <libpiga_handshake.pb.h>
#include <input.pb.h>

using std::cout;
using std::endl;

namespace piga
{
    Host::Host(const std::string &configFile, std::shared_ptr<PlayerManager> playerManager)
        : m_configFile(configFile), m_playerManager(playerManager)
    {

    }
    Host::~Host()
    {
        m_sharedLibs.clear();
        deleteSharedMemory();
        if(m_enetPeers.size() > 0)
        {
            for(auto &peer : m_enetPeers)
            {
                enet_peer_disconnect(peer.second, 1);
            }
            ENetEvent event;
            while(enet_host_service(m_enetHost, &event, 100))
            {
                switch(event.type)
                {
                    case ENET_EVENT_TYPE_DISCONNECT:
                        m_enetPeers.erase(event.peer->address.host);
                        event.peer->data = nullptr;
                        break;
                    case ENET_EVENT_TYPE_RECEIVE:
                        enet_packet_destroy(event.packet);
                        break;
                    default:
                        break;
                }
            }
        }
        if(m_enetHost != nullptr)
            enet_host_destroy(m_enetHost);
    }
    void Host::init()
    {
        m_sharedLibs.clear();

        createSharedMemory();

        YAML::Node doc = YAML::LoadAllFromFile(m_configFile).front();
        if(doc["Hosts"])
        {
            for(YAML::const_iterator it = doc["Hosts"].begin(); it != doc["Hosts"].end(); ++it)
            {
                std::shared_ptr<SharedLibWrapper> sharedLib(std::make_shared<SharedLibWrapper>((*it).as<std::string>()));
                sharedLib->init(m_playerCount);
                m_sharedLibs.push_back(sharedLib);
            }
        }
        if(doc["Name"])
        {
            m_name = doc["Name"].as<std::string>();
        }
        if(doc["Networked"])
        {
            GOOGLE_PROTOBUF_VERIFY_VERSION;
            YAML::Node net = doc["Networked"];
            int port = 17010;
            int clientCount = 1;
            int channelCount = 2;
            int maxBandwithUp = 0;
            int maxBandwithDown = 0;

            if(net["ServerPort"])
                port = net["ServerPort"].as<int>();
            if(net["MaxClientCount"])
                clientCount = net["MaxClientCount"].as<int>();
            if(net["MaxChannelCount"])
                channelCount = net["MaxChannelCount"].as<int>();
            if(net["MaxBandwithUp"])
                maxBandwithUp = net["MaxBandwithUp"].as<int>();
            if(net["MaxBandwithDown"])
                maxBandwithDown = net["MaxBandwithDown"].as<int>();

            ENetAddress address;
            address.host = ENET_HOST_ANY;
            address.port = port;

            m_enetHost = enet_host_create(&address,
                             clientCount,
                             channelCount,
                             maxBandwithDown,
                             maxBandwithUp);

            cout << PIGA_DEBUG_PRESTRING << "Using networked features." << endl;
            cout << PIGA_DEBUG_PRESTRING << "Server on port: " << port << endl;
            cout << PIGA_DEBUG_PRESTRING << "Maximum client count: " << clientCount << endl;
            cout << PIGA_DEBUG_PRESTRING << "Maximum bandwith (up): " << maxBandwithUp << endl;
            cout << PIGA_DEBUG_PRESTRING << "Maximum bandwith (down): " << maxBandwithDown << endl;
            cout << PIGA_DEBUG_PRESTRING << "Maximum channel count: " << channelCount << endl;

            if(m_enetHost == nullptr)
            {
                cout << PIGA_DEBUG_PRESTRING << "ENet host could not be created!" << endl;
            }
        }
    }
    void Host::applyFromGameInput(GameInput *gameInput)
    {
        using namespace boost::interprocess;
        managed_shared_memory shm(open_only, getInputSharedMemoryName());

        std::pair<PlayerInputStruct*, std::size_t> p =
                shm.find<PlayerInputStruct>("PlayerInput");

        GameEvent event;
        while(gameInput->pollEvent(event))
        {
            p.first[event.playerID()].fromGameEvent(event);
        }
    }
    void Host::setInput(unsigned int playerID, GameControl control, bool state)
    {
        using namespace boost::interprocess;
        managed_shared_memory shm(open_only, getInputSharedMemoryName());

        std::pair<PlayerInputStruct*, std::size_t> p =
                shm.find<PlayerInputStruct>("PlayerInput");

        p.first[playerID].fromGameEvent(control, state);
        
        if(m_backcallingGameInput)
        {
            GameEvent e(playerID, event::GameInput(control, state));
            m_backcallingGameInput->pushGameEvent(e);
        }
    }
    void Host::setBackcallingGameInput(std::shared_ptr<GameInput> gameInput)
    {
        m_backcallingGameInput = gameInput;
    }
    void Host::setCurrentGameHost(GameHost *gameHost)
    {
        m_currentGameHost = gameHost;
        if(gameHost != nullptr)
        {
            if(m_currentGameHost->isRunning())
            {
                using namespace boost::interprocess;
                managed_shared_memory shm(open_only, getStatusSharedMemoryName());

                std::pair<Status*, std::size_t> p =
                        shm.find<Status>("Status");

                Status *status = p.first;

                status->setRunning(true);
            }
        }
    }
    void Host::setPlayerManager(std::shared_ptr<PlayerManager> playerManager)
    {
        m_playerManager = playerManager;
    }
    bool Host::gameIsRunning()
    {
        using namespace boost::interprocess;
        managed_shared_memory shm(open_only, getStatusSharedMemoryName());

        std::pair<Status*, std::size_t> p =
                shm.find<Status>("Status");

        Status *status = p.first;

        if(m_currentGameHost != nullptr)
        {
            if(m_currentGameHost->isRunning())
            {
                if(!status->isRunning())
                {
                    m_currentGameHost->setRunning(false);
                }
            }
            else
            {
                if(status->isRunning())
                {
                    m_currentGameHost->setRunning(true);
                }
            }
        }
        return status->isRunning();
    }
    void Host::update(float frametime)
    {
        for(std::size_t i = 0; i < m_playerCount; ++i)
        {
            for(unsigned int control = GameControl::UP; control < GameControl::_COUNT; ++control)
            {
                for(auto sharedLibWrapper : m_sharedLibs)
                {
                    sharedLibWrapper->query(this, i, static_cast<GameControl>(control));
                }
            }
        }
        if(m_enetHost != nullptr)
        {
            ENetEvent event;
            while(enet_host_service(m_enetHost, &event, 10))
            {
                switch(event.type)
                {
                    case ENET_EVENT_TYPE_CONNECT:
                        cout << PIGA_DEBUG_PRESTRING << "Client connected from " << event.peer->address.host << "." << endl;
                        m_enetPeers[event.peer->address.host] = event.peer;
                        sendHandshakePacket(event.peer);
                        break;
                    case ENET_EVENT_TYPE_DISCONNECT:
                        m_enetPeers.erase(event.peer->address.host);
                        event.peer->data = nullptr;
                        break;
                    case ENET_EVENT_TYPE_RECEIVE:
                        receivePacket(event.packet, event.peer);
                        enet_packet_destroy(event.packet);
                        break;
                    case ENET_EVENT_TYPE_NONE:
                        break;
                }
            }
        }
    }
    const char *Host::getInputSharedMemoryName()
    {
        return "PiGa_GameInterface";
    }
    const char *Host::getStatusSharedMemoryName()
    {
        return "PiGa_GameStatus";
    }
    void Host::createSharedMemory()
    {
        using namespace boost::interprocess;

        deleteSharedMemory();

        managed_shared_memory shm_input(create_only,
                                  getInputSharedMemoryName(),
                                  1024);

        for(std::size_t i = 1; i < m_playerCount; ++i)
        {
            shm_input.construct<PlayerInputStruct>("PlayerInput")[m_playerCount]();
        }

        managed_shared_memory shm_status(create_only,
                                  getStatusSharedMemoryName(),
                                  1024);

        shm_status.construct<Status>("Status")[1](false);
    }
    void Host::deleteSharedMemory()
    {
        boost::interprocess::shared_memory_object::remove(getInputSharedMemoryName());
        boost::interprocess::shared_memory_object::remove(getStatusSharedMemoryName());
    }
    void Host::sendHandshakePacket(ENetPeer *peer)
    {
        if(m_playerManager)
        {
            LibpigaHandshake handshake;
            handshake.set_name(m_name.c_str());
            for(auto &player : m_playerManager->getPlayers())
            {
                ::Player *playerPacket = handshake.add_player();
                playerPacket->set_username(player.second->getName());
                playerPacket->set_id(player.first);
                cout << PIGA_DEBUG_PRESTRING << "Added the player " << player.second->getName() << " - ID: " << player.first << endl;
            }

            //This is a handshake packet.
            std::string buffer("HANDS" + handshake.SerializeAsString());

            ENetPacket *packet = enet_packet_create(&buffer[0u], buffer.length(), ENET_PACKET_FLAG_RELIABLE);
            enet_peer_send(peer, 0, packet);
        }
    }
    void Host::receivePacket(ENetPacket *packet, ENetPeer *peer)
    {
        cout << PIGA_DEBUG_PRESTRING << "Message Received!" << endl;
        std::string buffer(packet->data, packet->data + packet->dataLength);
        std::string packetType = buffer.substr(0, 5);
        buffer.erase(0, 5);

        if(packetType == "INPUT")
        {
            ::Input input;
            input.ParseFromString(buffer);

            piga::GameControl control;

            switch(input.control())
            {
                case ::GameControl::ACTION:
                    control = piga::GameControl::ACTION;
                    break;
                case ::GameControl::UP:
                    control = piga::GameControl::UP;
                    break;
                case ::GameControl::DOWN:
                    control = piga::GameControl::DOWN;
                    break;
                case ::GameControl::LEFT:
                    control = piga::GameControl::LEFT;
                    break;
                case ::GameControl::RIGHT:
                    control = piga::GameControl::RIGHT;
                    break;
            }

            bool state = false;

            if(input.input() > 0)
                state = true;

            cout << PIGA_DEBUG_PRESTRING << "INPUT!!" << endl;
            setInput(input.playerid(), control, state);
        }
    }
}
