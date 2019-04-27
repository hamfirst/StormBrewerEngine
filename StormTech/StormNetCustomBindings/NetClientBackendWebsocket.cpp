
#include "StormNet/NetBitReaderBuffer.h"
#include "NetClientBackendWebsocket.h"

#include <stdexcept>


NetClientBackendWebsocket::NetClientBackendWebsocket(NetClientInterface * iface, const char * host, int port, const char * uri, const char * origin) :
  m_Interface(iface),
  m_Connected(false)
{
  m_Host = std::make_unique<WebSocket>(host, port, uri, origin);
  m_Transmitter.m_Client = this;
}

NetClientBackendWebsocket::~NetClientBackendWebsocket()
{

}

void NetClientBackendWebsocket::Update()
{
  if (m_Connected == false)
  {
    if (m_Host->IsConnected())
    {
      m_Connected = true;
      m_Interface->GotConnection(&m_Transmitter);
    }
    else if (m_Host->IsConnecting() == false)
    {
      m_Interface->ConnectionFailed();
    }
  }
  else
  {
    if (m_Host->IsConnected() == false)
    {
      m_Connected = false;
      m_Interface->Disconnected();
    }
    else
    {
      while (true)
      {
        auto packet = m_Host->PollPacket();
        if(packet.IsValid() == false)
        {
          break;
        }

        if (m_Transmitter.m_Disconnected == false)
        {
          NetBitReaderBuffer reader(packet->m_Buffer.Get(), packet->m_Buffer.GetSize());
          m_Interface->GotMessage(reader);
        }
      }
    }
  }
}

void NetClientBackendWebsocket::Disconnect()
{
  if (m_Transmitter.m_Disconnected)
  {
    return;
  }

  m_Host->Close();
  m_Transmitter.m_Disconnected = true;
}
