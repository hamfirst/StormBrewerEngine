
#include "NetTransmitterServerWebrtc.h"

#include "StormWebrtcClientAPI/StormWebrtcClient.h"

NetTransmitterServerWebrtc::NetTransmitterServerWebrtc()
{

}

NetBitWriter & NetTransmitterServerWebrtc::CreateWriter(NetPipeMode mode, int channel_index, int channel_bits, bool ack)
{  
  m_StreamIndex = channel_index;
  m_SenderChannel = ack;

  m_Writer.Reset();

  if (ack == false && m_OutSeqs[channel_index].second)
  {
    m_Writer.WriteBits(m_OutSeqs[channel_index].first, 8);
    m_OutSeqs[channel_index].first++;
  }

  return m_Writer;
}

void NetTransmitterServerWebrtc::SendWriter(NetBitWriter & writer)
{
  m_Server->SendPacket(m_Handle, m_Writer.GetData(), m_Writer.GetDataSize(), m_StreamIndex, m_SenderChannel);
}
