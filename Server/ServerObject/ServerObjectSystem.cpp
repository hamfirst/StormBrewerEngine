
#include "Server/ServerCommon.h"
#include "Server/ServerObject/ServerObjectSystem.h"
#include "Server/ServerObject/ServerObject.h"

#include <sb/vector.h>

ServerObjectSystem g_ServerObjectSystem;
PreMainCallList g_ServerObjectRegisterCallList;

NotNullPtr<ServerObject> ServerObjectSystem::AllocateObject(std::size_t type_index, NullOptPtr<ServerObjectInitData> init_data)
{
  auto object = m_ObjectTypes[type_index].m_ObjectCreate();
  object->m_TypeIndex = type_index;

  m_ObjectTypes[type_index].m_ObjectInit(object, init_data);
  return object;
}

NotNullPtr<ServerObject> ServerObjectSystem::DuplicateObject(NotNullPtr<const ServerObject> rhs)
{
  auto type_index = rhs->m_TypeIndex;
  auto object = m_ObjectTypes[type_index].m_ObjectDuplicate(rhs);
  object->m_TypeIndex = type_index;
  return object;
}

void ServerObjectSystem::CopyObject(NotNullPtr<ServerObject> object, NotNullPtr<const ServerObject> rhs)
{
  ASSERT(object->m_TypeIndex == rhs->m_TypeIndex, "Cannot copy objects of differing types");

  auto type_index = rhs->m_TypeIndex;
  m_ObjectTypes[type_index].m_ObjectCopy(object, rhs);
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
    type.m_TypeIndex = index;
    *type.m_TypeIndexPtr = index;

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
  }

  m_ObjectDependencies.clear();
}

void ServerObjectSystem::FinalizeType(ServerObjectTypeInfo & type)
{
  if (*type.m_BaseListClassesPtr != nullptr)
  {
    return;
  }

  auto base_class = type.m_BaseClassTypeNameHash;
  if (base_class == 0)
  {
    auto base_class_list = static_cast<uint32_t *>(malloc(sizeof(uint32_t)));
    *base_class_list = type.m_TypeIndex;

    *type.m_BaseListClassesPtr = base_class_list;
    *type.m_NumBaseClassesPtr = 1;
    return;
  }

  for (auto & base_type : m_ObjectTypes)
  {
    if (base_type.m_TypeNameHash == base_class)
    {
      FinalizeType(type);

      auto base_class_list = static_cast<uint32_t *>(malloc(sizeof(uint32_t) * (*base_type.m_NumBaseClassesPtr + 1)));
      *base_class_list = type.m_TypeIndex;

      memcpy(base_class_list + 1, *base_type.m_BaseListClassesPtr, sizeof(uint32_t) * (*base_type.m_NumBaseClassesPtr));

      *type.m_BaseListClassesPtr = base_class_list;
      *type.m_NumBaseClassesPtr = *base_type.m_NumBaseClassesPtr + 1;
      return;
    }
  }

  ASSERT(false, "Could not find base class");
}
