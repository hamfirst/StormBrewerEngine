#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "ServerManager.refl.h"


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
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "iat"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x93C9C67E; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
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
  match_const_t<Self, std::string> & Get() { return self.iat; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.iat; }
  void SetDefault() { self.iat = StormReflTypeInfo<GoogleAssertionPayload>::GetDefault().iat; }
};

template <>
struct StormReflTypeInfo<GoogleAssertionPayload>::field_data_static<4>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "exp"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06BE521B; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
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
  match_const_t<Self, std::string> & Get() { return self.exp; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.exp; }
  void SetDefault() { self.exp = StormReflTypeInfo<GoogleAssertionPayload>::GetDefault().exp; }
};

template <>
struct StormReflTypeInfo<ServerListGame>
{
  using MyBase = void;
  static constexpr int fields_n = 7;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ServerListGame"; }
  static constexpr auto GetNameHash() { return 0xEDD5FB2A; }
  static constexpr bool HasDefault() { return true; }
  static ServerListGame & GetDefault() { static ServerListGame def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ServerListGame *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ServerListGame *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ServerListGame *>(ptr);
    if(typeid(ServerListGame).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ServerListGame *>(ptr);
    if(typeid(ServerListGame).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ServerListGame>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_MaxPlayers"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0D18B4FD; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &ServerListGame::m_MaxPlayers; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ServerListGame *>(obj); return &ptr->m_MaxPlayers; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ServerListGame *>(obj); return &ptr->m_MaxPlayers; }
};

template <typename Self>
struct StormReflTypeInfo<ServerListGame>::field_data<0, Self> : public StormReflTypeInfo<ServerListGame>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_MaxPlayers; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_MaxPlayers; }
  void SetDefault() { self.m_MaxPlayers = StormReflTypeInfo<ServerListGame>::GetDefault().m_MaxPlayers; }
};

template <>
struct StormReflTypeInfo<ServerListGame>::field_data_static<1>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_CurPlayers"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x733D8BFB; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &ServerListGame::m_CurPlayers; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ServerListGame *>(obj); return &ptr->m_CurPlayers; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ServerListGame *>(obj); return &ptr->m_CurPlayers; }
};

template <typename Self>
struct StormReflTypeInfo<ServerListGame>::field_data<1, Self> : public StormReflTypeInfo<ServerListGame>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_CurPlayers; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_CurPlayers; }
  void SetDefault() { self.m_CurPlayers = StormReflTypeInfo<ServerListGame>::GetDefault().m_CurPlayers; }
};

template <>
struct StormReflTypeInfo<ServerListGame>::field_data_static<2>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_CurObservers"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xBF51EB7C; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &ServerListGame::m_CurObservers; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ServerListGame *>(obj); return &ptr->m_CurObservers; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ServerListGame *>(obj); return &ptr->m_CurObservers; }
};

template <typename Self>
struct StormReflTypeInfo<ServerListGame>::field_data<2, Self> : public StormReflTypeInfo<ServerListGame>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_CurObservers; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_CurObservers; }
  void SetDefault() { self.m_CurObservers = StormReflTypeInfo<ServerListGame>::GetDefault().m_CurObservers; }
};

template <>
struct StormReflTypeInfo<ServerListGame>::field_data_static<3>
{
  using member_type = RBool; // RBool
  static constexpr auto GetName() { return "m_Started"; }
  static constexpr auto GetType() { return "RBool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2164E30F; }
  static constexpr unsigned GetTypeNameHash() { return 0x50062D06; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &ServerListGame::m_Started; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ServerListGame *>(obj); return &ptr->m_Started; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ServerListGame *>(obj); return &ptr->m_Started; }
};

template <typename Self>
struct StormReflTypeInfo<ServerListGame>::field_data<3, Self> : public StormReflTypeInfo<ServerListGame>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RBool> & Get() { return self.m_Started; }
  std::add_const_t<std::remove_reference_t<RBool>> & Get() const { return self.m_Started; }
  void SetDefault() { self.m_Started = StormReflTypeInfo<ServerListGame>::GetDefault().m_Started; }
};

template <>
struct StormReflTypeInfo<ServerListGame>::field_data_static<4>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &ServerListGame::m_Name; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ServerListGame *>(obj); return &ptr->m_Name; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ServerListGame *>(obj); return &ptr->m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<ServerListGame>::field_data<4, Self> : public StormReflTypeInfo<ServerListGame>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<ServerListGame>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<ServerListGame>::field_data_static<5>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Map"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x604F6E5C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &ServerListGame::m_Map; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ServerListGame *>(obj); return &ptr->m_Map; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ServerListGame *>(obj); return &ptr->m_Map; }
};

template <typename Self>
struct StormReflTypeInfo<ServerListGame>::field_data<5, Self> : public StormReflTypeInfo<ServerListGame>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Map; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Map; }
  void SetDefault() { self.m_Map = StormReflTypeInfo<ServerListGame>::GetDefault().m_Map; }
};

template <>
struct StormReflTypeInfo<ServerListGame>::field_data_static<6>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_PasswordProtected"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x536AB58A; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &ServerListGame::m_PasswordProtected; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ServerListGame *>(obj); return &ptr->m_PasswordProtected; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ServerListGame *>(obj); return &ptr->m_PasswordProtected; }
};

template <typename Self>
struct StormReflTypeInfo<ServerListGame>::field_data<6, Self> : public StormReflTypeInfo<ServerListGame>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_PasswordProtected; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_PasswordProtected; }
  void SetDefault() { self.m_PasswordProtected = StormReflTypeInfo<ServerListGame>::GetDefault().m_PasswordProtected; }
};

template <>
struct StormReflTypeInfo<ServerListServer>
{
  using MyBase = void;
  static constexpr int fields_n = 5;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ServerListServer"; }
  static constexpr auto GetNameHash() { return 0xD9812BC9; }
  static constexpr bool HasDefault() { return true; }
  static ServerListServer & GetDefault() { static ServerListServer def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ServerListServer *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ServerListServer *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ServerListServer *>(ptr);
    if(typeid(ServerListServer).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ServerListServer *>(ptr);
    if(typeid(ServerListServer).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ServerListServer>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &ServerListServer::m_Name; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ServerListServer *>(obj); return &ptr->m_Name; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ServerListServer *>(obj); return &ptr->m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<ServerListServer>::field_data<0, Self> : public StormReflTypeInfo<ServerListServer>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<ServerListServer>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<ServerListServer>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Location"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA8B25DE5; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &ServerListServer::m_Location; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ServerListServer *>(obj); return &ptr->m_Location; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ServerListServer *>(obj); return &ptr->m_Location; }
};

template <typename Self>
struct StormReflTypeInfo<ServerListServer>::field_data<1, Self> : public StormReflTypeInfo<ServerListServer>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Location; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Location; }
  void SetDefault() { self.m_Location = StormReflTypeInfo<ServerListServer>::GetDefault().m_Location; }
};

template <>
struct StormReflTypeInfo<ServerListServer>::field_data_static<2>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Host"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF1BA86E2; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &ServerListServer::m_Host; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ServerListServer *>(obj); return &ptr->m_Host; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ServerListServer *>(obj); return &ptr->m_Host; }
};

template <typename Self>
struct StormReflTypeInfo<ServerListServer>::field_data<2, Self> : public StormReflTypeInfo<ServerListServer>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Host; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Host; }
  void SetDefault() { self.m_Host = StormReflTypeInfo<ServerListServer>::GetDefault().m_Host; }
};

template <>
struct StormReflTypeInfo<ServerListServer>::field_data_static<3>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_PingPort"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFA7B7B78; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &ServerListServer::m_PingPort; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ServerListServer *>(obj); return &ptr->m_PingPort; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ServerListServer *>(obj); return &ptr->m_PingPort; }
};

template <typename Self>
struct StormReflTypeInfo<ServerListServer>::field_data<3, Self> : public StormReflTypeInfo<ServerListServer>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_PingPort; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_PingPort; }
  void SetDefault() { self.m_PingPort = StormReflTypeInfo<ServerListServer>::GetDefault().m_PingPort; }
};

template <>
struct StormReflTypeInfo<ServerListServer>::field_data_static<4>
{
  using member_type = RMergeList<ServerListGame>; // RMergeList<ServerListGame>
  static constexpr auto GetName() { return "m_Games"; }
  static constexpr auto GetType() { return "RMergeList<ServerListGame>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x7215BB51; }
  static constexpr unsigned GetTypeNameHash() { return 0x21518502; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &ServerListServer::m_Games; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ServerListServer *>(obj); return &ptr->m_Games; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ServerListServer *>(obj); return &ptr->m_Games; }
};

template <typename Self>
struct StormReflTypeInfo<ServerListServer>::field_data<4, Self> : public StormReflTypeInfo<ServerListServer>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<ServerListGame>> & Get() { return self.m_Games; }
  std::add_const_t<std::remove_reference_t<RMergeList<ServerListGame>>> & Get() const { return self.m_Games; }
  void SetDefault() { self.m_Games = StormReflTypeInfo<ServerListServer>::GetDefault().m_Games; }
};

template <>
struct StormReflTypeInfo<ServerManager>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ServerManager"; }
  static constexpr auto GetNameHash() { return 0x06A88995; }
  static constexpr bool HasDefault() { return false; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ServerManager *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ServerManager *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ServerManager *>(ptr);
    if(typeid(ServerManager).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ServerManager *>(ptr);
    if(typeid(ServerManager).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ServerManager>::field_data_static<0>
{
  using member_type = RMap<DDSKey, ServerListServer>; // RMap<unsigned long, ServerListServer>
  static constexpr auto GetName() { return "m_ServerList"; }
  static constexpr auto GetType() { return "RMap<unsigned long, ServerListServer>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1DE1AD4B; }
  static constexpr unsigned GetTypeNameHash() { return 0xB3E4C01D; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &ServerManager::m_ServerList; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ServerManager *>(obj); return &ptr->m_ServerList; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ServerManager *>(obj); return &ptr->m_ServerList; }
};

template <typename Self>
struct StormReflTypeInfo<ServerManager>::field_data<0, Self> : public StormReflTypeInfo<ServerManager>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMap<DDSKey, ServerListServer>> & Get() { return self.m_ServerList; }
  std::add_const_t<std::remove_reference_t<RMap<DDSKey, ServerListServer>>> & Get() const { return self.m_ServerList; }
};

template <>
struct StormReflFuncInfo<ServerManager>
{
  using MyBase = void;
  static constexpr int funcs_n = 7;
  template <int N> struct func_data_static {};
};

template <>
struct StormReflFuncInfo<ServerManager>::func_data_static<0>
{
  using func_ptr_type = void (ServerManager::*)(DDSKey, std::string, std::string, std::string, int);
  using return_type = void;
  static constexpr int params_n = 5;
  static constexpr auto GetName() { return "AddServer"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xE8BBB43E; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 0; }
  static constexpr func_ptr_type GetFunctionPtr() { return &ServerManager::AddServer; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<ServerManager>::func_data_static<0>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "server_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xB459A1F3; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<ServerManager>::func_data_static<0>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "server_name"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xD5A30FE6; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<ServerManager>::func_data_static<0>::param_info<2>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "location"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x5E9E89CB; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<ServerManager>::func_data_static<0>::param_info<3>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "server_host"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x44A7621D; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<ServerManager>::func_data_static<0>::param_info<4>
{
  using param_type = int;
  static constexpr auto GetName() { return "ping_port"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xCFE0BE7B; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<ServerManager>::func_data_static<1>
{
  using func_ptr_type = void (ServerManager::*)(DDSKey);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "RemoveServer"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x72677305; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 1; }
  static constexpr func_ptr_type GetFunctionPtr() { return &ServerManager::RemoveServer; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<ServerManager>::func_data_static<1>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "server_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xB459A1F3; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<ServerManager>::func_data_static<2>
{
  using func_ptr_type = void (ServerManager::*)(DDSKey, int, std::string, std::string, int, int, bool);
  using return_type = void;
  static constexpr int params_n = 7;
  static constexpr auto GetName() { return "AddGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x229A7CDC; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 2; }
  static constexpr func_ptr_type GetFunctionPtr() { return &ServerManager::AddGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<ServerManager>::func_data_static<2>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "server_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xB459A1F3; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<ServerManager>::func_data_static<2>::param_info<1>
{
  using param_type = int;
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<ServerManager>::func_data_static<2>::param_info<2>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "name"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x5E237E06; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<ServerManager>::func_data_static<2>::param_info<3>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "map"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x93ADAABB; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<ServerManager>::func_data_static<2>::param_info<4>
{
  using param_type = int;
  static constexpr auto GetName() { return "cur_players"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x5BA099E8; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<ServerManager>::func_data_static<2>::param_info<5>
{
  using param_type = int;
  static constexpr auto GetName() { return "max_players"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xB2BD19E2; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<ServerManager>::func_data_static<2>::param_info<6>
{
  using param_type = bool;
  static constexpr auto GetName() { return "password"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetNameHash() { return 0x35C246D5; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
};

template <>
struct StormReflFuncInfo<ServerManager>::func_data_static<3>
{
  using func_ptr_type = void (ServerManager::*)(DDSKey, int, int, int);
  using return_type = void;
  static constexpr int params_n = 4;
  static constexpr auto GetName() { return "UpdateGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x5648F9FB; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 3; }
  static constexpr func_ptr_type GetFunctionPtr() { return &ServerManager::UpdateGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<ServerManager>::func_data_static<3>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "server_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xB459A1F3; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<ServerManager>::func_data_static<3>::param_info<1>
{
  using param_type = int;
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<ServerManager>::func_data_static<3>::param_info<2>
{
  using param_type = int;
  static constexpr auto GetName() { return "cur_players"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x5BA099E8; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<ServerManager>::func_data_static<3>::param_info<3>
{
  using param_type = int;
  static constexpr auto GetName() { return "cur_observer"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x0A76C6AA; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<ServerManager>::func_data_static<4>
{
  using func_ptr_type = void (ServerManager::*)(DDSKey, int);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "StartGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x40E81A4D; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 4; }
  static constexpr func_ptr_type GetFunctionPtr() { return &ServerManager::StartGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<ServerManager>::func_data_static<4>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "server_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xB459A1F3; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<ServerManager>::func_data_static<4>::param_info<1>
{
  using param_type = int;
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<ServerManager>::func_data_static<5>
{
  using func_ptr_type = void (ServerManager::*)(DDSKey, int);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "RemoveGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x507B24C1; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 5; }
  static constexpr func_ptr_type GetFunctionPtr() { return &ServerManager::RemoveGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<ServerManager>::func_data_static<5>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "server_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xB459A1F3; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<ServerManager>::func_data_static<5>::param_info<1>
{
  using param_type = int;
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<ServerManager>::func_data_static<6>
{
  using func_ptr_type = void (ServerManager::*)();
  using return_type = void;
  static constexpr int params_n = 0;
  static constexpr auto GetName() { return "HangUpAllServers"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x751F7D64; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 6; }
  static constexpr func_ptr_type GetFunctionPtr() { return &ServerManager::HangUpAllServers; }
  template <int i>
  struct param_info { };
};

namespace StormReflFileInfo
{
  struct ServerManager
  {
    static const int types_n = 6;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct ServerManager::type_info<0>
  {
    using type = ::GoogleCredentialsInfo;
  };

  template <>
  struct ServerManager::type_info<1>
  {
    using type = ::GoogleAssertionHeader;
  };

  template <>
  struct ServerManager::type_info<2>
  {
    using type = ::GoogleAssertionPayload;
  };

  template <>
  struct ServerManager::type_info<3>
  {
    using type = ::ServerListGame;
  };

  template <>
  struct ServerManager::type_info<4>
  {
    using type = ::ServerListServer;
  };

  template <>
  struct ServerManager::type_info<5>
  {
    using type = ::ServerManager;
  };

}

