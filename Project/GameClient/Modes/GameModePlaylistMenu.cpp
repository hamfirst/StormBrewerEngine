
#include "GameClient/GameClientCommon.h"
#include "GameClient/Modes/GameModePlaylistMenu.h"
#include "GameClient/Modes/GameModePlayOnline.h"
#include "GameClient/Modes/GameModeMainMenu.h"
#include "GameClient/Modes/GameModeFindingMatch.h"
#include "GameClient/GameContainer.h"

#include "GameShared/GamePlayListAsset.refl.meta.h"

#include "LobbyShared/SharedTypes.refl.meta.h"

#include "Engine/UI/UIManager.h"

#include "Foundation/Script/ScriptDataObject.h"

#include "ProjectSettings/ProjectNetworkSettings.h"

GLOBAL_ASSET(UIResourcePtr, "./UIs/PlaylistMenuCompetitive.ui", g_PlaylistMenuCompetitive)
GLOBAL_ASSET(UIResourcePtr, "./UIs/PlaylistMenuCasual.ui", g_PlaylistMenuCasual);

GameModePlaylistMenu::GameModePlaylistMenu(GameContainer & game, bool competitive) :
  GameModeOnlineBase(game),
  m_CasualPlaylist("./CasualPlaylist.txt"),
  m_CompetitivePlaylist("./CompetitivePlaylist.txt"),
  m_Competitive(competitive)
{

}

GameModePlaylistMenu::~GameModePlaylistMenu()
{

}

void GameModePlaylistMenu::Initialize()
{

}

void GameModePlaylistMenu::Deinit()
{
  auto & container = GetContainer();
  container.GetUIManager()->ClearUI();
  container.GetUIManager()->ClearGameInterface();
}

void GameModePlaylistMenu::OnAssetsLoaded()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();

  auto ui = container.GetUIManager();

  auto & game_interface = ui->CreateGameInterface();

  game_interface.AddVariable("casual_playlist",
                             CreateScriptDataObject(ui->GetScriptState(), m_CasualPlaylist.GetPlayListAsset().GetData()));
  game_interface.AddVariable("competitive_playlist",
                             CreateScriptDataObject(ui->GetScriptState(), m_CompetitivePlaylist.GetPlayListAsset().GetData()));

  auto & user_local = container.GetLobbyClient().GetUserLocalData().Value();
  std::unordered_map<std::string, float> rank_data;
  for(auto & playlist : m_CompetitivePlaylist.GetPlayListAsset().GetData()->m_Elements)
  {
    auto rank = user_local.m_RankInfo.TryGet(crc32(playlist.m_InternalName));
    rank_data.emplace(std::make_pair(playlist.m_InternalName, rank ? (float)rank->m_Rank : -1.0f));
  }

  game_interface.AddVariable("competitive_ranks", CreateScriptDataObject(ui->GetScriptState(), rank_data));

  BIND_SCRIPT_INTERFACE(game_interface, this, Search);
  BIND_SCRIPT_INTERFACE(game_interface, this, Back);

  if(m_Competitive)
  {
    container.GetUIManager()->PushUIDef(g_PlaylistMenuCompetitive);
  }
  else
  {
    container.GetUIManager()->PushUIDef(g_PlaylistMenuCasual);
  }
}

void GameModePlaylistMenu::Update()
{
  if(HandleDisconnect())
  {
    return;
  }

  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();

  container.GetWindow().Update();
  container.UpdateUIManager();
}

void GameModePlaylistMenu::Render()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();

  render_state.SetDefaultClearColor();
  render_state.Clear();

  render_state.EnableBlendMode();

  container.RenderUIManager();
}

void GameModePlaylistMenu::Search(int playlist_mask)
{
  auto & container = GetContainer();
  container.GetLobbyClient().SendJoinMatchmaker(playlist_mask, m_Competitive);
  container.SwitchMode<GameModeFindingMatch>();
}

void GameModePlaylistMenu::Back()
{
  auto & container = GetContainer();
#ifdef NET_FORCE_CASUAL_GAMES
  container.StopLobbyClient();
  container.SwitchMode<GameModeMainMenu>();
#else
  container.SwitchMode<GameModePlayOnline>();
#endif
}
