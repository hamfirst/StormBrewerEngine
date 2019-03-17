#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "User.refl.h"
#include "HurricaneDDS/DDSThrottle.refl.meta.h"
#include "SharedTypes.refl.meta.h"
#include "GameData.refl.meta.h"


template <>
struct StormReflTypeInfo<UserPersistent>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserPersistent"; }
  static constexpr auto GetNameHash() { return 0x68592B2E; }
<<<<<<< HEAD
  static UserPersistent & GetDefault() { static UserPersistent def; return def; }
=======
  static constexpr bool HasDefault() { return true; }
  static UserPersistent & GetDefault() { static UserPersistent def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<UserPersistent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const UserPersistent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<UserPersistent *>(ptr);
    if(typeid(UserPersistent).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const UserPersistent *>(ptr);
    if(typeid(UserPersistent).hash_code() == type_id_hash) return c;
    return nullptr;
  }

>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <>
struct StormReflTypeInfo<UserPersistent>::field_data_static<0>
{
  using member_type = RBool; // RBool
  static constexpr auto GetName() { return "m_EnterExitMessages"; }
  static constexpr auto GetType() { return "RBool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x21E943F0; }
  static constexpr unsigned GetTypeNameHash() { return 0x50062D06; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserPersistent::m_EnterExitMessages; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserPersistent::m_EnterExitMessages; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserPersistent *>(obj); return &ptr->m_EnterExitMessages; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserPersistent *>(obj); return &ptr->m_EnterExitMessages; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<UserPersistent>::field_data<0, Self> : public StormReflTypeInfo<UserPersistent>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RBool> & Get() { return self.m_EnterExitMessages; }
  std::add_const_t<std::remove_reference_t<RBool>> & Get() const { return self.m_EnterExitMessages; }
  void SetDefault() { self.m_EnterExitMessages = StormReflTypeInfo<UserPersistent>::GetDefault().m_EnterExitMessages; }
};

template <>
struct StormReflTypeInfo<UserPersistent>::field_data_static<1>
{
  using member_type = RBool; // RBool
  static constexpr auto GetName() { return "m_TwelveHourClock"; }
  static constexpr auto GetType() { return "RBool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x573E0BAE; }
  static constexpr unsigned GetTypeNameHash() { return 0x50062D06; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserPersistent::m_TwelveHourClock; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserPersistent::m_TwelveHourClock; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserPersistent *>(obj); return &ptr->m_TwelveHourClock; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserPersistent *>(obj); return &ptr->m_TwelveHourClock; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<UserPersistent>::field_data<1, Self> : public StormReflTypeInfo<UserPersistent>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RBool> & Get() { return self.m_TwelveHourClock; }
  std::add_const_t<std::remove_reference_t<RBool>> & Get() const { return self.m_TwelveHourClock; }
  void SetDefault() { self.m_TwelveHourClock = StormReflTypeInfo<UserPersistent>::GetDefault().m_TwelveHourClock; }
};

template <>
struct StormReflTypeInfo<UserPersistent>::field_data_static<2>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_PlayerListSort"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5B4A069E; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UserPersistent::m_PlayerListSort; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UserPersistent::m_PlayerListSort; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserPersistent *>(obj); return &ptr->m_PlayerListSort; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserPersistent *>(obj); return &ptr->m_PlayerListSort; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<UserPersistent>::field_data<2, Self> : public StormReflTypeInfo<UserPersistent>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_PlayerListSort; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_PlayerListSort; }
  void SetDefault() { self.m_PlayerListSort = StormReflTypeInfo<UserPersistent>::GetDefault().m_PlayerListSort; }
};

template <>
struct StormReflTypeInfo<UserLocalData>
{
  using MyBase = void;
  static constexpr int fields_n = 19;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserLocalData"; }
  static constexpr auto GetNameHash() { return 0xA3E62FB5; }
<<<<<<< HEAD
  static UserLocalData & GetDefault() { static UserLocalData def; return def; }
=======
  static constexpr bool HasDefault() { return true; }
  static UserLocalData & GetDefault() { static UserLocalData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<UserLocalData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const UserLocalData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<UserLocalData *>(ptr);
    if(typeid(UserLocalData).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const UserLocalData *>(ptr);
    if(typeid(UserLocalData).hash_code() == type_id_hash) return c;
    return nullptr;
  }

>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <>
struct StormReflTypeInfo<UserLocalData>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_Name; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_Name; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserLocalData *>(obj); return &ptr->m_Name; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserLocalData *>(obj); return &ptr->m_Name; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<UserLocalData>::field_data<0, Self> : public StormReflTypeInfo<UserLocalData>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<UserLocalData>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<UserLocalData>::field_data_static<1>
{
<<<<<<< HEAD
  using member_type = RKey; // RNumber<unsigned long long>
  static constexpr auto GetName() { return "m_UserKey"; }
  static constexpr auto GetType() { return "RNumber<unsigned long long>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE6008E39; }
  static constexpr unsigned GetTypeNameHash() { return 0x656FF0F1; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_UserKey; }
=======
  using member_type = RKey; // RNumber<unsigned long>
  static constexpr auto GetName() { return "m_UserKey"; }
  static constexpr auto GetType() { return "RNumber<unsigned long>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE6008E39; }
  static constexpr unsigned GetTypeNameHash() { return 0xFD825A3A; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_UserKey; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserLocalData *>(obj); return &ptr->m_UserKey; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserLocalData *>(obj); return &ptr->m_UserKey; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<UserLocalData>::field_data<1, Self> : public StormReflTypeInfo<UserLocalData>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RKey> & Get() { return self.m_UserKey; }
  std::add_const_t<std::remove_reference_t<RKey>> & Get() const { return self.m_UserKey; }
  void SetDefault() { self.m_UserKey = StormReflTypeInfo<UserLocalData>::GetDefault().m_UserKey; }
};

template <>
struct StormReflTypeInfo<UserLocalData>::field_data_static<2>
{
<<<<<<< HEAD
  using member_type = RKey; // RNumber<unsigned long long>
  static constexpr auto GetName() { return "m_PlatformId"; }
  static constexpr auto GetType() { return "RNumber<unsigned long long>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0ED94F3C; }
  static constexpr unsigned GetTypeNameHash() { return 0x656FF0F1; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_PlatformId; }
=======
  using member_type = RKey; // RNumber<unsigned long>
  static constexpr auto GetName() { return "m_PlatformId"; }
  static constexpr auto GetType() { return "RNumber<unsigned long>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0ED94F3C; }
  static constexpr unsigned GetTypeNameHash() { return 0xFD825A3A; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_PlatformId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserLocalData *>(obj); return &ptr->m_PlatformId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserLocalData *>(obj); return &ptr->m_PlatformId; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<UserLocalData>::field_data<2, Self> : public StormReflTypeInfo<UserLocalData>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RKey> & Get() { return self.m_PlatformId; }
  std::add_const_t<std::remove_reference_t<RKey>> & Get() const { return self.m_PlatformId; }
  void SetDefault() { self.m_PlatformId = StormReflTypeInfo<UserLocalData>::GetDefault().m_PlatformId; }
};

template <>
struct StormReflTypeInfo<UserLocalData>::field_data_static<3>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_AdminLevel"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xACAEF821; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_AdminLevel; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_AdminLevel; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserLocalData *>(obj); return &ptr->m_AdminLevel; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserLocalData *>(obj); return &ptr->m_AdminLevel; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<UserLocalData>::field_data<3, Self> : public StormReflTypeInfo<UserLocalData>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_AdminLevel; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_AdminLevel; }
  void SetDefault() { self.m_AdminLevel = StormReflTypeInfo<UserLocalData>::GetDefault().m_AdminLevel; }
};

template <>
struct StormReflTypeInfo<UserLocalData>::field_data_static<4>
{
<<<<<<< HEAD
=======
  using member_type = UserPersistent; // UserPersistent
  static constexpr auto GetName() { return "m_Persistent"; }
  static constexpr auto GetType() { return "UserPersistent"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2DA59512; }
  static constexpr unsigned GetTypeNameHash() { return 0x68592B2E; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_Persistent; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserLocalData *>(obj); return &ptr->m_Persistent; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserLocalData *>(obj); return &ptr->m_Persistent; }
};

template <typename Self>
struct StormReflTypeInfo<UserLocalData>::field_data<4, Self> : public StormReflTypeInfo<UserLocalData>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, UserPersistent> & Get() { return self.m_Persistent; }
  std::add_const_t<std::remove_reference_t<UserPersistent>> & Get() const { return self.m_Persistent; }
  void SetDefault() { self.m_Persistent = StormReflTypeInfo<UserLocalData>::GetDefault().m_Persistent; }
};

template <>
struct StormReflTypeInfo<UserLocalData>::field_data_static<5>
{
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_Title"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA600E80B; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_Title; }
};

template <typename Self>
struct StormReflTypeInfo<UserLocalData>::field_data<4, Self> : public StormReflTypeInfo<UserLocalData>::field_data_static<4>
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_Title; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserLocalData *>(obj); return &ptr->m_Title; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserLocalData *>(obj); return &ptr->m_Title; }
};

template <typename Self>
struct StormReflTypeInfo<UserLocalData>::field_data<5, Self> : public StormReflTypeInfo<UserLocalData>::field_data_static<5>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_Title; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_Title; }
  void SetDefault() { self.m_Title = StormReflTypeInfo<UserLocalData>::GetDefault().m_Title; }
};

template <>
<<<<<<< HEAD
struct StormReflTypeInfo<UserLocalData>::field_data_static<5>
=======
struct StormReflTypeInfo<UserLocalData>::field_data_static<6>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  using member_type = RMergeList<RString>; // RMergeList<RString>
  static constexpr auto GetName() { return "m_TitleList"; }
  static constexpr auto GetType() { return "RMergeList<RString>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xABBF57E2; }
  static constexpr unsigned GetTypeNameHash() { return 0x8C9238EC; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_TitleList; }
};

template <typename Self>
struct StormReflTypeInfo<UserLocalData>::field_data<5, Self> : public StormReflTypeInfo<UserLocalData>::field_data_static<5>
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_TitleList; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserLocalData *>(obj); return &ptr->m_TitleList; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserLocalData *>(obj); return &ptr->m_TitleList; }
};

template <typename Self>
struct StormReflTypeInfo<UserLocalData>::field_data<6, Self> : public StormReflTypeInfo<UserLocalData>::field_data_static<6>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<RString>> & Get() { return self.m_TitleList; }
  std::add_const_t<std::remove_reference_t<RMergeList<RString>>> & Get() const { return self.m_TitleList; }
  void SetDefault() { self.m_TitleList = StormReflTypeInfo<UserLocalData>::GetDefault().m_TitleList; }
};

template <>
<<<<<<< HEAD
struct StormReflTypeInfo<UserLocalData>::field_data_static<6>
=======
struct StormReflTypeInfo<UserLocalData>::field_data_static<7>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_Icon"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5B09BCC4; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_Icon; }
};

template <typename Self>
struct StormReflTypeInfo<UserLocalData>::field_data<6, Self> : public StormReflTypeInfo<UserLocalData>::field_data_static<6>
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_Icon; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserLocalData *>(obj); return &ptr->m_Icon; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserLocalData *>(obj); return &ptr->m_Icon; }
};

template <typename Self>
struct StormReflTypeInfo<UserLocalData>::field_data<7, Self> : public StormReflTypeInfo<UserLocalData>::field_data_static<7>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_Icon; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_Icon; }
  void SetDefault() { self.m_Icon = StormReflTypeInfo<UserLocalData>::GetDefault().m_Icon; }
};

template <>
<<<<<<< HEAD
struct StormReflTypeInfo<UserLocalData>::field_data_static<7>
=======
struct StormReflTypeInfo<UserLocalData>::field_data_static<8>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  using member_type = RMergeList<RString>; // RMergeList<RString>
  static constexpr auto GetName() { return "m_IconNames"; }
  static constexpr auto GetType() { return "RMergeList<RString>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2E5D666D; }
  static constexpr unsigned GetTypeNameHash() { return 0x8C9238EC; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_IconNames; }
};

template <typename Self>
struct StormReflTypeInfo<UserLocalData>::field_data<7, Self> : public StormReflTypeInfo<UserLocalData>::field_data_static<7>
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 8; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_IconNames; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserLocalData *>(obj); return &ptr->m_IconNames; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserLocalData *>(obj); return &ptr->m_IconNames; }
};

template <typename Self>
struct StormReflTypeInfo<UserLocalData>::field_data<8, Self> : public StormReflTypeInfo<UserLocalData>::field_data_static<8>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<RString>> & Get() { return self.m_IconNames; }
  std::add_const_t<std::remove_reference_t<RMergeList<RString>>> & Get() const { return self.m_IconNames; }
  void SetDefault() { self.m_IconNames = StormReflTypeInfo<UserLocalData>::GetDefault().m_IconNames; }
};

template <>
<<<<<<< HEAD
struct StormReflTypeInfo<UserLocalData>::field_data_static<8>
=======
struct StormReflTypeInfo<UserLocalData>::field_data_static<9>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_IconURL"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC5DB60F3; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 8; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_IconURL; }
};

template <typename Self>
struct StormReflTypeInfo<UserLocalData>::field_data<8, Self> : public StormReflTypeInfo<UserLocalData>::field_data_static<8>
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 9; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_IconURL; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserLocalData *>(obj); return &ptr->m_IconURL; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserLocalData *>(obj); return &ptr->m_IconURL; }
};

template <typename Self>
struct StormReflTypeInfo<UserLocalData>::field_data<9, Self> : public StormReflTypeInfo<UserLocalData>::field_data_static<9>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_IconURL; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_IconURL; }
  void SetDefault() { self.m_IconURL = StormReflTypeInfo<UserLocalData>::GetDefault().m_IconURL; }
};

template <>
<<<<<<< HEAD
struct StormReflTypeInfo<UserLocalData>::field_data_static<9>
=======
struct StormReflTypeInfo<UserLocalData>::field_data_static<10>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_Celebration"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x47D906C2; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 9; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_Celebration; }
};

template <typename Self>
struct StormReflTypeInfo<UserLocalData>::field_data<9, Self> : public StormReflTypeInfo<UserLocalData>::field_data_static<9>
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 10; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_Celebration; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserLocalData *>(obj); return &ptr->m_Celebration; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserLocalData *>(obj); return &ptr->m_Celebration; }
};

template <typename Self>
struct StormReflTypeInfo<UserLocalData>::field_data<10, Self> : public StormReflTypeInfo<UserLocalData>::field_data_static<10>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_Celebration; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_Celebration; }
  void SetDefault() { self.m_Celebration = StormReflTypeInfo<UserLocalData>::GetDefault().m_Celebration; }
};

template <>
<<<<<<< HEAD
struct StormReflTypeInfo<UserLocalData>::field_data_static<10>
=======
struct StormReflTypeInfo<UserLocalData>::field_data_static<11>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  using member_type = RMergeList<RString>; // RMergeList<RString>
  static constexpr auto GetName() { return "m_CelebrationNames"; }
  static constexpr auto GetType() { return "RMergeList<RString>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB82C555E; }
  static constexpr unsigned GetTypeNameHash() { return 0x8C9238EC; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 10; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_CelebrationNames; }
};

template <typename Self>
struct StormReflTypeInfo<UserLocalData>::field_data<10, Self> : public StormReflTypeInfo<UserLocalData>::field_data_static<10>
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 11; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_CelebrationNames; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserLocalData *>(obj); return &ptr->m_CelebrationNames; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserLocalData *>(obj); return &ptr->m_CelebrationNames; }
};

template <typename Self>
struct StormReflTypeInfo<UserLocalData>::field_data<11, Self> : public StormReflTypeInfo<UserLocalData>::field_data_static<11>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<RString>> & Get() { return self.m_CelebrationNames; }
  std::add_const_t<std::remove_reference_t<RMergeList<RString>>> & Get() const { return self.m_CelebrationNames; }
  void SetDefault() { self.m_CelebrationNames = StormReflTypeInfo<UserLocalData>::GetDefault().m_CelebrationNames; }
};

template <>
<<<<<<< HEAD
struct StormReflTypeInfo<UserLocalData>::field_data_static<11>
{
  using member_type = UserPersistent; // UserPersistent
  static constexpr auto GetName() { return "m_Persistent"; }
  static constexpr auto GetType() { return "UserPersistent"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2DA59512; }
  static constexpr unsigned GetTypeNameHash() { return 0x68592B2E; }
  static constexpr auto GetFieldIndex() { return 11; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_Persistent; }
};

template <typename Self>
struct StormReflTypeInfo<UserLocalData>::field_data<11, Self> : public StormReflTypeInfo<UserLocalData>::field_data_static<11>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, UserPersistent> & Get() { return self.m_Persistent; }
  std::add_const_t<std::remove_reference_t<UserPersistent>> & Get() const { return self.m_Persistent; }
  void SetDefault() { self.m_Persistent = StormReflTypeInfo<UserLocalData>::GetDefault().m_Persistent; }
};

template <>
=======
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
struct StormReflTypeInfo<UserLocalData>::field_data_static<12>
{
  using member_type = RMergeList<RString>; // RMergeList<RString>
  static constexpr auto GetName() { return "m_AutoJoinChannels"; }
  static constexpr auto GetType() { return "RMergeList<RString>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5F0820B9; }
  static constexpr unsigned GetTypeNameHash() { return 0x8C9238EC; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 12; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_AutoJoinChannels; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 12; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_AutoJoinChannels; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserLocalData *>(obj); return &ptr->m_AutoJoinChannels; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserLocalData *>(obj); return &ptr->m_AutoJoinChannels; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<UserLocalData>::field_data<12, Self> : public StormReflTypeInfo<UserLocalData>::field_data_static<12>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<RString>> & Get() { return self.m_AutoJoinChannels; }
  std::add_const_t<std::remove_reference_t<RMergeList<RString>>> & Get() const { return self.m_AutoJoinChannels; }
  void SetDefault() { self.m_AutoJoinChannels = StormReflTypeInfo<UserLocalData>::GetDefault().m_AutoJoinChannels; }
};

template <>
struct StormReflTypeInfo<UserLocalData>::field_data_static<13>
{
  using member_type = RMergeList<DDSSharedLocalCopyPtr<ChannelInfo> >; // RMergeList<DDSSharedLocalCopyPtr<ChannelInfo> >
  static constexpr auto GetName() { return "m_Channels"; }
  static constexpr auto GetType() { return "RMergeList<DDSSharedLocalCopyPtr<ChannelInfo> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x05383698; }
  static constexpr unsigned GetTypeNameHash() { return 0xAC2FCAC4; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 13; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_Channels; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 13; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_Channels; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserLocalData *>(obj); return &ptr->m_Channels; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserLocalData *>(obj); return &ptr->m_Channels; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<UserLocalData>::field_data<13, Self> : public StormReflTypeInfo<UserLocalData>::field_data_static<13>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<DDSSharedLocalCopyPtr<ChannelInfo> >> & Get() { return self.m_Channels; }
  std::add_const_t<std::remove_reference_t<RMergeList<DDSSharedLocalCopyPtr<ChannelInfo> >>> & Get() const { return self.m_Channels; }
  void SetDefault() { self.m_Channels = StormReflTypeInfo<UserLocalData>::GetDefault().m_Channels; }
};

template <>
struct StormReflTypeInfo<UserLocalData>::field_data_static<14>
{
<<<<<<< HEAD
  using member_type = RKey; // RNumber<unsigned long long>
  static constexpr auto GetName() { return "m_PrimarySquad"; }
  static constexpr auto GetType() { return "RNumber<unsigned long long>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5D258656; }
  static constexpr unsigned GetTypeNameHash() { return 0x656FF0F1; }
  static constexpr auto GetFieldIndex() { return 14; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_PrimarySquad; }
=======
  using member_type = RKey; // RNumber<unsigned long>
  static constexpr auto GetName() { return "m_PrimarySquad"; }
  static constexpr auto GetType() { return "RNumber<unsigned long>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5D258656; }
  static constexpr unsigned GetTypeNameHash() { return 0xFD825A3A; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 14; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_PrimarySquad; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserLocalData *>(obj); return &ptr->m_PrimarySquad; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserLocalData *>(obj); return &ptr->m_PrimarySquad; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<UserLocalData>::field_data<14, Self> : public StormReflTypeInfo<UserLocalData>::field_data_static<14>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RKey> & Get() { return self.m_PrimarySquad; }
  std::add_const_t<std::remove_reference_t<RKey>> & Get() const { return self.m_PrimarySquad; }
  void SetDefault() { self.m_PrimarySquad = StormReflTypeInfo<UserLocalData>::GetDefault().m_PrimarySquad; }
};

template <>
struct StormReflTypeInfo<UserLocalData>::field_data_static<15>
{
<<<<<<< HEAD
  using member_type = RKey; // RNumber<unsigned long long>
  static constexpr auto GetName() { return "m_OwnerSquad"; }
  static constexpr auto GetType() { return "RNumber<unsigned long long>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x4F2B2AA5; }
  static constexpr unsigned GetTypeNameHash() { return 0x656FF0F1; }
  static constexpr auto GetFieldIndex() { return 15; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_OwnerSquad; }
=======
  using member_type = RKey; // RNumber<unsigned long>
  static constexpr auto GetName() { return "m_OwnerSquad"; }
  static constexpr auto GetType() { return "RNumber<unsigned long>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x4F2B2AA5; }
  static constexpr unsigned GetTypeNameHash() { return 0xFD825A3A; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 15; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_OwnerSquad; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserLocalData *>(obj); return &ptr->m_OwnerSquad; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserLocalData *>(obj); return &ptr->m_OwnerSquad; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<UserLocalData>::field_data<15, Self> : public StormReflTypeInfo<UserLocalData>::field_data_static<15>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RKey> & Get() { return self.m_OwnerSquad; }
  std::add_const_t<std::remove_reference_t<RKey>> & Get() const { return self.m_OwnerSquad; }
  void SetDefault() { self.m_OwnerSquad = StormReflTypeInfo<UserLocalData>::GetDefault().m_OwnerSquad; }
};

template <>
struct StormReflTypeInfo<UserLocalData>::field_data_static<16>
{
<<<<<<< HEAD
  using member_type = RMap<DDSKey, SquadInfo>; // RMap<unsigned long long, SquadInfo>
  static constexpr auto GetName() { return "m_Squads"; }
  static constexpr auto GetType() { return "RMap<unsigned long long, SquadInfo>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x68903FE7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF3D4CF60; }
  static constexpr auto GetFieldIndex() { return 16; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_Squads; }
=======
  using member_type = RMap<DDSKey, SquadInfo>; // RMap<unsigned long, SquadInfo>
  static constexpr auto GetName() { return "m_Squads"; }
  static constexpr auto GetType() { return "RMap<unsigned long, SquadInfo>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x68903FE7; }
  static constexpr unsigned GetTypeNameHash() { return 0x156CC62C; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 16; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_Squads; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserLocalData *>(obj); return &ptr->m_Squads; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserLocalData *>(obj); return &ptr->m_Squads; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<UserLocalData>::field_data<16, Self> : public StormReflTypeInfo<UserLocalData>::field_data_static<16>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMap<DDSKey, SquadInfo>> & Get() { return self.m_Squads; }
  std::add_const_t<std::remove_reference_t<RMap<DDSKey, SquadInfo>>> & Get() const { return self.m_Squads; }
  void SetDefault() { self.m_Squads = StormReflTypeInfo<UserLocalData>::GetDefault().m_Squads; }
};

template <>
struct StormReflTypeInfo<UserLocalData>::field_data_static<17>
{
  using member_type = RMergeList<UserApplication>; // RMergeList<UserApplication>
  static constexpr auto GetName() { return "m_Applications"; }
  static constexpr auto GetType() { return "RMergeList<UserApplication>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x504B1F96; }
  static constexpr unsigned GetTypeNameHash() { return 0x7E395CFC; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 17; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_Applications; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 17; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_Applications; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserLocalData *>(obj); return &ptr->m_Applications; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserLocalData *>(obj); return &ptr->m_Applications; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<UserLocalData>::field_data<17, Self> : public StormReflTypeInfo<UserLocalData>::field_data_static<17>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<UserApplication>> & Get() { return self.m_Applications; }
  std::add_const_t<std::remove_reference_t<RMergeList<UserApplication>>> & Get() const { return self.m_Applications; }
  void SetDefault() { self.m_Applications = StormReflTypeInfo<UserLocalData>::GetDefault().m_Applications; }
};

template <>
struct StormReflTypeInfo<UserLocalData>::field_data_static<18>
{
  using member_type = RMergeList<UserApplication>; // RMergeList<UserApplication>
  static constexpr auto GetName() { return "m_Requests"; }
  static constexpr auto GetType() { return "RMergeList<UserApplication>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8DA9027F; }
  static constexpr unsigned GetTypeNameHash() { return 0x7E395CFC; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 18; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_Requests; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 18; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_Requests; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserLocalData *>(obj); return &ptr->m_Requests; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserLocalData *>(obj); return &ptr->m_Requests; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<UserLocalData>::field_data<18, Self> : public StormReflTypeInfo<UserLocalData>::field_data_static<18>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<UserApplication>> & Get() { return self.m_Requests; }
  std::add_const_t<std::remove_reference_t<RMergeList<UserApplication>>> & Get() const { return self.m_Requests; }
  void SetDefault() { self.m_Requests = StormReflTypeInfo<UserLocalData>::GetDefault().m_Requests; }
};

template <>
struct StormReflTypeInfo<UserDatabaseObject>
{
  using MyBase = void;
<<<<<<< HEAD
  static constexpr int fields_n = 28;
=======
  static constexpr int fields_n = 27;
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserDatabaseObject"; }
  static constexpr auto GetNameHash() { return 0x8BDD1F29; }
<<<<<<< HEAD
  static UserDatabaseObject & GetDefault() { static UserDatabaseObject def; return def; }
=======
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

>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <>
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_UserName"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAE407D67; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_UserName; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_UserName; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_UserName; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_UserName; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
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
<<<<<<< HEAD
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_PlatformId"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0ED94F3C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_PlatformId; }
=======
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_PlatformId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0ED94F3C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_PlatformId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_PlatformId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_PlatformId; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<1, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_PlatformId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_PlatformId; }
  void SetDefault() { self.m_PlatformId = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_PlatformId; }
};

template <>
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<2>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_UserNameLower"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3D029B9C; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_UserNameLower; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_UserNameLower; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_UserNameLower; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_UserNameLower; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<2, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_UserNameLower; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_UserNameLower; }
  void SetDefault() { self.m_UserNameLower = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_UserNameLower; }
};

template <>
struct StormReflTypeInfo<UserDatabaseObject>::annotations<2>
{
  static constexpr int annotations_n = 1;
  template <int A> struct annoation { };
};

template <>
struct StormReflTypeInfo<UserDatabaseObject>::annotations<2>::annoation<0>
{
  static constexpr const char * GetAnnotation() { return "UniqueIndex"; }
  static constexpr uint32_t GetAnnotationHash() { return 0x5C838CC5; }
};

template <>
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<3>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_AdminLevel"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xACAEF821; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_AdminLevel; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_AdminLevel; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_AdminLevel; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_AdminLevel; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<3, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_AdminLevel; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_AdminLevel; }
  void SetDefault() { self.m_AdminLevel = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_AdminLevel; }
};

template <>
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<4>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_VisibilityFlags"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xBA7F5474; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_VisibilityFlags; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_VisibilityFlags; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_VisibilityFlags; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_VisibilityFlags; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<4, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_VisibilityFlags; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_VisibilityFlags; }
  void SetDefault() { self.m_VisibilityFlags = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_VisibilityFlags; }
};

template <>
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<5>
{
<<<<<<< HEAD
  using member_type = RBool; // RBool
  static constexpr auto GetName() { return "m_Veteran"; }
  static constexpr auto GetType() { return "RBool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5E2C3AEA; }
  static constexpr unsigned GetTypeNameHash() { return 0x50062D06; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_Veteran; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<5, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RBool> & Get() { return self.m_Veteran; }
  std::add_const_t<std::remove_reference_t<RBool>> & Get() const { return self.m_Veteran; }
  void SetDefault() { self.m_Veteran = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_Veteran; }
};

template <>
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<6>
{
=======
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_Created"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x27CFC26D; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_Created; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<6, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<6>
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_Created; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_Created; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_Created; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<5, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<5>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_Created; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_Created; }
  void SetDefault() { self.m_Created = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_Created; }
};

template <>
<<<<<<< HEAD
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<7>
=======
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<6>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_Title"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA600E80B; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_Title; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<7, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<7>
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_Title; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_Title; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_Title; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<6, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<6>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_Title; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_Title; }
  void SetDefault() { self.m_Title = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_Title; }
};

template <>
<<<<<<< HEAD
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<8>
=======
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<7>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  using member_type = RMergeList<RString>; // RMergeList<RString>
  static constexpr auto GetName() { return "m_TitleList"; }
  static constexpr auto GetType() { return "RMergeList<RString>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xABBF57E2; }
  static constexpr unsigned GetTypeNameHash() { return 0x8C9238EC; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 8; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_TitleList; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<8, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<8>
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_TitleList; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_TitleList; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_TitleList; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<7, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<7>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<RString>> & Get() { return self.m_TitleList; }
  std::add_const_t<std::remove_reference_t<RMergeList<RString>>> & Get() const { return self.m_TitleList; }
  void SetDefault() { self.m_TitleList = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_TitleList; }
};

template <>
<<<<<<< HEAD
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<9>
=======
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<8>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_Icon"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5B09BCC4; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 9; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_Icon; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<9, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<9>
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 8; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_Icon; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_Icon; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_Icon; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<8, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<8>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_Icon; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_Icon; }
  void SetDefault() { self.m_Icon = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_Icon; }
};

template <>
<<<<<<< HEAD
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<10>
=======
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<9>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  using member_type = RMergeList<RString>; // RMergeList<RString>
  static constexpr auto GetName() { return "m_IconNames"; }
  static constexpr auto GetType() { return "RMergeList<RString>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2E5D666D; }
  static constexpr unsigned GetTypeNameHash() { return 0x8C9238EC; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 10; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_IconNames; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<10, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<10>
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 9; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_IconNames; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_IconNames; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_IconNames; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<9, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<9>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<RString>> & Get() { return self.m_IconNames; }
  std::add_const_t<std::remove_reference_t<RMergeList<RString>>> & Get() const { return self.m_IconNames; }
  void SetDefault() { self.m_IconNames = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_IconNames; }
};

template <>
<<<<<<< HEAD
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<11>
=======
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<10>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  using member_type = RMergeList<RString>; // RMergeList<RString>
  static constexpr auto GetName() { return "m_IconURLs"; }
  static constexpr auto GetType() { return "RMergeList<RString>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3F7FB7CD; }
  static constexpr unsigned GetTypeNameHash() { return 0x8C9238EC; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 11; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_IconURLs; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<11, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<11>
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 10; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_IconURLs; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_IconURLs; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_IconURLs; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<10, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<10>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<RString>> & Get() { return self.m_IconURLs; }
  std::add_const_t<std::remove_reference_t<RMergeList<RString>>> & Get() const { return self.m_IconURLs; }
  void SetDefault() { self.m_IconURLs = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_IconURLs; }
};

template <>
<<<<<<< HEAD
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<12>
=======
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<11>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_Celebration"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x47D906C2; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 12; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_Celebration; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<12, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<12>
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 11; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_Celebration; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_Celebration; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_Celebration; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<11, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<11>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_Celebration; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_Celebration; }
  void SetDefault() { self.m_Celebration = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_Celebration; }
};

template <>
<<<<<<< HEAD
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<13>
=======
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<12>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  using member_type = RMergeList<RString>; // RMergeList<RString>
  static constexpr auto GetName() { return "m_CelebrationNames"; }
  static constexpr auto GetType() { return "RMergeList<RString>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB82C555E; }
  static constexpr unsigned GetTypeNameHash() { return 0x8C9238EC; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 13; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_CelebrationNames; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<13, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<13>
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 12; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_CelebrationNames; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_CelebrationNames; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_CelebrationNames; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<12, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<12>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<RString>> & Get() { return self.m_CelebrationNames; }
  std::add_const_t<std::remove_reference_t<RMergeList<RString>>> & Get() const { return self.m_CelebrationNames; }
  void SetDefault() { self.m_CelebrationNames = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_CelebrationNames; }
};

template <>
<<<<<<< HEAD
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<14>
=======
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<13>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  using member_type = RMergeList<RInt>; // RMergeList<RNumber<int> >
  static constexpr auto GetName() { return "m_CelebrationIDs"; }
  static constexpr auto GetType() { return "RMergeList<RNumber<int> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE66D4A45; }
  static constexpr unsigned GetTypeNameHash() { return 0xA536E2BA; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 14; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_CelebrationIDs; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<14, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<14>
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 13; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_CelebrationIDs; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_CelebrationIDs; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_CelebrationIDs; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<13, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<13>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<RInt>> & Get() { return self.m_CelebrationIDs; }
  std::add_const_t<std::remove_reference_t<RMergeList<RInt>>> & Get() const { return self.m_CelebrationIDs; }
  void SetDefault() { self.m_CelebrationIDs = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_CelebrationIDs; }
};

template <>
<<<<<<< HEAD
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<15>
=======
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<14>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_LastGamePlayed"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDC1A80E1; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 15; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_LastGamePlayed; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<15, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<15>
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 14; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_LastGamePlayed; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_LastGamePlayed; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_LastGamePlayed; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<14, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<14>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_LastGamePlayed; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_LastGamePlayed; }
  void SetDefault() { self.m_LastGamePlayed = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_LastGamePlayed; }
};

template <>
<<<<<<< HEAD
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<16>
=======
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<15>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  using member_type = GameStatsData; // GameStatsData
  static constexpr auto GetName() { return "m_Stats"; }
  static constexpr auto GetType() { return "GameStatsData"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDA71F7CA; }
  static constexpr unsigned GetTypeNameHash() { return 0x9CB3161C; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 16; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_Stats; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<16, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<16>
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 15; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_Stats; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_Stats; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_Stats; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<15, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<15>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameStatsData> & Get() { return self.m_Stats; }
  std::add_const_t<std::remove_reference_t<GameStatsData>> & Get() const { return self.m_Stats; }
  void SetDefault() { self.m_Stats = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_Stats; }
};

template <>
<<<<<<< HEAD
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<17>
=======
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<16>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_Level"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x17DC5C73; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 17; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_Level; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<17, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<17>
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 16; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_Level; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_Level; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_Level; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<16, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<16>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_Level; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_Level; }
  void SetDefault() { self.m_Level = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_Level; }
};

template <>
<<<<<<< HEAD
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<18>
=======
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<17>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_XP"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x96E11FE7; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 18; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_XP; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<18, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<18>
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 17; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_XP; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_XP; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_XP; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<17, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<17>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_XP; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_XP; }
  void SetDefault() { self.m_XP = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_XP; }
};

template <>
<<<<<<< HEAD
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<19>
=======
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<18>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  using member_type = RSparseList<UserXPGain>; // RSparseList<UserXPGain>
  static constexpr auto GetName() { return "m_XPLog"; }
  static constexpr auto GetType() { return "RSparseList<UserXPGain>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x018834E6; }
  static constexpr unsigned GetTypeNameHash() { return 0xAFBCC99F; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 19; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_XPLog; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<19, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<19>
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 18; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_XPLog; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_XPLog; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_XPLog; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<18, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<18>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RSparseList<UserXPGain>> & Get() { return self.m_XPLog; }
  std::add_const_t<std::remove_reference_t<RSparseList<UserXPGain>>> & Get() const { return self.m_XPLog; }
  void SetDefault() { self.m_XPLog = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_XPLog; }
};

template <>
<<<<<<< HEAD
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<20>
=======
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<19>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  using member_type = UserPersistent; // UserPersistent
  static constexpr auto GetName() { return "m_Persistent"; }
  static constexpr auto GetType() { return "UserPersistent"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2DA59512; }
  static constexpr unsigned GetTypeNameHash() { return 0x68592B2E; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 20; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_Persistent; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<20, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<20>
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 19; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_Persistent; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_Persistent; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_Persistent; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<19, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<19>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, UserPersistent> & Get() { return self.m_Persistent; }
  std::add_const_t<std::remove_reference_t<UserPersistent>> & Get() const { return self.m_Persistent; }
  void SetDefault() { self.m_Persistent = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_Persistent; }
};

template <>
<<<<<<< HEAD
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<21>
=======
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<20>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  using member_type = RMergeList<RString>; // RMergeList<RString>
  static constexpr auto GetName() { return "m_AutoJoinChannels"; }
  static constexpr auto GetType() { return "RMergeList<RString>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5F0820B9; }
  static constexpr unsigned GetTypeNameHash() { return 0x8C9238EC; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 21; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_AutoJoinChannels; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<21, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<21>
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 20; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_AutoJoinChannels; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_AutoJoinChannels; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_AutoJoinChannels; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<20, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<20>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<RString>> & Get() { return self.m_AutoJoinChannels; }
  std::add_const_t<std::remove_reference_t<RMergeList<RString>>> & Get() const { return self.m_AutoJoinChannels; }
  void SetDefault() { self.m_AutoJoinChannels = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_AutoJoinChannels; }
};

template <>
<<<<<<< HEAD
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<22>
{
  using member_type = RKey; // RNumber<unsigned long long>
  static constexpr auto GetName() { return "m_PrimarySquad"; }
  static constexpr auto GetType() { return "RNumber<unsigned long long>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5D258656; }
  static constexpr unsigned GetTypeNameHash() { return 0x656FF0F1; }
  static constexpr auto GetFieldIndex() { return 22; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_PrimarySquad; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<22, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<22>
=======
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<21>
{
  using member_type = RKey; // RNumber<unsigned long>
  static constexpr auto GetName() { return "m_PrimarySquad"; }
  static constexpr auto GetType() { return "RNumber<unsigned long>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5D258656; }
  static constexpr unsigned GetTypeNameHash() { return 0xFD825A3A; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 21; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_PrimarySquad; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_PrimarySquad; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_PrimarySquad; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<21, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<21>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RKey> & Get() { return self.m_PrimarySquad; }
  std::add_const_t<std::remove_reference_t<RKey>> & Get() const { return self.m_PrimarySquad; }
  void SetDefault() { self.m_PrimarySquad = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_PrimarySquad; }
};

template <>
<<<<<<< HEAD
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<23>
{
  using member_type = RKey; // RNumber<unsigned long long>
  static constexpr auto GetName() { return "m_OwnerSquad"; }
  static constexpr auto GetType() { return "RNumber<unsigned long long>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x4F2B2AA5; }
  static constexpr unsigned GetTypeNameHash() { return 0x656FF0F1; }
  static constexpr auto GetFieldIndex() { return 23; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_OwnerSquad; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<23, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<23>
=======
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<22>
{
  using member_type = RKey; // RNumber<unsigned long>
  static constexpr auto GetName() { return "m_OwnerSquad"; }
  static constexpr auto GetType() { return "RNumber<unsigned long>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x4F2B2AA5; }
  static constexpr unsigned GetTypeNameHash() { return 0xFD825A3A; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 22; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_OwnerSquad; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_OwnerSquad; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_OwnerSquad; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<22, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<22>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RKey> & Get() { return self.m_OwnerSquad; }
  std::add_const_t<std::remove_reference_t<RKey>> & Get() const { return self.m_OwnerSquad; }
  void SetDefault() { self.m_OwnerSquad = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_OwnerSquad; }
};

template <>
<<<<<<< HEAD
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<24>
{
  using member_type = RMergeList<RKey>; // RMergeList<RNumber<unsigned long long> >
  static constexpr auto GetName() { return "m_Squads"; }
  static constexpr auto GetType() { return "RMergeList<RNumber<unsigned long long> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x68903FE7; }
  static constexpr unsigned GetTypeNameHash() { return 0x95663C91; }
  static constexpr auto GetFieldIndex() { return 24; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_Squads; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<24, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<24>
=======
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<23>
{
  using member_type = RMergeList<RKey>; // RMergeList<RNumber<unsigned long> >
  static constexpr auto GetName() { return "m_Squads"; }
  static constexpr auto GetType() { return "RMergeList<RNumber<unsigned long> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x68903FE7; }
  static constexpr unsigned GetTypeNameHash() { return 0xD4BB98ED; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 23; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_Squads; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_Squads; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_Squads; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<23, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<23>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<RKey>> & Get() { return self.m_Squads; }
  std::add_const_t<std::remove_reference_t<RMergeList<RKey>>> & Get() const { return self.m_Squads; }
  void SetDefault() { self.m_Squads = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_Squads; }
};

template <>
<<<<<<< HEAD
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<25>
{
  using member_type = RMergeList<RKey>; // RMergeList<RNumber<unsigned long long> >
  static constexpr auto GetName() { return "m_Applications"; }
  static constexpr auto GetType() { return "RMergeList<RNumber<unsigned long long> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x504B1F96; }
  static constexpr unsigned GetTypeNameHash() { return 0x95663C91; }
  static constexpr auto GetFieldIndex() { return 25; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_Applications; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<25, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<25>
=======
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<24>
{
  using member_type = RMergeList<RKey>; // RMergeList<RNumber<unsigned long> >
  static constexpr auto GetName() { return "m_Applications"; }
  static constexpr auto GetType() { return "RMergeList<RNumber<unsigned long> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x504B1F96; }
  static constexpr unsigned GetTypeNameHash() { return 0xD4BB98ED; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 24; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_Applications; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_Applications; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_Applications; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<24, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<24>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<RKey>> & Get() { return self.m_Applications; }
  std::add_const_t<std::remove_reference_t<RMergeList<RKey>>> & Get() const { return self.m_Applications; }
  void SetDefault() { self.m_Applications = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_Applications; }
};

template <>
<<<<<<< HEAD
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<26>
{
  using member_type = RMergeList<RKey>; // RMergeList<RNumber<unsigned long long> >
  static constexpr auto GetName() { return "m_Requests"; }
  static constexpr auto GetType() { return "RMergeList<RNumber<unsigned long long> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8DA9027F; }
  static constexpr unsigned GetTypeNameHash() { return 0x95663C91; }
  static constexpr auto GetFieldIndex() { return 26; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_Requests; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<26, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<26>
=======
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<25>
{
  using member_type = RMergeList<RKey>; // RMergeList<RNumber<unsigned long> >
  static constexpr auto GetName() { return "m_Requests"; }
  static constexpr auto GetType() { return "RMergeList<RNumber<unsigned long> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8DA9027F; }
  static constexpr unsigned GetTypeNameHash() { return 0xD4BB98ED; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 25; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_Requests; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_Requests; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_Requests; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<25, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<25>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<RKey>> & Get() { return self.m_Requests; }
  std::add_const_t<std::remove_reference_t<RMergeList<RKey>>> & Get() const { return self.m_Requests; }
  void SetDefault() { self.m_Requests = StormReflTypeInfo<UserDatabaseObject>::GetDefault().m_Requests; }
};

template <>
<<<<<<< HEAD
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<27>
=======
struct StormReflTypeInfo<UserDatabaseObject>::field_data_static<26>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  using member_type = RMergeList<RString>; // RMergeList<RString>
  static constexpr auto GetName() { return "m_HistoryHosts"; }
  static constexpr auto GetType() { return "RMergeList<RString>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE89E30BC; }
  static constexpr unsigned GetTypeNameHash() { return 0x8C9238EC; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 27; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_HistoryHosts; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<27, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<27>
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 26; }
  static constexpr auto GetMemberPtr() { return &UserDatabaseObject::m_HistoryHosts; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserDatabaseObject *>(obj); return &ptr->m_HistoryHosts; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserDatabaseObject *>(obj); return &ptr->m_HistoryHosts; }
};

template <typename Self>
struct StormReflTypeInfo<UserDatabaseObject>::field_data<26, Self> : public StormReflTypeInfo<UserDatabaseObject>::field_data_static<26>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
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
<<<<<<< HEAD
};
=======
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
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c

template <>
struct StormReflTypeInfo<UserNameLookup>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_UserNameLower"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3D029B9C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserNameLookup::m_UserNameLower; }
=======
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserNameLookup::m_UserNameLower; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserNameLookup *>(obj); return &ptr->m_UserNameLower; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserNameLookup *>(obj); return &ptr->m_UserNameLower; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
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
struct StormReflTypeInfo<User>
{
  using MyBase = void;
  static constexpr int fields_n = 27;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "User"; }
  static constexpr auto GetNameHash() { return 0x2DA17977; }
<<<<<<< HEAD
=======
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

>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <>
struct StormReflTypeInfo<User>::field_data_static<0>
{
  using member_type = UserInfo; // UserInfo
  static constexpr auto GetName() { return "m_UserInfo"; }
  static constexpr auto GetType() { return "UserInfo"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3BEA3236; }
  static constexpr unsigned GetTypeNameHash() { return 0x34B0844E; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &User::m_UserInfo; }
=======
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &User::m_UserInfo; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_UserInfo; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_UserInfo; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
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
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &User::m_LocalInfo; }
=======
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &User::m_LocalInfo; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_LocalInfo; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_LocalInfo; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
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
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &User::m_CharsThrottle; }
=======
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &User::m_CharsThrottle; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_CharsThrottle; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_CharsThrottle; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
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
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &User::m_LinesThrottle; }
=======
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &User::m_LinesThrottle; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_LinesThrottle; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_LinesThrottle; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
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
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &User::m_GameCreationThrottle; }
=======
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &User::m_GameCreationThrottle; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_GameCreationThrottle; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_GameCreationThrottle; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
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
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &User::m_SquadCreationThrottle; }
=======
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &User::m_SquadCreationThrottle; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_SquadCreationThrottle; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_SquadCreationThrottle; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
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
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &User::m_ProfileThrottle; }
=======
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &User::m_ProfileThrottle; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_ProfileThrottle; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_ProfileThrottle; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
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
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &User::m_GameThrottle; }
=======
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &User::m_GameThrottle; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_GameThrottle; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_GameThrottle; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
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
<<<<<<< HEAD
  using member_type = std::vector<DDSKey>; // std::vector<unsigned long long, std::allocator<unsigned long long> >
  static constexpr auto GetName() { return "m_PendingSquadLoads"; }
  static constexpr auto GetType() { return "std::vector<unsigned long long, std::allocator<unsigned long long> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x760654C0; }
  static constexpr unsigned GetTypeNameHash() { return 0xF4103497; }
  static constexpr auto GetFieldIndex() { return 8; }
  static constexpr auto GetMemberPtr() { return &User::m_PendingSquadLoads; }
=======
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
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
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
<<<<<<< HEAD
  using member_type = std::vector<DDSKey>; // std::vector<unsigned long long, std::allocator<unsigned long long> >
  static constexpr auto GetName() { return "m_PendingApplicationLoads"; }
  static constexpr auto GetType() { return "std::vector<unsigned long long, std::allocator<unsigned long long> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0643EE38; }
  static constexpr unsigned GetTypeNameHash() { return 0xF4103497; }
  static constexpr auto GetFieldIndex() { return 9; }
  static constexpr auto GetMemberPtr() { return &User::m_PendingApplicationLoads; }
=======
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
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
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
<<<<<<< HEAD
  using member_type = std::vector<DDSKey>; // std::vector<unsigned long long, std::allocator<unsigned long long> >
  static constexpr auto GetName() { return "m_PendingRequestLoads"; }
  static constexpr auto GetType() { return "std::vector<unsigned long long, std::allocator<unsigned long long> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5997DC89; }
  static constexpr unsigned GetTypeNameHash() { return 0xF4103497; }
  static constexpr auto GetFieldIndex() { return 10; }
  static constexpr auto GetMemberPtr() { return &User::m_PendingRequestLoads; }
=======
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
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
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
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 11; }
  static constexpr auto GetMemberPtr() { return &User::m_CreatingSquad; }
=======
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 11; }
  static constexpr auto GetMemberPtr() { return &User::m_CreatingSquad; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_CreatingSquad; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_CreatingSquad; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
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
<<<<<<< HEAD
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_PendingPrimarySquad"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x385EFE6A; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 12; }
  static constexpr auto GetMemberPtr() { return &User::m_PendingPrimarySquad; }
=======
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
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
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
<<<<<<< HEAD
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_PendingPrimarySquadSettingEndpoint"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFF1448CF; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 13; }
  static constexpr auto GetMemberPtr() { return &User::m_PendingPrimarySquadSettingEndpoint; }
=======
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
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
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
<<<<<<< HEAD
  using member_type = std::map<DDSKey, DDSKey>; // std::map<unsigned long long, unsigned long long, std::less<unsigned long long>, std::allocator<std::pair<const unsigned long long, unsigned long long> > >
  static constexpr auto GetName() { return "m_SquadSubscriptionIds"; }
  static constexpr auto GetType() { return "std::map<unsigned long long, unsigned long long, std::less<unsigned long long>, std::allocator<std::pair<const unsigned long long, unsigned long long> > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE1E0508F; }
  static constexpr unsigned GetTypeNameHash() { return 0xD5EA0660; }
  static constexpr auto GetFieldIndex() { return 14; }
  static constexpr auto GetMemberPtr() { return &User::m_SquadSubscriptionIds; }
=======
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
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
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
<<<<<<< HEAD
  using member_type = std::vector<std::pair<std::pair<DDSKey, DDSKey>, DDSKey> >; // std::vector<std::pair<std::pair<unsigned long long, unsigned long long>, unsigned long long>, std::allocator<std::pair<std::pair<unsigned long long, unsigned long long>, unsigned long long> > >
  static constexpr auto GetName() { return "m_ChannelSubscriptions"; }
  static constexpr auto GetType() { return "std::vector<std::pair<std::pair<unsigned long long, unsigned long long>, unsigned long long>, std::allocator<std::pair<std::pair<unsigned long long, unsigned long long>, unsigned long long> > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5F29A36D; }
  static constexpr unsigned GetTypeNameHash() { return 0x8EBEC131; }
  static constexpr auto GetFieldIndex() { return 15; }
  static constexpr auto GetMemberPtr() { return &User::m_ChannelSubscriptions; }
=======
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
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
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
<<<<<<< HEAD
  using member_type = std::map<DDSKey, std::pair<std::string, std::string> >; // std::map<unsigned long long, std::pair<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::basic_string<char, std::char_traits<char>, std::allocator<char> > >, std::less<unsigned long long>, std::allocator<std::pair<const unsigned long long, std::pair<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::basic_string<char, std::char_traits<char>, std::allocator<char> > > > > >
  static constexpr auto GetName() { return "m_Endpoints"; }
  static constexpr auto GetType() { return "std::map<unsigned long long, std::pair<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::basic_string<char, std::char_traits<char>, std::allocator<char> > >, std::less<unsigned long long>, std::allocator<std::pair<const unsigned long long, std::pair<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::basic_string<char, std::char_traits<char>, std::allocator<char> > > > > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x003D04AB; }
  static constexpr unsigned GetTypeNameHash() { return 0x69CF27A8; }
  static constexpr auto GetFieldIndex() { return 16; }
  static constexpr auto GetMemberPtr() { return &User::m_Endpoints; }
=======
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
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
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
<<<<<<< HEAD
  using member_type = std::vector<DDSKey>; // std::vector<unsigned long long, std::allocator<unsigned long long> >
  static constexpr auto GetName() { return "m_PendingChannelJoins"; }
  static constexpr auto GetType() { return "std::vector<unsigned long long, std::allocator<unsigned long long> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC1D8149F; }
  static constexpr unsigned GetTypeNameHash() { return 0xF4103497; }
  static constexpr auto GetFieldIndex() { return 17; }
  static constexpr auto GetMemberPtr() { return &User::m_PendingChannelJoins; }
=======
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
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
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
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 18; }
  static constexpr auto GetMemberPtr() { return &User::m_InGame; }
=======
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 18; }
  static constexpr auto GetMemberPtr() { return &User::m_InGame; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_InGame; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_InGame; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
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
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 19; }
  static constexpr auto GetMemberPtr() { return &User::m_SentInitialGameData; }
=======
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 19; }
  static constexpr auto GetMemberPtr() { return &User::m_SentInitialGameData; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_SentInitialGameData; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_SentInitialGameData; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
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
<<<<<<< HEAD
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_GameServerId"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x219CFC9D; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 20; }
  static constexpr auto GetMemberPtr() { return &User::m_GameServerId; }
=======
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_GameServerId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x219CFC9D; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 20; }
  static constexpr auto GetMemberPtr() { return &User::m_GameServerId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_GameServerId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_GameServerId; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<User>::field_data<20, Self> : public StormReflTypeInfo<User>::field_data_static<20>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_GameServerId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_GameServerId; }
};

template <>
struct StormReflTypeInfo<User>::field_data_static<21>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_GameId"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA16AE06C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 21; }
  static constexpr auto GetMemberPtr() { return &User::m_GameId; }
=======
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 21; }
  static constexpr auto GetMemberPtr() { return &User::m_GameId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_GameId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_GameId; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<User>::field_data<21, Self> : public StormReflTypeInfo<User>::field_data_static<21>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_GameId; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_GameId; }
};

template <>
struct StormReflTypeInfo<User>::field_data_static<22>
{
<<<<<<< HEAD
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_GameRandomId"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0F8ADA3B; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 22; }
  static constexpr auto GetMemberPtr() { return &User::m_GameRandomId; }
=======
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
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
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
<<<<<<< HEAD
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_GameEndpoint"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x7B3C8A19; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 23; }
  static constexpr auto GetMemberPtr() { return &User::m_GameEndpoint; }
=======
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
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
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
<<<<<<< HEAD
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_GameSubscriptionId"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB3AF2C98; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 24; }
  static constexpr auto GetMemberPtr() { return &User::m_GameSubscriptionId; }
=======
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
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
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
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_CountryCode"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x443BB729; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 25; }
  static constexpr auto GetMemberPtr() { return &User::m_CountryCode; }
=======
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 25; }
  static constexpr auto GetMemberPtr() { return &User::m_CountryCode; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_CountryCode; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_CountryCode; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<User>::field_data<25, Self> : public StormReflTypeInfo<User>::field_data_static<25>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_CountryCode; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_CountryCode; }
};

template <>
struct StormReflTypeInfo<User>::field_data_static<26>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_CurrencyCode"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xEF446721; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 26; }
  static constexpr auto GetMemberPtr() { return &User::m_CurrencyCode; }
=======
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 26; }
  static constexpr auto GetMemberPtr() { return &User::m_CurrencyCode; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<User *>(obj); return &ptr->m_CurrencyCode; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const User *>(obj); return &ptr->m_CurrencyCode; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<User>::field_data<26, Self> : public StormReflTypeInfo<User>::field_data_static<26>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_CurrencyCode; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_CurrencyCode; }
};

template <>
struct StormReflFuncInfo<User>
{
<<<<<<< HEAD
=======
  using MyBase = void;
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
  static constexpr int funcs_n = 101;
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
  using func_ptr_type = void (User::*)();
  using return_type = void;
  static constexpr int params_n = 0;
  static constexpr auto GetName() { return "GiveGifts"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x2627AD3E; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 6; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::GiveGifts; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<7>
{
  using func_ptr_type = void (User::*)(int, std::string);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "HandleGiftData"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x4F7302A9; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 7; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::HandleGiftData; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<7>::param_info<0>
{
  using param_type = int;
  static constexpr auto GetName() { return "ec"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x8DE8BDFF; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<7>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "data"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xADF3F363; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<8>
{
  using func_ptr_type = void (User::*)(DDSKey, std::string);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "JoinChannel"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xBA0542A9; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 8; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::JoinChannel; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<8>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "requesting_endpoint"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x867D7DDF; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<8>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "channel_name"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xC277DD78; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<9>
{
  using func_ptr_type = void (User::*)(DDSKey);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "LeaveChannel"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xBA80150F; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 9; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::LeaveChannel; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<9>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "channel_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xD7357C6D; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<10>
{
  using func_ptr_type = void (User::*)();
  using return_type = void;
  static constexpr int params_n = 0;
  static constexpr auto GetName() { return "LeaveAllChannels"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xA6664CF9; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 10; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::LeaveAllChannels; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<11>
{
  using func_ptr_type = void (User::*)(DDSKey, DDSKey, std::string);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "SendChatToChannel"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x3FFA1AC4; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 11; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::SendChatToChannel; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<11>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "src_endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x7C0D78ED; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<11>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "channel_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xD7357C6D; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<11>::param_info<2>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "message"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xB6BD307F; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<12>
{
  using func_ptr_type = void (User::*)(std::pair<DDSKey, DDSKey>, ChannelJoinResult);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "HandleChannelJoinResponse"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x417CEED3; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 12; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::HandleChannelJoinResponse; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<12>::param_info<0>
{
  using param_type = std::pair<DDSKey, DDSKey>;
  static constexpr auto GetName() { return "join_info"; }
  static constexpr auto GetType() { return "std::pair<DDSKey, DDSKey>"; }
  static constexpr unsigned GetNameHash() { return 0x5AD17CCE; }
  static constexpr unsigned GetTypeNameHash() { return 0x5A7146D6; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<12>::param_info<1>
{
  using param_type = ChannelJoinResult;
  static constexpr auto GetName() { return "result"; }
  static constexpr auto GetType() { return "ChannelJoinResult"; }
  static constexpr unsigned GetNameHash() { return 0x136AC113; }
  static constexpr unsigned GetTypeNameHash() { return 0x94A3601C; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<13>
{
  using func_ptr_type = void (User::*)(DDSKey, std::string, int);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "HandleChannelUpdate"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x58A6FC95; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 13; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::HandleChannelUpdate; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<13>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "channel_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xD7357C6D; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<13>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "data"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xADF3F363; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<13>::param_info<2>
{
  using param_type = int;
  static constexpr auto GetName() { return "version"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xBF1CD3C3; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<14>
{
  using func_ptr_type = void (User::*)(DDSKey, DDSKey, GameInstanceData, std::string);
  using return_type = void;
  static constexpr int params_n = 4;
  static constexpr auto GetName() { return "CreateGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x9EA4204C; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 14; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::CreateGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<14>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "server_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x1844E6B7; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<14>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<14>::param_info<2>
{
  using param_type = GameInstanceData;
  static constexpr auto GetName() { return "creation_data"; }
  static constexpr auto GetType() { return "GameInstanceData"; }
  static constexpr unsigned GetNameHash() { return 0x7085B547; }
  static constexpr unsigned GetTypeNameHash() { return 0xC7A440E6; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<14>::param_info<3>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "password"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x35C246D5; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<15>
{
  using func_ptr_type = void (User::*)(DDSKey, DDSKey, int, std::string, bool);
  using return_type = void;
  static constexpr int params_n = 5;
  static constexpr auto GetName() { return "JoinGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x0B25EB50; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 15; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::JoinGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<15>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "server_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x1844E6B7; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<15>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<15>::param_info<2>
{
  using param_type = int;
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<15>::param_info<3>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "password"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x35C246D5; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<15>::param_info<4>
{
  using param_type = bool;
  static constexpr auto GetName() { return "observer"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetNameHash() { return 0x9B6F44E7; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<16>
{
  using func_ptr_type = void (User::*)(DDSKey, int, DDSKey, DDSKey, std::string);
  using return_type = void;
  static constexpr int params_n = 5;
  static constexpr auto GetName() { return "SetInGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x81F2E0DC; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 16; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::SetInGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<16>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "server_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x1844E6B7; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<16>::param_info<1>
{
  using param_type = int;
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<16>::param_info<2>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "game_random_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xF579374E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<16>::param_info<3>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<16>::param_info<4>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "game_info"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x209C5D7B; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<17>
{
  using func_ptr_type = void (User::*)(DDSKey, DDSKey, int);
  using return_type = void;
  static constexpr int params_n = 3;
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
  static constexpr auto GetName() { return "server_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x1844E6B7; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<17>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<17>::param_info<2>
{
  using param_type = int;
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<18>
{
  using func_ptr_type = void (User::*)(DDSKey, DDSKey, int, DDSKey, std::string, bool);
  using return_type = void;
  static constexpr int params_n = 6;
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
  static constexpr auto GetName() { return "server_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x1844E6B7; }
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
  using param_type = int;
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<18>::param_info<3>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "game_random_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xF579374E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<18>::param_info<4>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "game_info"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x209C5D7B; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<18>::param_info<5>
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
  using func_ptr_type = void (User::*)(DDSKey, std::string);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "SendGameChat"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xD0D87A16; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 19; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::SendGameChat; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<19>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<19>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "msg"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x688A5FAF; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<20>
{
  using func_ptr_type = void (User::*)(DDSKey);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "SwitchTeams"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x894C1DB3; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 20; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::SwitchTeams; }
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
struct StormReflFuncInfo<User>::func_data_static<21>
{
  using func_ptr_type = void (User::*)();
  using return_type = void;
  static constexpr int params_n = 0;
  static constexpr auto GetName() { return "StartGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x40E81A4D; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 21; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::StartGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<22>
{
  using func_ptr_type = void (User::*)();
  using return_type = void;
  static constexpr int params_n = 0;
  static constexpr auto GetName() { return "LeaveGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x45915A7C; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 22; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::LeaveGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<23>
{
  using func_ptr_type = void (User::*)(DDSKey);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "NotifyLeftGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x29289854; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 23; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::NotifyLeftGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<23>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "game_random_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xF579374E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<24>
{
  using func_ptr_type = void (User::*)(std::tuple<int, DDSKey>, std::string);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "HandleGameUpdate"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x44910382; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 24; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::HandleGameUpdate; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<24>::param_info<0>
{
  using param_type = std::tuple<int, DDSKey>;
  static constexpr auto GetName() { return "game_info"; }
  static constexpr auto GetType() { return "std::tuple<int, DDSKey>"; }
  static constexpr unsigned GetNameHash() { return 0x209C5D7B; }
  static constexpr unsigned GetTypeNameHash() { return 0x8D9A7443; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<24>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "data"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xADF3F363; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<25>
{
  using func_ptr_type = void (User::*)(DDSKey, std::string, std::string);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "CreateSquad"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x5409B246; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 25; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::CreateSquad; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<25>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "creator_endpoint"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x93A428E7; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<25>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "squad_name"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x861CED92; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<25>::param_info<2>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "squad_tag"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x3131F92B; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<26>
{
  using func_ptr_type = void (User::*)(DDSKey);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "DestroySquad"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xAE970DCE; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 26; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::DestroySquad; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<26>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "destroyer_endpoint"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x32682131; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<27>
{
  using func_ptr_type = void (User::*)(std::tuple<DDSKey, std::string, std::string>, std::string);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "HandleSquadCreateNameLookupFail"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x93AFE367; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 27; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::HandleSquadCreateNameLookupFail; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<27>::param_info<0>
{
  using param_type = std::tuple<DDSKey, std::string, std::string>;
  static constexpr auto GetName() { return "squad_data"; }
  static constexpr auto GetType() { return "std::tuple<DDSKey, std::string, std::string>"; }
  static constexpr unsigned GetNameHash() { return 0x75CC60F7; }
  static constexpr unsigned GetTypeNameHash() { return 0x3684BDFD; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<27>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "channel_name"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xC277DD78; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<28>
{
  using func_ptr_type = void (User::*)(std::tuple<DDSKey, std::string, std::string>);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "HandleSquadCreateNameLookupSuccess"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xBD93E219; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 28; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::HandleSquadCreateNameLookupSuccess; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<28>::param_info<0>
{
  using param_type = std::tuple<DDSKey, std::string, std::string>;
  static constexpr auto GetName() { return "squad_data"; }
  static constexpr auto GetType() { return "std::tuple<DDSKey, std::string, std::string>"; }
  static constexpr unsigned GetNameHash() { return 0x75CC60F7; }
  static constexpr unsigned GetTypeNameHash() { return 0x3684BDFD; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<29>
{
  using func_ptr_type = void (User::*)(std::tuple<std::string, std::string, DDSKey, DDSKey>, int);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "HandleSquadCreate"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xE3F7BD7C; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 29; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::HandleSquadCreate; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<29>::param_info<0>
{
  using param_type = std::tuple<std::string, std::string, DDSKey, DDSKey>;
  static constexpr auto GetName() { return "squad_info"; }
  static constexpr auto GetType() { return "std::tuple<std::string, std::string, DDSKey, DDSKey>"; }
  static constexpr unsigned GetNameHash() { return 0x13B6A2C3; }
  static constexpr unsigned GetTypeNameHash() { return 0xB8CB73E8; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<29>::param_info<1>
{
  using param_type = int;
  static constexpr auto GetName() { return "ec"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x8DE8BDFF; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<30>
{
  using func_ptr_type = void (User::*)(DDSKey, std::string);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "HandleSquadOperationResponse"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x107A06ED; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 30; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::HandleSquadOperationResponse; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<30>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<30>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "response"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x3E7B0BFB; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<31>
{
  using func_ptr_type = void (User::*)(DDSKey);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "HandleSquadLookupFail"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x52EC44D2; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 31; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::HandleSquadLookupFail; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<31>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<32>
{
  using func_ptr_type = void (User::*)(DDSKey, std::string);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "ApplyToSquad"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x373B4545; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 32; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::ApplyToSquad; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<32>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<32>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "squad_name"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x861CED92; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<33>
{
  using func_ptr_type = void (User::*)(DDSKey, DDSKey, DDSKey);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "AcceptSquadApplication"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xE78CDC24; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 33; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::AcceptSquadApplication; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<33>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<33>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "squad_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xDF1B2C7C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<33>::param_info<2>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xA76ED395; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<34>
{
  using func_ptr_type = void (User::*)(DDSKey, DDSKey);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "RescindSquadApplication"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x8BE7D1B1; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 34; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::RescindSquadApplication; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<34>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<34>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "squad_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xDF1B2C7C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<35>
{
  using func_ptr_type = void (User::*)(DDSKey, DDSKey, DDSKey);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "DeclineSquadApplication"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xD7828C09; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 35; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::DeclineSquadApplication; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<35>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<35>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "squad_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xDF1B2C7C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<35>::param_info<2>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xA76ED395; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<36>
{
  using func_ptr_type = void (User::*)(DDSKey, DDSKey, std::string);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "RequestUserToJoinSquad"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x66C141F0; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 36; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::RequestUserToJoinSquad; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<36>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<36>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "squad_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xDF1B2C7C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<36>::param_info<2>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "user_name"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x24A232CF; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<37>
{
  using func_ptr_type = void (User::*)(std::tuple<DDSKey, DDSKey>, int, std::string);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "HandleSquadRequestNameLookup"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xFA605770; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 37; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::HandleSquadRequestNameLookup; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<37>::param_info<0>
{
  using param_type = std::tuple<DDSKey, DDSKey>;
  static constexpr auto GetName() { return "squad_data"; }
  static constexpr auto GetType() { return "std::tuple<DDSKey, DDSKey>"; }
  static constexpr unsigned GetNameHash() { return 0x75CC60F7; }
  static constexpr unsigned GetTypeNameHash() { return 0x4C951411; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<37>::param_info<1>
{
  using param_type = int;
  static constexpr auto GetName() { return "ec"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x8DE8BDFF; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<37>::param_info<2>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "data"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xADF3F363; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<38>
{
  using func_ptr_type = void (User::*)(DDSKey, DDSKey);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "AcceptSquadRequest"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xF17F7BC4; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 38; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::AcceptSquadRequest; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<38>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<38>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "squad_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xDF1B2C7C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<39>
{
  using func_ptr_type = void (User::*)(DDSKey, DDSKey, DDSKey);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "RescindSquadRequest"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x7BF63CAC; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 39; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::RescindSquadRequest; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<39>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<39>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "squad_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xDF1B2C7C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<39>::param_info<2>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xA76ED395; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<40>
{
  using func_ptr_type = void (User::*)(DDSKey, DDSKey);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "DeclineSquadRequest"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xB1452B77; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 40; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::DeclineSquadRequest; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<40>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<40>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "squad_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xDF1B2C7C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<41>
{
  using func_ptr_type = void (User::*)(DDSKey, DDSKey);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "LeaveSquad"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x720BB790; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 41; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::LeaveSquad; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<41>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<41>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "squad_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xDF1B2C7C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<42>
{
  using func_ptr_type = void (User::*)(DDSKey, DDSKey, DDSKey);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "RemoveSquadMember"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x3D943C34; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 42; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::RemoveSquadMember; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<42>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<42>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "squad_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xDF1B2C7C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<42>::param_info<2>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xA76ED395; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<43>
{
  using func_ptr_type = void (User::*)(DDSKey, DDSKey, DDSKey, int);
  using return_type = void;
  static constexpr int params_n = 4;
  static constexpr auto GetName() { return "EditSquadPermissions"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x930A4359; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 43; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::EditSquadPermissions; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<43>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<43>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "squad_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xDF1B2C7C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<43>::param_info<2>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xA76ED395; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<43>::param_info<3>
{
  using param_type = int;
  static constexpr auto GetName() { return "permissions"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x2DEDCC6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<44>
{
  using func_ptr_type = void (User::*)(DDSKey, DDSKey, std::string);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "EditSquadMotd"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x41AFB51F; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 44; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::EditSquadMotd; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<44>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<44>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "squad_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xDF1B2C7C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<44>::param_info<2>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "motd"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xAA0F656C; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<45>
{
  using func_ptr_type = void (User::*)(DDSKey, DDSKey, bool);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "LockSquadChannel"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xE16F3F06; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 45; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::LockSquadChannel; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<45>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<45>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "squad_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xDF1B2C7C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<45>::param_info<2>
{
  using param_type = bool;
  static constexpr auto GetName() { return "locked"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetNameHash() { return 0xEAD2C891; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<46>
{
  using func_ptr_type = void (User::*)(DDSKey, DDSKey);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "SetPrimarySquad"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xA347985D; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 46; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::SetPrimarySquad; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<46>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<46>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "squad_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xDF1B2C7C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<47>
{
  using func_ptr_type = void (User::*)(DDSKey);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "AddSquadInternal"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x1D497BC3; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 47; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::AddSquadInternal; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<47>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "squad_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xDF1B2C7C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<48>
{
  using func_ptr_type = void (User::*)(DDSKey);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "LoadSquadInternal"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xF479FFD3; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 48; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::LoadSquadInternal; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<48>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "squad_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xDF1B2C7C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<49>
{
  using func_ptr_type = void (User::*)(DDSKey);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "RemoveSquadInternal"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x253837FF; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 49; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::RemoveSquadInternal; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<49>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "squad_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xDF1B2C7C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<50>
{
  using func_ptr_type = void (User::*)(DDSKey, std::string, std::string);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "AddApplicationInternal"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xF489A551; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 50; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::AddApplicationInternal; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<50>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "squad_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xDF1B2C7C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<50>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "squad_name"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x861CED92; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<50>::param_info<2>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "squad_tag"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x3131F92B; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<51>
{
  using func_ptr_type = void (User::*)(DDSKey, std::string, std::string);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "AddSquadRequestInternal"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x915C8745; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 51; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::AddSquadRequestInternal; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<51>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "squad_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xDF1B2C7C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<51>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "squad_name"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x861CED92; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<51>::param_info<2>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "squad_tag"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x3131F92B; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<52>
{
  using func_ptr_type = void (User::*)(int, DDSKey);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "LoadApplicationInternal"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xE521A216; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 52; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::LoadApplicationInternal; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<52>::param_info<0>
{
  using param_type = int;
  static constexpr auto GetName() { return "index"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x80736701; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<52>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "squad_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xDF1B2C7C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<53>
{
  using func_ptr_type = void (User::*)(int, DDSKey);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "LoadSquadRequestInternal"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x79F5FB71; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 53; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::LoadSquadRequestInternal; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<53>::param_info<0>
{
  using param_type = int;
  static constexpr auto GetName() { return "index"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x80736701; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<53>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "squad_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xDF1B2C7C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<54>
{
  using func_ptr_type = void (User::*)(DDSKey);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "CancelApplicationInternal"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x2C127CE7; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 54; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::CancelApplicationInternal; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<54>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "squad_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xDF1B2C7C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<55>
{
  using func_ptr_type = void (User::*)(DDSKey);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "CancelSquadRequestInternal"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xB3860A25; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 55; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::CancelSquadRequestInternal; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<55>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "squad_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xDF1B2C7C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<56>
{
  using func_ptr_type = void (User::*)(DDSKey, std::string);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "HandleSquadUpdate"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xF40468FF; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 56; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::HandleSquadUpdate; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<56>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "squad_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xDF1B2C7C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<56>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "data"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xADF3F363; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<57>
{
  using func_ptr_type = void (User::*)(DDSKey);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "HandleSquadDeleted"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x988B79ED; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 57; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::HandleSquadDeleted; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<57>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "squad_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xDF1B2C7C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<58>
{
  using func_ptr_type = void (User::*)(std::pair<int, DDSKey>, std::string, std::string);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "HandleSquadApplicationLoad"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x9C8BF1D5; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 58; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::HandleSquadApplicationLoad; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<58>::param_info<0>
{
  using param_type = std::pair<int, DDSKey>;
  static constexpr auto GetName() { return "squad_info"; }
  static constexpr auto GetType() { return "std::pair<int, DDSKey>"; }
  static constexpr unsigned GetNameHash() { return 0x13B6A2C3; }
  static constexpr unsigned GetTypeNameHash() { return 0xEAE92E8B; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<58>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "name"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x5E237E06; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<58>::param_info<2>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "tag"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x0389B783; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<59>
{
  using func_ptr_type = void (User::*)(std::pair<int, DDSKey>);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "HandleSquadApplicationLoadFailure"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xF8B3039C; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 59; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::HandleSquadApplicationLoadFailure; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<59>::param_info<0>
{
  using param_type = std::pair<int, DDSKey>;
  static constexpr auto GetName() { return "squad_info"; }
  static constexpr auto GetType() { return "std::pair<int, DDSKey>"; }
  static constexpr unsigned GetNameHash() { return 0x13B6A2C3; }
  static constexpr unsigned GetTypeNameHash() { return 0xEAE92E8B; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<60>
{
  using func_ptr_type = void (User::*)(std::pair<int, DDSKey>, std::string, std::string);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "HandleSquadRequestLoad"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xCF13A014; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 60; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::HandleSquadRequestLoad; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<60>::param_info<0>
{
  using param_type = std::pair<int, DDSKey>;
  static constexpr auto GetName() { return "squad_info"; }
  static constexpr auto GetType() { return "std::pair<int, DDSKey>"; }
  static constexpr unsigned GetNameHash() { return 0x13B6A2C3; }
  static constexpr unsigned GetTypeNameHash() { return 0xEAE92E8B; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<60>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "name"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x5E237E06; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<60>::param_info<2>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "tag"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x0389B783; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<61>
{
  using func_ptr_type = void (User::*)(std::pair<int, DDSKey>);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "HandleSquadRequestLoadFailure"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x6DC5806C; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 61; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::HandleSquadRequestLoadFailure; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<61>::param_info<0>
{
  using param_type = std::pair<int, DDSKey>;
  static constexpr auto GetName() { return "squad_info"; }
  static constexpr auto GetType() { return "std::pair<int, DDSKey>"; }
  static constexpr unsigned GetNameHash() { return 0x13B6A2C3; }
  static constexpr unsigned GetTypeNameHash() { return 0xEAE92E8B; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<62>
{
  using func_ptr_type = void (User::*)(DDSResponder &, std::string, bool);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "AddTitle"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x405C98D2; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 62; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::AddTitle; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<62>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<62>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "title"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x2B36786B; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<62>::param_info<2>
{
  using param_type = bool;
  static constexpr auto GetName() { return "quiet"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetNameHash() { return 0x5695B4A4; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<63>
{
  using func_ptr_type = void (User::*)(int);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "SetTitle"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xDB63A7AB; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 63; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::SetTitle; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<63>::param_info<0>
{
  using param_type = int;
  static constexpr auto GetName() { return "title_index"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x4082D176; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<64>
{
  using func_ptr_type = void (User::*)(DDSResponder &, std::string);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "RemoveTitle"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x23281553; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 64; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::RemoveTitle; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<64>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<64>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "title"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x2B36786B; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<65>
{
  using func_ptr_type = void (User::*)(DDSResponder &, std::string, std::string, bool, bool);
  using return_type = void;
  static constexpr int params_n = 5;
  static constexpr auto GetName() { return "AddIcon"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x6425648B; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 65; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::AddIcon; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<65>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<65>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "icon_url"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x5721C56A; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<65>::param_info<2>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "icon_name"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xC2892F2F; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<65>::param_info<3>
{
  using param_type = bool;
  static constexpr auto GetName() { return "set"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetNameHash() { return 0xE61425DC; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<65>::param_info<4>
{
  using param_type = bool;
  static constexpr auto GetName() { return "quiet"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetNameHash() { return 0x5695B4A4; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<66>
{
  using func_ptr_type = void (User::*)(int);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "SetIcon"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x3FD8AD4B; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 66; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::SetIcon; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<66>::param_info<0>
{
  using param_type = int;
  static constexpr auto GetName() { return "icon_index"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xC25D553C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<67>
{
  using func_ptr_type = void (User::*)(DDSResponder &, std::string);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "RemoveIcon"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x16C43C96; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 67; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::RemoveIcon; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<67>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<67>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "icon"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x659429DB; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<68>
{
  using func_ptr_type = void (User::*)(DDSResponder &, int, std::string, bool, bool);
  using return_type = void;
  static constexpr int params_n = 5;
  static constexpr auto GetName() { return "AddCelebration"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xA78EB7E2; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 68; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::AddCelebration; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<68>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<68>::param_info<1>
{
  using param_type = int;
  static constexpr auto GetName() { return "celebration_id"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x4741E894; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<68>::param_info<2>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "celebration_name"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x8CB20A85; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<68>::param_info<3>
{
  using param_type = bool;
  static constexpr auto GetName() { return "set"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetNameHash() { return 0xE61425DC; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<68>::param_info<4>
{
  using param_type = bool;
  static constexpr auto GetName() { return "quiet"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetNameHash() { return 0x5695B4A4; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<69>
{
  using func_ptr_type = void (User::*)(int);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "SetCelebration"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xF1DC7B5A; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 69; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::SetCelebration; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<69>::param_info<0>
{
  using param_type = int;
  static constexpr auto GetName() { return "celebration_index"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xF41024EF; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<70>
{
  using func_ptr_type = void (User::*)(DDSResponder &, std::string);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "RemoveCelebration"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x95D8460E; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 70; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::RemoveCelebration; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<70>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<70>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "celebration"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xA2860126; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<71>
{
  using func_ptr_type = void (User::*)(GameStatsData, GameInstanceData);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "UpdateStats"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x9953E0FD; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 71; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::UpdateStats; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<71>::param_info<0>
{
  using param_type = GameStatsData;
  static constexpr auto GetName() { return "stats"; }
  static constexpr auto GetType() { return "GameStatsData"; }
  static constexpr unsigned GetNameHash() { return 0x574767AA; }
  static constexpr unsigned GetTypeNameHash() { return 0x9CB3161C; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<71>::param_info<1>
{
  using param_type = GameInstanceData;
  static constexpr auto GetName() { return "instance_data"; }
  static constexpr auto GetType() { return "GameInstanceData"; }
  static constexpr unsigned GetNameHash() { return 0x85F9A3A8; }
  static constexpr unsigned GetTypeNameHash() { return 0xC7A440E6; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<72>
{
  using func_ptr_type = void (User::*)(DDSResponder &);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "FetchStats"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x409D20EC; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 72; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::FetchStats; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<72>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<73>
{
  using func_ptr_type = void (User::*)(DDSResponder &, const std::string &);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "AddAutoJoinChannel"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x339CD39E; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 73; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::AddAutoJoinChannel; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<73>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<73>::param_info<1>
{
  using param_type = const std::string &;
  static constexpr auto GetName() { return "channel_name"; }
  static constexpr auto GetType() { return "const std::string &"; }
  static constexpr unsigned GetNameHash() { return 0xC277DD78; }
  static constexpr unsigned GetTypeNameHash() { return 0xBB24E617; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<74>
{
  using func_ptr_type = void (User::*)(DDSResponder &, const std::string &);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "RemoveAutoJoinChannel"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x3F059FAB; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 74; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::RemoveAutoJoinChannel; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<74>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<74>::param_info<1>
{
  using param_type = const std::string &;
  static constexpr auto GetName() { return "channel_name"; }
  static constexpr auto GetType() { return "const std::string &"; }
  static constexpr unsigned GetNameHash() { return 0xC277DD78; }
  static constexpr unsigned GetTypeNameHash() { return 0xBB24E617; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<75>
{
  using func_ptr_type = void (User::*)(const std::string &);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "ModifyPersistent"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x88E51BEB; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 75; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::ModifyPersistent; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<75>::param_info<0>
{
  using param_type = const std::string &;
  static constexpr auto GetName() { return "change_packet"; }
  static constexpr auto GetType() { return "const std::string &"; }
  static constexpr unsigned GetNameHash() { return 0x347049E4; }
  static constexpr unsigned GetTypeNameHash() { return 0xBB24E617; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<76>
{
  using func_ptr_type = void (User::*)(DDSResponder &, int);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "GiveXP"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x2EFCFE68; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 76; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::GiveXP; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<76>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<76>::param_info<1>
{
  using param_type = int;
  static constexpr auto GetName() { return "amount"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x8EA17042; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<77>
{
  using func_ptr_type = void (User::*)(DDSKey);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "SendXPGain"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x94E853DA; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 77; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::SendXPGain; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<77>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<78>
{
  using func_ptr_type = void (User::*)(bool);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "ApplyXPGain"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x0D3209F1; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 78; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::ApplyXPGain; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<78>::param_info<0>
{
  using param_type = bool;
  static constexpr auto GetName() { return "quiet"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetNameHash() { return 0x5695B4A4; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<79>
{
  using func_ptr_type = void (User::*)();
  using return_type = void;
  static constexpr int params_n = 0;
  static constexpr auto GetName() { return "SkipXPGain"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xC57E398C; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 79; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::SkipXPGain; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<80>
{
  using func_ptr_type = void (User::*)(DDSKey, DDSKey, std::string);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "ProcessSlashCommand"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x34AC6AF1; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 80; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::ProcessSlashCommand; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<80>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<80>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "channel_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x72F5A1AA; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<80>::param_info<2>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "msg"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x688A5FAF; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<81>
{
  using func_ptr_type = void (User::*)(DDSResponder &, DDSKey, const std::string &);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "Rename"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xDE315178; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 81; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::Rename; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<81>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<81>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "src_endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x7C0D78ED; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<81>::param_info<2>
{
  using param_type = const std::string &;
  static constexpr auto GetName() { return "new_name"; }
  static constexpr auto GetType() { return "const std::string &"; }
  static constexpr unsigned GetNameHash() { return 0xAACECADB; }
  static constexpr unsigned GetTypeNameHash() { return 0xBB24E617; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<82>
{
  using func_ptr_type = void (User::*)(DDSResponder &, int);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "MakeAdmin"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x8BF00342; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 82; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::MakeAdmin; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<82>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<82>::param_info<1>
{
  using param_type = int;
  static constexpr auto GetName() { return "admin_level"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x3AC037E9; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<83>
{
  using func_ptr_type = void (User::*)(DDSResponder &, int, std::string);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "BanSelf"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x516FE7BC; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 83; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::BanSelf; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<83>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<83>::param_info<1>
{
  using param_type = int;
  static constexpr auto GetName() { return "duration"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x865F80C0; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<83>::param_info<2>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "message"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xB6BD307F; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<84>
{
  using func_ptr_type = void (User::*)(DDSResponder &, int, std::string);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "BanSelfAndConnections"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xB2ED1E00; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 84; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::BanSelfAndConnections; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<84>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<84>::param_info<1>
{
  using param_type = int;
  static constexpr auto GetName() { return "duration"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x865F80C0; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<84>::param_info<2>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "message"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xB6BD307F; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<85>
{
  using func_ptr_type = void (User::*)(DDSResponder &);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "Kick"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xBEE7703B; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 85; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::Kick; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<85>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<86>
{
<<<<<<< HEAD
  using func_ptr_type = void (User::*)(DDSResponder &, DDSKey, DDSKey, DDSKey, int);
  using return_type = void;
  static constexpr int params_n = 5;
  static constexpr auto GetName() { return "KickFromChannel"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xFFF3C528; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 86; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::KickFromChannel; }
=======
  using func_ptr_type = void (User::*)(DDSKey, bool);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "HandleRename"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x23788C9F; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 86; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::HandleRename; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<86>::param_info<0>
{
<<<<<<< HEAD
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<86>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "src_user_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x2D11805B; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<86>::param_info<2>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "src_user_endpoint"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xAF600F38; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<86>::param_info<3>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "channel_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x72F5A1AA; }
=======
  using param_type = DDSKey;
  static constexpr auto GetName() { return "return_ep"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x941B8DA4; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
<<<<<<< HEAD
struct StormReflFuncInfo<User>::func_data_static<86>::param_info<4>
{
  using param_type = int;
  static constexpr auto GetName() { return "src_admin_level"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x67623132; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
=======
struct StormReflFuncInfo<User>::func_data_static<86>::param_info<1>
{
  using param_type = bool;
  static constexpr auto GetName() { return "success"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetNameHash() { return 0x6F00DFB2; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <>
struct StormReflFuncInfo<User>::func_data_static<87>
{
  using func_ptr_type = void (User::*)(DDSKey);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "FetchWelcomeInfoForEdit"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x4EF182BD; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 87; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::FetchWelcomeInfoForEdit; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<87>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<88>
{
  using func_ptr_type = void (User::*)(DDSKey, std::string);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "HandleWelcomeInfoEdit"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x6376041C; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 88; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::HandleWelcomeInfoEdit; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<88>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<88>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "info"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xCB893157; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<89>
{
  using func_ptr_type = void (User::*)(DDSKey, std::string);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "UpdateWelcomeInfo"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xEBDD5ACF; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 89; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::UpdateWelcomeInfo; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<89>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<89>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "info"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xCB893157; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<90>
{
  using func_ptr_type = void (User::*)(DDSKey, DDSKey);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "FetchChannelTextForEdit"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x0EF454CB; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 90; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::FetchChannelTextForEdit; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<90>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<90>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "channel_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x72F5A1AA; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<91>
{
<<<<<<< HEAD
=======
  using func_ptr_type = void (User::*)(DDSResponder &, DDSKey, DDSKey, DDSKey, int);
  using return_type = void;
  static constexpr int params_n = 5;
  static constexpr auto GetName() { return "KickFromChannel"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xFFF3C528; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 91; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::KickFromChannel; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<91>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<91>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "src_user_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x2D11805B; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<91>::param_info<2>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "src_user_endpoint"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xAF600F38; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<91>::param_info<3>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "channel_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x72F5A1AA; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<91>::param_info<4>
{
  using param_type = int;
  static constexpr auto GetName() { return "src_admin_level"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x67623132; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<92>
{
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
  using func_ptr_type = void (User::*)(std::pair<DDSKey, DDSKey>, std::string);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "HandleChannelTextEdit"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x76BE73EC; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
<<<<<<< HEAD
  static constexpr auto GetFunctionIndex() { return 91; }
=======
  static constexpr auto GetFunctionIndex() { return 92; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
  static constexpr func_ptr_type GetFunctionPtr() { return &User::HandleChannelTextEdit; }
  template <int i>
  struct param_info { };
};

template <>
<<<<<<< HEAD
struct StormReflFuncInfo<User>::func_data_static<91>::param_info<0>
=======
struct StormReflFuncInfo<User>::func_data_static<92>::param_info<0>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  using param_type = std::pair<DDSKey, DDSKey>;
  static constexpr auto GetName() { return "edit_info"; }
  static constexpr auto GetType() { return "std::pair<DDSKey, DDSKey>"; }
  static constexpr unsigned GetNameHash() { return 0x7A4F8EB4; }
  static constexpr unsigned GetTypeNameHash() { return 0x5A7146D6; }
};

template <>
<<<<<<< HEAD
struct StormReflFuncInfo<User>::func_data_static<91>::param_info<1>
=======
struct StormReflFuncInfo<User>::func_data_static<92>::param_info<1>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  using param_type = std::string;
  static constexpr auto GetName() { return "channel_text"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xA7DF04B9; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
<<<<<<< HEAD
struct StormReflFuncInfo<User>::func_data_static<92>
=======
struct StormReflFuncInfo<User>::func_data_static<93>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  using func_ptr_type = void (User::*)(DDSKey, DDSKey, std::string);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "UpdateChannelText"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xDD70E988; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
<<<<<<< HEAD
  static constexpr auto GetFunctionIndex() { return 92; }
=======
  static constexpr auto GetFunctionIndex() { return 93; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
  static constexpr func_ptr_type GetFunctionPtr() { return &User::UpdateChannelText; }
  template <int i>
  struct param_info { };
};

template <>
<<<<<<< HEAD
struct StormReflFuncInfo<User>::func_data_static<92>::param_info<0>
=======
struct StormReflFuncInfo<User>::func_data_static<93>::param_info<0>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
<<<<<<< HEAD
struct StormReflFuncInfo<User>::func_data_static<92>::param_info<1>
=======
struct StormReflFuncInfo<User>::func_data_static<93>::param_info<1>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "channel_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x72F5A1AA; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
<<<<<<< HEAD
struct StormReflFuncInfo<User>::func_data_static<92>::param_info<2>
=======
struct StormReflFuncInfo<User>::func_data_static<93>::param_info<2>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  using param_type = std::string;
  static constexpr auto GetName() { return "channel_text"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xA7DF04B9; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
<<<<<<< HEAD
struct StormReflFuncInfo<User>::func_data_static<93>
=======
struct StormReflFuncInfo<User>::func_data_static<94>
{
  using func_ptr_type = void (User::*)(std::pair<DDSKey, std::string>, int);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "HandleBuiltInChannelCreate"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xDD51D4FB; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 94; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::HandleBuiltInChannelCreate; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<94>::param_info<0>
{
  using param_type = std::pair<DDSKey, std::string>;
  static constexpr auto GetName() { return "return_info"; }
  static constexpr auto GetType() { return "std::pair<DDSKey, std::string>"; }
  static constexpr unsigned GetNameHash() { return 0xAA7F81BE; }
  static constexpr unsigned GetTypeNameHash() { return 0xA4BE8D15; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<94>::param_info<1>
{
  using param_type = int;
  static constexpr auto GetName() { return "ec"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x8DE8BDFF; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<95>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  using func_ptr_type = void (User::*)(DDSKey, std::string);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "HandleCommandResponderMessage"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x17495892; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
<<<<<<< HEAD
  static constexpr auto GetFunctionIndex() { return 93; }
=======
  static constexpr auto GetFunctionIndex() { return 95; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
  static constexpr func_ptr_type GetFunctionPtr() { return &User::HandleCommandResponderMessage; }
  template <int i>
  struct param_info { };
};

template <>
<<<<<<< HEAD
struct StormReflFuncInfo<User>::func_data_static<93>::param_info<0>
=======
struct StormReflFuncInfo<User>::func_data_static<95>::param_info<0>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
<<<<<<< HEAD
struct StormReflFuncInfo<User>::func_data_static<93>::param_info<1>
=======
struct StormReflFuncInfo<User>::func_data_static<95>::param_info<1>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  using param_type = std::string;
  static constexpr auto GetName() { return "msg"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x688A5FAF; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
<<<<<<< HEAD
struct StormReflFuncInfo<User>::func_data_static<94>
=======
struct StormReflFuncInfo<User>::func_data_static<96>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  using func_ptr_type = void (User::*)(DDSKey);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "HandleCommandUserLookupFail"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x0406BB36; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
<<<<<<< HEAD
  static constexpr auto GetFunctionIndex() { return 94; }
=======
  static constexpr auto GetFunctionIndex() { return 96; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
  static constexpr func_ptr_type GetFunctionPtr() { return &User::HandleCommandUserLookupFail; }
  template <int i>
  struct param_info { };
};

template <>
<<<<<<< HEAD
struct StormReflFuncInfo<User>::func_data_static<94>::param_info<0>
=======
struct StormReflFuncInfo<User>::func_data_static<96>::param_info<0>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
<<<<<<< HEAD
struct StormReflFuncInfo<User>::func_data_static<95>
=======
struct StormReflFuncInfo<User>::func_data_static<97>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  using func_ptr_type = void (User::*)(DDSKey);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "HandleCommandSquadLookupFail"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x4E1E0992; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
<<<<<<< HEAD
  static constexpr auto GetFunctionIndex() { return 95; }
=======
  static constexpr auto GetFunctionIndex() { return 97; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
  static constexpr func_ptr_type GetFunctionPtr() { return &User::HandleCommandSquadLookupFail; }
  template <int i>
  struct param_info { };
};

template <>
<<<<<<< HEAD
struct StormReflFuncInfo<User>::func_data_static<95>::param_info<0>
=======
struct StormReflFuncInfo<User>::func_data_static<97>::param_info<0>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
<<<<<<< HEAD
struct StormReflFuncInfo<User>::func_data_static<96>
=======
struct StormReflFuncInfo<User>::func_data_static<98>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  using func_ptr_type = void (User::*)(DDSKey, int);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "HandleBotCreate"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xA902B9D0; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
<<<<<<< HEAD
  static constexpr auto GetFunctionIndex() { return 96; }
=======
  static constexpr auto GetFunctionIndex() { return 98; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
  static constexpr func_ptr_type GetFunctionPtr() { return &User::HandleBotCreate; }
  template <int i>
  struct param_info { };
};

template <>
<<<<<<< HEAD
struct StormReflFuncInfo<User>::func_data_static<96>::param_info<0>
=======
struct StormReflFuncInfo<User>::func_data_static<98>::param_info<0>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
<<<<<<< HEAD
struct StormReflFuncInfo<User>::func_data_static<96>::param_info<1>
{
  using param_type = int;
  static constexpr auto GetName() { return "ec"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x8DE8BDFF; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<97>
{
  using func_ptr_type = void (User::*)(std::pair<DDSKey, std::string>, int);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "HandleBuiltInChannelCreate"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xDD51D4FB; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 97; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::HandleBuiltInChannelCreate; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<97>::param_info<0>
{
  using param_type = std::pair<DDSKey, std::string>;
  static constexpr auto GetName() { return "return_info"; }
  static constexpr auto GetType() { return "std::pair<DDSKey, std::string>"; }
  static constexpr unsigned GetNameHash() { return 0xAA7F81BE; }
  static constexpr unsigned GetTypeNameHash() { return 0xA4BE8D15; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<97>::param_info<1>
=======
struct StormReflFuncInfo<User>::func_data_static<98>::param_info<1>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  using param_type = int;
  static constexpr auto GetName() { return "ec"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x8DE8BDFF; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
<<<<<<< HEAD
struct StormReflFuncInfo<User>::func_data_static<98>
{
  using func_ptr_type = void (User::*)(DDSKey, bool);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "HandleRename"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x23788C9F; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 98; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::HandleRename; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<98>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "return_ep"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x941B8DA4; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<98>::param_info<1>
{
  using param_type = bool;
  static constexpr auto GetName() { return "success"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetNameHash() { return 0x6F00DFB2; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
};

template <>
=======
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
struct StormReflFuncInfo<User>::func_data_static<99>
{
  using func_ptr_type = void (User::*)(DDSResponder &);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "GetInfo"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x02540D1A; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 99; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::GetInfo; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<99>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<100>
{
  using func_ptr_type = void (User::*)(std::tuple<int, std::string, DDSResponderData>, int, std::string);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "HandleUserNameLookupForCall"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x42DB6E29; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 100; }
  static constexpr func_ptr_type GetFunctionPtr() { return &User::HandleUserNameLookupForCall; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<User>::func_data_static<100>::param_info<0>
{
  using param_type = std::tuple<int, std::string, DDSResponderData>;
  static constexpr auto GetName() { return "call_data"; }
  static constexpr auto GetType() { return "std::tuple<int, std::string, DDSResponderData>"; }
  static constexpr unsigned GetNameHash() { return 0x9A72943F; }
  static constexpr unsigned GetTypeNameHash() { return 0xBC210B28; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<100>::param_info<1>
{
  using param_type = int;
  static constexpr auto GetName() { return "ec"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x8DE8BDFF; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<User>::func_data_static<100>::param_info<2>
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
    using type = ::UserPersistent;
  };

  template <>
  struct User::type_info<1>
  {
    using type = ::UserLocalData;
  };

  template <>
  struct User::type_info<2>
  {
    using type = ::UserDatabaseObject;
  };

  template <>
  struct User::type_info<3>
  {
    using type = ::UserNameLookup;
  };

  template <>
  struct User::type_info<4>
  {
    using type = ::User;
  };

}

