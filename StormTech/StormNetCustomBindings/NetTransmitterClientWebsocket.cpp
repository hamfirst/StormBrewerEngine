
#include "NetTransmitterClientWebsocket.h"
#include "NetClientBackendWebsocket.h"

#include "Foundation/Network/WebSocket.h"

NetTransmitterClientWebsocket::NetTransmitterClientWebsocket()
{

}

NetBitWriter & NetTransmitterClientWebsocket::CreateWriter(NetPipeMode mode, int channel_index, int channel_bits, bool ack)
{
  CreateDefaultMessage(m_Writer, channel_index, channel_bits, ack);
  return m_Writer;
}

void NetTransmitterClientWebsocket::SendWriter(NetBitWriter & writer)
{
  m_Client->m_Host->SendPacket(m_Writer.GetData(), m_Writer.GetDataSize(), WebSocketPacketType::kBinary);
}
