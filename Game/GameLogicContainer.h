#pragma once

struct GameGlobalData;
class ServerObjectManager;
class GameServerEventSender;
class GameSimulationEventCallbacks;
class GameStage;

class GameLogicContainer
{
public:
  GameLogicContainer(
    GameGlobalData & global_data,
    ServerObjectManager & object_manager,
    GameServerEventSender & server_event_sender,
    GameSimulationEventCallbacks & sim_event_sender,
    const GameStage & stage, 
    bool is_authority,
    int & send_timer);

  GameGlobalData & GetGlobalData();
  ServerObjectManager & GetObjectManager();
  GameServerEventSender & GetEventSender();
  GameSimulationEventCallbacks & GetSimEventCallbacks();
  const GameStage & GetStage();
  bool IsAuthority();
  void TriggerImmediateSend();

private:
  GameGlobalData & m_GlobalData;
  ServerObjectManager & m_ObjectManager;
  GameServerEventSender & m_ServerEventSender;
  GameSimulationEventCallbacks & m_SimEventSender;
  const GameStage & m_Stage;
  bool m_IsAuthority;
  int & m_SendTimer;
};
