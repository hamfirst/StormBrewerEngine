#pragma once

#include "Foundation/Time/StopWatch.h"
#include "Foundation/Sequencer/Sequencer.h"

#include "GameClient/GameMode.h"
#include "Game/GameNetworkData.refl.h"

#include "Engine/UI/UIManager.h"
#include "Engine/UI/Prototype/UIPrototypeButton.h"
#include "Engine/UI/Prototype/UIPrototypeMuteButton.h"
#include "Engine/UI/Prototype/UIPrototypeFullscreenButton.h"

class GameModeOfflineStaging : public GameMode
{
public:
  GameModeOfflineStaging(GameContainer & game);
  ~GameModeOfflineStaging();

  virtual void Initialize() override;
  virtual void OnAssetsLoaded() override;

  virtual void Update() override;
  virtual void Render() override;

protected:

  void Start();
  void Back();

private:

  Sequencer m_Sequencer;
  UIManager m_UIManager;

  UIElementHandle m_StagingUI;

  UIElementPtr<UIElementFullTexture> m_TitleImage;
  Optional<UIPrototypeMuteButton> m_MuteButton;
  Optional<UIPrototypeMuteButton> m_MusicButton;
  Optional<UIPrototypeFullscreenButton> m_FullscreenButton;

  UIElementPtr<UIElementShape> m_Fader;
  Optional<UIPrototypeButton> m_Start;
  Optional<UIPrototypeButton> m_Back;


  bool m_Attached[kMaxPlayers];
};


