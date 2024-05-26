
#pragma once

#include "Runtime/RuntimeCommon.h"

class ServerObject;
class ServerObjectManager;
class ServerObjectInitData;
class ServerObjectUpdateList;
class ServerObjectNetBitWriter;
class ServerObjectNetBitReader;

class GameWorld;

struct ServerObjectComponentInfo
{
  uint32_t m_TypeNameHash;
  std::size_t m_TypeIdHash;

  void * (*m_Get)(void *);
  const void * (*m_ConstGet)(const void *);
  void * (*m_Cast)(std::size_t, void *);
  const void * (*m_ConstCast)(std::size_t, const void *);
};

struct ServerObjectTypeInfo
{
  uint32_t m_TypeNameHash;
  uint32_t m_TypeIndex;
  uint32_t m_InitDataTypeNameHash;
  NotNullPtr<std::size_t> m_TypeIndexPtr;

  std::vector<ServerObjectComponentInfo> m_ComponentInfo;

  NotNullPtr<ServerObject>(*m_ObjectCreate)();
  NotNullPtr<ServerObject>(*m_ObjectDuplicate)(NotNullPtr<const ServerObject> rhs);

  void(*m_ObjectInit)(NotNullPtr<ServerObject> object, NullOptPtr<const ServerObjectInitData> init_data,
                      GameWorld & world);
  void(*m_ObjectCopy)(NotNullPtr<ServerObject> object, NotNullPtr<const ServerObject> rhs);
  void(*m_ObjectResetHandles)(NotNullPtr<ServerObject> object, const ServerObjectManager & obj_manager);
  void(*m_ObjectDestroy)(NotNullPtr<ServerObject> object);
  void(*m_AddToUpdateList)(NotNullPtr<ServerObject> object, ServerObjectUpdateList & l);

  void(*m_ObjectSerialize)(NotNullPtr<ServerObject> object, ServerObjectNetBitWriter & writer);
  void(*m_ObjectDeserialize)(NotNullPtr<ServerObject> object, ServerObjectNetBitReader & reader);
  void(*m_ComponentSerialize)(NotNullPtr<ServerObject> object, ServerObjectNetBitWriter & writer);
  void(*m_ComponentDeserialize)(NotNullPtr<ServerObject> object, ServerObjectNetBitReader & reader);

  std::string m_DefaultEntityFile;
};


