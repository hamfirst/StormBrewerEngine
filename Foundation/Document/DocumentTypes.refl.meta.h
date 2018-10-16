#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "DocumentTypes.refl.h"


template <>
struct StormReflTypeInfo<DocumentLink>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DocumentLink"; }
  static constexpr auto GetNameHash() { return 0x106E0629; }
  static DocumentLink & GetDefault() { static DocumentLink def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DocumentLink *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DocumentLink *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DocumentLink *>(ptr);
    if(typeid(DocumentLink).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DocumentLink *>(ptr);
    if(typeid(DocumentLink).hash_code() == type_id_hash) return c;
    return nullptr;
  }

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
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct DocumentTypes::type_info<0>
  {
    using type = ::DocumentLink;
  };

}

