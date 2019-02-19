#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "SteamServerMessages.refl.h"


template <>
struct StormReflTypeInfo<SteamValidationResponseParams>
{
  using MyBase = void;
  static constexpr int fields_n = 5;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "SteamValidationResponseParams"; }
  static constexpr auto GetNameHash() { return 0xCC2369E4; }
  static SteamValidationResponseParams & GetDefault() { static SteamValidationResponseParams def; return def; }
};

template <>
struct StormReflTypeInfo<SteamValidationResponseParams>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "result"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x136AC113; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SteamValidationResponseParams::result; }
};

template <typename Self>
struct StormReflTypeInfo<SteamValidationResponseParams>::field_data<0, Self> : public StormReflTypeInfo<SteamValidationResponseParams>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.result; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.result; }
  void SetDefault() { self.result = StormReflTypeInfo<SteamValidationResponseParams>::GetDefault().result; }
};

template <>
struct StormReflTypeInfo<SteamValidationResponseParams>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "steamid"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xBCF81F98; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &SteamValidationResponseParams::steamid; }
};

template <typename Self>
struct StormReflTypeInfo<SteamValidationResponseParams>::field_data<1, Self> : public StormReflTypeInfo<SteamValidationResponseParams>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.steamid; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.steamid; }
  void SetDefault() { self.steamid = StormReflTypeInfo<SteamValidationResponseParams>::GetDefault().steamid; }
};

template <>
struct StormReflTypeInfo<SteamValidationResponseParams>::field_data_static<2>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "ownersteamid"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE031D445; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &SteamValidationResponseParams::ownersteamid; }
};

template <typename Self>
struct StormReflTypeInfo<SteamValidationResponseParams>::field_data<2, Self> : public StormReflTypeInfo<SteamValidationResponseParams>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.ownersteamid; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.ownersteamid; }
  void SetDefault() { self.ownersteamid = StormReflTypeInfo<SteamValidationResponseParams>::GetDefault().ownersteamid; }
};

template <>
struct StormReflTypeInfo<SteamValidationResponseParams>::field_data_static<3>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "vacbanned"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE924F4B9; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &SteamValidationResponseParams::vacbanned; }
};

template <typename Self>
struct StormReflTypeInfo<SteamValidationResponseParams>::field_data<3, Self> : public StormReflTypeInfo<SteamValidationResponseParams>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.vacbanned; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.vacbanned; }
  void SetDefault() { self.vacbanned = StormReflTypeInfo<SteamValidationResponseParams>::GetDefault().vacbanned; }
};

template <>
struct StormReflTypeInfo<SteamValidationResponseParams>::field_data_static<4>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "publisherbanned"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE49F3CAD; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &SteamValidationResponseParams::publisherbanned; }
};

template <typename Self>
struct StormReflTypeInfo<SteamValidationResponseParams>::field_data<4, Self> : public StormReflTypeInfo<SteamValidationResponseParams>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.publisherbanned; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.publisherbanned; }
  void SetDefault() { self.publisherbanned = StormReflTypeInfo<SteamValidationResponseParams>::GetDefault().publisherbanned; }
};

template <>
struct StormReflTypeInfo<SteamValidationResponse>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "SteamValidationResponse"; }
  static constexpr auto GetNameHash() { return 0xD72966B7; }
  static SteamValidationResponse & GetDefault() { static SteamValidationResponse def; return def; }
};

template <>
struct StormReflTypeInfo<SteamValidationResponse>::field_data_static<0>
{
  using member_type = SteamValidationResponseParams; // SteamValidationResponseParams
  static constexpr auto GetName() { return "params"; }
  static constexpr auto GetType() { return "SteamValidationResponseParams"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8FCE0EF3; }
  static constexpr unsigned GetTypeNameHash() { return 0xCC2369E4; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SteamValidationResponse::params; }
};

template <typename Self>
struct StormReflTypeInfo<SteamValidationResponse>::field_data<0, Self> : public StormReflTypeInfo<SteamValidationResponse>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, SteamValidationResponseParams> & Get() { return self.params; }
  std::add_const_t<std::remove_reference_t<SteamValidationResponseParams>> & Get() const { return self.params; }
  void SetDefault() { self.params = StormReflTypeInfo<SteamValidationResponse>::GetDefault().params; }
};

template <>
struct StormReflTypeInfo<SteamValidation>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "SteamValidation"; }
  static constexpr auto GetNameHash() { return 0x3AE4132F; }
  static SteamValidation & GetDefault() { static SteamValidation def; return def; }
};

template <>
struct StormReflTypeInfo<SteamValidation>::field_data_static<0>
{
  using member_type = SteamValidationResponse; // SteamValidationResponse
  static constexpr auto GetName() { return "response"; }
  static constexpr auto GetType() { return "SteamValidationResponse"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3E7B0BFB; }
  static constexpr unsigned GetTypeNameHash() { return 0xD72966B7; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SteamValidation::response; }
};

template <typename Self>
struct StormReflTypeInfo<SteamValidation>::field_data<0, Self> : public StormReflTypeInfo<SteamValidation>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, SteamValidationResponse> & Get() { return self.response; }
  std::add_const_t<std::remove_reference_t<SteamValidationResponse>> & Get() const { return self.response; }
  void SetDefault() { self.response = StormReflTypeInfo<SteamValidation>::GetDefault().response; }
};

template <>
struct StormReflTypeInfo<SteamOwnershipResponseParams>
{
  using MyBase = void;
  static constexpr int fields_n = 5;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "SteamOwnershipResponseParams"; }
  static constexpr auto GetNameHash() { return 0x00726BB0; }
  static SteamOwnershipResponseParams & GetDefault() { static SteamOwnershipResponseParams def; return def; }
};

template <>
struct StormReflTypeInfo<SteamOwnershipResponseParams>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "appid"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA35E1483; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SteamOwnershipResponseParams::appid; }
};

template <typename Self>
struct StormReflTypeInfo<SteamOwnershipResponseParams>::field_data<0, Self> : public StormReflTypeInfo<SteamOwnershipResponseParams>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.appid; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.appid; }
  void SetDefault() { self.appid = StormReflTypeInfo<SteamOwnershipResponseParams>::GetDefault().appid; }
};

template <>
struct StormReflTypeInfo<SteamOwnershipResponseParams>::field_data_static<1>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "ownsapp"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x9F12B188; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &SteamOwnershipResponseParams::ownsapp; }
};

template <typename Self>
struct StormReflTypeInfo<SteamOwnershipResponseParams>::field_data<1, Self> : public StormReflTypeInfo<SteamOwnershipResponseParams>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.ownsapp; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.ownsapp; }
  void SetDefault() { self.ownsapp = StormReflTypeInfo<SteamOwnershipResponseParams>::GetDefault().ownsapp; }
};

template <>
struct StormReflTypeInfo<SteamOwnershipResponseParams>::field_data_static<2>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "permanent"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDC9D8028; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &SteamOwnershipResponseParams::permanent; }
};

template <typename Self>
struct StormReflTypeInfo<SteamOwnershipResponseParams>::field_data<2, Self> : public StormReflTypeInfo<SteamOwnershipResponseParams>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.permanent; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.permanent; }
  void SetDefault() { self.permanent = StormReflTypeInfo<SteamOwnershipResponseParams>::GetDefault().permanent; }
};

template <>
struct StormReflTypeInfo<SteamOwnershipResponseParams>::field_data_static<3>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "timestamp"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA5D6E63E; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &SteamOwnershipResponseParams::timestamp; }
};

template <typename Self>
struct StormReflTypeInfo<SteamOwnershipResponseParams>::field_data<3, Self> : public StormReflTypeInfo<SteamOwnershipResponseParams>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.timestamp; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.timestamp; }
  void SetDefault() { self.timestamp = StormReflTypeInfo<SteamOwnershipResponseParams>::GetDefault().timestamp; }
};

template <>
struct StormReflTypeInfo<SteamOwnershipResponseParams>::field_data_static<4>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "ownersteamid"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE031D445; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &SteamOwnershipResponseParams::ownersteamid; }
};

template <typename Self>
struct StormReflTypeInfo<SteamOwnershipResponseParams>::field_data<4, Self> : public StormReflTypeInfo<SteamOwnershipResponseParams>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.ownersteamid; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.ownersteamid; }
  void SetDefault() { self.ownersteamid = StormReflTypeInfo<SteamOwnershipResponseParams>::GetDefault().ownersteamid; }
};

template <>
struct StormReflTypeInfo<SteamOwnershipResponse>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "SteamOwnershipResponse"; }
  static constexpr auto GetNameHash() { return 0x66212007; }
  static SteamOwnershipResponse & GetDefault() { static SteamOwnershipResponse def; return def; }
};

template <>
struct StormReflTypeInfo<SteamOwnershipResponse>::field_data_static<0>
{
  using member_type = std::vector<SteamOwnershipResponseParams>; // std::vector<SteamOwnershipResponseParams, std::allocator<SteamOwnershipResponseParams> >
  static constexpr auto GetName() { return "apps"; }
  static constexpr auto GetType() { return "std::vector<SteamOwnershipResponseParams, std::allocator<SteamOwnershipResponseParams> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x101C7E5A; }
  static constexpr unsigned GetTypeNameHash() { return 0x6B4137CF; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SteamOwnershipResponse::apps; }
};

template <typename Self>
struct StormReflTypeInfo<SteamOwnershipResponse>::field_data<0, Self> : public StormReflTypeInfo<SteamOwnershipResponse>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<SteamOwnershipResponseParams>> & Get() { return self.apps; }
  std::add_const_t<std::remove_reference_t<std::vector<SteamOwnershipResponseParams>>> & Get() const { return self.apps; }
  void SetDefault() { self.apps = StormReflTypeInfo<SteamOwnershipResponse>::GetDefault().apps; }
};

template <>
struct StormReflTypeInfo<SteamOwnership>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "SteamOwnership"; }
  static constexpr auto GetNameHash() { return 0x8946262A; }
  static SteamOwnership & GetDefault() { static SteamOwnership def; return def; }
};

template <>
struct StormReflTypeInfo<SteamOwnership>::field_data_static<0>
{
  using member_type = SteamOwnershipResponse; // SteamOwnershipResponse
  static constexpr auto GetName() { return "appownership"; }
  static constexpr auto GetType() { return "SteamOwnershipResponse"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3ED0C959; }
  static constexpr unsigned GetTypeNameHash() { return 0x66212007; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SteamOwnership::appownership; }
};

template <typename Self>
struct StormReflTypeInfo<SteamOwnership>::field_data<0, Self> : public StormReflTypeInfo<SteamOwnership>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, SteamOwnershipResponse> & Get() { return self.appownership; }
  std::add_const_t<std::remove_reference_t<SteamOwnershipResponse>> & Get() const { return self.appownership; }
  void SetDefault() { self.appownership = StormReflTypeInfo<SteamOwnership>::GetDefault().appownership; }
};

template <>
struct StormReflTypeInfo<SteamTxnUserInfoResponseParams>
{
  using MyBase = void;
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "SteamTxnUserInfoResponseParams"; }
  static constexpr auto GetNameHash() { return 0x54CE31D1; }
  static SteamTxnUserInfoResponseParams & GetDefault() { static SteamTxnUserInfoResponseParams def; return def; }
};

template <>
struct StormReflTypeInfo<SteamTxnUserInfoResponseParams>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "state"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA393D2FB; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SteamTxnUserInfoResponseParams::state; }
};

template <typename Self>
struct StormReflTypeInfo<SteamTxnUserInfoResponseParams>::field_data<0, Self> : public StormReflTypeInfo<SteamTxnUserInfoResponseParams>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.state; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.state; }
  void SetDefault() { self.state = StormReflTypeInfo<SteamTxnUserInfoResponseParams>::GetDefault().state; }
};

template <>
struct StormReflTypeInfo<SteamTxnUserInfoResponseParams>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "country"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5373C966; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &SteamTxnUserInfoResponseParams::country; }
};

template <typename Self>
struct StormReflTypeInfo<SteamTxnUserInfoResponseParams>::field_data<1, Self> : public StormReflTypeInfo<SteamTxnUserInfoResponseParams>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.country; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.country; }
  void SetDefault() { self.country = StormReflTypeInfo<SteamTxnUserInfoResponseParams>::GetDefault().country; }
};

template <>
struct StormReflTypeInfo<SteamTxnUserInfoResponseParams>::field_data_static<2>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "currency"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6956883F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &SteamTxnUserInfoResponseParams::currency; }
};

template <typename Self>
struct StormReflTypeInfo<SteamTxnUserInfoResponseParams>::field_data<2, Self> : public StormReflTypeInfo<SteamTxnUserInfoResponseParams>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.currency; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.currency; }
  void SetDefault() { self.currency = StormReflTypeInfo<SteamTxnUserInfoResponseParams>::GetDefault().currency; }
};

template <>
struct StormReflTypeInfo<SteamTxnUserInfoResponseParams>::field_data_static<3>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "status"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x7B00651C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &SteamTxnUserInfoResponseParams::status; }
};

template <typename Self>
struct StormReflTypeInfo<SteamTxnUserInfoResponseParams>::field_data<3, Self> : public StormReflTypeInfo<SteamTxnUserInfoResponseParams>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.status; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.status; }
  void SetDefault() { self.status = StormReflTypeInfo<SteamTxnUserInfoResponseParams>::GetDefault().status; }
};

template <>
struct StormReflTypeInfo<SteamTxnUserInfoResponse>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "SteamTxnUserInfoResponse"; }
  static constexpr auto GetNameHash() { return 0xB6DEF1DD; }
  static SteamTxnUserInfoResponse & GetDefault() { static SteamTxnUserInfoResponse def; return def; }
};

template <>
struct StormReflTypeInfo<SteamTxnUserInfoResponse>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "result"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x136AC113; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SteamTxnUserInfoResponse::result; }
};

template <typename Self>
struct StormReflTypeInfo<SteamTxnUserInfoResponse>::field_data<0, Self> : public StormReflTypeInfo<SteamTxnUserInfoResponse>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.result; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.result; }
  void SetDefault() { self.result = StormReflTypeInfo<SteamTxnUserInfoResponse>::GetDefault().result; }
};

template <>
struct StormReflTypeInfo<SteamTxnUserInfoResponse>::field_data_static<1>
{
  using member_type = SteamTxnUserInfoResponseParams; // SteamTxnUserInfoResponseParams
  static constexpr auto GetName() { return "params"; }
  static constexpr auto GetType() { return "SteamTxnUserInfoResponseParams"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8FCE0EF3; }
  static constexpr unsigned GetTypeNameHash() { return 0x54CE31D1; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &SteamTxnUserInfoResponse::params; }
};

template <typename Self>
struct StormReflTypeInfo<SteamTxnUserInfoResponse>::field_data<1, Self> : public StormReflTypeInfo<SteamTxnUserInfoResponse>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, SteamTxnUserInfoResponseParams> & Get() { return self.params; }
  std::add_const_t<std::remove_reference_t<SteamTxnUserInfoResponseParams>> & Get() const { return self.params; }
  void SetDefault() { self.params = StormReflTypeInfo<SteamTxnUserInfoResponse>::GetDefault().params; }
};

template <>
struct StormReflTypeInfo<SteamTxnUserInfo>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "SteamTxnUserInfo"; }
  static constexpr auto GetNameHash() { return 0x04266DAE; }
  static SteamTxnUserInfo & GetDefault() { static SteamTxnUserInfo def; return def; }
};

template <>
struct StormReflTypeInfo<SteamTxnUserInfo>::field_data_static<0>
{
  using member_type = SteamTxnUserInfoResponse; // SteamTxnUserInfoResponse
  static constexpr auto GetName() { return "response"; }
  static constexpr auto GetType() { return "SteamTxnUserInfoResponse"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3E7B0BFB; }
  static constexpr unsigned GetTypeNameHash() { return 0xB6DEF1DD; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SteamTxnUserInfo::response; }
};

template <typename Self>
struct StormReflTypeInfo<SteamTxnUserInfo>::field_data<0, Self> : public StormReflTypeInfo<SteamTxnUserInfo>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, SteamTxnUserInfoResponse> & Get() { return self.response; }
  std::add_const_t<std::remove_reference_t<SteamTxnUserInfoResponse>> & Get() const { return self.response; }
  void SetDefault() { self.response = StormReflTypeInfo<SteamTxnUserInfo>::GetDefault().response; }
};

namespace StormReflFileInfo
{
  struct SteamServerMessages
  {
    static const int types_n = 9;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct SteamServerMessages::type_info<0>
  {
    using type = ::SteamValidationResponseParams;
  };

  template <>
  struct SteamServerMessages::type_info<1>
  {
    using type = ::SteamValidationResponse;
  };

  template <>
  struct SteamServerMessages::type_info<2>
  {
    using type = ::SteamValidation;
  };

  template <>
  struct SteamServerMessages::type_info<3>
  {
    using type = ::SteamOwnershipResponseParams;
  };

  template <>
  struct SteamServerMessages::type_info<4>
  {
    using type = ::SteamOwnershipResponse;
  };

  template <>
  struct SteamServerMessages::type_info<5>
  {
    using type = ::SteamOwnership;
  };

  template <>
  struct SteamServerMessages::type_info<6>
  {
    using type = ::SteamTxnUserInfoResponseParams;
  };

  template <>
  struct SteamServerMessages::type_info<7>
  {
    using type = ::SteamTxnUserInfoResponse;
  };

  template <>
  struct SteamServerMessages::type_info<8>
  {
    using type = ::SteamTxnUserInfo;
  };

}

