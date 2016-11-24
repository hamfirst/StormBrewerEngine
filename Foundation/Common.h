#pragma once

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

#include <new>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

#include <cstdint>

#include <gsl/gsl.h>

#include <hash/Hash.h>
#include <hash/Hash64.h>


#include <glm/glm.hpp>

using zstr = gsl::zstring<>;
using czstr = gsl::czstring<>;
using zwstr = gsl::wzstring<>;
using czwstr = gsl::cwzstring<>;

using RenderVec2 = glm::vec2;
using RenderVec3 = glm::vec3;
using RenderVec4 = glm::vec4;
using RenderMat3 = glm::mat3x4;
using RenderMat4 = glm::mat4x4;

#include "Foundation/Optional/Optional.h"
#include "Foundation/Singleton/Singleton.h"
#include "Foundation/Assert/Assert.h"

