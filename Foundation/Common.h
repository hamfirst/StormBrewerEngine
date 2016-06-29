#pragma once

#include <new>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

#include <cstdint>

#include <gsl\gsl.h>

#include <enum\enum.h>
#include <optional\optional.hpp>

#include <glm\glm.hpp>

using zstr = gsl::zstring<>;
using czstr = gsl::czstring<>;
using zwstr = gsl::wzstring<>;
using czwstr = gsl::cwzstring<>;

template <class T>
using Optional = std::experimental::optional<T>;

using RenderVec2 = glm::vec2;
using RenderVec3 = glm::vec3;
using RenderVec4 = glm::vec4;
using RenderMat3 = glm::mat3x4;
using RenderMat4 = glm::mat4x4;

#include "Foundation\Singleton\Singleton.h"
#include "Foundation\Hash\Hash.h"
#include "Foundation\Reflection\ReflectionCommon.h"

