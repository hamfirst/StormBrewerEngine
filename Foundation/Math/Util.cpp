
#include "Foundation/Common.h"
#include "Foundation/Math/Util.h"


float VecMagnitude(Vector2 v)
{
  return (float)sqrt(v.x * v.x + v.y * v.y);
}

int AccelToward(int cur_val, int target_val, int accel, int drag)
{
  int accel_dir = target_val > cur_val ? 1 : -1;

  int offset = target_val * cur_val < 0 ? target_val - cur_val : abs(target_val) - abs(cur_val);

  int accel_val = offset < 0 ? drag : accel;
  accel_val = std::min(abs(offset), accel_val);

  return cur_val += accel_val * accel_dir;
}

float AccelToward(float cur_val, float target_val, float accel, float drag)
{
  float accel_dir = target_val > cur_val ? 1.0f : -1.0f;

  float offset = target_val * cur_val < 0 ? target_val - cur_val : fabs(target_val) - fabs(cur_val);

  float accel_val = offset < 0 ? drag : accel;
  accel_val = std::min(fabs(offset), accel_val);

  return cur_val += accel_val * accel_dir;
}

Vector2 AccelToward(const Vector2 & cur_val, const Vector2 & target_val, int accel, int drag)
{
  auto result = Vector2(AccelToward(cur_val.x, target_val.x, accel, drag),
                        AccelToward(cur_val.y, target_val.y, accel, drag));

  float cur_speed = VecMagnitude(cur_val);
  float target_speed = VecMagnitude(target_val);

  float result_speed = VecMagnitude(result);
  float diff_speed = VecMagnitude(cur_val - result);
  
  if (target_speed > cur_speed)
  {
    if (diff_speed > accel)
    {
      Vector2f offset = result - cur_val;
      offset *= (accel / diff_speed);

      return cur_val + Vector2(offset);
    }
  }
  else
  {
    if (diff_speed > drag)
    {
      Vector2f offset = result - cur_val;
      offset *= (drag / diff_speed);

      return cur_val + Vector2(offset);
    }
  }

  return result;
}

int ManhattanLength(const Vector2 & v)
{
  return abs(v.x) + abs(v.y);
}

int ManhattanDist(const Vector2 & a, const Vector2 & b)
{
  return abs(a.x - b.x) + abs(a.y - b.y);
}
