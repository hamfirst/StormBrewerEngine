#pragma once

#include <string>
#include <thread>

#include <StormSockets/StormMessageQueue.h>

#include <Foundation/Common.h>
#include <Foundation/Network/WebSocket.h>

enum class DocumentServerEventType
{
  kConnected,
  kDisconnected,
  kData,
};

struct DocumentServerEvent
{
  DocumentServerEventType m_Type;
  std::string m_Data;
};

struct DocumentServerOutgoingMessage
{
  int m_ConnectionGen;
  std::string m_Data;
};

class DocumentServerThread
{
public:
  DocumentServerThread();
  ~DocumentServerThread();

  void Connect(std::string host);
  void Disconnect();
  bool GetEvent(DocumentServerEvent & ev);
  void SendData(int connection_gen, std::string && packet);

private:

  void DocumentServerThreadMain();

private:
  std::string m_Host;
  std::thread m_Thread;
  volatile bool m_ThreadStopRequested;

  int m_ConnectionGen;

  WebSocket m_WebSocket;
  StormSockets::StormMessageQueue<DocumentServerEvent> m_EventQueue;
  StormSockets::StormMessageQueue<DocumentServerOutgoingMessage> m_OutgoingQueue;
};

