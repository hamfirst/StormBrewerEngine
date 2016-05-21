#pragma once

#include <new>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

#include <cstdint>

#include <enum\enum.h>
#include <optional\optional.hpp>

#include <glm\glm.hpp>

template <class T>
using Optional = nonstd::optional<T>;

using Vec2 = glm::vec2;
using Vec3 = glm::vec3;
using Vec4 = glm::vec4;
using Mat3 = glm::mat3x4;
using Mat4 = glm::mat4x4;

#include "Foundation\Singleton\Singleton.h"
#include "Foundation\Hash\Hash.h"
#include "Foundation\Reflection\ReflectionCommon.h"

