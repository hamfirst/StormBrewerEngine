#pragma once

#include "Foundation/Time/StopWatch.h"
#include "Foundation/Sequencer/Sequencer.h"

#include "GameClient/GameMode.h"

#include "Engine/UI/UIManager.h"
#include "Engine/UI/Prototype/UIPrototypeButton.h"
#include "Engine/UI/Prototype/UIPrototypeMuteButton.h"
#include "Engine/UI/Prototype/UIPrototypeFullscreenButton.h"
#include "Engine/UI/Prototype/UIPrototypeConfirmPopup.h"

class GameModeMainMenu : public GameMode
{
public:
  explicit GameModeMainMenu(GameContainer & game);
  ~GameModeMainMenu() override;

  void Initialize() override;
  void OnAssetsLoaded() override;

  void Update() override;
  void Render() override;
  void InputEvent() override;

protected:

  void PlayOnline();
  void PlayOffline();
  void Tutorial();
  void PlaySingleplayer();
  void CreatePrivateMatch();
  void JoinPrivateMatch();

private:

  Sequencer m_Sequencer;
  UIManager m_UIManager;

  UIElementPtr<UIElementFullTexture> m_TitleImage;
  UIElementPtr<UIElementShape> m_Fader;
  Optional<UIPrototypeMuteButton> m_MuteButton;
  Optional<UIPrototypeMuteButton> m_MusicButton;
  Optional<UIPrototypeFullscreenButton> m_FullscreenButton;
  Optional<UIPrototypeConfirmPopup> m_TutorialPrompt;
  Optional<UIPrototypeButton> m_PlayOnline;
  Optional<UIPrototypeButton> m_PlayOffline;
  Optional<UIPrototypeButton> m_PlaySingleplayer;
  Optional<UIPrototypeButton> m_CreateOnlineMatch;
  Optional<UIPrototypeButton> m_JoinOnlineMatch;
  Optional<UIPrototypeButton> m_Tutorial;
  Optional<UIPrototypeButton> m_Host;
  Optional<UIPrototypeButton> m_Join;
  Optional<UIPrototypeButton> m_Settings;
};


