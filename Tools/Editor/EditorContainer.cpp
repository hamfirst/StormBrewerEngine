

#include <QTabWidget>
#include <QSurfaceFormat>
#include <QOpenGLFunctions>
#include <QTimer>
#include <QDockWidget>
#include <QOpenGLContext>
#include <QOffscreenSurface>
#include <QMessageBox>
#include <QProcess>
#include <QEvent>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QApplication>
#include <QFileInfo>
#include <QFileDialog>
#include <QSettings>
#include <QDir>
#include <QDebug>


#include "StormRefl/StormReflJson.h"
#include "StormRefl/StormReflMetaEnum.h"

#include "StormData/StormDataChangePacket.h"

#include "Foundation/Network/Network.h"
#include "Foundation/FileSystem/Path.h"

#include "Engine/Engine.h"
#include "Engine/Text/TextManager.h"
#include "Engine/Component/ComponentSystem.h"

#include "Runtime/Runtime.h"
#include "Runtime/Config/ConfigManager.h"

#include "GameClient/GameShaders.h"

#include "DocumentServer/DocumentServerMessages.refl.meta.h"

#include "EditorContainer.h"
#include "SelectFromListDialog.h"
#include "TextureViewer.h"
#include "FontViewer.h"
#include "AudioViewer.h"
#include "DocumentEditorWidgetBase.h"
#include "DocumentEditorConfig.h"
#include "DistributionContainer.h"
#include "GameServerWidget.h"
#include "GameClientWidget.h"
#include "GameHostWidget.h"
#include "MapEditorTypes.refl.meta.h"

#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "Imm32.lib")
#pragma comment(lib, "Version.lib")

Delegate<void> g_GlobalUndo;
Delegate<void> g_GlobalRedo;

DelegateList<void> g_GlobalUpdate;

EditorContainer::EditorContainer(QWidget *parent) : 
  QMainWindow(parent)
{
  EngineInit(false, true);
  const char * doc_server_host = "localhost";
  
  printf("Attempting to connect to doc server\n");
  if (ProbePort(doc_server_host, 27800, 100) == false)
  {
    if (!strcmp(doc_server_host, "localhost"))
    {
      printf("Starting new document server\n");
      auto doc_server_path = QDir::cleanPath(QDir::currentPath() + QDir::separator() + "documentserver");

      if(QProcess::startDetached(doc_server_path) == false)
      {
        printf("Failed to start document server from %s\n", doc_server_path.toStdString().c_str());
      }
    }
  }

  printf("Starting up editor\n");

#ifdef _MSC_VER
  AllocConsole();
  AttachConsole(GetCurrentProcessId());
  freopen("CON", "w", stdout);
#endif

  setDockOptions(QMainWindow::AllowNestedDocks | QMainWindow::AllowTabbedDocks | QMainWindow::AnimatedDocks | QMainWindow::GroupedDragging);
  setDockNestingEnabled(true);

  setAcceptDrops(true);
  setDocumentMode(true);
  setMinimumSize(300, 300);

  g_DocumentRegistrationEditor = this;
  g_DocumentRegistrationCallList.CallAll();

  ui.setupUi(this);
  resize(1280, 720);

  auto new_config = ui.menu_New->addAction("Config");
  connect(new_config, &QAction::triggered, this, &EditorContainer::newConfigFile);

  std::sort(m_DocumentTypes.begin(), m_DocumentTypes.end(), [](const DocumentTypeData & a, const DocumentTypeData & b) { return a.m_Name < b.m_Name; });

  for (auto & doc_type : m_DocumentTypes)
  {
    auto action = ui.menu_New->addAction(doc_type.m_Name.data());
    action->setData(QString(doc_type.m_Name.data()));
    connect(action, &QAction::triggered, this, &EditorContainer::newFile);
  }

  connect(ui.action_Open, &QAction::triggered, this, &EditorContainer::open);
  ui.action_Open->setShortcut(QKeySequence::Open);
  connect(ui.action_Save, &QAction::triggered, this, &EditorContainer::save);
  ui.action_Save->setShortcut(QKeySequence::Save);
  connect(ui.action_Quit, &QAction::triggered, this, &EditorContainer::quit);
  ui.action_Quit->setShortcut(QKeySequence::Quit);

  connect(ui.action_Undo, &QAction::triggered, this, &EditorContainer::undo);
  ui.action_Undo->setShortcut(QKeySequence::Undo);
  connect(ui.action_Redo, &QAction::triggered, this, &EditorContainer::redo);
  ui.action_Redo->setShortcut(QKeySequence::Redo);

  connect(ui.action_TestBuild, &QAction::triggered, this, &EditorContainer::testBuildOnline);
  ui.action_TestBuild->setShortcut(QKeySequence(Qt::Key_F7));

  connect(ui.action_TestBuildWithoutOneClient, &QAction::triggered, this, &EditorContainer::testBuildOnlineWithoutOneClient);

  connect(ui.action_TestBuildWithBots, &QAction::triggered, this, &EditorContainer::testBuildBots);
  ui.action_TestBuildWithBots->setShortcut(QKeySequence(Qt::Key_F6));

  connect(ui.actionBuild_List, &QAction::triggered, this, &EditorContainer::openDistList);
  connect(ui.actionDownload_Latest, &QAction::triggered, this, &EditorContainer::downloadLatest);
  connect(ui.actionShutdown, &QAction::triggered, this, &EditorContainer::shutdownDocServer);


  m_RecentFileSeparator = ui.menuFile->addSeparator();
  for (int index = 0; index < kNumRecentFiles; index++)
  {
    m_RecentFiles[index] = new QAction(this);
    m_RecentFiles[index]->setVisible(false);
    connect(m_RecentFiles[index], &QAction::triggered, this, &EditorContainer::openRecentFile);
    ui.menuFile->addAction(m_RecentFiles[index]);
  }

  m_RootPath = GetCanonicalRootPath();

  UpdateRecentFiles();

  m_EngineInitialized = false;
  m_Closing = false;
  m_WantsClose = false;

  QTimer * timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &EditorContainer::engineUpdate);
  timer->start(10);

  m_DocServerConnectionGen = 0;
  m_DocumentServerThread.Connect(doc_server_host);

  m_TabWidget = new QTabWidget();
  m_TabWidget->setTabsClosable(true);
  m_TabWidget->setDocumentMode(true);
  m_TabWidget->tabBar()->setDrawBase(false);
  setCentralWidget(m_TabWidget);
  m_TabWidget->setFocus();
  connect(m_TabWidget, &QTabWidget::tabCloseRequested, this, &EditorContainer::closeTab);

  m_ConnectingDialog.show();


  printf("Creating offscreen surface\n");
  auto global_context = QOpenGLContext::globalShareContext();

  m_Context = new QOpenGLContext(this);
  m_Context->setShareContext(global_context);
  m_Context->create();

  m_Surface = std::make_unique<QOffscreenSurface>();
  m_Surface->setFormat(m_Context->format());
  m_Surface->create();

  m_Context->makeCurrent(m_Surface.get());

  InitServerTypes();
  EngineRenderInit();
  RegisterGameplayShaders();

  g_ComponentTypeSystem.LoadPropertyDatabase(m_PropertyDatabase);
  RuntimeRegisterTypes(m_PropertyDatabase);

  GetProperyMetaData<MapEditorAnchorInitData>(m_PropertyDatabase);

  QString exec_path = QFileInfo(QCoreApplication::applicationFilePath()).canonicalPath();
  g_TextManager.LoadFont("./Fonts/FFF.ttf", -1, 8);

  m_EngineInitialized = true;
  m_NextDocumentId = 1;

  g_GlobalUndo = [this] { undo(); };
  g_GlobalRedo = [this] { redo(); };
}

EditorContainer::~EditorContainer()
{
  EngineCleanup();

  for (auto itr = m_DocumentEditors.begin(); itr != m_DocumentEditors.end(); ++itr)
  {
    delete itr->second.m_Editor;
  }
}

void EditorContainer::OpenEditorForFile(czstr file)
{
  for (auto & elem : m_DocumentEditors)
  {
    if (elem.second.m_Path == file)
    {
      auto tab = m_TabWidget->indexOf(elem.second.m_Editor);
      if (tab != -1)
      {
        m_TabWidget->setCurrentIndex(tab);
        return;
      }
    }
  }

  std::size_t len = strlen(file);

  auto extension = GetFileExtensionForPath(std::string(file));
  if (extension.length() == 0)
  {
    QMessageBox::warning(this, "Error opening file", QString(file) + QString(" has no extension"));
    return;
  }

  auto file_name = GetFileNameForCanonicalPath(std::string(file));
  Hash extension_hash = crc32lowercase(extension);

  QWidget * widget = nullptr;
  switch (extension_hash)
  {
  case COMPILE_TIME_CRC32_STR("png"):
    widget = new TextureViewer(file);
    break;
  case COMPILE_TIME_CRC32_STR("ttf"):
  case COMPILE_TIME_CRC32_STR("otf"):
    widget = new FontViewer(file);
    break;
  case COMPILE_TIME_CRC32_STR("wav"):
    widget = new AudioViewer(true, file);
    break;
  case COMPILE_TIME_CRC32_STR("ogg"):
    widget = new AudioViewer(false, file);
    break;
  default:
    {
      auto editor = CreateEditorForFile(file, extension_hash);
      if (editor.first == nullptr)
      {
        break;
      }

      m_DocumentServerThread.SendData(m_DocServerConnectionGen, std::string("kOpen ") + std::to_string(editor.second) + ' ' + file);
      widget = editor.first;
    }
    break;
  }

  if (widget == nullptr)
  {
    QMessageBox::warning(this, "Error opening file", QString("Could not find proper editor for file: ") + QString(file));
    return;
  }

  AddRecentFile(file);

  m_TabWidget->addTab(widget, file_name.data());
  m_TabWidget->setCurrentWidget(widget);
}

void EditorContainer::RegisterEditor(czstr asset_type, czstr file_extension, czstr default_dir, DocumentEditorCreationDelegate && widget_delegate)
{
  m_DocumentTypes.emplace_back(DocumentTypeData{ asset_type, file_extension, default_dir });
  m_DocumentEditorCreationCallbacks.emplace(std::make_pair(crc32(file_extension + 1), std::move(widget_delegate)));
}

void EditorContainer::CloseEditor(QWidget * editor, bool send_message)
{
  auto index = m_TabWidget->indexOf(editor);
  if (index == -1)
  {
    return;
  }

  m_TabWidget->removeTab(index);

  for (auto itr = m_DocumentEditors.begin(); itr != m_DocumentEditors.end(); ++itr)
  {
    if (itr->second.m_Editor == editor)
    {
      if (send_message)
      {
        m_DocumentServerThread.SendData(m_DocServerConnectionGen, std::string("kClose ") + std::to_string(itr->first));
      }

      delete itr->second.m_Editor;
      m_DocumentEditors.erase(itr);
      return;
    }
  }
}

void EditorContainer::AddRecentFile(const QString & filename)
{
  QSettings settings;
  auto files = settings.value("recent_files").toStringList();

  files.removeAll(filename);
  files.prepend(filename);

  while (files.size() > kNumRecentFiles)
  {
    files.removeLast();
  }

  settings.setValue("recent_files", files);

  UpdateRecentFiles();
}

void EditorContainer::RemoveRecentFile(const QString & filename)
{
  QSettings settings;
  auto files = settings.value("recent_files").toStringList();
  files.removeAll(filename);
  settings.setValue("recent_files", files);

  UpdateRecentFiles();
}

void EditorContainer::UpdateRecentFiles()
{
  QSettings settings;
  auto files = settings.value("recent_files").toStringList();

  while (files.size() > kNumRecentFiles)
  {
    files.removeLast();
  }

  int max_recent = kNumRecentFiles;
  int num_files = std::min((int)files.size(), max_recent);

  m_RecentFileSeparator->setVisible(num_files > 0);

  for (int index = 0; index < num_files; index++)
  {
    QFileInfo file_info(QString(m_RootPath.data()) + '/' + files[index]);
    auto menu_option = QString("&%1 - %2").arg(index + 1).arg(file_info.fileName());
    m_RecentFiles[index]->setText(menu_option);
    m_RecentFiles[index]->setData(files[index]);
    m_RecentFiles[index]->setVisible(true);
  }

  for (int index = num_files; index < kNumRecentFiles; index++)
  {
    m_RecentFiles[index]->setVisible(false);
  }
}

void EditorContainer::DownloadBuild(int build_id)
{
  m_DownloadBuild = build_id;
  m_WantsClose = true;
}

void EditorContainer::closeEvent(QCloseEvent * ev)
{
  m_Closing = true;
  m_HostWidgets.clear();

  closeAllTabs();

  if (m_EngineInitialized)
  {
    EngineCleanup();
  }

  if(m_DownloadBuild)
  {
#ifdef _MSC_VER
    auto fetch_path = QDir::cleanPath(QDir::currentPath() + QDir::separator() + "DownloadBuild.bat");
#else
    auto fetch_path = QDir::cleanPath(QDir::currentPath() + QDir::separator() + "DownloadBuild.sh");
#endif
    QStringList args;

    if(m_DownloadBuild.Value() >= 0)
    {
      args.push_back(QString::number(m_DownloadBuild.Value()));
    }

    if(QProcess::startDetached(fetch_path, args))
    {
      m_DocumentServerThread.SendData(m_DocServerConnectionGen, std::string("kShutdown"));
    }
  }
}

void EditorContainer::dragEnterEvent(QDragEnterEvent * event)
{
  if (event->mimeData()->hasFormat("text/uri-list"))
  {
    event->acceptProposedAction();
  }
}

void EditorContainer::dropEvent(QDropEvent* event)
{
  auto mime_data = event->mimeData();

  bool show_error = false;

  if (mime_data->hasUrls())
  {
    QList<QUrl> file_list = mime_data->urls();
    for (int index = 0; index < file_list.size(); index++)
    {
      auto filename = file_list.at(index).toLocalFile();

      auto canonical_filename = filename.toStdString();
      if (ConvertToCanonicalPath(canonical_filename, m_RootPath) == false)
      {
        show_error = true;
        continue;
      }

      OpenEditorForFile(canonical_filename.data());
    }
  }

  if (show_error)
  {
    QMessageBox::warning(this, "Error opening file", "One or more of the files was not in the document root path", QMessageBox::Ok);
  }
}

void EditorContainer::connectionComplete()
{
  m_ConnectingDialog.close();
  show();
}

void EditorContainer::connectionFailed()
{
  m_ConnectingDialog.show();
  hide();

  closeAllTabs();
}

void EditorContainer::closeAllTabs()
{
  for (int index = m_TabWidget->count() - 1; index >= 0; --index)
  {
    closeTab(index);
  }
}

void EditorContainer::closeTab(int index)
{
  auto close_widget = m_TabWidget->widget(index);
  CloseEditor(close_widget, true);
}

void EditorContainer::engineUpdate()
{
  if (m_EngineInitialized)
  {
    m_Context->makeCurrent(m_Surface.get());
    EngineUpdate();

    g_GlobalUpdate.Call();
  }

  DocumentServerEvent ev;
  while (m_DocumentServerThread.GetEvent(ev))
  {
    HandleDocumentServerEvent(ev);
  }

  m_DeadWidgets.clear();

  if(m_WantsClose)
  {
    QApplication::closeAllWindows();
  }
}

void EditorContainer::newFile()
{
  QAction * action = qobject_cast<QAction *>(sender());
  if (action)
  {
    auto document_type = action->data().toString();
    auto document_type_str = document_type.toStdString();
    
    DocumentTypeData * doc_type_data = nullptr;
    for (auto & doc_type : m_DocumentTypes)
    {
      if (doc_type.m_Name == document_type_str)
      {
        doc_type_data = &doc_type;
      }
    }

    if (doc_type_data == nullptr)
    {
      return;
    }

    auto caption = tr("New ") + document_type + tr(" File");
    auto filter = document_type + tr(" (*") + doc_type_data->m_FileExension.c_str() + ")";
    auto dir = GetCanonicalRootPath() + doc_type_data->m_DefaultDirectory + "/";
    auto filename = QFileDialog::getSaveFileName(this, caption, dir.data(), filter);

    if (filename.length() == 0)
    {
      return;
    }

    auto canonical_filename = filename.toStdString();
    if(ConvertToCanonicalPath(canonical_filename, m_RootPath) == false)
    {
      QMessageBox::warning(this, "Error creating file", "File is not inside the document root path", QMessageBox::Ok);
      return;
    }

    auto file_name = GetFileNameForCanonicalPath(std::string(canonical_filename));

    auto extension = GetFileExtensionForPath(canonical_filename);

    auto extension_hash = crc32(extension);
    auto editor = CreateEditorForFile(canonical_filename.data(), extension_hash);
    if (editor.first == nullptr)
    {
      QMessageBox::warning(this, "Error creating file", QString("Could not find proper editor for file: ") + QString(filename));
      return;
    }

    m_DocumentServerThread.SendData(m_DocServerConnectionGen, std::string("kNew ") + std::to_string(editor.second) + ' ' + canonical_filename);

    AddRecentFile(canonical_filename.data());

    m_TabWidget->addTab(editor.first, file_name.data());
    m_TabWidget->setCurrentWidget(editor.first);
  }
}

void EditorContainer::newConfigFile()
{
  QStringList config_options;

  auto visitor = [&](ConfigRegistrationInfo & elem)
  {
    auto option = elem.m_ConfigType + " (*." + elem.m_ConfigExtension + ")";
    config_options.append(option.data());
  };

  g_ConfigTypeManager.VisistTypes(std::move(visitor));

  auto dialog = new SelectFromListDialog(config_options);
  auto result = dialog->exec();

  if (result == QDialog::Rejected)
  {
    return;
  }

  if (dialog->GetSelectedIndex() == -1)
  {
    return;
  }

  auto & elem = g_ConfigTypeManager.GetTypeForIndex(dialog->GetSelectedIndex());


  auto caption = std::string("New ") + elem.m_ConfigType + " File";
  auto filter = elem.m_ConfigType + " (*." + elem.m_ConfigExtension.c_str() + ")";
  auto dir = GetCanonicalRootPath() + elem.m_DefaultDirectory + "/";
  auto filename = QFileDialog::getSaveFileName(this, caption.data(), dir.data(), filter.data());

  if (filename.length() == 0)
  {
    return;
  }

  auto canonical_filename = filename.toStdString();
  if (ConvertToCanonicalPath(canonical_filename, m_RootPath) == false)
  {
    QMessageBox::warning(this, "Error creating file", "File is not inside the document root path", QMessageBox::Ok);
    return;
  }

  auto file_name = GetFileNameForCanonicalPath(std::string(canonical_filename));

  auto extension = GetFileExtensionForPath(canonical_filename);

  auto extension_hash = crc32(extension);
  auto editor = CreateEditorForFile(canonical_filename.data(), extension_hash);
  if (editor.first == nullptr)
  {
    QMessageBox::warning(this, "Error creating file", QString("Could not find proper editor for file: ") + QString(filename));
    return;
  }

  m_DocumentServerThread.SendData(m_DocServerConnectionGen, std::string("kNew ") + std::to_string(editor.second) + ' ' + canonical_filename);
  AddRecentFile(canonical_filename.data());

  m_TabWidget->addTab(editor.first, file_name.data());
  m_TabWidget->setCurrentWidget(editor.first);
}

void EditorContainer::open()
{
  auto filename = QFileDialog::getOpenFileName(this, tr("Open File"), m_RootPath.data(), tr("All Files (*.*)"));
  if (filename.length() == 0)
  {
    return;
  }

  auto canonical_filename = filename.toStdString();
  if (ConvertToCanonicalPath(canonical_filename, m_RootPath) == false)
  {
    QMessageBox::warning(this, "Error opening file", "File is not inside the document root path", QMessageBox::Ok);
    return;
  }

  OpenEditorForFile(canonical_filename.data());
}

void EditorContainer::save()
{
  auto current_tab = m_TabWidget->currentWidget();
  for (auto & editor : m_DocumentEditors)
  {
    if (editor.second.m_Editor == current_tab)
    {
      m_DocumentServerThread.SendData(m_DocServerConnectionGen, std::string("kSave ") + std::to_string(editor.first));
      return;
    }
  }
}

void EditorContainer::close()
{

}

void EditorContainer::quit()
{
  QApplication::closeAllWindows();
}

void EditorContainer::openRecentFile()
{
  QAction * action = qobject_cast<QAction *>(sender());
  if (action)
  {
    auto file_name = action->data().toString().toStdString();
    OpenEditorForFile(file_name.c_str());
  }
}

void EditorContainer::undo()
{
  auto current_tab = m_TabWidget->currentWidget();
  for (auto & editor : m_DocumentEditors)
  {
    if (editor.second.m_Editor == current_tab)
    {
      m_DocumentServerThread.SendData(m_DocServerConnectionGen, std::string("kUndo ") + std::to_string(editor.first));
      return;
    }
  }
}

void EditorContainer::redo()
{
  auto current_tab = m_TabWidget->currentWidget();
  for (auto & editor : m_DocumentEditors)
  {
    if (editor.second.m_Editor == current_tab)
    {
      m_DocumentServerThread.SendData(m_DocServerConnectionGen, std::string("kRedo ") + std::to_string(editor.first));
      return;
    }
  }
}

void EditorContainer::openDistList()
{
  if(m_DistList.get() == nullptr)
  {
    m_DistList = std::make_unique<DistributionContainer>(this);
  }

  m_DistList->show();
}

void EditorContainer::downloadLatest()
{
  auto reply = QMessageBox::question(this, "Downloading Build...", "Are you sure you want to download the latest build??",
                                     QMessageBox::Yes|QMessageBox::No);
  if (reply == QMessageBox::Yes)
  {
    DownloadBuild(0);
  }
}

void EditorContainer::shutdownDocServer()
{
  m_DocumentServerThread.SendData(m_DocServerConnectionGen, std::string("kShutdown"));
}

void EditorContainer::testBuildOnline()
{
  m_HostWidgets.emplace_back(std::make_unique<GameHostWidget>(this, 2));
  m_HostWidgets.back()->show();
}

void EditorContainer::testBuildOnlineWithoutOneClient()
{
  m_HostWidgets.emplace_back(std::make_unique<GameHostWidget>(this, 3));
  m_HostWidgets.back()->show();
}

void EditorContainer::testBuildBots()
{
  m_HostWidgets.emplace_back(std::make_unique<GameClientWidget>(this, 0, true));
  m_HostWidgets.back()->show();
}

void EditorContainer::NotifyClientWindowClosed(NotNullPtr<QWidget> host_widget)
{
  if (m_Closing)
  {
    return;
  }

  if(m_DistList.get() == host_widget)
  {
    m_DeadWidgets.emplace_back(std::move(m_DistList));
    return;
  }

  for (auto itr = m_HostWidgets.begin(), end = m_HostWidgets.end(); itr != end; ++itr)
  {
    if (itr->get() == host_widget)
    {
      m_DeadWidgets.emplace_back(std::move(*itr));
      m_HostWidgets.erase(itr);
      return;
    }
  }
}

void EditorContainer::HandleDocumentServerEvent(DocumentServerEvent & ev)
{
  if (ev.m_Type == DocumentServerEventType::kConnected)
  {
    m_DocServerConnectionGen = atoi(ev.m_Data.data());
    connectionComplete();
  }
  else if (ev.m_Type == DocumentServerEventType::kDisconnected)
  {
    connectionFailed();
  }
  else
  {
    const char * data = ev.m_Data.c_str();
    qInfo() << data;

    auto enum_hash = crc32begin();
    while (*data != ' ')
    {
      if (*data == 0)
      {
        return;
      }

      enum_hash = crc32additive(enum_hash, *data);
      data++;
    }

    enum_hash = crc32end(enum_hash);

    DocumentClientMessageType type;
    if (StormReflGetEnumFromHash(type, enum_hash) == false)
    {
      return;
    }

    data++;
    int document_id;
    if (StormReflParseJson(document_id, data, data) == false)
    {
      return;
    }

    auto itr = m_DocumentEditors.find(document_id);
    if (itr == m_DocumentEditors.end())
    {
      return;
    }

    switch (type)
    {
    case DocumentClientMessageType::kNewFileError:
      QMessageBox::warning(this, "Error creating file", QString("Got file creation error: ") + data);
      RemoveRecentFile(itr->second.m_Path.data());
      CloseEditor(itr->second.m_Editor, false);
      return;
    case DocumentClientMessageType::kOpenFileError:
      QMessageBox::warning(this, "Error opening file", QString("Got file open error: ") + data);
      RemoveRecentFile(itr->second.m_Path.data());
      CloseEditor(itr->second.m_Editor, false);
      return;
    case DocumentClientMessageType::kCheckoutError:
      QMessageBox::warning(this, "Error checking out file", QString("Got error checking out file: ") + data);
      return;
    case DocumentClientMessageType::kDocumentState:
      {
        int document_state;
        if (StormReflParseJson(document_state, data, data) == false)
        {
          return;
        }

        data++;
        int document_gen;
        if (StormReflParseJson(document_gen, data, data) == false)
        {
          return;
        }

        data++;
        itr->second.m_Editor->GotDocumentStateChange((DocumentState)document_state, data);
      }
      return;
    case DocumentClientMessageType::kChange:
      {
        data++;
        int document_gen;
        if (StormReflParseJson(document_gen, data, data) == false)
        {
          return;
        }

        data++;
        std::vector<std::string> change_packets;
        if (StormReflParseJson(change_packets, data, data) == false)
        {
          return;
        }
        
        for (auto & elem : change_packets)
        {
          ReflectionChangeNotification change;
          if (StormDataParseChangePacket(change, elem.data()) == false)
          {
            return;
          }

          itr->second.m_Editor->GotDocumentChange(change);
        }

        itr->second.m_Editor->DocumentChangeComplete();
      }
      return;
    case DocumentClientMessageType::kDocumentClosed:
      {
        CloseEditor(itr->second.m_Editor, false);
      }
      return;
    case DocumentClientMessageType::kChangeOk:
      {
        itr->second.m_Editor->GotServerChangeOkay();
      }
      return;
    case DocumentClientMessageType::kChangeLinks:
      {
        itr->second.m_Editor->LinksChanged(data);
      }
      return;
    default:
      return;
    }
  }
}

std::pair<QWidget *, int> EditorContainer::CreateEditorForFile(czstr file, uint32_t extension_hash)
{
  auto itr = m_DocumentEditorCreationCallbacks.find(extension_hash);
  if (itr == m_DocumentEditorCreationCallbacks.end())
  {
    auto config_info = g_ConfigTypeManager.GetConfigRegistrationInfoByExtensionHash(extension_hash);
   
    if (config_info == nullptr)
    {
      return{};
    }

    DocumentOutputDelegate del = [this, doc_id = m_NextDocumentId](DocumentServerMessageType type, const std::string & args)
    {
      m_DocumentServerThread.SendData(m_DocServerConnectionGen, std::string(StormReflGetEnumAsString(type)) + ' ' + std::to_string(doc_id) + ' ' + args);
    };

    auto editor = new DocumentEditorConfig(*this, *config_info, m_PropertyDatabase, m_RootPath, std::move(del), nullptr);

    m_DocumentEditors.emplace(std::make_pair(m_NextDocumentId, DocumentEditorData{ editor, file }));
    m_NextDocumentId++;

    return std::make_pair(editor, m_NextDocumentId - 1);
  }

  DocumentOutputDelegate del = [this, doc_id = m_NextDocumentId](DocumentServerMessageType type, const std::string & args)
  {
    m_DocumentServerThread.SendData(m_DocServerConnectionGen, std::string(StormReflGetEnumAsString(type)) + ' ' + std::to_string(doc_id) + ' ' + args);
  };

  auto editor = itr->second(*this, m_PropertyDatabase, m_RootPath, std::move(del), nullptr);

  m_DocumentEditors.emplace(std::make_pair(m_NextDocumentId, DocumentEditorData{ editor, file }));
  m_NextDocumentId++;

  return std::make_pair(editor, m_NextDocumentId - 1);
}
