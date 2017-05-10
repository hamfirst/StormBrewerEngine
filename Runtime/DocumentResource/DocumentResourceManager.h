#pragma once

#include "Foundation/CallList/CallList.h"

#include "Runtime/RuntimeCommon.h"
#include "Runtime/DocumentResource/DocumentResourceBase.h"
#include "Runtime/DocumentResource/DocumentResourceReferenceBase.h"
#include "Runtime/DocumentResource/DocumentResourceLoader.h"


class RUNTIME_EXPORT DocumentResourceManager
{
public:
  DocumentResourceManager();

protected:
  NotNullPtr<DocumentResourceBase> LoadDocumentResource(czstr file_path, std::unique_ptr<DocumentResourceBase> (*ResourceCreator)(Any &&, uint64_t));
  void HandleResourceLoadResult(uint64_t path_hash, NullOptPtr<std::string> resource_data);
  void DestroyDocument(uint64_t path_hash);

private:
  friend class DocumentResourceBase;

  uint64_t m_PendingDocumentLoad;
  std::string m_PendingDocumentData;
  bool m_PendingDocumentLoaded;

  std::unordered_map<uint64_t, std::unique_ptr<DocumentResourceBase>> m_Documents;
};

extern RUNTIME_EXPORT DocumentResourceManager g_DocumentResourceManager;
