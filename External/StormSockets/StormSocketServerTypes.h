#pragma once

#include <StormSockets\StormMessageWriter.h>
#include <StormSockets\StormMessageReader.h>

namespace StormSockets
{
  namespace StormSocketEventType
  {
    enum Index
    {
      ClientConnected,
      ClientHandshakeComplete,
      Disconnected,
      Data,
    };
  }

  namespace StormSocketContinuationMode
  {
    enum Index
    {
      Combine,
      DeliverImmediately,
      WaitForCompletion,
    };
  }

  struct StormSocketEventInfo
  {
    StormSocketEventType::Index Type;
    StormSocketServerConnectionId ConnectionId;
    StormMessageReader Reader;

    uint32_t RemoteIP;
    uint16_t RemotePort;
  };

  struct StormSocketInitSettings
  {
    uint16_t Port;
    const char * LocalInterface;
    const char * Protocol;

    bool UseMasking;
    StormSocketContinuationMode::Index ContinuationMode;

    int NumIOThreads;
    int NumSendThreads;
    int MaxConnections;

    int HeapSize;
    int BlockSize;

    int MessageQueueSize;

    int MaxPendingOutgoingPacketsPerConnection;
    int MaxPendingFreeingPacketsPerConnection;
    int MaxPendingIncomingPacketsPerConnection;
    int MaxSendQueueElements;

    const wchar_t * CertificateFile;
    const wchar_t * PrivateKeyFile;

    void SetDefaults();
  };
}

