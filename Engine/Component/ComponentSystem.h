#pragma once

#include "Foundation/CallList/CallList.h"

#include "Engine/Component/Component.h"

class ComponentUpdateBucketList;
class PropertyFieldDatabase;

struct ComponentTypeCreationInfo
{
  uint32_t m_ComponentTypeNameHash;
  uint32_t m_BaseClassTypeNameHash;
  uint32_t m_InitDataTypeNameHash;

  NotNullPtr<const uint32_t *> m_BaseListClassesPtr;
  NotNullPtr<uint32_t> m_NumBaseClassesPtr;

  void * (*CreateComponentStore)();
  void (*DestroyComponentStore)(void *);

  NotNullPtr<Component>(*CreateComponent)(void *);
  NotNullPtr<Component>(*CreateComponentWithInitData)(void *, void *);
  void(*FreeComponent)(void *, NotNullPtr<Component>);
  NullOptPtr<Component>(*ResolveHandle)(void *, const ComponentHandle &);

  void (*AddToUpdateList)(void *, ComponentUpdateBucketList &);
  void(*VisitAll)(void *, void(*)(NotNullPtr<Component>, void *), void *);
  std::vector<uint32_t> m_BaseClassList;
};

class ENGINE_EXPORT ComponentTypeSystem
{
public:
  ComponentTypeSystem();
  ~ComponentTypeSystem();

  std::size_t RegisterComponentType(const ComponentTypeCreationInfo & comp_info);
  void SetComponentUpdateOrdering(uint32_t pre_type_name_hash, uint32_t post_type_name_hash);
  void FinalizeComponentSystem();
  void LoadPropertyDatabase(PropertyFieldDatabase & property_db);

private:
  
  friend class ComponentSystem;

  std::vector<ComponentTypeCreationInfo> m_ComponentInfo;
  std::unordered_map<uint32_t, std::size_t> m_ComponentTypeLookup;
  std::vector<std::pair<uint32_t, uint32_t>> m_UpdateReqs;
  std::vector<std::pair<std::size_t, void(*)(void *, ComponentUpdateBucketList &)>> m_ComponentUpdate;
};

class ENGINE_EXPORT ComponentSystem
{
public:

  ComponentSystem();
  ~ComponentSystem();

  void CreateUpdateBucketList(ComponentUpdateBucketList & bucket_list);
  void FinalizeComponentDestroys();

protected:

  friend class Component;
  friend class Entity;
  friend class EntitySystem;
  friend class EngineState;

  NullOptPtr<Component> CreateComponent(std::size_t type_index, void * init_data);
  NullOptPtr<Component> CreateComponentFromTypeNameHash(uint32_t type_name_hash, void * init_data);

  void VisitComponents(uint32_t type_name_hash, void(*callback)(NotNullPtr<Component>, void *), void * user_data);

  void AddToDeadComponentList(NotNullPtr<Component> comp);

private:

  std::vector<void *> m_ComponentStores;
  std::vector<NotNullPtr<Component>> m_DeadComponents;
};

extern ENGINE_EXPORT ComponentTypeSystem g_ComponentTypeSystem;
extern ENGINE_EXPORT PreMainCallList g_ComponentRegisterCallList;
extern ENGINE_EXPORT PreMainCallList g_ComponentUpdateDepRegisterCallList;
