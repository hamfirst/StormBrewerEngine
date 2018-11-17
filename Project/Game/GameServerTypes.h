#pragma once

#include "StormNet/NetReflectionFixedPoint.h"
#include "StormNet/NetReflectionFixedPointLUT.h"
#include "StormNet/NetReflectionNumber.h"

#include "Foundation/Math/Intersection.h"

static const int kMaxPlayers = 2;
static const int kMaxTeams = 4;
static const int kServerUpdateRate = 3;
static const int kMaxScore = 5;

extern template struct NetFixedPointVals<int64_t, 32, 16>;
extern template class NetFixedPointLUT<int64_t, 32, 16>;

using GameNetVal = NetFixedPoint<int64_t, 32, 16>;
using GameNetVec2 = Intersection<GameNetVal>::VecType;
using GameNetVals = NetFixedPointVals<int64_t, 32, 16>;
using GameNetLUT = NetFixedPointLUT<int64_t, 32, 16>;

using GameNetIntersectionResult = IntersectionResult<GameNetVal>;
using GameNetHealthVal = NetRangedNumber<int, 0, 127>;
using GameNetPlayerIndex = NetRangedNumber<int, 0, kMaxTeams>;

void InitServerTypes();