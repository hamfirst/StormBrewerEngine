#pragma once

#include <QOpenGLWidget>
#include <QToolBar>
#include <QCheckBox>

#include "Foundation/Delegate/DelegateLink.h"
#include "Foundation/FileSystem/FileSystemWatcher.h"
#include "Foundation/Time/StopWatch.h"

#include "Engine/Rendering/ShaderProgram.h"
#include "Engine/Rendering/VertexBuffer.h"
#include "Engine/Rendering/VertexBufferBuilder.h"
#include "Engine/Rendering/VertexArray.h"
#include "Engine/Rendering/RenderState.h"
#include "Engine/Window/FakeWindow.h"
#include "Engine/UI/UIManager.h"

#include "Runtime/UI/UIDef.refl.h"

#include "QTUtil/QtLerpVar.h"

#include "DocumentValueWatcher.h"

class UIEditor;

class UIEditorViewer : public QOpenGLWidget
{
  Q_OBJECT
public:
  UIEditorViewer(NotNullPtr<UIEditor> editor, UIDef & ui, QWidget *parent = nullptr);
  ~UIEditorViewer();

protected:

  void Refresh();
  void Update();

protected:


  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

  void showEvent(QShowEvent * ev) override;
  void closeEvent(QCloseEvent * ev) override;

  void keyPressEvent(QKeyEvent * event) override;
  void keyReleaseEvent(QKeyEvent * event) override;

  void mousePressEvent(QMouseEvent * event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent * event) override;

  void moveEvent(QMoveEvent * event) override;
  void wheelEvent(QWheelEvent * event) override;

  void focusInEvent(QFocusEvent * event) override;
  void focusOutEvent(QFocusEvent * event) override;
  void enterEvent(QEvent * event) override;
  void leaveEvent(QEvent * event) override;

public slots:

  void centerChanged();

private:
  NotNullPtr<UIEditor> m_Editor;
  UIDef & m_UI;

  StopWatch m_FrameTimer;
  DocumentValueWatcher m_Watcher;

  Optional<FileSystemWatcher> m_FileSystemWatcher;

  Optional<FakeWindow> m_FakeWindow;
  std::unique_ptr<UIManager> m_UIManager;

  DelegateLink<void> m_UpdateDelegate;

  RenderState m_RenderState;
  bool m_ImeMode;
};
