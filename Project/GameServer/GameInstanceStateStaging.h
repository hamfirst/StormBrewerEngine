#pragma once

#include "GameServer/GameInstanceStateBase.h"

#include "Game/GameFullState.refl.h"

class GameInstanceStateStaging : public GameInstanceStateBase
{
public:
  explicit GameInstanceStateStaging(GameInstanceStateData & state_data);

  bool JoinPlayer(std::size_t client_index, const GameJoinInfo & join_game) override;
  void RemovePlayer(std::size_t client_index) override;

  void Update() override;

  void HandlePlayerReady(std::size_t client_index, const ReadyMessage & msg) override;
  void HandlePlayerLoaded(std::size_t client_index, const FinishLoadingMessage & msg) override;
  void HandleTextChat(std::size_t client_index, const SendTextChatMessage & msg) override;
  void HandleChangeLoadout(std::size_t client_index, const ChangeLoadoutMessage & msg) override;

protected:

  void AddPlayer(std::size_t client_index);
  bool CheckGameReady();

private:

  GameStateStaging m_State;
  int m_TimeToWaitForPlayers;
  int m_SendTimer;
};
