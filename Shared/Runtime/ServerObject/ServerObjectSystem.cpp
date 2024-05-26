
#include "Runtime/RuntimeCommon.h"
#include "Runtime/ServerObject/ServerObjectSystem.h"
#include "Runtime/ServerObject/ServerObject.h"

#include <sb/vector.h>

ServerObjectSystem g_ServerObjectSystem;
PreMainCallList g_ServerObjectRegisterCallList;

NotNullPtr<ServerObject> ServerObjectSystem::AllocateObject(std::size_t type_index)
{
  auto object = m_ObjectTypes[type_index].m_ObjectCreate();
  object->m_TypeIndex = (int)type_index;

  return object;
}

NotNullPtr<ServerObject> ServerObjectSystem::DuplicateObject(NotNullPtr<const ServerObject> rhs)
{
  auto type_index = rhs->m_TypeIndex;
  auto object = m_ObjectTypes[type_index].m_ObjectDuplicate(rhs);
  object->m_TypeIndex = type_index;
  object->m_EventDispatch = rhs->m_EventDispatch;
  object->m_FramesAlive = rhs->m_FramesAlive;
  return object;
}

void ServerObjectSystem::InitObject(NotNullPtr<ServerObject> object, NotNullPtr<const ServerObjectInitData> init_data, GameWorld & world)
{
  m_ObjectTypes[object->m_TypeIndex].m_ObjectInit(object, init_data, world);
}

void ServerObjectSystem::CopyObject(NotNullPtr<ServerObject> object, NotNullPtr<const ServerObject> rhs)
{
  ASSERT(object->m_TypeIndex == rhs->m_TypeIndex, "Cannot copy objects of differing types");

  auto type_index = rhs->m_TypeIndex;
  m_ObjectTypes[type_index].m_ObjectCopy(object, rhs);
  object->m_EventDispatch = rhs->m_EventDispatch;
  object->m_FramesAlive = rhs->m_FramesAlive;
}

void ServerObjectSystem::FreeObject(NotNullPtr<ServerObject> object)
{
  m_ObjectTypes[object->m_TypeIndex].m_ObjectDestroy(object);
}

void ServerObjectSystem::ResetObjectHandles(NotNullPtr<ServerObject> object, const ServerObjectManager & obj_manager)
{
  m_ObjectTypes[object->m_TypeIndex].m_ObjectResetHandles(object, obj_manager);
}

void ServerObjectSystem::RegisterType(const ServerObjectTypeInfo & type_info)
{
  m_ObjectTypes.emplace_back(type_info);
}

void ServerObjectSystem::FinalizeTypes()
{
  std::sort(m_ObjectTypes.begin(), m_ObjectTypes.end(), 
    [](const ServerObjectTypeInfo & a, const ServerObjectTypeInfo & b) { return a.m_TypeNameHash < b.m_TypeNameHash; });

  for (std::size_t index = 0, end = m_ObjectTypes.size(); index < end; ++index)
  {
    auto & type = m_ObjectTypes[index];
    type.m_TypeIndex = (int)index;
    *type.m_TypeIndexPtr = index;
  }

  for (std::size_t index = 0, end = m_ObjectTypes.size(); index < end; ++index)
  {
    auto & type = m_ObjectTypes[index];
    FinalizeType(type);
  }

  std::vector<uint32_t> processed_types;

  using ItrType = std::unordered_map<uint32_t, std::vector<uint32_t>>::iterator;

  std::unordered_map<uint32_t, std::vector<uint32_t>> dep_list;
  std::unordered_map<uint32_t, std::vector<uint32_t>> rev_list;

  for (auto & type : m_ObjectTypes)
  {
    dep_list.emplace(std::make_pair(type.m_TypeNameHash, std::vector<uint32_t>{}));
    rev_list.emplace(std::make_pair(type.m_TypeNameHash, std::vector<uint32_t>{}));
  }

  for (auto & dep : m_ObjectDependencies)
  {
    auto itr = dep_list.find(dep.first);
    itr->second.push_back(dep.second);

    itr = rev_list.find(dep.second);
    itr->second.push_back(dep.first);
  }

  m_ObjectUpdateIndex.resize(m_ObjectTypes.size());

  int update_index = 0;
  while (true)
  {
    std::vector<std::pair<ItrType, ItrType>> nodep_types;
    for (auto & elem : dep_list)
    {
      if (elem.second.size() == 0)
      {
        nodep_types.emplace_back(std::make_pair(dep_list.find(elem.first), rev_list.find(elem.first)));
      }
    }

    std::vector<std::pair<int, uint32_t>> type_ids;
    for (auto & elem : nodep_types)
    {
      for (auto & type : m_ObjectTypes)
      {
        if (type.m_TypeNameHash == elem.first->first)
        {
          type_ids.push_back(std::make_pair(type.m_TypeIndex, type.m_TypeNameHash));
          break;
        }
      }
    }

    std::sort(type_ids.begin(), type_ids.end(), [](const std::pair<int, uint32_t> & a, const std::pair<int, uint32_t> & b) { return a.second < b.second; });
    for (auto & elem : type_ids)
    {
      m_ObjectUpdateIndex[elem.first] = update_index;
      update_index++;
    }

    for (auto & elem : nodep_types)
    {
      for (auto & rev : elem.second->second)
      {
        auto dep = dep_list.find(rev);
        vremove_quick(dep->second, elem.first->first);
      }

      dep_list.erase(elem.first);
      rev_list.erase(elem.second);
    }

    if (nodep_types.size() == 0)
    {
      break;
    }
  }

  m_ObjectDependencies.clear();
}

void ServerObjectSystem::FinalizeType(ServerObjectTypeInfo & type)
{
  auto object = type.m_ObjectCreate();
  auto entity_file = object->GetDefaultEntityBinding();
  if (entity_file)
  {
    type.m_DefaultEntityFile = entity_file;
  }

  type.m_ObjectDestroy(object);
}

Optional<std::size_t> ServerObjectSystem::GetTypeIndexForInitDataTypeNameHash(uint32_t init_data_type_name_hash)
{
  for (auto & elem : m_ObjectTypes)
  {
    if (elem.m_InitDataTypeNameHash == init_data_type_name_hash)
    {
      return elem.m_TypeIndex;
    }
  }

  return {};
}

czstr ServerObjectSystem::GetEntityBindingForInitDataTypeNameHash(uint32_t init_data_type_name_hash)
{
  for (auto & elem : m_ObjectTypes)
  {
    if (elem.m_InitDataTypeNameHash == init_data_type_name_hash)
    {
      return elem.m_DefaultEntityFile.size() > 0 ? elem.m_DefaultEntityFile.data() : nullptr;
    }
  }

  return nullptr;
}

const ServerObjectTypeInfo & ServerObjectSystem::GetTypeInfo(int type_index) const
{
  return m_ObjectTypes[type_index];
}
