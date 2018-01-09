#include "GameClient/GameClientCommon.h"
#include "GameClient/GameModeOfflineStaging.h"
#include "GameClient/GameModeMainMenu.h"
#include "GameClient/GameModeLocalMultiplayer.h"
#include "GameClient/GameContainer.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Text/TextManager.h"


GameModeOfflineStaging::GameModeOfflineStaging(GameContainer & game) :
  GameMode(game),
  m_UIManager(game.GetWindow())
{
  for (int index = 0; index < kMaxPlayers; ++index)
  {
    m_Attached[index] = false;
  }
}

GameModeOfflineStaging::~GameModeOfflineStaging()
{

}

void GameModeOfflineStaging::Initialize()
{

}

void GameModeOfflineStaging::OnAssetsLoaded()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();
  auto & render_util = container.GetRenderUtil();
  render_util.SetClearColor(Color(255, 255, 255, 255));

  auto half_res = Vector2(render_state.GetRenderWidth(), render_state.GetRenderHeight()) / 2;

  UIElementFullTextureInitData logo_init;
  logo_init.m_TextureFile = "./Images/GameTitle.png";
  UIElementFullTextureData logo_data;
  logo_data.m_PositionX = 0;
  logo_data.m_PositionY = 0;
  logo_data.m_ColorA = 0.3f;

  m_TitleImage = m_UIManager.AllocateFullTexture("logo", nullptr, logo_init, logo_data);

  m_Start.Emplace(m_UIManager, "start", nullptr, Box::FromFrameCenterAndSize(Vector2(half_res.x - 85, 30), Vector2(150, 25)), 
    "Start", &container.GetClientGlobalResources().UISoundEffects);
  m_Start->SetOnClickCallback([this] { Start(); });

  m_Back.Emplace(m_UIManager, "back", nullptr, Box::FromFrameCenterAndSize(Vector2(half_res.x - 85, 30 - half_res.y), Vector2(150, 25)), 
    "Back", &container.GetClientGlobalResources().UISoundEffects, true);
  m_Back->SetOnClickCallback([this] { Back(); });

  m_StagingUI = m_UIManager.AllocateElementFromDef("staging", *container.GetClientGlobalResources().Staging.GetData());

  m_MuteButton.Emplace(m_UIManager, "mute", nullptr, half_res - Vector2(60, 20), false, &container.GetClientGlobalResources().UISoundEffects);
  m_MusicButton.Emplace(m_UIManager, "music", nullptr, half_res - Vector2(100, 20), true, &container.GetClientGlobalResources().UISoundEffects);
  m_FullscreenButton.Emplace(m_UIManager, "fullscreen", nullptr, half_res - Vector2(20, 20), container.GetWindow(), &container.GetClientGlobalResources().UISoundEffects);

  m_Fader = m_UIManager.AllocateShape("fader", nullptr);
  m_Fader->SetActive();
  auto & fader_data = m_Fader->GetData();
  fader_data.SetColor(Color(255, 255, 255, 255));
  fader_data.SetBounds(Box::FromPoints(-half_res, half_res));
  fader_data.m_Shape = kUIElementShapeFilledRectangle;

  m_Sequencer.Push(0.5f, [this](float val) {
    auto & fader_data = m_Fader->GetData();
    fader_data.m_ColorA = 1.0f - val;
  });

  m_Sequencer.Push(0.0f, [this](float val) { m_Fader->SetInactive(); });
}

void GameModeOfflineStaging::Update()
{
  m_Sequencer.Update();

  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();

  container.GetWindow().Update();

  auto input_state = container.GetWindow().GetInputState();
  m_UIManager.Update(*input_state, render_state);

  auto staging_ui = m_StagingUI.Resolve();

  for (auto index = 0; index < kMaxPlayers; ++index)
  {
    if (m_Attached[index])
    {
      if (input_state->GetGamepadButtonPressedThisFrame(index, GamepadButton::kB))
      {
        m_Attached[index] = false;
      }
      else if (input_state->GetGamepadButtonPressedThisFrame(index, GamepadButton::kStart) && m_Sequencer.IsComplete())
      {
        Start();
      }
    }
    else
    {
      if (input_state->GetGamepadButtonPressedThisFrame(index, GamepadButton::kA))
      {
        m_Attached[index] = true;
      }
    }

    if (staging_ui)
    {
      auto player_base_str = "Player" + std::to_string(index + 1);
      staging_ui->SetInput(crc32(player_base_str + "Joined"), m_Attached[index] ? 1.0f : 0.0f);

      auto input = input_state->GetGamepadJoystick(index, GamepadJoystick::kLeft);
      InputState::ApplyDeadZone(input);

      staging_ui->SetInput(crc32(player_base_str + "XInput"), input.x);
      staging_ui->SetInput(crc32(player_base_str + "YInput"), -input.y);
    }
  }
}

void GameModeOfflineStaging::Render()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();
  auto & render_util = container.GetRenderUtil();

  render_util.SetClearColor(Color(255, 255, 255, 255));
  render_util.Clear();

  render_state.EnableBlendMode();

  m_UIManager.Render(render_state, render_util);
}

void GameModeOfflineStaging::Start()
{
  auto num_attached = 0;
  for (auto attached : m_Attached)
  {
    if (attached)
    {
      num_attached++;
    }
  }

  if (num_attached == 0)
  {
    return;
  }

  m_Sequencer.Push(0.5f, [this](float val) {
    m_Fader->SetActive();
    auto & fader_data = m_Fader->GetData();
    fader_data.m_ColorA = val;
  });

  m_Sequencer.Push(0.0f, [this](float val) {

    std::vector<bool> attached_players;
    for (auto index = 0; index < kMaxPlayers; ++index)
    {
      attached_players.push_back(m_Attached[index]);
    }

    auto & container = GetContainer();
    container.SwitchMode(GameModeDef<GameModeLocalMultiplayer>{}, attached_players, GameInitSettings{});
  });
}


void GameModeOfflineStaging::Back()
{
  m_Sequencer.Push(0.5f, [this](float val) {
    m_Fader->SetActive();
    auto & fader_data = m_Fader->GetData();
    fader_data.m_ColorA = val;
  });

  m_Sequencer.Push(0.0f, [this](float val) {
    auto & container = GetContainer();
    container.SwitchMode(GameModeDef<GameModeMainMenu>{});
  });
}

