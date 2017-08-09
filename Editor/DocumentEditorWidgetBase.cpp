
#include <Foundation/Common.h>
#include <Foundation/FileSystem/Path.h>

#include <sb/vector.h>

#include <QFileDialog>

#include "DocumentEditorWidgetBase.h"

PreMainCallList g_DocumentRegistrationCallList;
EditorContainer * g_DocumentRegistrationEditor;

DocumentEditorWidgetBase::DocumentEditorWidgetBase(PropertyFieldDatabase & property_db, const std::string & root_path, DocumentChangeLinkDelegate && change_link_callback,
  DocumentBeginTransactionDelegate && begin_transaction_callback, DocumentCommitChangesDelegate && commit_change_callback, QWidget *parent) :
  QWidget(parent),
  m_PropertyDb(property_db),
  m_RootPath(root_path),
  m_IgnoreCallbacks(false),
  m_TriggeringCallbacks(false),
  m_ChangeLinkCallback(std::move(change_link_callback)),
  m_BeginTransactionCallback(std::move(begin_transaction_callback)),
  m_CommitChangesCallback(std::move(commit_change_callback))
{

}

DocumentEditorWidgetBase::~DocumentEditorWidgetBase()
{

}

uint64_t DocumentEditorWidgetBase::AddChangeCallback(uint64_t path_hash, DocumentExternalChangeCallback && callback)
{
  auto callback_id = GetRandomNumber64();
  
  auto itr = m_PathLookup.find(path_hash);
  if (itr == m_PathLookup.end())
  {
    auto result = m_PathLookup.emplace(std::make_pair(path_hash, std::vector<uint64_t>{}));
    itr = result.first;
  }

  itr->second.push_back(callback_id);

  m_ChangeCallbacks.emplace(std::make_pair(callback_id, std::move(callback)));
  return callback_id;
}

void DocumentEditorWidgetBase::RemoveChangeCallback(uint64_t path_hash, uint64_t callback_id)
{
  auto callback_itr = m_ChangeCallbacks.find(callback_id);

  if (m_TriggeringCallbacks)
  {
    if (callback_itr != m_ChangeCallbacks.end())
    {
      callback_itr->second = {};
    }

    m_DeadCallbacks.emplace_back(std::make_pair(path_hash, callback_id));
    return;
  }

  if (callback_itr != m_ChangeCallbacks.end())
  {
    m_ChangeCallbacks.erase(callback_itr);
  }

  auto itr = m_PathLookup.find(path_hash);
  if (itr != m_PathLookup.end())
  {
    vremove_quick(itr->second, callback_id);
  }
}

uint64_t DocumentEditorWidgetBase::AddParentChangeCallback(czstr path, DocumentExternalChangeCallback && callback)
{
  auto callback_id = GetRandomNumber64();

  ParentPathChangeCallbackData cb_data;
  cb_data.m_Callback = std::move(callback);
  cb_data.m_Path = path;
  cb_data.m_Defunct = false;

  if (m_TriggeringCallbacks)
  {
    m_NewParentChangeCallbacks.emplace_back(std::make_pair(callback_id, std::move(cb_data)));
    m_ParentChangeCallbackOperations.push_back(1);
  }
  else
  {
    m_ParentChangeCallbacks.emplace(callback_id, std::move(cb_data));
  }

  return callback_id;
}

void DocumentEditorWidgetBase::RemovParentChangeCallback(uint64_t callback_id)
{
  if (m_TriggeringCallbacks)
  {
    m_DeadParentChangeCallbacks.emplace_back(callback_id);
    m_ParentChangeCallbackOperations.push_back(0);
  }

  auto itr = m_ParentChangeCallbacks.find(callback_id);
  if (itr != m_ParentChangeCallbacks.end())
  {
    if (m_TriggeringCallbacks)
    {
      itr->second.m_Defunct = true;
    }
    else
    {
      m_ParentChangeCallbacks.erase(itr);
    }
  }
}

uint64_t DocumentEditorWidgetBase::AddChildChangeCallback(czstr path, DocumentExternalChangeCallback && callback)
{
  auto callback_id = GetRandomNumber64();

  ChildPathChangeCallbackData cb_data;
  cb_data.m_Callback = std::move(callback);
  cb_data.m_PathHash = crc64(path);
  cb_data.m_PathLength = strlen(path);
  cb_data.m_Defunct = false;

  if (m_TriggeringCallbacks)
  {
    m_NewChildChangeCallbacks.emplace_back(std::make_pair(callback_id, std::move(cb_data)));
    m_ChildChangeCallbackOperations.push_back(1);
  }
  else
  {
    m_ChildChangeCallbacks.emplace(callback_id, std::move(cb_data));
  }

  return callback_id;
}

void DocumentEditorWidgetBase::RemoveChildChangeCallback(uint64_t callback_id)
{
  if (m_TriggeringCallbacks)
  {
    m_DeadChildChangeCallbacks.emplace_back(callback_id);
    m_ChildChangeCallbackOperations.push_back(0);
  }

  auto itr = m_ChildChangeCallbacks.find(callback_id);
  if (itr != m_ChildChangeCallbacks.end())
  {
    if (m_TriggeringCallbacks)
    {
      itr->second.m_Defunct = true;
    }
    else
    {
      m_ChildChangeCallbacks.erase(itr);
    }
  }
}

void DocumentEditorWidgetBase::TriggerChangeCallbacks(const ReflectionChangeNotification & change)
{
  if (m_IgnoreCallbacks)
  {
    return;
  }

  m_TriggeringCallbacks = true;

  auto path_len = change.m_Path.size();
  for (auto & elem : m_ParentChangeCallbacks)
  {
    if (elem.second.m_Defunct == false && path_len < elem.second.m_Path.size())
    {
      auto len = path_len;
      auto callback_path_ptr = elem.second.m_Path.data();

      bool match = true;
      for (auto change_path_ptr = change.m_Path.data(); len > 0; --len, ++change_path_ptr, ++callback_path_ptr)
      {
        if (*callback_path_ptr != *change_path_ptr)
        {
          match = false;
          break;
        }
      }

      if (match)
      {
        elem.second.m_Callback(change);
      }
    }
  }

  m_TriggeringCallbacks = false;

  std::size_t new_parent_change_index = 0;
  std::size_t dead_parent_change_index = 0;

  for (auto & op : m_ParentChangeCallbackOperations)
  {
    if (op == 0)
    {
      m_ParentChangeCallbacks.erase(m_DeadParentChangeCallbacks[dead_parent_change_index]);
      dead_parent_change_index++;
    }
    else
    {
      m_ParentChangeCallbacks.emplace(std::move(m_NewParentChangeCallbacks[new_parent_change_index]));
      new_parent_change_index++;
    }
  }

  m_ParentChangeCallbackOperations.clear();
  m_DeadParentChangeCallbacks.clear();
  m_NewParentChangeCallbacks.clear();


  m_TriggeringCallbacks = true;

  for (auto & elem : m_ChildChangeCallbacks)
  {
    if (elem.second.m_Defunct == false && path_len > elem.second.m_PathLength)
    {
      auto path_hash = crc64begin();
      auto len = elem.second.m_PathLength;
      for (auto path_ptr = change.m_Path.data(); len > 0; --len, ++path_ptr)
      {
        path_hash = crc64additive(path_hash, *path_ptr);
      }

      path_hash = crc64end(path_hash);
      if (elem.second.m_PathHash == path_hash)
      {
        elem.second.m_Callback(change);
      }
    }
  }

  m_TriggeringCallbacks = false;

  std::size_t new_child_change_index = 0;
  std::size_t dead_child_change_index = 0;

  for (auto & op : m_ChildChangeCallbackOperations)
  {
    if (op == 0)
    {
      m_ChildChangeCallbacks.erase(m_DeadChildChangeCallbacks[dead_child_change_index]);
      dead_child_change_index++;
    }
    else
    {
      m_ChildChangeCallbacks.emplace(std::move(m_NewChildChangeCallbacks[new_child_change_index]));
      new_child_change_index++;
    }
  }

  m_ChildChangeCallbackOperations.clear();
  m_DeadChildChangeCallbacks.clear();
  m_NewChildChangeCallbacks.clear();

  auto hash = crc64(change.m_Path);

  auto itr = m_PathLookup.find(hash);
  if (itr == m_PathLookup.end())
  {
    return;
  }

  m_TriggeringCallbacks = true;

  for(std::size_t index = 0, end = itr->second.size(); index < end; index++)
  {
    auto callback_id = itr->second[index];
    auto callback = m_ChangeCallbacks.find(callback_id);
    callback->second(change);
  }

  m_TriggeringCallbacks = false;

  for (auto & callback_data : m_DeadCallbacks)
  {
    RemoveChangeCallback(callback_data.first, callback_data.second);
  }

  m_DeadCallbacks.clear();
}

void DocumentEditorWidgetBase::EnableChangeCallbacks()
{
  m_IgnoreCallbacks = false;
}

void DocumentEditorWidgetBase::DisableChangeCallbacks()
{
  m_IgnoreCallbacks = true;
}

void DocumentEditorWidgetBase::CreateLink(czstr src_asset_path, czstr remote_path, czstr local_path)
{
  m_ChangeLinkCallback(true, src_asset_path, remote_path, local_path);
}

void DocumentEditorWidgetBase::RemoveLink(czstr src_asset_path, czstr remote_path, czstr local_path)
{
  m_ChangeLinkCallback(false, src_asset_path, remote_path, local_path);
}

void DocumentEditorWidgetBase::BeginTransaction()
{
  m_BeginTransactionCallback();
}

void DocumentEditorWidgetBase::CommitChanges()
{
  m_CommitChangesCallback();
}

void DocumentEditorWidgetBase::UpdateLinks(const std::vector<DocumentLink> & links)
{
  m_Links = links;
}

void DocumentEditorWidgetBase::AboutToClose()
{

}

const std::vector<DocumentLink> & DocumentEditorWidgetBase::GetLinks() const
{
  return m_Links;
}

PropertyFieldDatabase & DocumentEditorWidgetBase::GetPropertyFieldDatabase()
{
  return m_PropertyDb;
}

const std::string & DocumentEditorWidgetBase::GetRootPath() const
{
  return m_RootPath;
}

Optional<std::string> DocumentEditorWidgetBase::GetFileNameForAssetType(czstr asset_type)
{
  std::string file_name;

  auto root_path = GetRootPath();
  if (!strcmp(asset_type, "image"))
  {
    auto path = GetRootPath() + "Images";
    file_name = QFileDialog::getOpenFileName(this, tr("Open Image"), path.data(), tr("Image Files (*.png)")).toStdString();
  }
  else if (!strcmp(asset_type, "sprite"))
  {
    auto path = GetRootPath() + "Sprites";
    file_name = QFileDialog::getOpenFileName(this, tr("Open Sprite"), path.data(), tr("Sprite Files (*.sprite)")).toStdString();
  }
  else if (!strcmp(asset_type, "tilesheet"))
  {
    auto path = GetRootPath() + "TileSheets";
    file_name = QFileDialog::getOpenFileName(this, tr("Open Tile Sheet"), path.data(), tr("Tile Sheet Files (*.tilesheet)")).toStdString();
  }
  else if (!strcmp(asset_type, "entity"))
  {
    auto path = GetRootPath() + "Entities";
    file_name = QFileDialog::getOpenFileName(this, tr("Open Entity"), path.data(), tr("Entity Files (*.entity)")).toStdString();
  }
  else if (!strcmp(asset_type, "ui"))
  {
    auto path = GetRootPath() + "UIs";
    file_name = QFileDialog::getOpenFileName(this, tr("Open UI"), path.data(), tr("UI Files (*.ui)")).toStdString();
  }

  if (ConvertToCanonicalPath(file_name, root_path))
  {
    return file_name;
  }

  return{};
}
