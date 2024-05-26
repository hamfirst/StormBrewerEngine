#pragma once

#include "Foundation/CallList/CallList.h"

#include "Runtime/RuntimeCommon.h"
#include "Runtime/ServerObject/ServerObjectTypeInfo.h"

class ServerObjectSystem
{
public:

  void RegisterType(const ServerObjectTypeInfo & type_info);
  void FinalizeTypes();

  Optional<std::size_t> GetTypeIndexForInitDataTypeNameHash(uint32_t init_data_type_name_hash);
  czstr GetEntityBindingForInitDataTypeNameHash(uint32_t init_data_type_name_hash);

  const ServerObjectTypeInfo & GetTypeInfo(int type_index) const;

private:

  friend class ServerObjectManager;

  NotNullPtr<ServerObject> AllocateObject(std::size_t type_index);
  NotNullPtr<ServerObject> DuplicateObject(NotNullPtr<const ServerObject> rhs);

  void InitObject(NotNullPtr<ServerObject> object, NotNullPtr<const ServerObjectInitData> init_data, GameWorld & world);
  void CopyObject(NotNullPtr<ServerObject> object, NotNullPtr<const ServerObject> rhs);
  void FreeObject(NotNullPtr<ServerObject> object);
  void ResetObjectHandles(NotNullPtr<ServerObject> object, const ServerObjectManager & obj_manager);
  void FinalizeType(ServerObjectTypeInfo & type);
  
private:

  std::vector<ServerObjectTypeInfo> m_ObjectTypes;

  std::vector<std::pair<uint32_t, uint32_t>> m_ObjectDependencies;
  std::vector<int> m_ObjectUpdateIndex;
};

extern ServerObjectSystem g_ServerObjectSystem;
extern PreMainCallList g_ServerObjectRegisterCallList;