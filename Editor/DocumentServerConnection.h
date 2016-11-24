#pragma once

#include <QObject>
#include <QWebSocket>

#include "DocumentServer/DocumentServerMessages.refl.h"

class DocumentServerConnection : public QObject
{
  Q_OBJECT;

public:
  DocumentServerConnection();

  void Connect(const char * host, unsigned int port);
  void StartDocumentServer();


public slots:

  void textMessageReceived(const QString &message);
  void connected();
  void disconnected();

  void reconnectRetry();

signals:
  void connectionComplete();
  void connectionFailed();

  void newEditorWindow(const DocumentServerMessageOpen & open_request);
  void closeEditorWindow(const DocumentServerMessageClose & close_request);

  void finalizeRequest(const DocumentServerMessageFinalizeRequest & finalize_request);
  void applyChange(const DocumentServerMessageApplyChange & apply_change);
  void changeState(const DocumentServerMessageChangeState & change_state);

  void createError(const DocumentServerMessageCreateError & error);
  void openError(const DocumentServerMessageOpenError & error);
  void saveError(const DocumentServerMessageSaveError & error);

private:

  QWebSocket m_WebSocket;

  bool m_Connected = false;
  QUrl m_ReconnectUrl;
};

