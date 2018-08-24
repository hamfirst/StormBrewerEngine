#pragma once

#include <QLayout>

#include <StormData/StormDataJson.h>
#include <StormData/StormDataChangePacket.h>
#include <StormData/StormDataSync.h>
#include <StormData/StormDataParent.h>

#include "DocumentEditorBase.h"
#include "DocumentEditorWidgetBase.h"

template <class DataType, typename Widget>
class DocumentEditor : public DocumentEditorBase
{
public:
  DocumentEditor(EditorContainer & editor_container, PropertyFieldDatabase & property_db, const std::string & root_path, DocumentOutputDelegate && output_delegate, QWidget *parent = nullptr) :
    DocumentEditorBase(editor_container, property_db, root_path, std::move(output_delegate), parent),
    m_Widget(nullptr),
    m_Layout(nullptr)
  {
    InitializeParentInfo(m_ClientCopy);
    InitializeParentInfo(m_ServerCopy);
  }

  virtual ~DocumentEditor()
  {
    ClearExistingContent();
  }

  virtual void GotDocumentChange(ReflectionChangeNotification & change) override
  { 
    StormDataApplyChangePacket(m_ServerCopy, change);    
    DocumentEditorBase::GotDocumentChange(change);
  }

  virtual void GotDocumentStateChange(DocumentState state, const std::string & document_data) override
  {
    ClearNotifyCallback(m_ClientCopy);

    if (state == DocumentState::kLoaded)
    {
      ClearExistingContent();

      StormReflParseJson(m_ServerCopy, document_data.c_str());
      StormReflParseJson(m_ClientCopy, document_data.c_str());

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

      m_Widget = new Widget(m_EditorContainer, m_PropertyDb, m_RootPath, m_ClientCopy, std::move(change_link_callback), std::move(begin_changes_callback), std::move(commit_changes_callback));
      m_Layout->addWidget(m_Widget);

      UpdateLinks();

      auto notify_callback = [](void * user_ptr, const ReflectionChangeNotification & change)
      {
        auto p_this = (DocumentEditor<DataType, Widget> *)user_ptr;

        if (p_this->m_IgnoreChanges == false)
        {
          p_this->QueueChange(change);
        }

        p_this->ApplyLocalChange(change);
      };

      SetNotifyCallback(m_ClientCopy, notify_callback, this);

      setLayout(m_Layout);
    }

    DocumentEditorBase::GotDocumentStateChange(state, document_data);
  }

  virtual void ApplyServerChange(const ReflectionChangeNotification & change) override
  {
    StormDataApplyChangePacket(m_ServerCopy, change);
  }

  virtual void ApplyLocalChange(const ReflectionChangeNotification & change) override
  {
    if (m_Widget)
    {
      m_Widget->TriggerChangeCallbacks(change);
    }
  }

  virtual void UpdateLinks() override
  {
    if (m_Widget)
    {
      m_Widget->UpdateLinks(m_Links);
    }
  }

  virtual void SyncHotSpots() override
  {
    m_IgnoreChanges = true;
    for (auto & hot_spot : m_HotSpots)
    {
      StormDataSync(m_ServerCopy, m_ClientCopy, hot_spot.data());
    }

    m_IgnoreChanges = false;

    m_HotSpots.clear();
  }


  virtual void ClearExistingContent() override
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

private:

  Widget * m_Widget;
  QHBoxLayout * m_Layout;

  DataType m_ClientCopy;
  DataType m_ServerCopy;
};
