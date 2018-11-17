#include "GameClient/GameClientCommon.h"
#include "GameClient/GameModeJoinPrivateGame.h"
#include "GameClient/GameModeMainMenu.h"
#include "GameClient/GameModeConnecting.h"
#include "GameClient/GameContainer.h"

#include "GameShared/GameValidation.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Text/TextManager.h"

GameModeJoinPrivateGame::GameModeJoinPrivateGame(GameContainer & game) :
        GameMode(game),
        m_UIManager(game.GetWindow())
{

}

GameModeJoinPrivateGame::~GameModeJoinPrivateGame()
{

}

void GameModeJoinPrivateGame::Initialize()
{

}

void GameModeJoinPrivateGame::OnAssetsLoaded()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();
  auto & render_util = container.GetRenderUtil();
  render_util.SetClearColor(Color(255, 255, 255, 255));

  auto half_res = Vector2(render_state.GetRenderWidth(), render_state.GetRenderHeight()) / 2;

  m_Caption = m_UIManager.AllocateText("prompt");
  auto & caption_data = m_Caption->GetData();
  caption_data.m_FontId = -1.0f;
  caption_data.m_PositionX = 0;
  caption_data.m_PositionY = 20;
  caption_data.m_Text = "Private Room Key";
  caption_data.m_TextMode = 2.0f;

  m_Input.Emplace(m_UIManager, "input", nullptr,
                  Box::FromFrameCenterAndSize(Vector2(0, 0), Vector2(200, 25)), "");

  m_Input->GetInputContext().SetEnterDelegate([this](const char *) { Submit(); });
  m_Input->GetInputContext().SetValidator([](const char * val) { return ValidGameCode(val, true); });

  m_Okay.Emplace(m_UIManager, "okay", nullptr,
                 Box::FromFrameCenterAndSize(Vector2(70, -30), Vector2(60, 25)), "Submit");
  m_Okay->SetOnClickCallback([this]() { Submit(); });

  m_Back.Emplace(m_UIManager, "back", nullptr,
                 Box::FromFrameCenterAndSize(Vector2(half_res.x - 35, 30 - half_res.y), Vector2(60, 25)), "Back", nullptr, true);
  m_Back->SetOnClickCallback([this]() { Back(); });

  m_MuteButton.Emplace(m_UIManager, "mute", nullptr, half_res - Vector2(60, 20), false);
  m_MusicButton.Emplace(m_UIManager, "music", nullptr, half_res - Vector2(100, 20), true);
  m_FullscreenButton.Emplace(m_UIManager, "fullscreen", nullptr, half_res - Vector2(20, 20), container.GetWindow());

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

void GameModeJoinPrivateGame::Update()
{
  m_Sequencer.Update();

  m_Input->MakeCurrent();

  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();

  container.GetWindow().Update();

  auto input_state = container.GetWindow().GetInputState();
  m_UIManager.Update(*input_state, render_state);
}

void GameModeJoinPrivateGame::Render()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();
  auto & render_util = container.GetRenderUtil();

  RenderUtil::SetClearColor(Color(255, 255, 255, 255));
  RenderUtil::Clear();

  render_state.EnableBlendMode();

  m_UIManager.Render(render_state, render_util);
}

void GameModeJoinPrivateGame::Submit()
{
  if (ValidGameCode(m_Input->GetInputContext().GetCurrentInput().data()) == false)
  {
    return;
  }

  auto & container = GetContainer();
  auto & input_text = m_Input->GetInputContext().GetCurrentInput();
  auto & net_init_settings = container.GetNetworkInitSettings();

  auto text = input_text.data();
  uint32_t game_code = 0;

  for(int index = 0; index < 4; ++index)
  {
    auto c = text[index];
    int val = 0;

    if(c >= 'a' && c <= 'z')
    {
      val = c - 'a';
    }
    else if(c >= 'A' && c <= 'A')
    {
      val = c - 'A';
    }
    else if(c >= '0' && c <= '9')
    {
      val = c - '0' + 26;
    }

    game_code <<= 8;
    game_code |= val;
  }

  net_init_settings.m_CreatePrivateGame = false;
  net_init_settings.m_JoinPrivateGameKey = game_code;
  container.StartNetworkClient();
  container.SwitchMode(GameModeDef<GameModeConnecting>{});
}

void GameModeJoinPrivateGame::Back()
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
