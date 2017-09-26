#pragma once

#include "Foundation/Time/StopWatch.h"
#include "Foundation/Time/FrameClock.h"

#include "GameClient/GameMode.h"

#include "Engine/UI/UIManager.h"
#include "Engine/UI/Prototype/UIPrototypeButton.h"
#include "Engine/UI/Prototype/UIPrototypeTextInput.h"
#include "Engine/UI/Prototype/UIPrototypeConfirmPopup.h"
#include "Engine/UI/Prototype/UIPrototypeMuteButton.h"
#include "Engine/UI/Prototype/UIPrototypeFullscreenButton.h"

class GameModeConnecting : public GameMode
{
public:
  GameModeConnecting(GameContainer & game);
  ~GameModeConnecting();

  virtual void Initialize() override;
  virtual void OnAssetsLoaded() override;

  virtual void Update() override;
  virtual void Render() override;

protected:

  void Back();

protected:

  UIManager m_UIManager;
  Optional<UIPrototypeButton> m_Back;

  Optional<UIPrototypeMuteButton> m_MuteButton;
  Optional<UIPrototypeMuteButton> m_MusicButton;
  Optional<UIPrototypeFullscreenButton> m_FullscreenButton;

  bool m_ConnectFailed;

  double m_LastConnect;
  FrameClock m_FrameClock;
};


