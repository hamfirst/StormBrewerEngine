
#include <gl3w/gl3w.h>

#include <QTimer>
#include <QEvent>
#include <QKeyEvent>

#include <SDL2/SDL_keyboard.h>

#include "Engine/EngineCommon.h"
#include "Engine/Shader/ShaderManager.h"
#include "Engine/Camera/Camera.h"
#include "Engine/Input/KeyboardState.h"
#include "Engine/Text/TextManager.h"

#include "GameClient/GameCamera.h"

#include "EditorContainer.h"
#include "VisualEffectEditorViewer.h"
#include "VisualEffectEditor.h"

extern DelegateList<void> g_GlobalUpdate;

VisualEffectEditorViewer::VisualEffectEditorViewer(NotNullPtr<VisualEffectEditor> editor, VisualEffectDef & ui, QWidget *parent) :
  QOpenGLWidget(parent),
  m_Editor(editor),
  m_VisualEffect(ui),
  m_Watcher(editor),
  m_ToolBar(std::make_unique<QToolBar>(this)),
  //m_Center(std::make_unique<QCheckBox>("From Center")),
  m_PlayMode(true),
  m_Magnification(1.0f),
  m_Dragging(false),
  m_Moving(false),
  m_EffectPos(0, 0)
{
  //m_ToolBar->addWidget(m_Center.get());
  //connect(m_Center.get(), &QCheckBox::stateChanged, this, &VisualEffectEditorViewer::centerChanged);

  setFocusPolicy(Qt::ClickFocus);
  setMouseTracking(true);

  m_Watcher.SetPath("", false, true, [] {return true; });
  m_Watcher.SetAllUpdateCallbacks([this] {Refresh(); });
}

VisualEffectEditorViewer::~VisualEffectEditorViewer()
{

}

void VisualEffectEditorViewer::ChangeSelection(const VisualEffectEditorNodeSelection & layer)
{
  m_Selection = layer;
  repaint();
}

void VisualEffectEditorViewer::ClearSelection()
{
  m_Selection.Clear();
  repaint();
}

void VisualEffectEditorViewer::Refresh()
{
  m_VisualEffectManager.Emplace();
  auto fx = m_VisualEffectManager->CreateVisualEffect(&m_VisualEffect, 0, m_EffectPos);
  m_Handle = fx->GetHandle();
}

void VisualEffectEditorViewer::initializeGL()
{
  m_RenderState.InitRenderState(width(), height());
  m_RenderState.SetRenderSize(Vector2(kDefaultResolutionWidth, kDefaultResolutionHeight));
  m_RenderUtil.LoadShaders();

  auto window_geo = geometry();
  auto window_pos = mapToGlobal(QPoint(window_geo.x(), window_geo.y()));
  auto window_box = Box{ Vector2{ window_pos.x(), window_pos.y() }, Vector2{ window_pos.x() + window_geo.width(), window_pos.y() + window_geo.height() } };

  m_FakeWindow.Emplace(
    window_box,
    [this] {},
    [this] {},
    [this](int x, int y) { QCursor::setPos(x, y); },
    [this] { close(); },
    [this](NullOptPtr<Box> box) { m_ImeMode = true; },
    [this] { m_ImeMode = false; }
  );

  auto cursor_pos = mapFromGlobal(QCursor::pos());

  if (window_geo.contains(cursor_pos))
  {
    m_FakeWindow->SetWindowMouseFocused(true);
  }

  if (hasFocus())
  {
    m_FakeWindow->SetWindowKeyboardFocused(true);
  }

  m_FakeWindow->HandleMouseMoveMessage(cursor_pos.x(), cursor_pos.y());
  m_UpdateDelegate = g_GlobalUpdate.AddDelegate([this] { Update(); });

  Refresh();
}

void VisualEffectEditorViewer::Update()
{
  if (!m_FakeWindow)
  {
    return;
  }

  auto pos = mapToGlobal(QPoint(0, 0));
  m_FakeWindow->SetWindowPos(Vector2(pos.x(), pos.y()));

  if (m_PlayMode)
  {
    auto viewport = Box::FromFrameCenterAndSize(Vector2(0, 0), m_RenderState.GetRenderSize());
    m_VisualEffectManager->Update(viewport);
  }

  auto fx_pos = m_EffectPos;
  if (m_Moving)
  {
    fx_pos.x += 100 * sinf((float)GetTimeSeconds());
  }

  auto fx = m_Handle.Resolve();
  if (fx)
  {
    fx->SetPosition(fx_pos);
  }

  repaint();
}

void VisualEffectEditorViewer::StartPlayMode()
{
  m_PlayMode = true;
}

void VisualEffectEditorViewer::StopPlayMode()
{
  m_PlayMode = false;
}

void VisualEffectEditorViewer::resizeGL(int w, int h)
{
  if (m_FakeWindow)
  {
    m_FakeWindow->SetWindowSize(Vector2(w, h));
    m_RenderState.SetScreenSize(Vector2(w, h));
  }
}

void VisualEffectEditorViewer::paintGL()
{
  Color color(100, 149, 237, 255);

  glClearColor(color.r, color.g, color.b, color.a);
  glClear(GL_COLOR_BUFFER_BIT);

  m_FPSClock.Update();

  if (m_VisualEffectManager)
  {
    auto viewport = Box::FromFrameCenterAndSize(Vector2(0, 0), m_RenderState.GetRenderSize());

    DrawList draw_list;
    m_VisualEffectManager->DrawAllEffects(viewport, draw_list);

    auto size = RenderVec2{ kDefaultResolutionWidth, kDefaultResolutionHeight } *m_Magnification.Get();
    m_RenderState.SetRenderSize(size);

    auto & shader = g_ShaderManager.GetDefaultShader();
    shader.Bind();
    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_ScreenSize"), size);

    GameContainer * container = nullptr;
    draw_list.Draw(*container, viewport, {}, m_RenderState, m_RenderUtil);
  }

  std::string fps_data = std::to_string(m_FPSClock.GetFrameCount());
  g_TextManager.SetTextPos(Vector2(40, 10));
  g_TextManager.SetPrimaryColor();
  g_TextManager.SetShadowColor();
  g_TextManager.SetTextMode(TextRenderMode::kOutlined);
  g_TextManager.ClearTextBounds();
  g_TextManager.RenderText(fps_data.data(), -1, m_RenderState);
}

void VisualEffectEditorViewer::showEvent(QShowEvent * ev)
{
  setFocus();
}

void VisualEffectEditorViewer::closeEvent(QCloseEvent * ev)
{

}

void VisualEffectEditorViewer::keyPressEvent(QKeyEvent * event)
{
  if (!m_FakeWindow)
  {
    return;
  }

  //if (m_ImeMode)
  //{
  //  auto text = event->text().toStdString();
  //  m_FakeWindow->HandleTextInputCommit(text.data());
  //  event->text();
  //}

  //auto scan_code = KeyboardState::ScanCodeFromQtCode(event->key());
  //m_FakeWindow->HandleKeyPressMessage(SDL_GetKeyFromScancode((SDL_Scancode)scan_code), scan_code, true);
}

void VisualEffectEditorViewer::keyReleaseEvent(QKeyEvent * event)
{
  if (!m_FakeWindow)
  {
    return;
  }

  //auto scan_code = KeyboardState::ScanCodeFromQtCode(event->key());
  //m_FakeWindow->HandleKeyPressMessage(SDL_GetKeyFromScancode((SDL_Scancode)scan_code), scan_code, false);
}

void VisualEffectEditorViewer::mousePressEvent(QMouseEvent * event)
{
  if (!m_FakeWindow)
  {
    return;
  }

  if (event->button() == Qt::RightButton)
  {
    Refresh();
  }

  if (event->button() == Qt::LeftButton)
  {
    m_Dragging = true;
    grabMouse();

    RenderVec2 screen_pos = { event->pos().x(), height() - event->pos().y() - 1 };
    m_EffectPos = m_RenderState.ScreenPixelsToRenderPixels(screen_pos);
  }

  if (event->button() == Qt::MidButton)
  {
    m_Moving = !m_Moving;
  }

  //int button;
  //if (event->button() == Qt::LeftButton)
  //{
  //  button = kMouseLeftButton;
  //}
  //else if (event->button() == Qt::MiddleButton)
  //{
  //  button = kMouseMiddleButton;
  //}
  //else if (event->button() == Qt::RightButton)
  //{
  //  button = kMouseRightButton;
  //}
  //else
  //{
  //  return;
  //}

  //m_FakeWindow->HandleMouseButtonPressMessage(button, true);
}

void VisualEffectEditorViewer::mouseMoveEvent(QMouseEvent *event)
{
  if (!m_FakeWindow)
  {
    return;
  }

  if (m_Dragging)
  {
    RenderVec2 screen_pos = { event->pos().x(), height() - event->pos().y() - 1 };
    m_EffectPos = m_RenderState.ScreenPixelsToRenderPixels(screen_pos);
  }

  //m_FakeWindow->HandleMouseMoveMessage(event->x(), event->y());
}

void VisualEffectEditorViewer::mouseReleaseEvent(QMouseEvent * event)
{
  if (!m_FakeWindow)
  {
    return;
  }


  if (event->button() == Qt::LeftButton)
  {
    m_Dragging = false;
    releaseMouse();
  }

  //int button;
  //if (event->button() == Qt::LeftButton)
  //{
  //  button = kMouseLeftButton;
  //}
  //else if (event->button() == Qt::MiddleButton)
  //{
  //  button = kMouseMiddleButton;
  //}
  //else if (event->button() == Qt::RightButton)
  //{
  //  button = kMouseRightButton;
  //}
  //else
  //{
  //  return;
  //}

  //m_FakeWindow->HandleMouseButtonPressMessage(button, false);
}

void VisualEffectEditorViewer::wheelEvent(QWheelEvent * ev)
{
  if (ev->delta() < 0)
  {
    m_Magnification.LerpTo(m_Magnification.GetTarget() * 1.25f, 0.25f);
  }
  else
  {
    m_Magnification.LerpTo(m_Magnification.GetTarget() * 0.8f, 0.25f);
  }
}

void VisualEffectEditorViewer::moveEvent(QMoveEvent * event)
{
  if (!m_FakeWindow)
  {
    return;
  }

  //auto pos = mapToGlobal(QPoint(0, 0));
  //m_FakeWindow->SetWindowPos(Vector2(pos.x(), pos.y()));
}

void VisualEffectEditorViewer::focusInEvent(QFocusEvent * event)
{
  if (!m_FakeWindow)
  {
    return;
  }

  m_FakeWindow->SetWindowKeyboardFocused(true);
}

void VisualEffectEditorViewer::focusOutEvent(QFocusEvent * event)
{
  if (!m_FakeWindow)
  {
    return;
  }

  m_FakeWindow->SetWindowKeyboardFocused(false);
}

void VisualEffectEditorViewer::enterEvent(QEvent * event)
{
  if (!m_FakeWindow)
  {
    return;
  }

  m_FakeWindow->SetWindowMouseFocused(true);
}

void VisualEffectEditorViewer::leaveEvent(QEvent * event)
{
  if (!m_FakeWindow)
  {
    return;
  }

  m_FakeWindow->SetWindowMouseFocused(false);
}

void VisualEffectEditorViewer::centerChanged()
{
  Refresh();
}

