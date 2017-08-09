
#include "StormNet/NetBitReaderBuffer.h"
#include "NetClientBackendWebrtc.h"

#include <stdexcept>


NetClientBackendWebrtc::NetClientBackendWebrtc(NetClientInterface * iface, const char * host_addr, uint16_t port, const char * fingerprint,
                                               const std::vector<NetPipeMode> & inc_channels, const std::vector<NetPipeMode> & out_channels) :
  m_Interface(iface),
  m_Connected(false)
{

  std::vector<StormWebrtcClientStreamType> client_inc_types;
  std::vector<StormWebrtcClientStreamType> client_out_types;

  for (auto & pipe : inc_channels)
  {
    m_IncSeqs.push_back(std::make_pair(0, pipe == NetPipeMode::kUnreliableSequenced));
    client_inc_types.push_back(pipe == NetPipeMode::kReliable ? StormWebrtcClientStreamType::kReliable : StormWebrtcClientStreamType::kUnreliable);
  }

  for (auto & pipe : out_channels)
  {
    m_OutSeqs.push_back(std::make_pair(0, pipe == NetPipeMode::kUnreliableSequenced));
    client_out_types.push_back(pipe == NetPipeMode::kReliable ? StormWebrtcClientStreamType::kReliable : StormWebrtcClientStreamType::kUnreliable);
  }

  m_Host = CreateStormWebrtcClient(client_inc_types, client_out_types, host_addr, port, fingerprint);
  m_Transmitter.m_Client = this;
}

NetClientBackendWebrtc::~NetClientBackendWebrtc()
{

}

void NetClientBackendWebrtc::Update()
{
  m_Host->Update();
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
      StormWebrtcClientPacket packet;
      while (m_Host->PollPacket(packet))
      {
        if (m_Transmitter.m_Disconnected == false)
        {
          if (packet.m_SenderChannel == false && m_IncSeqs[packet.m_Stream].second)
          {
            auto seq = packet.m_Buffer.get()[0];
            auto diff = seq - m_IncSeqs[packet.m_Stream].first;

            if (diff > 128)
            {
              continue;
            }

            NetBitReaderBuffer reader(packet.m_Buffer.get() + 1, packet.m_Length - 1);
            m_Interface->GotMessage(reader, packet.m_SenderChannel, packet.m_Stream);

            m_IncSeqs[packet.m_Stream].first = seq;
          }
          else
          {
            NetBitReaderBuffer reader(packet.m_Buffer.get(), packet.m_Length);
            m_Interface->GotMessage(reader, packet.m_SenderChannel, packet.m_Stream);
          }
        }
      }
    }
  }
}

void NetClientBackendWebrtc::Disconnect()
{
  if (m_Transmitter.m_Disconnected)
  {
    return;
  }

  m_Host->Close();
  m_Transmitter.m_Disconnected = true;
}
