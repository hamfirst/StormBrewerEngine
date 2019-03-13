#pragma once

#include <string>
#include <string_view>

std::string UrlEncode(const void * data, std::size_t length);
std::string UrlEncode(const std::string_view & data);
std::string UrlDecodeAsString(const std::string_view & data);
