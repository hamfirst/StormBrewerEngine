#pragma once

#include "Foundation/Time/StopWatch.h"
#include "Foundation/Sequencer/Sequencer.h"

#include "GameClient/GameMode.h"

#include "Engine/UI/UIManager.h"
#include "Engine/UI/Prototype/UIPrototypeButton.h"
#include "Engine/UI/Prototype/UIPrototypeTextInput.h"
#include "Engine/UI/Prototype/UIPrototypeConfirmPopup.h"
#include "Engine/UI/Prototype/UIPrototypeMuteButton.h"
#include "Engine/UI/Prototype/UIPrototypeFullscreenButton.h"

class GameModeOnlineStaging : public GameMode
{
public:
  GameModeOnlineStaging(GameContainer & game);

  ~GameModeOnlineStaging() override;

  void Initialize() override;

  void OnAssetsLoaded() override;

  void Update() override;

  void Render() override;

protected:

  void Ready();
  void KickPlayer();

  void Quit();

private:

  Sequencer m_Sequencer;
  UIManager m_UIManager;

  UIElementPtr<UIElementShape> m_Fader;

  Optional<UIPrototypeMuteButton> m_MuteButton;
  Optional<UIPrototypeMuteButton> m_MusicButton;
  Optional<UIPrototypeFullscreenButton> m_FullscreenButton;

  Optional<UIPrototypeButton> m_Ready;
  Optional<UIPrototypeButton> m_Back;

  std::vector<UIPrototypeButton> m_KickButtons;
};