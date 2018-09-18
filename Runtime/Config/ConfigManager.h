#pragma once

#include "Foundation/Common.h"
#include "Foundation/Any/Any.h"
#include "Foundation/CallList/CallList.h"

struct PropertyField;
class PropertyFieldDatabase;

struct ConfigRegistrationInfo
{
  NotNullPtr<PropertyField>(*RegisterPropertyMeta)(PropertyFieldDatabase & property_db);
  Any(*CreateConfigData)();

  void(*InitializeParentInfo)(void * ptr);
  void(*SetNotifyCallback)(void * ptr, StormDataNotifyCallback callback, void * user_ptr);
  void(*ClearNotifyCallback)(void * ptr);
  void(*ApplyChangePacket)(void * ptr, const ReflectionChangeNotification & change);
  void(*ParseJson)(void * ptr, czstr data);
  void(*Sync)(const void * src, void * dst, czstr path);

  std::string m_ConfigType;
  std::string m_ConfigExtension;
  uint32_t m_ConfigExtensionHash;

  std::string m_DefaultDirectory;

  NullOptPtr<PropertyField> m_Props;
};

class ConfigTypeManager
{
public:
  template <typename ConfigType>
  void RegisterConfig(czstr config_type, czstr config_extension, czstr default_dir);

  void RegisterConfigProperties(PropertyFieldDatabase & property_db);

  NullOptPtr<ConfigRegistrationInfo> GetConfigRegistrationInfoByExtension(czstr extension);
  NullOptPtr<ConfigRegistrationInfo> GetConfigRegistrationInfoByExtensionHash(uint32_t extension_hash);

  template <typename Visitor>
  void VisistTypes(Visitor && visitor)
  {
    for (auto & elem : m_ConfigRegInfo)
    {
      visitor(elem);
    }
  }

  ConfigRegistrationInfo & GetTypeForIndex(std::size_t index);

private:

  std::vector<ConfigRegistrationInfo> m_ConfigRegInfo;
};

extern ConfigTypeManager g_ConfigTypeManager;
extern PreMainCallList g_ConfigRegistrationCallList;
