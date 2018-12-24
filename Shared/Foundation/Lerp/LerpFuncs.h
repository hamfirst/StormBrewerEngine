#pragma once

#include <cmath>

#include "Foundation/BasicTypes/BasicTypeFuncs.h"
#include "Foundation/Math/Math.h"

enum class EasingType
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

enum class EasingCurve
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

inline float EaseInStep(float t){ return Easing::EaseIn(t, EasingType::kStep); };
inline float EaseOutStep(float t){ return Easing::EaseOut(t, EasingType::kStep); };
inline float EaseInOutStep(float t){ return Easing::EaseInOut(t, EasingType::kCubic); };

inline float EaseInLinear(float t){ return Easing::EaseIn(t, EasingType::kLinear); };
inline float EaseOutLinear(float t){ return Easing::EaseOut(t, EasingType::kLinear); };
inline float EaseInOutLinear(float t){ return Easing::EaseInOut(t, EasingType::kLinear); };

inline float EaseInSine(float t){ return Easing::EaseIn(t, EasingType::kSine); };
inline float EaseOutSine(float t){ return Easing::EaseOut(t, EasingType::kSine); };
inline float EaseInOutSine(float t){ return Easing::EaseInOut(t, EasingType::kSine); };

inline float EaseInQuadratic(float t){ return Easing::EaseIn(t, EasingType::kQuadratic); };
inline float EaseOutQuadratic(float t){ return Easing::EaseOut(t, EasingType::kQuadratic); };
inline float EaseInOutQuadratic(float t){ return Easing::EaseInOut(t, EasingType::kCubic); };

inline float EaseInCubic(float t){ return Easing::EaseIn(t, EasingType::kCubic); };
inline float EaseOutCubic(float t){ return Easing::EaseOut(t, EasingType::kCubic); };
inline float EaseInOutCubic(float t){ return Easing::EaseInOut(t, EasingType::kCubic); };

inline float EaseInQuartic(float t){ return Easing::EaseIn(t, EasingType::kQuartic); };
inline float EaseOutQuartic(float t){ return Easing::EaseOut(t, EasingType::kQuartic); };
inline float EaseInOutQuartic(float t){ return Easing::EaseInOut(t, EasingType::kQuartic); };

inline float EaseInQuintic(float t){ return Easing::EaseIn(t, EasingType::kQuintic); };
inline float EaseOutQuintic(float t){ return Easing::EaseOut(t, EasingType::kQuintic); };
inline float EaseInOutQuintic(float t){ return Easing::EaseInOut(t, EasingType::kQuintic); };

inline float EaseInBounce(float t){ return Easing::EaseIn(t, EasingType::kBounce); };
inline float EaseOutBounce(float t){ return Easing::EaseOut(t, EasingType::kBounce); };
inline float EaseInOutBounce(float t){ return Easing::EaseInOut(t, EasingType::kBounce); };

inline float EaseInElastic(float t){ return Easing::EaseIn(t, EasingType::kElastic); };
inline float EaseOutElastic(float t){ return Easing::EaseOut(t, EasingType::kElastic); };
inline float EaseInOutElastic(float t){ return Easing::EaseInOut(t, EasingType::kElastic); };


