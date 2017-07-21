#pragma once

#include <atomic>

#include "Foundation/Delegate/DelegateList.h"
#include "Foundation/Delegate/DelegateLink.h"
#include "Foundation/Any/Any.h"

#include "Runtime/RuntimeCommon.h"
#include "Runtime/DocumentResource/DocumentResourceReferenceBase.h"

class DocumentResourceManager;

class RUNTIME_EXPORT DocumentResourceBase
{
public:
  bool IsLoaded() const;
  uint64_t GetFileNameHash() const;

  virtual ~DocumentResourceBase();

protected:
  friend class DocumentResourceReferenceBase;

  DocumentResourceBase(Any && load_data, uint64_t file_name_hash);

  void IncRef();
  void DecRef();

protected:

  static NotNullPtr<DocumentResourceBase> LoadDocumentResource(czstr file_path, std::unique_ptr<DocumentResourceBase>(*ResourceCreator)(Any &&, uint64_t));

  virtual void OnDataLoadComplete(const std::string & resource_data);
  virtual void CallAssetLoadCallbacks();

protected:

  friend class DocumentResourceManager;

  Any m_LoadData;

  std::atomic_int m_RefCount;
  bool m_Loaded;

  NotNullPtr<DocumentResourceManager> m_ResourceManager;
  uint64_t m_FileNameHash;
};
