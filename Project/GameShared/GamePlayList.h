#pragma once

#include "Foundation/Common.h"

#include "GameShared/GamePlayListAsset.refl.h"

#include "Runtime/GenericResource/GenericResource.h"

using PlayListPtr = GenericResourcePtr<PlaylistAsset>;

class GamePlayList
{
public:

  GamePlayList(czstr playlist_asset);
  bool IsPlayListLoaded() const;

  const PlayListPtr & GetPlayListAsset() const;

private:

  PlayListPtr m_PlayListResource;
};

