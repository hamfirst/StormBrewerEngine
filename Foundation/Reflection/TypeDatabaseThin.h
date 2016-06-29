#pragma once

#include "Foundation\Common.h"

Optional<void *> CreateTypeInstance(Hash type_name_hash);
bool CompareTypeInstance(void * ptr1, void * ptr2, Hash type_name_hash);

#ifdef REFLECTION_CHANGE_NOTIFIER
void SetParentInfo(void * ptr, Hash type_name_hash, const ReflectionParentInfo & info);
#endif

