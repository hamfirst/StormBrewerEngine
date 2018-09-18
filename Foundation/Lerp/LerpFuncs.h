#pragma once

#include <cmath>

#include "Foundation/BasicTypes/BasicTypeFuncs.h"
#include "Foundation/Math/Math.h"

enum EasingType
{
  kStep,
  kLinear,
  kSine,
  kQuadratic,
  kCubic,
  kQuartic,
  kQuintic,
  kBounce,
  kElastic,
};

enum EasingCurve
{
  kEaseIn,
  kEaseOut,
  kEaseInOut,
};

class Easing
{
public:
  // Adapted from source : http://www.robertpenner.com/easing/

  static float Ease(float t, EasingType type, EasingCurve curve);

  static float EaseIn(float t, EasingType type);
  static float EaseOut(float t, EasingType type);
  static float EaseInOut(float t, EasingType easeInType, EasingType easeOutType);
  static float EaseInOut(float t, EasingType type);
};


