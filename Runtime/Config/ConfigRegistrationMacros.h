#pragma once

#include "Runtime/Config/ConfigManager.h"
#include "Foundation/PropertyMeta/PropertyFieldMetaFuncs.h"

#include "StormRefl/StormReflJson.h"

#include "StormData/StormData.h"
#include "StormData/StormDataSync.h"
#include "StormData/StormDataParent.h"
#include "StormData/StormDataChangePacket.h"


template <typename ConfigType>
void ConfigTypeManager::RegisterConfig(czstr config_type, czstr config_extension, czstr default_dir)
{
  ConfigRegistrationInfo reg_info;
  reg_info.RegisterPropertyMeta = [](PropertyFieldDatabase & property_db) { return GetProperyMetaData<ConfigType>(property_db); };
  reg_info.CreateConfigData = []() { return Any(ConfigType{}); };
  reg_info.InitializeParentInfo = [](void * ptr) { InitializeParentInfo(*((ConfigType *)ptr)); };
  reg_info.SetNotifyCallback = [](void * ptr, StormDataNotifyCallback callback, void * user_ptr) { SetNotifyCallback(*((ConfigType *)ptr), callback, user_ptr); };
  reg_info.ClearNotifyCallback = [](void * ptr) { ClearNotifyCallback(*((ConfigType *)ptr)); };
  reg_info.ApplyChangePacket = [](void * ptr, const ReflectionChangeNotification & change) { StormDataApplyChangePacket(*((ConfigType *)ptr), change); };
  reg_info.ParseJson = [](void * ptr, czstr data) { StormReflParseJson(*((ConfigType *)ptr), data); };
  reg_info.Sync = [](const void * src, void * dst, czstr path) { StormDataSync(*((const ConfigType *)src), *((ConfigType *)dst), path); };
  reg_info.m_ConfigType = config_type;
  reg_info.m_ConfigExtension = config_extension;
  reg_info.m_ConfigExtensionHash = crc32(config_extension);
  reg_info.m_DefaultDirectory = default_dir;
  reg_info.m_Props = nullptr;

  m_ConfigRegInfo.emplace_back(std::move(reg_info));
}

#define REGISTER_CONFIG_TYPE(ConfigType, ConfigName, ConfigExtension, DefaultDir) \
  ADD_PREMAIN_CALL(g_ConfigRegistrationCallList, ConfigType, [](){ g_ConfigTypeManager.RegisterConfig<ConfigType>(ConfigName, ConfigExtension, DefaultDir); })
