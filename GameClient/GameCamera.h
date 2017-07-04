#pragma once

#include "Engine/Camera/Camera.h"

class GameContainer;

static const int kDefaultResolutionWidth = 320;
static const int kDefaultResolutionHeight = 180;

class GameCamera
{
public:
  GameCamera();

  void Update(GameContainer & container, const Vector2 & screen_resolution);

  Vector2 GetGameResolution();
  Vector2 GetCameraPosition();

private:

  Vector2 m_GameResolution;
  Vector2 m_CameraPosition;
};

