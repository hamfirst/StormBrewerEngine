

#include "Engine/EngineCommon.h"
#include "Engine/Asset/MusicAsset.h"
#include "Engine/Asset/AssetManager.h"

#ifdef _WEB

#include "Foundation/Allocator/IdAllocator.h"
#include "Foundation/SparseList/SparseList.h"

#include <emscripten/html5.h>
#include <emscripten/emscripten.h>

IdAllocator s_MusicIdAllocator;
SparseList<MusicAsset *> s_MusicAssetLookup;

extern "C"
{
  void HandleMusicLoaded(std::size_t music_id)
  {
    auto asset = s_MusicAssetLookup.GetAt(music_id);
    asset->HandleLoadComplete(true);
  }

  void HandleMusicLoadFailed(std::size_t music_id)
  {
    auto asset = s_MusicAssetLookup.GetAt(music_id);
    asset->HandleLoadComplete(false);
  }
}

#endif

int MusicAsset::PreProcessLoadedData(Buffer & buffer, bool load_deps)
{
  return 0;
}

void MusicAsset::OnDataLoadComplete(Buffer & buffer, bool load_deps)
{
  m_AudioBuffer = std::move(buffer);

#ifdef _WEB

  IncRef();

  m_MusicId = s_MusicIdAllocator.Allocate();
  s_MusicAssetLookup.EmplaceAt(m_MusicId, this);

  EM_ASM_ARGS({ LoadMusic($0, $1, $2); }, m_AudioBuffer.Get(), m_AudioBuffer.GetSize(), m_MusicId);

#else
  FinalizeAssetLoad();
#endif
}

void MusicAsset::CleanupAsset()
{
#ifdef _WEB

  s_MusicIdAllocator.Release(m_MusicId);
  s_MusicAssetLookup.RemoveAt(m_MusicId);

  EM_ASM_ARGS({ UnloadMusic($0); }, m_MusicId);

#endif
}
#ifdef _WEB
void MusicAsset::HandleLoadComplete(bool success)
{
  if (success)
  {
    FinalizeAssetLoad();
  }
  else
  {
    CallAssetLoadCallbacksWithFailure();
  }

  DecRef();
}
#endif

ASSET_SOURCE_FUNCS(MusicAsset)
