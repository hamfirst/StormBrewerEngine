
#include "GameClient/GameClientCommon.h"
#include "GameClient/GameCamera.h"
#include "GameClient/GameContainer.h"

#include "Engine/EngineCommon.h"

GameCamera::GameCamera(GameContainer & container) :
  Camera(Vector2(kDefaultResolutionWidth, kDefaultResolutionHeight), Vector2(1, 1), Vector2f(0, 0)),
  m_GameContainer(container)
{

}

void GameCamera::Update()
{
  RenderVec2 shake = {};

  auto cur_time = (float)GetTimeSeconds();

  auto itr = std::remove_if(m_ShakeInfo.begin(), m_ShakeInfo.end(), [&](const CameraShakeInfo & shake_info) { return cur_time >= shake_info.m_StartTime + shake_info.m_Duration; });
  m_ShakeInfo.erase(itr, m_ShakeInfo.end());

  for (auto & elem : m_ShakeInfo)
  {
    auto t = cur_time - elem.m_StartTime;
    shake += EvalShake(elem, t);
  }

  SetPosition(Vector2(0, 0) + shake);
}

void GameCamera::TransformWorldSpaceToGameplaySpace(int & x, int & y)
{

}

Vector2 GameCamera::TransformWorldSpaceToGameplaySpace(const Vector2 & vec)
{
  return vec;
}

Box GameCamera::TransformWorldSpaceToGameplaySpace(const Box & box)
{
  return box;
}


void GameCamera::Shake(float duration, float amplitude, float frequency)
{
  CameraShakeInfo shake_info;
  shake_info.m_StartTime = (float)GetTimeSeconds();
  shake_info.m_Duration = duration;
  shake_info.m_Amplitude = amplitude;
  shake_info.m_Frequency = frequency;
  shake_info.m_NumSamples = (int)(duration * frequency + 0.999f);

  shake_info.m_Samples = std::make_unique<float[]>(shake_info.m_NumSamples * 2);
  for (int index = 0; index < shake_info.m_NumSamples * 2; ++index)
  {
    shake_info.m_Samples[index] = GetRandomUnitFloat() * 2.0f - 1.0f;
  }

  m_ShakeInfo.emplace_back(std::move(shake_info));
}

RenderVec2 GameCamera::EvalShake(const CameraShakeInfo & shake_info, float t)
{
  float s = t * shake_info.m_Frequency;
  float k = powf((t - shake_info.m_Duration) / shake_info.m_Duration, 2.0f);

  int s0 = ((int)s) % shake_info.m_NumSamples;
  int s1 = (s0 + 1) % shake_info.m_NumSamples;
  float x = s - floorf(s);

  float xm = shake_info.m_Samples[s1] - shake_info.m_Samples[s0];
  float xb = shake_info.m_Samples[s0];
  float xy = xm * x + xb;

  float ym = shake_info.m_Samples[s1 + shake_info.m_NumSamples] - shake_info.m_Samples[s0 + shake_info.m_NumSamples];
  float yb = shake_info.m_Samples[s0 + shake_info.m_NumSamples];
  float yy = ym * x + yb;

  return RenderVec2{ xy, yy } * (k * shake_info.m_Amplitude);
}



