#pragma once

#include <cstddef>
#include <cstdint>

std::uint32_t StormExprHashString(const char * str);
std::uint32_t StormExprHashString(const char * start, const char * end);
