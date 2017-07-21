
#include "Runtime/RuntimeCommon.h"
#include "Runtime/Config/ConfigManager.h"

ConfigTypeManager g_ConfigTypeManager;
PreMainCallList g_ConfigRegistrationCallList;

void ConfigTypeManager::RegisterConfigProperties(PropertyFieldDatabase & property_db)
{
  for (auto & elem : m_ConfigRegInfo)
  {
    elem.m_Props = elem.RegisterPropertyMeta(property_db);
  }
}

NullOptPtr<ConfigRegistrationInfo> ConfigTypeManager::GetConfigRegistrationInfoByExtension(czstr extension)
{
  auto ext_hash = crc32(extension);
  for (auto & elem : m_ConfigRegInfo)
  {
    if (elem.m_ConfigExtensionHash == ext_hash)
    {
      return &elem;
    }
  }

  return nullptr;
}

NullOptPtr<ConfigRegistrationInfo> ConfigTypeManager::GetConfigRegistrationInfoByExtensionHash(uint32_t extension_hash)
{
  for (auto & elem : m_ConfigRegInfo)
  {
    if (elem.m_ConfigExtensionHash == extension_hash)
    {
      return &elem;
    }
  }

  return nullptr;
}


ConfigRegistrationInfo & ConfigTypeManager::GetTypeForIndex(std::size_t index)
{
  return m_ConfigRegInfo[index];
}
