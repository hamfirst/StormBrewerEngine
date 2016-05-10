#pragma once

#include "Foundation\Common.h"
#include "Foundation\Reflection\Reflection.h"

#ifdef REFLECTION_PARENT

void ReflectionNotifySet(ReflectionParentInfo & parent_info, bool value);
void ReflectionNotifySet(ReflectionParentInfo & parent_info, int8_t value);
void ReflectionNotifySet(ReflectionParentInfo & parent_info, int16_t value);
void ReflectionNotifySet(ReflectionParentInfo & parent_info, int32_t value);
void ReflectionNotifySet(ReflectionParentInfo & parent_info, int64_t value);
void ReflectionNotifySet(ReflectionParentInfo & parent_info, uint8_t value);
void ReflectionNotifySet(ReflectionParentInfo & parent_info, uint16_t value);
void ReflectionNotifySet(ReflectionParentInfo & parent_info, uint32_t value);
void ReflectionNotifySet(ReflectionParentInfo & parent_info, uint64_t value);
void ReflectionNotifySet(ReflectionParentInfo & parent_info, float value);
void ReflectionNotifySet(ReflectionParentInfo & parent_info, const char * value);
void ReflectionNotifySet(ReflectionParentInfo & parent_info, void * value, uint32_t type_name_hash);


#endif