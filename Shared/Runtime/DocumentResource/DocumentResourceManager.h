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
  ~DocumentResourceManager();

protected:
  NullOptPtr<DocumentResourceBase> FindDocumentResource(uint32_t file_path_hash);
  NotNullPtr<DocumentResourceBase> LoadDocumentResource(czstr file_path,
          std::unique_ptr<DocumentResourceBase> (*ResourceCreator)(Any &&, uint32_t, czstr));
  void HandleResourceLoadResult(uint32_t path_hash, NullOptPtr<std::string> resource_data);
  void DestroyDocument(uint32_t path_hash);

private:
  friend class DocumentResourceBase;

  uint32_t m_PendingDocumentLoad;
  std::string m_PendingDocumentData;
  bool m_PendingDocumentLoaded;

  std::unordered_map<uint32_t, std::unique_ptr<DocumentResourceBase>> m_Documents;
};

extern RUNTIME_EXPORT DocumentResourceManager g_DocumentResourceManager;
