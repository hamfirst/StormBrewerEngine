#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "Settings.refl.h"


template <>
struct StormReflTypeInfo<UploadSettings>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UploadSettings"; }
  static constexpr auto GetNameHash() { return 0x602841D8; }
  static constexpr bool HasDefault() { return true; }
  static UploadSettings & GetDefault() { static UploadSettings def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<UploadSettings *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const UploadSettings *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<UploadSettings *>(ptr);
    if(typeid(UploadSettings).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const UploadSettings *>(ptr);
    if(typeid(UploadSettings).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<UploadSettings>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_DistServerAddress"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x34DE83BA; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UploadSettings::m_DistServerAddress; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UploadSettings *>(obj); return &ptr->m_DistServerAddress; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UploadSettings *>(obj); return &ptr->m_DistServerAddress; }
};

template <typename Self>
struct StormReflTypeInfo<UploadSettings>::field_data<0, Self> : public StormReflTypeInfo<UploadSettings>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_DistServerAddress; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_DistServerAddress; }
  void SetDefault() { self.m_DistServerAddress = StormReflTypeInfo<UploadSettings>::GetDefault().m_DistServerAddress; }
};

template <>
struct StormReflTypeInfo<UploadSettings>::field_data_static<1>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_DistServerPort"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF62BF3F9; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UploadSettings::m_DistServerPort; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UploadSettings *>(obj); return &ptr->m_DistServerPort; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UploadSettings *>(obj); return &ptr->m_DistServerPort; }
};

template <typename Self>
struct StormReflTypeInfo<UploadSettings>::field_data<1, Self> : public StormReflTypeInfo<UploadSettings>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_DistServerPort; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_DistServerPort; }
  void SetDefault() { self.m_DistServerPort = StormReflTypeInfo<UploadSettings>::GetDefault().m_DistServerPort; }
};

template <>
struct StormReflTypeInfo<UploadSettings>::field_data_static<2>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_DistServerIdent"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5248063F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UploadSettings::m_DistServerIdent; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UploadSettings *>(obj); return &ptr->m_DistServerIdent; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UploadSettings *>(obj); return &ptr->m_DistServerIdent; }
};

template <typename Self>
struct StormReflTypeInfo<UploadSettings>::field_data<2, Self> : public StormReflTypeInfo<UploadSettings>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_DistServerIdent; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_DistServerIdent; }
  void SetDefault() { self.m_DistServerIdent = StormReflTypeInfo<UploadSettings>::GetDefault().m_DistServerIdent; }
};

template <>
struct StormReflTypeInfo<ServerSettings>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ServerSettings"; }
  static constexpr auto GetNameHash() { return 0xD761408A; }
  static constexpr bool HasDefault() { return true; }
  static ServerSettings & GetDefault() { static ServerSettings def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ServerSettings *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ServerSettings *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ServerSettings *>(ptr);
    if(typeid(ServerSettings).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ServerSettings *>(ptr);
    if(typeid(ServerSettings).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ServerSettings>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_DistServerPort"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF62BF3F9; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &ServerSettings::m_DistServerPort; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ServerSettings *>(obj); return &ptr->m_DistServerPort; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ServerSettings *>(obj); return &ptr->m_DistServerPort; }
};

template <typename Self>
struct StormReflTypeInfo<ServerSettings>::field_data<0, Self> : public StormReflTypeInfo<ServerSettings>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_DistServerPort; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_DistServerPort; }
  void SetDefault() { self.m_DistServerPort = StormReflTypeInfo<ServerSettings>::GetDefault().m_DistServerPort; }
};

template <>
struct StormReflTypeInfo<ServerSettings>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_DistServerIdent"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5248063F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &ServerSettings::m_DistServerIdent; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ServerSettings *>(obj); return &ptr->m_DistServerIdent; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ServerSettings *>(obj); return &ptr->m_DistServerIdent; }
};

template <typename Self>
struct StormReflTypeInfo<ServerSettings>::field_data<1, Self> : public StormReflTypeInfo<ServerSettings>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_DistServerIdent; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_DistServerIdent; }
  void SetDefault() { self.m_DistServerIdent = StormReflTypeInfo<ServerSettings>::GetDefault().m_DistServerIdent; }
};

namespace StormReflFileInfo
{
  struct Settings
  {
    static const int types_n = 2;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct Settings::type_info<0>
  {
    using type = ::UploadSettings;
  };

  template <>
  struct Settings::type_info<1>
  {
    using type = ::ServerSettings;
  };

}

