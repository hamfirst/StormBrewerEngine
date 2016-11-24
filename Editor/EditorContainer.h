#pragma once

#include <QMainWindow>


#include <memory>

#include "ui_EditorContainer.h"

#include "DocumentServerConnection.h"
#include "ConnectingDialog.h"

class QTabWidget;
class QOpenGLContext;
class QOffscreenSurface;

class EditorContainer : public QMainWindow
{
  Q_OBJECT

public:
  EditorContainer(QWidget *parent = Q_NULLPTR);
  ~EditorContainer();

  void OpenEditorForFile(const char * file);

  void closeEvent(QCloseEvent * ev) override;



public slots:

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

  void engineUpdate();

private:
  Ui::EditorContainerClass ui;

  QTabWidget * m_TabWidget;

  QOpenGLContext * m_Context;
  std::unique_ptr<QOffscreenSurface> m_Surface;

  ConnectingDialog m_ConnectingDialog;
  DocumentServerConnection m_DocServer;

  bool m_EngineInitialized;

};
