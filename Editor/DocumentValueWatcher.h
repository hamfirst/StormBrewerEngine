#pragma once

#include "Foundation/Common.h"
#include "Foundation/Delegate/Delegate.h"

class DocumentEditorWidgetBase;

class DocumentValueWatcher
{
public:
  DocumentValueWatcher(NotNullPtr<DocumentEditorWidgetBase> editor);
  ~DocumentValueWatcher();

  void SetChangeCallback(Delegate<void, const ReflectionChangeNotification &> && change_cb);
  void SetParentChangeCallback(Delegate<void> && update_cb);
  void SetChildChangeCallback(Delegate<void> && update_cb);
  void SetAllUpdateCallbacks(Delegate<void> && update_cb);
  void SetDeletedCallback(Delegate<void> && deleted_cb);
  void SetPath(czstr path, bool check_parent, bool check_child, Delegate<bool> && exist_check_callback);
  void ClearPath();

  void HandleDirectChange(const ReflectionChangeNotification & change);
  void HandleParentChange(const ReflectionChangeNotification & change);
  void HandleChildChange(const ReflectionChangeNotification & change);

private:
  NotNullPtr<DocumentEditorWidgetBase> m_Editor;
  uint64_t m_ChangeCallbackId;
  uint64_t m_ParentCallbackId;
  uint64_t m_ChildCallbackId;

  std::string m_Path;
  uint64_t m_PathHash;

  Delegate<void> m_ParentChangeCallback;
  Delegate<void> m_ChildChangeCallback;
  Delegate<void> m_UpdateCallback;
  Delegate<void, const ReflectionChangeNotification &> m_ChangeCallback;
  Delegate<bool> m_ExistCheckCallback;
  Delegate<void> m_DeletedCallback;
};

