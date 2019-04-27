#pragma once

#include "GameClient/Modes/GameModeOnlineBase.h"

#include "Engine/UI/UIManager.h"

class GameModePlayOnline : public GameModeOnlineBase
{
public:
  GameModePlayOnline(GameContainer & game, const std::string_view & error_msg = "");
  ~GameModePlayOnline();

  void Initialize() override;
  void Deinit() override;
  void OnAssetsLoaded() override;

  void Update() override;
  void Render() override;

protected:

  void SearchCompetitive();
  void SearchCasual();
  void CreatePrivate();
  void JoinPrivate();

  void Back();

private:

  std::string m_ErrorMessage;
};
