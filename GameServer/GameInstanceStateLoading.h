#pragma once

#include "GameServer/GameInstanceStateBase.h"

#include "Game/GameFullState.refl.h"

class GameInstanceStateLoading : public GameInstanceStateBase
{
public:
  GameInstanceStateLoading(GameInstanceStateData & state_data, const GameStateStaging & staging_data);

  virtual bool JoinPlayer(std::size_t client_index, const JoinGameMessage & join_game) override;
  virtual void RemovePlayer(std::size_t client_index) override;

  virtual void Update() override;

  virtual void HandlePlayerReady(std::size_t client_index, const ReadyMessage & msg) override;
  virtual void HandlePlayerLoaded(std::size_t client_index, const FinishLoadingMessage & msg) override;

protected:

  void AddPlayer(std::size_t client_index, int team);
  bool CheckGameReady();

private:

  GameStateLoading m_State;
  std::unique_ptr<GameSharedInstanceResources> m_InstanceResources;
  int m_TimeToWaitForLoad;
  int m_SendTimer;

  SparseList<uint64_t> m_LoadTokens;
};
