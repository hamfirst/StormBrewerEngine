
#include "StormNet/NetBitReaderVector.h"

#include "NetServerBackendWebsocket.h"
#include "NetTransmitterServerWebsocket.h"

#ifdef _MSC_VER
#define _WIN32_WINNT 0x0501
#endif

#include "StormSockets/StormSocketBackend.h"
#include "StormSockets/StormSocketServerFrontendWebsocket.h"

#include <stdexcept>


NetServerBackendWebsocket::NetServerBackendWebsocket(NetServerInterface * iface, const NetServerBackendWebsocketSettings & settings) :
  m_Interface(iface),
  m_Transmitters(settings.m_MaxConnections)
{
  StormSockets::StormSocketInitSettings backend_settings;

  backend_settings.NumIOThreads = 1;
  backend_settings.NumSendThreads = 1;

  backend_settings.MaxConnections = settings.m_MaxConnections;

  m_Backend = std::make_unique<StormSockets::StormSocketBackend>(backend_settings);

  StormSockets::StormSocketServerFrontendWebsocketSettings server_settings;
  server_settings.MaxConnections = settings.m_MaxConnections;
  server_settings.ListenSettings.Port = settings.m_Port;

  m_WebsocketFrontend = std::make_unique<StormSockets::StormSocketServerFrontendWebsocket>(server_settings, m_Backend.get());
  m_Transmitters.resize(settings.m_MaxConnections);
}

NetServerBackendWebsocket::~NetServerBackendWebsocket()
{

}

void NetServerBackendWebsocket::Update()
{
  StormSockets::StormSocketEventInfo event;
  NetTransmitterServerWebsocket * trans;

  while (m_WebsocketFrontend->GetEvent(event))
  {
    switch (event.Type)
    {
    case StormSockets::StormSocketEventType::ClientConnected:
      break;
    case StormSockets::StormSocketEventType::ClientHandShakeCompleted:
      printf("A new client connected from %x:%u.\n", event.RemoteIP, event.RemotePort);

      //trans = m_Transmitters.Allocate(event.ConnectionId.GetIndex());
      {
        auto new_trans = std::make_unique<NetTransmitterServerWebsocket>();
        m_Transmitters[event.ConnectionId.GetIndex()] = std::move(new_trans);
      }

      trans = m_Transmitters[event.ConnectionId.GetIndex()].get();
      trans->m_Server = this;
      trans->m_Handle = event.ConnectionId;

      m_Interface->GotNewConnection(event.ConnectionId, event.RemoteIP, event.RemotePort, trans);
      break;
    case StormSockets::StormSocketEventType::Data:
      trans = m_Transmitters[event.ConnectionId.GetIndex()].get();

      if (trans->m_Disconnected == false)
      {
        auto & websocket_reader = event.GetWebsocketReader();
        if(websocket_reader.GetDataType() == StormSockets::StormSocketWebsocketDataType::Binary ||
           websocket_reader.GetDataType() == StormSockets::StormSocketWebsocketDataType::Text)
        {
          auto buffer = std::make_unique<uint8_t[]>(websocket_reader.GetDataLength());
          websocket_reader.ReadByteBlock(buffer.get(), websocket_reader.GetDataLength());

          NetBitReaderBuffer reader(buffer.get(), websocket_reader.GetDataLength());
          m_Interface->GotMessage(event.ConnectionId, reader);
        }

        m_WebsocketFrontend->FreeIncomingPacket(websocket_reader);
      }
      break;
    case StormSockets::StormSocketEventType::Disconnected:

      printf("A client disconnected from %x:%u.\n", event.RemoteIP, event.RemotePort);
      m_Interface->ConnectionLost(event.ConnectionId);

      m_Transmitters[event.ConnectionId.GetIndex()].reset();
      m_WebsocketFrontend->FinalizeConnection(event.ConnectionId);
      break;
    }
  }
}

void NetServerBackendWebsocket::ForceDisconnect(uint32_t connection_id)
{
  StormSockets::StormSocketConnectionId id;
  id.m_Index.Raw = connection_id;

  m_WebsocketFrontend->ForceDisconnect(id);
}
