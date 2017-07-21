#pragma once

#include "Foundation/Time/StopWatch.h"
#include "Foundation/Sequencer/Sequencer.h"

#include "Engine/UI/UIManager.h"
#include "Engine/UI/Prototype/UIPrototypeButton.h"

#include "GameClient/GameMode.h"
#include "GameClient/GameClientInstanceContainer.h"

class GameModeEndGame : public GameMode
{
public:
  GameModeEndGame(GameContainer & game, std::unique_ptr<GameClientInstanceContainer> && instance_container);
  ~GameModeEndGame();

  virtual void Initialize() override;
  virtual void OnAssetsLoaded() override;

  virtual void Update() override;
  virtual void Render() override;

protected:

  void PlayOnline();

private:

  bool m_Victory;
  std::unique_ptr<GameClientInstanceContainer> m_InstanceContainer;
  GameClientEventSender m_DefaultSender;

  Sequencer m_Sequencer;
  UIManager m_UIManager;

  UIElementPtr<UIElementShape> m_Fader;
  UIElementPtr<UIElementText> m_Result;
  Optional<UIPrototypeButton> m_PlayAgain;
};

