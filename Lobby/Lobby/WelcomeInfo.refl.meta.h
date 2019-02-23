#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "WelcomeInfo.refl.h"


template <>
struct StormReflTypeInfo<WelcomeInfoTab>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "WelcomeInfoTab"; }
  static constexpr auto GetNameHash() { return 0x53B1D070; }
  static constexpr bool HasDefault() { return true; }
  static WelcomeInfoTab & GetDefault() { static WelcomeInfoTab def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<WelcomeInfoTab *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const WelcomeInfoTab *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<WelcomeInfoTab *>(ptr);
    if(typeid(WelcomeInfoTab).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const WelcomeInfoTab *>(ptr);
    if(typeid(WelcomeInfoTab).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<WelcomeInfoTab>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &WelcomeInfoTab::m_Name; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<WelcomeInfoTab *>(obj); return &ptr->m_Name; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const WelcomeInfoTab *>(obj); return &ptr->m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<WelcomeInfoTab>::field_data<0, Self> : public StormReflTypeInfo<WelcomeInfoTab>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<WelcomeInfoTab>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<WelcomeInfoTab>::field_data_static<1>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Info"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF514A448; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &WelcomeInfoTab::m_Info; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<WelcomeInfoTab *>(obj); return &ptr->m_Info; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const WelcomeInfoTab *>(obj); return &ptr->m_Info; }
};

template <typename Self>
struct StormReflTypeInfo<WelcomeInfoTab>::field_data<1, Self> : public StormReflTypeInfo<WelcomeInfoTab>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Info; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Info; }
  void SetDefault() { self.m_Info = StormReflTypeInfo<WelcomeInfoTab>::GetDefault().m_Info; }
};

template <>
struct StormReflTypeInfo<WelcomeInfo>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "WelcomeInfo"; }
  static constexpr auto GetNameHash() { return 0x3B46FA57; }
  static constexpr bool HasDefault() { return false; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<WelcomeInfo *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const WelcomeInfo *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<WelcomeInfo *>(ptr);
    if(typeid(WelcomeInfo).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const WelcomeInfo *>(ptr);
    if(typeid(WelcomeInfo).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<WelcomeInfo>::field_data_static<0>
{
  using member_type = RMergeList<WelcomeInfoTab>; // RMergeList<WelcomeInfoTab>
  static constexpr auto GetName() { return "m_Tabs"; }
  static constexpr auto GetType() { return "RMergeList<WelcomeInfoTab>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2C56F57C; }
  static constexpr unsigned GetTypeNameHash() { return 0xAA5159C3; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &WelcomeInfo::m_Tabs; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<WelcomeInfo *>(obj); return &ptr->m_Tabs; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const WelcomeInfo *>(obj); return &ptr->m_Tabs; }
};

template <typename Self>
struct StormReflTypeInfo<WelcomeInfo>::field_data<0, Self> : public StormReflTypeInfo<WelcomeInfo>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<WelcomeInfoTab>> & Get() { return self.m_Tabs; }
  std::add_const_t<std::remove_reference_t<RMergeList<WelcomeInfoTab>>> & Get() const { return self.m_Tabs; }
};

template <>
struct StormReflFuncInfo<WelcomeInfo>
{
  using MyBase = void;
  static constexpr int funcs_n = 3;
  template <int N> struct func_data_static {};
};

template <>
struct StormReflFuncInfo<WelcomeInfo>::func_data_static<0>
{
  using func_ptr_type = void (WelcomeInfo::*)(DDSResponder &, std::string, std::string);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "UpdateInfo"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xBEEAF920; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 0; }
  static constexpr func_ptr_type GetFunctionPtr() { return &WelcomeInfo::UpdateInfo; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<WelcomeInfo>::func_data_static<0>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<WelcomeInfo>::func_data_static<0>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "tab_name"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xE0E15003; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<WelcomeInfo>::func_data_static<0>::param_info<2>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "info"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xCB893157; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<WelcomeInfo>::func_data_static<1>
{
  using func_ptr_type = void (WelcomeInfo::*)(DDSResponder &, std::string);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "RemoveTab"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xFFE08D8B; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 1; }
  static constexpr func_ptr_type GetFunctionPtr() { return &WelcomeInfo::RemoveTab; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<WelcomeInfo>::func_data_static<1>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<WelcomeInfo>::func_data_static<1>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "tab_name"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xE0E15003; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<WelcomeInfo>::func_data_static<2>
{
  using func_ptr_type = void (WelcomeInfo::*)(DDSResponder &);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "FetchWelcomeInfo"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xDE88F4A0; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 2; }
  static constexpr func_ptr_type GetFunctionPtr() { return &WelcomeInfo::FetchWelcomeInfo; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<WelcomeInfo>::func_data_static<2>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

namespace StormReflFileInfo
{
  struct WelcomeInfo
  {
    static const int types_n = 2;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct WelcomeInfo::type_info<0>
  {
    using type = ::WelcomeInfoTab;
  };

  template <>
  struct WelcomeInfo::type_info<1>
  {
    using type = ::WelcomeInfo;
  };

}

