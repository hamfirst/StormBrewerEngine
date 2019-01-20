
#pragma once

#include "GameClient/GameMode.h"
#include "Game/GameNetworkData.refl.h"

#include "Engine/UI/UIManager.h"

enum class GameModeMapSettingsNextScreen
{
    kOfflineStaging,
    kPrivateGame,
};

class GameModeMapSettings : public GameMode
{
public:
    GameModeMapSettings(GameContainer & game, GameModeMapSettingsNextScreen next_screen);

    void OnAssetsLoaded() override;

    void Update() override;
    void Render() override;

protected:

    void Ready();
    void KickPlayer();

    void Quit();

private:

    GameModeMapSettingsNextScreen m_NextScreen;
};

