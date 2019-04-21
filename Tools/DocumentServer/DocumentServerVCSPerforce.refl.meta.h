#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "DocumentServerVCSPerforce.refl.h"
#include "DocumentServerVCS.refl.meta.h"


template <>
struct StormReflTypeInfo<DocumentServerVCSPerforceInitData>
{
  using MyBase = DocumentServerVCSInitData;
  static constexpr int fields_n = 5 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "DocumentServerVCSPerforceInitData"; }
  static constexpr auto GetNameHash() { return 0x2D4271A4; }
  static constexpr bool HasDefault() { return true; }
  static DocumentServerVCSPerforceInitData & GetDefault() { static DocumentServerVCSPerforceInitData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DocumentServerVCSPerforceInitData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xC00348A6 == type_name_hash) return static_cast<DocumentServerVCSInitData *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DocumentServerVCSPerforceInitData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xC00348A6 == type_name_hash) return static_cast<const DocumentServerVCSInitData *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DocumentServerVCSPerforceInitData *>(ptr);
    if(typeid(DocumentServerVCSPerforceInitData).hash_code() == type_id_hash) return c;
    if(typeid(DocumentServerVCSInitData).hash_code() == type_id_hash) return static_cast<DocumentServerVCSInitData *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DocumentServerVCSPerforceInitData *>(ptr);
    if(typeid(DocumentServerVCSPerforceInitData).hash_code() == type_id_hash) return c;
    if(typeid(DocumentServerVCSInitData).hash_code() == type_id_hash) return static_cast<const DocumentServerVCSInitData *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DocumentServerVCSPerforceInitData>::field_data_static<0 + StormReflTypeInfo<DocumentServerVCSInitData>::fields_n>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "RootPath"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x700D1773; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<DocumentServerVCSInitData>::fields_n; }
  static constexpr auto GetMemberPtr() { return &DocumentServerVCSPerforceInitData::RootPath; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DocumentServerVCSPerforceInitData *>(obj); return &ptr->RootPath; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DocumentServerVCSPerforceInitData *>(obj); return &ptr->RootPath; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerVCSPerforceInitData>::field_data<0 + StormReflTypeInfo<DocumentServerVCSInitData>::fields_n, Self> : public StormReflTypeInfo<DocumentServerVCSPerforceInitData>::field_data_static<0 + StormReflTypeInfo<DocumentServerVCSInitData>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.RootPath; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.RootPath; }
  void SetDefault() { self.RootPath = StormReflTypeInfo<DocumentServerVCSPerforceInitData>::GetDefault().RootPath; }
};

template <>
struct StormReflTypeInfo<DocumentServerVCSPerforceInitData>::field_data_static<1 + StormReflTypeInfo<DocumentServerVCSInitData>::fields_n>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "User"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2DA17977; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1 + StormReflTypeInfo<DocumentServerVCSInitData>::fields_n; }
  static constexpr auto GetMemberPtr() { return &DocumentServerVCSPerforceInitData::User; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DocumentServerVCSPerforceInitData *>(obj); return &ptr->User; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DocumentServerVCSPerforceInitData *>(obj); return &ptr->User; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerVCSPerforceInitData>::field_data<1 + StormReflTypeInfo<DocumentServerVCSInitData>::fields_n, Self> : public StormReflTypeInfo<DocumentServerVCSPerforceInitData>::field_data_static<1 + StormReflTypeInfo<DocumentServerVCSInitData>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.User; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.User; }
  void SetDefault() { self.User = StormReflTypeInfo<DocumentServerVCSPerforceInitData>::GetDefault().User; }
};

template <>
struct StormReflTypeInfo<DocumentServerVCSPerforceInitData>::field_data_static<2 + StormReflTypeInfo<DocumentServerVCSInitData>::fields_n>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "Password"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xCCB42483; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2 + StormReflTypeInfo<DocumentServerVCSInitData>::fields_n; }
  static constexpr auto GetMemberPtr() { return &DocumentServerVCSPerforceInitData::Password; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DocumentServerVCSPerforceInitData *>(obj); return &ptr->Password; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DocumentServerVCSPerforceInitData *>(obj); return &ptr->Password; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerVCSPerforceInitData>::field_data<2 + StormReflTypeInfo<DocumentServerVCSInitData>::fields_n, Self> : public StormReflTypeInfo<DocumentServerVCSPerforceInitData>::field_data_static<2 + StormReflTypeInfo<DocumentServerVCSInitData>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.Password; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.Password; }
  void SetDefault() { self.Password = StormReflTypeInfo<DocumentServerVCSPerforceInitData>::GetDefault().Password; }
};

template <>
struct StormReflTypeInfo<DocumentServerVCSPerforceInitData>::field_data_static<3 + StormReflTypeInfo<DocumentServerVCSInitData>::fields_n>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "Port"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE3A3F2F2; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3 + StormReflTypeInfo<DocumentServerVCSInitData>::fields_n; }
  static constexpr auto GetMemberPtr() { return &DocumentServerVCSPerforceInitData::Port; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DocumentServerVCSPerforceInitData *>(obj); return &ptr->Port; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DocumentServerVCSPerforceInitData *>(obj); return &ptr->Port; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerVCSPerforceInitData>::field_data<3 + StormReflTypeInfo<DocumentServerVCSInitData>::fields_n, Self> : public StormReflTypeInfo<DocumentServerVCSPerforceInitData>::field_data_static<3 + StormReflTypeInfo<DocumentServerVCSInitData>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.Port; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.Port; }
  void SetDefault() { self.Port = StormReflTypeInfo<DocumentServerVCSPerforceInitData>::GetDefault().Port; }
};

template <>
struct StormReflTypeInfo<DocumentServerVCSPerforceInitData>::field_data_static<4 + StormReflTypeInfo<DocumentServerVCSInitData>::fields_n>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "Client"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC0E80163; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4 + StormReflTypeInfo<DocumentServerVCSInitData>::fields_n; }
  static constexpr auto GetMemberPtr() { return &DocumentServerVCSPerforceInitData::Client; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DocumentServerVCSPerforceInitData *>(obj); return &ptr->Client; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DocumentServerVCSPerforceInitData *>(obj); return &ptr->Client; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerVCSPerforceInitData>::field_data<4 + StormReflTypeInfo<DocumentServerVCSInitData>::fields_n, Self> : public StormReflTypeInfo<DocumentServerVCSPerforceInitData>::field_data_static<4 + StormReflTypeInfo<DocumentServerVCSInitData>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.Client; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.Client; }
  void SetDefault() { self.Client = StormReflTypeInfo<DocumentServerVCSPerforceInitData>::GetDefault().Client; }
};

namespace StormReflFileInfo
{
  struct DocumentServerVCSPerforce
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct DocumentServerVCSPerforce::type_info<0>
  {
    using type = ::DocumentServerVCSPerforceInitData;
  };

}

