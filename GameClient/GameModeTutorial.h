#pragma once

#include "GameClient/GameMode.h"
#include "GameClient/GameClientSystems.h"
#include "GameClient/GameClientInstanceContainer.h"

#include "Engine/UI/Prototype/UIPrototypeTutorialPopup.h"

#include "Engine/Camera/Camera.h"

#include "Foundation/Time/FrameClock.h"
#include "Foundation/Sequencer/Sequencer.h"

class GameModeTutorial : public GameMode, public GameClientEventSender
{
public:
  GameModeTutorial(GameContainer & game, const GameInitSettings game_settings);
  ~GameModeTutorial();

  virtual void Initialize() override;
  virtual void OnAssetsLoaded() override;

  virtual void Update() override;
  virtual void Render() override;

  virtual bool IsLoaded() override;

protected:

  virtual void SendClientEvent(std::size_t class_id, const void * event_ptr, std::size_t client_index) override;

  void Pause();
  void Resume();

private:
  std::unique_ptr<GameClientInstanceContainer> m_InstanceContainer;
  std::unique_ptr<GameClientSystems> m_ClientSystems;

  UIElementPtr<UIElementShape> m_Fader;

  Optional<UIPrototypeTutorialPopup> m_TutorialPopup;
  Sequencer m_Sequencer;

  FrameClock m_FrameClock;
  bool m_Paused = false;
};


