#pragma once

#include "Foundation/Common.h"
#include "Foundation/SparseList/SparseList.h"
#include "Foundation/Allocator/IdAllocator.h"

#include "Game/GameNetworkData.refl.h"

class GameInstance;
class GameClientConnection;
class GameInstanceStateBase;
class GameStageManager;

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
  GameInstanceStateData(NotNullPtr<GameInstance> instance, const GameInitSettings & init_settings, GameStageManager & stage_manager);

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
  void ChangeInitSettings(const GameInitSettings & init_settings);

  const GameStage & GetStage() const;
  uint32_t GetPrivateRoomId() const;

protected:

  void SetNewState(std::unique_ptr<GameInstanceStateBase> && state);

private:

  friend class GameInstance;

  NotNullPtr<GameInstance> m_Instance;
  GameStageManager & m_StageManager;

  GameInitSettings m_InitSettings;
  IdAllocator m_IdAllocator;
  SparseList<GameInstanceStatePlayer> m_Players;
};

