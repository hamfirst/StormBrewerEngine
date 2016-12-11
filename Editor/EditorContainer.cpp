

#include "EditorContainer.h"
#include "TextureViewer.h"
#include "FontViewer.h"
#include "AudioViewer.h"

#include <QTabWidget>
#include <QTimer>
#include <QDockWidget>
#include <QOpenGLContext>
#include <QOffscreenSurface>
#include <QMessageBox>
#include <QProcess>
#include <QApplication>
#include <QFileInfo>

#include "Foundation/Network/Network.h"

#include "Engine/Engine.h"
#include "Engine/Text/TextManager.h"

#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "Imm32.lib")
#pragma comment(lib, "Version.lib")

EditorContainer::EditorContainer(QWidget *parent) : 
  QMainWindow(parent)

{
  setDockOptions(QMainWindow::AllowNestedDocks | QMainWindow::AllowTabbedDocks | QMainWindow::AnimatedDocks | QMainWindow::GroupedDragging);
  setDockNestingEnabled(true);

  ui.setupUi(this);

  m_Context = new QOpenGLContext(this);
  m_Context->setShareContext(QOpenGLContext::globalShareContext());
  m_Context->create();

  m_Surface = std::make_unique<QOffscreenSurface>();
  m_Surface->setFormat(m_Context->format());
  m_Surface->create();

  m_EngineInitialized = false;

  connect(&m_DocServer, &DocumentServerConnection::connectionComplete, this, &EditorContainer::connectionComplete);
  connect(&m_DocServer, &DocumentServerConnection::connectionFailed, this, &EditorContainer::connectionFailed);
  connect(&m_DocServer, &DocumentServerConnection::newEditorWindow, this, &EditorContainer::newEditorWindow);
  connect(&m_DocServer, &DocumentServerConnection::closeEditorWindow, this, &EditorContainer::closeEditorWindow);
  connect(&m_DocServer, &DocumentServerConnection::finalizeRequest, this, &EditorContainer::finalizeRequest);
  connect(&m_DocServer, &DocumentServerConnection::applyChange, this, &EditorContainer::applyChange);
  connect(&m_DocServer, &DocumentServerConnection::changeState, this, &EditorContainer::changeState);
  connect(&m_DocServer, &DocumentServerConnection::createError, this, &EditorContainer::createError);
  connect(&m_DocServer, &DocumentServerConnection::openError, this, &EditorContainer::openError);
  connect(&m_DocServer, &DocumentServerConnection::saveError, this, &EditorContainer::saveError);

  QTimer * timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &EditorContainer::engineUpdate);
  timer->start(16);

  const char * doc_server_host = "localhost";

  if (ProbePort(doc_server_host, 27800, 100) == false)
  {
    if (!strcmp(doc_server_host, "localhost"))
    {
      QProcess::startDetached("DocumentServer");
    }
  }

  setMinimumSize(1280, 720);
  m_DocServer.Connect(doc_server_host, 27800);

  m_TabWidget = new QTabWidget();
  setCentralWidget(m_TabWidget);

  m_ConnectingDialog.show();
}

EditorContainer::~EditorContainer()
{

}

void EditorContainer::OpenEditorForFile(const char * file)
{
  std::size_t len = strlen(file);

  const char * extension = nullptr;
  for (int index = (int)len - 1; index >= 0; index--)
  {
    if (file[index] == '.')
    {
      extension = file + index + 1;
    }
  }

  if (extension == nullptr)
  {
    QMessageBox::warning(this, "Error opening file", QString(file) + QString(" has no extension"));
    return;
  }

  Hash extension_hash = crc32lowercase(extension);
  Hash png_hash = COMPILE_TIME_CRC32_STR("png");

  QWidget * widget = nullptr;
  switch (extension_hash)
  {
  case COMPILE_TIME_CRC32_STR("png"):
    widget = new TextureViewer(file);
    break;
  case COMPILE_TIME_CRC32_STR("ttf"):
    widget = new FontViewer(file);
    break;
  case COMPILE_TIME_CRC32_STR("wav"):
    widget = new AudioViewer(true, file);
    break;
  case COMPILE_TIME_CRC32_STR("ogg"):
    widget = new AudioViewer(false, file);
    break;
  }

  if (widget == nullptr)
  {
    QMessageBox::warning(this, "Error opening file", QString("Could not find proper editor for file: ") + QString(file));
    return;
  }

  m_TabWidget->addTab(widget, file);
}

void EditorContainer::closeEvent(QCloseEvent * ev)
{
  if (m_EngineInitialized)
  {
    EngineCleanup();
  }
}

void EditorContainer::connectionComplete()
{
  m_Context->makeCurrent(m_Surface.get());
  EngineInit();
  EngineRenderInit();

  QString exec_path = QFileInfo(QCoreApplication::applicationFilePath()).canonicalPath();
  exec_path += "/editor/OpenSans-Regular.ttf";

  g_TextManager.LoadFont(exec_path.toStdString().data(), -1, 12);

  m_EngineInitialized = true;

  m_ConnectingDialog.hide();
  show();

  OpenEditorForFile("Images/test.png");
  OpenEditorForFile("Sounds/DudeDeath.wav");
  OpenEditorForFile("Music/music.ogg");
  OpenEditorForFile("Fonts/arial.ttf");
}

void EditorContainer::connectionFailed()
{

}

void EditorContainer::newEditorWindow(const DocumentServerMessageOpen & open_request)
{

}

void EditorContainer::closeEditorWindow(const DocumentServerMessageClose & close_request)
{

}

void EditorContainer::finalizeRequest(const DocumentServerMessageFinalizeRequest & finalize_request)
{

}

void EditorContainer::applyChange(const DocumentServerMessageApplyChange & apply_change)
{

}

void EditorContainer::changeState(const DocumentServerMessageChangeState & change_state)
{

}

void EditorContainer::createError(const DocumentServerMessageCreateError & error)
{

}

void EditorContainer::openError(const DocumentServerMessageOpenError & error)
{

}

void EditorContainer::saveError(const DocumentServerMessageSaveError & error)
{

}

void EditorContainer::engineUpdate()
{
  if (m_EngineInitialized)
  {
    m_Context->makeCurrent(m_Surface.get());
    EngineUpdate();
  }
}
