#pragma once

#include <QOpenGLWidget>
#include <QToolBar>
#include <QCheckBox>

#include "Foundation/Delegate/DelegateLink.h"
#include "Foundation/Time/FPSClock.h"

#include "Engine/Rendering/ShaderProgram.h"
#include "Engine/Rendering/VertexBuffer.h"
#include "Engine/Rendering/VertexBufferBuilder.h"
#include "Engine/Rendering/VertexArray.h"
#include "Engine/Rendering/RenderState.h"
#include "Engine/Rendering/RenderUtil.h"
#include "Engine/Window/FakeWindow.h"
#include "Engine/VisualEffect/VisualEffectManager.h"

#include "Runtime/VisualEffect/VisualEffectDef.refl.h"

#include "Foundation/Lerp/LerpVar.h"

#include "QTUtil/QtLerpVar.h"

#include "VisualEffectEditorNodeSelection.h"
#include "DocumentValueWatcher.h"

class VisualEffectEditor;

class VisualEffectEditorViewer : public QOpenGLWidget
{
  Q_OBJECT
public:
  VisualEffectEditorViewer(NotNullPtr<VisualEffectEditor> editor, VisualEffectDef & ui, QWidget *parent = nullptr);
  ~VisualEffectEditorViewer();

  void ChangeSelection(const VisualEffectEditorNodeSelection & layer);
  void ClearSelection();


protected:

  void Refresh();
  void Update();

  void StartPlayMode();
  void StopPlayMode();

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
  void wheelEvent(QWheelEvent * ev) override;

  void moveEvent(QMoveEvent * event) override;

  void focusInEvent(QFocusEvent * event) override;
  void focusOutEvent(QFocusEvent * event) override;
  void enterEvent(QEvent * event) override;
  void leaveEvent(QEvent * event) override;

  public slots:

  void centerChanged();

private:
  NotNullPtr<VisualEffectEditor> m_Editor;
  VisualEffectDef & m_VisualEffect;

  DocumentValueWatcher m_Watcher;

  std::unique_ptr<QToolBar> m_ToolBar;
  std::unique_ptr<QCheckBox> m_Center;

  Optional<FakeWindow> m_FakeWindow;
  Optional<VisualEffectManager> m_VisualEffectManager;

  DelegateLink<void> m_UpdateDelegate;

  RenderState m_RenderState;
  RenderUtil m_RenderUtil;

  Optional<VisualEffectEditorNodeSelection> m_Selection;

  LerpVar m_Magnification;
  bool m_Dragging;
  Vector2f m_EffectPos;
  VisualEffectHandle m_Handle;

  FPSClock m_FPSClock;

  ShaderProgram m_GridShader;
  int m_GridWidth = 16;
  int m_GridHeight = 16;
  bool m_DrawGrid = true;

  bool m_PlayMode;
  bool m_Moving;
  bool m_ImeMode;
};
