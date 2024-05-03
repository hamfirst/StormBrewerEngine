#pragma once

#include <unordered_map>

#include <QWidget>

#include "Shared/Foundation/Common.h"
#include "Shared/Foundation/Delegate/Delegate.h"
#include "Shared/Foundation/CallList/CallList.h"
#include "Shared/Foundation/PropertyMeta/PropertyFieldDatabase.h"
#include "Shared/Foundation/Document/DocumentTypes.refl.h"

using DocumentExternalChangeCallback = Delegate<void, const ReflectionChangeNotification &>;
using DocumentChangeLinkDelegate = Delegate<void, bool, czstr, czstr, czstr>;
using DocumentBeginTransactionDelegate = Delegate<void>;
using DocumentCommitChangesDelegate = Delegate<void>;

class EditorContainer;
struct MapDef;

class DocumentEditorWidgetBase : public QWidget
{
  Q_OBJECT;
public:
  DocumentEditorWidgetBase(EditorContainer & editor_container, PropertyFieldDatabase & property_db, const std::string & root_path, DocumentChangeLinkDelegate && change_link_callback,
    DocumentBeginTransactionDelegate && begin_transaction_callback, DocumentCommitChangesDelegate && commit_change_callback, QWidget *parent = nullptr);
  ~DocumentEditorWidgetBase();

  uint64_t AddChangeCallback(uint64_t path_hash, DocumentExternalChangeCallback && callback);
  void RemoveChangeCallback(uint64_t path_hash, uint64_t callback_id);

  uint64_t AddParentChangeCallback(czstr path, DocumentExternalChangeCallback && callback);
  void RemoveParentChangeCallback(uint64_t callback_id);

  uint64_t AddChildChangeCallback(czstr path, DocumentExternalChangeCallback && callback);
  void RemoveChildChangeCallback(uint64_t callback_id);

  void TriggerChangeCallbacks(const ReflectionChangeNotification & change);
  void EnableChangeCallbacks();
  void DisableChangeCallbacks();

  void CreateLink(czstr src_asset_path, czstr remote_path, czstr local_path);
  void RemoveLink(czstr src_asset_path, czstr remote_path, czstr local_path);

  void Undo();
  void Redo();

  void BeginTransaction();
  void CommitChanges();

  virtual void UpdateLinks(const std::vector<DocumentLink> & links);
  virtual void AboutToClose();
  const std::vector<DocumentLink> & GetLinks() const;

  PropertyFieldDatabase & GetPropertyFieldDatabase();
  const std::string & GetRootPath() const;

  Optional<std::string> GetFileNameForAssetType(czstr asset_type);

  virtual NullOptPtr<MapDef> GetMap();

private:
  EditorContainer & m_EditorContainer;
  PropertyFieldDatabase & m_PropertyDb;
  const std::string & m_RootPath;

  std::vector<DocumentLink> m_Links;

  bool m_IgnoreCallbacks;
  bool m_TriggeringCallbacks;
  std::vector<std::pair<uint64_t, uint64_t>> m_DeadCallbacks;

  std::unordered_map<uint64_t, std::vector<uint64_t>> m_PathLookup;
  std::unordered_map<uint64_t, DocumentExternalChangeCallback> m_ChangeCallbacks;

  struct ParentPathChangeCallbackData
  {
    std::string m_Path;
    DocumentExternalChangeCallback m_Callback;
    bool m_Defunct;
  };

  std::vector<int> m_ParentChangeCallbackOperations;
  std::unordered_map<uint64_t, ParentPathChangeCallbackData> m_ParentChangeCallbacks;
  std::vector<std::pair<uint64_t, ParentPathChangeCallbackData>> m_NewParentChangeCallbacks;
  std::vector<std::size_t> m_DeadParentChangeCallbacks;

  struct ChildPathChangeCallbackData
  {
    uint64_t m_PathHash;
    int m_PathLength;
    DocumentExternalChangeCallback m_Callback;
    bool m_Defunct;
  };

  std::vector<int> m_ChildChangeCallbackOperations;
  std::unordered_map<uint64_t, ChildPathChangeCallbackData> m_ChildChangeCallbacks;
  std::vector<std::pair<uint64_t, ChildPathChangeCallbackData>> m_NewChildChangeCallbacks;
  std::vector<std::size_t> m_DeadChildChangeCallbacks;

  DocumentChangeLinkDelegate m_ChangeLinkCallback;
  DocumentBeginTransactionDelegate m_BeginTransactionCallback;
  DocumentCommitChangesDelegate m_CommitChangesCallback;
};

extern PreMainCallList g_DocumentRegistrationCallList;
extern EditorContainer * g_DocumentRegistrationEditor;

#define REGISTER_EDITOR(AssetType, WidgetType, DataType, Extension, DefaultDirectory)  \
  ADD_PREMAIN_CALL(g_DocumentRegistrationCallList, WidgetType, \
    []() { g_DocumentRegistrationEditor->RegisterEditor(AssetType, Extension, DefaultDirectory, \
      DocumentEditorCreationDelegate([](EditorContainer & editor_container, PropertyFieldDatabase & property_db, const std::string & root_path, DocumentOutputDelegate && output_delegate, QWidget * parent) -> DocumentEditorBase * \
        { return new DocumentEditor<DataType, WidgetType>(editor_container, property_db, root_path, std::move(output_delegate), parent); })); }) \

