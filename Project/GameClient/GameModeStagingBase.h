
#pragma once

#include "GameClient/GameMode.h"
#include "Game/GameNetworkData.refl.h"

#include "Engine/UI/UIManager.h"

class GameModeStagingBase : public GameMode
{
public:

  void OnAssetsLoaded() override;
  void Update() override;
  void Render() override;

protected:

  void Ready();
  void KickPlayer();

  void Quit();

private:
};

