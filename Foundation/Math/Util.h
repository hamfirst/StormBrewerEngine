#pragma once

#include "Foundation/Common.h"

float VecMagnitude(Vector2 v);

int AccelToward(int cur_val, int target_val, int accel, int drag);
float AccelToward(float cur_val, float target_val, float accel, float drag);

Vector2 AccelToward(const Vector2 & cur_val, const Vector2 & target_val, int accel, int drag);

int ManhattanLength(const Vector2 & v);
int ManhattanDist(const Vector2 & a, const Vector2 & b);
