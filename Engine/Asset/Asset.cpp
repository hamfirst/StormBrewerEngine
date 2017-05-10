
#include "Engine/EngineCommon.h"
#include "Engine/Asset/Asset.h"

Asset::Asset()
{

}

void Asset::IncRef()
{
  ++m_RefCount;
}

void Asset::DecRef()
{
  int val = --m_RefCount;
  if (val == 0)
  {
    m_Deleter(m_AssetManager, m_Handle);
  }
}

void Asset::FinalizeAssetLoad()
{
  m_State = AssetState::kLoaded;
  CallAssetLoadCallbacks();
}

void Asset::CallAssetLoadCallbacksWithFailure()
{
  m_State = AssetState::kLoadError;
  CallAssetLoadCallbacks();
}

bool Asset::IsLoaded()
{
  return m_State == AssetState::kLoaded;
}

bool Asset::IsError()
{
  return m_State == AssetState::kLoadError;
}

const std::string & Asset::GetFileName() const
{
  return m_FileName;
}

GenericLoadCallbackLink Asset::AddLoadCallback(GenericLoadCallback del)
{
  if (m_State == AssetState::kLoadError)
  {
    del.Call(this);
  }
  else if (m_State == AssetState::kLoaded)
  {
    del.Call(this);
  }

  return GenericLoadCallbackLink{
    m_GenericLoadCallbackList.AddDelegate(del), AssetReferenceBase(this) };
}

int Asset::PreProcessLoadedData(Buffer & file_data)
{
  return 0;
}

void Asset::OnDataLoadComplete(Buffer & file_data)
{

}

void Asset::CallAssetLoadCallbacks()
{ 
  m_GenericLoadCallbackList.Call(this); 
}
