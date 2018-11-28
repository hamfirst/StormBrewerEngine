
#include "Runtime/RuntimeCommon.h"
#include "Runtime/BinaryResource/BinaryResourceBase.h"
#include "Runtime/BinaryResource/BinaryResourceManager.h"

BinaryResourceBase::BinaryResourceBase(Any && load_data, uint32_t path_hash, czstr path) :
  m_LoadData(std::move(load_data)),
  m_RefCount(0),
  m_Loaded(false),
  m_Error(false),
  m_FileName(path),
  m_FileNameHash(path_hash)
{

}

BinaryResourceBase::~BinaryResourceBase()
{
  m_LoadData.Clear();
}

void BinaryResourceBase::IncRef()
{
  ++m_RefCount;
}

void BinaryResourceBase::DecRef()
{
  int val = --m_RefCount;
  if (val == 0)
  {
    m_ResourceManager->DestroyBinary(m_FileNameHash);
  }
}

bool BinaryResourceBase::IsLoaded() const
{
  return m_Loaded;
}

bool BinaryResourceBase::IsError() const
{
  return m_Error;
}

czstr BinaryResourceBase::GetFileName() const
{
  return m_FileName.c_str();
}

uint64_t BinaryResourceBase::GetFileNameHash() const
{
  return m_FileNameHash;
}

NullOptPtr<BinaryResourceBase> BinaryResourceBase::FindBinaryResource(uint32_t file_path_hash)
{
  return g_BinaryResourceManager.FindBinaryResource(file_path_hash);
}

NotNullPtr<BinaryResourceBase> BinaryResourceBase::LoadBinaryResource(czstr file_path,
        std::unique_ptr<BinaryResourceBase>(*ResourceCreator)(Any &&, uint32_t, czstr))
{
  return g_BinaryResourceManager.LoadBinaryResource(file_path, ResourceCreator);
}

void BinaryResourceBase::OnDataLoadComplete(const void * data, std::size_t length)
{

}

void BinaryResourceBase::CallAssetLoadCallbacks()
{

}
