
#include "StormSocketServer.h"
//#include "StormSocketServerWin.h"
#include "StormSocketServerASIO.h"

namespace StormSockets
{
  using ServerType = StormSocketServerASIO;

  StormSocketServer::StormSocketServer(StormSocketInitSettings & settings)
  {
    ServerType * server = new ServerType(settings);
    m_Impl = (StormSocketServerImpl)server;
  }

  StormSocketServer::StormSocketServer(StormSocketServer && rhs) noexcept
  {
    m_Impl = rhs.m_Impl;
    rhs.m_Impl = nullptr;
  }

  StormSocketServer::~StormSocketServer()
  {
    if (m_Impl)
    {
      ServerType * server = (ServerType *)m_Impl;
      delete server;
    }
  }

  StormSocketServer & StormSocketServer::operator = (StormSocketServer && rhs) noexcept
  {
    m_Impl = rhs.m_Impl;
    rhs.m_Impl = nullptr;
    return *this;
  }

  void StormSocketServer::Start()
  {
    ServerType * server = (ServerType *)m_Impl;
    server->Start();
  }

  bool StormSocketServer::GetEvent(StormSocketEventInfo & message)
  {
    ServerType * server = (ServerType *)m_Impl;
    return server->GetEvent(message);
  }

  StormMessageWriter StormSocketServer::CreateOutgoingPacket(StormSocketDataType::Index type, bool final)
  {
    ServerType * server = (ServerType *)m_Impl;
    return server->CreateOutgoingPacket(type, final);
  }

  void StormSocketServer::FinalizeOutgoingPacket(StormMessageWriter & writer)
  {
    ServerType * server = (ServerType *)m_Impl;
    return server->FinalizeOutgoingPacket(writer);
  }

  bool StormSocketServer::SendPacketToConnection(StormMessageWriter & writer, StormSocketServerConnectionId id)
  {
    ServerType * server = (ServerType *)m_Impl;
    return server->SendPacketToConnection(writer, id);
  }

  void StormSocketServer::SendPacketToConnectionBlocking(StormMessageWriter & writer, StormSocketServerConnectionId id)
  {
    ServerType * server = (ServerType *)m_Impl;
    return server->SendPacketToConnectionBlocking(writer, id);
  }

  void StormSocketServer::FreeOutgoingPacket(StormMessageWriter & writer)
  {
    ServerType * server = (ServerType *)m_Impl;
    return server->FreeOutgoingPacket(writer);
  }

  void StormSocketServer::FreeIncomingPacket(StormMessageReader & reader)
  {
    ServerType * server = (ServerType *)m_Impl;
    return server->FreeIncomingPacket(reader);
  }

  void StormSocketServer::FinalizeConnection(StormSocketServerConnectionId id)
  {
    ServerType * server = (ServerType *)m_Impl;
    return server->FinalizeConnection(id);
  }

  void StormSocketServer::ForceDisconnect(StormSocketServerConnectionId id)
  {
    ServerType * server = (ServerType *)m_Impl;
    return server->ForceDisconnect(id);
  }
}
