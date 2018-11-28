#pragma once

#include <atomic>

#include "Foundation/Delegate/DelegateList.h"
#include "Foundation/Delegate/DelegateLink.h"
#include "Foundation/Any/Any.h"

#include "Runtime/RuntimeCommon.h"
#include "Runtime/BinaryResource/BinaryResourceReferenceBase.h"

class BinaryResourceManager;

class RUNTIME_EXPORT BinaryResourceBase
{
public:
  bool IsLoaded() const;
  bool IsError() const;
  czstr GetFileName() const;
  uint64_t GetFileNameHash() const;

  virtual ~BinaryResourceBase();

protected:
  friend class BinaryResourceReferenceBase;

  BinaryResourceBase(Any && load_data, uint32_t path_hash, czstr path);

  void IncRef();
  void DecRef();

protected:

  static NullOptPtr<BinaryResourceBase> FindBinaryResource(uint32_t file_path_hash);
  static NotNullPtr<BinaryResourceBase> LoadBinaryResource(czstr file_path,
          std::unique_ptr<BinaryResourceBase>(*ResourceCreator)(Any &&, uint32_t, czstr));

  virtual void OnDataLoadComplete(const void * data, std::size_t length);
  virtual void CallAssetLoadCallbacks();

protected:

  friend class BinaryResourceManager;

  Any m_LoadData;

  std::atomic_int m_RefCount;
  bool m_Loaded;
  bool m_Error;

  NotNullPtr<BinaryResourceManager> m_ResourceManager;
  std::string m_FileName;
  uint32_t m_FileNameHash;
};
