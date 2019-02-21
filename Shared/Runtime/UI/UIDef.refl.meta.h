#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "UIDef.refl.h"


template <>
struct StormReflTypeInfo<UIDefDebugVariable>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UIDefDebugVariable"; }
  static constexpr auto GetNameHash() { return 0x69D0B1AE; }
  static constexpr bool HasDefault() { return true; }
  static UIDefDebugVariable & GetDefault() { static UIDefDebugVariable def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<UIDefDebugVariable *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const UIDefDebugVariable *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<UIDefDebugVariable *>(ptr);
    if(typeid(UIDefDebugVariable).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const UIDefDebugVariable *>(ptr);
    if(typeid(UIDefDebugVariable).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<UIDefDebugVariable>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UIDefDebugVariable::m_Name; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UIDefDebugVariable *>(obj); return &ptr->m_Name; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UIDefDebugVariable *>(obj); return &ptr->m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<UIDefDebugVariable>::field_data<0, Self> : public StormReflTypeInfo<UIDefDebugVariable>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<UIDefDebugVariable>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<UIDefDebugVariable>::field_data_static<1>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Value"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x9041C854; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UIDefDebugVariable::m_Value; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UIDefDebugVariable *>(obj); return &ptr->m_Value; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UIDefDebugVariable *>(obj); return &ptr->m_Value; }
};

template <typename Self>
struct StormReflTypeInfo<UIDefDebugVariable>::field_data<1, Self> : public StormReflTypeInfo<UIDefDebugVariable>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Value; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Value; }
  void SetDefault() { self.m_Value = StormReflTypeInfo<UIDefDebugVariable>::GetDefault().m_Value; }
};

template <>
struct StormReflTypeInfo<UIDefDebugFunction>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UIDefDebugFunction"; }
  static constexpr auto GetNameHash() { return 0x6F33201E; }
  static constexpr bool HasDefault() { return true; }
  static UIDefDebugFunction & GetDefault() { static UIDefDebugFunction def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<UIDefDebugFunction *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const UIDefDebugFunction *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<UIDefDebugFunction *>(ptr);
    if(typeid(UIDefDebugFunction).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const UIDefDebugFunction *>(ptr);
    if(typeid(UIDefDebugFunction).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<UIDefDebugFunction>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UIDefDebugFunction::m_Name; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UIDefDebugFunction *>(obj); return &ptr->m_Name; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UIDefDebugFunction *>(obj); return &ptr->m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<UIDefDebugFunction>::field_data<0, Self> : public StormReflTypeInfo<UIDefDebugFunction>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<UIDefDebugFunction>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<UIDefDebugFunction>::field_data_static<1>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Value"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x9041C854; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UIDefDebugFunction::m_Value; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UIDefDebugFunction *>(obj); return &ptr->m_Value; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UIDefDebugFunction *>(obj); return &ptr->m_Value; }
};

template <typename Self>
struct StormReflTypeInfo<UIDefDebugFunction>::field_data<1, Self> : public StormReflTypeInfo<UIDefDebugFunction>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Value; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Value; }
  void SetDefault() { self.m_Value = StormReflTypeInfo<UIDefDebugFunction>::GetDefault().m_Value; }
};

template <>
struct StormReflTypeInfo<UIDefDebugFunction>::field_data_static<2>
{
  using member_type = RBool; // RBool
  static constexpr auto GetName() { return "m_DebugOutput"; }
  static constexpr auto GetType() { return "RBool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFB9F6830; }
  static constexpr unsigned GetTypeNameHash() { return 0x50062D06; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UIDefDebugFunction::m_DebugOutput; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UIDefDebugFunction *>(obj); return &ptr->m_DebugOutput; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UIDefDebugFunction *>(obj); return &ptr->m_DebugOutput; }
};

template <typename Self>
struct StormReflTypeInfo<UIDefDebugFunction>::field_data<2, Self> : public StormReflTypeInfo<UIDefDebugFunction>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RBool> & Get() { return self.m_DebugOutput; }
  std::add_const_t<std::remove_reference_t<RBool>> & Get() const { return self.m_DebugOutput; }
  void SetDefault() { self.m_DebugOutput = StormReflTypeInfo<UIDefDebugFunction>::GetDefault().m_DebugOutput; }
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
  static constexpr bool HasDefault() { return true; }
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
  static constexpr bool HasDefault() { return true; }
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
  static constexpr bool HasDefault() { return true; }
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
  using member_type = RMergeList<UIDefDebugVariable>; // RMergeList<UIDefDebugVariable>
  static constexpr auto GetName() { return "m_Variables"; }
  static constexpr auto GetType() { return "RMergeList<UIDefDebugVariable>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x54EB5C0A; }
  static constexpr unsigned GetTypeNameHash() { return 0xC3A9334C; }
  static constexpr bool HasDefault() { return true; }
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
  match_const_t<Self, RMergeList<UIDefDebugVariable>> & Get() { return self.m_Variables; }
  std::add_const_t<std::remove_reference_t<RMergeList<UIDefDebugVariable>>> & Get() const { return self.m_Variables; }
  void SetDefault() { self.m_Variables = StormReflTypeInfo<UIDef>::GetDefault().m_Variables; }
};

template <>
struct StormReflTypeInfo<UIDef>::field_data_static<3>
{
  using member_type = RMergeList<UIDefDebugFunction>; // RMergeList<UIDefDebugFunction>
  static constexpr auto GetName() { return "m_Functions"; }
  static constexpr auto GetType() { return "RMergeList<UIDefDebugFunction>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x9F8C0C17; }
  static constexpr unsigned GetTypeNameHash() { return 0x08CE6351; }
  static constexpr bool HasDefault() { return true; }
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
  match_const_t<Self, RMergeList<UIDefDebugFunction>> & Get() { return self.m_Functions; }
  std::add_const_t<std::remove_reference_t<RMergeList<UIDefDebugFunction>>> & Get() const { return self.m_Functions; }
  void SetDefault() { self.m_Functions = StormReflTypeInfo<UIDef>::GetDefault().m_Functions; }
};

namespace StormReflFileInfo
{
  struct UIDef
  {
    static const int types_n = 3;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct UIDef::type_info<0>
  {
    using type = ::UIDefDebugVariable;
  };

  template <>
  struct UIDef::type_info<1>
  {
    using type = ::UIDefDebugFunction;
  };

  template <>
  struct UIDef::type_info<2>
  {
    using type = ::UIDef;
  };

}

