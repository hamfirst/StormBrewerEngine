#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "SharedTypes.refl.h"


template <>
struct StormReflEnumInfo<ChannelJoinResult>
{
  static constexpr int elems_n = 3;
  static constexpr auto GetName() { return "ChannelJoinResult"; }
  static constexpr auto GetNameHash() { return 0x94A3601C; }
  template <int N> struct elems { };
};

template <>
struct StormReflEnumInfo<ChannelJoinResult>::elems<0>
{
  static constexpr auto GetName() { return "kSuccess"; }
  static constexpr auto GetNameHash() { return 0xD5725AD4; }
  static constexpr auto GetValue() { return ChannelJoinResult::kSuccess; }
};

template <>
struct StormReflEnumInfo<ChannelJoinResult>::elems<1>
{
  static constexpr auto GetName() { return "kLocked"; }
  static constexpr auto GetNameHash() { return 0x4861AB65; }
  static constexpr auto GetValue() { return ChannelJoinResult::kLocked; }
};

template <>
struct StormReflEnumInfo<ChannelJoinResult>::elems<2>
{
  static constexpr auto GetName() { return "kAlreadyIn"; }
  static constexpr auto GetNameHash() { return 0x6769BFCF; }
  static constexpr auto GetValue() { return ChannelJoinResult::kAlreadyIn; }
};

template <>
struct StormReflTypeInfo<UserGameInfo>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserGameInfo"; }
  static constexpr auto GetNameHash() { return 0xF088D28F; }
  static UserGameInfo & GetDefault() { static UserGameInfo def; return def; }
};

template <>
struct StormReflTypeInfo<UserGameInfo>::field_data_static<0>
{
  using member_type = RKey; // RNumber<unsigned long long>
  static constexpr auto GetName() { return "m_GameId"; }
  static constexpr auto GetType() { return "RNumber<unsigned long long>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA16AE06C; }
  static constexpr unsigned GetTypeNameHash() { return 0x656FF0F1; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserGameInfo::m_GameId; }
};

template <typename Self>
struct StormReflTypeInfo<UserGameInfo>::field_data<0, Self> : public StormReflTypeInfo<UserGameInfo>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RKey> & Get() { return self.m_GameId; }
  std::add_const_t<std::remove_reference_t<RKey>> & Get() const { return self.m_GameId; }
  void SetDefault() { self.m_GameId = StormReflTypeInfo<UserGameInfo>::GetDefault().m_GameId; }
};

template <>
struct StormReflTypeInfo<UserGameInfo>::field_data_static<1>
{
  using member_type = RKey; // RNumber<unsigned long long>
  static constexpr auto GetName() { return "m_GameServerId"; }
  static constexpr auto GetType() { return "RNumber<unsigned long long>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x219CFC9D; }
  static constexpr unsigned GetTypeNameHash() { return 0x656FF0F1; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserGameInfo::m_GameServerId; }
};

template <typename Self>
struct StormReflTypeInfo<UserGameInfo>::field_data<1, Self> : public StormReflTypeInfo<UserGameInfo>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RKey> & Get() { return self.m_GameServerId; }
  std::add_const_t<std::remove_reference_t<RKey>> & Get() const { return self.m_GameServerId; }
  void SetDefault() { self.m_GameServerId = StormReflTypeInfo<UserGameInfo>::GetDefault().m_GameServerId; }
};

template <>
struct StormReflTypeInfo<UserInfo>
{
  using MyBase = void;
  static constexpr int fields_n = 9;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserInfo"; }
  static constexpr auto GetNameHash() { return 0x34B0844E; }
  static UserInfo & GetDefault() { static UserInfo def; return def; }
};

template <>
struct StormReflTypeInfo<UserInfo>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserInfo::m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<UserInfo>::field_data<0, Self> : public StormReflTypeInfo<UserInfo>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<UserInfo>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<UserInfo>::field_data_static<1>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Squad"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x42E66F87; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserInfo::m_Squad; }
};

template <typename Self>
struct StormReflTypeInfo<UserInfo>::field_data<1, Self> : public StormReflTypeInfo<UserInfo>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Squad; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Squad; }
  void SetDefault() { self.m_Squad = StormReflTypeInfo<UserInfo>::GetDefault().m_Squad; }
};

template <>
struct StormReflTypeInfo<UserInfo>::field_data_static<2>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_SquadTag"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x74B2CC01; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UserInfo::m_SquadTag; }
};

template <typename Self>
struct StormReflTypeInfo<UserInfo>::field_data<2, Self> : public StormReflTypeInfo<UserInfo>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_SquadTag; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_SquadTag; }
  void SetDefault() { self.m_SquadTag = StormReflTypeInfo<UserInfo>::GetDefault().m_SquadTag; }
};

template <>
struct StormReflTypeInfo<UserInfo>::field_data_static<3>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_PlatformId"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0ED94F3C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &UserInfo::m_PlatformId; }
};

template <typename Self>
struct StormReflTypeInfo<UserInfo>::field_data<3, Self> : public StormReflTypeInfo<UserInfo>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_PlatformId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_PlatformId; }
  void SetDefault() { self.m_PlatformId = StormReflTypeInfo<UserInfo>::GetDefault().m_PlatformId; }
};

template <>
struct StormReflTypeInfo<UserInfo>::field_data_static<4>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Icon"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5B09BCC4; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &UserInfo::m_Icon; }
};

template <typename Self>
struct StormReflTypeInfo<UserInfo>::field_data<4, Self> : public StormReflTypeInfo<UserInfo>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Icon; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Icon; }
  void SetDefault() { self.m_Icon = StormReflTypeInfo<UserInfo>::GetDefault().m_Icon; }
};

template <>
struct StormReflTypeInfo<UserInfo>::field_data_static<5>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_AdminLevel"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xACAEF821; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &UserInfo::m_AdminLevel; }
};

template <typename Self>
struct StormReflTypeInfo<UserInfo>::field_data<5, Self> : public StormReflTypeInfo<UserInfo>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_AdminLevel; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_AdminLevel; }
  void SetDefault() { self.m_AdminLevel = StormReflTypeInfo<UserInfo>::GetDefault().m_AdminLevel; }
};

template <>
struct StormReflTypeInfo<UserInfo>::field_data_static<6>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_VisibleFlags"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5B00BCD9; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &UserInfo::m_VisibleFlags; }
};

template <typename Self>
struct StormReflTypeInfo<UserInfo>::field_data<6, Self> : public StormReflTypeInfo<UserInfo>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_VisibleFlags; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_VisibleFlags; }
  void SetDefault() { self.m_VisibleFlags = StormReflTypeInfo<UserInfo>::GetDefault().m_VisibleFlags; }
};

template <>
struct StormReflTypeInfo<UserInfo>::field_data_static<7>
{
  using member_type = RBool; // RBool
  static constexpr auto GetName() { return "m_Veteran"; }
  static constexpr auto GetType() { return "RBool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5E2C3AEA; }
  static constexpr unsigned GetTypeNameHash() { return 0x50062D06; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &UserInfo::m_Veteran; }
};

template <typename Self>
struct StormReflTypeInfo<UserInfo>::field_data<7, Self> : public StormReflTypeInfo<UserInfo>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RBool> & Get() { return self.m_Veteran; }
  std::add_const_t<std::remove_reference_t<RBool>> & Get() const { return self.m_Veteran; }
  void SetDefault() { self.m_Veteran = StormReflTypeInfo<UserInfo>::GetDefault().m_Veteran; }
};

template <>
struct StormReflTypeInfo<UserInfo>::field_data_static<8>
{
  using member_type = UserGameInfo; // UserGameInfo
  static constexpr auto GetName() { return "m_Game"; }
  static constexpr auto GetType() { return "UserGameInfo"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1DB6A493; }
  static constexpr unsigned GetTypeNameHash() { return 0xF088D28F; }
  static constexpr auto GetFieldIndex() { return 8; }
  static constexpr auto GetMemberPtr() { return &UserInfo::m_Game; }
};

template <typename Self>
struct StormReflTypeInfo<UserInfo>::field_data<8, Self> : public StormReflTypeInfo<UserInfo>::field_data_static<8>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, UserGameInfo> & Get() { return self.m_Game; }
  std::add_const_t<std::remove_reference_t<UserGameInfo>> & Get() const { return self.m_Game; }
  void SetDefault() { self.m_Game = StormReflTypeInfo<UserInfo>::GetDefault().m_Game; }
};

template <>
struct StormReflTypeInfo<UserApplication>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserApplication"; }
  static constexpr auto GetNameHash() { return 0x6E2E5A1C; }
  static UserApplication & GetDefault() { static UserApplication def; return def; }
};

template <>
struct StormReflTypeInfo<UserApplication>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_SquadName"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5DE2A771; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserApplication::m_SquadName; }
};

template <typename Self>
struct StormReflTypeInfo<UserApplication>::field_data<0, Self> : public StormReflTypeInfo<UserApplication>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_SquadName; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_SquadName; }
  void SetDefault() { self.m_SquadName = StormReflTypeInfo<UserApplication>::GetDefault().m_SquadName; }
};

template <>
struct StormReflTypeInfo<UserApplication>::field_data_static<1>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_SquadTag"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x74B2CC01; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserApplication::m_SquadTag; }
};

template <typename Self>
struct StormReflTypeInfo<UserApplication>::field_data<1, Self> : public StormReflTypeInfo<UserApplication>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_SquadTag; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_SquadTag; }
  void SetDefault() { self.m_SquadTag = StormReflTypeInfo<UserApplication>::GetDefault().m_SquadTag; }
};

template <>
struct StormReflTypeInfo<UserApplication>::field_data_static<2>
{
  using member_type = RKey; // RNumber<unsigned long long>
  static constexpr auto GetName() { return "m_SquadId"; }
  static constexpr auto GetType() { return "RNumber<unsigned long long>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x83727351; }
  static constexpr unsigned GetTypeNameHash() { return 0x656FF0F1; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UserApplication::m_SquadId; }
};

template <typename Self>
struct StormReflTypeInfo<UserApplication>::field_data<2, Self> : public StormReflTypeInfo<UserApplication>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RKey> & Get() { return self.m_SquadId; }
  std::add_const_t<std::remove_reference_t<RKey>> & Get() const { return self.m_SquadId; }
  void SetDefault() { self.m_SquadId = StormReflTypeInfo<UserApplication>::GetDefault().m_SquadId; }
};

template <>
struct StormReflTypeInfo<ChannelMember>
{
  using MyBase = void;
  static constexpr int fields_n = 9;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ChannelMember"; }
  static constexpr auto GetNameHash() { return 0xF92F50BF; }
  static ChannelMember & GetDefault() { static ChannelMember def; return def; }
};

template <>
struct StormReflTypeInfo<ChannelMember>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &ChannelMember::m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<ChannelMember>::field_data<0, Self> : public StormReflTypeInfo<ChannelMember>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<ChannelMember>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<ChannelMember>::field_data_static<1>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_SquadTag"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x74B2CC01; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &ChannelMember::m_SquadTag; }
};

template <typename Self>
struct StormReflTypeInfo<ChannelMember>::field_data<1, Self> : public StormReflTypeInfo<ChannelMember>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_SquadTag; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_SquadTag; }
  void SetDefault() { self.m_SquadTag = StormReflTypeInfo<ChannelMember>::GetDefault().m_SquadTag; }
};

template <>
struct StormReflTypeInfo<ChannelMember>::field_data_static<2>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_UserKey"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE6008E39; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &ChannelMember::m_UserKey; }
};

template <typename Self>
struct StormReflTypeInfo<ChannelMember>::field_data<2, Self> : public StormReflTypeInfo<ChannelMember>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_UserKey; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_UserKey; }
  void SetDefault() { self.m_UserKey = StormReflTypeInfo<ChannelMember>::GetDefault().m_UserKey; }
};

template <>
struct StormReflTypeInfo<ChannelMember>::field_data_static<3>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_PlatformId"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0ED94F3C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &ChannelMember::m_PlatformId; }
};

template <typename Self>
struct StormReflTypeInfo<ChannelMember>::field_data<3, Self> : public StormReflTypeInfo<ChannelMember>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_PlatformId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_PlatformId; }
  void SetDefault() { self.m_PlatformId = StormReflTypeInfo<ChannelMember>::GetDefault().m_PlatformId; }
};

template <>
struct StormReflTypeInfo<ChannelMember>::field_data_static<4>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Icon"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5B09BCC4; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &ChannelMember::m_Icon; }
};

template <typename Self>
struct StormReflTypeInfo<ChannelMember>::field_data<4, Self> : public StormReflTypeInfo<ChannelMember>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Icon; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Icon; }
  void SetDefault() { self.m_Icon = StormReflTypeInfo<ChannelMember>::GetDefault().m_Icon; }
};

template <>
struct StormReflTypeInfo<ChannelMember>::field_data_static<5>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_AdminLevel"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xACAEF821; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &ChannelMember::m_AdminLevel; }
};

template <typename Self>
struct StormReflTypeInfo<ChannelMember>::field_data<5, Self> : public StormReflTypeInfo<ChannelMember>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_AdminLevel; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_AdminLevel; }
  void SetDefault() { self.m_AdminLevel = StormReflTypeInfo<ChannelMember>::GetDefault().m_AdminLevel; }
};

template <>
struct StormReflTypeInfo<ChannelMember>::field_data_static<6>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_VisibleFlags"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5B00BCD9; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &ChannelMember::m_VisibleFlags; }
};

template <typename Self>
struct StormReflTypeInfo<ChannelMember>::field_data<6, Self> : public StormReflTypeInfo<ChannelMember>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_VisibleFlags; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_VisibleFlags; }
  void SetDefault() { self.m_VisibleFlags = StormReflTypeInfo<ChannelMember>::GetDefault().m_VisibleFlags; }
};

template <>
struct StormReflTypeInfo<ChannelMember>::field_data_static<7>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_MembershipFlags"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5DCFBCE8; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &ChannelMember::m_MembershipFlags; }
};

template <typename Self>
struct StormReflTypeInfo<ChannelMember>::field_data<7, Self> : public StormReflTypeInfo<ChannelMember>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_MembershipFlags; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_MembershipFlags; }
  void SetDefault() { self.m_MembershipFlags = StormReflTypeInfo<ChannelMember>::GetDefault().m_MembershipFlags; }
};

template <>
struct StormReflTypeInfo<ChannelMember>::field_data_static<8>
{
  using member_type = UserGameInfo; // UserGameInfo
  static constexpr auto GetName() { return "m_Game"; }
  static constexpr auto GetType() { return "UserGameInfo"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1DB6A493; }
  static constexpr unsigned GetTypeNameHash() { return 0xF088D28F; }
  static constexpr auto GetFieldIndex() { return 8; }
  static constexpr auto GetMemberPtr() { return &ChannelMember::m_Game; }
};

template <typename Self>
struct StormReflTypeInfo<ChannelMember>::field_data<8, Self> : public StormReflTypeInfo<ChannelMember>::field_data_static<8>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, UserGameInfo> & Get() { return self.m_Game; }
  std::add_const_t<std::remove_reference_t<UserGameInfo>> & Get() const { return self.m_Game; }
  void SetDefault() { self.m_Game = StormReflTypeInfo<ChannelMember>::GetDefault().m_Game; }
};

template <>
struct StormReflTypeInfo<ChannelBot>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ChannelBot"; }
  static constexpr auto GetNameHash() { return 0x62BB25BB; }
  static ChannelBot & GetDefault() { static ChannelBot def; return def; }
};

template <>
struct StormReflTypeInfo<ChannelBot>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &ChannelBot::m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<ChannelBot>::field_data<0, Self> : public StormReflTypeInfo<ChannelBot>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<ChannelBot>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<ChannelBot>::field_data_static<1>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_BotKey"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0B62BB36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &ChannelBot::m_BotKey; }
};

template <typename Self>
struct StormReflTypeInfo<ChannelBot>::field_data<1, Self> : public StormReflTypeInfo<ChannelBot>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_BotKey; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_BotKey; }
  void SetDefault() { self.m_BotKey = StormReflTypeInfo<ChannelBot>::GetDefault().m_BotKey; }
};

template <>
struct StormReflTypeInfo<ChannelInfo>
{
  using MyBase = void;
  static constexpr int fields_n = 6;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ChannelInfo"; }
  static constexpr auto GetNameHash() { return 0xFDE9DF80; }
  static ChannelInfo & GetDefault() { static ChannelInfo def; return def; }
};

template <>
struct StormReflTypeInfo<ChannelInfo>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &ChannelInfo::m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<ChannelInfo>::field_data<0, Self> : public StormReflTypeInfo<ChannelInfo>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<ChannelInfo>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<ChannelInfo>::field_data_static<1>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Motd"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x9492F073; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &ChannelInfo::m_Motd; }
};

template <typename Self>
struct StormReflTypeInfo<ChannelInfo>::field_data<1, Self> : public StormReflTypeInfo<ChannelInfo>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Motd; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Motd; }
  void SetDefault() { self.m_Motd = StormReflTypeInfo<ChannelInfo>::GetDefault().m_Motd; }
};

template <>
struct StormReflTypeInfo<ChannelInfo>::field_data_static<2>
{
  using member_type = RKey; // RNumber<unsigned long long>
  static constexpr auto GetName() { return "m_ChannelKey"; }
  static constexpr auto GetType() { return "RNumber<unsigned long long>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2CD0601E; }
  static constexpr unsigned GetTypeNameHash() { return 0x656FF0F1; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &ChannelInfo::m_ChannelKey; }
};

template <typename Self>
struct StormReflTypeInfo<ChannelInfo>::field_data<2, Self> : public StormReflTypeInfo<ChannelInfo>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RKey> & Get() { return self.m_ChannelKey; }
  std::add_const_t<std::remove_reference_t<RKey>> & Get() const { return self.m_ChannelKey; }
  void SetDefault() { self.m_ChannelKey = StormReflTypeInfo<ChannelInfo>::GetDefault().m_ChannelKey; }
};

template <>
struct StormReflTypeInfo<ChannelInfo>::field_data_static<3>
{
  using member_type = RBool; // RBool
  static constexpr auto GetName() { return "m_Locked"; }
  static constexpr auto GetType() { return "RBool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA7ED9F59; }
  static constexpr unsigned GetTypeNameHash() { return 0x50062D06; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &ChannelInfo::m_Locked; }
};

template <typename Self>
struct StormReflTypeInfo<ChannelInfo>::field_data<3, Self> : public StormReflTypeInfo<ChannelInfo>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RBool> & Get() { return self.m_Locked; }
  std::add_const_t<std::remove_reference_t<RBool>> & Get() const { return self.m_Locked; }
  void SetDefault() { self.m_Locked = StormReflTypeInfo<ChannelInfo>::GetDefault().m_Locked; }
};

template <>
struct StormReflTypeInfo<ChannelInfo>::field_data_static<4>
{
  using member_type = RSparseList<ChannelMember>; // RSparseList<ChannelMember>
  static constexpr auto GetName() { return "m_Users"; }
  static constexpr auto GetType() { return "RSparseList<ChannelMember>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x99B53589; }
  static constexpr unsigned GetTypeNameHash() { return 0x3532E9AF; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &ChannelInfo::m_Users; }
};

template <typename Self>
struct StormReflTypeInfo<ChannelInfo>::field_data<4, Self> : public StormReflTypeInfo<ChannelInfo>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RSparseList<ChannelMember>> & Get() { return self.m_Users; }
  std::add_const_t<std::remove_reference_t<RSparseList<ChannelMember>>> & Get() const { return self.m_Users; }
  void SetDefault() { self.m_Users = StormReflTypeInfo<ChannelInfo>::GetDefault().m_Users; }
};

template <>
struct StormReflTypeInfo<ChannelInfo>::field_data_static<5>
{
  using member_type = RMergeList<ChannelBot>; // RMergeList<ChannelBot>
  static constexpr auto GetName() { return "m_Bots"; }
  static constexpr auto GetType() { return "RMergeList<ChannelBot>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x4F2265E2; }
  static constexpr unsigned GetTypeNameHash() { return 0x54EF326B; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &ChannelInfo::m_Bots; }
};

template <typename Self>
struct StormReflTypeInfo<ChannelInfo>::field_data<5, Self> : public StormReflTypeInfo<ChannelInfo>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<ChannelBot>> & Get() { return self.m_Bots; }
  std::add_const_t<std::remove_reference_t<RMergeList<ChannelBot>>> & Get() const { return self.m_Bots; }
  void SetDefault() { self.m_Bots = StormReflTypeInfo<ChannelInfo>::GetDefault().m_Bots; }
};

template <>
struct StormReflTypeInfo<SquadMember>
{
  using MyBase = void;
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "SquadMember"; }
  static constexpr auto GetNameHash() { return 0x8C56F4CB; }
  static SquadMember & GetDefault() { static SquadMember def; return def; }
};

template <>
struct StormReflTypeInfo<SquadMember>::field_data_static<0>
{
  using member_type = RKey; // RNumber<unsigned long long>
  static constexpr auto GetName() { return "m_UserKey"; }
  static constexpr auto GetType() { return "RNumber<unsigned long long>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE6008E39; }
  static constexpr unsigned GetTypeNameHash() { return 0x656FF0F1; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SquadMember::m_UserKey; }
};

template <typename Self>
struct StormReflTypeInfo<SquadMember>::field_data<0, Self> : public StormReflTypeInfo<SquadMember>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RKey> & Get() { return self.m_UserKey; }
  std::add_const_t<std::remove_reference_t<RKey>> & Get() const { return self.m_UserKey; }
  void SetDefault() { self.m_UserKey = StormReflTypeInfo<SquadMember>::GetDefault().m_UserKey; }
};

template <>
struct StormReflTypeInfo<SquadMember>::field_data_static<1>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &SquadMember::m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<SquadMember>::field_data<1, Self> : public StormReflTypeInfo<SquadMember>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<SquadMember>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<SquadMember>::field_data_static<2>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_Joined"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x18C25ECB; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &SquadMember::m_Joined; }
};

template <typename Self>
struct StormReflTypeInfo<SquadMember>::field_data<2, Self> : public StormReflTypeInfo<SquadMember>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_Joined; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_Joined; }
  void SetDefault() { self.m_Joined = StormReflTypeInfo<SquadMember>::GetDefault().m_Joined; }
};

template <>
struct StormReflTypeInfo<SquadMember>::field_data_static<3>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_MembershipFlags"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5DCFBCE8; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &SquadMember::m_MembershipFlags; }
};

template <typename Self>
struct StormReflTypeInfo<SquadMember>::field_data<3, Self> : public StormReflTypeInfo<SquadMember>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_MembershipFlags; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_MembershipFlags; }
  void SetDefault() { self.m_MembershipFlags = StormReflTypeInfo<SquadMember>::GetDefault().m_MembershipFlags; }
};

template <>
struct StormReflTypeInfo<SquadApplication>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "SquadApplication"; }
  static constexpr auto GetNameHash() { return 0x6D305CF9; }
  static SquadApplication & GetDefault() { static SquadApplication def; return def; }
};

template <>
struct StormReflTypeInfo<SquadApplication>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_UserName"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAE407D67; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SquadApplication::m_UserName; }
};

template <typename Self>
struct StormReflTypeInfo<SquadApplication>::field_data<0, Self> : public StormReflTypeInfo<SquadApplication>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_UserName; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_UserName; }
  void SetDefault() { self.m_UserName = StormReflTypeInfo<SquadApplication>::GetDefault().m_UserName; }
};

template <>
struct StormReflTypeInfo<SquadApplication>::field_data_static<1>
{
  using member_type = RKey; // RNumber<unsigned long long>
  static constexpr auto GetName() { return "m_UserKey"; }
  static constexpr auto GetType() { return "RNumber<unsigned long long>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE6008E39; }
  static constexpr unsigned GetTypeNameHash() { return 0x656FF0F1; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &SquadApplication::m_UserKey; }
};

template <typename Self>
struct StormReflTypeInfo<SquadApplication>::field_data<1, Self> : public StormReflTypeInfo<SquadApplication>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RKey> & Get() { return self.m_UserKey; }
  std::add_const_t<std::remove_reference_t<RKey>> & Get() const { return self.m_UserKey; }
  void SetDefault() { self.m_UserKey = StormReflTypeInfo<SquadApplication>::GetDefault().m_UserKey; }
};

template <>
struct StormReflTypeInfo<SquadInfo>
{
  using MyBase = void;
  static constexpr int fields_n = 8;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "SquadInfo"; }
  static constexpr auto GetNameHash() { return 0x96994B98; }
  static SquadInfo & GetDefault() { static SquadInfo def; return def; }
};

template <>
struct StormReflTypeInfo<SquadInfo>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SquadInfo::m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<SquadInfo>::field_data<0, Self> : public StormReflTypeInfo<SquadInfo>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<SquadInfo>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<SquadInfo>::field_data_static<1>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Tag"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF06B7364; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &SquadInfo::m_Tag; }
};

template <typename Self>
struct StormReflTypeInfo<SquadInfo>::field_data<1, Self> : public StormReflTypeInfo<SquadInfo>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Tag; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Tag; }
  void SetDefault() { self.m_Tag = StormReflTypeInfo<SquadInfo>::GetDefault().m_Tag; }
};

template <>
struct StormReflTypeInfo<SquadInfo>::field_data_static<2>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Motd"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x9492F073; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &SquadInfo::m_Motd; }
};

template <typename Self>
struct StormReflTypeInfo<SquadInfo>::field_data<2, Self> : public StormReflTypeInfo<SquadInfo>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Motd; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Motd; }
  void SetDefault() { self.m_Motd = StormReflTypeInfo<SquadInfo>::GetDefault().m_Motd; }
};

template <>
struct StormReflTypeInfo<SquadInfo>::field_data_static<3>
{
  using member_type = RKey; // RNumber<unsigned long long>
  static constexpr auto GetName() { return "m_SquadKey"; }
  static constexpr auto GetType() { return "RNumber<unsigned long long>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFDABD02B; }
  static constexpr unsigned GetTypeNameHash() { return 0x656FF0F1; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &SquadInfo::m_SquadKey; }
};

template <typename Self>
struct StormReflTypeInfo<SquadInfo>::field_data<3, Self> : public StormReflTypeInfo<SquadInfo>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RKey> & Get() { return self.m_SquadKey; }
  std::add_const_t<std::remove_reference_t<RKey>> & Get() const { return self.m_SquadKey; }
  void SetDefault() { self.m_SquadKey = StormReflTypeInfo<SquadInfo>::GetDefault().m_SquadKey; }
};

template <>
struct StormReflTypeInfo<SquadInfo>::field_data_static<4>
{
  using member_type = RBool; // RBool
  static constexpr auto GetName() { return "m_Locked"; }
  static constexpr auto GetType() { return "RBool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA7ED9F59; }
  static constexpr unsigned GetTypeNameHash() { return 0x50062D06; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &SquadInfo::m_Locked; }
};

template <typename Self>
struct StormReflTypeInfo<SquadInfo>::field_data<4, Self> : public StormReflTypeInfo<SquadInfo>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RBool> & Get() { return self.m_Locked; }
  std::add_const_t<std::remove_reference_t<RBool>> & Get() const { return self.m_Locked; }
  void SetDefault() { self.m_Locked = StormReflTypeInfo<SquadInfo>::GetDefault().m_Locked; }
};

template <>
struct StormReflTypeInfo<SquadInfo>::field_data_static<5>
{
  using member_type = RSparseList<SquadMember>; // RSparseList<SquadMember>
  static constexpr auto GetName() { return "m_Users"; }
  static constexpr auto GetType() { return "RSparseList<SquadMember>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x99B53589; }
  static constexpr unsigned GetTypeNameHash() { return 0xAAA9B9AE; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &SquadInfo::m_Users; }
};

template <typename Self>
struct StormReflTypeInfo<SquadInfo>::field_data<5, Self> : public StormReflTypeInfo<SquadInfo>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RSparseList<SquadMember>> & Get() { return self.m_Users; }
  std::add_const_t<std::remove_reference_t<RSparseList<SquadMember>>> & Get() const { return self.m_Users; }
  void SetDefault() { self.m_Users = StormReflTypeInfo<SquadInfo>::GetDefault().m_Users; }
};

template <>
struct StormReflTypeInfo<SquadInfo>::field_data_static<6>
{
  using member_type = RSparseList<SquadApplication>; // RSparseList<SquadApplication>
  static constexpr auto GetName() { return "m_Applicants"; }
  static constexpr auto GetType() { return "RSparseList<SquadApplication>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF5162316; }
  static constexpr unsigned GetTypeNameHash() { return 0x730100BA; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &SquadInfo::m_Applicants; }
};

template <typename Self>
struct StormReflTypeInfo<SquadInfo>::field_data<6, Self> : public StormReflTypeInfo<SquadInfo>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RSparseList<SquadApplication>> & Get() { return self.m_Applicants; }
  std::add_const_t<std::remove_reference_t<RSparseList<SquadApplication>>> & Get() const { return self.m_Applicants; }
  void SetDefault() { self.m_Applicants = StormReflTypeInfo<SquadInfo>::GetDefault().m_Applicants; }
};

template <>
struct StormReflTypeInfo<SquadInfo>::field_data_static<7>
{
  using member_type = RSparseList<SquadApplication>; // RSparseList<SquadApplication>
  static constexpr auto GetName() { return "m_Requests"; }
  static constexpr auto GetType() { return "RSparseList<SquadApplication>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8DA9027F; }
  static constexpr unsigned GetTypeNameHash() { return 0x730100BA; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &SquadInfo::m_Requests; }
};

template <typename Self>
struct StormReflTypeInfo<SquadInfo>::field_data<7, Self> : public StormReflTypeInfo<SquadInfo>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RSparseList<SquadApplication>> & Get() { return self.m_Requests; }
  std::add_const_t<std::remove_reference_t<RSparseList<SquadApplication>>> & Get() const { return self.m_Requests; }
  void SetDefault() { self.m_Requests = StormReflTypeInfo<SquadInfo>::GetDefault().m_Requests; }
};

namespace StormReflFileInfo
{
  struct SharedTypes
  {
    static const int types_n = 9;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct SharedTypes::type_info<0>
  {
    using type = ::UserGameInfo;
  };

  template <>
  struct SharedTypes::type_info<1>
  {
    using type = ::UserInfo;
  };

  template <>
  struct SharedTypes::type_info<2>
  {
    using type = ::UserApplication;
  };

  template <>
  struct SharedTypes::type_info<3>
  {
    using type = ::ChannelMember;
  };

  template <>
  struct SharedTypes::type_info<4>
  {
    using type = ::ChannelBot;
  };

  template <>
  struct SharedTypes::type_info<5>
  {
    using type = ::ChannelInfo;
  };

  template <>
  struct SharedTypes::type_info<6>
  {
    using type = ::SquadMember;
  };

  template <>
  struct SharedTypes::type_info<7>
  {
    using type = ::SquadApplication;
  };

  template <>
  struct SharedTypes::type_info<8>
  {
    using type = ::SquadInfo;
  };

}

