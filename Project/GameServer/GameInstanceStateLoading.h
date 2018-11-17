#pragma once

#include "GameServer/GameInstanceStateBase.h"

#include "Game/GameFullState.refl.h"

class GameInstanceStateLoading : public GameInstanceStateBase
{
public:
  GameInstanceStateLoading(GameInstanceStateData & state_data, const GameStateStaging & staging_data);

  bool JoinPlayer(std::size_t client_index, const GameJoinInfo & join_game) override;
  void RemovePlayer(std::size_t client_index) override;

  void Update() override;

  void HandlePlayerReady(std::size_t client_index, const ReadyMessage & msg) override;
  void HandlePlayerLoaded(std::size_t client_index, const FinishLoadingMessage & msg) override;

protected:

  void AddPlayer(std::size_t client_index, int team);
  bool CheckGameReady();

private:

  GameStateLoading m_State;
  int m_TimeToWaitForLoad;
  int m_SendTimer;

  SparseList<uint64_t> m_LoadTokens;
};
