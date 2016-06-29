
#pragma once

#include <StormSockets\StormSocketServerTypes.h>

namespace StormSockets
{
  using StormSocketServerImpl = void *;

  class StormSocketServer
  {
  public:
    StormSocketServer(StormSocketInitSettings & settings);
    StormSocketServer(StormSocketServer && rhs) noexcept;
    StormSocketServer(const StormSocketServer & rhs) = delete;
    ~StormSocketServer();

    StormSocketServer & operator = (StormSocketServer && rhs) noexcept;

    void Start();
    bool GetEvent(StormSocketEventInfo & message);

    StormMessageWriter CreateOutgoingPacket(StormSocketDataType::Index type, bool final);
    void FinalizeOutgoingPacket(StormMessageWriter & writer);

    bool SendPacketToConnection(StormMessageWriter & writer, StormSocketServerConnectionId id);
    void SendPacketToConnectionBlocking(StormMessageWriter & writer, StormSocketServerConnectionId id);

    void FreeOutgoingPacket(StormMessageWriter & writer);
    void FreeIncomingPacket(StormMessageReader & reader);
    void FinalizeConnection(StormSocketServerConnectionId id);
    void ForceDisconnect(StormSocketServerConnectionId id);

  private:

    StormSocketServerImpl m_Impl;
  };
}



