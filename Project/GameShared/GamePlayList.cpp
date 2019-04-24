#include "GameShared/GameSharedCommon.h"
#include "GameShared/GamePlayList.h"
#include "GameShared/GamePlayListAsset.refl.meta.h"

#include "Runtime/GenericResource/GenericResource.h"

#include "StormData/StormDataJson.h"

using PlayList = GenericResource<PlaylistAsset>;
using PlayListPtr = GenericResourcePtr<PlaylistAsset>;

GamePlayList::GamePlayList(czstr playlist_asset)
{
  m_PlayListResource = PlayList::Load(playlist_asset);
}

bool GamePlayList::IsPlayListLoaded() const
{
  return m_PlayListResource.IsLoaded();
}

const PlayListPtr & GamePlayList::GetPlayListAsset() const
{
  return m_PlayListResource;
}
