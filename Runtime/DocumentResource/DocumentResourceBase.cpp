
#include "Runtime/RuntimeCommon.h"
#include "Runtime/DocumentResource/DocumentResourceBase.h"
#include "Runtime/DocumentResource/DocumentResourceManager.h"

DocumentResourceBase::DocumentResourceBase(Any && load_data, uint32_t path_hash, czstr path) :
  m_LoadData(std::move(load_data)),
  m_RefCount(0),
  m_Loaded(false),
  m_Error(false),
  m_FileName(path),
  m_FileNameHash(path_hash)
{

}

DocumentResourceBase::~DocumentResourceBase()
{

}

void DocumentResourceBase::IncRef()
{
  ++m_RefCount;
}

void DocumentResourceBase::DecRef()
{
  int val = --m_RefCount;
  if (val == 0)
  {
    m_ResourceManager->DestroyDocument(m_FileNameHash);
  }
}

bool DocumentResourceBase::IsLoaded() const
{
  return m_Loaded;
}

bool DocumentResourceBase::IsError() const
{
  return m_Error;
}

czstr DocumentResourceBase::GetFileName() const
{
  return m_FileName.c_str();
}

uint64_t DocumentResourceBase::GetFileNameHash() const
{
  return m_FileNameHash;
}

NullOptPtr<DocumentResourceBase> DocumentResourceBase::FindDocumentResource(uint32_t file_path_hash)
{
  return g_DocumentResourceManager.FindDocumentResource(file_path_hash);
}

NotNullPtr<DocumentResourceBase> DocumentResourceBase::LoadDocumentResource(czstr file_path,
        std::unique_ptr<DocumentResourceBase>(*ResourceCreator)(Any &&, uint32_t, czstr))
{
  return g_DocumentResourceManager.LoadDocumentResource(file_path, ResourceCreator);
}

void DocumentResourceBase::OnDataLoadComplete(const std::string & resource_data)
{

}

void DocumentResourceBase::CallAssetLoadCallbacks()
{

}
