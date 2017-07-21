#pragma once

#include "Foundation/Time/StopWatch.h"
#include "Foundation/Sequencer/Sequencer.h"

#include "GameClient/GameMode.h"

#include "Engine/UI/UIManager.h"
#include "Engine/UI/Prototype/UIPrototypeButton.h"

class GameModeMainMenu : public GameMode
{
public:
  GameModeMainMenu(GameContainer & game);
  ~GameModeMainMenu();

  virtual void Initialize() override;
  virtual void OnAssetsLoaded() override;

  virtual void Update() override;
  virtual void Render() override;

protected:

  void PlayOnline();

private:

  Sequencer m_Sequencer;
  UIManager m_UIManager;

  UIElementPtr<UIElementFullTexture> m_TitleImage;
  UIElementPtr<UIElementShape> m_Fader;
  Optional<UIPrototypeButton> m_PlayOnline;
  Optional<UIPrototypeButton> m_Host;
  Optional<UIPrototypeButton> m_Join;
  Optional<UIPrototypeButton> m_Settings;
};


