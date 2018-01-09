
#include <gl3w/gl3w.h>

#include <QTimer>
#include <QEvent>
#include <QKeyEvent>

#include <SDL2/SDL_keyboard.h>

#include "Engine/EngineCommon.h"
#include "Engine/Shader/ShaderManager.h"
#include "Engine/Camera/Camera.h"
#include "Engine/Input/KeyboardState.h"
#include "Engine/Rendering/GeometryVertexBufferBuilder.h"

#include "GameClient/GameCamera.h"

#include "EditorContainer.h"
#include "UIEditorViewer.h"
#include "UIEditor.h"

extern DelegateList<void> g_GlobalUpdate;

UIEditorViewer::UIEditorViewer(NotNullPtr<UIEditor> editor, UIDef & ui, QWidget *parent) :
  QOpenGLWidget(parent),
  m_Editor(editor),
  m_UI(ui),
  m_Watcher(editor),
  m_ToolBar(std::make_unique<QToolBar>(this)),
  m_Center(std::make_unique<QCheckBox>("From Center")),
  m_PlayMode(true)
{
  m_ToolBar->addWidget(m_Center.get());
  connect(m_Center.get(), &QCheckBox::stateChanged, this, &UIEditorViewer::centerChanged);

  setFocusPolicy(Qt::ClickFocus);
  setMouseTracking(true);

  m_Watcher.SetPath("", false, true, [] {return true; });
  m_Watcher.SetAllUpdateCallbacks([this] {Refresh(); });
}

UIEditorViewer::~UIEditorViewer()
{

}

void UIEditorViewer::ChangeSelection(const UIEditorNodeSelection & layer)
{
  m_Selection = layer;
  repaint();
}

void UIEditorViewer::ClearSelection()
{
  m_Selection.Clear();
  repaint();
}

void UIEditorViewer::Refresh()
{
  m_RootReference.Clear();

  UIElementContainerData container_data;

  if (m_Center->isChecked())
  {
    container_data.m_StartX = kDefaultResolutionWidth / 2;
    container_data.m_StartY = kDefaultResolutionHeight / 2;
    container_data.m_EndX = kDefaultResolutionWidth;
    container_data.m_EndY = kDefaultResolutionHeight;
  }
  else
  {
    container_data.m_StartX = 0;
    container_data.m_StartY = 0;
    container_data.m_EndX = kDefaultResolutionWidth;
    container_data.m_EndY = kDefaultResolutionHeight;
  }

  m_UIManager.Emplace(m_FakeWindow->GetWindow());
  m_RootReference = m_UIManager->AllocateContainer("container", nullptr, {}, container_data);
  m_UIManager->AllocateElementFromDef("root", m_UI, m_RootReference->Get(), true);
  m_UIManager->Update(*m_FakeWindow->GetWindow().GetInputState(), m_RenderState);
}

void UIEditorViewer::initializeGL()
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
    [this] { makeCurrent(); glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebufferObject()); },
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

void UIEditorViewer::Update()
{
  if (!m_FakeWindow)
  {
    return;
  }

  auto pos = mapToGlobal(QPoint(0, 0));
  m_FakeWindow->SetWindowPos(Vector2(pos.x(), pos.y()));

  if (m_PlayMode)
  {
    m_UIManager->Update(*m_FakeWindow->GetWindow().GetInputState(), m_RenderState);
  }

  repaint();
}

void UIEditorViewer::StartPlayMode()
{
  m_PlayMode = true;
}

void UIEditorViewer::StopPlayMode()
{
  m_PlayMode = false;
}

void UIEditorViewer::resizeGL(int w, int h)
{
  if (m_FakeWindow)
  {
    m_FakeWindow->SetWindowSize(Vector2(w, h));
    m_RenderState.SetScreenSize(Vector2(std::max(w + 100, 1), std::max(h + 100, 1)));
  }
}

void UIEditorViewer::paintGL()
{
  Color color(100, 149, 237, 255);

  glClearColor(color.r, color.g, color.b, color.a);
  glClear(GL_COLOR_BUFFER_BIT);

  auto & shader = g_ShaderManager.GetDefaultScreenSpaceShader();
  m_RenderState.BindShader(shader);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_ScreenSize"), Vector2f(kDefaultResolutionWidth + 100, kDefaultResolutionHeight + 100));
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), Color(255, 255, 255, 255));
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), 1.0f, 0.0f, 0.0f, 1.0f);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), Vector2f(kDefaultResolutionWidth, kDefaultResolutionHeight) * -0.5f);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Texture"), 0);

  GeometryVertexBufferBuilder builder;
  builder.Rectangle(Box::FromPoints(Vector2(0, 0), Vector2(kDefaultResolutionWidth, kDefaultResolutionHeight)), 2.0f, Color(255, 255, 255, 255));
  builder.DrawDefault(m_RenderState, m_RenderUtil);

  if (m_UIManager)
  {
    m_RenderState.SetRenderSize(Vector2f(kDefaultResolutionWidth + 100, kDefaultResolutionHeight + 100));
    m_UIManager->Render(m_RenderState, m_RenderUtil);
  }
}

void UIEditorViewer::showEvent(QShowEvent * ev)
{
  setFocus();
}

void UIEditorViewer::closeEvent(QCloseEvent * ev)
{

}

void UIEditorViewer::keyPressEvent(QKeyEvent * event)
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

void UIEditorViewer::keyReleaseEvent(QKeyEvent * event)
{
  if (!m_FakeWindow)
  {
    return;
  }

  //auto scan_code = KeyboardState::ScanCodeFromQtCode(event->key());
  //m_FakeWindow->HandleKeyPressMessage(SDL_GetKeyFromScancode((SDL_Scancode)scan_code), scan_code, false);
}

void UIEditorViewer::mousePressEvent(QMouseEvent * event)
{
  if (!m_FakeWindow)
  {
    return;
  }

  if (event->button() == Qt::RightButton)
  {
    Refresh();
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

void UIEditorViewer::mouseMoveEvent(QMouseEvent *event)
{
  if (!m_FakeWindow)
  {
    return;
  }

  //m_FakeWindow->HandleMouseMoveMessage(event->x(), event->y());
}

void UIEditorViewer::mouseReleaseEvent(QMouseEvent * event)
{
  if (!m_FakeWindow)
  {
    return;
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

void UIEditorViewer::moveEvent(QMoveEvent * event)
{
  if (!m_FakeWindow)
  {
    return;
  }

  //auto pos = mapToGlobal(QPoint(0, 0));
  //m_FakeWindow->SetWindowPos(Vector2(pos.x(), pos.y()));
}

void UIEditorViewer::focusInEvent(QFocusEvent * event)
{
  if (!m_FakeWindow)
  {
    return;
  }

  m_FakeWindow->SetWindowKeyboardFocused(true);
}

void UIEditorViewer::focusOutEvent(QFocusEvent * event)
{
  if (!m_FakeWindow)
  {
    return;
  }

  m_FakeWindow->SetWindowKeyboardFocused(false);
}

void UIEditorViewer::enterEvent(QEvent * event)
{
  if (!m_FakeWindow)
  {
    return;
  }

  m_FakeWindow->SetWindowMouseFocused(true);
}

void UIEditorViewer::leaveEvent(QEvent * event)
{
  if (!m_FakeWindow)
  {
    return;
  }

  m_FakeWindow->SetWindowMouseFocused(false);
}

void UIEditorViewer::centerChanged()
{
  Refresh();
}

