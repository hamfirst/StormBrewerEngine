
#include "NetTransmitterClientWebrtc.h"
#include "NetClientBackendWebrtc.h"
#include "StormWebrtcClientAPI/StormWebrtcClient.h"

NetTransmitterClientWebrtc::NetTransmitterClientWebrtc()
{

}

NetBitWriter & NetTransmitterClientWebrtc::CreateWriter(NetPipeMode mode, int channel_index, int channel_bits, bool ack)
{
  m_StreamIndex = channel_index;
  m_SenderChannel = ack;

  if (ack == false && m_Client->m_OutSeqs[channel_index].second)
  {
    m_Writer.WriteBits(m_Client->m_OutSeqs[channel_index].first, 8);
    m_Client->m_OutSeqs[channel_index].first++;
  }
  return m_Writer;
}

void NetTransmitterClientWebrtc::SendWriter(NetBitWriter & writer)
{
  m_Client->m_Host->SendPacket(m_StreamIndex, m_SenderChannel, m_Writer.GetData(), m_Writer.GetDataSize());
}
