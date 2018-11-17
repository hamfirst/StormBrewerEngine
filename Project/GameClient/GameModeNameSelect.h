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

enum class GameModeNameSelectNextScreen
{
  kJoinOnline,
  kCreatePrivate,
  kJoinPrivate,
};

class GameModeNameSelect : public GameMode
{
public:
  GameModeNameSelect(GameContainer & game, GameModeNameSelectNextScreen next_screen);
  ~GameModeNameSelect() override;

  void Initialize() override;
  void OnAssetsLoaded() override;

  void Update() override;
  void Render() override;

protected:

  void Submit();
  void Back();

  void GoToNextMode();

private:

  GameModeNameSelectNextScreen m_NextMode;

  Sequencer m_Sequencer;
  UIManager m_UIManager;

  UIElementPtr<UIElementText> m_Caption;
  UIElementPtr<UIElementText> m_Instructions;
  UIElementPtr<UIElementShape> m_Fader;

  Optional<UIPrototypeMuteButton> m_MuteButton;
  Optional<UIPrototypeMuteButton> m_MusicButton;
  Optional<UIPrototypeFullscreenButton> m_FullscreenButton;

  Optional<UIPrototypeTextInput> m_Input;
  Optional<UIPrototypeButton> m_Okay;
  Optional<UIPrototypeButton> m_Back;
};


