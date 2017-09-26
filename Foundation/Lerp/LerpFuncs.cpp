
#include "Foundation/Common.h"
#include "Foundation/Lerp/LerpFuncs.h"

struct Sine
{
  static float EaseIn(float s)
  {
    return (float)sinf(s * kHalfPi - kPi) + 1;
  }
  static float EaseOut(float s)
  {
    return (float)sinf(s * kHalfPi);
  }
  static float EaseInOut(float s)
  {
    return (float)(sinf(s * kPi - kHalfPi) + 1) / 2;
  }
};

struct Power
{
  static float EaseIn(float s, int power)
  {
    return (float)powf(s, (float)power);
  }

  static float EaseOut(float s, int power)
  {
    auto sign = power % 2 == 0 ? -1 : 1;
    auto sf = (float)sign;
    return (float)(sf * (powf(s - 1, (float)power) + sf));
  }

  static float EaseInOut(float s, int power)
  {
    s *= 2;
    if (s < 1) return EaseIn(s, power) / 2;
    auto sign = power % 2 == 0 ? -1 : 1;
    auto sf = (float)sign;
    return (float)(sf / 2.0 * (powf(s - 2, (float)power) + sf * 2));
  }
};

struct Bounce
{
  static float EaseIn(float s)
  {
    return EaseOut(1 - s);
  }

  static float EaseOut(float s)
  {
    if (s < (1.0f / 2.75f))
      return (7.5625f * s * s);
    else if (s < (2.0f / 2.75f))
      return (7.5625f * (s -= (1.5f / 2.75f)) * s + .75f);
    else if (s < (2.5f / 2.75f))
      return (7.5625f * (s -= (2.25f / 2.75f)) * s + .9375f);
    else
      return (7.5625f * (s -= (2.625f / 2.75f)) * s + .984375f);
  }

  static float EaseInOut(float s)
  {
    if (s < 0.5f)
      return EaseIn(s * 2.0f) * .5f;
    else
      return EaseOut(s * 2.0f - 1.0f) * .5f + .5f;
  }
};

struct Elastic
{
  static float EaseIn(float s)
  {
    if (s <= 0.0f)
    {
      return 0.0f;
    }

    if (s >= 1.0f)
    {
      return 1.0f;
    }

    return powf(2, 10.0f * (s - 1.0f)) * sinf((s - 1.1f) * 5.0f * kPi);
  }

  static float EaseOut(float s)
  {
    if (s <= 0.0f)
    {
      return 0.0f;
    }

    if (s >= 1.0f)
    {
      return 1.0f;
    }

    return powf(2, -10.0f * s) * sinf((s - 0.1f) * 5.0f * kPi) + 1;
  }

  static float EaseInOut(float s)
  {
    if (s <= 0.0f)
    {
      return 0.0f;
    }

    if (s >= 1.0f)
    {
      return 1.0f;
    }

    s *= 2;

    if (s < 1) 
    {
      return -0.5f * powf(2, 10.0f * (s - 1.0f)) * sinf((s - 1.1f) * 5.0f * kPi);
    }

    return 0.5f * powf(2, -10.0f * (s - 1.0f)) * sinf((s - 1.1f) * 5.0f * kPi) + 1;
  }
};

float Easing::Ease(float t, EasingType type, EasingCurve curve)
{
  switch (curve)
  {
  case EasingCurve::kEaseIn:
  default:
    return EaseIn(t, type);
  case EasingCurve::kEaseOut:
    return EaseOut(t, type);
  case EasingCurve::kEaseInOut:
    return EaseInOut(t, type);
  }
}

float Easing::EaseIn(float t, EasingType type)
{
  switch (type)
  {
  case EasingType::kStep: return t < 0.5f ? 0.0f : 1.0f;
  case EasingType::kLinear: return (float)t;
  case EasingType::kSine: return Sine::EaseIn(t);
  case EasingType::kQuadratic: return Power::EaseIn(t, 2);
  case EasingType::kCubic: return Power::EaseIn(t, 3);
  case EasingType::kQuartic: return Power::EaseIn(t, 4);
  case EasingType::kQuintic: return Power::EaseIn(t, 5);
  case EasingType::kBounce: return Bounce::EaseIn(t);
  case EasingType::kElastic: return Elastic::EaseIn(t);
  default: return Power::EaseIn(t, 2);
  }
}

float Easing::EaseOut(float t, EasingType type)
{
  switch (type)
  {
  case EasingType::kStep: return t < 0.5f ? 0.0f : 1.0f;
  case EasingType::kLinear: return (float)t;
  case EasingType::kSine: return Sine::EaseOut(t);
  case EasingType::kQuadratic: return Power::EaseOut(t, 2);
  case EasingType::kCubic: return Power::EaseOut(t, 3);
  case EasingType::kQuartic: return Power::EaseOut(t, 4);
  case EasingType::kQuintic: return Power::EaseOut(t, 5);
  case EasingType::kBounce: return Bounce::EaseOut(t);
  case EasingType::kElastic: return Elastic::EaseOut(t);
  default: return Power::EaseOut(t, 2);
  }
}

float Easing::EaseInOut(float t, EasingType easeInType, EasingType easeOutType)
{
  return t < 0.5 ? EaseInOut(t, easeInType) : EaseInOut(t, easeOutType);
}

float Easing::EaseInOut(float t, EasingType type)
{
  switch (type)
  {
  case EasingType::kStep: return t < 0.5f ? 0.0f : 1.0f;
  case EasingType::kLinear: return (float)t;
  case EasingType::kSine: return Sine::EaseInOut(t);
  case EasingType::kQuadratic: return Power::EaseInOut(t, 2);
  case EasingType::kCubic: return Power::EaseInOut(t, 3);
  case EasingType::kQuartic: return Power::EaseInOut(t, 4);
  case EasingType::kQuintic: return Power::EaseInOut(t, 5);
  case EasingType::kBounce: return Bounce::EaseInOut(t);
  case EasingType::kElastic: return Elastic::EaseInOut(t);
  default: return Power::EaseInOut(t, 2);
  }
}

