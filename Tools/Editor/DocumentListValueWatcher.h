#pragma once

#include "Foundation/Common.h"
#include "Foundation/Delegate/Delegate.h"

class DocumentEditorWidgetBase;

class DocumentListValueWatcher
{
public:
  DocumentListValueWatcher(NotNullPtr<DocumentEditorWidgetBase> editor);
  ~DocumentListValueWatcher();

  void SetChangeCallback(Delegate<void, const ReflectionChangeNotification &> && change_cb);
  void SetParentChangeCallback(Delegate<void, const ReflectionChangeNotification &> && change_cb);
  void SetChildChangeCallback(Delegate<void, const ReflectionChangeNotification &, std::size_t> && change_cb);
  void SetDeletedCallback(Delegate<void> && deleted_cb);
  void SetPath(czstr path, bool check_parent, bool check_child, Delegate<bool> && exist_check_callback);
  void ClearPath();

protected:

  void HandleDirectChange(const ReflectionChangeNotification & change);
  void HandleChildChange(const ReflectionChangeNotification & change);
  void HandleParentChange(const ReflectionChangeNotification & change);

private:
  NotNullPtr<DocumentEditorWidgetBase> m_Editor;
  uint64_t m_ChangeCallbackId;
  uint64_t m_ParentCallbackId;
  uint64_t m_ChildCallbackId;

  std::string m_Path;
  uint64_t m_PathHash;

  Delegate<void, const ReflectionChangeNotification &> m_ChangeCallback;
  Delegate<void, const ReflectionChangeNotification &> m_ParentChangeCallback;
  Delegate<void, const ReflectionChangeNotification &, std::size_t> m_ChildChangeCallback;
  Delegate<bool> m_ExistCheckCallback;
  Delegate<void> m_DeletedCallback;
};

