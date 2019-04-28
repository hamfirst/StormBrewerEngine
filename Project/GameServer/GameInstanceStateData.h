#pragma once

#include "Foundation/Common.h"
#include "Foundation/SparseList/SparseList.h"
#include "Foundation/Allocator/IdAllocator.h"

#include "LobbyShared/SharedTypes.refl.h"

#include "Game/GameNetworkData.refl.h"

class GameInstance;
class GameClientConnection;
class GameInstanceStateBase;
class GameStageManager;

struct GameJoinInfo
{
  std::string m_UserName;
  uint64_t m_UserId;
  int m_Team;
};

struct GameInstanceStatePlayer
{
  NullOptPtr<GameClientConnection> m_Client;
  std::string m_UserName;
  uint32_t m_RandomSeed;
  bool m_GameLeader;
};

template <typename State>
struct GameInstanceStateDef
{


};

class GameInstanceStateData
{
public:
  GameInstanceStateData(NotNullPtr<GameInstance> instance, const GameInitSettings & init_settings,
          const GameInfoTeamSizes & team_info, GameStageManager & stage_manager);

  template <typename Visitor>
  void VisitPlayers(Visitor && visitor)
  {
    for (auto elem : m_Players)
    {
      visitor(elem.first, elem.second);
    }
  }

  template <typename State, typename ... InitArgs>
  void SwitchState(const GameInstanceStateDef<State> &, InitArgs && ... init_args)
  {
    auto ptr = std::make_unique<State>(*this, std::forward<InitArgs>(init_args)...);
    SetNewState(std::move(ptr));
  }

  GameInstanceStatePlayer & GetClient(std::size_t index);
  const GameInitSettings & GetInitSettings() const;
  const GameInfoTeamSizes & GetTeamInfo() const;
  void ChangeInitSettings(const GameInitSettings & init_settings);

  void NotifyLobbyNoLongerAcceptingPlayers();
  const GameStage & GetStage() const;

protected:

  void SetNewState(std::unique_ptr<GameInstanceStateBase> && state);

private:

  friend class GameInstance;

  NotNullPtr<GameInstance> m_Instance;
  GameStageManager & m_StageManager;

  GameInitSettings m_InitSettings;
  GameInfoTeamSizes m_TeamSizes;
  IdAllocator m_IdAllocator;
  SparseList<GameInstanceStatePlayer> m_Players;
};


