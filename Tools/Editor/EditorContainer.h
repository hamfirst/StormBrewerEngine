#pragma once

#include <memory>
#include <unordered_map>

#include <QMainWindow>

#include <Foundation/Common.h>
#include <Foundation/PropertyMeta/PropertyFieldDatabase.h>

#include "ui_EditorContainer.h"

#include "ConnectingDialog.h"
#include "DocumentEditorBase.h"
#include "DocumentServerThread.h"

class QTabWidget;
class QOpenGLContext;
class QOffscreenSurface;

class GameHostWidget;
class DistributionContainer;

using DocumentEditorCreationDelegate = Delegate<DocumentEditorBase *, EditorContainer &, PropertyFieldDatabase &, const std::string &, DocumentOutputDelegate &&, QWidget *>;

class EditorContainer : public QMainWindow
{
  Q_OBJECT

public:
  EditorContainer(QWidget *parent = Q_NULLPTR);
  ~EditorContainer();

  void OpenEditorForFile(czstr file);
  void RegisterEditor(czstr asset_type, czstr file_extension, czstr default_dir, DocumentEditorCreationDelegate && widget_delegate);
  void CloseEditor(QWidget * editor, bool send_message);

  void AddRecentFile(const QString & filename);
  void RemoveRecentFile(const QString & filename);
  void UpdateRecentFiles();

  void DownloadBuild(int build_id);

protected:

  void closeEvent(QCloseEvent * ev) override;
  void dragEnterEvent(QDragEnterEvent * event) override;
  void dropEvent(QDropEvent* event) override;

public slots:

  void connectionComplete();
  void connectionFailed();

  void closeAllTabs();
  void closeTab(int index);

  void engineUpdate();

  void newFile();
  void newConfigFile();
  void open();
  void save();
  void close();
  void quit();
  void openRecentFile();

  void undo();
  void redo();

  void openDistList();
  void downloadLatest();
  void shutdownDocServer();

  void testBuildOnline();
  void testBuildOnlineWithoutOneClient();
  void testBuildBots();

protected:

  friend class GameHostWidget;
  friend class GameClientWidget;
  friend class DistributionContainer;

  void NotifyClientWindowClosed(NotNullPtr<QWidget> host_widget);

private:

  void HandleDocumentServerEvent(DocumentServerEvent & ev);
  std::pair<QWidget *, int> CreateEditorForFile(czstr file, uint32_t extension_hash);

private:

  struct DocumentTypeData
  {
    std::string m_Name;
    std::string m_FileExension;
    std::string m_DefaultDirectory;
  };

  struct DocumentEditorData
  {
    DocumentEditorBase * m_Editor;
    std::string m_Path;
  };

  Ui::EditorContainerClass ui;

  QTabWidget * m_TabWidget;

  static const int kNumRecentFiles = 10;
  QAction * m_RecentFileSeparator;
  QAction * m_RecentFiles[kNumRecentFiles];

  QOpenGLContext * m_Context;
  std::unique_ptr<QOffscreenSurface> m_Surface;

  std::vector<DocumentTypeData> m_DocumentTypes;
  std::unordered_map<uint32_t, DocumentEditorCreationDelegate> m_DocumentEditorCreationCallbacks;
  std::unordered_map<int, DocumentEditorData> m_DocumentEditors;

  ConnectingDialog m_ConnectingDialog;
  DocumentServerThread m_DocumentServerThread;

  bool m_Closing;
  bool m_EngineInitialized;
  bool m_WantsClose;
  int m_DocServerConnectionGen;
  int m_NextDocumentId;

  Optional<int> m_DownloadBuild;

  std::string m_RootPath;
  PropertyFieldDatabase m_PropertyDatabase;

  std::unique_ptr<DistributionContainer> m_DistList;
  std::vector<std::unique_ptr<QWidget>> m_HostWidgets;
  std::vector<std::unique_ptr<QWidget>> m_DeadWidgets;
};
