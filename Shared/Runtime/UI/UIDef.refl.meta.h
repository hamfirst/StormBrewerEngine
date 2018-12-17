#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "UIDef.refl.h"


template <>
struct StormReflTypeInfo<UIDefDebugData>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UIDefDebugData"; }
  static constexpr auto GetNameHash() { return 0xDD3090C0; }
  static UIDefDebugData & GetDefault() { static UIDefDebugData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<UIDefDebugData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const UIDefDebugData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<UIDefDebugData *>(ptr);
    if(typeid(UIDefDebugData).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const UIDefDebugData *>(ptr);
    if(typeid(UIDefDebugData).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<UIDefDebugData>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UIDefDebugData::m_Name; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UIDefDebugData *>(obj); return &ptr->m_Name; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UIDefDebugData *>(obj); return &ptr->m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<UIDefDebugData>::field_data<0, Self> : public StormReflTypeInfo<UIDefDebugData>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<UIDefDebugData>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<UIDefDebugData>::field_data_static<1>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Value"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x9041C854; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UIDefDebugData::m_Value; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UIDefDebugData *>(obj); return &ptr->m_Value; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UIDefDebugData *>(obj); return &ptr->m_Value; }
};

template <typename Self>
struct StormReflTypeInfo<UIDefDebugData>::field_data<1, Self> : public StormReflTypeInfo<UIDefDebugData>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Value; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Value; }
  void SetDefault() { self.m_Value = StormReflTypeInfo<UIDefDebugData>::GetDefault().m_Value; }
};

template <>
struct StormReflTypeInfo<UIDef>
{
  using MyBase = void;
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UIDef"; }
  static constexpr auto GetNameHash() { return 0x1B05DE82; }
  static UIDef & GetDefault() { static UIDef def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<UIDef *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const UIDef *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<UIDef *>(ptr);
    if(typeid(UIDef).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const UIDef *>(ptr);
    if(typeid(UIDef).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<UIDef>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_InitFunction"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0xBD4942CF; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UIDef::m_InitFunction; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UIDef *>(obj); return &ptr->m_InitFunction; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UIDef *>(obj); return &ptr->m_InitFunction; }
};

template <typename Self>
struct StormReflTypeInfo<UIDef>::field_data<0, Self> : public StormReflTypeInfo<UIDef>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_InitFunction; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_InitFunction; }
  void SetDefault() { self.m_InitFunction = StormReflTypeInfo<UIDef>::GetDefault().m_InitFunction; }
};

template <>
struct StormReflTypeInfo<UIDef>::field_data_static<1>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_CleanupFunction"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x871977E0; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UIDef::m_CleanupFunction; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UIDef *>(obj); return &ptr->m_CleanupFunction; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UIDef *>(obj); return &ptr->m_CleanupFunction; }
};

template <typename Self>
struct StormReflTypeInfo<UIDef>::field_data<1, Self> : public StormReflTypeInfo<UIDef>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_CleanupFunction; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_CleanupFunction; }
  void SetDefault() { self.m_CleanupFunction = StormReflTypeInfo<UIDef>::GetDefault().m_CleanupFunction; }
};

template <>
struct StormReflTypeInfo<UIDef>::field_data_static<2>
{
  using member_type = RMergeList<UIDefDebugData>; // RMergeList<UIDefDebugData>
  static constexpr auto GetName() { return "m_Variables"; }
  static constexpr auto GetType() { return "RMergeList<UIDefDebugData>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x54EB5C0A; }
  static constexpr unsigned GetTypeNameHash() { return 0x61BE6B0F; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UIDef::m_Variables; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UIDef *>(obj); return &ptr->m_Variables; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UIDef *>(obj); return &ptr->m_Variables; }
};

template <typename Self>
struct StormReflTypeInfo<UIDef>::field_data<2, Self> : public StormReflTypeInfo<UIDef>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<UIDefDebugData>> & Get() { return self.m_Variables; }
  std::add_const_t<std::remove_reference_t<RMergeList<UIDefDebugData>>> & Get() const { return self.m_Variables; }
  void SetDefault() { self.m_Variables = StormReflTypeInfo<UIDef>::GetDefault().m_Variables; }
};

template <>
struct StormReflTypeInfo<UIDef>::field_data_static<3>
{
  using member_type = RMergeList<UIDefDebugData>; // RMergeList<UIDefDebugData>
  static constexpr auto GetName() { return "m_Functions"; }
  static constexpr auto GetType() { return "RMergeList<UIDefDebugData>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x9F8C0C17; }
  static constexpr unsigned GetTypeNameHash() { return 0x61BE6B0F; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &UIDef::m_Functions; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UIDef *>(obj); return &ptr->m_Functions; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UIDef *>(obj); return &ptr->m_Functions; }
};

template <typename Self>
struct StormReflTypeInfo<UIDef>::field_data<3, Self> : public StormReflTypeInfo<UIDef>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<UIDefDebugData>> & Get() { return self.m_Functions; }
  std::add_const_t<std::remove_reference_t<RMergeList<UIDefDebugData>>> & Get() const { return self.m_Functions; }
  void SetDefault() { self.m_Functions = StormReflTypeInfo<UIDef>::GetDefault().m_Functions; }
};

namespace StormReflFileInfo
{
  struct UIDef
  {
    static const int types_n = 2;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct UIDef::type_info<0>
  {
    using type = ::UIDefDebugData;
  };

  template <>
  struct UIDef::type_info<1>
  {
    using type = ::UIDef;
  };

}

