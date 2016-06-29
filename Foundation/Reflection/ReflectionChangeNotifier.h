#pragma once

#include "Foundation\Common.h"
#include "Foundation\Reflection\Reflection.h"

#ifdef REFLECTION_CHANGE_NOTIFIER

struct DocumentModification;

void EnableChangeNotification();
void DisableChangeNotification();

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
void ReflectionNotifySet(ReflectionParentInfo & parent_info, czstr value);
void ReflectionNotifySet(ReflectionParentInfo & parent_info, void * value, Hash type_name_hash);

void ReflectionNotifyClearArray(ReflectionParentInfo & parent_info);
void ReflectionNotifyClearObject(ReflectionParentInfo & parent_info);

void ReflectionNotifyAppendArray(ReflectionParentInfo & parent_info, const std::string & data);
void ReflectionNotifyCompress(ReflectionParentInfo & parent_info);

void ReflectionNotifyInsertArray(ReflectionParentInfo & parent_info, std::size_t index, const std::string & data);
void ReflectionNotifyInsertObject(ReflectionParentInfo & parent_info, std::size_t index, const std::string & data);

void ReflectionNotifyRemoveArray(ReflectionParentInfo & parent_info, std::size_t index);
void ReflectionNotifyRemoveObject(ReflectionParentInfo & parent_info, std::size_t index);

#endif