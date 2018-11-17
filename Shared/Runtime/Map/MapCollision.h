#pragma once

#include "Runtime/RuntimeCommon.h"
#include "Runtime/Map/MapDef.refl.h"

std::vector<std::vector<Box>> ExtractMapCollision(const MapDef & map_def, const Vector2 & offset, const std::vector<uint32_t> & collision_type_hashes = { COMPILE_TIME_CRC32_STR("Collision") });
