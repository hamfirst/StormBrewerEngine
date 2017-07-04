
#include "GameClient/GameCamera.h"


GameCamera::GameCamera()
{
  m_GameResolution = Vector2(kDefaultResolutionWidth, kDefaultResolutionHeight);
  m_CameraPosition = {};
}

void GameCamera::Update(GameContainer & container, const Vector2 & screen_resolution)
{

}

Vector2 GameCamera::GetGameResolution()
{
  return m_GameResolution;
}

Vector2 GameCamera::GetCameraPosition()
{
  return m_CameraPosition;
}
