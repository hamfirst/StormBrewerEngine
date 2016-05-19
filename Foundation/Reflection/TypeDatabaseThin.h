#pragma once

#include "Foundation\Common.h"

Optional<void *> CreateTypeInstance(uint32_t type_name_hash);
bool CompareTypeInstance(void * ptr1, void * ptr2, uint32_t type_name_hash);

#ifdef REFLECTION_CHANGE_NOTIFIER
void SetParentInfo(void * ptr, const uint32_t type_name_hash, const ReflectionParentInfo & info);
#endif

