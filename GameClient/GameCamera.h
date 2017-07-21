#pragma once

#include "Engine/Camera/Camera.h"

class GameContainer;

static const int kDefaultResolutionWidth = 360;
static const int kDefaultResolutionHeight = 640;

class GameCamera : public Camera
{
public:
  GameCamera(GameContainer & container);

  void Update();

  void TransformWorldSpaceToGameplaySpace(int & x, int & y);
  Vector2 TransformWorldSpaceToGameplaySpace(const Vector2 & vec);
  Box TransformWorldSpaceToGameplaySpace(const Box & box);

private:

  GameContainer & m_GameContainer;
};

