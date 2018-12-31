
#include "DocumentValueWatcher.h"
#include "DocumentEditorWidgetBase.h"

DocumentValueWatcher::DocumentValueWatcher(NotNullPtr<DocumentEditorWidgetBase> editor) :
  m_Editor(editor),
  m_ChangeCallbackId(0),
  m_ParentCallbackId(0),
  m_ChildCallbackId(0)
{

}

DocumentValueWatcher::~DocumentValueWatcher()
{
  ClearPath();
}

void DocumentValueWatcher::SetChangeCallback(Delegate<void, const ReflectionChangeNotification &> && change_cb)
{
  m_ChangeCallback = std::move(change_cb);
}

void DocumentValueWatcher::SetParentChangeCallback(Delegate<void> && update_cb)
{
  m_ParentChangeCallback = std::move(update_cb);
}

void DocumentValueWatcher::SetChildChangeCallback(Delegate<void> && update_cb)
{
  m_ChildChangeCallback = std::move(update_cb);
}

void DocumentValueWatcher::SetAllUpdateCallbacks(Delegate<void> && update_cb)
{
  m_UpdateCallback = std::move(update_cb);
  m_ChangeCallback = [this](const ReflectionChangeNotification &) { m_UpdateCallback(); };
  m_ParentChangeCallback = [this]() { m_UpdateCallback(); };
  m_ChildChangeCallback = [this]() { m_UpdateCallback(); };
}

void DocumentValueWatcher::SetDeletedCallback(Delegate<void> && deleted_cb)
{
  m_DeletedCallback = std::move(deleted_cb);
}


void DocumentValueWatcher::SetPath(czstr path, bool check_parent, bool check_child, Delegate<bool> && exist_check_callback)
{
  ClearPath();

  m_Path = path;
  m_PathHash = crc64(path);

  m_ChangeCallbackId = m_Editor->AddChangeCallback(m_PathHash, DocumentExternalChangeCallback(&DocumentValueWatcher::HandleDirectChange, this));

  if (check_parent)
  {
    m_ParentCallbackId = m_Editor->AddParentChangeCallback(path, DocumentExternalChangeCallback(&DocumentValueWatcher::HandleParentChange, this));
  }

  if (check_child)
  {
    m_ChildCallbackId = m_Editor->AddChildChangeCallback(path, DocumentExternalChangeCallback(&DocumentValueWatcher::HandleChildChange, this));
  }

  m_ExistCheckCallback = std::move(exist_check_callback);
}

void DocumentValueWatcher::ClearPath()
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

void DocumentValueWatcher::HandleDirectChange(const ReflectionChangeNotification & change)
{
  m_ChangeCallback(change);
}

void DocumentValueWatcher::HandleParentChange(const ReflectionChangeNotification & change)
{
  m_ParentChangeCallback();
}

void DocumentValueWatcher::HandleChildChange(const ReflectionChangeNotification & change)
{
  m_ChildChangeCallback();
}

