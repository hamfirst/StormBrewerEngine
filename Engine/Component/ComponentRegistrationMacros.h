#pragma once


#define DECLARE_COMPONENT                                                                                                       \
  static czstr TypeName;                                                                                                        \
  static uint32_t TypeNameHash;                                                                                                 \
  static std::size_t TypeIndex;                                                                                                 \
  static const uint32_t * BaseTypes;                                                                                            \
  static uint32_t NumBaseTypes;                                                                                                 \
                                                                                                                                \
  virtual uint32_t GetTypeNameHash() const override;                                                                            \
  static void RegisterComponent();                                                                                              \
  virtual void FinalizeDestroy() override;                                                                                      \
                                                                                                                                \
  static bool CanCastToType(uint32_t type_name_hash);                                                                           \
  virtual bool CastToInternal(uint32_t type_name_hash) const override;                                                          \
                                                                                                                                \
  virtual ComponentResolver GetResolver() override;                                                                             \

#define DECLARE_BASE_COMPONENT                                                                                                  \
  static czstr TypeName;                                                                                                        \
  static uint32_t TypeNameHash;                                                                                                 \
  static std::size_t TypeIndex;                                                                                                 \
  static const uint32_t * BaseTypes;                                                                                            \
  static uint32_t NumBaseTypes;                                                                                                 \
                                                                                                                                \
  virtual uint32_t GetTypeNameHash() const;                                                                                     \
  static void RegisterComponent();                                                                                              \
  virtual void FinalizeDestroy();                                                                                               \
                                                                                                                                \
  static bool CanCastToType(uint32_t type_name_hash);                                                                           \
  virtual bool CastToInternal(uint32_t type_name_hash) const;                                                                   \
                                                                                                                                \
  virtual ComponentResolver GetResolver();                                                                                      \


#define REGISTER_COMPONENT_CODE(ComponentName, InitData, ConstructDefault, ConstructInit, BaseClassHash, Base)                  \
czstr ComponentName::TypeName = #ComponentName;                                                                                 \
uint32_t ComponentName::TypeNameHash = COMPILE_TIME_CRC32_STR(#ComponentName);                                                  \
std::size_t ComponentName::TypeIndex = 0;                                                                                       \
const uint32_t * ComponentName::BaseTypes = nullptr;                                                                            \
uint32_t ComponentName::NumBaseTypes = 0;                                                                                       \
                                                                                                                                \
uint32_t ComponentName::GetTypeNameHash() const                                                                                 \
{                                                                                                                               \
  return ComponentName::TypeNameHash;                                                                                           \
}                                                                                                                               \
                                                                                                                                \
void ComponentName::RegisterComponent()                                                                                         \
{                                                                                                                               \
  ComponentTypeCreationInfo type_info;                                                                                          \
  type_info.m_ComponentTypeNameHash = ComponentName::TypeNameHash;                                                              \
  type_info.m_BaseClassTypeNameHash = BaseClassHash;                                                                            \
  type_info.m_InitDataTypeNameHash = COMPILE_TIME_CRC32_STR(#InitData);                                                         \
  type_info.m_BaseListClassesPtr = &ComponentName::BaseTypes;                                                                   \
  type_info.m_NumBaseClassesPtr = &ComponentName::NumBaseTypes;                                                                 \
                                                                                                                                \
  type_info.CreateComponentStore = []() -> void *                                                                               \
  {                                                                                                                             \
    return new ComponentList<ComponentName>;                                                                                    \
  };                                                                                                                            \
                                                                                                                                \
  type_info.DestroyComponentStore = [](void * comp_store)                                                                       \
  {                                                                                                                             \
    auto store = static_cast<ComponentList<ComponentName> *>(comp_store);                                                       \
    delete store;                                                                                                               \
  };                                                                                                                            \
                                                                                                                                \
  type_info.CreateComponent = [](void * comp_store) -> Component *                                                              \
  {                                                                                                                             \
    auto store = static_cast<ComponentList<ComponentName> *>(comp_store);                                                       \
    ConstructDefault;                                                                                                           \
    comp->InitComponentStore(store);                                                                                            \
    return comp;                                                                                                                \
  };                                                                                                                            \
                                                                                                                                \
  type_info.CreateComponentWithInitData = [](void * comp_store, void * init_data) -> Component *                                \
  {                                                                                                                             \
    auto store = static_cast<ComponentList<ComponentName> *>(comp_store);                                                       \
    ConstructInit;                                                                                                              \
    comp->InitComponentStore(store);                                                                                            \
    return comp;                                                                                                                \
  };                                                                                                                            \
                                                                                                                                \
  type_info.FreeComponent = [](void * comp_store, NotNullPtr<Component> comp)                                                   \
  {                                                                                                                             \
    auto store = static_cast<ComponentList<ComponentName> *>(comp_store);                                                       \
    store->FreeComponent((ComponentName *)comp);                                                                                \
  };                                                                                                                            \
                                                                                                                                \
  type_info.ResolveHandle = [](void * comp_store, const ComponentHandle & handle)                                               \
  {                                                                                                                             \
    auto store = static_cast<ComponentList<ComponentName> *>(comp_store);                                                       \
    return store->ResolveHandle(handle);                                                                                        \
  };                                                                                                                            \
                                                                                                                                \
  type_info.AddToUpdateList = [](void * comp_store, ComponentUpdateBucketList & l)                                              \
  {                                                                                                                             \
    auto store = static_cast<ComponentList<ComponentName> *>(comp_store);                                                       \
    auto visitor = [&](auto & comp)                                                                                             \
    {                                                                                                                           \
      ComponentRegisterUpdate(comp, l);                                                                                         \
    };                                                                                                                          \
                                                                                                                                \
    store->VisitAll(visitor);                                                                                                   \
  };                                                                                                                            \
                                                                                                                                \
  type_info.VisitAll = [](void * comp_store, void(*f)(NotNullPtr<Component>, void *), void * user_data)                         \
  {                                                                                                                             \
    auto store = static_cast<ComponentList<ComponentName> *>(comp_store);                                                       \
    auto visitor = [&](auto & comp)                                                                                             \
    {                                                                                                                           \
      f(&comp, user_data);                                                                                                      \
    };                                                                                                                          \
                                                                                                                                \
    store->VisitAll(visitor);                                                                                                   \
  };                                                                                                                            \
                                                                                                                                \
  ComponentName::TypeIndex =                                                                                                    \
    g_ComponentTypeSystem.RegisterComponentType(type_info);                                                                     \
                                                                                                                                \
  ComponentInitDataTypeDatabase::RegisterType<ComponentName, InitData Base>();                                                  \
}                                                                                                                               \
                                                                                                                                \
ADD_PREMAIN_CALL(g_ComponentRegisterCallList, ComponentName, []() { ComponentName::RegisterComponent(); });                     \
                                                                                                                                \
void ComponentName::FinalizeDestroy()                                                                                           \
{                                                                                                                               \
  auto store = static_cast<ComponentList<ComponentName> *>(GetComponentSore());                                                 \
  store->FreeComponent(this);                                                                                                   \
}                                                                                                                               \
                                                                                                                                \
bool ComponentName::CanCastToType(uint32_t type_name_hash)                                                                      \
{                                                                                                                               \
  for (uint32_t base_type = 0; base_type < ComponentName::NumBaseTypes; ++base_type)                                            \
  {                                                                                                                             \
    if (ComponentName::BaseTypes[base_type] == type_name_hash)                                                                  \
    {                                                                                                                           \
      return true;                                                                                                              \
    }                                                                                                                           \
  }                                                                                                                             \
                                                                                                                                \
  return false;                                                                                                                 \
}                                                                                                                               \
                                                                                                                                \
bool ComponentName::CastToInternal(uint32_t type_name_hash) const                                                               \
{                                                                                                                               \
  return ComponentName::CanCastToType(type_name_hash);                                                                          \
}                                                                                                                               \
                                                                                                                                \
ComponentResolver ComponentName::GetResolver()                                                                                  \
{                                                                                                                               \
  return [](const ComponentHandle & handle, void * comp_store)                                                                  \
  {                                                                                                                             \
    auto store = static_cast<ComponentList<ComponentName> *>(comp_store);                                                       \
    return store->ResolveHandle(handle);                                                                                        \
  };                                                                                                                            \
}                                                                                                                               \

#define COMPONENT_CONSTRUCT_NOBASE
#define COMPONNET_CONSTRUCT_BASE(BaseClass) , BaseClass

#define COMPONENT_CONSTRUCT_NOINIT_DEFAULT auto comp = store->AllocateComponent();
#define COMPONENT_CONSTRUCT_NOINIT_DATA    auto comp = store->AllocateComponent();

#define COMPONENT_CONSTRUCT_INIT_DEFAULT(InitData) InitData init_data = {}; auto comp = store->AllocateComponent(init_data);
#define COMPONENT_CONSTRUCT_INIT_DATA(InitData)    auto comp = store->AllocateComponent(*((InitData *)init_data));

#define REGISTER_BASE_COMPONENT(ComponentName) \
  REGISTER_COMPONENT_CODE(ComponentName, ComponentInitData, COMPONENT_CONSTRUCT_NOINIT_DEFAULT, COMPONENT_CONSTRUCT_NOINIT_DATA, 0, COMPONENT_CONSTRUCT_NOBASE)

#define REGISTER_COMPONENT(ComponentName, BaseClass) \
  REGISTER_COMPONENT_CODE(ComponentName, ComponentInitData, COMPONENT_CONSTRUCT_NOINIT_DEFAULT, COMPONENT_CONSTRUCT_NOINIT_DATA, BaseClass::TypeNameHash, COMPONNET_CONSTRUCT_BASE(BaseClass))

#define REGISTER_COMPONENT_WITH_INIT_DATA(ComponentName, InitData, BaseClass) \
  REGISTER_COMPONENT_CODE(ComponentName, InitData, COMPONENT_CONSTRUCT_INIT_DEFAULT(InitData), COMPONENT_CONSTRUCT_INIT_DATA(InitData), BaseClass::TypeNameHash, COMPONNET_CONSTRUCT_BASE(BaseClass))
