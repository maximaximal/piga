#include <Client.hpp>

#include <../../include/easylogging++.h>
#include <libpiga_handshake.pb.h>
#include <input.pb.h>

Client::Client(std::shared_ptr<piga::PlayerManager> playerManager)
    : m_playerManager(playerManager)
{
    m_client = enet_host_create(nullptr,
                                1,
                                2,
                                0,
                                0);

    if(m_client == nullptr)
        LOG(FATAL) << "ENet Client could not initialize correctly!";
    else
        LOG(INFO) << "ENet Client started successfully.";
}
Client::~Client()
{
    if(m_serverPeer != nullptr)
    {
        enet_peer_disconnect(m_serverPeer, 0);
        ENetEvent event;
        bool force = false;
        while(enet_host_service(m_client, &event, 3000))
        {
            switch(event.type)
            {
                case ENET_EVENT_TYPE_DISCONNECT:
                    LOG(INFO) << "Disconnected successfully.";
                    force = false;
                    break;
                case ENET_EVENT_TYPE_RECEIVE:
                    enet_packet_destroy(event.packet);
                    break;
                default:
                    force = true;
                    break;
            }
        }
        if(force)
        {
            enet_peer_reset(m_serverPeer);
            m_serverPeer = nullptr;
        }
    }
    enet_host_destroy(m_client);
    LOG(INFO) << "Client destroyed.";
}
void Client::setServerAdress(const std::string &adress)
{
    m_serverAdress = adress;
}
void Client::setServerPort(int port)
{
    m_serverPort = port;
}
const std::string &Client::getServerAdress()
{
    return m_serverAdress;
}
int Client::getServerPort()
{
    return m_serverPort;
}
void Client::connect()
{
    ENetAddress address;
    ENetEvent event;
    m_connected = true;
    enet_address_set_host(&address, m_serverAdress.c_str());
    address.port = m_serverPort;

    LOG(INFO) << "Trying to connect to " << m_serverAdress << ":" << m_serverPort << ".";

    m_serverPeer = enet_host_connect(m_client, &address, 2, 0);
    if(m_serverPeer == nullptr)
    {
        LOG(FATAL) << "No available peers to initialize connection!";
        m_connected = false;
    }
}
void Client::update()
{
    ENetEvent event;

    while(enet_host_service(m_client, &event, 10))
    {
        switch(event.type)
        {
            case ENET_EVENT_TYPE_CONNECT:
                LOG(INFO) << "Client connected successfully to " << event.peer->address.host
                          << ":" << event.peer->address.port << ".";
                m_connected = true;
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                event.peer->data = nullptr;
                LOG(INFO) << "Client disconnected.";
                m_serverPeer = nullptr;
                m_connected = false;
                break;
            case ENET_EVENT_TYPE_NONE:
                //Nothing happened
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                receivePacket(event.packet, event.peer);
                enet_packet_destroy(event.packet);
                break;
        }
    }
}
bool Client::disconnected()
{
    return !m_connected;
}
Client::HandshakeCompletedSignal& Client::handshakeCompleted()
{
    return m_handshakeCompleted;
}
void Client::sendInputPacket(unsigned int playerID, piga::GameControl control, int input)
{
    if(m_serverPeer != nullptr)
    {
        Input inputPacket;

        inputPacket.set_playerid(playerID);
        inputPacket.set_input(input);

        ::GameControl controlEnum;

        switch(input)
        {
            case piga::ACTION:
                controlEnum = ::GameControl::ACTION;
                break;
            case piga::UP:
                controlEnum = ::GameControl::UP;
                break;
            case piga::DOWN:
                controlEnum = ::GameControl::DOWN;
                break;
            case piga::LEFT:
                controlEnum = ::GameControl::LEFT;
                break;
            case piga::RIGHT:
                controlEnum = ::GameControl::RIGHT;
                break;
            case piga::BUTTON1:
                controlEnum = ::GameControl::BUTTON1;
                break;
            case piga::BUTTON2:
                controlEnum = ::GameControl::BUTTON2;
                break;
            case piga::BUTTON3:
                controlEnum = ::GameControl::BUTTON3;
                break;
            case piga::BUTTON4:
                controlEnum = ::GameControl::BUTTON4;
                break;
            case piga::BUTTON5:
                controlEnum = ::GameControl::BUTTON5;
                break;
            case piga::BUTTON6:
                controlEnum = ::GameControl::BUTTON6;
                break;
        }

        inputPacket.set_control(controlEnum);

        std::string buffer("INPUT" + inputPacket.SerializeAsString());
        ENetPacket *packet = enet_packet_create(&buffer[0u], buffer.length(), ENET_PACKET_FLAG_RELIABLE);
        enet_peer_send(m_serverPeer, 1, packet);
    }
}
void Client::receivePacket(ENetPacket *packet, ENetPeer *peer)
{
    std::string buffer(packet->data, packet->data + packet->dataLength);
    std::string messageType = buffer.substr(0, 5);
    buffer.erase(0, 5);
    if(messageType == "HANDS")
    {
        m_playerManager->clear();
        LibpigaHandshake handshake;
        handshake.ParseFromString(buffer);
        LOG(INFO) << "Received a handshake package from the pigaco installation \"" << handshake.name() << "\".";

        for(int i = 0; i < handshake.player_size(); ++i)
        {
            std::shared_ptr<piga::Player> player = std::make_shared<piga::Player>(
                        handshake.player(i).id(),
                        handshake.player(i).username());
            LOG(INFO) << "Adding the player \"" << player->getName() << "\" (ID: " << player->getPlayerID() << ").";
            m_playerManager->set(player, player->getPlayerID());
        }

        m_handshakeCompleted();
    }
}
