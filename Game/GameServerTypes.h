#pragma once

#include "StormNet/NetReflectionFixedPoint.h"
#include "StormNet/NetReflectionNumber.h"

#include "Foundation/Math/Intersection.h"

#include "Game/GameNetworkData.refl.h"

using GameNetVal = NetFixedPoint<int64_t, 32, 16>;
using GameNetVec2 = Intersection<GameNetVal>::VecType;

using GameNetIntersectionResult = IntersectionResult<GameNetVal>;
using GameNetHealthVal = NetRangedNumber<int, 0, 127>;
using GameNetPlayerIndex = NetRangedNumber<int, 0, kMaxTeams>;

