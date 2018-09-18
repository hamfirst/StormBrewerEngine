
#include "Engine/EngineCommon.h"
#include "Engine/Component/ComponentSystem.h"

#include "Runtime/Component/ComponentInitDataTypeDatabase.h"
#include "Runtime/Component/ComponentInitDataTypeDatabaseRegister.h"

#include <sb/vector.h>

ComponentTypeSystem g_ComponentTypeSystem;
PreMainCallList g_ComponentRegisterCallList;
PreMainCallList g_ComponentUpdateDepRegisterCallList;

ComponentTypeSystem::ComponentTypeSystem()
{

}

ComponentTypeSystem::~ComponentTypeSystem()
{

}

std::size_t ComponentTypeSystem::RegisterComponentType(const ComponentTypeCreationInfo & comp_info)
{
  auto type_index = m_ComponentInfo.size();

  m_ComponentInfo.emplace_back(comp_info);
  m_ComponentTypeLookup.emplace(std::make_pair(comp_info.m_ComponentTypeNameHash, type_index));
  return type_index;
}

void ComponentTypeSystem::SetComponentUpdateOrdering(uint32_t pre_type_name_hash, uint32_t post_type_name_hash)
{
  m_UpdateReqs.emplace_back(std::make_pair(pre_type_name_hash, post_type_name_hash));
}

void ComponentTypeSystem::FinalizeComponentSystem()
{
  std::unordered_map<uint32_t, std::vector<uint32_t>> preconditions;
  std::unordered_map<uint32_t, std::vector<uint32_t>> postconditions;
 
  for (auto & elem : m_ComponentTypeLookup)
  {
    preconditions.emplace(elem.first, std::vector<uint32_t>{});
    postconditions.emplace(elem.first, std::vector<uint32_t>{});
  }

  for (auto & elem : m_UpdateReqs)
  {
    auto pre_itr = preconditions.find(elem.first);
    pre_itr->second.emplace_back(elem.second);

    auto post_itr = preconditions.find(elem.first);
    post_itr->second.emplace_back(elem.second);
  }

  if (preconditions.size() > 0)
  {
    std::vector<std::unordered_map<uint32_t, std::vector<uint32_t>>::iterator> dead_iterators;
    while (true)
    {
      for (auto elem_itr = preconditions.begin(), end = preconditions.end(); elem_itr != end; ++elem_itr)
      {
        auto & elem = (*elem_itr);
        if (elem.second.size() == 0)
        {
          dead_iterators.emplace_back(elem_itr);

          auto comp_itr = m_ComponentTypeLookup.find(elem.first);

          auto & type_info = m_ComponentInfo[comp_itr->second];
          m_ComponentUpdate.emplace_back(std::make_pair(comp_itr->second, type_info.AddToUpdateList));

          auto post_itr = postconditions.find(elem.first);
          for (auto post_cond : post_itr->second)
          {
            auto pre_itr = preconditions.find(post_cond);
            vremove_quick(pre_itr->second, elem.first);
          }

          postconditions.erase(post_itr);
        }
      }

      if (dead_iterators.size() == 0)
      {
        ASSERT(false, "Circular dependency in the component update dependency graph");
      }

      for (auto & itr : dead_iterators)
      {
        preconditions.erase(itr);
      }

      if (preconditions.size() == 0)
      {
        break;
      }

      dead_iterators.clear();
    }
  }

  m_UpdateReqs.clear();

  struct BaseClassInfo
  {
    bool m_InList = false;
    ComponentTypeCreationInfo * m_MyInfo;
    BaseClassInfo * m_BaseInfo = nullptr;
  };

  std::unordered_map<uint32_t, BaseClassInfo> base_classes;
  for (auto & elem : m_ComponentInfo)
  {
    BaseClassInfo info;
    info.m_MyInfo = &elem;

    base_classes.emplace(elem.m_ComponentTypeNameHash, info);
  }

  for (auto & elem : base_classes)
  {
    auto itr = base_classes.find(elem.second.m_MyInfo->m_BaseClassTypeNameHash);
    if (itr != base_classes.end())
    {
      elem.second.m_BaseInfo = &itr->second;
    }
  }

  while (true)
  {
    bool added_bases = false;
    for (auto & elem : base_classes)
    {
      if (elem.second.m_InList == false)
      {
        if(elem.second.m_BaseInfo == nullptr)
        {
          auto info = elem.second.m_MyInfo;
          info->m_BaseClassList.emplace_back(elem.first);
          *info->m_BaseListClassesPtr = info->m_BaseClassList.data();
          *info->m_NumBaseClassesPtr = (uint32_t)info->m_BaseClassList.size();

          elem.second.m_InList = true;
          added_bases = true;
        }
        else if (elem.second.m_BaseInfo->m_InList == true)
        {
          auto info = elem.second.m_MyInfo;
          auto base_info = elem.second.m_BaseInfo->m_MyInfo;
          info->m_BaseClassList.emplace_back(elem.first);
          std::copy(base_info->m_BaseClassList.begin(), base_info->m_BaseClassList.end(), std::back_inserter(info->m_BaseClassList));

          *info->m_BaseListClassesPtr = info->m_BaseClassList.data();
          *info->m_NumBaseClassesPtr = (uint32_t)info->m_BaseClassList.size();

          elem.second.m_InList = true;
          added_bases = true;
        }
      }
    }

    if (added_bases == false)
    {
      break;
    }
  }
}

void ComponentTypeSystem::LoadPropertyDatabase(PropertyFieldDatabase & property_db)
{
  auto visitor = [&](uint32_t type_name_hash, const ComponentInitDataTypeInfo & type_info)
  {
    type_info.RegisterPropertyFields(property_db);
  };

  StormDataTypeDatabaseVisitTypes(StormDataTypeDatabaseVistorInfo<ComponentInitData, ComponentInitDataTypeInfo>{}, visitor);
}

ComponentSystem::ComponentSystem()
{
  m_ComponentStores.reserve(g_ComponentTypeSystem.m_ComponentInfo.size());

  for (auto & type : g_ComponentTypeSystem.m_ComponentInfo)
  {
    m_ComponentStores.push_back(type.CreateComponentStore());
  }
}

ComponentSystem::~ComponentSystem()
{
  for(std::size_t index = 0, end = g_ComponentTypeSystem.m_ComponentInfo.size(); index < end; index++)
  {
    auto & type = g_ComponentTypeSystem.m_ComponentInfo[index];
    type.DestroyComponentStore(m_ComponentStores[index]);
  }
}

void ComponentSystem::CreateUpdateBucketList(ComponentUpdateBucketList & bucket_list)
{
  for (auto & elem : g_ComponentTypeSystem.m_ComponentUpdate)
  {
    elem.second(m_ComponentStores[elem.first], bucket_list);
  }
}

void ComponentSystem::FinalizeComponentDestroys()
{
  for (auto & elem : m_DeadComponents)
  {
    elem->FinalizeDestroy();
  }

  m_DeadComponents.clear();
}

NullOptPtr<Component> ComponentSystem::CreateComponent(std::size_t type_index, void * init_data)
{
  NullOptPtr<Component> comp;
  if (init_data)
  {
    comp = g_ComponentTypeSystem.m_ComponentInfo[type_index].CreateComponentWithInitData(m_ComponentStores[type_index], init_data);
  }
  else
  {
    comp = g_ComponentTypeSystem.m_ComponentInfo[type_index].CreateComponent(m_ComponentStores[type_index]);
  }

  if (comp)
  {
    comp->m_ComponentSystem = this;
  }

  return comp;
}

NullOptPtr<Component> ComponentSystem::CreateComponentFromTypeNameHash(uint32_t type_name_hash, void * init_data)
{
  auto itr = g_ComponentTypeSystem.m_ComponentTypeLookup.find(type_name_hash);
  if (itr == g_ComponentTypeSystem.m_ComponentTypeLookup.end())
  {
    return nullptr;
  }

  return CreateComponent(itr->second, init_data);
}

void ComponentSystem::VisitComponents(uint32_t type_name_hash, void(*callback)(NotNullPtr<Component>, void *), void * user_data)
{
  auto itr = g_ComponentTypeSystem.m_ComponentTypeLookup.find(type_name_hash);
  if (itr == g_ComponentTypeSystem.m_ComponentTypeLookup.end())
  {
    return;
  }

  g_ComponentTypeSystem.m_ComponentInfo[itr->second].VisitAll(&m_ComponentStores[itr->second], callback, user_data);
}

void ComponentSystem::AddToDeadComponentList(NotNullPtr<Component> comp)
{
  m_DeadComponents.push_back(comp);
}
