#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "UserConnectionMessages.refl.h"
#include "GameData.refl.meta.h"


template <>
struct StormReflTypeInfo<GeolocationResponse>
{
  using MyBase = void;
  static constexpr int fields_n = 14;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GeolocationResponse"; }
  static constexpr auto GetNameHash() { return 0xDAD3B341; }
  static GeolocationResponse & GetDefault() { static GeolocationResponse def; return def; }
};

template <>
struct StormReflTypeInfo<GeolocationResponse>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "as"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF433689F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GeolocationResponse::as; }
};

template <typename Self>
struct StormReflTypeInfo<GeolocationResponse>::field_data<0, Self> : public StormReflTypeInfo<GeolocationResponse>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.as; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.as; }
  void SetDefault() { self.as = StormReflTypeInfo<GeolocationResponse>::GetDefault().as; }
};

template <>
struct StormReflTypeInfo<GeolocationResponse>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "city"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2D5B0234; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GeolocationResponse::city; }
};

template <typename Self>
struct StormReflTypeInfo<GeolocationResponse>::field_data<1, Self> : public StormReflTypeInfo<GeolocationResponse>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.city; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.city; }
  void SetDefault() { self.city = StormReflTypeInfo<GeolocationResponse>::GetDefault().city; }
};

template <>
struct StormReflTypeInfo<GeolocationResponse>::field_data_static<2>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "country"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5373C966; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GeolocationResponse::country; }
};

template <typename Self>
struct StormReflTypeInfo<GeolocationResponse>::field_data<2, Self> : public StormReflTypeInfo<GeolocationResponse>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.country; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.country; }
  void SetDefault() { self.country = StormReflTypeInfo<GeolocationResponse>::GetDefault().country; }
};

template <>
struct StormReflTypeInfo<GeolocationResponse>::field_data_static<3>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "countryCode"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA164B0CD; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &GeolocationResponse::countryCode; }
};

template <typename Self>
struct StormReflTypeInfo<GeolocationResponse>::field_data<3, Self> : public StormReflTypeInfo<GeolocationResponse>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.countryCode; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.countryCode; }
  void SetDefault() { self.countryCode = StormReflTypeInfo<GeolocationResponse>::GetDefault().countryCode; }
};

template <>
struct StormReflTypeInfo<GeolocationResponse>::field_data_static<4>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "isp"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xEC5072B4; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &GeolocationResponse::isp; }
};

template <typename Self>
struct StormReflTypeInfo<GeolocationResponse>::field_data<4, Self> : public StormReflTypeInfo<GeolocationResponse>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.isp; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.isp; }
  void SetDefault() { self.isp = StormReflTypeInfo<GeolocationResponse>::GetDefault().isp; }
};

template <>
struct StormReflTypeInfo<GeolocationResponse>::field_data_static<5>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "lat"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x95020495; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &GeolocationResponse::lat; }
};

template <typename Self>
struct StormReflTypeInfo<GeolocationResponse>::field_data<5, Self> : public StormReflTypeInfo<GeolocationResponse>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.lat; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.lat; }
  void SetDefault() { self.lat = StormReflTypeInfo<GeolocationResponse>::GetDefault().lat; }
};

template <>
struct StormReflTypeInfo<GeolocationResponse>::field_data_static<6>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "lon"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF6E3D061; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &GeolocationResponse::lon; }
};

template <typename Self>
struct StormReflTypeInfo<GeolocationResponse>::field_data<6, Self> : public StormReflTypeInfo<GeolocationResponse>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.lon; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.lon; }
  void SetDefault() { self.lon = StormReflTypeInfo<GeolocationResponse>::GetDefault().lon; }
};

template <>
struct StormReflTypeInfo<GeolocationResponse>::field_data_static<7>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "org"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x7215BA80; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &GeolocationResponse::org; }
};

template <typename Self>
struct StormReflTypeInfo<GeolocationResponse>::field_data<7, Self> : public StormReflTypeInfo<GeolocationResponse>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.org; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.org; }
  void SetDefault() { self.org = StormReflTypeInfo<GeolocationResponse>::GetDefault().org; }
};

template <>
struct StormReflTypeInfo<GeolocationResponse>::field_data_static<8>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "query"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x24BDB5EB; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 8; }
  static constexpr auto GetMemberPtr() { return &GeolocationResponse::query; }
};

template <typename Self>
struct StormReflTypeInfo<GeolocationResponse>::field_data<8, Self> : public StormReflTypeInfo<GeolocationResponse>::field_data_static<8>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.query; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.query; }
  void SetDefault() { self.query = StormReflTypeInfo<GeolocationResponse>::GetDefault().query; }
};

template <>
struct StormReflTypeInfo<GeolocationResponse>::field_data_static<9>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "region"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0F62F176; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 9; }
  static constexpr auto GetMemberPtr() { return &GeolocationResponse::region; }
};

template <typename Self>
struct StormReflTypeInfo<GeolocationResponse>::field_data<9, Self> : public StormReflTypeInfo<GeolocationResponse>::field_data_static<9>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.region; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.region; }
  void SetDefault() { self.region = StormReflTypeInfo<GeolocationResponse>::GetDefault().region; }
};

template <>
struct StormReflTypeInfo<GeolocationResponse>::field_data_static<10>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "regionName"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC337232B; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 10; }
  static constexpr auto GetMemberPtr() { return &GeolocationResponse::regionName; }
};

template <typename Self>
struct StormReflTypeInfo<GeolocationResponse>::field_data<10, Self> : public StormReflTypeInfo<GeolocationResponse>::field_data_static<10>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.regionName; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.regionName; }
  void SetDefault() { self.regionName = StormReflTypeInfo<GeolocationResponse>::GetDefault().regionName; }
};

template <>
struct StormReflTypeInfo<GeolocationResponse>::field_data_static<11>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "status"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x7B00651C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 11; }
  static constexpr auto GetMemberPtr() { return &GeolocationResponse::status; }
};

template <typename Self>
struct StormReflTypeInfo<GeolocationResponse>::field_data<11, Self> : public StormReflTypeInfo<GeolocationResponse>::field_data_static<11>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.status; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.status; }
  void SetDefault() { self.status = StormReflTypeInfo<GeolocationResponse>::GetDefault().status; }
};

template <>
struct StormReflTypeInfo<GeolocationResponse>::field_data_static<12>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "timezone"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3701B297; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 12; }
  static constexpr auto GetMemberPtr() { return &GeolocationResponse::timezone; }
};

template <typename Self>
struct StormReflTypeInfo<GeolocationResponse>::field_data<12, Self> : public StormReflTypeInfo<GeolocationResponse>::field_data_static<12>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.timezone; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.timezone; }
  void SetDefault() { self.timezone = StormReflTypeInfo<GeolocationResponse>::GetDefault().timezone; }
};

template <>
struct StormReflTypeInfo<GeolocationResponse>::field_data_static<13>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "zip"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x421D9546; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 13; }
  static constexpr auto GetMemberPtr() { return &GeolocationResponse::zip; }
};

template <typename Self>
struct StormReflTypeInfo<GeolocationResponse>::field_data<13, Self> : public StormReflTypeInfo<GeolocationResponse>::field_data_static<13>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.zip; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.zip; }
  void SetDefault() { self.zip = StormReflTypeInfo<GeolocationResponse>::GetDefault().zip; }
};

template <>
struct StormReflTypeInfo<UserMessageBase>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserMessageBase"; }
  static constexpr auto GetNameHash() { return 0xCEAD4594; }
  static UserMessageBase & GetDefault() { static UserMessageBase def; return def; }
};

template <>
struct StormReflTypeInfo<UserMessageBase>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserMessageBase::c; }
};

template <typename Self>
struct StormReflTypeInfo<UserMessageBase>::field_data<0, Self> : public StormReflTypeInfo<UserMessageBase>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<UserMessageBase>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<UserVersionRequest>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserVersionRequest"; }
  static constexpr auto GetNameHash() { return 0xAC88544D; }
  static UserVersionRequest & GetDefault() { static UserVersionRequest def; return def; }
};

template <>
struct StormReflTypeInfo<UserVersionRequest>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserVersionRequest::c; }
};

template <typename Self>
struct StormReflTypeInfo<UserVersionRequest>::field_data<0, Self> : public StormReflTypeInfo<UserVersionRequest>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<UserVersionRequest>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<UserVersionRequest>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "sha"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3E67BF7A; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserVersionRequest::sha; }
};

template <typename Self>
struct StormReflTypeInfo<UserVersionRequest>::field_data<1, Self> : public StormReflTypeInfo<UserVersionRequest>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.sha; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.sha; }
  void SetDefault() { self.sha = StormReflTypeInfo<UserVersionRequest>::GetDefault().sha; }
};

template <>
struct StormReflTypeInfo<UserVersionRequest>::field_data_static<2>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "prefix"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x93B1868E; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UserVersionRequest::prefix; }
};

template <typename Self>
struct StormReflTypeInfo<UserVersionRequest>::field_data<2, Self> : public StormReflTypeInfo<UserVersionRequest>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.prefix; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.prefix; }
  void SetDefault() { self.prefix = StormReflTypeInfo<UserVersionRequest>::GetDefault().prefix; }
};

template <>
struct StormReflTypeInfo<UserMessageConnectionErrror>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserMessageConnectionErrror"; }
  static constexpr auto GetNameHash() { return 0x58670ED8; }
  static UserMessageConnectionErrror & GetDefault() { static UserMessageConnectionErrror def; return def; }
};

template <>
struct StormReflTypeInfo<UserMessageConnectionErrror>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserMessageConnectionErrror::c; }
};

template <typename Self>
struct StormReflTypeInfo<UserMessageConnectionErrror>::field_data<0, Self> : public StormReflTypeInfo<UserMessageConnectionErrror>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<UserMessageConnectionErrror>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<UserMessageConnectionErrror>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "msg"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x688A5FAF; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserMessageConnectionErrror::msg; }
};

template <typename Self>
struct StormReflTypeInfo<UserMessageConnectionErrror>::field_data<1, Self> : public StormReflTypeInfo<UserMessageConnectionErrror>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.msg; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.msg; }
  void SetDefault() { self.msg = StormReflTypeInfo<UserMessageConnectionErrror>::GetDefault().msg; }
};

template <>
struct StormReflTypeInfo<UserMessageRuntimeError>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserMessageRuntimeError"; }
  static constexpr auto GetNameHash() { return 0x776201DD; }
  static UserMessageRuntimeError & GetDefault() { static UserMessageRuntimeError def; return def; }
};

template <>
struct StormReflTypeInfo<UserMessageRuntimeError>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserMessageRuntimeError::c; }
};

template <typename Self>
struct StormReflTypeInfo<UserMessageRuntimeError>::field_data<0, Self> : public StormReflTypeInfo<UserMessageRuntimeError>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<UserMessageRuntimeError>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<UserMessageRuntimeError>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "msg"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x688A5FAF; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserMessageRuntimeError::msg; }
};

template <typename Self>
struct StormReflTypeInfo<UserMessageRuntimeError>::field_data<1, Self> : public StormReflTypeInfo<UserMessageRuntimeError>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.msg; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.msg; }
  void SetDefault() { self.msg = StormReflTypeInfo<UserMessageRuntimeError>::GetDefault().msg; }
};

template <>
struct StormReflTypeInfo<UserMessageVersionResponse>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserMessageVersionResponse"; }
  static constexpr auto GetNameHash() { return 0xD4E7307C; }
  static UserMessageVersionResponse & GetDefault() { static UserMessageVersionResponse def; return def; }
};

template <>
struct StormReflTypeInfo<UserMessageVersionResponse>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "ver"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x09BC4202; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserMessageVersionResponse::ver; }
};

template <typename Self>
struct StormReflTypeInfo<UserMessageVersionResponse>::field_data<0, Self> : public StormReflTypeInfo<UserMessageVersionResponse>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.ver; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.ver; }
  void SetDefault() { self.ver = StormReflTypeInfo<UserMessageVersionResponse>::GetDefault().ver; }
};

template <>
struct StormReflTypeInfo<UserMessageVersionResponse>::field_data_static<1>
{
  using member_type = uint32_t; // unsigned int
  static constexpr auto GetName() { return "sha"; }
  static constexpr auto GetType() { return "unsigned int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3E67BF7A; }
  static constexpr unsigned GetTypeNameHash() { return 0x562EF932; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserMessageVersionResponse::sha; }
};

template <typename Self>
struct StormReflTypeInfo<UserMessageVersionResponse>::field_data<1, Self> : public StormReflTypeInfo<UserMessageVersionResponse>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint32_t> & Get() { return self.sha; }
  std::add_const_t<std::remove_reference_t<uint32_t>> & Get() const { return self.sha; }
  void SetDefault() { self.sha = StormReflTypeInfo<UserMessageVersionResponse>::GetDefault().sha; }
};

template <>
struct StormReflTypeInfo<UserMessageIdentifyResponse>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserMessageIdentifyResponse"; }
  static constexpr auto GetNameHash() { return 0xA1566B1E; }
  static UserMessageIdentifyResponse & GetDefault() { static UserMessageIdentifyResponse def; return def; }
};

template <>
struct StormReflTypeInfo<UserMessageIdentifyResponse>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserMessageIdentifyResponse::c; }
};

template <typename Self>
struct StormReflTypeInfo<UserMessageIdentifyResponse>::field_data<0, Self> : public StormReflTypeInfo<UserMessageIdentifyResponse>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<UserMessageIdentifyResponse>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<UserMessageIdentifyResponse>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "token"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5F37A13B; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserMessageIdentifyResponse::token; }
};

template <typename Self>
struct StormReflTypeInfo<UserMessageIdentifyResponse>::field_data<1, Self> : public StormReflTypeInfo<UserMessageIdentifyResponse>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.token; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.token; }
  void SetDefault() { self.token = StormReflTypeInfo<UserMessageIdentifyResponse>::GetDefault().token; }
};

template <>
struct StormReflTypeInfo<UserMessageCreateName>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserMessageCreateName"; }
  static constexpr auto GetNameHash() { return 0xA936E8A6; }
  static UserMessageCreateName & GetDefault() { static UserMessageCreateName def; return def; }
};

template <>
struct StormReflTypeInfo<UserMessageCreateName>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "uname"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x887739B8; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserMessageCreateName::uname; }
};

template <typename Self>
struct StormReflTypeInfo<UserMessageCreateName>::field_data<0, Self> : public StormReflTypeInfo<UserMessageCreateName>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.uname; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.uname; }
  void SetDefault() { self.uname = StormReflTypeInfo<UserMessageCreateName>::GetDefault().uname; }
};

template <>
struct StormReflTypeInfo<UserLocalInfoUpdate>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserLocalInfoUpdate"; }
  static constexpr auto GetNameHash() { return 0xFAD3FEEA; }
  static UserLocalInfoUpdate & GetDefault() { static UserLocalInfoUpdate def; return def; }
};

template <>
struct StormReflTypeInfo<UserLocalInfoUpdate>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserLocalInfoUpdate::c; }
};

template <typename Self>
struct StormReflTypeInfo<UserLocalInfoUpdate>::field_data<0, Self> : public StormReflTypeInfo<UserLocalInfoUpdate>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<UserLocalInfoUpdate>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<UserLocalInfoUpdate>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "data"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xADF3F363; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserLocalInfoUpdate::data; }
};

template <typename Self>
struct StormReflTypeInfo<UserLocalInfoUpdate>::field_data<1, Self> : public StormReflTypeInfo<UserLocalInfoUpdate>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.data; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.data; }
  void SetDefault() { self.data = StormReflTypeInfo<UserLocalInfoUpdate>::GetDefault().data; }
};

template <>
struct StormReflTypeInfo<UserGamePreviewUpdate>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserGamePreviewUpdate"; }
  static constexpr auto GetNameHash() { return 0xA22031D9; }
  static UserGamePreviewUpdate & GetDefault() { static UserGamePreviewUpdate def; return def; }
};

template <>
struct StormReflTypeInfo<UserGamePreviewUpdate>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserGamePreviewUpdate::c; }
};

template <typename Self>
struct StormReflTypeInfo<UserGamePreviewUpdate>::field_data<0, Self> : public StormReflTypeInfo<UserGamePreviewUpdate>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<UserGamePreviewUpdate>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<UserGamePreviewUpdate>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "data"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xADF3F363; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserGamePreviewUpdate::data; }
};

template <typename Self>
struct StormReflTypeInfo<UserGamePreviewUpdate>::field_data<1, Self> : public StormReflTypeInfo<UserGamePreviewUpdate>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.data; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.data; }
  void SetDefault() { self.data = StormReflTypeInfo<UserGamePreviewUpdate>::GetDefault().data; }
};

template <>
struct StormReflTypeInfo<UserGamePreviewUpdate>::field_data_static<2>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "request_id"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x427EB8A5; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UserGamePreviewUpdate::request_id; }
};

template <typename Self>
struct StormReflTypeInfo<UserGamePreviewUpdate>::field_data<2, Self> : public StormReflTypeInfo<UserGamePreviewUpdate>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.request_id; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.request_id; }
  void SetDefault() { self.request_id = StormReflTypeInfo<UserGamePreviewUpdate>::GetDefault().request_id; }
};

template <>
struct StormReflTypeInfo<UserGamePreviewCancel>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserGamePreviewCancel"; }
  static constexpr auto GetNameHash() { return 0x6C13C1D3; }
  static UserGamePreviewCancel & GetDefault() { static UserGamePreviewCancel def; return def; }
};

template <>
struct StormReflTypeInfo<UserGamePreviewCancel>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserGamePreviewCancel::c; }
};

template <typename Self>
struct StormReflTypeInfo<UserGamePreviewCancel>::field_data<0, Self> : public StormReflTypeInfo<UserGamePreviewCancel>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<UserGamePreviewCancel>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<UserGamePreviewCancel>::field_data_static<1>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "request_id"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x427EB8A5; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserGamePreviewCancel::request_id; }
};

template <typename Self>
struct StormReflTypeInfo<UserGamePreviewCancel>::field_data<1, Self> : public StormReflTypeInfo<UserGamePreviewCancel>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.request_id; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.request_id; }
  void SetDefault() { self.request_id = StormReflTypeInfo<UserGamePreviewCancel>::GetDefault().request_id; }
};

template <>
struct StormReflTypeInfo<UserGameInfoUpdate>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserGameInfoUpdate"; }
  static constexpr auto GetNameHash() { return 0x1E73577E; }
  static UserGameInfoUpdate & GetDefault() { static UserGameInfoUpdate def; return def; }
};

template <>
struct StormReflTypeInfo<UserGameInfoUpdate>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserGameInfoUpdate::c; }
};

template <typename Self>
struct StormReflTypeInfo<UserGameInfoUpdate>::field_data<0, Self> : public StormReflTypeInfo<UserGameInfoUpdate>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<UserGameInfoUpdate>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<UserGameInfoUpdate>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "data"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xADF3F363; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserGameInfoUpdate::data; }
};

template <typename Self>
struct StormReflTypeInfo<UserGameInfoUpdate>::field_data<1, Self> : public StormReflTypeInfo<UserGameInfoUpdate>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.data; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.data; }
  void SetDefault() { self.data = StormReflTypeInfo<UserGameInfoUpdate>::GetDefault().data; }
};

template <>
struct StormReflTypeInfo<UserGameInfoUpdate>::field_data_static<2>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UserGameInfoUpdate::game_id; }
};

template <typename Self>
struct StormReflTypeInfo<UserGameInfoUpdate>::field_data<2, Self> : public StormReflTypeInfo<UserGameInfoUpdate>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.game_id; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.game_id; }
  void SetDefault() { self.game_id = StormReflTypeInfo<UserGameInfoUpdate>::GetDefault().game_id; }
};

template <>
struct StormReflTypeInfo<UserChannelInfoUpdate>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserChannelInfoUpdate"; }
  static constexpr auto GetNameHash() { return 0xDFEB309E; }
  static UserChannelInfoUpdate & GetDefault() { static UserChannelInfoUpdate def; return def; }
};

template <>
struct StormReflTypeInfo<UserChannelInfoUpdate>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserChannelInfoUpdate::c; }
};

template <typename Self>
struct StormReflTypeInfo<UserChannelInfoUpdate>::field_data<0, Self> : public StormReflTypeInfo<UserChannelInfoUpdate>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<UserChannelInfoUpdate>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<UserChannelInfoUpdate>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "data"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xADF3F363; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserChannelInfoUpdate::data; }
};

template <typename Self>
struct StormReflTypeInfo<UserChannelInfoUpdate>::field_data<1, Self> : public StormReflTypeInfo<UserChannelInfoUpdate>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.data; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.data; }
  void SetDefault() { self.data = StormReflTypeInfo<UserChannelInfoUpdate>::GetDefault().data; }
};

template <>
struct StormReflTypeInfo<UserChannelInfoUpdate>::field_data_static<2>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "channel_id"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x72F5A1AA; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UserChannelInfoUpdate::channel_id; }
};

template <typename Self>
struct StormReflTypeInfo<UserChannelInfoUpdate>::field_data<2, Self> : public StormReflTypeInfo<UserChannelInfoUpdate>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.channel_id; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.channel_id; }
  void SetDefault() { self.channel_id = StormReflTypeInfo<UserChannelInfoUpdate>::GetDefault().channel_id; }
};

template <>
struct StormReflTypeInfo<UserMessageRelocate>
{
  using MyBase = void;
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserMessageRelocate"; }
  static constexpr auto GetNameHash() { return 0x248BA6DF; }
  static UserMessageRelocate & GetDefault() { static UserMessageRelocate def; return def; }
};

template <>
struct StormReflTypeInfo<UserMessageRelocate>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserMessageRelocate::c; }
};

template <typename Self>
struct StormReflTypeInfo<UserMessageRelocate>::field_data<0, Self> : public StormReflTypeInfo<UserMessageRelocate>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<UserMessageRelocate>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<UserMessageRelocate>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "new_host"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3BCAA720; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserMessageRelocate::new_host; }
};

template <typename Self>
struct StormReflTypeInfo<UserMessageRelocate>::field_data<1, Self> : public StormReflTypeInfo<UserMessageRelocate>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.new_host; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.new_host; }
  void SetDefault() { self.new_host = StormReflTypeInfo<UserMessageRelocate>::GetDefault().new_host; }
};

template <>
struct StormReflTypeInfo<UserMessageRelocate>::field_data_static<2>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "new_port"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB77CE911; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UserMessageRelocate::new_port; }
};

template <typename Self>
struct StormReflTypeInfo<UserMessageRelocate>::field_data<2, Self> : public StormReflTypeInfo<UserMessageRelocate>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.new_port; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.new_port; }
  void SetDefault() { self.new_port = StormReflTypeInfo<UserMessageRelocate>::GetDefault().new_port; }
};

template <>
struct StormReflTypeInfo<UserMessageRelocate>::field_data_static<3>
{
  using member_type = uint64_t; // unsigned long long
  static constexpr auto GetName() { return "relocation_token"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3D14BB9E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &UserMessageRelocate::relocation_token; }
};

template <typename Self>
struct StormReflTypeInfo<UserMessageRelocate>::field_data<3, Self> : public StormReflTypeInfo<UserMessageRelocate>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint64_t> & Get() { return self.relocation_token; }
  std::add_const_t<std::remove_reference_t<uint64_t>> & Get() const { return self.relocation_token; }
  void SetDefault() { self.relocation_token = StormReflTypeInfo<UserMessageRelocate>::GetDefault().relocation_token; }
};

template <>
struct StormReflTypeInfo<UserChatMessageIncoming>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserChatMessageIncoming"; }
  static constexpr auto GetNameHash() { return 0x35F02C18; }
  static UserChatMessageIncoming & GetDefault() { static UserChatMessageIncoming def; return def; }
};

template <>
struct StormReflTypeInfo<UserChatMessageIncoming>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserChatMessageIncoming::c; }
};

template <typename Self>
struct StormReflTypeInfo<UserChatMessageIncoming>::field_data<0, Self> : public StormReflTypeInfo<UserChatMessageIncoming>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<UserChatMessageIncoming>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<UserChatMessageIncoming>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "msg"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x688A5FAF; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserChatMessageIncoming::msg; }
};

template <typename Self>
struct StormReflTypeInfo<UserChatMessageIncoming>::field_data<1, Self> : public StormReflTypeInfo<UserChatMessageIncoming>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.msg; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.msg; }
  void SetDefault() { self.msg = StormReflTypeInfo<UserChatMessageIncoming>::GetDefault().msg; }
};

template <>
struct StormReflTypeInfo<UserChatMessageIncoming>::field_data_static<2>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "channel_id"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x72F5A1AA; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UserChatMessageIncoming::channel_id; }
};

template <typename Self>
struct StormReflTypeInfo<UserChatMessageIncoming>::field_data<2, Self> : public StormReflTypeInfo<UserChatMessageIncoming>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.channel_id; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.channel_id; }
  void SetDefault() { self.channel_id = StormReflTypeInfo<UserChatMessageIncoming>::GetDefault().channel_id; }
};

template <>
struct StormReflTypeInfo<UserChatMessageOutgoing>
{
  using MyBase = void;
  static constexpr int fields_n = 6;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserChatMessageOutgoing"; }
  static constexpr auto GetNameHash() { return 0x12EC5CC2; }
  static UserChatMessageOutgoing & GetDefault() { static UserChatMessageOutgoing def; return def; }
};

template <>
struct StormReflTypeInfo<UserChatMessageOutgoing>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserChatMessageOutgoing::c; }
};

template <typename Self>
struct StormReflTypeInfo<UserChatMessageOutgoing>::field_data<0, Self> : public StormReflTypeInfo<UserChatMessageOutgoing>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<UserChatMessageOutgoing>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<UserChatMessageOutgoing>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "user"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8D93D649; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserChatMessageOutgoing::user; }
};

template <typename Self>
struct StormReflTypeInfo<UserChatMessageOutgoing>::field_data<1, Self> : public StormReflTypeInfo<UserChatMessageOutgoing>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.user; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.user; }
  void SetDefault() { self.user = StormReflTypeInfo<UserChatMessageOutgoing>::GetDefault().user; }
};

template <>
struct StormReflTypeInfo<UserChatMessageOutgoing>::field_data_static<2>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "msg"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x688A5FAF; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UserChatMessageOutgoing::msg; }
};

template <typename Self>
struct StormReflTypeInfo<UserChatMessageOutgoing>::field_data<2, Self> : public StormReflTypeInfo<UserChatMessageOutgoing>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.msg; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.msg; }
  void SetDefault() { self.msg = StormReflTypeInfo<UserChatMessageOutgoing>::GetDefault().msg; }
};

template <>
struct StormReflTypeInfo<UserChatMessageOutgoing>::field_data_static<3>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "b"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x71BEEFF9; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &UserChatMessageOutgoing::b; }
};

template <typename Self>
struct StormReflTypeInfo<UserChatMessageOutgoing>::field_data<3, Self> : public StormReflTypeInfo<UserChatMessageOutgoing>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.b; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.b; }
  void SetDefault() { self.b = StormReflTypeInfo<UserChatMessageOutgoing>::GetDefault().b; }
};

template <>
struct StormReflTypeInfo<UserChatMessageOutgoing>::field_data_static<4>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "t"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x856A5AA8; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &UserChatMessageOutgoing::t; }
};

template <typename Self>
struct StormReflTypeInfo<UserChatMessageOutgoing>::field_data<4, Self> : public StormReflTypeInfo<UserChatMessageOutgoing>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.t; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.t; }
  void SetDefault() { self.t = StormReflTypeInfo<UserChatMessageOutgoing>::GetDefault().t; }
};

template <>
struct StormReflTypeInfo<UserChatMessageOutgoing>::field_data_static<5>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "channel_id"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x72F5A1AA; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &UserChatMessageOutgoing::channel_id; }
};

template <typename Self>
struct StormReflTypeInfo<UserChatMessageOutgoing>::field_data<5, Self> : public StormReflTypeInfo<UserChatMessageOutgoing>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.channel_id; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.channel_id; }
  void SetDefault() { self.channel_id = StormReflTypeInfo<UserChatMessageOutgoing>::GetDefault().channel_id; }
};

template <>
struct StormReflTypeInfo<UserChatMessageGame>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserChatMessageGame"; }
  static constexpr auto GetNameHash() { return 0xDCDCFDF1; }
  static UserChatMessageGame & GetDefault() { static UserChatMessageGame def; return def; }
};

template <>
struct StormReflTypeInfo<UserChatMessageGame>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserChatMessageGame::c; }
};

template <typename Self>
struct StormReflTypeInfo<UserChatMessageGame>::field_data<0, Self> : public StormReflTypeInfo<UserChatMessageGame>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<UserChatMessageGame>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<UserChatMessageGame>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "user"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8D93D649; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserChatMessageGame::user; }
};

template <typename Self>
struct StormReflTypeInfo<UserChatMessageGame>::field_data<1, Self> : public StormReflTypeInfo<UserChatMessageGame>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.user; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.user; }
  void SetDefault() { self.user = StormReflTypeInfo<UserChatMessageGame>::GetDefault().user; }
};

template <>
struct StormReflTypeInfo<UserChatMessageGame>::field_data_static<2>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "msg"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x688A5FAF; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UserChatMessageGame::msg; }
};

template <typename Self>
struct StormReflTypeInfo<UserChatMessageGame>::field_data<2, Self> : public StormReflTypeInfo<UserChatMessageGame>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.msg; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.msg; }
  void SetDefault() { self.msg = StormReflTypeInfo<UserChatMessageGame>::GetDefault().msg; }
};

template <>
struct StormReflTypeInfo<UserServerMessageGame>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserServerMessageGame"; }
  static constexpr auto GetNameHash() { return 0xBDE0C2E7; }
  static UserServerMessageGame & GetDefault() { static UserServerMessageGame def; return def; }
};

template <>
struct StormReflTypeInfo<UserServerMessageGame>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserServerMessageGame::c; }
};

template <typename Self>
struct StormReflTypeInfo<UserServerMessageGame>::field_data<0, Self> : public StormReflTypeInfo<UserServerMessageGame>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<UserServerMessageGame>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<UserServerMessageGame>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "msg"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x688A5FAF; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserServerMessageGame::msg; }
};

template <typename Self>
struct StormReflTypeInfo<UserServerMessageGame>::field_data<1, Self> : public StormReflTypeInfo<UserServerMessageGame>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.msg; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.msg; }
  void SetDefault() { self.msg = StormReflTypeInfo<UserServerMessageGame>::GetDefault().msg; }
};

template <>
struct StormReflTypeInfo<UserMapListRequest>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserMapListRequest"; }
  static constexpr auto GetNameHash() { return 0xB59D8499; }
  static UserMapListRequest & GetDefault() { static UserMapListRequest def; return def; }
};

template <>
struct StormReflTypeInfo<UserMapListRequest>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserMapListRequest::c; }
};

template <typename Self>
struct StormReflTypeInfo<UserMapListRequest>::field_data<0, Self> : public StormReflTypeInfo<UserMapListRequest>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<UserMapListRequest>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<UserMapListRequest>::field_data_static<1>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "server_id"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1844E6B7; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserMapListRequest::server_id; }
};

template <typename Self>
struct StormReflTypeInfo<UserMapListRequest>::field_data<1, Self> : public StormReflTypeInfo<UserMapListRequest>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.server_id; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.server_id; }
  void SetDefault() { self.server_id = StormReflTypeInfo<UserMapListRequest>::GetDefault().server_id; }
};

template <>
struct StormReflTypeInfo<UserMapListMap>
{
  using MyBase = void;
  static constexpr int fields_n = 7;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserMapListMap"; }
  static constexpr auto GetNameHash() { return 0x4D406D32; }
  static UserMapListMap & GetDefault() { static UserMapListMap def; return def; }
};

template <>
struct StormReflTypeInfo<UserMapListMap>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "map_name"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xCD0BD993; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserMapListMap::map_name; }
};

template <typename Self>
struct StormReflTypeInfo<UserMapListMap>::field_data<0, Self> : public StormReflTypeInfo<UserMapListMap>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.map_name; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.map_name; }
  void SetDefault() { self.map_name = StormReflTypeInfo<UserMapListMap>::GetDefault().map_name; }
};

template <>
struct StormReflTypeInfo<UserMapListMap>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "creator"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xBC06EA63; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserMapListMap::creator; }
};

template <typename Self>
struct StormReflTypeInfo<UserMapListMap>::field_data<1, Self> : public StormReflTypeInfo<UserMapListMap>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.creator; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.creator; }
  void SetDefault() { self.creator = StormReflTypeInfo<UserMapListMap>::GetDefault().creator; }
};

template <>
struct StormReflTypeInfo<UserMapListMap>::field_data_static<2>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "game_type"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x67CB3B05; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UserMapListMap::game_type; }
};

template <typename Self>
struct StormReflTypeInfo<UserMapListMap>::field_data<2, Self> : public StormReflTypeInfo<UserMapListMap>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.game_type; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.game_type; }
  void SetDefault() { self.game_type = StormReflTypeInfo<UserMapListMap>::GetDefault().game_type; }
};

template <>
struct StormReflTypeInfo<UserMapListMap>::field_data_static<3>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "max_teams"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x25DB2353; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &UserMapListMap::max_teams; }
};

template <typename Self>
struct StormReflTypeInfo<UserMapListMap>::field_data<3, Self> : public StormReflTypeInfo<UserMapListMap>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.max_teams; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.max_teams; }
  void SetDefault() { self.max_teams = StormReflTypeInfo<UserMapListMap>::GetDefault().max_teams; }
};

template <>
struct StormReflTypeInfo<UserMapListMap>::field_data_static<4>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "player_limit"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC0E49326; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &UserMapListMap::player_limit; }
};

template <typename Self>
struct StormReflTypeInfo<UserMapListMap>::field_data<4, Self> : public StormReflTypeInfo<UserMapListMap>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.player_limit; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.player_limit; }
  void SetDefault() { self.player_limit = StormReflTypeInfo<UserMapListMap>::GetDefault().player_limit; }
};

template <>
struct StormReflTypeInfo<UserMapListMap>::field_data_static<5>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "time_limit"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3AE4091C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &UserMapListMap::time_limit; }
};

template <typename Self>
struct StormReflTypeInfo<UserMapListMap>::field_data<5, Self> : public StormReflTypeInfo<UserMapListMap>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.time_limit; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.time_limit; }
  void SetDefault() { self.time_limit = StormReflTypeInfo<UserMapListMap>::GetDefault().time_limit; }
};

template <>
struct StormReflTypeInfo<UserMapListMap>::field_data_static<6>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "score_limit"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC6DA24E8; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &UserMapListMap::score_limit; }
};

template <typename Self>
struct StormReflTypeInfo<UserMapListMap>::field_data<6, Self> : public StormReflTypeInfo<UserMapListMap>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.score_limit; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.score_limit; }
  void SetDefault() { self.score_limit = StormReflTypeInfo<UserMapListMap>::GetDefault().score_limit; }
};

template <>
struct StormReflTypeInfo<UserMapList>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserMapList"; }
  static constexpr auto GetNameHash() { return 0x5D890CA4; }
  static UserMapList & GetDefault() { static UserMapList def; return def; }
};

template <>
struct StormReflTypeInfo<UserMapList>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserMapList::c; }
};

template <typename Self>
struct StormReflTypeInfo<UserMapList>::field_data<0, Self> : public StormReflTypeInfo<UserMapList>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<UserMapList>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<UserMapList>::field_data_static<1>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "server_id"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1844E6B7; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserMapList::server_id; }
};

template <typename Self>
struct StormReflTypeInfo<UserMapList>::field_data<1, Self> : public StormReflTypeInfo<UserMapList>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.server_id; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.server_id; }
  void SetDefault() { self.server_id = StormReflTypeInfo<UserMapList>::GetDefault().server_id; }
};

template <>
struct StormReflTypeInfo<UserMapList>::field_data_static<2>
{
  using member_type = std::vector<UserMapListMap>; // std::vector<UserMapListMap, std::allocator<UserMapListMap> >
  static constexpr auto GetName() { return "maps"; }
  static constexpr auto GetType() { return "std::vector<UserMapListMap, std::allocator<UserMapListMap> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x472E08A5; }
  static constexpr unsigned GetTypeNameHash() { return 0x7828182A; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UserMapList::maps; }
};

template <typename Self>
struct StormReflTypeInfo<UserMapList>::field_data<2, Self> : public StormReflTypeInfo<UserMapList>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<UserMapListMap>> & Get() { return self.maps; }
  std::add_const_t<std::remove_reference_t<std::vector<UserMapListMap>>> & Get() const { return self.maps; }
  void SetDefault() { self.maps = StormReflTypeInfo<UserMapList>::GetDefault().maps; }
};

template <>
struct StormReflTypeInfo<UserGameCreate>
{
  using MyBase = void;
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserGameCreate"; }
  static constexpr auto GetNameHash() { return 0xFF34272F; }
  static UserGameCreate & GetDefault() { static UserGameCreate def; return def; }
};

template <>
struct StormReflTypeInfo<UserGameCreate>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserGameCreate::c; }
};

template <typename Self>
struct StormReflTypeInfo<UserGameCreate>::field_data<0, Self> : public StormReflTypeInfo<UserGameCreate>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<UserGameCreate>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<UserGameCreate>::field_data_static<1>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "server_id"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1844E6B7; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserGameCreate::server_id; }
};

template <typename Self>
struct StormReflTypeInfo<UserGameCreate>::field_data<1, Self> : public StormReflTypeInfo<UserGameCreate>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.server_id; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.server_id; }
  void SetDefault() { self.server_id = StormReflTypeInfo<UserGameCreate>::GetDefault().server_id; }
};

template <>
struct StormReflTypeInfo<UserGameCreate>::field_data_static<2>
{
  using member_type = GameInstanceData; // GameInstanceData
  static constexpr auto GetName() { return "create_data"; }
  static constexpr auto GetType() { return "GameInstanceData"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2C526E0A; }
  static constexpr unsigned GetTypeNameHash() { return 0xC7A440E6; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UserGameCreate::create_data; }
};

template <typename Self>
struct StormReflTypeInfo<UserGameCreate>::field_data<2, Self> : public StormReflTypeInfo<UserGameCreate>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameInstanceData> & Get() { return self.create_data; }
  std::add_const_t<std::remove_reference_t<GameInstanceData>> & Get() const { return self.create_data; }
  void SetDefault() { self.create_data = StormReflTypeInfo<UserGameCreate>::GetDefault().create_data; }
};

template <>
struct StormReflTypeInfo<UserGameCreate>::field_data_static<3>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "password"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x35C246D5; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &UserGameCreate::password; }
};

template <typename Self>
struct StormReflTypeInfo<UserGameCreate>::field_data<3, Self> : public StormReflTypeInfo<UserGameCreate>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.password; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.password; }
  void SetDefault() { self.password = StormReflTypeInfo<UserGameCreate>::GetDefault().password; }
};

template <>
struct StormReflTypeInfo<UserJoinGame>
{
  using MyBase = void;
  static constexpr int fields_n = 5;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserJoinGame"; }
  static constexpr auto GetNameHash() { return 0x3F51CFDF; }
  static UserJoinGame & GetDefault() { static UserJoinGame def; return def; }
};

template <>
struct StormReflTypeInfo<UserJoinGame>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserJoinGame::c; }
};

template <typename Self>
struct StormReflTypeInfo<UserJoinGame>::field_data<0, Self> : public StormReflTypeInfo<UserJoinGame>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<UserJoinGame>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<UserJoinGame>::field_data_static<1>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "server_id"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1844E6B7; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserJoinGame::server_id; }
};

template <typename Self>
struct StormReflTypeInfo<UserJoinGame>::field_data<1, Self> : public StormReflTypeInfo<UserJoinGame>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.server_id; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.server_id; }
  void SetDefault() { self.server_id = StormReflTypeInfo<UserJoinGame>::GetDefault().server_id; }
};

template <>
struct StormReflTypeInfo<UserJoinGame>::field_data_static<2>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UserJoinGame::game_id; }
};

template <typename Self>
struct StormReflTypeInfo<UserJoinGame>::field_data<2, Self> : public StormReflTypeInfo<UserJoinGame>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.game_id; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.game_id; }
  void SetDefault() { self.game_id = StormReflTypeInfo<UserJoinGame>::GetDefault().game_id; }
};

template <>
struct StormReflTypeInfo<UserJoinGame>::field_data_static<3>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "password"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x35C246D5; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &UserJoinGame::password; }
};

template <typename Self>
struct StormReflTypeInfo<UserJoinGame>::field_data<3, Self> : public StormReflTypeInfo<UserJoinGame>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.password; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.password; }
  void SetDefault() { self.password = StormReflTypeInfo<UserJoinGame>::GetDefault().password; }
};

template <>
struct StormReflTypeInfo<UserJoinGame>::field_data_static<4>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "observer"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x9B6F44E7; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &UserJoinGame::observer; }
};

template <typename Self>
struct StormReflTypeInfo<UserJoinGame>::field_data<4, Self> : public StormReflTypeInfo<UserJoinGame>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.observer; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.observer; }
  void SetDefault() { self.observer = StormReflTypeInfo<UserJoinGame>::GetDefault().observer; }
};

template <>
struct StormReflTypeInfo<UserDestroyGame>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserDestroyGame"; }
  static constexpr auto GetNameHash() { return 0x43CFC358; }
  static UserDestroyGame & GetDefault() { static UserDestroyGame def; return def; }
};

template <>
struct StormReflTypeInfo<UserDestroyGame>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserDestroyGame::c; }
};

template <typename Self>
struct StormReflTypeInfo<UserDestroyGame>::field_data<0, Self> : public StormReflTypeInfo<UserDestroyGame>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<UserDestroyGame>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<UserDestroyGame>::field_data_static<1>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "server_id"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1844E6B7; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserDestroyGame::server_id; }
};

template <typename Self>
struct StormReflTypeInfo<UserDestroyGame>::field_data<1, Self> : public StormReflTypeInfo<UserDestroyGame>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.server_id; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.server_id; }
  void SetDefault() { self.server_id = StormReflTypeInfo<UserDestroyGame>::GetDefault().server_id; }
};

template <>
struct StormReflTypeInfo<UserDestroyGame>::field_data_static<2>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UserDestroyGame::game_id; }
};

template <typename Self>
struct StormReflTypeInfo<UserDestroyGame>::field_data<2, Self> : public StormReflTypeInfo<UserDestroyGame>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.game_id; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.game_id; }
  void SetDefault() { self.game_id = StormReflTypeInfo<UserDestroyGame>::GetDefault().game_id; }
};

template <>
struct StormReflTypeInfo<UserStartGame>
{
  using MyBase = void;
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserStartGame"; }
  static constexpr auto GetNameHash() { return 0x3DDBF0D8; }
  static UserStartGame & GetDefault() { static UserStartGame def; return def; }
};

template <>
struct StormReflTypeInfo<UserStartGame>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserStartGame::c; }
};

template <typename Self>
struct StormReflTypeInfo<UserStartGame>::field_data<0, Self> : public StormReflTypeInfo<UserStartGame>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<UserStartGame>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<UserStartGame>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "ip_addr"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x41FDCEBA; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserStartGame::ip_addr; }
};

template <typename Self>
struct StormReflTypeInfo<UserStartGame>::field_data<1, Self> : public StormReflTypeInfo<UserStartGame>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.ip_addr; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.ip_addr; }
  void SetDefault() { self.ip_addr = StormReflTypeInfo<UserStartGame>::GetDefault().ip_addr; }
};

template <>
struct StormReflTypeInfo<UserStartGame>::field_data_static<2>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "port"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x43915DCC; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UserStartGame::port; }
};

template <typename Self>
struct StormReflTypeInfo<UserStartGame>::field_data<2, Self> : public StormReflTypeInfo<UserStartGame>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.port; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.port; }
  void SetDefault() { self.port = StormReflTypeInfo<UserStartGame>::GetDefault().port; }
};

template <>
struct StormReflTypeInfo<UserStartGame>::field_data_static<3>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "token"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5F37A13B; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &UserStartGame::token; }
};

template <typename Self>
struct StormReflTypeInfo<UserStartGame>::field_data<3, Self> : public StormReflTypeInfo<UserStartGame>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.token; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.token; }
  void SetDefault() { self.token = StormReflTypeInfo<UserStartGame>::GetDefault().token; }
};

template <>
struct StormReflTypeInfo<UserCreateSquad>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserCreateSquad"; }
  static constexpr auto GetNameHash() { return 0x18E0BA4C; }
  static UserCreateSquad & GetDefault() { static UserCreateSquad def; return def; }
};

template <>
struct StormReflTypeInfo<UserCreateSquad>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserCreateSquad::c; }
};

template <typename Self>
struct StormReflTypeInfo<UserCreateSquad>::field_data<0, Self> : public StormReflTypeInfo<UserCreateSquad>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<UserCreateSquad>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<UserCreateSquad>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "name"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5E237E06; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserCreateSquad::name; }
};

template <typename Self>
struct StormReflTypeInfo<UserCreateSquad>::field_data<1, Self> : public StormReflTypeInfo<UserCreateSquad>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.name; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.name; }
  void SetDefault() { self.name = StormReflTypeInfo<UserCreateSquad>::GetDefault().name; }
};

template <>
struct StormReflTypeInfo<UserCreateSquad>::field_data_static<2>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "tag"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0389B783; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UserCreateSquad::tag; }
};

template <typename Self>
struct StormReflTypeInfo<UserCreateSquad>::field_data<2, Self> : public StormReflTypeInfo<UserCreateSquad>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.tag; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.tag; }
  void SetDefault() { self.tag = StormReflTypeInfo<UserCreateSquad>::GetDefault().tag; }
};

template <>
struct StormReflTypeInfo<UserSquadAction>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserSquadAction"; }
  static constexpr auto GetNameHash() { return 0xF7978A2B; }
  static UserSquadAction & GetDefault() { static UserSquadAction def; return def; }
};

template <>
struct StormReflTypeInfo<UserSquadAction>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserSquadAction::c; }
};

template <typename Self>
struct StormReflTypeInfo<UserSquadAction>::field_data<0, Self> : public StormReflTypeInfo<UserSquadAction>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<UserSquadAction>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<UserSquadAction>::field_data_static<1>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "squad"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xCFD0FFE7; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserSquadAction::squad; }
};

template <typename Self>
struct StormReflTypeInfo<UserSquadAction>::field_data<1, Self> : public StormReflTypeInfo<UserSquadAction>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.squad; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.squad; }
  void SetDefault() { self.squad = StormReflTypeInfo<UserSquadAction>::GetDefault().squad; }
};

template <>
struct StormReflTypeInfo<UserSquadMemberAction>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserSquadMemberAction"; }
  static constexpr auto GetNameHash() { return 0xC3AE3165; }
  static UserSquadMemberAction & GetDefault() { static UserSquadMemberAction def; return def; }
};

template <>
struct StormReflTypeInfo<UserSquadMemberAction>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserSquadMemberAction::c; }
};

template <typename Self>
struct StormReflTypeInfo<UserSquadMemberAction>::field_data<0, Self> : public StormReflTypeInfo<UserSquadMemberAction>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<UserSquadMemberAction>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<UserSquadMemberAction>::field_data_static<1>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "squad"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xCFD0FFE7; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserSquadMemberAction::squad; }
};

template <typename Self>
struct StormReflTypeInfo<UserSquadMemberAction>::field_data<1, Self> : public StormReflTypeInfo<UserSquadMemberAction>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.squad; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.squad; }
  void SetDefault() { self.squad = StormReflTypeInfo<UserSquadMemberAction>::GetDefault().squad; }
};

template <>
struct StormReflTypeInfo<UserSquadMemberAction>::field_data_static<2>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "user"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8D93D649; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UserSquadMemberAction::user; }
};

template <typename Self>
struct StormReflTypeInfo<UserSquadMemberAction>::field_data<2, Self> : public StormReflTypeInfo<UserSquadMemberAction>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.user; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.user; }
  void SetDefault() { self.user = StormReflTypeInfo<UserSquadMemberAction>::GetDefault().user; }
};

template <>
struct StormReflTypeInfo<UserSquadLookupAction>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserSquadLookupAction"; }
  static constexpr auto GetNameHash() { return 0xF9D663EA; }
  static UserSquadLookupAction & GetDefault() { static UserSquadLookupAction def; return def; }
};

template <>
struct StormReflTypeInfo<UserSquadLookupAction>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserSquadLookupAction::c; }
};

template <typename Self>
struct StormReflTypeInfo<UserSquadLookupAction>::field_data<0, Self> : public StormReflTypeInfo<UserSquadLookupAction>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<UserSquadLookupAction>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<UserSquadLookupAction>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "squad"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xCFD0FFE7; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserSquadLookupAction::squad; }
};

template <typename Self>
struct StormReflTypeInfo<UserSquadLookupAction>::field_data<1, Self> : public StormReflTypeInfo<UserSquadLookupAction>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.squad; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.squad; }
  void SetDefault() { self.squad = StormReflTypeInfo<UserSquadLookupAction>::GetDefault().squad; }
};

template <>
struct StormReflTypeInfo<UserSquadMemberLookupAction>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserSquadMemberLookupAction"; }
  static constexpr auto GetNameHash() { return 0x05D2CB94; }
  static UserSquadMemberLookupAction & GetDefault() { static UserSquadMemberLookupAction def; return def; }
};

template <>
struct StormReflTypeInfo<UserSquadMemberLookupAction>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserSquadMemberLookupAction::c; }
};

template <typename Self>
struct StormReflTypeInfo<UserSquadMemberLookupAction>::field_data<0, Self> : public StormReflTypeInfo<UserSquadMemberLookupAction>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<UserSquadMemberLookupAction>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<UserSquadMemberLookupAction>::field_data_static<1>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "squad"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xCFD0FFE7; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserSquadMemberLookupAction::squad; }
};

template <typename Self>
struct StormReflTypeInfo<UserSquadMemberLookupAction>::field_data<1, Self> : public StormReflTypeInfo<UserSquadMemberLookupAction>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.squad; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.squad; }
  void SetDefault() { self.squad = StormReflTypeInfo<UserSquadMemberLookupAction>::GetDefault().squad; }
};

template <>
struct StormReflTypeInfo<UserSquadMemberLookupAction>::field_data_static<2>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "user"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8D93D649; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UserSquadMemberLookupAction::user; }
};

template <typename Self>
struct StormReflTypeInfo<UserSquadMemberLookupAction>::field_data<2, Self> : public StormReflTypeInfo<UserSquadMemberLookupAction>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.user; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.user; }
  void SetDefault() { self.user = StormReflTypeInfo<UserSquadMemberLookupAction>::GetDefault().user; }
};

template <>
struct StormReflTypeInfo<UserSquadMemberPermissions>
{
  using MyBase = void;
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserSquadMemberPermissions"; }
  static constexpr auto GetNameHash() { return 0x2C5D9464; }
  static UserSquadMemberPermissions & GetDefault() { static UserSquadMemberPermissions def; return def; }
};

template <>
struct StormReflTypeInfo<UserSquadMemberPermissions>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserSquadMemberPermissions::c; }
};

template <typename Self>
struct StormReflTypeInfo<UserSquadMemberPermissions>::field_data<0, Self> : public StormReflTypeInfo<UserSquadMemberPermissions>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<UserSquadMemberPermissions>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<UserSquadMemberPermissions>::field_data_static<1>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "squad"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xCFD0FFE7; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserSquadMemberPermissions::squad; }
};

template <typename Self>
struct StormReflTypeInfo<UserSquadMemberPermissions>::field_data<1, Self> : public StormReflTypeInfo<UserSquadMemberPermissions>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.squad; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.squad; }
  void SetDefault() { self.squad = StormReflTypeInfo<UserSquadMemberPermissions>::GetDefault().squad; }
};

template <>
struct StormReflTypeInfo<UserSquadMemberPermissions>::field_data_static<2>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "member"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x70E4FA78; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UserSquadMemberPermissions::member; }
};

template <typename Self>
struct StormReflTypeInfo<UserSquadMemberPermissions>::field_data<2, Self> : public StormReflTypeInfo<UserSquadMemberPermissions>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.member; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.member; }
  void SetDefault() { self.member = StormReflTypeInfo<UserSquadMemberPermissions>::GetDefault().member; }
};

template <>
struct StormReflTypeInfo<UserSquadMemberPermissions>::field_data_static<3>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "rank"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8879E8E5; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &UserSquadMemberPermissions::rank; }
};

template <typename Self>
struct StormReflTypeInfo<UserSquadMemberPermissions>::field_data<3, Self> : public StormReflTypeInfo<UserSquadMemberPermissions>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.rank; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.rank; }
  void SetDefault() { self.rank = StormReflTypeInfo<UserSquadMemberPermissions>::GetDefault().rank; }
};

template <>
struct StormReflTypeInfo<UserSquadMotd>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserSquadMotd"; }
  static constexpr auto GetNameHash() { return 0x8A2CF536; }
  static UserSquadMotd & GetDefault() { static UserSquadMotd def; return def; }
};

template <>
struct StormReflTypeInfo<UserSquadMotd>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserSquadMotd::c; }
};

template <typename Self>
struct StormReflTypeInfo<UserSquadMotd>::field_data<0, Self> : public StormReflTypeInfo<UserSquadMotd>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<UserSquadMotd>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<UserSquadMotd>::field_data_static<1>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "squad"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xCFD0FFE7; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserSquadMotd::squad; }
};

template <typename Self>
struct StormReflTypeInfo<UserSquadMotd>::field_data<1, Self> : public StormReflTypeInfo<UserSquadMotd>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.squad; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.squad; }
  void SetDefault() { self.squad = StormReflTypeInfo<UserSquadMotd>::GetDefault().squad; }
};

template <>
struct StormReflTypeInfo<UserSquadMotd>::field_data_static<2>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "motd"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAA0F656C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UserSquadMotd::motd; }
};

template <typename Self>
struct StormReflTypeInfo<UserSquadMotd>::field_data<2, Self> : public StormReflTypeInfo<UserSquadMotd>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.motd; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.motd; }
  void SetDefault() { self.motd = StormReflTypeInfo<UserSquadMotd>::GetDefault().motd; }
};

template <>
struct StormReflTypeInfo<UserSquadLock>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserSquadLock"; }
  static constexpr auto GetNameHash() { return 0xA7AC0B54; }
  static UserSquadLock & GetDefault() { static UserSquadLock def; return def; }
};

template <>
struct StormReflTypeInfo<UserSquadLock>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserSquadLock::c; }
};

template <typename Self>
struct StormReflTypeInfo<UserSquadLock>::field_data<0, Self> : public StormReflTypeInfo<UserSquadLock>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<UserSquadLock>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<UserSquadLock>::field_data_static<1>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "squad"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xCFD0FFE7; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserSquadLock::squad; }
};

template <typename Self>
struct StormReflTypeInfo<UserSquadLock>::field_data<1, Self> : public StormReflTypeInfo<UserSquadLock>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.squad; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.squad; }
  void SetDefault() { self.squad = StormReflTypeInfo<UserSquadLock>::GetDefault().squad; }
};

template <>
struct StormReflTypeInfo<UserSquadLock>::field_data_static<2>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "lock"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x878F9B0E; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UserSquadLock::lock; }
};

template <typename Self>
struct StormReflTypeInfo<UserSquadLock>::field_data<2, Self> : public StormReflTypeInfo<UserSquadLock>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.lock; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.lock; }
  void SetDefault() { self.lock = StormReflTypeInfo<UserSquadLock>::GetDefault().lock; }
};

template <>
struct StormReflTypeInfo<UserStatsData>
{
  using MyBase = void;
  static constexpr int fields_n = 6;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserStatsData"; }
  static constexpr auto GetNameHash() { return 0xD77A0D3A; }
  static UserStatsData & GetDefault() { static UserStatsData def; return def; }
};

template <>
struct StormReflTypeInfo<UserStatsData>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserStatsData::c; }
};

template <typename Self>
struct StormReflTypeInfo<UserStatsData>::field_data<0, Self> : public StormReflTypeInfo<UserStatsData>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<UserStatsData>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<UserStatsData>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "name"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5E237E06; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserStatsData::name; }
};

template <typename Self>
struct StormReflTypeInfo<UserStatsData>::field_data<1, Self> : public StormReflTypeInfo<UserStatsData>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.name; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.name; }
  void SetDefault() { self.name = StormReflTypeInfo<UserStatsData>::GetDefault().name; }
};

template <>
struct StormReflTypeInfo<UserStatsData>::field_data_static<2>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "last_game_played"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x51CE1DF0; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UserStatsData::last_game_played; }
};

template <typename Self>
struct StormReflTypeInfo<UserStatsData>::field_data<2, Self> : public StormReflTypeInfo<UserStatsData>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.last_game_played; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.last_game_played; }
  void SetDefault() { self.last_game_played = StormReflTypeInfo<UserStatsData>::GetDefault().last_game_played; }
};

template <>
struct StormReflTypeInfo<UserStatsData>::field_data_static<3>
{
  using member_type = GameStatsData; // GameStatsData
  static constexpr auto GetName() { return "stats"; }
  static constexpr auto GetType() { return "GameStatsData"; }
  static constexpr unsigned GetFieldNameHash() { return 0x574767AA; }
  static constexpr unsigned GetTypeNameHash() { return 0x9CB3161C; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &UserStatsData::stats; }
};

template <typename Self>
struct StormReflTypeInfo<UserStatsData>::field_data<3, Self> : public StormReflTypeInfo<UserStatsData>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameStatsData> & Get() { return self.stats; }
  std::add_const_t<std::remove_reference_t<GameStatsData>> & Get() const { return self.stats; }
  void SetDefault() { self.stats = StormReflTypeInfo<UserStatsData>::GetDefault().stats; }
};

template <>
struct StormReflTypeInfo<UserStatsData>::field_data_static<4>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "rank"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8879E8E5; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &UserStatsData::rank; }
};

template <typename Self>
struct StormReflTypeInfo<UserStatsData>::field_data<4, Self> : public StormReflTypeInfo<UserStatsData>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.rank; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.rank; }
  void SetDefault() { self.rank = StormReflTypeInfo<UserStatsData>::GetDefault().rank; }
};

template <>
struct StormReflTypeInfo<UserStatsData>::field_data_static<5>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "xp"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF63A903D; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &UserStatsData::xp; }
};

template <typename Self>
struct StormReflTypeInfo<UserStatsData>::field_data<5, Self> : public StormReflTypeInfo<UserStatsData>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.xp; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.xp; }
  void SetDefault() { self.xp = StormReflTypeInfo<UserStatsData>::GetDefault().xp; }
};

template <>
struct StormReflTypeInfo<UserEditInfo>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserEditInfo"; }
  static constexpr auto GetNameHash() { return 0x26840671; }
  static UserEditInfo & GetDefault() { static UserEditInfo def; return def; }
};

template <>
struct StormReflTypeInfo<UserEditInfo>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserEditInfo::c; }
};

template <typename Self>
struct StormReflTypeInfo<UserEditInfo>::field_data<0, Self> : public StormReflTypeInfo<UserEditInfo>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<UserEditInfo>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<UserEditInfo>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "data"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xADF3F363; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserEditInfo::data; }
};

template <typename Self>
struct StormReflTypeInfo<UserEditInfo>::field_data<1, Self> : public StormReflTypeInfo<UserEditInfo>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.data; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.data; }
  void SetDefault() { self.data = StormReflTypeInfo<UserEditInfo>::GetDefault().data; }
};

template <>
struct StormReflTypeInfo<UserEditChannelInfo>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserEditChannelInfo"; }
  static constexpr auto GetNameHash() { return 0x12E236B0; }
  static UserEditChannelInfo & GetDefault() { static UserEditChannelInfo def; return def; }
};

template <>
struct StormReflTypeInfo<UserEditChannelInfo>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserEditChannelInfo::c; }
};

template <typename Self>
struct StormReflTypeInfo<UserEditChannelInfo>::field_data<0, Self> : public StormReflTypeInfo<UserEditChannelInfo>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<UserEditChannelInfo>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<UserEditChannelInfo>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "data"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xADF3F363; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserEditChannelInfo::data; }
};

template <typename Self>
struct StormReflTypeInfo<UserEditChannelInfo>::field_data<1, Self> : public StormReflTypeInfo<UserEditChannelInfo>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.data; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.data; }
  void SetDefault() { self.data = StormReflTypeInfo<UserEditChannelInfo>::GetDefault().data; }
};

template <>
struct StormReflTypeInfo<UserEditChannelInfo>::field_data_static<2>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "channel_id"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x72F5A1AA; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UserEditChannelInfo::channel_id; }
};

template <typename Self>
struct StormReflTypeInfo<UserEditChannelInfo>::field_data<2, Self> : public StormReflTypeInfo<UserEditChannelInfo>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.channel_id; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.channel_id; }
  void SetDefault() { self.channel_id = StormReflTypeInfo<UserEditChannelInfo>::GetDefault().channel_id; }
};

template <>
struct StormReflTypeInfo<UserFetchStats>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserFetchStats"; }
  static constexpr auto GetNameHash() { return 0xC08574CD; }
  static UserFetchStats & GetDefault() { static UserFetchStats def; return def; }
};

template <>
struct StormReflTypeInfo<UserFetchStats>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserFetchStats::c; }
};

template <typename Self>
struct StormReflTypeInfo<UserFetchStats>::field_data<0, Self> : public StormReflTypeInfo<UserFetchStats>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<UserFetchStats>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<UserFetchStats>::field_data_static<1>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "user"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8D93D649; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserFetchStats::user; }
};

template <typename Self>
struct StormReflTypeInfo<UserFetchStats>::field_data<1, Self> : public StormReflTypeInfo<UserFetchStats>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.user; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.user; }
  void SetDefault() { self.user = StormReflTypeInfo<UserFetchStats>::GetDefault().user; }
};

template <>
struct StormReflTypeInfo<UserSetProfileVal>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserSetProfileVal"; }
  static constexpr auto GetNameHash() { return 0x18F44BAE; }
  static UserSetProfileVal & GetDefault() { static UserSetProfileVal def; return def; }
};

template <>
struct StormReflTypeInfo<UserSetProfileVal>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserSetProfileVal::c; }
};

template <typename Self>
struct StormReflTypeInfo<UserSetProfileVal>::field_data<0, Self> : public StormReflTypeInfo<UserSetProfileVal>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<UserSetProfileVal>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<UserSetProfileVal>::field_data_static<1>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "val"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x97DFBA65; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserSetProfileVal::val; }
};

template <typename Self>
struct StormReflTypeInfo<UserSetProfileVal>::field_data<1, Self> : public StormReflTypeInfo<UserSetProfileVal>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.val; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.val; }
  void SetDefault() { self.val = StormReflTypeInfo<UserSetProfileVal>::GetDefault().val; }
};

template <>
struct StormReflTypeInfo<UserSetProfileSquad>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserSetProfileSquad"; }
  static constexpr auto GetNameHash() { return 0x2D64BCC3; }
  static UserSetProfileSquad & GetDefault() { static UserSetProfileSquad def; return def; }
};

template <>
struct StormReflTypeInfo<UserSetProfileSquad>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserSetProfileSquad::c; }
};

template <typename Self>
struct StormReflTypeInfo<UserSetProfileSquad>::field_data<0, Self> : public StormReflTypeInfo<UserSetProfileSquad>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<UserSetProfileSquad>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<UserSetProfileSquad>::field_data_static<1>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "val"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x97DFBA65; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserSetProfileSquad::val; }
};

template <typename Self>
struct StormReflTypeInfo<UserSetProfileSquad>::field_data<1, Self> : public StormReflTypeInfo<UserSetProfileSquad>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.val; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.val; }
  void SetDefault() { self.val = StormReflTypeInfo<UserSetProfileSquad>::GetDefault().val; }
};

template <>
struct StormReflTypeInfo<UserPreviewGame>
{
  using MyBase = void;
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserPreviewGame"; }
  static constexpr auto GetNameHash() { return 0x7E1F8735; }
  static UserPreviewGame & GetDefault() { static UserPreviewGame def; return def; }
};

template <>
struct StormReflTypeInfo<UserPreviewGame>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserPreviewGame::c; }
};

template <typename Self>
struct StormReflTypeInfo<UserPreviewGame>::field_data<0, Self> : public StormReflTypeInfo<UserPreviewGame>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<UserPreviewGame>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<UserPreviewGame>::field_data_static<1>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "server_id"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1844E6B7; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserPreviewGame::server_id; }
};

template <typename Self>
struct StormReflTypeInfo<UserPreviewGame>::field_data<1, Self> : public StormReflTypeInfo<UserPreviewGame>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.server_id; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.server_id; }
  void SetDefault() { self.server_id = StormReflTypeInfo<UserPreviewGame>::GetDefault().server_id; }
};

template <>
struct StormReflTypeInfo<UserPreviewGame>::field_data_static<2>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UserPreviewGame::game_id; }
};

template <typename Self>
struct StormReflTypeInfo<UserPreviewGame>::field_data<2, Self> : public StormReflTypeInfo<UserPreviewGame>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.game_id; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.game_id; }
  void SetDefault() { self.game_id = StormReflTypeInfo<UserPreviewGame>::GetDefault().game_id; }
};

template <>
struct StormReflTypeInfo<UserPreviewGame>::field_data_static<3>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "request_id"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x427EB8A5; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &UserPreviewGame::request_id; }
};

template <typename Self>
struct StormReflTypeInfo<UserPreviewGame>::field_data<3, Self> : public StormReflTypeInfo<UserPreviewGame>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.request_id; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.request_id; }
  void SetDefault() { self.request_id = StormReflTypeInfo<UserPreviewGame>::GetDefault().request_id; }
};

template <>
struct StormReflTypeInfo<UserAutoJoinModify>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserAutoJoinModify"; }
  static constexpr auto GetNameHash() { return 0x0DD914B4; }
  static UserAutoJoinModify & GetDefault() { static UserAutoJoinModify def; return def; }
};

template <>
struct StormReflTypeInfo<UserAutoJoinModify>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserAutoJoinModify::c; }
};

template <typename Self>
struct StormReflTypeInfo<UserAutoJoinModify>::field_data<0, Self> : public StormReflTypeInfo<UserAutoJoinModify>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<UserAutoJoinModify>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<UserAutoJoinModify>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "channel"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA2F98E47; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserAutoJoinModify::channel; }
};

template <typename Self>
struct StormReflTypeInfo<UserAutoJoinModify>::field_data<1, Self> : public StormReflTypeInfo<UserAutoJoinModify>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.channel; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.channel; }
  void SetDefault() { self.channel = StormReflTypeInfo<UserAutoJoinModify>::GetDefault().channel; }
};

template <>
struct StormReflTypeInfo<UserPersistentModify>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserPersistentModify"; }
  static constexpr auto GetNameHash() { return 0x8B2C6D2C; }
  static UserPersistentModify & GetDefault() { static UserPersistentModify def; return def; }
};

template <>
struct StormReflTypeInfo<UserPersistentModify>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserPersistentModify::c; }
};

template <typename Self>
struct StormReflTypeInfo<UserPersistentModify>::field_data<0, Self> : public StormReflTypeInfo<UserPersistentModify>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<UserPersistentModify>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<UserPersistentModify>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "change"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x4057FE20; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserPersistentModify::change; }
};

template <typename Self>
struct StormReflTypeInfo<UserPersistentModify>::field_data<1, Self> : public StormReflTypeInfo<UserPersistentModify>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.change; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.change; }
  void SetDefault() { self.change = StormReflTypeInfo<UserPersistentModify>::GetDefault().change; }
};

template <>
struct StormReflTypeInfo<UserGotXP>
{
  using MyBase = void;
  static constexpr int fields_n = 5;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserGotXP"; }
  static constexpr auto GetNameHash() { return 0xA0106C44; }
  static UserGotXP & GetDefault() { static UserGotXP def; return def; }
};

template <>
struct StormReflTypeInfo<UserGotXP>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserGotXP::c; }
};

template <typename Self>
struct StormReflTypeInfo<UserGotXP>::field_data<0, Self> : public StormReflTypeInfo<UserGotXP>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<UserGotXP>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<UserGotXP>::field_data_static<1>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "xp"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF63A903D; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserGotXP::xp; }
};

template <typename Self>
struct StormReflTypeInfo<UserGotXP>::field_data<1, Self> : public StormReflTypeInfo<UserGotXP>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.xp; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.xp; }
  void SetDefault() { self.xp = StormReflTypeInfo<UserGotXP>::GetDefault().xp; }
};

template <>
struct StormReflTypeInfo<UserGotXP>::field_data_static<2>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "level"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x9AEACC13; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UserGotXP::level; }
};

template <typename Self>
struct StormReflTypeInfo<UserGotXP>::field_data<2, Self> : public StormReflTypeInfo<UserGotXP>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.level; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.level; }
  void SetDefault() { self.level = StormReflTypeInfo<UserGotXP>::GetDefault().level; }
};

template <>
struct StormReflTypeInfo<UserGotXP>::field_data_static<3>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "last"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x4ADBA9A0; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &UserGotXP::last; }
};

template <typename Self>
struct StormReflTypeInfo<UserGotXP>::field_data<3, Self> : public StormReflTypeInfo<UserGotXP>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.last; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.last; }
  void SetDefault() { self.last = StormReflTypeInfo<UserGotXP>::GetDefault().last; }
};

template <>
struct StormReflTypeInfo<UserGotXP>::field_data_static<4>
{
  using member_type = UserXPGain; // UserXPGain
  static constexpr auto GetName() { return "xp_info"; }
  static constexpr auto GetType() { return "UserXPGain"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1947FAA2; }
  static constexpr unsigned GetTypeNameHash() { return 0x1F48ADC4; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &UserGotXP::xp_info; }
};

template <typename Self>
struct StormReflTypeInfo<UserGotXP>::field_data<4, Self> : public StormReflTypeInfo<UserGotXP>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, UserXPGain> & Get() { return self.xp_info; }
  std::add_const_t<std::remove_reference_t<UserXPGain>> & Get() const { return self.xp_info; }
  void SetDefault() { self.xp_info = StormReflTypeInfo<UserGotXP>::GetDefault().xp_info; }
};

namespace StormReflFileInfo
{
  struct UserConnectionMessages
  {
    static const int types_n = 43;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct UserConnectionMessages::type_info<0>
  {
    using type = ::GeolocationResponse;
  };

  template <>
  struct UserConnectionMessages::type_info<1>
  {
    using type = ::UserMessageBase;
  };

  template <>
  struct UserConnectionMessages::type_info<2>
  {
    using type = ::UserVersionRequest;
  };

  template <>
  struct UserConnectionMessages::type_info<3>
  {
    using type = ::UserMessageConnectionErrror;
  };

  template <>
  struct UserConnectionMessages::type_info<4>
  {
    using type = ::UserMessageRuntimeError;
  };

  template <>
  struct UserConnectionMessages::type_info<5>
  {
    using type = ::UserMessageVersionResponse;
  };

  template <>
  struct UserConnectionMessages::type_info<6>
  {
    using type = ::UserMessageIdentifyResponse;
  };

  template <>
  struct UserConnectionMessages::type_info<7>
  {
    using type = ::UserMessageCreateName;
  };

  template <>
  struct UserConnectionMessages::type_info<8>
  {
    using type = ::UserLocalInfoUpdate;
  };

  template <>
  struct UserConnectionMessages::type_info<9>
  {
    using type = ::UserGamePreviewUpdate;
  };

  template <>
  struct UserConnectionMessages::type_info<10>
  {
    using type = ::UserGamePreviewCancel;
  };

  template <>
  struct UserConnectionMessages::type_info<11>
  {
    using type = ::UserGameInfoUpdate;
  };

  template <>
  struct UserConnectionMessages::type_info<12>
  {
    using type = ::UserChannelInfoUpdate;
  };

  template <>
  struct UserConnectionMessages::type_info<13>
  {
    using type = ::UserMessageRelocate;
  };

  template <>
  struct UserConnectionMessages::type_info<14>
  {
    using type = ::UserChatMessageIncoming;
  };

  template <>
  struct UserConnectionMessages::type_info<15>
  {
    using type = ::UserChatMessageOutgoing;
  };

  template <>
  struct UserConnectionMessages::type_info<16>
  {
    using type = ::UserChatMessageGame;
  };

  template <>
  struct UserConnectionMessages::type_info<17>
  {
    using type = ::UserServerMessageGame;
  };

  template <>
  struct UserConnectionMessages::type_info<18>
  {
    using type = ::UserMapListRequest;
  };

  template <>
  struct UserConnectionMessages::type_info<19>
  {
    using type = ::UserMapListMap;
  };

  template <>
  struct UserConnectionMessages::type_info<20>
  {
    using type = ::UserMapList;
  };

  template <>
  struct UserConnectionMessages::type_info<21>
  {
    using type = ::UserGameCreate;
  };

  template <>
  struct UserConnectionMessages::type_info<22>
  {
    using type = ::UserJoinGame;
  };

  template <>
  struct UserConnectionMessages::type_info<23>
  {
    using type = ::UserDestroyGame;
  };

  template <>
  struct UserConnectionMessages::type_info<24>
  {
    using type = ::UserStartGame;
  };

  template <>
  struct UserConnectionMessages::type_info<25>
  {
    using type = ::UserCreateSquad;
  };

  template <>
  struct UserConnectionMessages::type_info<26>
  {
    using type = ::UserSquadAction;
  };

  template <>
  struct UserConnectionMessages::type_info<27>
  {
    using type = ::UserSquadMemberAction;
  };

  template <>
  struct UserConnectionMessages::type_info<28>
  {
    using type = ::UserSquadLookupAction;
  };

  template <>
  struct UserConnectionMessages::type_info<29>
  {
    using type = ::UserSquadMemberLookupAction;
  };

  template <>
  struct UserConnectionMessages::type_info<30>
  {
    using type = ::UserSquadMemberPermissions;
  };

  template <>
  struct UserConnectionMessages::type_info<31>
  {
    using type = ::UserSquadMotd;
  };

  template <>
  struct UserConnectionMessages::type_info<32>
  {
    using type = ::UserSquadLock;
  };

  template <>
  struct UserConnectionMessages::type_info<33>
  {
    using type = ::UserStatsData;
  };

  template <>
  struct UserConnectionMessages::type_info<34>
  {
    using type = ::UserEditInfo;
  };

  template <>
  struct UserConnectionMessages::type_info<35>
  {
    using type = ::UserEditChannelInfo;
  };

  template <>
  struct UserConnectionMessages::type_info<36>
  {
    using type = ::UserFetchStats;
  };

  template <>
  struct UserConnectionMessages::type_info<37>
  {
    using type = ::UserSetProfileVal;
  };

  template <>
  struct UserConnectionMessages::type_info<38>
  {
    using type = ::UserSetProfileSquad;
  };

  template <>
  struct UserConnectionMessages::type_info<39>
  {
    using type = ::UserPreviewGame;
  };

  template <>
  struct UserConnectionMessages::type_info<40>
  {
    using type = ::UserAutoJoinModify;
  };

  template <>
  struct UserConnectionMessages::type_info<41>
  {
    using type = ::UserPersistentModify;
  };

  template <>
  struct UserConnectionMessages::type_info<42>
  {
    using type = ::UserGotXP;
  };

}

