#pragma once

#include <hash/Hash.h>

#define DECLARE_EVENT(EventType) static const uint32_t TypeNameHash = COMPILE_TIME_CRC32_STR(#EventType);
