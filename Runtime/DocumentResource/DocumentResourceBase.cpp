
#include "Runtime/RuntimeCommon.h"
#include "Runtime/DocumentResource/DocumentResourceBase.h"
#include "Runtime/DocumentResource/DocumentResourceManager.h"

DocumentResourceBase::DocumentResourceBase(Any && load_data, uint64_t file_name_hash) :
  m_LoadData(std::move(load_data)),
  m_RefCount(0),
  m_Loaded(false),
  m_Error(false),
  m_FileNameHash(file_name_hash)
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

uint64_t DocumentResourceBase::GetFileNameHash() const
{
  return m_FileNameHash;
}

NotNullPtr<DocumentResourceBase> DocumentResourceBase::LoadDocumentResource(czstr file_path, std::unique_ptr<DocumentResourceBase>(*ResourceCreator)(Any &&, uint64_t))
{
  return g_DocumentResourceManager.LoadDocumentResource(file_path, ResourceCreator);
}

void DocumentResourceBase::OnDataLoadComplete(const std::string & resource_data)
{

}

void DocumentResourceBase::CallAssetLoadCallbacks()
{

}
