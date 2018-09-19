#pragma once

#include "GameServer/GameInstanceStateBase.h"

#include "Game/GameFullState.refl.h"

class GameInstanceStateStaging : public GameInstanceStateBase
{
public:
  GameInstanceStateStaging(GameInstanceStateData & state_data);

  virtual bool JoinPlayer(std::size_t client_index, const JoinGameMessage & join_game) override;
  virtual void RemovePlayer(std::size_t client_index) override;

  virtual void Update() override;

  virtual void HandlePlayerReady(std::size_t client_index, const ReadyMessage & msg) override;
  virtual void HandlePlayerLoaded(std::size_t client_index, const FinishLoadingMessage & msg) override;

protected:

  void AddPlayer(std::size_t client_index);
  bool CheckGameReady();

private:

  GameStateStaging m_State;
  int m_TimeToWaitForPlayers;
  int m_SendTimer;
};
