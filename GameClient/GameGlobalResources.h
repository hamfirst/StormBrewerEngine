#pragma once

#include "Shared/AssetBundle/AssetBundle.h"

class GameGlobalResources
{
public:

  GameGlobalResources();

  bool AreAllAssetsLoaded();

private:

  AssetBundle m_AssetBundle;
};

