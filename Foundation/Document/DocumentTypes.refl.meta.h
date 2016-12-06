#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "DocumentTypes.refl.h"


template <>
struct StormReflTypeInfo<DocumentSchemaError>
{
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DocumentSchemaError"; }
  static constexpr auto GetNameHash() { return 0x58408051; }
  static DocumentSchemaError & GetDefault() { static DocumentSchemaError def; return def; }
};

template <>
struct StormReflTypeInfo<DocumentSchemaError>::field_data_static<0>
{
  using member_type = size_t; // unsigned int
  static constexpr auto GetName() { return "m_Time"; }
  static constexpr auto GetType() { return "unsigned int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x51090D5A; }
  static constexpr unsigned GetTypeNameHash() { return 0x562EF932; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DocumentSchemaError::m_Time; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentSchemaError>::field_data<0, Self> : public StormReflTypeInfo<DocumentSchemaError>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, size_t> & Get() { return self.m_Time; }
  std::add_const_t<std::remove_reference_t<size_t>> & Get() const { return self.m_Time; }
  void SetDefault() { self.m_Time = StormReflTypeInfo<DocumentSchemaError>::GetDefault().m_Time; }
};

template <>
struct StormReflTypeInfo<DocumentSchemaError>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Path"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x35C91E10; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DocumentSchemaError::m_Path; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentSchemaError>::field_data<1, Self> : public StormReflTypeInfo<DocumentSchemaError>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Path; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Path; }
  void SetDefault() { self.m_Path = StormReflTypeInfo<DocumentSchemaError>::GetDefault().m_Path; }
};

template <>
struct StormReflTypeInfo<DocumentSchemaError>::field_data_static<2>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Data"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x936E667C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DocumentSchemaError::m_Data; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentSchemaError>::field_data<2, Self> : public StormReflTypeInfo<DocumentSchemaError>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Data; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Data; }
  void SetDefault() { self.m_Data = StormReflTypeInfo<DocumentSchemaError>::GetDefault().m_Data; }
};

template <>
struct StormReflTypeInfo<DocumentLink>
{
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DocumentLink"; }
  static constexpr auto GetNameHash() { return 0x106E0629; }
  static DocumentLink & GetDefault() { static DocumentLink def; return def; }
};

template <>
struct StormReflTypeInfo<DocumentLink>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_SourceAsset"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x7A9E87A4; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DocumentLink::m_SourceAsset; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentLink>::field_data<0, Self> : public StormReflTypeInfo<DocumentLink>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_SourceAsset; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_SourceAsset; }
  void SetDefault() { self.m_SourceAsset = StormReflTypeInfo<DocumentLink>::GetDefault().m_SourceAsset; }
};

template <>
struct StormReflTypeInfo<DocumentLink>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_RemotePath"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF028D554; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DocumentLink::m_RemotePath; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentLink>::field_data<1, Self> : public StormReflTypeInfo<DocumentLink>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_RemotePath; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_RemotePath; }
  void SetDefault() { self.m_RemotePath = StormReflTypeInfo<DocumentLink>::GetDefault().m_RemotePath; }
};

template <>
struct StormReflTypeInfo<DocumentLink>::field_data_static<2>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_LocalPath"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x26A31EF4; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DocumentLink::m_LocalPath; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentLink>::field_data<2, Self> : public StormReflTypeInfo<DocumentLink>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_LocalPath; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_LocalPath; }
  void SetDefault() { self.m_LocalPath = StormReflTypeInfo<DocumentLink>::GetDefault().m_LocalPath; }
};

namespace StormReflFileInfo
{
  struct DocumentTypes
  {
    static const int types_n = 2;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct DocumentTypes::type_info<0>
  {
    using type = ::DocumentSchemaError;
  };

  template <>
  struct DocumentTypes::type_info<1>
  {
    using type = ::DocumentLink;
  };

}

