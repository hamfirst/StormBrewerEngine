
#include "StormNet/NetBitReaderVector.h"

#include "NetServerBackendWebrtc.h"
#include "NetTransmitterServerWebrtc.h"

#include <stdexcept>
#include <enet/enet.h>


NetServerBackendWebrtc::NetServerBackendWebrtc(NetServerInterface * iface, const NetServerBackendWebrtcSettings & settings) :
  m_Interface(iface),
  m_Transmitters(settings.m_MaxConnections)
{
  StormWebrtcServerSettings server_settings;
  server_settings.m_Port = settings.m_Port;
  server_settings.m_MaxConnections = settings.m_MaxConnections;
  server_settings.m_KeyFile = settings.m_KeyFile;
  server_settings.m_CertFile = settings.m_CertFile;

  for (auto & str : settings.m_InStreams)
  {
    server_settings.m_InStreams.emplace_back(str == NetPipeMode::kReliable ? StormWebrtcStreamType::kReliable : StormWebrtcStreamType::kUnreliable);
  }

  for (auto & str : settings.m_OutStreams)
  {
    server_settings.m_OutStreams.emplace_back(str == NetPipeMode::kReliable ? StormWebrtcStreamType::kReliable : StormWebrtcStreamType::kUnreliable);
  }

  m_IncStreams = settings.m_InStreams;
  m_OutStreams = settings.m_OutStreams;

  m_Host = CreateStormWebrtcServer(server_settings);
}

NetServerBackendWebrtc::~NetServerBackendWebrtc()
{

}

void NetServerBackendWebrtc::Update()
{
  m_Host->Update();

  StormWebrtcEvent event;
  NetTransmitterServerWebrtc * trans;

  while (m_Host->PollEvent(event))
  {
    switch (event.m_Type)
    {
    case StormWebrtcEventType::kConnected:
      printf("A new client connected from %x:%u.\n", event.m_RemoteAddr, event.m_RemotePort);

      trans = m_Transmitters.Allocate(event.m_ConnectionHandle.m_SlotId);
      trans->m_Server = m_Host.get();
      trans->m_Handle = event.m_ConnectionHandle;

      for (auto & str : m_IncStreams)
      {
        trans->m_IncSeqs.emplace_back(std::make_pair(0, str == NetPipeMode::kUnreliableSequenced));
      }

      for (auto & str : m_OutStreams)
      {
        trans->m_OutSeqs.emplace_back(std::make_pair(0, str == NetPipeMode::kUnreliableSequenced));
      }

      m_Interface->GotNewConnection(event.m_ConnectionHandle.m_SlotId, event.m_RemoteAddr, event.m_RemotePort, trans);
      break;
    case StormWebrtcEventType::kData:
      trans = m_Transmitters.GetElementForId(event.m_ConnectionHandle.m_SlotId);

      if (trans->m_Disconnected == false)
      {
        if (event.m_SenderChannel == false && m_IncStreams[event.m_StreamIndex] == NetPipeMode::kUnreliableSequenced)
        {
          auto seq = event.m_Buffer.get()[0];
          auto diff = seq - trans->m_IncSeqs[event.m_StreamIndex].first;

          if (diff > 128)
          {
            continue;
          }

          NetBitReaderBuffer reader(event.m_Buffer.get() + 1, event.m_DataSize - 1);
          m_Interface->GotMessage(event.m_ConnectionHandle.m_SlotId, reader, event.m_SenderChannel, event.m_StreamIndex);

          trans->m_IncSeqs[event.m_StreamIndex].first = seq;
        }
        else
        {
          NetBitReaderBuffer reader(event.m_Buffer.get(), event.m_DataSize);
          m_Interface->GotMessage(event.m_ConnectionHandle.m_SlotId, reader, event.m_SenderChannel, event.m_StreamIndex);
        }

      }
      break;
    case StormWebrtcEventType::kDisconnected:
      printf("A client disconnected from %x:%u.\n", event.m_RemoteAddr, event.m_RemotePort);

      trans = m_Transmitters.GetElementForId(event.m_ConnectionHandle.m_SlotId);
      m_Interface->ConnectionLost(event.m_ConnectionHandle.m_SlotId);

      m_Transmitters.Free(trans);
      break;
    }
  }
}

void NetServerBackendWebrtc::ForceDisconnect(uint32_t connection_id)
{
  m_Host->ForceDisconnect(StormWebrtcConnectionHandle(connection_id));
}
