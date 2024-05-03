#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "GameNetworkEvents.refl.h"


template <>
struct StormReflTypeInfo<GlobalNetworkEvent>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GlobalNetworkEvent"; }
  static constexpr auto GetNameHash() { return 0xBD3E127B; }
  static constexpr bool HasDefault() { return true; }
  static GlobalNetworkEvent & GetDefault() { static GlobalNetworkEvent def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GlobalNetworkEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GlobalNetworkEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GlobalNetworkEvent *>(ptr);
    if(typeid(GlobalNetworkEvent).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GlobalNetworkEvent *>(ptr);
    if(typeid(GlobalNetworkEvent).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<CreateEntityGlobalEvent>
{
  using MyBase = GlobalNetworkEvent;
  static constexpr int fields_n = 3 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "CreateEntityGlobalEvent"; }
  static constexpr auto GetNameHash() { return 0x642FDCD2; }
  static constexpr bool HasDefault() { return true; }
  static CreateEntityGlobalEvent & GetDefault() { static CreateEntityGlobalEvent def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<CreateEntityGlobalEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xBD3E127B == type_name_hash) return static_cast<GlobalNetworkEvent *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const CreateEntityGlobalEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xBD3E127B == type_name_hash) return static_cast<const GlobalNetworkEvent *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<CreateEntityGlobalEvent *>(ptr);
    if(typeid(CreateEntityGlobalEvent).hash_code() == type_id_hash) return c;
    if(typeid(GlobalNetworkEvent).hash_code() == type_id_hash) return static_cast<GlobalNetworkEvent *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const CreateEntityGlobalEvent *>(ptr);
    if(typeid(CreateEntityGlobalEvent).hash_code() == type_id_hash) return c;
    if(typeid(GlobalNetworkEvent).hash_code() == type_id_hash) return static_cast<const GlobalNetworkEvent *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<CreateEntityGlobalEvent>::field_data_static<0 + StormReflTypeInfo<GlobalNetworkEvent>::fields_n>
{
  using member_type = uint32_t; // unsigned int
  static constexpr auto GetName() { return "m_AssetHash"; }
  static constexpr auto GetType() { return "unsigned int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8ACB36EB; }
  static constexpr unsigned GetTypeNameHash() { return 0x562EF932; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<GlobalNetworkEvent>::fields_n; }
  static constexpr auto GetMemberPtr() { return &CreateEntityGlobalEvent::m_AssetHash; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<CreateEntityGlobalEvent *>(obj); return &ptr->m_AssetHash; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const CreateEntityGlobalEvent *>(obj); return &ptr->m_AssetHash; }
};

template <typename Self>
struct StormReflTypeInfo<CreateEntityGlobalEvent>::field_data<0 + StormReflTypeInfo<GlobalNetworkEvent>::fields_n, Self> : public StormReflTypeInfo<CreateEntityGlobalEvent>::field_data_static<0 + StormReflTypeInfo<GlobalNetworkEvent>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint32_t> & Get() { return self.m_AssetHash; }
  std::add_const_t<std::remove_reference_t<uint32_t>> & Get() const { return self.m_AssetHash; }
  void SetDefault() { self.m_AssetHash = StormReflTypeInfo<CreateEntityGlobalEvent>::GetDefault().m_AssetHash; }
};

template <>
struct StormReflTypeInfo<CreateEntityGlobalEvent>::field_data_static<1 + StormReflTypeInfo<GlobalNetworkEvent>::fields_n>
{
  using member_type = int16_t; // short
  static constexpr auto GetName() { return "m_PositionX"; }
  static constexpr auto GetType() { return "short"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA6033D27; }
  static constexpr unsigned GetTypeNameHash() { return 0x8F2890A2; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1 + StormReflTypeInfo<GlobalNetworkEvent>::fields_n; }
  static constexpr auto GetMemberPtr() { return &CreateEntityGlobalEvent::m_PositionX; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<CreateEntityGlobalEvent *>(obj); return &ptr->m_PositionX; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const CreateEntityGlobalEvent *>(obj); return &ptr->m_PositionX; }
};

template <typename Self>
struct StormReflTypeInfo<CreateEntityGlobalEvent>::field_data<1 + StormReflTypeInfo<GlobalNetworkEvent>::fields_n, Self> : public StormReflTypeInfo<CreateEntityGlobalEvent>::field_data_static<1 + StormReflTypeInfo<GlobalNetworkEvent>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int16_t> & Get() { return self.m_PositionX; }
  std::add_const_t<std::remove_reference_t<int16_t>> & Get() const { return self.m_PositionX; }
  void SetDefault() { self.m_PositionX = StormReflTypeInfo<CreateEntityGlobalEvent>::GetDefault().m_PositionX; }
};

template <>
struct StormReflTypeInfo<CreateEntityGlobalEvent>::field_data_static<2 + StormReflTypeInfo<GlobalNetworkEvent>::fields_n>
{
  using member_type = int16_t; // short
  static constexpr auto GetName() { return "m_PositionY"; }
  static constexpr auto GetType() { return "short"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD1040DB1; }
  static constexpr unsigned GetTypeNameHash() { return 0x8F2890A2; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2 + StormReflTypeInfo<GlobalNetworkEvent>::fields_n; }
  static constexpr auto GetMemberPtr() { return &CreateEntityGlobalEvent::m_PositionY; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<CreateEntityGlobalEvent *>(obj); return &ptr->m_PositionY; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const CreateEntityGlobalEvent *>(obj); return &ptr->m_PositionY; }
};

template <typename Self>
struct StormReflTypeInfo<CreateEntityGlobalEvent>::field_data<2 + StormReflTypeInfo<GlobalNetworkEvent>::fields_n, Self> : public StormReflTypeInfo<CreateEntityGlobalEvent>::field_data_static<2 + StormReflTypeInfo<GlobalNetworkEvent>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int16_t> & Get() { return self.m_PositionY; }
  std::add_const_t<std::remove_reference_t<int16_t>> & Get() const { return self.m_PositionY; }
  void SetDefault() { self.m_PositionY = StormReflTypeInfo<CreateEntityGlobalEvent>::GetDefault().m_PositionY; }
};

template <>
struct StormReflTypeInfo<CameraShakeEvent>
{
  using MyBase = GlobalNetworkEvent;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "CameraShakeEvent"; }
  static constexpr auto GetNameHash() { return 0x2504BD60; }
  static constexpr bool HasDefault() { return true; }
  static CameraShakeEvent & GetDefault() { static CameraShakeEvent def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<CameraShakeEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xBD3E127B == type_name_hash) return static_cast<GlobalNetworkEvent *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const CameraShakeEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xBD3E127B == type_name_hash) return static_cast<const GlobalNetworkEvent *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<CameraShakeEvent *>(ptr);
    if(typeid(CameraShakeEvent).hash_code() == type_id_hash) return c;
    if(typeid(GlobalNetworkEvent).hash_code() == type_id_hash) return static_cast<GlobalNetworkEvent *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const CameraShakeEvent *>(ptr);
    if(typeid(CameraShakeEvent).hash_code() == type_id_hash) return c;
    if(typeid(GlobalNetworkEvent).hash_code() == type_id_hash) return static_cast<const GlobalNetworkEvent *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<PlaySoundGlobalEvent>
{
  using MyBase = GlobalNetworkEvent;
  static constexpr int fields_n = 3 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "PlaySoundGlobalEvent"; }
  static constexpr auto GetNameHash() { return 0x5199D34C; }
  static constexpr bool HasDefault() { return true; }
  static PlaySoundGlobalEvent & GetDefault() { static PlaySoundGlobalEvent def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<PlaySoundGlobalEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xBD3E127B == type_name_hash) return static_cast<GlobalNetworkEvent *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const PlaySoundGlobalEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xBD3E127B == type_name_hash) return static_cast<const GlobalNetworkEvent *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<PlaySoundGlobalEvent *>(ptr);
    if(typeid(PlaySoundGlobalEvent).hash_code() == type_id_hash) return c;
    if(typeid(GlobalNetworkEvent).hash_code() == type_id_hash) return static_cast<GlobalNetworkEvent *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const PlaySoundGlobalEvent *>(ptr);
    if(typeid(PlaySoundGlobalEvent).hash_code() == type_id_hash) return c;
    if(typeid(GlobalNetworkEvent).hash_code() == type_id_hash) return static_cast<const GlobalNetworkEvent *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<PlaySoundGlobalEvent>::field_data_static<0 + StormReflTypeInfo<GlobalNetworkEvent>::fields_n>
{
  using member_type = uint32_t; // unsigned int
  static constexpr auto GetName() { return "m_AssetHash"; }
  static constexpr auto GetType() { return "unsigned int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8ACB36EB; }
  static constexpr unsigned GetTypeNameHash() { return 0x562EF932; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<GlobalNetworkEvent>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlaySoundGlobalEvent::m_AssetHash; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlaySoundGlobalEvent *>(obj); return &ptr->m_AssetHash; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlaySoundGlobalEvent *>(obj); return &ptr->m_AssetHash; }
};

template <typename Self>
struct StormReflTypeInfo<PlaySoundGlobalEvent>::field_data<0 + StormReflTypeInfo<GlobalNetworkEvent>::fields_n, Self> : public StormReflTypeInfo<PlaySoundGlobalEvent>::field_data_static<0 + StormReflTypeInfo<GlobalNetworkEvent>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint32_t> & Get() { return self.m_AssetHash; }
  std::add_const_t<std::remove_reference_t<uint32_t>> & Get() const { return self.m_AssetHash; }
  void SetDefault() { self.m_AssetHash = StormReflTypeInfo<PlaySoundGlobalEvent>::GetDefault().m_AssetHash; }
};

template <>
struct StormReflTypeInfo<PlaySoundGlobalEvent>::field_data_static<1 + StormReflTypeInfo<GlobalNetworkEvent>::fields_n>
{
  using member_type = int16_t; // short
  static constexpr auto GetName() { return "m_PositionX"; }
  static constexpr auto GetType() { return "short"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA6033D27; }
  static constexpr unsigned GetTypeNameHash() { return 0x8F2890A2; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1 + StormReflTypeInfo<GlobalNetworkEvent>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlaySoundGlobalEvent::m_PositionX; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlaySoundGlobalEvent *>(obj); return &ptr->m_PositionX; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlaySoundGlobalEvent *>(obj); return &ptr->m_PositionX; }
};

template <typename Self>
struct StormReflTypeInfo<PlaySoundGlobalEvent>::field_data<1 + StormReflTypeInfo<GlobalNetworkEvent>::fields_n, Self> : public StormReflTypeInfo<PlaySoundGlobalEvent>::field_data_static<1 + StormReflTypeInfo<GlobalNetworkEvent>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int16_t> & Get() { return self.m_PositionX; }
  std::add_const_t<std::remove_reference_t<int16_t>> & Get() const { return self.m_PositionX; }
  void SetDefault() { self.m_PositionX = StormReflTypeInfo<PlaySoundGlobalEvent>::GetDefault().m_PositionX; }
};

template <>
struct StormReflTypeInfo<PlaySoundGlobalEvent>::field_data_static<2 + StormReflTypeInfo<GlobalNetworkEvent>::fields_n>
{
  using member_type = int16_t; // short
  static constexpr auto GetName() { return "m_PositionY"; }
  static constexpr auto GetType() { return "short"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD1040DB1; }
  static constexpr unsigned GetTypeNameHash() { return 0x8F2890A2; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2 + StormReflTypeInfo<GlobalNetworkEvent>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlaySoundGlobalEvent::m_PositionY; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlaySoundGlobalEvent *>(obj); return &ptr->m_PositionY; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlaySoundGlobalEvent *>(obj); return &ptr->m_PositionY; }
};

template <typename Self>
struct StormReflTypeInfo<PlaySoundGlobalEvent>::field_data<2 + StormReflTypeInfo<GlobalNetworkEvent>::fields_n, Self> : public StormReflTypeInfo<PlaySoundGlobalEvent>::field_data_static<2 + StormReflTypeInfo<GlobalNetworkEvent>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int16_t> & Get() { return self.m_PositionY; }
  std::add_const_t<std::remove_reference_t<int16_t>> & Get() const { return self.m_PositionY; }
  void SetDefault() { self.m_PositionY = StormReflTypeInfo<PlaySoundGlobalEvent>::GetDefault().m_PositionY; }
};

template <>
struct StormReflTypeInfo<PlayVfxGlobalEvent>
{
  using MyBase = GlobalNetworkEvent;
  static constexpr int fields_n = 3 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "PlayVfxGlobalEvent"; }
  static constexpr auto GetNameHash() { return 0xEA5024F2; }
  static constexpr bool HasDefault() { return true; }
  static PlayVfxGlobalEvent & GetDefault() { static PlayVfxGlobalEvent def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<PlayVfxGlobalEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xBD3E127B == type_name_hash) return static_cast<GlobalNetworkEvent *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const PlayVfxGlobalEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xBD3E127B == type_name_hash) return static_cast<const GlobalNetworkEvent *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<PlayVfxGlobalEvent *>(ptr);
    if(typeid(PlayVfxGlobalEvent).hash_code() == type_id_hash) return c;
    if(typeid(GlobalNetworkEvent).hash_code() == type_id_hash) return static_cast<GlobalNetworkEvent *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const PlayVfxGlobalEvent *>(ptr);
    if(typeid(PlayVfxGlobalEvent).hash_code() == type_id_hash) return c;
    if(typeid(GlobalNetworkEvent).hash_code() == type_id_hash) return static_cast<const GlobalNetworkEvent *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<PlayVfxGlobalEvent>::field_data_static<0 + StormReflTypeInfo<GlobalNetworkEvent>::fields_n>
{
  using member_type = uint32_t; // unsigned int
  static constexpr auto GetName() { return "m_AssetHash"; }
  static constexpr auto GetType() { return "unsigned int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8ACB36EB; }
  static constexpr unsigned GetTypeNameHash() { return 0x562EF932; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<GlobalNetworkEvent>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayVfxGlobalEvent::m_AssetHash; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlayVfxGlobalEvent *>(obj); return &ptr->m_AssetHash; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlayVfxGlobalEvent *>(obj); return &ptr->m_AssetHash; }
};

template <typename Self>
struct StormReflTypeInfo<PlayVfxGlobalEvent>::field_data<0 + StormReflTypeInfo<GlobalNetworkEvent>::fields_n, Self> : public StormReflTypeInfo<PlayVfxGlobalEvent>::field_data_static<0 + StormReflTypeInfo<GlobalNetworkEvent>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint32_t> & Get() { return self.m_AssetHash; }
  std::add_const_t<std::remove_reference_t<uint32_t>> & Get() const { return self.m_AssetHash; }
  void SetDefault() { self.m_AssetHash = StormReflTypeInfo<PlayVfxGlobalEvent>::GetDefault().m_AssetHash; }
};

template <>
struct StormReflTypeInfo<PlayVfxGlobalEvent>::field_data_static<1 + StormReflTypeInfo<GlobalNetworkEvent>::fields_n>
{
  using member_type = int16_t; // short
  static constexpr auto GetName() { return "m_PositionX"; }
  static constexpr auto GetType() { return "short"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA6033D27; }
  static constexpr unsigned GetTypeNameHash() { return 0x8F2890A2; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1 + StormReflTypeInfo<GlobalNetworkEvent>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayVfxGlobalEvent::m_PositionX; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlayVfxGlobalEvent *>(obj); return &ptr->m_PositionX; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlayVfxGlobalEvent *>(obj); return &ptr->m_PositionX; }
};

template <typename Self>
struct StormReflTypeInfo<PlayVfxGlobalEvent>::field_data<1 + StormReflTypeInfo<GlobalNetworkEvent>::fields_n, Self> : public StormReflTypeInfo<PlayVfxGlobalEvent>::field_data_static<1 + StormReflTypeInfo<GlobalNetworkEvent>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int16_t> & Get() { return self.m_PositionX; }
  std::add_const_t<std::remove_reference_t<int16_t>> & Get() const { return self.m_PositionX; }
  void SetDefault() { self.m_PositionX = StormReflTypeInfo<PlayVfxGlobalEvent>::GetDefault().m_PositionX; }
};

template <>
struct StormReflTypeInfo<PlayVfxGlobalEvent>::field_data_static<2 + StormReflTypeInfo<GlobalNetworkEvent>::fields_n>
{
  using member_type = int16_t; // short
  static constexpr auto GetName() { return "m_PositionY"; }
  static constexpr auto GetType() { return "short"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD1040DB1; }
  static constexpr unsigned GetTypeNameHash() { return 0x8F2890A2; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2 + StormReflTypeInfo<GlobalNetworkEvent>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayVfxGlobalEvent::m_PositionY; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlayVfxGlobalEvent *>(obj); return &ptr->m_PositionY; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlayVfxGlobalEvent *>(obj); return &ptr->m_PositionY; }
};

template <typename Self>
struct StormReflTypeInfo<PlayVfxGlobalEvent>::field_data<2 + StormReflTypeInfo<GlobalNetworkEvent>::fields_n, Self> : public StormReflTypeInfo<PlayVfxGlobalEvent>::field_data_static<2 + StormReflTypeInfo<GlobalNetworkEvent>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int16_t> & Get() { return self.m_PositionY; }
  std::add_const_t<std::remove_reference_t<int16_t>> & Get() const { return self.m_PositionY; }
  void SetDefault() { self.m_PositionY = StormReflTypeInfo<PlayVfxGlobalEvent>::GetDefault().m_PositionY; }
};

template <>
struct StormReflTypeInfo<TieEvent>
{
  using MyBase = GlobalNetworkEvent;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "TieEvent"; }
  static constexpr auto GetNameHash() { return 0xCE146734; }
  static constexpr bool HasDefault() { return true; }
  static TieEvent & GetDefault() { static TieEvent def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<TieEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xBD3E127B == type_name_hash) return static_cast<GlobalNetworkEvent *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const TieEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xBD3E127B == type_name_hash) return static_cast<const GlobalNetworkEvent *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<TieEvent *>(ptr);
    if(typeid(TieEvent).hash_code() == type_id_hash) return c;
    if(typeid(GlobalNetworkEvent).hash_code() == type_id_hash) return static_cast<GlobalNetworkEvent *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const TieEvent *>(ptr);
    if(typeid(TieEvent).hash_code() == type_id_hash) return c;
    if(typeid(GlobalNetworkEvent).hash_code() == type_id_hash) return static_cast<const GlobalNetworkEvent *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ServerAuthNetworkEvent>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ServerAuthNetworkEvent"; }
  static constexpr auto GetNameHash() { return 0xE24857C1; }
  static constexpr bool HasDefault() { return true; }
  static ServerAuthNetworkEvent & GetDefault() { static ServerAuthNetworkEvent def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ServerAuthNetworkEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ServerAuthNetworkEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ServerAuthNetworkEvent *>(ptr);
    if(typeid(ServerAuthNetworkEvent).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ServerAuthNetworkEvent *>(ptr);
    if(typeid(ServerAuthNetworkEvent).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<PlaceholderServerAuthEvent>
{
  using MyBase = ServerAuthNetworkEvent;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "PlaceholderServerAuthEvent"; }
  static constexpr auto GetNameHash() { return 0x29691225; }
  static constexpr bool HasDefault() { return true; }
  static PlaceholderServerAuthEvent & GetDefault() { static PlaceholderServerAuthEvent def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<PlaceholderServerAuthEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xE24857C1 == type_name_hash) return static_cast<ServerAuthNetworkEvent *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const PlaceholderServerAuthEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xE24857C1 == type_name_hash) return static_cast<const ServerAuthNetworkEvent *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<PlaceholderServerAuthEvent *>(ptr);
    if(typeid(PlaceholderServerAuthEvent).hash_code() == type_id_hash) return c;
    if(typeid(ServerAuthNetworkEvent).hash_code() == type_id_hash) return static_cast<ServerAuthNetworkEvent *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const PlaceholderServerAuthEvent *>(ptr);
    if(typeid(PlaceholderServerAuthEvent).hash_code() == type_id_hash) return c;
    if(typeid(ServerAuthNetworkEvent).hash_code() == type_id_hash) return static_cast<const ServerAuthNetworkEvent *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<TargetNetworkEvent>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "TargetNetworkEvent"; }
  static constexpr auto GetNameHash() { return 0x40E708F3; }
  static constexpr bool HasDefault() { return true; }
  static TargetNetworkEvent & GetDefault() { static TargetNetworkEvent def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<TargetNetworkEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const TargetNetworkEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<TargetNetworkEvent *>(ptr);
    if(typeid(TargetNetworkEvent).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const TargetNetworkEvent *>(ptr);
    if(typeid(TargetNetworkEvent).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<TargetNetworkEvent>::field_data_static<0>
{
  using member_type = NetRangedNumber<int, 0, 255>; // NetRangedNumber<int, 0, 255>
  static constexpr auto GetName() { return "m_Target"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, 0, 255>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0B507834; }
  static constexpr unsigned GetTypeNameHash() { return 0x4CE63414; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &TargetNetworkEvent::m_Target; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<TargetNetworkEvent *>(obj); return &ptr->m_Target; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const TargetNetworkEvent *>(obj); return &ptr->m_Target; }
};

template <typename Self>
struct StormReflTypeInfo<TargetNetworkEvent>::field_data<0, Self> : public StormReflTypeInfo<TargetNetworkEvent>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRangedNumber<int, 0, 255>> & Get() { return self.m_Target; }
  std::add_const_t<std::remove_reference_t<NetRangedNumber<int, 0, 255>>> & Get() const { return self.m_Target; }
  void SetDefault() { self.m_Target = StormReflTypeInfo<TargetNetworkEvent>::GetDefault().m_Target; }
};

template <>
struct StormReflTypeInfo<PlaceholderTargetEvent>
{
  using MyBase = TargetNetworkEvent;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "PlaceholderTargetEvent"; }
  static constexpr auto GetNameHash() { return 0xF23AD6F7; }
  static constexpr bool HasDefault() { return true; }
  static PlaceholderTargetEvent & GetDefault() { static PlaceholderTargetEvent def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<PlaceholderTargetEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x40E708F3 == type_name_hash) return static_cast<TargetNetworkEvent *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const PlaceholderTargetEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x40E708F3 == type_name_hash) return static_cast<const TargetNetworkEvent *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<PlaceholderTargetEvent *>(ptr);
    if(typeid(PlaceholderTargetEvent).hash_code() == type_id_hash) return c;
    if(typeid(TargetNetworkEvent).hash_code() == type_id_hash) return static_cast<TargetNetworkEvent *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const PlaceholderTargetEvent *>(ptr);
    if(typeid(PlaceholderTargetEvent).hash_code() == type_id_hash) return c;
    if(typeid(TargetNetworkEvent).hash_code() == type_id_hash) return static_cast<const TargetNetworkEvent *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ClientNetworkEvent>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ClientNetworkEvent"; }
  static constexpr auto GetNameHash() { return 0xC69662C2; }
  static constexpr bool HasDefault() { return true; }
  static ClientNetworkEvent & GetDefault() { static ClientNetworkEvent def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ClientNetworkEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ClientNetworkEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ClientNetworkEvent *>(ptr);
    if(typeid(ClientNetworkEvent).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ClientNetworkEvent *>(ptr);
    if(typeid(ClientNetworkEvent).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<PlaceholderClientEvent>
{
  using MyBase = ClientNetworkEvent;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "PlaceholderClientEvent"; }
  static constexpr auto GetNameHash() { return 0xEEBE0324; }
  static constexpr bool HasDefault() { return true; }
  static PlaceholderClientEvent & GetDefault() { static PlaceholderClientEvent def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<PlaceholderClientEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xC69662C2 == type_name_hash) return static_cast<ClientNetworkEvent *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const PlaceholderClientEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xC69662C2 == type_name_hash) return static_cast<const ClientNetworkEvent *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<PlaceholderClientEvent *>(ptr);
    if(typeid(PlaceholderClientEvent).hash_code() == type_id_hash) return c;
    if(typeid(ClientNetworkEvent).hash_code() == type_id_hash) return static_cast<ClientNetworkEvent *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const PlaceholderClientEvent *>(ptr);
    if(typeid(PlaceholderClientEvent).hash_code() == type_id_hash) return c;
    if(typeid(ClientNetworkEvent).hash_code() == type_id_hash) return static_cast<const ClientNetworkEvent *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<JumpEvent>
{
  using MyBase = ClientNetworkEvent;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "JumpEvent"; }
  static constexpr auto GetNameHash() { return 0x940BF099; }
  static constexpr bool HasDefault() { return true; }
  static JumpEvent & GetDefault() { static JumpEvent def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<JumpEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xC69662C2 == type_name_hash) return static_cast<ClientNetworkEvent *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const JumpEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xC69662C2 == type_name_hash) return static_cast<const ClientNetworkEvent *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<JumpEvent *>(ptr);
    if(typeid(JumpEvent).hash_code() == type_id_hash) return c;
    if(typeid(ClientNetworkEvent).hash_code() == type_id_hash) return static_cast<ClientNetworkEvent *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const JumpEvent *>(ptr);
    if(typeid(JumpEvent).hash_code() == type_id_hash) return c;
    if(typeid(ClientNetworkEvent).hash_code() == type_id_hash) return static_cast<const ClientNetworkEvent *>(c);
    return nullptr;
  }

};

namespace StormReflFileInfo
{
  struct GameNetworkEvents
  {
    static const int types_n = 13;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct GameNetworkEvents::type_info<0>
  {
    using type = ::GlobalNetworkEvent;
  };

  template <>
  struct GameNetworkEvents::type_info<1>
  {
    using type = ::CreateEntityGlobalEvent;
  };

  template <>
  struct GameNetworkEvents::type_info<2>
  {
    using type = ::CameraShakeEvent;
  };

  template <>
  struct GameNetworkEvents::type_info<3>
  {
    using type = ::PlaySoundGlobalEvent;
  };

  template <>
  struct GameNetworkEvents::type_info<4>
  {
    using type = ::PlayVfxGlobalEvent;
  };

  template <>
  struct GameNetworkEvents::type_info<5>
  {
    using type = ::TieEvent;
  };

  template <>
  struct GameNetworkEvents::type_info<6>
  {
    using type = ::ServerAuthNetworkEvent;
  };

  template <>
  struct GameNetworkEvents::type_info<7>
  {
    using type = ::PlaceholderServerAuthEvent;
  };

  template <>
  struct GameNetworkEvents::type_info<8>
  {
    using type = ::TargetNetworkEvent;
  };

  template <>
  struct GameNetworkEvents::type_info<9>
  {
    using type = ::PlaceholderTargetEvent;
  };

  template <>
  struct GameNetworkEvents::type_info<10>
  {
    using type = ::ClientNetworkEvent;
  };

  template <>
  struct GameNetworkEvents::type_info<11>
  {
    using type = ::PlaceholderClientEvent;
  };

  template <>
  struct GameNetworkEvents::type_info<12>
  {
    using type = ::JumpEvent;
  };

}

