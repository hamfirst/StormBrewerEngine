

#include <QTImer>
#include <QProcess>

#include "DocumentServerConnection.h"
#include "DocumentServer/DocumentServerMessages.refl.meta.h"

#include <StormRefl/StormReflJsonStd.h>

DocumentServerConnection::DocumentServerConnection() :
  m_WebSocket("localhost")
{
  connect(&m_WebSocket, &QWebSocket::connected, this, &DocumentServerConnection::connected);
  connect(&m_WebSocket, &QWebSocket::disconnected, this, &DocumentServerConnection::disconnected);
  connect(&m_WebSocket, &QWebSocket::textMessageReceived, this, &DocumentServerConnection::textMessageReceived);
}

void DocumentServerConnection::Connect(const char * host, unsigned int port)
{
  std::string url = std::string("ws://") + host + ":" + std::to_string(port) + "/";
  m_ReconnectUrl = QUrl(url.data());
  
  m_WebSocket.open(m_ReconnectUrl);
}

void DocumentServerConnection::StartDocumentServer()
{

}

void DocumentServerConnection::textMessageReceived(const QString &message)
{
  std::string message_str = message.toStdString();
  std::size_t length = message_str.length();

  const char * msg = message_str.data();
  const char * start_msg = msg;

  Hash hash = crc32begin();
  while (length > 0)
  {
    if (*msg == ' ' || *msg == 0)
    {
      break;
    }

    hash = crc32additive(hash, *msg);
    msg++;
  }

  hash = crc32end(hash);
  msg++;

  if (length == 0)
  {
    return;
  }

  DocumentServerMessageType type = DocumentServerMessageType::kUnknown;
  if (StormReflGetEnumFromHash(type, hash) == false)
  {
    return;
  }

  switch (type)
  {
  case DocumentServerMessageType::kInitComplete:
    {
      DocumentServerMessageInitComplete packet;
      if (StormReflParseJson(packet, msg) == false)
      {
        return;
      }

      if (packet.m_Version != kDocumentServerVersion)
      {
        m_WebSocket.close();
        return;
      }

      emit connectionComplete();
    }
    break;
  case DocumentServerMessageType::kOpenData:
    {
      DocumentServerMessageOpen packet;
      if (StormReflParseJson(packet, msg) == false)
      {
        return;
      }

      emit newEditorWindow(packet);
    }
    break;
  }
}

void DocumentServerConnection::connected()
{
  m_Connected = true;
}

void DocumentServerConnection::disconnected()
{
  if (m_Connected == false)
  {
    QTimer::singleShot(2000, this, &DocumentServerConnection::reconnectRetry);
  }
  else
  {
    emit connectionFailed();

    m_Connected = false;
    reconnectRetry();
  }
}

void DocumentServerConnection::reconnectRetry()
{
  m_WebSocket.open(m_ReconnectUrl);
}
