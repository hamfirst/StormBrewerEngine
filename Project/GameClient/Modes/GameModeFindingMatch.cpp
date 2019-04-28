
#include "GameClient/GameClientCommon.h"
#include "GameClient/Modes/GameModeFindingMatch.h"
#include "GameClient/Modes/GameModePlayOnline.h"
#include "GameClient/Modes/GameModeMainMenu.h"
#include "GameClient/Modes/GameModeOnlineStaging.h"
#include "GameClient/GameContainer.h"

#include "Engine/UI/UIManager.h"

GLOBAL_ASSET(UIResourcePtr, "./UIs/FindingMatch.ui", g_FindingMatchMenu);

GameModeFindingMatch::GameModeFindingMatch(GameContainer & game, bool ranked) :
        GameModeOnlineBase(game),
        m_Ranked(ranked),
        m_StartTime(GetTimeSeconds())
{
  auto & container = GetContainer();
  auto & lobby_connection = container.GetLobbyClient();

  lobby_connection.SetGameJoinCallback([&](){
    if(m_State == GameModeFindingMatchState::kCancelling)
    {
      lobby_connection.SendLeaveGame();
      m_State = GameModeFindingMatchState::kCanceled;
    }
    else
    {
      m_State = GameModeFindingMatchState::kInGame;
    }
  });

  lobby_connection.SetGameJoinFailedCallback([&]() {
    m_State = GameModeFindingMatchState::kFailed;
  });

  lobby_connection.SetCancelMatchmakingCallback([&]() {
    m_State = GameModeFindingMatchState::kCanceled;
  });
}

GameModeFindingMatch::~GameModeFindingMatch()
{
  auto & container = GetContainer();

  if(container.HasLobbyClient())
  {
    auto & lobby_connection = container.GetLobbyClient();

    lobby_connection.SetGameJoinCallback({});
    lobby_connection.SetGameJoinFailedCallback({});
    lobby_connection.SetCancelMatchmakingCallback({});
  }
}

void GameModeFindingMatch::Initialize()
{

}

void GameModeFindingMatch::Deinit()
{
  auto & container = GetContainer();
  container.GetUIManager()->ClearUI();
  container.GetUIManager()->ClearGameInterface();
}

void GameModeFindingMatch::OnAssetsLoaded()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();

  auto ui = container.GetUIManager();

  auto & game_interface = ui->CreateGameInterface();

  BIND_SCRIPT_INTERFACE(game_interface, this, Back);

  container.GetUIManager()->PushUIDef(g_FindingMatchMenu);
}

void GameModeFindingMatch::Update()
{
  if(HandleDisconnect())
  {
    return;
  }

  auto & container = GetContainer();
  if(m_State == GameModeFindingMatchState::kCanceled)
  {
#ifdef NET_FORCE_CASUAL_GAMES
    container.StopLobbyClient();
    container.SwitchMode<GameModeMainMenu>();
#else
    container.SwitchMode<GameModePlayOnline>();
#endif
    return;
  }

  if(m_State == GameModeFindingMatchState::kFailed)
  {
#ifdef NET_FORCE_CASUAL_GAMES
    container.StopLobbyClient();
    container.SwitchMode<GameModeMainMenu>("Failed to connect to game");
#else
    container.SwitchMode<GameModePlayOnline>("Failed to connect to game");
#endif
    return;
  }

  if(m_State == GameModeFindingMatchState::kInGame)
  {
    container.SwitchMode<GameModeOnlineStaging>();
    return;
  }

  if(m_Ranked == false)
  {
    auto timer = kMaxTimeInMatchmaker - (int)(GetTimeSeconds() - m_StartTime);
    auto minutes = timer / 60;
    auto seconds = timer % 60;

    char timer_str[20];
    snprintf(timer_str, sizeof(timer_str), "%d:%02d", minutes, seconds);

    container.GetUIManager()->SetGlobal("time_to_wait", ScriptValue(std::string(timer_str)));
  }
  else
  {
    container.GetUIManager()->SetGlobal("time_to_wait", ScriptValue(std::string("")));
  }

  auto & render_state = container.GetRenderState();

  container.GetLobbyClient().Update();
  container.GetWindow().Update();
  container.UpdateUIManager();
}

void GameModeFindingMatch::Render()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();

  render_state.SetDefaultClearColor();
  render_state.Clear();

  render_state.EnableBlendMode();

  container.RenderUIManager();
}

void GameModeFindingMatch::Back()
{
  auto & container = GetContainer();
  container.GetLobbyClient().CancelMatchmaker();
}