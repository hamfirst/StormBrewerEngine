
#include "NetTransmitterServerWebsocket.h"
#include "NetServerBackendWebsocket.h"

#ifdef _MSC_VER
#define _WIN32_WINNT 0x0501
#endif

#include "StormSockets/StormSocketServerFrontendWebsocket.h"

NetTransmitterServerWebsocket::NetTransmitterServerWebsocket()
{

}

NetBitWriter & NetTransmitterServerWebsocket::CreateWriter(NetPipeMode mode, int channel_index, int channel_bits, bool ack)
{  
  CreateDefaultMessage(m_Writer, channel_index, channel_bits, ack);
  return m_Writer;
}

void NetTransmitterServerWebsocket::SendWriter(NetBitWriter & writer)
{
  auto packet = m_Server->m_WebsocketFrontend->CreateOutgoingPacket(StormSockets::StormSocketWebsocketDataType::Binary, true);
  packet.WriteByteBlock(m_Writer.GetData(), 0, m_Writer.GetDataSize());
  m_Server->m_WebsocketFrontend->FinalizeOutgoingPacket(packet);
  m_Server->m_WebsocketFrontend->SendPacketToConnectionBlocking(packet, m_Handle);
  m_Server->m_WebsocketFrontend->FreeOutgoingPacket(packet);
}
