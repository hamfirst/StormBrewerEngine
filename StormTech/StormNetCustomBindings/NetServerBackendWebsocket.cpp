
#include "StormNet/NetBitReaderVector.h"

#include "NetServerBackendWebsocket.h"
#include "NetTransmitterServerWebsocket.h"

#ifdef _MSC_VER
#define _WIN32_WINNT 0x0501
#endif

#include "StormSockets/StormSocketBackend.h"
#include "StormSockets/StormSocketServerFrontendWebsocket.h"

#include <stdexcept>
#include <enet/enet.h>


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
    case StormSockets::StormSocketEventType::ClientHandShakeCompleted:
      printf("A new client connected from %x:%u.\n", event.RemoteIP, event.RemotePort);

      trans = m_Transmitters.Allocate(event.ConnectionId.GetIndex());
      trans->m_Server = this;
      trans->m_Handle = event.ConnectionId;

      m_Interface->GotNewConnection(event.ConnectionId, event.RemoteIP, event.RemotePort, trans);
      break;
    case StormSockets::StormSocketEventType::Data:
      trans = m_Transmitters.GetElementForId(event.ConnectionId.GetIndex());

      if (trans->m_Disconnected == false)
      {
        auto & websocket_reader = event.GetWebsocketReader();

        auto buffer = std::make_unique<uint8_t[]>(websocket_reader.GetDataLength());
        websocket_reader.ReadByteBlock(buffer.get(), websocket_reader.GetDataLength());

        NetBitReaderBuffer reader(buffer.get(), websocket_reader.GetDataLength());
        m_Interface->GotMessage(event.ConnectionId, reader);
      }
      break;
    case StormSockets::StormSocketEventType::Disconnected:

      trans = m_Transmitters.GetElementForId(event.ConnectionId.GetIndex());
      m_Interface->ConnectionLost(event.ConnectionId);

      m_Transmitters.Free(trans);
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
