
#include "GameClient/GameModeNameSelect.h"
#include "GameClient/GameModeMainMenu.h"
#include "GameClient/GameContainer.h"

#include "Game/GameValidation.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Text/TextManager.h"

GameModeNameSelect::GameModeNameSelect(GameContainer & game) :
  GameMode(game)
{
  
}

GameModeNameSelect::~GameModeNameSelect()
{

}

void GameModeNameSelect::Initialize()
{

}

void GameModeNameSelect::OnAssetsLoaded()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();
  auto & render_util = container.GetRenderUtil();
  render_util.SetClearColor(Color(255, 255, 255, 255));

  m_Caption = m_UIManager.AllocateText("prompt");
  auto & caption_data = m_Caption->GetData();
  caption_data.m_Centered = 1.0f;
  caption_data.m_FontId = -1.0f;
  caption_data.m_PositionX = render_state.GetRenderWidth() / 2.0f;
  caption_data.m_PositionY = render_state.GetRenderHeight() / 2.0f + 20;
  caption_data.m_Text = "Enter Your Name";
  caption_data.m_TextMode = 2.0f;

  m_Input.Emplace(m_UIManager, container.GetWindow().CreateTextInputContext(true), "input", nullptr, 
    Box::FromFrameCenterAndSize(render_state.GetRenderSize() / 2, Vector2(200, 25)), "", &container.GetClientGlobalResources().UISoundEffects);
  m_Input->MakeCurrent();
  m_Input->GetInputContext().SetEnterDelegate([this](const char *) { Submit(); });
  m_Input->GetInputContext().SetValidator([](const char * val) { return ValidUserName(val, true); });

  m_Okay.Emplace(m_UIManager, "okay", nullptr,
    Box::FromFrameCenterAndSize(render_state.GetRenderSize() / 2 + Vector2(70, -30), Vector2(60, 25)), "Submit", &container.GetClientGlobalResources().UISoundEffects);
  m_Okay->SetOnClickCallback([this]() { Submit(); });

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

void GameModeNameSelect::Update()
{
  m_Sequencer.Update();

  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();

  auto input_state = container.GetWindow().GetInputState();
  m_UIManager.Update(*input_state, render_state);

  if (m_Finished)
  {
    container.SwitchMode(GameModeDef<GameModeMainMenu>{});
  }
}

void GameModeNameSelect::Render()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();
  auto & render_util = container.GetRenderUtil();

  render_util.SetClearColor(Color(255, 255, 255, 255));
  render_util.Clear();

  render_state.EnableBlendMode();

  m_UIManager.Render(render_state, render_util);
}

void GameModeNameSelect::Submit()
{
  if (ValidUserName(m_Input->GetInputContext().GetCurrentInput().data()) == false)
  {
    return;
  }

  m_Sequencer.Push(0.5f, [this](float val) {
    m_Fader->SetActive();
    auto & fader_data = m_Fader->GetData();
    fader_data.m_ColorA = val;
  });

  m_Sequencer.Push(0.0f, [this](float val) {  
    m_Finished = true;
  });
}
