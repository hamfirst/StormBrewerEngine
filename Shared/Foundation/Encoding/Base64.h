#pragma once

#include "Foundation/Buffer/Buffer.h"

#include <string>
#include <string_view>

std::string Base64Encode(const void * data, std::size_t length);
std::string Base64Encode(const std::string_view & str);
std::vector<uint8_t> Base64Decode(const std::string_view & data);
