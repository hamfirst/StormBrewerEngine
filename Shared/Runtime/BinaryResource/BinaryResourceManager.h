#pragma once

#include "Foundation/CallList/CallList.h"

#include "Runtime/RuntimeCommon.h"
#include "Runtime/BinaryResource/BinaryResourceBase.h"
#include "Runtime/BinaryResource/BinaryResourceReferenceBase.h"
#include "Runtime/BinaryResource/BinaryResourceLoader.h"


class RUNTIME_EXPORT BinaryResourceManager
{
public:
  BinaryResourceManager();
  ~BinaryResourceManager();

protected:
  NullOptPtr<BinaryResourceBase> FindBinaryResource(uint32_t file_path_hash);
  NotNullPtr<BinaryResourceBase> LoadBinaryResource(czstr file_path,
          std::unique_ptr<BinaryResourceBase> (*ResourceCreator)(Any &&, uint32_t, czstr));
  void HandleResourceLoadResult(uint32_t path_hash, const void * data, std::size_t length);
  void DestroyBinary(uint32_t path_hash);

private:
  friend class BinaryResourceBase;

  uint32_t m_PendingBinaryLoad;
  const void * m_PendingBinaryData;
  std::size_t m_PendingBinaryLength;
  bool m_PendingBinaryLoaded;

  std::unordered_map<uint32_t, std::unique_ptr<BinaryResourceBase>> m_BinaryResources;
};

extern RUNTIME_EXPORT BinaryResourceManager g_BinaryResourceManager;
