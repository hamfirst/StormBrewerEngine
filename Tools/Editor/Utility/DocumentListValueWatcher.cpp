
#include "DocumentListValueWatcher.h"
#include "Tools/Editor/AssetEditors/DocumentEditor/DocumentEditorWidgetBase.h"

DocumentListValueWatcher::DocumentListValueWatcher(NotNullPtr<DocumentEditorWidgetBase> editor) :
  m_Editor(editor),
  m_ParentCallbackId(0),
  m_ChildCallbackId(0)
{

}

DocumentListValueWatcher::~DocumentListValueWatcher()
{
  ClearPath();
}

void DocumentListValueWatcher::SetChangeCallback(Delegate<void, const ReflectionChangeNotification &> && change_cb)
{
  m_ChangeCallback = std::move(change_cb);
}

void DocumentListValueWatcher::SetParentChangeCallback(Delegate<void, const ReflectionChangeNotification &> && change_cb)
{
  m_ParentChangeCallback = std::move(change_cb);
}

void DocumentListValueWatcher::SetChildChangeCallback(Delegate<void, const ReflectionChangeNotification &, std::size_t> && change_cb)
{
  m_ChildChangeCallback = std::move(change_cb);
}

void DocumentListValueWatcher::SetDeletedCallback(Delegate<void> && deleted_cb)
{
  m_DeletedCallback = std::move(deleted_cb);
}

void DocumentListValueWatcher::SetPath(czstr path, bool check_parent, bool check_child, Delegate<bool> && exist_check_callback)
{
  ClearPath();

  m_Path = path;
  m_PathHash = crc64(path);

  m_ChangeCallbackId = m_Editor->AddChangeCallback(m_PathHash, DocumentExternalChangeCallback(&DocumentListValueWatcher::HandleDirectChange, this));

  if (check_parent)
  {
    m_ParentCallbackId = m_Editor->AddParentChangeCallback(path, DocumentExternalChangeCallback(&DocumentListValueWatcher::HandleParentChange, this));
  }

  if (check_child)
  {
    m_ChildCallbackId = m_Editor->AddChildChangeCallback(path, DocumentExternalChangeCallback(&DocumentListValueWatcher::HandleChildChange, this));
  }

  m_ExistCheckCallback = std::move(exist_check_callback);
}

void DocumentListValueWatcher::ClearPath()
{
  if (m_ChangeCallbackId != 0)
  {
    m_Editor->RemoveChangeCallback(m_PathHash, m_ChangeCallbackId);
    m_ChangeCallbackId = 0;
  }

  if (m_ParentCallbackId != 0)
  {
    m_Editor->RemoveParentChangeCallback(m_ParentCallbackId);
    m_ParentCallbackId = 0;
  }

  if (m_ChildCallbackId != 0)
  {
    m_Editor->RemoveChildChangeCallback(m_ChildCallbackId);
    m_ChildCallbackId = 0;
  }

  m_Path.clear();
}

void DocumentListValueWatcher::HandleDirectChange(const ReflectionChangeNotification & change)
{
  m_ChangeCallback(change);
}

void DocumentListValueWatcher::HandleChildChange(const ReflectionChangeNotification & change)
{
  auto path_ptr = change.m_Path.data();
  path_ptr += m_Path.size();

  if (*path_ptr != '[')
  {
    return;
  }

  path_ptr++;
  if (*path_ptr < '0' || *path_ptr > '9')
  {
    return;
  }

  std::size_t child_index = *path_ptr - '0';
  path_ptr++;

  while (*path_ptr != ']')
  {
    if (*path_ptr < '0' || *path_ptr > '9')
    {
      return;
    }

    child_index *= 10;
    child_index += *path_ptr - '0';
    path_ptr++;
  }

  path_ptr++;

  m_ChildChangeCallback(change, child_index);
}

void DocumentListValueWatcher::HandleParentChange(const ReflectionChangeNotification & change)
{
  m_ParentChangeCallback(change);
}
