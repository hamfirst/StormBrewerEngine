#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "DocumentServerVCSGit.refl.h"
#include "DocumentServerVCS.refl.meta.h"


template <>
struct StormReflTypeInfo<DocumentServerVCSGitInitData>
{
  using MyBase = DocumentServerVCSInitData;
  static constexpr int fields_n = 1 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "DocumentServerVCSGitInitData"; }
  static constexpr auto GetNameHash() { return 0x587148DA; }
  static DocumentServerVCSGitInitData & GetDefault() { static DocumentServerVCSGitInitData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DocumentServerVCSGitInitData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xC00348A6 == type_name_hash) return static_cast<DocumentServerVCSInitData *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DocumentServerVCSGitInitData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xC00348A6 == type_name_hash) return static_cast<const DocumentServerVCSInitData *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DocumentServerVCSGitInitData *>(ptr);
    if(typeid(DocumentServerVCSGitInitData).hash_code() == type_id_hash) return c;
    if(typeid(DocumentServerVCSInitData).hash_code() == type_id_hash) return static_cast<DocumentServerVCSInitData *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DocumentServerVCSGitInitData *>(ptr);
    if(typeid(DocumentServerVCSGitInitData).hash_code() == type_id_hash) return c;
    if(typeid(DocumentServerVCSInitData).hash_code() == type_id_hash) return static_cast<const DocumentServerVCSInitData *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DocumentServerVCSGitInitData>::field_data_static<0 + StormReflTypeInfo<DocumentServerVCSInitData>::fields_n>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "RootPath"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x700D1773; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<DocumentServerVCSInitData>::fields_n; }
  static constexpr auto GetMemberPtr() { return &DocumentServerVCSGitInitData::RootPath; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DocumentServerVCSGitInitData *>(obj); return &ptr->RootPath; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DocumentServerVCSGitInitData *>(obj); return &ptr->RootPath; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerVCSGitInitData>::field_data<0 + StormReflTypeInfo<DocumentServerVCSInitData>::fields_n, Self> : public StormReflTypeInfo<DocumentServerVCSGitInitData>::field_data_static<0 + StormReflTypeInfo<DocumentServerVCSInitData>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.RootPath; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.RootPath; }
  void SetDefault() { self.RootPath = StormReflTypeInfo<DocumentServerVCSGitInitData>::GetDefault().RootPath; }
};

namespace StormReflFileInfo
{
  struct DocumentServerVCSGit
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct DocumentServerVCSGit::type_info<0>
  {
    using type = ::DocumentServerVCSGitInitData;
  };

}

