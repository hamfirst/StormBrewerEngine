#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "GooglePlatform.refl.h"


template <>
struct StormReflTypeInfo<GoogleCredentialsInfo>
{
  using MyBase = void;
  static constexpr int fields_n = 10;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GoogleCredentialsInfo"; }
  static constexpr auto GetNameHash() { return 0xC6B9032A; }
  static constexpr bool HasDefault() { return true; }
  static GoogleCredentialsInfo & GetDefault() { static GoogleCredentialsInfo def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GoogleCredentialsInfo *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GoogleCredentialsInfo *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GoogleCredentialsInfo *>(ptr);
    if(typeid(GoogleCredentialsInfo).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GoogleCredentialsInfo *>(ptr);
    if(typeid(GoogleCredentialsInfo).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GoogleCredentialsInfo>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "type"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8CDE5729; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GoogleCredentialsInfo::type; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GoogleCredentialsInfo *>(obj); return &ptr->type; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GoogleCredentialsInfo *>(obj); return &ptr->type; }
};

template <typename Self>
struct StormReflTypeInfo<GoogleCredentialsInfo>::field_data<0, Self> : public StormReflTypeInfo<GoogleCredentialsInfo>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.type; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.type; }
  void SetDefault() { self.type = StormReflTypeInfo<GoogleCredentialsInfo>::GetDefault().type; }
};

template <>
struct StormReflTypeInfo<GoogleCredentialsInfo>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "project_id"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x166D1F9C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GoogleCredentialsInfo::project_id; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GoogleCredentialsInfo *>(obj); return &ptr->project_id; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GoogleCredentialsInfo *>(obj); return &ptr->project_id; }
};

template <typename Self>
struct StormReflTypeInfo<GoogleCredentialsInfo>::field_data<1, Self> : public StormReflTypeInfo<GoogleCredentialsInfo>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.project_id; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.project_id; }
  void SetDefault() { self.project_id = StormReflTypeInfo<GoogleCredentialsInfo>::GetDefault().project_id; }
};

template <>
struct StormReflTypeInfo<GoogleCredentialsInfo>::field_data_static<2>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "private_key_id"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x203AF3E2; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GoogleCredentialsInfo::private_key_id; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GoogleCredentialsInfo *>(obj); return &ptr->private_key_id; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GoogleCredentialsInfo *>(obj); return &ptr->private_key_id; }
};

template <typename Self>
struct StormReflTypeInfo<GoogleCredentialsInfo>::field_data<2, Self> : public StormReflTypeInfo<GoogleCredentialsInfo>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.private_key_id; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.private_key_id; }
  void SetDefault() { self.private_key_id = StormReflTypeInfo<GoogleCredentialsInfo>::GetDefault().private_key_id; }
};

template <>
struct StormReflTypeInfo<GoogleCredentialsInfo>::field_data_static<3>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "private_key"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF7F984A6; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &GoogleCredentialsInfo::private_key; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GoogleCredentialsInfo *>(obj); return &ptr->private_key; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GoogleCredentialsInfo *>(obj); return &ptr->private_key; }
};

template <typename Self>
struct StormReflTypeInfo<GoogleCredentialsInfo>::field_data<3, Self> : public StormReflTypeInfo<GoogleCredentialsInfo>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.private_key; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.private_key; }
  void SetDefault() { self.private_key = StormReflTypeInfo<GoogleCredentialsInfo>::GetDefault().private_key; }
};

template <>
struct StormReflTypeInfo<GoogleCredentialsInfo>::field_data_static<4>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "client_email"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x44FFE0C3; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &GoogleCredentialsInfo::client_email; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GoogleCredentialsInfo *>(obj); return &ptr->client_email; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GoogleCredentialsInfo *>(obj); return &ptr->client_email; }
};

template <typename Self>
struct StormReflTypeInfo<GoogleCredentialsInfo>::field_data<4, Self> : public StormReflTypeInfo<GoogleCredentialsInfo>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.client_email; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.client_email; }
  void SetDefault() { self.client_email = StormReflTypeInfo<GoogleCredentialsInfo>::GetDefault().client_email; }
};

template <>
struct StormReflTypeInfo<GoogleCredentialsInfo>::field_data_static<5>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "client_id"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x19EB6921; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &GoogleCredentialsInfo::client_id; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GoogleCredentialsInfo *>(obj); return &ptr->client_id; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GoogleCredentialsInfo *>(obj); return &ptr->client_id; }
};

template <typename Self>
struct StormReflTypeInfo<GoogleCredentialsInfo>::field_data<5, Self> : public StormReflTypeInfo<GoogleCredentialsInfo>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.client_id; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.client_id; }
  void SetDefault() { self.client_id = StormReflTypeInfo<GoogleCredentialsInfo>::GetDefault().client_id; }
};

template <>
struct StormReflTypeInfo<GoogleCredentialsInfo>::field_data_static<6>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "auth_uri"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x16F1845C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &GoogleCredentialsInfo::auth_uri; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GoogleCredentialsInfo *>(obj); return &ptr->auth_uri; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GoogleCredentialsInfo *>(obj); return &ptr->auth_uri; }
};

template <typename Self>
struct StormReflTypeInfo<GoogleCredentialsInfo>::field_data<6, Self> : public StormReflTypeInfo<GoogleCredentialsInfo>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.auth_uri; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.auth_uri; }
  void SetDefault() { self.auth_uri = StormReflTypeInfo<GoogleCredentialsInfo>::GetDefault().auth_uri; }
};

template <>
struct StormReflTypeInfo<GoogleCredentialsInfo>::field_data_static<7>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "token_uri"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5D340C7D; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &GoogleCredentialsInfo::token_uri; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GoogleCredentialsInfo *>(obj); return &ptr->token_uri; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GoogleCredentialsInfo *>(obj); return &ptr->token_uri; }
};

template <typename Self>
struct StormReflTypeInfo<GoogleCredentialsInfo>::field_data<7, Self> : public StormReflTypeInfo<GoogleCredentialsInfo>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.token_uri; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.token_uri; }
  void SetDefault() { self.token_uri = StormReflTypeInfo<GoogleCredentialsInfo>::GetDefault().token_uri; }
};

template <>
struct StormReflTypeInfo<GoogleCredentialsInfo>::field_data_static<8>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "auth_provider_x509_cert_url"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xACB1ADA7; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 8; }
  static constexpr auto GetMemberPtr() { return &GoogleCredentialsInfo::auth_provider_x509_cert_url; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GoogleCredentialsInfo *>(obj); return &ptr->auth_provider_x509_cert_url; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GoogleCredentialsInfo *>(obj); return &ptr->auth_provider_x509_cert_url; }
};

template <typename Self>
struct StormReflTypeInfo<GoogleCredentialsInfo>::field_data<8, Self> : public StormReflTypeInfo<GoogleCredentialsInfo>::field_data_static<8>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.auth_provider_x509_cert_url; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.auth_provider_x509_cert_url; }
  void SetDefault() { self.auth_provider_x509_cert_url = StormReflTypeInfo<GoogleCredentialsInfo>::GetDefault().auth_provider_x509_cert_url; }
};

template <>
struct StormReflTypeInfo<GoogleCredentialsInfo>::field_data_static<9>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "client_x509_cert_url"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x50D35395; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 9; }
  static constexpr auto GetMemberPtr() { return &GoogleCredentialsInfo::client_x509_cert_url; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GoogleCredentialsInfo *>(obj); return &ptr->client_x509_cert_url; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GoogleCredentialsInfo *>(obj); return &ptr->client_x509_cert_url; }
};

template <typename Self>
struct StormReflTypeInfo<GoogleCredentialsInfo>::field_data<9, Self> : public StormReflTypeInfo<GoogleCredentialsInfo>::field_data_static<9>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.client_x509_cert_url; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.client_x509_cert_url; }
  void SetDefault() { self.client_x509_cert_url = StormReflTypeInfo<GoogleCredentialsInfo>::GetDefault().client_x509_cert_url; }
};

template <>
struct StormReflTypeInfo<GooglePlatformSettings>
{
  using MyBase = void;
  static constexpr int fields_n = 5;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GooglePlatformSettings"; }
  static constexpr auto GetNameHash() { return 0xA01D0967; }
  static constexpr bool HasDefault() { return true; }
  static GooglePlatformSettings & GetDefault() { static GooglePlatformSettings def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GooglePlatformSettings *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GooglePlatformSettings *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GooglePlatformSettings *>(ptr);
    if(typeid(GooglePlatformSettings).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GooglePlatformSettings *>(ptr);
    if(typeid(GooglePlatformSettings).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GooglePlatformSettings>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "project_id"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x166D1F9C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GooglePlatformSettings::project_id; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GooglePlatformSettings *>(obj); return &ptr->project_id; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GooglePlatformSettings *>(obj); return &ptr->project_id; }
};

template <typename Self>
struct StormReflTypeInfo<GooglePlatformSettings>::field_data<0, Self> : public StormReflTypeInfo<GooglePlatformSettings>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.project_id; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.project_id; }
  void SetDefault() { self.project_id = StormReflTypeInfo<GooglePlatformSettings>::GetDefault().project_id; }
};

template <>
struct StormReflTypeInfo<GooglePlatformSettings>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "service_email"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x4EE09193; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GooglePlatformSettings::service_email; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GooglePlatformSettings *>(obj); return &ptr->service_email; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GooglePlatformSettings *>(obj); return &ptr->service_email; }
};

template <typename Self>
struct StormReflTypeInfo<GooglePlatformSettings>::field_data<1, Self> : public StormReflTypeInfo<GooglePlatformSettings>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.service_email; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.service_email; }
  void SetDefault() { self.service_email = StormReflTypeInfo<GooglePlatformSettings>::GetDefault().service_email; }
};

template <>
struct StormReflTypeInfo<GooglePlatformSettings>::field_data_static<2>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "instance_type"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA4D407E2; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GooglePlatformSettings::instance_type; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GooglePlatformSettings *>(obj); return &ptr->instance_type; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GooglePlatformSettings *>(obj); return &ptr->instance_type; }
};

template <typename Self>
struct StormReflTypeInfo<GooglePlatformSettings>::field_data<2, Self> : public StormReflTypeInfo<GooglePlatformSettings>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.instance_type; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.instance_type; }
  void SetDefault() { self.instance_type = StormReflTypeInfo<GooglePlatformSettings>::GetDefault().instance_type; }
};

template <>
struct StormReflTypeInfo<GooglePlatformSettings>::field_data_static<3>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "instance_tags"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x47B6C4ED; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &GooglePlatformSettings::instance_tags; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GooglePlatformSettings *>(obj); return &ptr->instance_tags; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GooglePlatformSettings *>(obj); return &ptr->instance_tags; }
};

template <typename Self>
struct StormReflTypeInfo<GooglePlatformSettings>::field_data<3, Self> : public StormReflTypeInfo<GooglePlatformSettings>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.instance_tags; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.instance_tags; }
  void SetDefault() { self.instance_tags = StormReflTypeInfo<GooglePlatformSettings>::GetDefault().instance_tags; }
};

template <>
struct StormReflTypeInfo<GooglePlatformSettings>::field_data_static<4>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "max_games_per_instance"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDD61E6DB; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &GooglePlatformSettings::max_games_per_instance; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GooglePlatformSettings *>(obj); return &ptr->max_games_per_instance; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GooglePlatformSettings *>(obj); return &ptr->max_games_per_instance; }
};

template <typename Self>
struct StormReflTypeInfo<GooglePlatformSettings>::field_data<4, Self> : public StormReflTypeInfo<GooglePlatformSettings>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.max_games_per_instance; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.max_games_per_instance; }
  void SetDefault() { self.max_games_per_instance = StormReflTypeInfo<GooglePlatformSettings>::GetDefault().max_games_per_instance; }
};

template <>
struct StormReflTypeInfo<GoogleAssertionHeader>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GoogleAssertionHeader"; }
  static constexpr auto GetNameHash() { return 0xF539629B; }
  static constexpr bool HasDefault() { return true; }
  static GoogleAssertionHeader & GetDefault() { static GoogleAssertionHeader def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GoogleAssertionHeader *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GoogleAssertionHeader *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GoogleAssertionHeader *>(ptr);
    if(typeid(GoogleAssertionHeader).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GoogleAssertionHeader *>(ptr);
    if(typeid(GoogleAssertionHeader).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GoogleAssertionHeader>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "alg"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xACCAA855; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GoogleAssertionHeader::alg; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GoogleAssertionHeader *>(obj); return &ptr->alg; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GoogleAssertionHeader *>(obj); return &ptr->alg; }
};

template <typename Self>
struct StormReflTypeInfo<GoogleAssertionHeader>::field_data<0, Self> : public StormReflTypeInfo<GoogleAssertionHeader>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.alg; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.alg; }
  void SetDefault() { self.alg = StormReflTypeInfo<GoogleAssertionHeader>::GetDefault().alg; }
};

template <>
struct StormReflTypeInfo<GoogleAssertionHeader>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "kid"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x4523887C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GoogleAssertionHeader::kid; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GoogleAssertionHeader *>(obj); return &ptr->kid; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GoogleAssertionHeader *>(obj); return &ptr->kid; }
};

template <typename Self>
struct StormReflTypeInfo<GoogleAssertionHeader>::field_data<1, Self> : public StormReflTypeInfo<GoogleAssertionHeader>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.kid; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.kid; }
  void SetDefault() { self.kid = StormReflTypeInfo<GoogleAssertionHeader>::GetDefault().kid; }
};

template <>
struct StormReflTypeInfo<GoogleAssertionHeader>::field_data_static<2>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "typ"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0241AA1D; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GoogleAssertionHeader::typ; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GoogleAssertionHeader *>(obj); return &ptr->typ; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GoogleAssertionHeader *>(obj); return &ptr->typ; }
};

template <typename Self>
struct StormReflTypeInfo<GoogleAssertionHeader>::field_data<2, Self> : public StormReflTypeInfo<GoogleAssertionHeader>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.typ; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.typ; }
  void SetDefault() { self.typ = StormReflTypeInfo<GoogleAssertionHeader>::GetDefault().typ; }
};

template <>
struct StormReflTypeInfo<GoogleAssertionPayload>
{
  using MyBase = void;
  static constexpr int fields_n = 5;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GoogleAssertionPayload"; }
  static constexpr auto GetNameHash() { return 0xC9099935; }
  static constexpr bool HasDefault() { return true; }
  static GoogleAssertionPayload & GetDefault() { static GoogleAssertionPayload def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GoogleAssertionPayload *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GoogleAssertionPayload *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GoogleAssertionPayload *>(ptr);
    if(typeid(GoogleAssertionPayload).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GoogleAssertionPayload *>(ptr);
    if(typeid(GoogleAssertionPayload).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GoogleAssertionPayload>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "iss"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x7559230E; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GoogleAssertionPayload::iss; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GoogleAssertionPayload *>(obj); return &ptr->iss; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GoogleAssertionPayload *>(obj); return &ptr->iss; }
};

template <typename Self>
struct StormReflTypeInfo<GoogleAssertionPayload>::field_data<0, Self> : public StormReflTypeInfo<GoogleAssertionPayload>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.iss; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.iss; }
  void SetDefault() { self.iss = StormReflTypeInfo<GoogleAssertionPayload>::GetDefault().iss; }
};

template <>
struct StormReflTypeInfo<GoogleAssertionPayload>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "scope"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x00AF55D3; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GoogleAssertionPayload::scope; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GoogleAssertionPayload *>(obj); return &ptr->scope; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GoogleAssertionPayload *>(obj); return &ptr->scope; }
};

template <typename Self>
struct StormReflTypeInfo<GoogleAssertionPayload>::field_data<1, Self> : public StormReflTypeInfo<GoogleAssertionPayload>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.scope; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.scope; }
  void SetDefault() { self.scope = StormReflTypeInfo<GoogleAssertionPayload>::GetDefault().scope; }
};

template <>
struct StormReflTypeInfo<GoogleAssertionPayload>::field_data_static<2>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "aud"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAEC350F7; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GoogleAssertionPayload::aud; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GoogleAssertionPayload *>(obj); return &ptr->aud; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GoogleAssertionPayload *>(obj); return &ptr->aud; }
};

template <typename Self>
struct StormReflTypeInfo<GoogleAssertionPayload>::field_data<2, Self> : public StormReflTypeInfo<GoogleAssertionPayload>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.aud; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.aud; }
  void SetDefault() { self.aud = StormReflTypeInfo<GoogleAssertionPayload>::GetDefault().aud; }
};

template <>
struct StormReflTypeInfo<GoogleAssertionPayload>::field_data_static<3>
{
  using member_type = long; // long
  static constexpr auto GetName() { return "iat"; }
  static constexpr auto GetType() { return "long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x93C9C67E; }
  static constexpr unsigned GetTypeNameHash() { return 0x3B97A968; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &GoogleAssertionPayload::iat; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GoogleAssertionPayload *>(obj); return &ptr->iat; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GoogleAssertionPayload *>(obj); return &ptr->iat; }
};

template <typename Self>
struct StormReflTypeInfo<GoogleAssertionPayload>::field_data<3, Self> : public StormReflTypeInfo<GoogleAssertionPayload>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, long> & Get() { return self.iat; }
  std::add_const_t<std::remove_reference_t<long>> & Get() const { return self.iat; }
  void SetDefault() { self.iat = StormReflTypeInfo<GoogleAssertionPayload>::GetDefault().iat; }
};

template <>
struct StormReflTypeInfo<GoogleAssertionPayload>::field_data_static<4>
{
  using member_type = long; // long
  static constexpr auto GetName() { return "exp"; }
  static constexpr auto GetType() { return "long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06BE521B; }
  static constexpr unsigned GetTypeNameHash() { return 0x3B97A968; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &GoogleAssertionPayload::exp; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GoogleAssertionPayload *>(obj); return &ptr->exp; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GoogleAssertionPayload *>(obj); return &ptr->exp; }
};

template <typename Self>
struct StormReflTypeInfo<GoogleAssertionPayload>::field_data<4, Self> : public StormReflTypeInfo<GoogleAssertionPayload>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, long> & Get() { return self.exp; }
  std::add_const_t<std::remove_reference_t<long>> & Get() const { return self.exp; }
  void SetDefault() { self.exp = StormReflTypeInfo<GoogleAssertionPayload>::GetDefault().exp; }
};

template <>
struct StormReflTypeInfo<GoogleTokenResponse>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GoogleTokenResponse"; }
  static constexpr auto GetNameHash() { return 0x53A0427A; }
  static constexpr bool HasDefault() { return true; }
  static GoogleTokenResponse & GetDefault() { static GoogleTokenResponse def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GoogleTokenResponse *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GoogleTokenResponse *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GoogleTokenResponse *>(ptr);
    if(typeid(GoogleTokenResponse).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GoogleTokenResponse *>(ptr);
    if(typeid(GoogleTokenResponse).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GoogleTokenResponse>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "access_token"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB6A2DD68; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GoogleTokenResponse::access_token; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GoogleTokenResponse *>(obj); return &ptr->access_token; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GoogleTokenResponse *>(obj); return &ptr->access_token; }
};

template <typename Self>
struct StormReflTypeInfo<GoogleTokenResponse>::field_data<0, Self> : public StormReflTypeInfo<GoogleTokenResponse>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.access_token; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.access_token; }
  void SetDefault() { self.access_token = StormReflTypeInfo<GoogleTokenResponse>::GetDefault().access_token; }
};

template <>
struct StormReflTypeInfo<GoogleTokenResponse>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "token_type"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xEEDA624B; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GoogleTokenResponse::token_type; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GoogleTokenResponse *>(obj); return &ptr->token_type; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GoogleTokenResponse *>(obj); return &ptr->token_type; }
};

template <typename Self>
struct StormReflTypeInfo<GoogleTokenResponse>::field_data<1, Self> : public StormReflTypeInfo<GoogleTokenResponse>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.token_type; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.token_type; }
  void SetDefault() { self.token_type = StormReflTypeInfo<GoogleTokenResponse>::GetDefault().token_type; }
};

template <>
struct StormReflTypeInfo<GoogleTokenResponse>::field_data_static<2>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "expires_in"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3A26F090; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GoogleTokenResponse::expires_in; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GoogleTokenResponse *>(obj); return &ptr->expires_in; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GoogleTokenResponse *>(obj); return &ptr->expires_in; }
};

template <typename Self>
struct StormReflTypeInfo<GoogleTokenResponse>::field_data<2, Self> : public StormReflTypeInfo<GoogleTokenResponse>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.expires_in; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.expires_in; }
  void SetDefault() { self.expires_in = StormReflTypeInfo<GoogleTokenResponse>::GetDefault().expires_in; }
};

template <>
struct StormReflTypeInfo<GoogleInstanceElement>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GoogleInstanceElement"; }
  static constexpr auto GetNameHash() { return 0x6F37E532; }
  static constexpr bool HasDefault() { return true; }
  static GoogleInstanceElement & GetDefault() { static GoogleInstanceElement def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GoogleInstanceElement *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GoogleInstanceElement *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GoogleInstanceElement *>(ptr);
    if(typeid(GoogleInstanceElement).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GoogleInstanceElement *>(ptr);
    if(typeid(GoogleInstanceElement).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GoogleInstanceElement>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "id"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xBF396750; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GoogleInstanceElement::id; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GoogleInstanceElement *>(obj); return &ptr->id; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GoogleInstanceElement *>(obj); return &ptr->id; }
};

template <typename Self>
struct StormReflTypeInfo<GoogleInstanceElement>::field_data<0, Self> : public StormReflTypeInfo<GoogleInstanceElement>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.id; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.id; }
  void SetDefault() { self.id = StormReflTypeInfo<GoogleInstanceElement>::GetDefault().id; }
};

template <>
struct StormReflTypeInfo<GoogleInstanceElement>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "name"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5E237E06; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GoogleInstanceElement::name; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GoogleInstanceElement *>(obj); return &ptr->name; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GoogleInstanceElement *>(obj); return &ptr->name; }
};

template <typename Self>
struct StormReflTypeInfo<GoogleInstanceElement>::field_data<1, Self> : public StormReflTypeInfo<GoogleInstanceElement>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.name; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.name; }
  void SetDefault() { self.name = StormReflTypeInfo<GoogleInstanceElement>::GetDefault().name; }
};

template <>
struct StormReflTypeInfo<GoogleInstanceElement>::field_data_static<2>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "zone"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA0EBC007; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GoogleInstanceElement::zone; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GoogleInstanceElement *>(obj); return &ptr->zone; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GoogleInstanceElement *>(obj); return &ptr->zone; }
};

template <typename Self>
struct StormReflTypeInfo<GoogleInstanceElement>::field_data<2, Self> : public StormReflTypeInfo<GoogleInstanceElement>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.zone; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.zone; }
  void SetDefault() { self.zone = StormReflTypeInfo<GoogleInstanceElement>::GetDefault().zone; }
};

template <>
struct StormReflTypeInfo<GoogleInstanceList>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GoogleInstanceList"; }
  static constexpr auto GetNameHash() { return 0x902200EC; }
  static constexpr bool HasDefault() { return true; }
  static GoogleInstanceList & GetDefault() { static GoogleInstanceList def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GoogleInstanceList *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GoogleInstanceList *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GoogleInstanceList *>(ptr);
    if(typeid(GoogleInstanceList).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GoogleInstanceList *>(ptr);
    if(typeid(GoogleInstanceList).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GoogleInstanceList>::field_data_static<0>
{
  using member_type = std::vector<GoogleInstanceElement>; // std::vector<GoogleInstanceElement, std::allocator<GoogleInstanceElement> >
  static constexpr auto GetName() { return "items"; }
  static constexpr auto GetType() { return "std::vector<GoogleInstanceElement, std::allocator<GoogleInstanceElement> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE11EE94D; }
  static constexpr unsigned GetTypeNameHash() { return 0x2EB1398E; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GoogleInstanceList::items; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GoogleInstanceList *>(obj); return &ptr->items; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GoogleInstanceList *>(obj); return &ptr->items; }
};

template <typename Self>
struct StormReflTypeInfo<GoogleInstanceList>::field_data<0, Self> : public StormReflTypeInfo<GoogleInstanceList>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<GoogleInstanceElement>> & Get() { return self.items; }
  std::add_const_t<std::remove_reference_t<std::vector<GoogleInstanceElement>>> & Get() const { return self.items; }
  void SetDefault() { self.items = StormReflTypeInfo<GoogleInstanceList>::GetDefault().items; }
};

template <>
struct StormReflTypeInfo<GoogleInstanceList>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "nextPageToken"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD03C69D3; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GoogleInstanceList::nextPageToken; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GoogleInstanceList *>(obj); return &ptr->nextPageToken; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GoogleInstanceList *>(obj); return &ptr->nextPageToken; }
};

template <typename Self>
struct StormReflTypeInfo<GoogleInstanceList>::field_data<1, Self> : public StormReflTypeInfo<GoogleInstanceList>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.nextPageToken; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.nextPageToken; }
  void SetDefault() { self.nextPageToken = StormReflTypeInfo<GoogleInstanceList>::GetDefault().nextPageToken; }
};

template <>
struct StormReflTypeInfo<GoogleInstanceCreateResponse>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GoogleInstanceCreateResponse"; }
  static constexpr auto GetNameHash() { return 0xE8684C49; }
  static constexpr bool HasDefault() { return true; }
  static GoogleInstanceCreateResponse & GetDefault() { static GoogleInstanceCreateResponse def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GoogleInstanceCreateResponse *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GoogleInstanceCreateResponse *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GoogleInstanceCreateResponse *>(ptr);
    if(typeid(GoogleInstanceCreateResponse).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GoogleInstanceCreateResponse *>(ptr);
    if(typeid(GoogleInstanceCreateResponse).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GoogleInstanceCreateResponse>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "id"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xBF396750; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GoogleInstanceCreateResponse::id; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GoogleInstanceCreateResponse *>(obj); return &ptr->id; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GoogleInstanceCreateResponse *>(obj); return &ptr->id; }
};

template <typename Self>
struct StormReflTypeInfo<GoogleInstanceCreateResponse>::field_data<0, Self> : public StormReflTypeInfo<GoogleInstanceCreateResponse>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.id; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.id; }
  void SetDefault() { self.id = StormReflTypeInfo<GoogleInstanceCreateResponse>::GetDefault().id; }
};

template <>
struct StormReflTypeInfo<GoogleInstanceCreateResponse>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "name"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5E237E06; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GoogleInstanceCreateResponse::name; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GoogleInstanceCreateResponse *>(obj); return &ptr->name; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GoogleInstanceCreateResponse *>(obj); return &ptr->name; }
};

template <typename Self>
struct StormReflTypeInfo<GoogleInstanceCreateResponse>::field_data<1, Self> : public StormReflTypeInfo<GoogleInstanceCreateResponse>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.name; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.name; }
  void SetDefault() { self.name = StormReflTypeInfo<GoogleInstanceCreateResponse>::GetDefault().name; }
};

template <>
struct StormReflTypeInfo<GoogleInstanceCreateResponse>::field_data_static<2>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "zone"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA0EBC007; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GoogleInstanceCreateResponse::zone; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GoogleInstanceCreateResponse *>(obj); return &ptr->zone; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GoogleInstanceCreateResponse *>(obj); return &ptr->zone; }
};

template <typename Self>
struct StormReflTypeInfo<GoogleInstanceCreateResponse>::field_data<2, Self> : public StormReflTypeInfo<GoogleInstanceCreateResponse>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.zone; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.zone; }
  void SetDefault() { self.zone = StormReflTypeInfo<GoogleInstanceCreateResponse>::GetDefault().zone; }
};

namespace StormReflFileInfo
{
  struct GooglePlatform
  {
    static const int types_n = 8;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct GooglePlatform::type_info<0>
  {
    using type = ::GoogleCredentialsInfo;
  };

  template <>
  struct GooglePlatform::type_info<1>
  {
    using type = ::GooglePlatformSettings;
  };

  template <>
  struct GooglePlatform::type_info<2>
  {
    using type = ::GoogleAssertionHeader;
  };

  template <>
  struct GooglePlatform::type_info<3>
  {
    using type = ::GoogleAssertionPayload;
  };

  template <>
  struct GooglePlatform::type_info<4>
  {
    using type = ::GoogleTokenResponse;
  };

  template <>
  struct GooglePlatform::type_info<5>
  {
    using type = ::GoogleInstanceElement;
  };

  template <>
  struct GooglePlatform::type_info<6>
  {
    using type = ::GoogleInstanceList;
  };

  template <>
  struct GooglePlatform::type_info<7>
  {
    using type = ::GoogleInstanceCreateResponse;
  };

}

