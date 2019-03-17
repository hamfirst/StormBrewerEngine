#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "BanList.refl.h"


template <>
struct StormReflEnumInfo<BanType>
{
  static constexpr int elems_n = 3;
  static constexpr auto GetName() { return "BanType"; }
  static constexpr auto GetNameHash() { return 0xA6FA89F6; }
  template <int N> struct elems { };
};

template <>
struct StormReflEnumInfo<BanType>::elems<0>
{
  static constexpr auto GetName() { return "kRemoteIp"; }
  static constexpr auto GetNameHash() { return 0x8245DB46; }
  static constexpr auto GetValue() { return BanType::kRemoteIp; }
};

template <>
struct StormReflEnumInfo<BanType>::elems<1>
{
  static constexpr auto GetName() { return "kRemoteHost"; }
  static constexpr auto GetNameHash() { return 0x0A476F5D; }
  static constexpr auto GetValue() { return BanType::kRemoteHost; }
};

template <>
struct StormReflEnumInfo<BanType>::elems<2>
{
  static constexpr auto GetName() { return "kPlatformId"; }
  static constexpr auto GetNameHash() { return 0x30C56DC7; }
  static constexpr auto GetValue() { return BanType::kPlatformId; }
};

template <>
struct StormReflTypeInfo<BanListElement>
{
  using MyBase = void;
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "BanListElement"; }
  static constexpr auto GetNameHash() { return 0x606F8A65; }
  static constexpr bool HasDefault() { return true; }
  static BanListElement & GetDefault() { static BanListElement def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<BanListElement *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const BanListElement *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<BanListElement *>(ptr);
    if(typeid(BanListElement).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const BanListElement *>(ptr);
    if(typeid(BanListElement).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<BanListElement>::field_data_static<0>
{
  using member_type = REnum<BanType>; // REnum<BanType>
  static constexpr auto GetName() { return "m_Type"; }
  static constexpr auto GetType() { return "REnum<BanType>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB243C236; }
  static constexpr unsigned GetTypeNameHash() { return 0x374F2901; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &BanListElement::m_Type; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<BanListElement *>(obj); return &ptr->m_Type; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const BanListElement *>(obj); return &ptr->m_Type; }
};

template <typename Self>
struct StormReflTypeInfo<BanListElement>::field_data<0, Self> : public StormReflTypeInfo<BanListElement>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, REnum<BanType>> & Get() { return self.m_Type; }
  std::add_const_t<std::remove_reference_t<REnum<BanType>>> & Get() const { return self.m_Type; }
  void SetDefault() { self.m_Type = StormReflTypeInfo<BanListElement>::GetDefault().m_Type; }
};

template <>
struct StormReflTypeInfo<BanListElement>::field_data_static<1>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Data"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x936E667C; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &BanListElement::m_Data; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<BanListElement *>(obj); return &ptr->m_Data; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const BanListElement *>(obj); return &ptr->m_Data; }
};

template <typename Self>
struct StormReflTypeInfo<BanListElement>::field_data<1, Self> : public StormReflTypeInfo<BanListElement>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Data; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Data; }
  void SetDefault() { self.m_Data = StormReflTypeInfo<BanListElement>::GetDefault().m_Data; }
};

template <>
struct StormReflTypeInfo<BanListElement>::field_data_static<2>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_Expiration"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAE74B980; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &BanListElement::m_Expiration; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<BanListElement *>(obj); return &ptr->m_Expiration; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const BanListElement *>(obj); return &ptr->m_Expiration; }
};

template <typename Self>
struct StormReflTypeInfo<BanListElement>::field_data<2, Self> : public StormReflTypeInfo<BanListElement>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_Expiration; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_Expiration; }
  void SetDefault() { self.m_Expiration = StormReflTypeInfo<BanListElement>::GetDefault().m_Expiration; }
};

template <>
struct StormReflTypeInfo<BanListElement>::field_data_static<3>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Message"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x234F45AA; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &BanListElement::m_Message; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<BanListElement *>(obj); return &ptr->m_Message; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const BanListElement *>(obj); return &ptr->m_Message; }
};

template <typename Self>
struct StormReflTypeInfo<BanListElement>::field_data<3, Self> : public StormReflTypeInfo<BanListElement>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Message; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Message; }
  void SetDefault() { self.m_Message = StormReflTypeInfo<BanListElement>::GetDefault().m_Message; }
};

template <>
struct StormReflTypeInfo<BanList>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "BanList"; }
  static constexpr auto GetNameHash() { return 0x6EEC26C7; }
  static constexpr bool HasDefault() { return false; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<BanList *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const BanList *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<BanList *>(ptr);
    if(typeid(BanList).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const BanList *>(ptr);
    if(typeid(BanList).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<BanList>::field_data_static<0>
{
  using member_type = RMergeList<BanListElement>; // RMergeList<BanListElement>
  static constexpr auto GetName() { return "m_List"; }
  static constexpr auto GetType() { return "RMergeList<BanListElement>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x7A556D07; }
  static constexpr unsigned GetTypeNameHash() { return 0xC7BF6372; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &BanList::m_List; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<BanList *>(obj); return &ptr->m_List; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const BanList *>(obj); return &ptr->m_List; }
};

template <typename Self>
struct StormReflTypeInfo<BanList>::field_data<0, Self> : public StormReflTypeInfo<BanList>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<BanListElement>> & Get() { return self.m_List; }
  std::add_const_t<std::remove_reference_t<RMergeList<BanListElement>>> & Get() const { return self.m_List; }
};

template <>
struct StormReflFuncInfo<BanList>
{
  using MyBase = void;
  static constexpr int funcs_n = 4;
  template <int N> struct func_data_static {};
};

template <>
struct StormReflFuncInfo<BanList>::func_data_static<0>
{
  using func_ptr_type = void (BanList::*)(BanType, std::string, int, std::string);
  using return_type = void;
  static constexpr int params_n = 4;
  static constexpr auto GetName() { return "Ban"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x5AB39605; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 0; }
  static constexpr func_ptr_type GetFunctionPtr() { return &BanList::Ban; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<BanList>::func_data_static<0>::param_info<0>
{
  using param_type = BanType;
  static constexpr auto GetName() { return "type"; }
  static constexpr auto GetType() { return "BanType"; }
  static constexpr unsigned GetNameHash() { return 0x8CDE5729; }
  static constexpr unsigned GetTypeNameHash() { return 0xA6FA89F6; }
};

template <>
struct StormReflFuncInfo<BanList>::func_data_static<0>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "data"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xADF3F363; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<BanList>::func_data_static<0>::param_info<2>
{
  using param_type = int;
  static constexpr auto GetName() { return "duration"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x865F80C0; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<BanList>::func_data_static<0>::param_info<3>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "message"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xB6BD307F; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<BanList>::func_data_static<1>
{
  using func_ptr_type = void (BanList::*)(int);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "Unban"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x70973E61; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 1; }
  static constexpr func_ptr_type GetFunctionPtr() { return &BanList::Unban; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<BanList>::func_data_static<1>::param_info<0>
{
  using param_type = int;
  static constexpr auto GetName() { return "ban_index"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xE8DD002F; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<BanList>::func_data_static<2>
{
  using func_ptr_type = void (BanList::*)(std::string);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "UnbanMatch"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xD85FECED; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 2; }
  static constexpr func_ptr_type GetFunctionPtr() { return &BanList::UnbanMatch; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<BanList>::func_data_static<2>::param_info<0>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "match_str"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x58E00227; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<BanList>::func_data_static<3>
{
  using func_ptr_type = void (BanList::*)(DDSResponder &);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "GetInfo"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x02540D1A; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 3; }
  static constexpr func_ptr_type GetFunctionPtr() { return &BanList::GetInfo; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<BanList>::func_data_static<3>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

namespace StormReflFileInfo
{
  struct BanList
  {
    static const int types_n = 2;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct BanList::type_info<0>
  {
    using type = ::BanListElement;
  };

  template <>
  struct BanList::type_info<1>
  {
    using type = ::BanList;
  };

}

