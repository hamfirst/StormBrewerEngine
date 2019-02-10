
#include <Foundation/Buffer/BufferUtil.h>

#include "DocumentServerThread.h"

DocumentServerThread::DocumentServerThread() :
  m_ThreadStopRequested(true),
  m_ConnectionGen(0),
  m_EventQueue(4096),
  m_OutgoingQueue(4096)
{
}

DocumentServerThread::~DocumentServerThread()
{
  m_ThreadStopRequested = true;
  m_WebSocket.Close();
  m_Thread.join();
}

void DocumentServerThread::Connect(std::string host)
{
  if (m_ThreadStopRequested != true)
  {
    m_ThreadStopRequested = true;
    m_WebSocket.Close();
    m_Thread.join();
  }

  m_Host = host;
  m_ThreadStopRequested = false;
  m_Thread = std::thread(&DocumentServerThread::DocumentServerThreadMain, this);
}

bool DocumentServerThread::GetEvent(DocumentServerEvent & ev)
{
  return m_EventQueue.TryDequeue(ev);
}

void DocumentServerThread::SendData(int connection_gen, std::string && packet)
{
  m_OutgoingQueue.Enqueue(DocumentServerOutgoingMessage{ connection_gen, std::move(packet) });
}

void DocumentServerThread::DocumentServerThreadMain()
{
  bool connected = false;
  while (m_ThreadStopRequested == false)
  {
    if (connected == false)
    {
      m_WebSocket.StartConnect(m_Host.data(), 27800, "/", m_Host.data(), nullptr, 2000);
      if (m_WebSocket.IsConnected())
      {
        m_ConnectionGen++;
        while (m_EventQueue.Enqueue(DocumentServerEvent{ DocumentServerEventType::kConnected, std::to_string(m_ConnectionGen) }) == false)
        {
          if (m_ThreadStopRequested)
          {
            return;
          }

          std::this_thread::yield();
        }

        connected = true;
      }   
    }
    else
    {
      while (true)
      {
        if (m_WebSocket.IsConnected() == false)
        {
          while(m_EventQueue.Enqueue(DocumentServerEvent{ DocumentServerEventType::kDisconnected }) == false)
          {
            if (m_ThreadStopRequested)
            {
              return;
            }

            std::this_thread::yield();
          }
          connected = false;
          break;
        }

        DocumentServerOutgoingMessage outgoing;
        while (m_OutgoingQueue.TryDequeue(outgoing))
        {
          if (outgoing.m_ConnectionGen == m_ConnectionGen)
          {
            m_WebSocket.SendString(outgoing.m_Data);
          }
        }

        auto packet = m_WebSocket.PollPacket();
        if (!packet)
        {
          break;
        }

        m_EventQueue.Enqueue(DocumentServerEvent{ DocumentServerEventType::kData, BufferToString(packet->m_Buffer) });
      }

      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
  }
}
