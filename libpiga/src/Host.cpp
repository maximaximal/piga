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
    void Host::init(int playerCount)
    {
        m_sharedLibs.clear();

        createSharedMemory(playerCount);

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
            else
            {
                cout << PIGA_DEBUG_PRESTRING << "ENet host created successfully!" << endl;
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

        if(m_playerInputStructs == nullptr)
        {
            std::pair<PlayerInputStruct*, std::size_t> p =
                    m_inputsShm->find<PlayerInputStruct>("PlayerInput");


            m_playerInputStructs = p.first;
        }

        m_playerInputStructs[playerID].fromGameEvent(control, state);
        
        GameEvent e(playerID, event::GameInput(control, state));
        if(m_backcallingGameInput)
        {
            m_backcallingGameInput->pushGameEvent(e);
        }
        
        if(m_currentGameHost != nullptr)
            m_currentGameHost->sendGameEvent(e);
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
                m_status->setRunning(true);
                Player *player = nullptr;
                for(int i = 0; i < m_playerManager->size(); ++i)
                {
                    player = m_playerManager->getPlayer(i);
                    m_status->pushEvent(event::PlayerAdded(player->getPlayerID(), player->getName()));
                }
            }
        }
    }
    void Host::setPlayerManager(std::shared_ptr<PlayerManager> playerManager)
    {
        m_playerManager = playerManager;
    }
    bool Host::gameIsRunning(bool fsCheck)
    {
        bool state = false;
        if(m_currentGameHost != nullptr)
        {
            state = m_currentGameHost->isRunning(fsCheck);
        }
        return state;
    }
    void Host::update(float frametime)
    {
        m_isRunningTimer += frametime;
        if(m_isRunningTimer > 0.5)
        {
            gameIsRunning(true);
            m_isRunningTimer = 0;
        }
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
    const char *Host::getPlayersSharedMemoryName()
    {
        return "PiGa_GamePlayers";
    }
    void Host::createSharedMemory(int playerCount)
    {
        using namespace boost::interprocess;

        deleteSharedMemory();

        m_inputsShm = new managed_shared_memory(create_only,
                                  getInputSharedMemoryName(),
                                  1024);

        for(std::size_t i = 1; i < m_playerCount; ++i)
        {
            m_inputsShm->construct<PlayerInputStruct>("PlayerInput")[m_playerCount]();
        }

        m_statusShm = new managed_shared_memory(create_only,
                                  getStatusSharedMemoryName(),
                                  1024 + sizeof(Status));

        m_statusShm->construct<Status>("Status")[1](false);

        std::pair<Status*, std::size_t> p =
                m_statusShm->find<Status>("Status");

        m_status = p.first;

        managed_shared_memory shm_players(create_only,
                                          getPlayersSharedMemoryName(),
                                          1024 + sizeof(Player) * playerCount);

        shm_players.construct<Player>("Player")[playerCount]("Undefined", false);

        //Set the IDs of the players.
        std::pair<Player*, std::size_t> players = shm_players.find<Player>("Player");
        for(std::size_t i = 0; i < players.second; ++i)
        {
            players.first[i].setPlayerID((int) i);
        }
    }
    void Host::deleteSharedMemory()
    {
        boost::interprocess::shared_memory_object::remove(getInputSharedMemoryName());
        delete m_inputsShm;
        m_inputsShm = nullptr;
        boost::interprocess::shared_memory_object::remove(getStatusSharedMemoryName());
        delete m_statusShm;
        m_statusShm = nullptr;
        m_status = nullptr;
        boost::interprocess::shared_memory_object::remove(getPlayersSharedMemoryName());
    }
    void Host::sendHandshakePacket(ENetPeer *peer)
    {
        if(m_playerManager)
        {
            LibpigaHandshake handshake;
            handshake.set_name(m_name.c_str());

            for(int i = 0; i < m_playerManager->size(); ++i)
            {
                Player *player = m_playerManager->getPlayer(i);

                ::Player *playerPacket = handshake.add_player();
                playerPacket->set_username(player->getName());
                playerPacket->set_id(i);
                playerPacket->set_active(player->isActive());
                cout << PIGA_DEBUG_PRESTRING << "Added the player " << player->getName() << " - ID: " << i << endl;
            }

            //This is a handshake packet.
            std::string buffer("HANDS" + handshake.SerializeAsString());

            ENetPacket *packet = enet_packet_create(&buffer[0u], buffer.length(), ENET_PACKET_FLAG_RELIABLE);
            enet_peer_send(peer, 0, packet);
        }
    }
    void Host::receivePacket(ENetPacket *packet, ENetPeer *peer)
    {
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

            setInput(input.playerid(), control, state);
        }
    }
}
