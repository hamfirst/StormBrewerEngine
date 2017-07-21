#pragma once

#include <QOpenGLWidget>

#include "Foundation/Time/FrameClock.h"

#include "Engine/Window/FakeWindow.h"
#include "Engine/Rendering/RenderState.h"
#include "Engine/Rendering/RenderUtil.h"

#include "Game/GameLevelList.h"
#include "Game/GameStageManager.h"

#include "GameClient/GameContainer.h"

class EditorContainer;

class GameClientWidget : public QOpenGLWidget
{
  Q_OBJECT
public:

  GameClientWidget(int client_index, QWidget *parent = Q_NULLPTR);
  ~GameClientWidget();

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

  void Update();

private:
  NotNullPtr<EditorContainer> m_Editor;

  Optional<FakeWindow> m_FakeWindow;
  Optional<GameContainer> m_GameContainer;
  DelegateLink<void> m_UpdateDelegate;

  int m_ClientIndex;
  bool m_ImeMode = false;
};
