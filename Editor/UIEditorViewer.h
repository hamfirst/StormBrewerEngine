#pragma once

#include <QOpenGLWidget>
#include <QToolBar>
#include <QCheckBox>

#include "Foundation/Delegate/DelegateLink.h"

#include "Engine/Rendering/ShaderProgram.h"
#include "Engine/Rendering/VertexBuffer.h"
#include "Engine/Rendering/VertexBufferBuilder.h"
#include "Engine/Rendering/VertexArray.h"
#include "Engine/Rendering/RenderState.h"
#include "Engine/Rendering/RenderUtil.h"
#include "Engine/Window/FakeWindow.h"
#include "Engine/UI/UIManager.h"

#include "Runtime/UI/UIDef.refl.h"

#include "QTUtil/QtLerpVar.h"

#include "UIEditorNode.h"
#include "DocumentValueWatcher.h"

class UIEditor;

class UIEditorViewer : public QOpenGLWidget
{
  Q_OBJECT
public:
  UIEditorViewer(NotNullPtr<UIEditor> editor, UIDef & ui, QWidget *parent = nullptr);
  ~UIEditorViewer();

  void ChangeSelection(const UIEditorNodeSelection & layer);
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

  void moveEvent(QMoveEvent * event) override;

  void focusInEvent(QFocusEvent * event) override;
  void focusOutEvent(QFocusEvent * event) override;
  void enterEvent(QEvent * event) override;
  void leaveEvent(QEvent * event) override;

public slots:

  void centerChanged();

private:
  NotNullPtr<UIEditor> m_Editor;
  UIDef & m_UI;

  DocumentValueWatcher m_Watcher;

  std::unique_ptr<QToolBar> m_ToolBar;
  std::unique_ptr<QCheckBox> m_Center;

  Optional<FakeWindow> m_FakeWindow;
  Optional<UIManager> m_UIManager;
  Optional<UIElementPtr<UIElementContainer>> m_RootReference;

  DelegateLink<void> m_UpdateDelegate;

  RenderState m_RenderState;
  RenderUtil m_RenderUtil;

  Optional<UIEditorNodeSelection> m_Selection;

  bool m_PlayMode;
  bool m_ImeMode;
};
