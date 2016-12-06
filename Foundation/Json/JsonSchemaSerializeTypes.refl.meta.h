#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "JsonSchemaSerializeTypes.refl.h"


template <>
struct StormReflTypeInfo<JsonSchemaSerializeInfo>
{
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "JsonSchemaSerializeInfo"; }
  static constexpr auto GetNameHash() { return 0x346EC82E; }
  static JsonSchemaSerializeInfo & GetDefault() { static JsonSchemaSerializeInfo def; return def; }
};

template <>
struct StormReflTypeInfo<JsonSchemaSerializeInfo>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_Type"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB243C236; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &JsonSchemaSerializeInfo::m_Type; }
};

template <typename Self>
struct StormReflTypeInfo<JsonSchemaSerializeInfo>::field_data<0, Self> : public StormReflTypeInfo<JsonSchemaSerializeInfo>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_Type; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_Type; }
  void SetDefault() { self.m_Type = StormReflTypeInfo<JsonSchemaSerializeInfo>::GetDefault().m_Type; }
};

template <>
struct StormReflTypeInfo<JsonSchemaSerializeInfo>::field_data_static<1>
{
  using member_type = size_t; // unsigned int
  static constexpr auto GetName() { return "m_SubSchemaIndex"; }
  static constexpr auto GetType() { return "unsigned int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x341CB795; }
  static constexpr unsigned GetTypeNameHash() { return 0x562EF932; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &JsonSchemaSerializeInfo::m_SubSchemaIndex; }
};

template <typename Self>
struct StormReflTypeInfo<JsonSchemaSerializeInfo>::field_data<1, Self> : public StormReflTypeInfo<JsonSchemaSerializeInfo>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, size_t> & Get() { return self.m_SubSchemaIndex; }
  std::add_const_t<std::remove_reference_t<size_t>> & Get() const { return self.m_SubSchemaIndex; }
  void SetDefault() { self.m_SubSchemaIndex = StormReflTypeInfo<JsonSchemaSerializeInfo>::GetDefault().m_SubSchemaIndex; }
};

template <>
struct StormReflTypeInfo<JsonSchemaSerializeInfo>::field_data_static<2>
{
  using member_type = uint32_t; // unsigned int
  static constexpr auto GetName() { return "m_TypeId"; }
  static constexpr auto GetType() { return "unsigned int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD6CBC358; }
  static constexpr unsigned GetTypeNameHash() { return 0x562EF932; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &JsonSchemaSerializeInfo::m_TypeId; }
};

template <typename Self>
struct StormReflTypeInfo<JsonSchemaSerializeInfo>::field_data<2, Self> : public StormReflTypeInfo<JsonSchemaSerializeInfo>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint32_t> & Get() { return self.m_TypeId; }
  std::add_const_t<std::remove_reference_t<uint32_t>> & Get() const { return self.m_TypeId; }
  void SetDefault() { self.m_TypeId = StormReflTypeInfo<JsonSchemaSerializeInfo>::GetDefault().m_TypeId; }
};

template <>
struct StormReflTypeInfo<JsonSchemaSerializeChildList>
{
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "JsonSchemaSerializeChildList"; }
  static constexpr auto GetNameHash() { return 0x78D86DA5; }
  static JsonSchemaSerializeChildList & GetDefault() { static JsonSchemaSerializeChildList def; return def; }
};

template <>
struct StormReflTypeInfo<JsonSchemaSerializeChildList>::field_data_static<0>
{
  using member_type = std::vector<std::pair<std::string, size_t> >; // std::vector<std::pair<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, unsigned int>, std::allocator<std::pair<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, unsigned int> > >
  static constexpr auto GetName() { return "m_ChildSchemas"; }
  static constexpr auto GetType() { return "std::vector<std::pair<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, unsigned int>, std::allocator<std::pair<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, unsigned int> > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x668A12B7; }
  static constexpr unsigned GetTypeNameHash() { return 0x9358AD07; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &JsonSchemaSerializeChildList::m_ChildSchemas; }
};

template <typename Self>
struct StormReflTypeInfo<JsonSchemaSerializeChildList>::field_data<0, Self> : public StormReflTypeInfo<JsonSchemaSerializeChildList>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<std::pair<std::string, size_t> >> & Get() { return self.m_ChildSchemas; }
  std::add_const_t<std::remove_reference_t<std::vector<std::pair<std::string, size_t> >>> & Get() const { return self.m_ChildSchemas; }
  void SetDefault() { self.m_ChildSchemas = StormReflTypeInfo<JsonSchemaSerializeChildList>::GetDefault().m_ChildSchemas; }
};

template <>
struct StormReflTypeInfo<JsonSchemaSerializeMessage>
{
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "JsonSchemaSerializeMessage"; }
  static constexpr auto GetNameHash() { return 0x168D4E70; }
  static JsonSchemaSerializeMessage & GetDefault() { static JsonSchemaSerializeMessage def; return def; }
};

template <>
struct StormReflTypeInfo<JsonSchemaSerializeMessage>::field_data_static<0>
{
  using member_type = std::vector<JsonSchemaSerializeInfo>; // std::vector<JsonSchemaSerializeInfo, std::allocator<JsonSchemaSerializeInfo> >
  static constexpr auto GetName() { return "m_Schemas"; }
  static constexpr auto GetType() { return "std::vector<JsonSchemaSerializeInfo, std::allocator<JsonSchemaSerializeInfo> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0B210447; }
  static constexpr unsigned GetTypeNameHash() { return 0x1D75B9C0; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &JsonSchemaSerializeMessage::m_Schemas; }
};

template <typename Self>
struct StormReflTypeInfo<JsonSchemaSerializeMessage>::field_data<0, Self> : public StormReflTypeInfo<JsonSchemaSerializeMessage>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<JsonSchemaSerializeInfo>> & Get() { return self.m_Schemas; }
  std::add_const_t<std::remove_reference_t<std::vector<JsonSchemaSerializeInfo>>> & Get() const { return self.m_Schemas; }
  void SetDefault() { self.m_Schemas = StormReflTypeInfo<JsonSchemaSerializeMessage>::GetDefault().m_Schemas; }
};

template <>
struct StormReflTypeInfo<JsonSchemaSerializeMessage>::field_data_static<1>
{
  using member_type = std::vector<JsonSchemaSerializeChildList>; // std::vector<JsonSchemaSerializeChildList, std::allocator<JsonSchemaSerializeChildList> >
  static constexpr auto GetName() { return "m_ChildSchemas"; }
  static constexpr auto GetType() { return "std::vector<JsonSchemaSerializeChildList, std::allocator<JsonSchemaSerializeChildList> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x668A12B7; }
  static constexpr unsigned GetTypeNameHash() { return 0xB5A594D3; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &JsonSchemaSerializeMessage::m_ChildSchemas; }
};

template <typename Self>
struct StormReflTypeInfo<JsonSchemaSerializeMessage>::field_data<1, Self> : public StormReflTypeInfo<JsonSchemaSerializeMessage>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<JsonSchemaSerializeChildList>> & Get() { return self.m_ChildSchemas; }
  std::add_const_t<std::remove_reference_t<std::vector<JsonSchemaSerializeChildList>>> & Get() const { return self.m_ChildSchemas; }
  void SetDefault() { self.m_ChildSchemas = StormReflTypeInfo<JsonSchemaSerializeMessage>::GetDefault().m_ChildSchemas; }
};

template <>
struct StormReflTypeInfo<JsonSchemaSerializeMessage>::field_data_static<2>
{
  using member_type = size_t; // unsigned int
  static constexpr auto GetName() { return "m_PrimarySchema"; }
  static constexpr auto GetType() { return "unsigned int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x047A3731; }
  static constexpr unsigned GetTypeNameHash() { return 0x562EF932; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &JsonSchemaSerializeMessage::m_PrimarySchema; }
};

template <typename Self>
struct StormReflTypeInfo<JsonSchemaSerializeMessage>::field_data<2, Self> : public StormReflTypeInfo<JsonSchemaSerializeMessage>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, size_t> & Get() { return self.m_PrimarySchema; }
  std::add_const_t<std::remove_reference_t<size_t>> & Get() const { return self.m_PrimarySchema; }
  void SetDefault() { self.m_PrimarySchema = StormReflTypeInfo<JsonSchemaSerializeMessage>::GetDefault().m_PrimarySchema; }
};

namespace StormReflFileInfo
{
  struct JsonSchemaSerializeTypes
  {
    static const int types_n = 3;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct JsonSchemaSerializeTypes::type_info<0>
  {
    using type = ::JsonSchemaSerializeInfo;
  };

  template <>
  struct JsonSchemaSerializeTypes::type_info<1>
  {
    using type = ::JsonSchemaSerializeChildList;
  };

  template <>
  struct JsonSchemaSerializeTypes::type_info<2>
  {
    using type = ::JsonSchemaSerializeMessage;
  };

}

