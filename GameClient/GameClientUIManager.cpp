
#include "GameClient/GameClientUIManager.h"
#include "GameClient/GameContainer.h"
#include "GameClient/GameClientEventSender.h"
#include "GameClient/GameCamera.h"
#include "GameClient/GameClientSystems.h"

#include "Game/GameNetworkEvents.refl.h"

#include "Engine/Window/Window.h"
#include "Engine/Input/ControlId.h"

GameClientUIManager::GameClientUIManager(GameContainer & container) :
  m_GameContainer(container)
{
  m_Turn = m_UIManager.AllocateText("Turn", nullptr, {});
  m_Turn->GetData().m_FontId = -1;
  m_Turn->GetData().m_Centered = 1;

  m_EndTurn = m_UIManager.AllocateGradient("EndTurn", nullptr, {});
  m_EndTurn->SetActive();

  m_EndTurnTimer = m_UIManager.AllocateText("TurnTimer", nullptr, {}, {});
  m_EndTurnTimer->GetData().m_FontId = -1;
  m_EndTurnTimer->GetData().m_Centered = 1;  

  m_EndTurn->SetOnClickHandler([this](NotNullPtr<UIElement>) 
  { 
    m_GameContainer.GetInstanceData()->GetEventSender().SendClientEvent(EndTurnEvent{}); 
  });

  m_EndTurnCaption = m_UIManager.AllocateText("Caption", m_EndTurn, {}, {});
  m_EndTurnCaption->GetData().m_FontId = -1;
  m_EndTurnCaption->GetData().m_TextMode = 2;
  m_EndTurnCaption->GetData().m_PositionX = 50;
  m_EndTurnCaption->GetData().m_PositionY = 40;
  m_EndTurnCaption->GetData().m_Centered = 1;
  m_EndTurnCaption->GetData().m_Text = "End Turn";

  m_PlayerHealth = m_UIManager.AllocateText("PlayerHealth", nullptr, {}, {});
  m_PlayerHealth->GetData().m_FontId = -1;

  m_OpponentHealth = m_UIManager.AllocateText("OpponentHealth", nullptr, {}, {});
  m_OpponentHealth->GetData().m_FontId = -1;
}

GameClientUIManager::~GameClientUIManager()
{

}

void GameClientUIManager::Update()
{
  auto & local_data = m_GameContainer.GetInstanceData()->GetLocalData();
  auto & game_state = m_GameContainer.GetInstanceData()->GetGameState();
  auto & local_player = game_state.m_Players[(int)local_data.m_PlayerIndex];
  auto & camera = m_GameContainer.GetClientSystems()->GetCamera();

  auto resolution = camera.GetGameResolution();
  m_Turn->GetData().m_PositionX = (float)(resolution.x / 2);
  m_Turn->GetData().m_PositionY = (float)(resolution.y - 10);

  m_EndTurnTimer->GetData().m_PositionX = (float)(resolution.x / 2);
  m_EndTurnTimer->GetData().m_PositionY = (float)(resolution.y - 25);

  if (game_state.m_ActiveTurn == -1 || game_state.m_Running)
  {
    m_Turn->GetData().m_Text.clear();
    m_EndTurn->SetDisabled();
    m_EndTurnTimer->SetDisabled();
  }
  else
  {
    if (game_state.m_ActiveTurn == local_player.m_Team)
    {
      m_Turn->GetData().m_Text = "Your turn";

      m_EndTurn->SetEnabled();

      m_EndTurn->GetData().m_StartX = (float)(resolution.x - 110);
      m_EndTurn->GetData().m_StartY = (float)(resolution.y - 80);
      m_EndTurn->GetData().m_EndX = m_EndTurn->GetData().m_StartX + 100;
      m_EndTurn->GetData().m_EndY = m_EndTurn->GetData().m_StartY + 70;

      if (m_EndTurn->GetState() == UIElementState::kPressed)
      {
        m_EndTurn->GetData().SetColor(Color(0.8f, 0.5f, 0.5f, 1.0f));
      }
      else if (m_EndTurn->GetState() == UIElementState::kHover)
      {
        m_EndTurn->GetData().SetColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
      }
      else
      {
        m_EndTurn->GetData().SetColor(Color(0.8f, 0.8f, 0.8f, 1.0f));
      }
    }
    else
    {
      m_Turn->GetData().m_Text = "Opponent's turn";
      m_EndTurn->SetDisabled();
    }

    auto time_left = game_state.m_TimeExpiration / 60;

    m_EndTurnTimer->SetEnabled();
    m_EndTurnTimer->GetData().m_Text = std::to_string(time_left);
  }

  m_PlayerHealth->GetData().m_Text = "Player Health: " + std::to_string(local_player.m_Health);
  m_PlayerHealth->GetData().m_PositionX = 5;
  m_PlayerHealth->GetData().m_PositionY = 5;


  auto opponent_player_index = !(int)local_data.m_PlayerIndex;

  if (game_state.m_Players.HasAt(opponent_player_index))
  {
    auto & opponent_player = game_state.m_Players[(int)opponent_player_index];

    m_OpponentHealth->GetData().m_Text = "Opponent Health: " + std::to_string(opponent_player.m_Health);
    m_OpponentHealth->GetData().m_PositionX = 5;
    m_OpponentHealth->GetData().m_PositionY = (float)(resolution.y - 15);
  }

  m_UIManager.Update(*m_GameContainer.GetWindow().GetInputState(), m_GameContainer.GetRenderState());
}

void GameClientUIManager::Render()
{
  m_UIManager.Render(m_GameContainer.GetRenderState(), m_GameContainer.GetRenderUtil());
}

bool GameClientUIManager::IsBlocking()
{
  return m_UIManager.HasSelectedElement();
}
