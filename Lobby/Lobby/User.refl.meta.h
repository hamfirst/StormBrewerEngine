#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "User.refl.h"
#include "HurricaneDDS/DDSThrottle.refl.meta.h"
#include "Game/GameNetworkData.refl.meta.h"
#include "LobbyShared/SharedTypes.refl.meta.h"
#include "Lobby/GameData.refl.meta.h"


template <>
struct StormReflTypeInfo<UserDatabaseObject>
{
  using MyBase = void;
  static constexpr int fields_n = 21;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserDatabaseObject"; }
  static constexpr auto GetNameHash() { return 0x8BDD1F29; }
  static constexpr bool HasDefault() { return true; }
  static UserDatabaseObject & GetDefault() { static UserDatabaseObject def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<UserDatabaseObject *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const UserDatabaseObject *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<UserDatabaseObject *>(ptr);
    if(typeid(UserDatabaseObject).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const UserDatabaseObject *>(ptr);
    if(typeid(UserDatabaseObject).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_UserName"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAE407D67; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_UserName; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_UserName; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_UserName; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<0, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_UserName; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_UserName; }
  void SetDefault() { self.m_UserName = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_UserName; }
};

template <>
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<1>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_UserNameLower"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3D029B9C; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_UserNameLower; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_UserNameLower; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_UserNameLower; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<1, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_UserNameLower; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_UserNameLower; }
  void SetDefault() { self.m_UserNameLower = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_UserNameLower; }
};

template <>
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<2>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Platform"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0xCF7E04E5; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_Platform; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_Platform; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_Platform; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<2, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Platform; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Platform; }
  void SetDefault() { self.m_Platform = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_Platform; }
};

template <>
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<3>
{
  using member_type = RKey; // RNumber<unsigned long>
  static constexpr auto GetName() { return "m_PlatformId"; }
  static constexpr auto GetType() { return "RNumber<unsigned long>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0ED94F3C; }
  static constexpr unsigned GetTypeNameHash() { return 0xFD825A3A; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_PlatformId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_PlatformId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_PlatformId; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<3, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RKey> & Get() { return self.m_PlatformId; }
  std::add_const_t<std::remove_reference_t<RKey>> & Get() const { return self.m_PlatformId; }
  void SetDefault() { self.m_PlatformId = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_PlatformId; }
};

template <>
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<4>
{
  using member_type = RBool; // RBool
  static constexpr auto GetName() { return "m_IsGuest"; }
  static constexpr auto GetType() { return "RBool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x30529EDE; }
  static constexpr unsigned GetTypeNameHash() { return 0x50062D06; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_IsGuest; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_IsGuest; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_IsGuest; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<4, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RBool> & Get() { return self.m_IsGuest; }
  std::add_const_t<std::remove_reference_t<RBool>> & Get() const { return self.m_IsGuest; }
  void SetDefault() { self.m_IsGuest = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_IsGuest; }
};

template <>
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<5>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_AdminLevel"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xACAEF821; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_AdminLevel; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_AdminLevel; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_AdminLevel; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<5, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_AdminLevel; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_AdminLevel; }
  void SetDefault() { self.m_AdminLevel = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_AdminLevel; }
};

template <>
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<6>
{
  using member_type = RMap<uint32_t, UserRankInfo>; // RMap<unsigned int, UserRankInfo>
  static constexpr auto GetName() { return "m_CompetitiveRanks"; }
  static constexpr auto GetType() { return "RMap<unsigned int, UserRankInfo>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC5AA7F45; }
  static constexpr unsigned GetTypeNameHash() { return 0xB9C97FF6; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_CompetitiveRanks; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_CompetitiveRanks; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_CompetitiveRanks; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<6, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMap<uint32_t, UserRankInfo>> & Get() { return self.m_CompetitiveRanks; }
  std::add_const_t<std::remove_reference_t<RMap<uint32_t, UserRankInfo>>> & Get() const { return self.m_CompetitiveRanks; }
  void SetDefault() { self.m_CompetitiveRanks = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_CompetitiveRanks; }
};

template <>
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<7>
{
  using member_type = RNumber<time_t>; // RNumber<long>
  static constexpr auto GetName() { return "m_CompetitiveBanStart"; }
  static constexpr auto GetType() { return "RNumber<long>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x64FD4CA0; }
  static constexpr unsigned GetTypeNameHash() { return 0x605EABF6; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_CompetitiveBanStart; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_CompetitiveBanStart; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_CompetitiveBanStart; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<7, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RNumber<time_t>> & Get() { return self.m_CompetitiveBanStart; }
  std::add_const_t<std::remove_reference_t<RNumber<time_t>>> & Get() const { return self.m_CompetitiveBanStart; }
  void SetDefault() { self.m_CompetitiveBanStart = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_CompetitiveBanStart; }
};

template <>
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<8>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_CompetitiveBanDuration"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC49B6FC7; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 8; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_CompetitiveBanDuration; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_CompetitiveBanDuration; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_CompetitiveBanDuration; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<8, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<8>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_CompetitiveBanDuration; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_CompetitiveBanDuration; }
  void SetDefault() { self.m_CompetitiveBanDuration = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_CompetitiveBanDuration; }
};

template <>
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<9>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_CompetitiveBanProbation"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x115D2029; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 9; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_CompetitiveBanProbation; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_CompetitiveBanProbation; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_CompetitiveBanProbation; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<9, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<9>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_CompetitiveBanProbation; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_CompetitiveBanProbation; }
  void SetDefault() { self.m_CompetitiveBanProbation = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_CompetitiveBanProbation; }
};

template <>
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<10>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_Created"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x27CFC26D; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 10; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_Created; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_Created; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_Created; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<10, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<10>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_Created; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_Created; }
  void SetDefault() { self.m_Created = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_Created; }
};

template <>
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<11>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_Title"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA600E80B; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 11; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_Title; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_Title; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_Title; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<11, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<11>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_Title; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_Title; }
  void SetDefault() { self.m_Title = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_Title; }
};

template <>
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<12>
{
  using member_type = RMergeList<RInt>; // RMergeList<RNumber<int> >
  static constexpr auto GetName() { return "m_TitleList"; }
  static constexpr auto GetType() { return "RMergeList<RNumber<int> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xABBF57E2; }
  static constexpr unsigned GetTypeNameHash() { return 0xA536E2BA; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 12; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_TitleList; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_TitleList; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_TitleList; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<12, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<12>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<RInt>> & Get() { return self.m_TitleList; }
  std::add_const_t<std::remove_reference_t<RMergeList<RInt>>> & Get() const { return self.m_TitleList; }
  void SetDefault() { self.m_TitleList = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_TitleList; }
};

template <>
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<13>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_Icon"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5B09BCC4; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 13; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_Icon; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_Icon; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_Icon; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<13, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<13>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_Icon; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_Icon; }
  void SetDefault() { self.m_Icon = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_Icon; }
};

template <>
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<14>
{
  using member_type = RMergeList<RInt>; // RMergeList<RNumber<int> >
  static constexpr auto GetName() { return "m_IconList"; }
  static constexpr auto GetType() { return "RMergeList<RNumber<int> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFCEA1A36; }
  static constexpr unsigned GetTypeNameHash() { return 0xA536E2BA; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 14; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_IconList; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_IconList; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_IconList; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<14, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<14>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<RInt>> & Get() { return self.m_IconList; }
  std::add_const_t<std::remove_reference_t<RMergeList<RInt>>> & Get() const { return self.m_IconList; }
  void SetDefault() { self.m_IconList = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_IconList; }
};

template <>
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<15>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_Celebration"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x47D906C2; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 15; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_Celebration; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_Celebration; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_Celebration; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<15, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<15>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_Celebration; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_Celebration; }
  void SetDefault() { self.m_Celebration = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_Celebration; }
};

template <>
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<16>
{
  using member_type = RMergeList<RInt>; // RMergeList<RNumber<int> >
  static constexpr auto GetName() { return "m_CelebrationList"; }
  static constexpr auto GetType() { return "RMergeList<RNumber<int> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8471A77C; }
  static constexpr unsigned GetTypeNameHash() { return 0xA536E2BA; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 16; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_CelebrationList; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_CelebrationList; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_CelebrationList; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<16, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<16>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<RInt>> & Get() { return self.m_CelebrationList; }
  std::add_const_t<std::remove_reference_t<RMergeList<RInt>>> & Get() const { return self.m_CelebrationList; }
  void SetDefault() { self.m_CelebrationList = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_CelebrationList; }
};

template <>
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<17>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_LastGamePlayed"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDC1A80E1; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 17; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_LastGamePlayed; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_LastGamePlayed; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_LastGamePlayed; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<17, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<17>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_LastGamePlayed; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_LastGamePlayed; }
  void SetDefault() { self.m_LastGamePlayed = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_LastGamePlayed; }
};

template <>
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<18>
{
  using member_type = GameStatsData; // GameStatsData
  static constexpr auto GetName() { return "m_Stats"; }
  static constexpr auto GetType() { return "GameStatsData"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDA71F7CA; }
  static constexpr unsigned GetTypeNameHash() { return 0x9CB3161C; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 18; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_Stats; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_Stats; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_Stats; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<18, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<18>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameStatsData> & Get() { return self.m_Stats; }
  std::add_const_t<std::remove_reference_t<GameStatsData>> & Get() const { return self.m_Stats; }
  void SetDefault() { self.m_Stats = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_Stats; }
};

template <>
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<19>
{
  using member_type = UserPersistent; // UserPersistent
  static constexpr auto GetName() { return "m_Persistent"; }
  static constexpr auto GetType() { return "UserPersistent"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2DA59512; }
  static constexpr unsigned GetTypeNameHash() { return 0x68592B2E; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 19; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_Persistent; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_Persistent; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_Persistent; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<19, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<19>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, UserPersistent> & Get() { return self.m_Persistent; }
  std::add_const_t<std::remove_reference_t<UserPersistent>> & Get() const { return self.m_Persistent; }
  void SetDefault() { self.m_Persistent = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_Persistent; }
};

template <>
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<20>
{
  using member_type = RMergeList<RString>; // RMergeList<RString>
  static constexpr auto GetName() { return "m_HistoryHosts"; }
  static constexpr auto GetType() { return "RMergeList<RString>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE89E30BC; }
  static constexpr unsigned GetTypeNameHash() { return 0x8C9238EC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 20; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_HistoryHosts; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_HistoryHosts; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_HistoryHosts; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<20, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<20>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<RString>> & Get() { return self.m_HistoryHosts; }
  std::add_const_t<std::remove_reference_t<RMergeList<RString>>> & Get() const { return self.m_HistoryHosts; }
  void SetDefault() { self.m_HistoryHosts = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_HistoryHosts; }
};

template <>
struct StormReflTypeInfo<UserNameLookup>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserNameLookup"; }
  static constexpr auto GetNameHash() { return 0x7CEB5D1B; }
  static constexpr bool HasDefault() { return false; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<UserNameLookup *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const UserNameLookup *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<UserNameLookup *>(ptr);
    if(typeid(UserNameLookup).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const UserNameLookup *>(ptr);
    if(typeid(UserNameLookup).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<UserNameLookup>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_UserNameLower"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3D029B9C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserNameLookup::m_UserNameLower; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserNameLookup *>(obj); return &ptr->m_UserNameLower; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserNameLookup *>(obj); return &ptr->m_UserNameLower; }
};

template <typename Self>
struct StormReflTypeInfo<UserNameLookup>::field_data<0, Self> : public StormReflTypeInfo<UserNameLookup>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_UserNameLower; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_UserNameLower; }
};

template <>
struct StormReflTypeInfo<UserPlatformIdLookup>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserPlatformIdLookup"; }
  static constexpr auto GetNameHash() { return 0x69C7F0F3; }
  static constexpr bool HasDefault() { return false; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<UserPlatformIdLookup *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const UserPlatformIdLookup *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<UserPlatformIdLookup *>(ptr);
    if(typeid(UserPlatformIdLookup).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const UserPlatformIdLookup *>(ptr);
    if(typeid(UserPlatformIdLookup).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<UserPlatformIdLookup>::field_data_static<0>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_PlatformId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0ED94F3C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserPlatformIdLookup::m_PlatformId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserPlatformIdLookup *>(obj); return &ptr->m_PlatformId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserPlatformIdLookup *>(obj); return &ptr->m_PlatformId; }
};

template <typename Self>
struct StormReflTypeInfo<UserPlatformIdLookup>::field_data<0, Self> : public StormReflTypeInfo<UserPlatformIdLookup>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_PlatformId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_PlatformId; }
};

template <>
struct StormReflTypeInfo<UserGameJoinInfo>
{
  using MyBase = void;
  static constexpr int fields_n = 7;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserGameJoinInfo"; }
  static constexpr auto GetNameHash() { return 0xFAA5AE37; }
  static constexpr bool HasDefault() { return true; }
  static UserGameJoinInfo & GetDefault() { static UserGameJoinInfo def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<UserGameJoinInfo *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const UserGameJoinInfo *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<UserGameJoinInfo *>(ptr);
    if(typeid(UserGameJoinInfo).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const UserGameJoinInfo *>(ptr);
    if(typeid(UserGameJoinInfo).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<UserGameJoinInfo>::field_data_static<0>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_EndpointId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFC70D3D1; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserGameJoinInfo::m_EndpointId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserGameJoinInfo *>(obj); return &ptr->m_EndpointId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserGameJoinInfo *>(obj); return &ptr->m_EndpointId; }
};

template <typename Self>
struct StormReflTypeInfo<UserGameJoinInfo>::field_data<0, Self> : public StormReflTypeInfo<UserGameJoinInfo>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_EndpointId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_EndpointId; }
  void SetDefault() { self.m_EndpointId = StormReflTypeInfo<UserGameJoinInfo>::GetDefault().m_EndpointId; }
};

template <>
struct StormReflTypeInfo<UserGameJoinInfo>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Password"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC3EE92FB; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserGameJoinInfo::m_Password; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserGameJoinInfo *>(obj); return &ptr->m_Password; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserGameJoinInfo *>(obj); return &ptr->m_Password; }
};

template <typename Self>
struct StormReflTypeInfo<UserGameJoinInfo>::field_data<1, Self> : public StormReflTypeInfo<UserGameJoinInfo>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Password; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Password; }
  void SetDefault() { self.m_Password = StormReflTypeInfo<UserGameJoinInfo>::GetDefault().m_Password; }
};

template <>
struct StormReflTypeInfo<UserGameJoinInfo>::field_data_static<2>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_Observer"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6D4390C9; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UserGameJoinInfo::m_Observer; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserGameJoinInfo *>(obj); return &ptr->m_Observer; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserGameJoinInfo *>(obj); return &ptr->m_Observer; }
};

template <typename Self>
struct StormReflTypeInfo<UserGameJoinInfo>::field_data<2, Self> : public StormReflTypeInfo<UserGameJoinInfo>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_Observer; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_Observer; }
  void SetDefault() { self.m_Observer = StormReflTypeInfo<UserGameJoinInfo>::GetDefault().m_Observer; }
};

template <>
struct StormReflTypeInfo<UserGameJoinInfo>::field_data_static<3>
{
  using member_type = LobbyGameType; // LobbyGameType
  static constexpr auto GetName() { return "m_IntendedType"; }
  static constexpr auto GetType() { return "LobbyGameType"; }
  static constexpr unsigned GetFieldNameHash() { return 0x01E307B7; }
  static constexpr unsigned GetTypeNameHash() { return 0x15A65C86; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &UserGameJoinInfo::m_IntendedType; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserGameJoinInfo *>(obj); return &ptr->m_IntendedType; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserGameJoinInfo *>(obj); return &ptr->m_IntendedType; }
};

template <typename Self>
struct StormReflTypeInfo<UserGameJoinInfo>::field_data<3, Self> : public StormReflTypeInfo<UserGameJoinInfo>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, LobbyGameType> & Get() { return self.m_IntendedType; }
  std::add_const_t<std::remove_reference_t<LobbyGameType>> & Get() const { return self.m_IntendedType; }
  void SetDefault() { self.m_IntendedType = StormReflTypeInfo<UserGameJoinInfo>::GetDefault().m_IntendedType; }
};

template <>
struct StormReflTypeInfo<UserGameJoinInfo>::field_data_static<4>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_AssignedTeam"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x9564A5BB; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &UserGameJoinInfo::m_AssignedTeam; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserGameJoinInfo *>(obj); return &ptr->m_AssignedTeam; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserGameJoinInfo *>(obj); return &ptr->m_AssignedTeam; }
};

template <typename Self>
struct StormReflTypeInfo<UserGameJoinInfo>::field_data<4, Self> : public StormReflTypeInfo<UserGameJoinInfo>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_AssignedTeam; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_AssignedTeam; }
  void SetDefault() { self.m_AssignedTeam = StormReflTypeInfo<UserGameJoinInfo>::GetDefault().m_AssignedTeam; }
};

template <>
struct StormReflTypeInfo<UserGameJoinInfo>::field_data_static<5>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_MatchmakerRandomId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x9D460336; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &UserGameJoinInfo::m_MatchmakerRandomId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserGameJoinInfo *>(obj); return &ptr->m_MatchmakerRandomId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserGameJoinInfo *>(obj); return &ptr->m_MatchmakerRandomId; }
};

template <typename Self>
struct StormReflTypeInfo<UserGameJoinInfo>::field_data<5, Self> : public StormReflTypeInfo<UserGameJoinInfo>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_MatchmakerRandomId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_MatchmakerRandomId; }
  void SetDefault() { self.m_MatchmakerRandomId = StormReflTypeInfo<UserGameJoinInfo>::GetDefault().m_MatchmakerRandomId; }
};

template <>
struct StormReflTypeInfo<UserGameJoinInfo>::field_data_static<6>
{
  using member_type = UserZoneInfo; // UserZoneInfo
  static constexpr auto GetName() { return "m_ZoneInfo"; }
  static constexpr auto GetType() { return "UserZoneInfo"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFAB36D71; }
  static constexpr unsigned GetTypeNameHash() { return 0xC19DFF86; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &UserGameJoinInfo::m_ZoneInfo; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserGameJoinInfo *>(obj); return &ptr->m_ZoneInfo; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserGameJoinInfo *>(obj); return &ptr->m_ZoneInfo; }
};

template <typename Self>
struct StormReflTypeInfo<UserGameJoinInfo>::field_data<6, Self> : public StormReflTypeInfo<UserGameJoinInfo>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, UserZoneInfo> & Get() { return self.m_ZoneInfo; }
  std::add_const_t<std::remove_reference_t<UserZoneInfo>> & Get() const { return self.m_ZoneInfo; }
  void SetDefault() { self.m_ZoneInfo = StormReflTypeInfo<UserGameJoinInfo>::GetDefault().m_ZoneInfo; }
};

template <>
struct StormReflTypeInfo<User>
{
  using MyBase = void;
  static constexpr int fields_n = 35;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "User"; }
  static constexpr auto GetNameHash() { return 0x2DA17977; }
  static constexpr bool HasDefault() { return false; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<User *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const User *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<User *>(ptr);
    if(typeid(User).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const User *>(ptr);
    if(typeid(User).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<User>::field_data_static<0>
{
  using member_type = UserInfo; // UserInfo
  static constexpr auto GetName() { return "m_UserInfo"; }
  static constexpr auto GetType() { return "UserInfo"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3BEA3236; }
  static constexpr unsigned GetTypeNameHash() { return 0x34B0844E; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &User::m_UserInfo; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_UserInfo; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_UserInfo; }
};

template <typename Self>
struct StormReflTypeInfo<User>::field_data<0, Self> : public StormReflTypeInfo<User>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, UserInfo> & Get() { return self.m_UserInfo; }
  std::add_const_t<std::remove_reference_t<UserInfo>> & Get() const { return self.m_UserInfo; }
};

template <>
struct StormReflTypeInfo<User>::field_data_static<1>
{
  using member_type = UserLocalData; // UserLocalData
  static constexpr auto GetName() { return "m_LocalInfo"; }
  static constexpr auto GetType() { return "UserLocalData"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE67EA4AC; }
  static constexpr unsigned GetTypeNameHash() { return 0xA3E62FB5; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &User::m_LocalInfo; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_LocalInfo; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_LocalInfo; }
};

template <typename Self>
struct StormReflTypeInfo<User>::field_data<1, Self> : public StormReflTypeInfo<User>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, UserLocalData> & Get() { return self.m_LocalInfo; }
  std::add_const_t<std::remove_reference_t<UserLocalData>> & Get() const { return self.m_LocalInfo; }
};

template <>
struct StormReflTypeInfo<User>::field_data_static<2>
{
  using member_type = DDSThrottle; // DDSThrottle
  static constexpr auto GetName() { return "m_CharsThrottle"; }
  static constexpr auto GetType() { return "DDSThrottle"; }
  static constexpr unsigned GetFieldNameHash() { return 0xEB25BA6E; }
  static constexpr unsigned GetTypeNameHash() { return 0xA610F43B; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &User::m_CharsThrottle; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_CharsThrottle; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_CharsThrottle; }
};

template <typename Self>
struct StormReflTypeInfo<User>::field_data<2, Self> : public StormReflTypeInfo<User>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSThrottle> & Get() { return self.m_CharsThrottle; }
  std::add_const_t<std::remove_reference_t<DDSThrottle>> & Get() const { return self.m_CharsThrottle; }
};

template <>
struct StormReflTypeInfo<User>::field_data_static<3>
{
  using member_type = DDSThrottle; // DDSThrottle
  static constexpr auto GetName() { return "m_LinesThrottle"; }
  static constexpr auto GetType() { return "DDSThrottle"; }
  static constexpr unsigned GetFieldNameHash() { return 0x017A4D63; }
  static constexpr unsigned GetTypeNameHash() { return 0xA610F43B; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &User::m_LinesThrottle; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_LinesThrottle; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_LinesThrottle; }
};

template <typename Self>
struct StormReflTypeInfo<User>::field_data<3, Self> : public StormReflTypeInfo<User>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSThrottle> & Get() { return self.m_LinesThrottle; }
  std::add_const_t<std::remove_reference_t<DDSThrottle>> & Get() const { return self.m_LinesThrottle; }
};

template <>
struct StormReflTypeInfo<User>::field_data_static<4>
{
  using member_type = DDSThrottle; // DDSThrottle
  static constexpr auto GetName() { return "m_GameCreationThrottle"; }
  static constexpr auto GetType() { return "DDSThrottle"; }
  static constexpr unsigned GetFieldNameHash() { return 0xADBC884B; }
  static constexpr unsigned GetTypeNameHash() { return 0xA610F43B; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &User::m_GameCreationThrottle; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_GameCreationThrottle; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_GameCreationThrottle; }
};

template <typename Self>
struct StormReflTypeInfo<User>::field_data<4, Self> : public StormReflTypeInfo<User>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSThrottle> & Get() { return self.m_GameCreationThrottle; }
  std::add_const_t<std::remove_reference_t<DDSThrottle>> & Get() const { return self.m_GameCreationThrottle; }
};

template <>
struct StormReflTypeInfo<User>::field_data_static<5>
{
  using member_type = DDSThrottle; // DDSThrottle
  static constexpr auto GetName() { return "m_SquadCreationThrottle"; }
  static constexpr auto GetType() { return "DDSThrottle"; }
  static constexpr unsigned GetFieldNameHash() { return 0xCCD3FEB3; }
  static constexpr unsigned GetTypeNameHash() { return 0xA610F43B; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &User::m_SquadCreationThrottle; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_SquadCreationThrottle; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_SquadCreationThrottle; }
};

template <typename Self>
struct StormReflTypeInfo<User>::field_data<5, Self> : public StormReflTypeInfo<User>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSThrottle> & Get() { return self.m_SquadCreationThrottle; }
  std::add_const_t<std::remove_reference_t<DDSThrottle>> & Get() const { return self.m_SquadCreationThrottle; }
};

template <>
struct StormReflTypeInfo<User>::field_data_static<6>
{
  using member_type = DDSThrottle; // DDSThrottle
  static constexpr auto GetName() { return "m_ProfileThrottle"; }
  static constexpr auto GetType() { return "DDSThrottle"; }
  static constexpr unsigned GetFieldNameHash() { return 0x044D82DD; }
  static constexpr unsigned GetTypeNameHash() { return 0xA610F43B; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &User::m_ProfileThrottle; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_ProfileThrottle; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_ProfileThrottle; }
};

template <typename Self>
struct StormReflTypeInfo<User>::field_data<6, Self> : public StormReflTypeInfo<User>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSThrottle> & Get() { return self.m_ProfileThrottle; }
  std::add_const_t<std::remove_reference_t<DDSThrottle>> & Get() const { return self.m_ProfileThrottle; }
};

template <>
struct StormReflTypeInfo<User>::field_data_static<7>
{
  using member_type = DDSThrottle; // DDSThrottle
  static constexpr auto GetName() { return "m_GameThrottle"; }
  static constexpr auto GetType() { return "DDSThrottle"; }
  static constexpr unsigned GetFieldNameHash() { return 0x54A2CD8E; }
  static constexpr unsigned GetTypeNameHash() { return 0xA610F43B; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &User::m_GameThrottle; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_GameThrottle; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_GameThrottle; }
};

template <typename Self>
struct StormReflTypeInfo<User>::field_data<7, Self> : public StormReflTypeInfo<User>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSThrottle> & Get() { return self.m_GameThrottle; }
  std::add_const_t<std::remove_reference_t<DDSThrottle>> & Get() const { return self.m_GameThrottle; }
};

template <>
struct StormReflTypeInfo<User>::field_data_static<8>
{
  using member_type = std::vector<DDSKey>; // std::vector<unsigned long, std::allocator<unsigned long> >
  static constexpr auto GetName() { return "m_PendingSquadLoads"; }
  static constexpr auto GetType() { return "std::vector<unsigned long, std::allocator<unsigned long> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x760654C0; }
  static constexpr unsigned GetTypeNameHash() { return 0x940F60C3; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 8; }
  static constexpr auto GetMemberPtr() { return &User::m_PendingSquadLoads; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_PendingSquadLoads; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_PendingSquadLoads; }
};

template <typename Self>
struct StormReflTypeInfo<User>::field_data<8, Self> : public StormReflTypeInfo<User>::field_data_static<8>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<DDSKey>> & Get() { return self.m_PendingSquadLoads; }
  std::add_const_t<std::remove_reference_t<std::vector<DDSKey>>> & Get() const { return self.m_PendingSquadLoads; }
};

template <>
struct StormReflTypeInfo<User>::field_data_static<9>
{
  using member_type = std::vector<DDSKey>; // std::vector<unsigned long, std::allocator<unsigned long> >
  static constexpr auto GetName() { return "m_PendingApplicationLoads"; }
  static constexpr auto GetType() { return "std::vector<unsigned long, std::allocator<unsigned long> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0643EE38; }
  static constexpr unsigned GetTypeNameHash() { return 0x940F60C3; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 9; }
  static constexpr auto GetMemberPtr() { return &User::m_PendingApplicationLoads; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_PendingApplicationLoads; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_PendingApplicationLoads; }
};

template <typename Self>
struct StormReflTypeInfo<User>::field_data<9, Self> : public StormReflTypeInfo<User>::field_data_static<9>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<DDSKey>> & Get() { return self.m_PendingApplicationLoads; }
  std::add_const_t<std::remove_reference_t<std::vector<DDSKey>>> & Get() const { return self.m_PendingApplicationLoads; }
};

template <>
struct StormReflTypeInfo<User>::field_data_static<10>
{
  using member_type = std::vector<DDSKey>; // std::vector<unsigned long, std::allocator<unsigned long> >
  static constexpr auto GetName() { return "m_PendingRequestLoads"; }
  static constexpr auto GetType() { return "std::vector<unsigned long, std::allocator<unsigned long> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5997DC89; }
  static constexpr unsigned GetTypeNameHash() { return 0x940F60C3; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 10; }
  static constexpr auto GetMemberPtr() { return &User::m_PendingRequestLoads; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_PendingRequestLoads; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_PendingRequestLoads; }
};

template <typename Self>
struct StormReflTypeInfo<User>::field_data<10, Self> : public StormReflTypeInfo<User>::field_data_static<10>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<DDSKey>> & Get() { return self.m_PendingRequestLoads; }
  std::add_const_t<std::remove_reference_t<std::vector<DDSKey>>> & Get() const { return self.m_PendingRequestLoads; }
};

template <>
struct StormReflTypeInfo<User>::field_data_static<11>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_CreatingSquad"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAB4CFAB4; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 11; }
  static constexpr auto GetMemberPtr() { return &User::m_CreatingSquad; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_CreatingSquad; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_CreatingSquad; }
};

template <typename Self>
struct StormReflTypeInfo<User>::field_data<11, Self> : public StormReflTypeInfo<User>::field_data_static<11>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_CreatingSquad; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_CreatingSquad; }
};

template <>
struct StormReflTypeInfo<User>::field_data_static<12>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_PendingPrimarySquad"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x385EFE6A; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 12; }
  static constexpr auto GetMemberPtr() { return &User::m_PendingPrimarySquad; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_PendingPrimarySquad; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_PendingPrimarySquad; }
};

template <typename Self>
struct StormReflTypeInfo<User>::field_data<12, Self> : public StormReflTypeInfo<User>::field_data_static<12>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_PendingPrimarySquad; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_PendingPrimarySquad; }
};

template <>
struct StormReflTypeInfo<User>::field_data_static<13>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_PendingPrimarySquadSettingEndpoint"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFF1448CF; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 13; }
  static constexpr auto GetMemberPtr() { return &User::m_PendingPrimarySquadSettingEndpoint; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_PendingPrimarySquadSettingEndpoint; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_PendingPrimarySquadSettingEndpoint; }
};

template <typename Self>
struct StormReflTypeInfo<User>::field_data<13, Self> : public StormReflTypeInfo<User>::field_data_static<13>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_PendingPrimarySquadSettingEndpoint; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_PendingPrimarySquadSettingEndpoint; }
};

template <>
struct StormReflTypeInfo<User>::field_data_static<14>
{
  using member_type = std::map<DDSKey, DDSKey>; // std::map<unsigned long, unsigned long, std::less<unsigned long>, std::allocator<std::pair<const unsigned long, unsigned long> > >
  static constexpr auto GetName() { return "m_SquadSubscriptionIds"; }
  static constexpr auto GetType() { return "std::map<unsigned long, unsigned long, std::less<unsigned long>, std::allocator<std::pair<const unsigned long, unsigned long> > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE1E0508F; }
  static constexpr unsigned GetTypeNameHash() { return 0x9D5C622D; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 14; }
  static constexpr auto GetMemberPtr() { return &User::m_SquadSubscriptionIds; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_SquadSubscriptionIds; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_SquadSubscriptionIds; }
};

template <typename Self>
struct StormReflTypeInfo<User>::field_data<14, Self> : public StormReflTypeInfo<User>::field_data_static<14>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::map<DDSKey, DDSKey>> & Get() { return self.m_SquadSubscriptionIds; }
  std::add_const_t<std::remove_reference_t<std::map<DDSKey, DDSKey>>> & Get() const { return self.m_SquadSubscriptionIds; }
};

template <>
struct StormReflTypeInfo<User>::field_data_static<15>
{
  using member_type = std::vector<std::pair<std::pair<DDSKey, DDSKey>, DDSKey> >; // std::vector<std::pair<std::pair<unsigned long, unsigned long>, unsigned long>, std::allocator<std::pair<std::pair<unsigned long, unsigned long>, unsigned long> > >
  static constexpr auto GetName() { return "m_ChannelSubscriptions"; }
  static constexpr auto GetType() { return "std::vector<std::pair<std::pair<unsigned long, unsigned long>, unsigned long>, std::allocator<std::pair<std::pair<unsigned long, unsigned long>, unsigned long> > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5F29A36D; }
  static constexpr unsigned GetTypeNameHash() { return 0xB9261FCC; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 15; }
  static constexpr auto GetMemberPtr() { return &User::m_ChannelSubscriptions; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_ChannelSubscriptions; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_ChannelSubscriptions; }
};

template <typename Self>
struct StormReflTypeInfo<User>::field_data<15, Self> : public StormReflTypeInfo<User>::field_data_static<15>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<std::pair<std::pair<DDSKey, DDSKey>, DDSKey> >> & Get() { return self.m_ChannelSubscriptions; }
  std::add_const_t<std::remove_reference_t<std::vector<std::pair<std::pair<DDSKey, DDSKey>, DDSKey> >>> & Get() const { return self.m_ChannelSubscriptions; }
};

template <>
struct StormReflTypeInfo<User>::field_data_static<16>
{
  using member_type = std::map<DDSKey, std::pair<std::string, std::string> >; // std::map<unsigned long, std::pair<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::basic_string<char, std::char_traits<char>, std::allocator<char> > >, std::less<unsigned long>, std::allocator<std::pair<const unsigned long, std::pair<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::basic_string<char, std::char_traits<char>, std::allocator<char> > > > > >
  static constexpr auto GetName() { return "m_Endpoints"; }
  static constexpr auto GetType() { return "std::map<unsigned long, std::pair<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::basic_string<char, std::char_traits<char>, std::allocator<char> > >, std::less<unsigned long>, std::allocator<std::pair<const unsigned long, std::pair<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::basic_string<char, std::char_traits<char>, std::allocator<char> > > > > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x003D04AB; }
  static constexpr unsigned GetTypeNameHash() { return 0x3ACD95B8; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 16; }
  static constexpr auto GetMemberPtr() { return &User::m_Endpoints; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_Endpoints; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_Endpoints; }
};

template <typename Self>
struct StormReflTypeInfo<User>::field_data<16, Self> : public StormReflTypeInfo<User>::field_data_static<16>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::map<DDSKey, std::pair<std::string, std::string> >> & Get() { return self.m_Endpoints; }
  std::add_const_t<std::remove_reference_t<std::map<DDSKey, std::pair<std::string, std::string> >>> & Get() const { return self.m_Endpoints; }
};

template <>
struct StormReflTypeInfo<User>::field_data_static<17>
{
  using member_type = std::vector<DDSKey>; // std::vector<unsigned long, std::allocator<unsigned long> >
  static constexpr auto GetName() { return "m_PendingChannelJoins"; }
  static constexpr auto GetType() { return "std::vector<unsigned long, std::allocator<unsigned long> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC1D8149F; }
  static constexpr unsigned GetTypeNameHash() { return 0x940F60C3; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 17; }
  static constexpr auto GetMemberPtr() { return &User::m_PendingChannelJoins; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_PendingChannelJoins; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_PendingChannelJoins; }
};

template <typename Self>
struct StormReflTypeInfo<User>::field_data<17, Self> : public StormReflTypeInfo<User>::field_data_static<17>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<DDSKey>> & Get() { return self.m_PendingChannelJoins; }
  std::add_const_t<std::remove_reference_t<std::vector<DDSKey>>> & Get() const { return self.m_PendingChannelJoins; }
};

template <>
struct StormReflTypeInfo<User>::field_data_static<18>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_InGame"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5759207B; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 18; }
  static constexpr auto GetMemberPtr() { return &User::m_InGame; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_InGame; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_InGame; }
};

template <typename Self>
struct StormReflTypeInfo<User>::field_data<18, Self> : public StormReflTypeInfo<User>::field_data_static<18>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_InGame; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_InGame; }
};

template <>
struct StormReflTypeInfo<User>::field_data_static<19>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_SentInitialGameData"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD94C7241; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 19; }
  static constexpr auto GetMemberPtr() { return &User::m_SentInitialGameData; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_SentInitialGameData; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_SentInitialGameData; }
};

template <typename Self>
struct StormReflTypeInfo<User>::field_data<19, Self> : public StormReflTypeInfo<User>::field_data_static<19>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_SentInitialGameData; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_SentInitialGameData; }
};

template <>
struct StormReflTypeInfo<User>::field_data_static<20>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_PendingGameId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5A229A12; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 20; }
  static constexpr auto GetMemberPtr() { return &User::m_PendingGameId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_PendingGameId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_PendingGameId; }
};

template <typename Self>
struct StormReflTypeInfo<User>::field_data<20, Self> : public StormReflTypeInfo<User>::field_data_static<20>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_PendingGameId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_PendingGameId; }
};

template <>
struct StormReflTypeInfo<User>::field_data_static<21>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_GameId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA16AE06C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 21; }
  static constexpr auto GetMemberPtr() { return &User::m_GameId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_GameId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_GameId; }
};

template <typename Self>
struct StormReflTypeInfo<User>::field_data<21, Self> : public StormReflTypeInfo<User>::field_data_static<21>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_GameId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_GameId; }
};

template <>
struct StormReflTypeInfo<User>::field_data_static<22>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_GameRandomId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0F8ADA3B; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 22; }
  static constexpr auto GetMemberPtr() { return &User::m_GameRandomId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_GameRandomId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_GameRandomId; }
};

template <typename Self>
struct StormReflTypeInfo<User>::field_data<22, Self> : public StormReflTypeInfo<User>::field_data_static<22>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_GameRandomId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_GameRandomId; }
};

template <>
struct StormReflTypeInfo<User>::field_data_static<23>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_GameEndpoint"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x7B3C8A19; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 23; }
  static constexpr auto GetMemberPtr() { return &User::m_GameEndpoint; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_GameEndpoint; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_GameEndpoint; }
};

template <typename Self>
struct StormReflTypeInfo<User>::field_data<23, Self> : public StormReflTypeInfo<User>::field_data_static<23>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_GameEndpoint; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_GameEndpoint; }
};

template <>
struct StormReflTypeInfo<User>::field_data_static<24>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_GameSubscriptionId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB3AF2C98; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 24; }
  static constexpr auto GetMemberPtr() { return &User::m_GameSubscriptionId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_GameSubscriptionId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_GameSubscriptionId; }
};

template <typename Self>
struct StormReflTypeInfo<User>::field_data<24, Self> : public StormReflTypeInfo<User>::field_data_static<24>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_GameSubscriptionId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_GameSubscriptionId; }
};

template <>
struct StormReflTypeInfo<User>::field_data_static<25>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_InMatchmaking"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x183D1395; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 25; }
  static constexpr auto GetMemberPtr() { return &User::m_InMatchmaking; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_InMatchmaking; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_InMatchmaking; }
};

template <typename Self>
struct StormReflTypeInfo<User>::field_data<25, Self> : public StormReflTypeInfo<User>::field_data_static<25>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_InMatchmaking; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_InMatchmaking; }
};

template <>
struct StormReflTypeInfo<User>::field_data_static<26>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_MatchmakingEndpoint"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xEE44F510; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 26; }
  static constexpr auto GetMemberPtr() { return &User::m_MatchmakingEndpoint; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_MatchmakingEndpoint; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_MatchmakingEndpoint; }
};

template <typename Self>
struct StormReflTypeInfo<User>::field_data<26, Self> : public StormReflTypeInfo<User>::field_data_static<26>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_MatchmakingEndpoint; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_MatchmakingEndpoint; }
};

template <>
struct StormReflTypeInfo<User>::field_data_static<27>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_MatchmakingRandomId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x9AF2A532; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 27; }
  static constexpr auto GetMemberPtr() { return &User::m_MatchmakingRandomId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_MatchmakingRandomId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_MatchmakingRandomId; }
};

template <typename Self>
struct StormReflTypeInfo<User>::field_data<27, Self> : public StormReflTypeInfo<User>::field_data_static<27>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_MatchmakingRandomId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_MatchmakingRandomId; }
};

template <>
struct StormReflTypeInfo<User>::field_data_static<28>
{
  using member_type = uint32_t; // unsigned int
  static constexpr auto GetName() { return "m_MatchmakingPlaylistMask"; }
  static constexpr auto GetType() { return "unsigned int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x58768740; }
  static constexpr unsigned GetTypeNameHash() { return 0x562EF932; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 28; }
  static constexpr auto GetMemberPtr() { return &User::m_MatchmakingPlaylistMask; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_MatchmakingPlaylistMask; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_MatchmakingPlaylistMask; }
};

template <typename Self>
struct StormReflTypeInfo<User>::field_data<28, Self> : public StormReflTypeInfo<User>::field_data_static<28>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint32_t> & Get() { return self.m_MatchmakingPlaylistMask; }
  std::add_const_t<std::remove_reference_t<uint32_t>> & Get() const { return self.m_MatchmakingPlaylistMask; }
};

template <>
struct StormReflTypeInfo<User>::field_data_static<29>
{
  using member_type = UserZoneInfo; // UserZoneInfo
  static constexpr auto GetName() { return "m_MatchmakingZoneInfo"; }
  static constexpr auto GetType() { return "UserZoneInfo"; }
  static constexpr unsigned GetFieldNameHash() { return 0x26994334; }
  static constexpr unsigned GetTypeNameHash() { return 0xC19DFF86; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 29; }
  static constexpr auto GetMemberPtr() { return &User::m_MatchmakingZoneInfo; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_MatchmakingZoneInfo; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_MatchmakingZoneInfo; }
};

template <typename Self>
struct StormReflTypeInfo<User>::field_data<29, Self> : public StormReflTypeInfo<User>::field_data_static<29>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, UserZoneInfo> & Get() { return self.m_MatchmakingZoneInfo; }
  std::add_const_t<std::remove_reference_t<UserZoneInfo>> & Get() const { return self.m_MatchmakingZoneInfo; }
};

template <>
struct StormReflTypeInfo<User>::field_data_static<30>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_MatchmakingRanked"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x4969C855; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 30; }
  static constexpr auto GetMemberPtr() { return &User::m_MatchmakingRanked; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_MatchmakingRanked; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_MatchmakingRanked; }
};

template <typename Self>
struct StormReflTypeInfo<User>::field_data<30, Self> : public StormReflTypeInfo<User>::field_data_static<30>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_MatchmakingRanked; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_MatchmakingRanked; }
};

template <>
struct StormReflTypeInfo<User>::field_data_static<31>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_ReconnectGame"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x80A08C2D; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 31; }
  static constexpr auto GetMemberPtr() { return &User::m_ReconnectGame; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_ReconnectGame; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_ReconnectGame; }
};

template <typename Self>
struct StormReflTypeInfo<User>::field_data<31, Self> : public StormReflTypeInfo<User>::field_data_static<31>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_ReconnectGame; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_ReconnectGame; }
};

template <>
struct StormReflTypeInfo<User>::field_data_static<32>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_ReconnectGameRandomId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xCCBD6B72; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 32; }
  static constexpr auto GetMemberPtr() { return &User::m_ReconnectGameRandomId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_ReconnectGameRandomId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_ReconnectGameRandomId; }
};

template <typename Self>
struct StormReflTypeInfo<User>::field_data<32, Self> : public StormReflTypeInfo<User>::field_data_static<32>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_ReconnectGameRandomId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_ReconnectGameRandomId; }
};

template <>
struct StormReflTypeInfo<User>::field_data_static<33>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_CountryCode"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x443BB729; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 33; }
  static constexpr auto GetMemberPtr() { return &User::m_CountryCode; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_CountryCode; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_CountryCode; }
};

template <typename Self>
struct StormReflTypeInfo<User>::field_data<33, Self> : public StormReflTypeInfo<User>::field_data_static<33>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_CountryCode; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_CountryCode; }
};

template <>
struct StormReflTypeInfo<User>::field_data_static<34>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_CurrencyCode"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xEF446721; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 34; }
  static constexpr auto GetMemberPtr() { return &User::m_CurrencyCode; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_CurrencyCode; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_CurrencyCode; }
};

template <typename Self>
struct StormReflTypeInfo<User>::field_data<34, Self> : public StormReflTypeInfo<User>::field_data_static<34>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_CurrencyCode; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_CurrencyCode; }
};

template <>
struct StormReflFuncInfo<User>
{
  using MyBase = void;
  static constexpr int funcs_n = 57;
  template <int N> struct func_data_static {};
};

template <>
struct StormReflFuncInfo<User>::func_data_static<0>
{
  using func_ptr_type = void (User::*)(DDSKey, std::string, std::string);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "AddEndpoint"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xFDD4B125; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 0; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::AddEndpoint; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<0>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x8A90ABA9; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<0>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "remote_ip"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x30E448E9; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<0>::param_info<2>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "remote_host"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x4ADEBF24; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<1>
{
  using func_ptr_type = void (User::*)(std::string);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "SendToAllEndpoints"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xDA6B3DB7; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 1; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::SendToAllEndpoints; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<1>::param_info<0>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "data"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xADF3F363; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<2>
{
  using func_ptr_type = void (User::*)(std::string);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "SendNotification"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x292FCD97; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 2; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::SendNotification; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<2>::param_info<0>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "msg"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x688A5FAF; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<3>
{
  using func_ptr_type = void (User::*)(DDSKey, std::string);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "SendToEndpoint"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xD3507E63; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 3; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::SendToEndpoint; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<3>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<3>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "data"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xADF3F363; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<4>
{
  using func_ptr_type = void (User::*)(DDSKey);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "RemoveEndpoint"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xC46693D2; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 4; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::RemoveEndpoint; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<4>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x8A90ABA9; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<5>
{
  using func_ptr_type = void (User::*)(std::string, std::string);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "SetLocation"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xD29063D0; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 5; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::SetLocation; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<5>::param_info<0>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "country_code"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xF026BB7C; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<5>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "currency_code"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xFDA273EC; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<6>
{
  using func_ptr_type = void (User::*)(std::string);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "UpdateName"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x2B40B671; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 6; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::UpdateName; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<6>::param_info<0>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "name"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x5E237E06; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<7>
{
  using func_ptr_type = void (User::*)(uint32_t, const UserGameJoinInfo &);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "JoinGameByLookupTable"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xE2BD12AD; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 7; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::JoinGameByLookupTable; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<7>::param_info<0>
{
  using param_type = uint32_t;
  static constexpr auto GetName() { return "join_code"; }
  static constexpr auto GetType() { return "uint32_t"; }
  static constexpr unsigned GetNameHash() { return 0xE64D7D01; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E2AF381; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<7>::param_info<1>
{
  using param_type = const UserGameJoinInfo &;
  static constexpr auto GetName() { return "join_info"; }
  static constexpr auto GetType() { return "const UserGameJoinInfo &"; }
  static constexpr unsigned GetNameHash() { return 0x5AD17CCE; }
  static constexpr unsigned GetTypeNameHash() { return 0xEFC3F2A3; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<8>
{
  using func_ptr_type = void (User::*)(DDSKey, DDSKey, const UserGameJoinInfo &);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "JoinGameByMatchmaker"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x67287EAB; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 8; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::JoinGameByMatchmaker; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<8>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<8>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "matchmaker_random_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x5BADD915; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<8>::param_info<2>
{
  using param_type = const UserGameJoinInfo &;
  static constexpr auto GetName() { return "join_info"; }
  static constexpr auto GetType() { return "const UserGameJoinInfo &"; }
  static constexpr unsigned GetNameHash() { return 0x5AD17CCE; }
  static constexpr unsigned GetTypeNameHash() { return 0xEFC3F2A3; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<9>
{
  using func_ptr_type = void (User::*)(uint32_t, DDSKey, const UserZoneInfo &);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "StartMatchmakingCompetitive"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x81143CB0; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 9; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::StartMatchmakingCompetitive; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<9>::param_info<0>
{
  using param_type = uint32_t;
  static constexpr auto GetName() { return "playlist_mask"; }
  static constexpr auto GetType() { return "uint32_t"; }
  static constexpr unsigned GetNameHash() { return 0xDF76F452; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E2AF381; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<9>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<9>::param_info<2>
{
  using param_type = const UserZoneInfo &;
  static constexpr auto GetName() { return "zone_info"; }
  static constexpr auto GetType() { return "const UserZoneInfo &"; }
  static constexpr unsigned GetNameHash() { return 0x5971F0F2; }
  static constexpr unsigned GetTypeNameHash() { return 0x7A017F3C; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<10>
{
  using func_ptr_type = void (User::*)(uint32_t, DDSKey, const UserZoneInfo &);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "StartMatchmakingCasual"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xF7643A93; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 10; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::StartMatchmakingCasual; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<10>::param_info<0>
{
  using param_type = uint32_t;
  static constexpr auto GetName() { return "playlist_mask"; }
  static constexpr auto GetType() { return "uint32_t"; }
  static constexpr unsigned GetNameHash() { return 0xDF76F452; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E2AF381; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<10>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<10>::param_info<2>
{
  using param_type = const UserZoneInfo &;
  static constexpr auto GetName() { return "zone_info"; }
  static constexpr auto GetType() { return "const UserZoneInfo &"; }
  static constexpr unsigned GetNameHash() { return 0x5971F0F2; }
  static constexpr unsigned GetTypeNameHash() { return 0x7A017F3C; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<11>
{
  using func_ptr_type = void (User::*)();
  using return_type = void;
  static constexpr int params_n = 0;
  static constexpr auto GetName() { return "CancelMatchmaking"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xCA5510D8; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 11; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::CancelMatchmaking; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<12>
{
  using func_ptr_type = void (User::*)(DDSKey);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "RemoveFromMatchmaking"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x54843271; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 12; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::RemoveFromMatchmaking; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<12>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<13>
{
  using func_ptr_type = void (User::*)(DDSKey, DDSKey);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "RejoinMatchmaking"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x589BDD4B; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 13; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::RejoinMatchmaking; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<13>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<13>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "matchmaking_random_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x79897FF1; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<14>
{
  using func_ptr_type = void (User::*)(DDSKey, const GameInitSettings &, std::string, const UserZoneInfo &);
  using return_type = void;
  static constexpr int params_n = 4;
  static constexpr auto GetName() { return "CreatePrivateGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x6B2257F6; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 14; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::CreatePrivateGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<14>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<14>::param_info<1>
{
  using param_type = const GameInitSettings &;
  static constexpr auto GetName() { return "creation_data"; }
  static constexpr auto GetType() { return "const GameInitSettings &"; }
  static constexpr unsigned GetNameHash() { return 0x7085B547; }
  static constexpr unsigned GetTypeNameHash() { return 0xEB959CD8; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<14>::param_info<2>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "password"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x35C246D5; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<14>::param_info<3>
{
  using param_type = const UserZoneInfo &;
  static constexpr auto GetName() { return "zone_info"; }
  static constexpr auto GetType() { return "const UserZoneInfo &"; }
  static constexpr unsigned GetNameHash() { return 0x5971F0F2; }
  static constexpr unsigned GetTypeNameHash() { return 0x7A017F3C; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<15>
{
  using func_ptr_type = void (User::*)(DDSKey, DDSKey, DDSKey);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "SetInGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x81F2E0DC; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 15; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::SetInGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<15>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<15>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "game_random_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xF579374E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<15>::param_info<2>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<16>
{
  using func_ptr_type = void (User::*)();
  using return_type = void;
  static constexpr int params_n = 0;
  static constexpr auto GetName() { return "RequestLeaveGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x894B8444; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 16; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::RequestLeaveGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<17>
{
  using func_ptr_type = void (User::*)(DDSKey, DDSKey);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "DestroyGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x0F26CB52; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 17; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::DestroyGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<17>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<17>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<18>
{
  using func_ptr_type = void (User::*)(DDSKey, DDSKey, DDSKey, bool);
  using return_type = void;
  static constexpr int params_n = 4;
  static constexpr auto GetName() { return "HandleGameJoinResponse"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xED0B8170; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 18; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::HandleGameJoinResponse; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<18>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<18>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<18>::param_info<2>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "game_random_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xF579374E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<18>::param_info<3>
{
  using param_type = bool;
  static constexpr auto GetName() { return "success"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetNameHash() { return 0x6F00DFB2; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<19>
{
  using func_ptr_type = void (User::*)(DDSKey, const UserGameJoinInfo &);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "HandleJoinCodeLookup"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x3A171B91; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 19; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::HandleJoinCodeLookup; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<19>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<19>::param_info<1>
{
  using param_type = const UserGameJoinInfo &;
  static constexpr auto GetName() { return "join_info"; }
  static constexpr auto GetType() { return "const UserGameJoinInfo &"; }
  static constexpr unsigned GetNameHash() { return 0x5AD17CCE; }
  static constexpr unsigned GetTypeNameHash() { return 0xEFC3F2A3; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<20>
{
  using func_ptr_type = void (User::*)(DDSKey, std::string);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "SendGameChat"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xD0D87A16; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 20; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::SendGameChat; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<20>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<20>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "msg"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x688A5FAF; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<21>
{
  using func_ptr_type = void (User::*)(DDSKey, int, DDSKey);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "SwitchTeams"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x894C1DB3; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 21; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::SwitchTeams; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<21>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "target_user"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x408BC0F8; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<21>::param_info<1>
{
  using param_type = int;
  static constexpr auto GetName() { return "team"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xC4E0A61F; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<21>::param_info<2>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<22>
{
  using func_ptr_type = void (User::*)();
  using return_type = void;
  static constexpr int params_n = 0;
  static constexpr auto GetName() { return "StartGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x40E81A4D; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 22; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::StartGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<23>
{
  using func_ptr_type = void (User::*)(bool);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "ChangeReady"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x513A1CDC; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 23; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::ChangeReady; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<23>::param_info<0>
{
  using param_type = bool;
  static constexpr auto GetName() { return "ready"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetNameHash() { return 0x289585AF; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<24>
{
  using func_ptr_type = void (User::*)(const GameInitSettings &);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "ChangeGameSettings"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xFE1036AD; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 24; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::ChangeGameSettings; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<24>::param_info<0>
{
  using param_type = const GameInitSettings &;
  static constexpr auto GetName() { return "settings"; }
  static constexpr auto GetType() { return "const GameInitSettings &"; }
  static constexpr unsigned GetNameHash() { return 0xE545A0C5; }
  static constexpr unsigned GetTypeNameHash() { return 0xEB959CD8; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<25>
{
  using func_ptr_type = void (User::*)(DDSKey);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "KickUserFromGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x310F73AD; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 25; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::KickUserFromGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<25>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xA76ED395; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<26>
{
  using func_ptr_type = void (User::*)(DDSKey, DDSKey, DDSKey);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "ReconnectToGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xA356074C; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 26; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::ReconnectToGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<26>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<26>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<26>::param_info<2>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "game_random_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xF579374E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<27>
{
  using func_ptr_type = void (User::*)();
  using return_type = void;
  static constexpr int params_n = 0;
  static constexpr auto GetName() { return "DeclineReconnectToGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xC1B0F2B8; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 27; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::DeclineReconnectToGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<28>
{
  using func_ptr_type = void (User::*)();
  using return_type = void;
  static constexpr int params_n = 0;
  static constexpr auto GetName() { return "BanFromCompetitive"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x1D7FEB3F; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 28; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::BanFromCompetitive; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<29>
{
  using func_ptr_type = void (User::*)(DDSKey, DDSKey, bool);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "NotifyLeftGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x29289854; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 29; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::NotifyLeftGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<29>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<29>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "game_random_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xF579374E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<29>::param_info<2>
{
  using param_type = bool;
  static constexpr auto GetName() { return "allow_reconnect"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetNameHash() { return 0x744AEA6C; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<30>
{
  using func_ptr_type = void (User::*)(DDSKey, DDSKey, std::string, int, DDSKey);
  using return_type = void;
  static constexpr int params_n = 5;
  static constexpr auto GetName() { return "NotifyLaunchGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xB98C5E5F; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 30; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::NotifyLaunchGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<30>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<30>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "game_random_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xF579374E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<30>::param_info<2>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "server_ip"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x029E32CA; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<30>::param_info<3>
{
  using param_type = int;
  static constexpr auto GetName() { return "server_port"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xC8112C2C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<30>::param_info<4>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "token"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x5F37A13B; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<31>
{
  using func_ptr_type = void (User::*)(DDSKey, DDSKey);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "NotifyResetGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xB8807D43; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 31; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::NotifyResetGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<31>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<31>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "game_random_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xF579374E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<32>
{
  using func_ptr_type = void (User::*)(DDSKey, DDSKey);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "NotifyReconnectGameEnded"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x921DB97B; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 32; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::NotifyReconnectGameEnded; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<32>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<32>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "game_random_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xF579374E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<33>
{
  using func_ptr_type = void (User::*)(DDSKey, DDSKey, std::string, int, int, std::string);
  using return_type = void;
  static constexpr int params_n = 6;
  static constexpr auto GetName() { return "HandleGameChat"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x83B503F6; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 33; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::HandleGameChat; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<33>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<33>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "game_random_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xF579374E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<33>::param_info<2>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "name"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x5E237E06; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<33>::param_info<3>
{
  using param_type = int;
  static constexpr auto GetName() { return "icon"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x659429DB; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<33>::param_info<4>
{
  using param_type = int;
  static constexpr auto GetName() { return "title"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x2B36786B; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<33>::param_info<5>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "msg"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x688A5FAF; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<34>
{
  using func_ptr_type = void (User::*)(std::tuple<DDSKey, DDSKey>, std::string);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "HandleGameUpdate"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x44910382; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 34; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::HandleGameUpdate; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<34>::param_info<0>
{
  using param_type = std::tuple<DDSKey, DDSKey>;
  static constexpr auto GetName() { return "game_info"; }
  static constexpr auto GetType() { return "std::tuple<DDSKey, DDSKey>"; }
  static constexpr unsigned GetNameHash() { return 0x209C5D7B; }
  static constexpr unsigned GetTypeNameHash() { return 0x4C951411; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<34>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "data"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xADF3F363; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<35>
{
  using func_ptr_type = void (User::*)(DDSResponder &, int, bool);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "AddTitle"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x405C98D2; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 35; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::AddTitle; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<35>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<35>::param_info<1>
{
  using param_type = int;
  static constexpr auto GetName() { return "title"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x2B36786B; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<35>::param_info<2>
{
  using param_type = bool;
  static constexpr auto GetName() { return "quiet"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetNameHash() { return 0x5695B4A4; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<36>
{
  using func_ptr_type = void (User::*)(int);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "SetTitle"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xDB63A7AB; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 36; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::SetTitle; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<36>::param_info<0>
{
  using param_type = int;
  static constexpr auto GetName() { return "title"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x2B36786B; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<37>
{
  using func_ptr_type = void (User::*)(DDSResponder &, int);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "RemoveTitle"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x23281553; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 37; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::RemoveTitle; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<37>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<37>::param_info<1>
{
  using param_type = int;
  static constexpr auto GetName() { return "title"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x2B36786B; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<38>
{
  using func_ptr_type = void (User::*)(DDSResponder &, int, bool, bool);
  using return_type = void;
  static constexpr int params_n = 4;
  static constexpr auto GetName() { return "AddIcon"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x6425648B; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 38; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::AddIcon; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<38>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<38>::param_info<1>
{
  using param_type = int;
  static constexpr auto GetName() { return "icon"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x659429DB; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<38>::param_info<2>
{
  using param_type = bool;
  static constexpr auto GetName() { return "set"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetNameHash() { return 0xE61425DC; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<38>::param_info<3>
{
  using param_type = bool;
  static constexpr auto GetName() { return "quiet"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetNameHash() { return 0x5695B4A4; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<39>
{
  using func_ptr_type = void (User::*)(int);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "SetIcon"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x3FD8AD4B; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 39; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::SetIcon; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<39>::param_info<0>
{
  using param_type = int;
  static constexpr auto GetName() { return "icon"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x659429DB; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<40>
{
  using func_ptr_type = void (User::*)(DDSResponder &, int);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "RemoveIcon"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x16C43C96; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 40; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::RemoveIcon; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<40>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<40>::param_info<1>
{
  using param_type = int;
  static constexpr auto GetName() { return "icon"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x659429DB; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<41>
{
  using func_ptr_type = void (User::*)(DDSResponder &, int, bool, bool);
  using return_type = void;
  static constexpr int params_n = 4;
  static constexpr auto GetName() { return "AddCelebration"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xA78EB7E2; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 41; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::AddCelebration; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<41>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<41>::param_info<1>
{
  using param_type = int;
  static constexpr auto GetName() { return "celebration"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xA2860126; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<41>::param_info<2>
{
  using param_type = bool;
  static constexpr auto GetName() { return "set"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetNameHash() { return 0xE61425DC; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<41>::param_info<3>
{
  using param_type = bool;
  static constexpr auto GetName() { return "quiet"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetNameHash() { return 0x5695B4A4; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<42>
{
  using func_ptr_type = void (User::*)(int);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "SetCelebration"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xF1DC7B5A; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 42; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::SetCelebration; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<42>::param_info<0>
{
  using param_type = int;
  static constexpr auto GetName() { return "celebration"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xA2860126; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<43>
{
  using func_ptr_type = void (User::*)(DDSResponder &, int);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "RemoveCelebration"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x95D8460E; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 43; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::RemoveCelebration; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<43>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<43>::param_info<1>
{
  using param_type = int;
  static constexpr auto GetName() { return "celebration"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xA2860126; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<44>
{
  using func_ptr_type = void (User::*)(GameStatsData, GameInitSettings);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "UpdateStats"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x9953E0FD; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 44; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::UpdateStats; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<44>::param_info<0>
{
  using param_type = GameStatsData;
  static constexpr auto GetName() { return "stats"; }
  static constexpr auto GetType() { return "GameStatsData"; }
  static constexpr unsigned GetNameHash() { return 0x574767AA; }
  static constexpr unsigned GetTypeNameHash() { return 0x9CB3161C; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<44>::param_info<1>
{
  using param_type = GameInitSettings;
  static constexpr auto GetName() { return "instance_data"; }
  static constexpr auto GetType() { return "GameInitSettings"; }
  static constexpr unsigned GetNameHash() { return 0x85F9A3A8; }
  static constexpr unsigned GetTypeNameHash() { return 0xBAC6DD28; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<45>
{
  using func_ptr_type = void (User::*)(DDSResponder &);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "FetchStats"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x409D20EC; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 45; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::FetchStats; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<45>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<46>
{
  using func_ptr_type = void (User::*)(const std::string &);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "ModifyPersistent"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x88E51BEB; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 46; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::ModifyPersistent; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<46>::param_info<0>
{
  using param_type = const std::string &;
  static constexpr auto GetName() { return "change_packet"; }
  static constexpr auto GetType() { return "const std::string &"; }
  static constexpr unsigned GetNameHash() { return 0x347049E4; }
  static constexpr unsigned GetTypeNameHash() { return 0xBB24E617; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<47>
{
  using func_ptr_type = void (User::*)(DDSKey, DDSKey, std::string);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "ProcessSlashCommand"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x34AC6AF1; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 47; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::ProcessSlashCommand; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<47>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<47>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "channel_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x72F5A1AA; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<47>::param_info<2>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "msg"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x688A5FAF; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<48>
{
  using func_ptr_type = void (User::*)(DDSResponder &, DDSKey, const std::string &);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "Rename"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xDE315178; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 48; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::Rename; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<48>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<48>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "src_endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x7C0D78ED; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<48>::param_info<2>
{
  using param_type = const std::string &;
  static constexpr auto GetName() { return "new_name"; }
  static constexpr auto GetType() { return "const std::string &"; }
  static constexpr unsigned GetNameHash() { return 0xAACECADB; }
  static constexpr unsigned GetTypeNameHash() { return 0xBB24E617; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<49>
{
  using func_ptr_type = void (User::*)(DDSResponder &, int);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "MakeAdmin"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x8BF00342; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 49; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::MakeAdmin; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<49>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<49>::param_info<1>
{
  using param_type = int;
  static constexpr auto GetName() { return "admin_level"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x3AC037E9; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<50>
{
  using func_ptr_type = void (User::*)(DDSResponder &);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "Kick"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xBEE7703B; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 50; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::Kick; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<50>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<51>
{
  using func_ptr_type = void (User::*)(DDSKey, bool);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "HandleRename"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x23788C9F; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 51; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::HandleRename; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<51>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "return_ep"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x941B8DA4; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<51>::param_info<1>
{
  using param_type = bool;
  static constexpr auto GetName() { return "success"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetNameHash() { return 0x6F00DFB2; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<52>
{
  using func_ptr_type = void (User::*)(DDSKey, std::string);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "HandleCommandResponderMessage"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x17495892; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 52; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::HandleCommandResponderMessage; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<52>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<52>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "msg"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x688A5FAF; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<53>
{
  using func_ptr_type = void (User::*)(DDSKey);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "HandleCommandUserLookupFail"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x0406BB36; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 53; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::HandleCommandUserLookupFail; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<53>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<54>
{
  using func_ptr_type = void (User::*)(DDSKey);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "HandleCommandSquadLookupFail"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x4E1E0992; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 54; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::HandleCommandSquadLookupFail; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<54>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<55>
{
  using func_ptr_type = void (User::*)(DDSResponder &);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "GetInfo"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x02540D1A; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 55; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::GetInfo; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<55>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<56>
{
  using func_ptr_type = void (User::*)(std::tuple<int, std::string, DDSResponderData>, int, std::string);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "HandleUserNameLookupForCall"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x42DB6E29; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 56; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::HandleUserNameLookupForCall; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<56>::param_info<0>
{
  using param_type = std::tuple<int, std::string, DDSResponderData>;
  static constexpr auto GetName() { return "call_data"; }
  static constexpr auto GetType() { return "std::tuple<int, std::string, DDSResponderData>"; }
  static constexpr unsigned GetNameHash() { return 0x9A72943F; }
  static constexpr unsigned GetTypeNameHash() { return 0xBC210B28; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<56>::param_info<1>
{
  using param_type = int;
  static constexpr auto GetName() { return "ec"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x8DE8BDFF; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<56>::param_info<2>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "data"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xADF3F363; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

namespace StormReflFileInfo
{
  struct User
  {
    static const int types_n = 5;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct User::type_info<0>
  {
    using type = ::UserDatabaseObject;
  };

  template <>
  struct User::type_info<1>
  {
    using type = ::UserNameLookup;
  };

  template <>
  struct User::type_info<2>
  {
    using type = ::UserPlatformIdLookup;
  };

  template <>
  struct User::type_info<3>
  {
    using type = ::UserGameJoinInfo;
  };

  template <>
  struct User::type_info<4>
  {
    using type = ::User;
  };

}

