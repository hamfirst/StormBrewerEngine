
#include "GameClient/GameCamera.h"
#include "GameClient/GameContainer.h"


GameCamera::GameCamera(GameContainer & container) :
  m_GameContainer(container)
{

}

void GameCamera::Update()
{
  SetGameResolution(Vector2(kDefaultResolutionWidth, kDefaultResolutionHeight));
}

void GameCamera::TransformWorldSpaceToGameplaySpace(int & x, int & y)
{
  auto & local_data = m_GameContainer.GetInstanceData()->GetLocalData();
  auto & game_state = m_GameContainer.GetInstanceData()->GetGameState();
  auto & local_player = game_state.m_Players[(int)local_data.m_PlayerIndex];

  if (local_player.m_Team == 1)
  {
    x *= -1;
    y *= -1;
  }
}

Vector2 GameCamera::TransformWorldSpaceToGameplaySpace(const Vector2 & vec)
{
  auto & local_data = m_GameContainer.GetInstanceData()->GetLocalData();
  auto & game_state = m_GameContainer.GetInstanceData()->GetGameState();
  auto & local_player = game_state.m_Players[(int)local_data.m_PlayerIndex];

  if (local_player.m_Team == 1)
  {
    return vec * -1;
  }

  return vec;
}

Box GameCamera::TransformWorldSpaceToGameplaySpace(const Box & box)
{
  auto & local_data = m_GameContainer.GetInstanceData()->GetLocalData();
  auto & game_state = m_GameContainer.GetInstanceData()->GetGameState();
  auto & local_player = game_state.m_Players[(int)local_data.m_PlayerIndex];

  if (local_player.m_Team == 1)
  {
    auto b = box;
    std::swap(b.m_Start, b.m_End);
    b.m_Start *= -1;
    b.m_End *= -1;
    return b;
  }

  return box;
}
