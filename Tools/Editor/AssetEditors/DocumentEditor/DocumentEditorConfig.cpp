
#include "AssetEditors/DocumentEditor/DocumentEditorConfig.h"

DocumentEditorConfig::DocumentEditorConfig(EditorContainer & editor_container, ConfigRegistrationInfo & config_info, 
                                           PropertyFieldDatabase & property_db, const std::string & root_path, DocumentOutputDelegate && output_delegate, QWidget *parent) :
  DocumentEditorBase(editor_container, property_db, root_path, std::move(output_delegate), parent),
  m_ConfigInfo(config_info),
  m_Widget(nullptr),
  m_Layout(nullptr),
  m_ClientCopy(config_info.CreateConfigData()),
  m_ServerCopy(config_info.CreateConfigData())
{
  config_info.InitializeParentInfo(m_ClientCopy.GetRaw());
  config_info.InitializeParentInfo(m_ServerCopy.GetRaw());
}

DocumentEditorConfig::~DocumentEditorConfig()
{
  ClearExistingContent();
}

void DocumentEditorConfig::GotDocumentChange(ReflectionChangeNotification & change)
{
  m_ConfigInfo.ApplyChangePacket(m_ServerCopy.GetRaw(), change);
  DocumentEditorBase::GotDocumentChange(change);
}

void DocumentEditorConfig::GotDocumentStateChange(DocumentState state, const std::string & document_data)
{
  m_ConfigInfo.ClearNotifyCallback(m_ClientCopy.GetRaw());

  if (state == DocumentState::kLoaded)
  {
    ClearExistingContent();

    m_ConfigInfo.ParseJson(m_ServerCopy.GetRaw(), document_data.c_str());
    m_ConfigInfo.ParseJson(m_ClientCopy.GetRaw(), document_data.c_str());

    m_HotSpots.clear();

    m_Layout = new QHBoxLayout();

    auto change_link_callback = DocumentChangeLinkDelegate([this](bool add, czstr source_asset, czstr remote_path, czstr local_path) {
      if (add)
      {
        QueueAddLink(source_asset, remote_path, local_path);
      }
      else
      {
        QueueRemoveLink(source_asset, remote_path, local_path);
      }
    });

    auto begin_changes_callback = DocumentBeginTransactionDelegate([this]() {
      BeginTransaction();
    });

    auto commit_changes_callback = DocumentCommitChangesDelegate([this]() {
      CommitQueuedChanges();
    });

    m_Widget = new ConfigEditor(m_EditorContainer, m_PropertyDb, m_RootPath, m_ClientCopy.GetRaw(), m_ConfigInfo,
      std::move(change_link_callback), std::move(begin_changes_callback), std::move(commit_changes_callback));

    m_Layout->addWidget(m_Widget);

    UpdateLinks();

    auto notify_callback = [](void * user_ptr, const ReflectionChangeNotification & change)
    {
      auto p_this = (DocumentEditorConfig *)user_ptr;

      if (p_this->m_IgnoreChanges == false)
      {
        p_this->QueueChange(change);
      }

      p_this->ApplyLocalChange(change);
    };

    m_ConfigInfo.SetNotifyCallback(m_ClientCopy.GetRaw(), notify_callback, this);

    setLayout(m_Layout);
  }

  DocumentEditorBase::GotDocumentStateChange(state, document_data);
}

void DocumentEditorConfig::ApplyServerChange(const ReflectionChangeNotification & change)
{
  m_ConfigInfo.ApplyChangePacket(m_ServerCopy.GetRaw(), change);
}

void DocumentEditorConfig::ApplyLocalChange(const ReflectionChangeNotification & change)
{
  if (m_Widget)
  {
    m_Widget->TriggerChangeCallbacks(change);
  }
}

void DocumentEditorConfig::UpdateLinks()
{
  if (m_Widget)
  {
    m_Widget->UpdateLinks(m_Links);
  }
}

void DocumentEditorConfig::SyncHotSpots()
{
  m_IgnoreChanges = true;
  for (auto & hot_spot : m_HotSpots)
  {
    m_ConfigInfo.Sync(m_ServerCopy.GetRaw(), m_ClientCopy.GetRaw(), hot_spot.data());
  }

  m_IgnoreChanges = false;

  m_HotSpots.clear();
}

void DocumentEditorConfig::ClearExistingContent()
{
  if (m_Widget)
  {
    m_Widget->AboutToClose();
    delete m_Widget;
  }

  if (m_Layout)
  {
    delete m_Layout;
  }

  m_Widget = nullptr;
  m_Layout = nullptr;

  DocumentEditorBase::ClearExistingContent();
}

