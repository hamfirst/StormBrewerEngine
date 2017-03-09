
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
  CallAssetLoadCallbacks(true);
}

void Asset::CallAssetLoadCallbacksWithFailure()
{
  CallAssetLoadCallbacks(false);
}

bool Asset::IsLoaded()
{
  return m_State == AssetState::kLoaded;
}

bool Asset::IsError()
{
  return m_State == AssetState::kLoadError;
}
