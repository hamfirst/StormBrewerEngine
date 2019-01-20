
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

#include "Foundation/FileSystem/Path.h"

#include "EditorContainer.h"
#include "UIEditorViewer.h"
#include "UIEditor.h"


extern DelegateList<void> g_GlobalUpdate;

UIEditorViewer::UIEditorViewer(NotNullPtr<UIEditor> editor, UIDef & ui, QWidget *parent) :
  QOpenGLWidget(parent),
  m_Editor(editor),
  m_UI(ui),
  m_Watcher(editor)
{
  setFocusPolicy(Qt::ClickFocus);
  setMouseTracking(true);

  m_Watcher.SetPath("", false, true, [] {return true; });
  m_Watcher.SetAllUpdateCallbacks([this] {Refresh(); });

  m_FrameTimer.Start();

}

UIEditorViewer::~UIEditorViewer()
{

}

void UIEditorViewer::Refresh()
{
  m_Editor->ClearErrors();

  time_t t = time(nullptr);
  char time_str[100];
  strftime(time_str, sizeof(time_str), "Loading Scripts: %T", localtime(&t));

  m_Editor->DisplayError(time_str);

  auto old_manager = m_UIManager ? std::move(m_UIManager) : std::unique_ptr<UIManager>();
  auto screen_size = Vector2(kDefaultResolutionWidth, kDefaultResolutionHeight);

  m_UIManager = std::make_unique<UIManager>(m_FakeWindow->GetWindow());
  m_UIManager->LoadScripts(screen_size, true,
          [this] { m_UIManager->PushUIDef(m_UI); }, [this](czstr err) { m_Editor->DisplayError(err); });

  auto & interface = m_UIManager->CreateGameInterface();
  for(auto elem : m_UI.m_Variables)
  {
    ScriptValue val;
    if(ScriptValueParse(elem.second.m_Value.c_str(), val))
    {
      interface.AddVariable(elem.second.m_Name.data(), val);
    }
  }

  for(auto elem : m_UI.m_Functions)
  {
    ScriptValue val;
    if(ScriptValueParse(elem.second.m_Value.c_str(), val))
    {
      interface.AddDebugStubFunction(elem.second.m_Name.data(), std::move(val), elem.second.m_DebugOutput);
    }
    else
    {
      interface.AddDebugStubFunction(elem.second.m_Name.data(), {}, elem.second.m_DebugOutput);
    }
  }

  m_UIManager->SetGlobal("in_editor", true);
  m_UIManager->Update(0.0f, *m_FakeWindow->GetWindow().GetInputState(), m_RenderState);
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
    [this] { m_ImeMode = false; },
    [this] { grabMouse(); },
    [this] { releaseMouse(); }
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

  auto root_path = GetCanonicalRootPath();
  auto script_path = GetFullPath(JoinPath(root_path, "./UIs/Scripts/"), root_path);
  m_FileSystemWatcher.Emplace(script_path, Delegate<void>{});

  Refresh();

}

void UIEditorViewer::Update()
{
  auto delta_time = static_cast<float>(m_FrameTimer.GetTimeSinceLastCheck());

  if (!m_FakeWindow)
  {
    return;
  }

  auto pos = mapToGlobal(QPoint(0, 0));
  m_FakeWindow->SetWindowPos(Vector2(pos.x(), pos.y()));

  bool reload = false;
  while(m_FileSystemWatcher->GetFileChange())
  {
    reload = true;
  }

  if(reload)
  {
    Refresh();
  }

  m_FakeWindow->GetWindow().Update();
  m_UIManager->Update(delta_time, *m_FakeWindow->GetWindow().GetInputState(), m_RenderState);

  repaint();
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
  m_RenderUtil.SetDefaultClearColor();
  m_RenderUtil.Clear();

  m_RenderState.MakeCurrent();

  m_RenderState.SetScreenSize(Vector2f(width(), height()));
  m_RenderState.SetRenderSize(Vector2f(width(), height()));

  GeometryVertexBufferBuilder builder;
  builder.Rectangle(Box::FromFrameCenterAndSize({}, Vector2(kDefaultResolutionWidth, kDefaultResolutionHeight)),
          1.0f, Color(0.0f, 0.0f, 0.0f, 1.0f));

  auto & vertex_buffer = m_RenderUtil.GetScratchBuffer();
  builder.FillVertexBuffer(vertex_buffer);

  auto & shader = g_ShaderManager.GetDefaultScreenSpaceShader();
  m_RenderState.BindShader(shader);

  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_ScreenSize"), RenderVec2{ m_RenderState.GetRenderSize() });
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), RenderVec2{ 0.0, 0.0 });
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), RenderVec4{ 1.0f, 0, 0, 1.0f });
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Texture"), 0);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), RenderVec4{ 1.0f, 1.0f, 1.0f, 1.0f });
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Bounds"), RenderVec4{ -1.0f, -1.0f, 1.0f, 1.0f });
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_ColorMatrix"), Mat4f());

  m_RenderState.BindTexture(m_RenderUtil.GetDefaultTexture());
  m_RenderState.BindVertexBuffer(vertex_buffer);
  m_RenderState.Draw();

  m_UIManager->Render(m_RenderState, m_RenderUtil);
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

  if(event->key() == Qt::Key_F5)
  {
    Refresh();
    return;
  }

  if(event->key() == Qt::Key_F4)
  {
    m_UIManager->ClearUI();
    return;
  }

  if (m_ImeMode)
  {
    auto text = event->text().toStdString();
    m_FakeWindow->HandleTextInputCommit(text.data());
    event->text();
  }

  auto scan_code = KeyboardState::ScanCodeFromQtCode(event->key());
  m_FakeWindow->HandleKeyPressMessage(SDL_GetKeyFromScancode((SDL_Scancode)scan_code), scan_code, true);
}

void UIEditorViewer::keyReleaseEvent(QKeyEvent * event)
{
  if (!m_FakeWindow)
  {
    return;
  }

  if(event->key() == Qt::Key_F5)
  {
    return;
  }

  if(event->key() == Qt::Key_F4)
  {
    return;
  }

  auto scan_code = KeyboardState::ScanCodeFromQtCode(event->key());
  m_FakeWindow->HandleKeyPressMessage(SDL_GetKeyFromScancode((SDL_Scancode)scan_code), scan_code, false);
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

  int button;
  if (event->button() == Qt::LeftButton)
  {
    button = kMouseLeftButton;
  }
  else if (event->button() == Qt::MiddleButton)
  {
    button = kMouseMiddleButton;
  }
  else if (event->button() == Qt::RightButton)
  {
    button = kMouseRightButton;
  }
  else
  {
    return;
  }

  m_FakeWindow->HandleMouseButtonPressMessage(button, true);
}

void UIEditorViewer::mouseMoveEvent(QMouseEvent *event)
{
  if (!m_FakeWindow)
  {
    return;
  }


//  auto pointer_pos = (Vector2)m_RenderState.ScreenPixelsToRenderPixels(Vector2(event->x(), event->y()));
//  auto info = std::to_string(pointer_pos.x) + " " + std::to_string(pointer_pos.y);
//  m_Editor->DisplayError(info.c_str());

  m_FakeWindow->HandleMouseMoveMessage(event->x(), event->y());
}

void UIEditorViewer::mouseReleaseEvent(QMouseEvent * event)
{
  if (!m_FakeWindow)
  {
    return;
  }

  int button;
  if (event->button() == Qt::LeftButton)
  {
    button = kMouseLeftButton;
  }
  else if (event->button() == Qt::MiddleButton)
  {
    button = kMouseMiddleButton;
  }
  else if (event->button() == Qt::RightButton)
  {
    button = kMouseRightButton;
  }
  else
  {
    return;
  }

  m_FakeWindow->HandleMouseButtonPressMessage(button, false);
}

void UIEditorViewer::moveEvent(QMoveEvent * event)
{
  if (!m_FakeWindow)
  {
    return;
  }

  auto pos = mapToGlobal(QPoint(0, 0));
  m_FakeWindow->SetWindowPos(Vector2(pos.x(), pos.y()));
}

void UIEditorViewer::wheelEvent(QWheelEvent * event)
{
  if (!m_FakeWindow)
  {
    return;
  }

  m_FakeWindow->HandleMouseWheelMessage(event->delta());
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

