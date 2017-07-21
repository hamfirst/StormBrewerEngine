
#include "GameClient/GameModeEndGame.h"
#include "GameClient/GameModeConnecting.h"
#include "GameClient/GameContainer.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Text/TextManager.h"

GameModeEndGame::GameModeEndGame(GameContainer & game, std::unique_ptr<GameClientInstanceContainer> && instance_container) :
  GameMode(game),
  m_InstanceContainer(std::move(instance_container))
{

}

GameModeEndGame::~GameModeEndGame()
{

}

void GameModeEndGame::Initialize()
{
  auto instance_data = m_InstanceContainer->GetInstanceData(m_DefaultSender);

  auto & local_data = instance_data.GetLocalData();
  auto & game_state = instance_data.GetGameState();
  auto & local_player = game_state.m_Players[(int)local_data.m_PlayerIndex];

  m_Victory = (game_state.m_WiningTeam == local_player.m_Team);
}

void GameModeEndGame::OnAssetsLoaded()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();
  auto & render_util = container.GetRenderUtil();
  render_util.SetClearColor(Color(255, 255, 255, 255));

  m_PlayAgain.Emplace(m_UIManager, "playonline", nullptr, Box::FromFrameCenterAndSize(render_state.GetRenderSize() / 2, Vector2(150, 50)), "Play Again", &container.GetClientGlobalResources().UISoundEffects);
  m_PlayAgain->SetOnClickCallback([this] { PlayOnline(); });

  m_Result = m_UIManager.AllocateText("result");
  auto & result_data = m_Result->GetData();
  result_data.m_Centered = 1.0f;
  result_data.m_FontId = -1.0f;
  result_data.m_PositionX = render_state.GetRenderWidth() / 2.0f;
  result_data.m_PositionY = render_state.GetRenderHeight() / 2.0f + 80;
  result_data.m_Text = m_Victory ? "Victory" : "Defeat";
  result_data.m_TextMode = 2.0f;

  m_Fader = m_UIManager.AllocateShape("fader", nullptr);
  m_Fader->SetActive();
  auto & fader_data = m_Fader->GetData();
  fader_data.SetColor(Color(255, 255, 255, 255));
  fader_data.SetBounds(Box::FromPoints(Vector2(0, 0), Vector2(kDefaultResolutionWidth, kDefaultResolutionHeight)));
  fader_data.m_Shape = kUIElementShapeFilledRectangle;

  m_Sequencer.Push(0.5f, [this](float val) {
    auto & fader_data = m_Fader->GetData();
    fader_data.m_ColorA = 1.0f - val;
  });

  m_Sequencer.Push(0.0f, [this](float val) { m_Fader->SetInactive(); });
}

void GameModeEndGame::Update()
{
  m_Sequencer.Update();

  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();

  auto input_state = container.GetWindow().GetInputState();
  m_UIManager.Update(*input_state, render_state);

}

void GameModeEndGame::Render()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();
  auto & render_util = container.GetRenderUtil();

  render_util.SetClearColor(Color(255, 255, 255, 255));
  render_util.Clear();

  render_state.EnableBlendMode();

  m_UIManager.Render(render_state, render_util);
}

void GameModeEndGame::PlayOnline()
{
  m_Fader->SetActive();

  auto & container = GetContainer();
  container.StartNetworkClient();
  container.SwitchMode(GameModeDef<GameModeConnecting>{});
}
