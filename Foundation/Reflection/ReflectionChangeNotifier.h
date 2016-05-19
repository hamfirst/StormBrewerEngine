#pragma once

#include "Foundation\Common.h"
#include "Foundation\Reflection\Reflection.h"

#ifdef REFLECTION_CHANGE_NOTIFIER

struct DocumentModification;

void BeginChangeNotification(void (*change_notifier)(const DocumentModification & mod));
void EndChangeNotification();

void ReflectionNotifySet(const ReflectionParentInfo & parent_info, bool value);
void ReflectionNotifySet(const ReflectionParentInfo & parent_info, int8_t value);
void ReflectionNotifySet(const ReflectionParentInfo & parent_info, int16_t value);
void ReflectionNotifySet(const ReflectionParentInfo & parent_info, int32_t value);
void ReflectionNotifySet(const ReflectionParentInfo & parent_info, int64_t value);
void ReflectionNotifySet(const ReflectionParentInfo & parent_info, uint8_t value);
void ReflectionNotifySet(const ReflectionParentInfo & parent_info, uint16_t value);
void ReflectionNotifySet(const ReflectionParentInfo & parent_info, uint32_t value);
void ReflectionNotifySet(const ReflectionParentInfo & parent_info, uint64_t value);
void ReflectionNotifySet(const ReflectionParentInfo & parent_info, float value);
void ReflectionNotifySet(const ReflectionParentInfo & parent_info, const char * value);
void ReflectionNotifySet(const ReflectionParentInfo & parent_info, void * value, uint32_t type_name_hash);

void ReflectionNotifyClearArray(const ReflectionParentInfo & parent_info);
void ReflectionNotifyClearObject(const ReflectionParentInfo & parent_info);

void ReflectionNotifyAppendArray(const ReflectionParentInfo & parent_info, const std::string & data);
void ReflectionNotifyCompress(const ReflectionParentInfo & parent_info);

void ReflectionNotifyInsertArray(const ReflectionParentInfo & parent_info, std::size_t index, const std::string & data);
void ReflectionNotifyInsertObject(const ReflectionParentInfo & parent_info, std::size_t index, const std::string & data);

void ReflectionNotifyRemoveArray(const ReflectionParentInfo & parent_info, std::size_t index);
void ReflectionNotifyRemoveObject(const ReflectionParentInfo & parent_info, std::size_t index);

#endif