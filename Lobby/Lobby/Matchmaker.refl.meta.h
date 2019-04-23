#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "Matchmaker.refl.h"
#include "Game/GameNetworkData.refl.meta.h"
#include "LobbyShared/SharedTypes.refl.meta.h"


template <>
struct StormReflTypeInfo<PlaylistDatabaseElement>
{
  using MyBase = void;
  static constexpr int fields_n = 5;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "PlaylistDatabaseElement"; }
  static constexpr auto GetNameHash() { return 0x5E943D5F; }
  static constexpr bool HasDefault() { return true; }
  static PlaylistDatabaseElement & GetDefault() { static PlaylistDatabaseElement def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<PlaylistDatabaseElement *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const PlaylistDatabaseElement *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<PlaylistDatabaseElement *>(ptr);
    if(typeid(PlaylistDatabaseElement).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const PlaylistDatabaseElement *>(ptr);
    if(typeid(PlaylistDatabaseElement).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<PlaylistDatabaseElement>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &PlaylistDatabaseElement::m_Name; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlaylistDatabaseElement *>(obj); return &ptr->m_Name; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlaylistDatabaseElement *>(obj); return &ptr->m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<PlaylistDatabaseElement>::field_data<0, Self> : public StormReflTypeInfo<PlaylistDatabaseElement>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<PlaylistDatabaseElement>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<PlaylistDatabaseElement>::field_data_static<1>
{
  using member_type = std::vector<GameInitSettings>; // std::vector<GameInitSettings, std::allocator<GameInitSettings> >
  static constexpr auto GetName() { return "m_GameModes"; }
  static constexpr auto GetType() { return "std::vector<GameInitSettings, std::allocator<GameInitSettings> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF14C6D04; }
  static constexpr unsigned GetTypeNameHash() { return 0xC7D24044; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &PlaylistDatabaseElement::m_GameModes; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlaylistDatabaseElement *>(obj); return &ptr->m_GameModes; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlaylistDatabaseElement *>(obj); return &ptr->m_GameModes; }
};

template <typename Self>
struct StormReflTypeInfo<PlaylistDatabaseElement>::field_data<1, Self> : public StormReflTypeInfo<PlaylistDatabaseElement>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<GameInitSettings>> & Get() { return self.m_GameModes; }
  std::add_const_t<std::remove_reference_t<std::vector<GameInitSettings>>> & Get() const { return self.m_GameModes; }
  void SetDefault() { self.m_GameModes = StormReflTypeInfo<PlaylistDatabaseElement>::GetDefault().m_GameModes; }
};

template <>
struct StormReflTypeInfo<PlaylistDatabaseElement>::field_data_static<2>
{
  using member_type = int [2]; // int [2]
  static constexpr auto GetName() { return "m_TeamSizes"; }
  static constexpr auto GetType() { return "int [2]"; }
  static constexpr unsigned GetFieldNameHash() { return 0x27BB0D16; }
  static constexpr unsigned GetTypeNameHash() { return 0x859FE93A; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &PlaylistDatabaseElement::m_TeamSizes; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlaylistDatabaseElement *>(obj); return &ptr->m_TeamSizes; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlaylistDatabaseElement *>(obj); return &ptr->m_TeamSizes; }
};

template <typename Self>
struct StormReflTypeInfo<PlaylistDatabaseElement>::field_data<2, Self> : public StormReflTypeInfo<PlaylistDatabaseElement>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int [2]> & Get() { return self.m_TeamSizes; }
  std::add_const_t<std::remove_reference_t<int [2]>> & Get() const { return self.m_TeamSizes; }
};

template <>
struct StormReflTypeInfo<PlaylistDatabaseElement>::field_data_static<3>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_AllowParties"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xCA485774; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &PlaylistDatabaseElement::m_AllowParties; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlaylistDatabaseElement *>(obj); return &ptr->m_AllowParties; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlaylistDatabaseElement *>(obj); return &ptr->m_AllowParties; }
};

template <typename Self>
struct StormReflTypeInfo<PlaylistDatabaseElement>::field_data<3, Self> : public StormReflTypeInfo<PlaylistDatabaseElement>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_AllowParties; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_AllowParties; }
  void SetDefault() { self.m_AllowParties = StormReflTypeInfo<PlaylistDatabaseElement>::GetDefault().m_AllowParties; }
};

template <>
struct StormReflTypeInfo<PlaylistDatabaseElement>::field_data_static<4>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_TotalGameSize"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDC97E526; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &PlaylistDatabaseElement::m_TotalGameSize; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlaylistDatabaseElement *>(obj); return &ptr->m_TotalGameSize; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlaylistDatabaseElement *>(obj); return &ptr->m_TotalGameSize; }
};

template <typename Self>
struct StormReflTypeInfo<PlaylistDatabaseElement>::field_data<4, Self> : public StormReflTypeInfo<PlaylistDatabaseElement>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_TotalGameSize; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_TotalGameSize; }
  void SetDefault() { self.m_TotalGameSize = StormReflTypeInfo<PlaylistDatabaseElement>::GetDefault().m_TotalGameSize; }
};

template <>
struct StormReflTypeInfo<PlaylistDatabaseObj>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "PlaylistDatabaseObj"; }
  static constexpr auto GetNameHash() { return 0x89C7D86E; }
  static constexpr bool HasDefault() { return true; }
  static PlaylistDatabaseObj & GetDefault() { static PlaylistDatabaseObj def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<PlaylistDatabaseObj *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const PlaylistDatabaseObj *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<PlaylistDatabaseObj *>(ptr);
    if(typeid(PlaylistDatabaseObj).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const PlaylistDatabaseObj *>(ptr);
    if(typeid(PlaylistDatabaseObj).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<PlaylistDatabaseObj>::field_data_static<0>
{
  using member_type = std::vector<PlaylistDatabaseElement>; // std::vector<PlaylistDatabaseElement, std::allocator<PlaylistDatabaseElement> >
  static constexpr auto GetName() { return "m_Elements"; }
  static constexpr auto GetType() { return "std::vector<PlaylistDatabaseElement, std::allocator<PlaylistDatabaseElement> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB266D373; }
  static constexpr unsigned GetTypeNameHash() { return 0x18F69FD1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &PlaylistDatabaseObj::m_Elements; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlaylistDatabaseObj *>(obj); return &ptr->m_Elements; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlaylistDatabaseObj *>(obj); return &ptr->m_Elements; }
};

template <typename Self>
struct StormReflTypeInfo<PlaylistDatabaseObj>::field_data<0, Self> : public StormReflTypeInfo<PlaylistDatabaseObj>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<PlaylistDatabaseElement>> & Get() { return self.m_Elements; }
  std::add_const_t<std::remove_reference_t<std::vector<PlaylistDatabaseElement>>> & Get() const { return self.m_Elements; }
  void SetDefault() { self.m_Elements = StormReflTypeInfo<PlaylistDatabaseObj>::GetDefault().m_Elements; }
};

template <>
struct StormReflTypeInfo<PlaylistBucketUser>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "PlaylistBucketUser"; }
  static constexpr auto GetNameHash() { return 0x6F8E21B5; }
  static constexpr bool HasDefault() { return true; }
  static PlaylistBucketUser & GetDefault() { static PlaylistBucketUser def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<PlaylistBucketUser *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const PlaylistBucketUser *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<PlaylistBucketUser *>(ptr);
    if(typeid(PlaylistBucketUser).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const PlaylistBucketUser *>(ptr);
    if(typeid(PlaylistBucketUser).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<PlaylistBucketUser>::field_data_static<0>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_UserKey"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE6008E39; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &PlaylistBucketUser::m_UserKey; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlaylistBucketUser *>(obj); return &ptr->m_UserKey; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlaylistBucketUser *>(obj); return &ptr->m_UserKey; }
};

template <typename Self>
struct StormReflTypeInfo<PlaylistBucketUser>::field_data<0, Self> : public StormReflTypeInfo<PlaylistBucketUser>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_UserKey; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_UserKey; }
  void SetDefault() { self.m_UserKey = StormReflTypeInfo<PlaylistBucketUser>::GetDefault().m_UserKey; }
};

template <>
struct StormReflTypeInfo<PlaylistBucketUser>::field_data_static<1>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_EndpointId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFC70D3D1; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &PlaylistBucketUser::m_EndpointId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlaylistBucketUser *>(obj); return &ptr->m_EndpointId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlaylistBucketUser *>(obj); return &ptr->m_EndpointId; }
};

template <typename Self>
struct StormReflTypeInfo<PlaylistBucketUser>::field_data<1, Self> : public StormReflTypeInfo<PlaylistBucketUser>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_EndpointId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_EndpointId; }
  void SetDefault() { self.m_EndpointId = StormReflTypeInfo<PlaylistBucketUser>::GetDefault().m_EndpointId; }
};

template <>
struct StormReflTypeInfo<PlaylistBucketUserList>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "PlaylistBucketUserList"; }
  static constexpr auto GetNameHash() { return 0x8FD40C55; }
  static constexpr bool HasDefault() { return true; }
  static PlaylistBucketUserList & GetDefault() { static PlaylistBucketUserList def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<PlaylistBucketUserList *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const PlaylistBucketUserList *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<PlaylistBucketUserList *>(ptr);
    if(typeid(PlaylistBucketUserList).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const PlaylistBucketUserList *>(ptr);
    if(typeid(PlaylistBucketUserList).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<PlaylistBucketUserList>::field_data_static<0>
{
  using member_type = PlaylistBucketUser; // PlaylistBucketUser
  static constexpr auto GetName() { return "m_PrimaryUser"; }
  static constexpr auto GetType() { return "PlaylistBucketUser"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAA64FC85; }
  static constexpr unsigned GetTypeNameHash() { return 0x6F8E21B5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &PlaylistBucketUserList::m_PrimaryUser; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlaylistBucketUserList *>(obj); return &ptr->m_PrimaryUser; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlaylistBucketUserList *>(obj); return &ptr->m_PrimaryUser; }
};

template <typename Self>
struct StormReflTypeInfo<PlaylistBucketUserList>::field_data<0, Self> : public StormReflTypeInfo<PlaylistBucketUserList>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, PlaylistBucketUser> & Get() { return self.m_PrimaryUser; }
  std::add_const_t<std::remove_reference_t<PlaylistBucketUser>> & Get() const { return self.m_PrimaryUser; }
  void SetDefault() { self.m_PrimaryUser = StormReflTypeInfo<PlaylistBucketUserList>::GetDefault().m_PrimaryUser; }
};

template <>
struct StormReflTypeInfo<PlaylistBucketUserList>::field_data_static<1>
{
  using member_type = std::vector<PlaylistBucketUser>; // std::vector<PlaylistBucketUser, std::allocator<PlaylistBucketUser> >
  static constexpr auto GetName() { return "m_ExtraUsers"; }
  static constexpr auto GetType() { return "std::vector<PlaylistBucketUser, std::allocator<PlaylistBucketUser> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x96A3D025; }
  static constexpr unsigned GetTypeNameHash() { return 0xFAA1F222; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &PlaylistBucketUserList::m_ExtraUsers; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlaylistBucketUserList *>(obj); return &ptr->m_ExtraUsers; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlaylistBucketUserList *>(obj); return &ptr->m_ExtraUsers; }
};

template <typename Self>
struct StormReflTypeInfo<PlaylistBucketUserList>::field_data<1, Self> : public StormReflTypeInfo<PlaylistBucketUserList>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<PlaylistBucketUser>> & Get() { return self.m_ExtraUsers; }
  std::add_const_t<std::remove_reference_t<std::vector<PlaylistBucketUser>>> & Get() const { return self.m_ExtraUsers; }
  void SetDefault() { self.m_ExtraUsers = StormReflTypeInfo<PlaylistBucketUserList>::GetDefault().m_ExtraUsers; }
};

template <>
struct StormReflTypeInfo<PlaylistBucket>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "PlaylistBucket"; }
  static constexpr auto GetNameHash() { return 0x04D3BE97; }
  static constexpr bool HasDefault() { return true; }
  static PlaylistBucket & GetDefault() { static PlaylistBucket def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<PlaylistBucket *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const PlaylistBucket *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<PlaylistBucket *>(ptr);
    if(typeid(PlaylistBucket).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const PlaylistBucket *>(ptr);
    if(typeid(PlaylistBucket).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<PlaylistBucket>::field_data_static<0>
{
  using member_type = std::vector<PlaylistBucketUserList>; // std::vector<PlaylistBucketUserList, std::allocator<PlaylistBucketUserList> >
  static constexpr auto GetName() { return "m_Users"; }
  static constexpr auto GetType() { return "std::vector<PlaylistBucketUserList, std::allocator<PlaylistBucketUserList> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x99B53589; }
  static constexpr unsigned GetTypeNameHash() { return 0xBCADCBF6; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &PlaylistBucket::m_Users; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlaylistBucket *>(obj); return &ptr->m_Users; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlaylistBucket *>(obj); return &ptr->m_Users; }
};

template <typename Self>
struct StormReflTypeInfo<PlaylistBucket>::field_data<0, Self> : public StormReflTypeInfo<PlaylistBucket>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<PlaylistBucketUserList>> & Get() { return self.m_Users; }
  std::add_const_t<std::remove_reference_t<std::vector<PlaylistBucketUserList>>> & Get() const { return self.m_Users; }
  void SetDefault() { self.m_Users = StormReflTypeInfo<PlaylistBucket>::GetDefault().m_Users; }
};

template <>
struct StormReflTypeInfo<PlaylistBucketList>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "PlaylistBucketList"; }
  static constexpr auto GetNameHash() { return 0xA6D50FE4; }
  static constexpr bool HasDefault() { return true; }
  static PlaylistBucketList & GetDefault() { static PlaylistBucketList def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<PlaylistBucketList *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const PlaylistBucketList *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<PlaylistBucketList *>(ptr);
    if(typeid(PlaylistBucketList).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const PlaylistBucketList *>(ptr);
    if(typeid(PlaylistBucketList).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<PlaylistBucketList>::field_data_static<0>
{
  using member_type = std::vector<PlaylistBucket>; // std::vector<PlaylistBucket, std::allocator<PlaylistBucket> >
  static constexpr auto GetName() { return "m_Buckets"; }
  static constexpr auto GetType() { return "std::vector<PlaylistBucket, std::allocator<PlaylistBucket> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB1AE8335; }
  static constexpr unsigned GetTypeNameHash() { return 0x0C1C0B86; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &PlaylistBucketList::m_Buckets; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlaylistBucketList *>(obj); return &ptr->m_Buckets; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlaylistBucketList *>(obj); return &ptr->m_Buckets; }
};

template <typename Self>
struct StormReflTypeInfo<PlaylistBucketList>::field_data<0, Self> : public StormReflTypeInfo<PlaylistBucketList>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<PlaylistBucket>> & Get() { return self.m_Buckets; }
  std::add_const_t<std::remove_reference_t<std::vector<PlaylistBucket>>> & Get() const { return self.m_Buckets; }
  void SetDefault() { self.m_Buckets = StormReflTypeInfo<PlaylistBucketList>::GetDefault().m_Buckets; }
};

template <>
struct StormReflTypeInfo<RefillGame>
{
  using MyBase = void;
  static constexpr int fields_n = 5;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "RefillGame"; }
  static constexpr auto GetNameHash() { return 0xC19C4E21; }
  static constexpr bool HasDefault() { return true; }
  static RefillGame & GetDefault() { static RefillGame def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<RefillGame *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const RefillGame *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<RefillGame *>(ptr);
    if(typeid(RefillGame).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const RefillGame *>(ptr);
    if(typeid(RefillGame).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<RefillGame>::field_data_static<0>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_GameId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA16AE06C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &RefillGame::m_GameId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<RefillGame *>(obj); return &ptr->m_GameId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const RefillGame *>(obj); return &ptr->m_GameId; }
};

template <typename Self>
struct StormReflTypeInfo<RefillGame>::field_data<0, Self> : public StormReflTypeInfo<RefillGame>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_GameId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_GameId; }
  void SetDefault() { self.m_GameId = StormReflTypeInfo<RefillGame>::GetDefault().m_GameId; }
};

template <>
struct StormReflTypeInfo<RefillGame>::field_data_static<1>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_Playlist"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x21AEC503; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &RefillGame::m_Playlist; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<RefillGame *>(obj); return &ptr->m_Playlist; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const RefillGame *>(obj); return &ptr->m_Playlist; }
};

template <typename Self>
struct StormReflTypeInfo<RefillGame>::field_data<1, Self> : public StormReflTypeInfo<RefillGame>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_Playlist; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_Playlist; }
  void SetDefault() { self.m_Playlist = StormReflTypeInfo<RefillGame>::GetDefault().m_Playlist; }
};

template <>
struct StormReflTypeInfo<RefillGame>::field_data_static<2>
{
  using member_type = int [2]; // int [2]
  static constexpr auto GetName() { return "m_PlayersNeeded"; }
  static constexpr auto GetType() { return "int [2]"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF75AEFCE; }
  static constexpr unsigned GetTypeNameHash() { return 0x859FE93A; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &RefillGame::m_PlayersNeeded; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<RefillGame *>(obj); return &ptr->m_PlayersNeeded; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const RefillGame *>(obj); return &ptr->m_PlayersNeeded; }
};

template <typename Self>
struct StormReflTypeInfo<RefillGame>::field_data<2, Self> : public StormReflTypeInfo<RefillGame>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int [2]> & Get() { return self.m_PlayersNeeded; }
  std::add_const_t<std::remove_reference_t<int [2]>> & Get() const { return self.m_PlayersNeeded; }
};

template <>
struct StormReflTypeInfo<RefillGame>::field_data_static<3>
{
  using member_type = int [2]; // int [2]
  static constexpr auto GetName() { return "m_PlayersAssigned"; }
  static constexpr auto GetType() { return "int [2]"; }
  static constexpr unsigned GetFieldNameHash() { return 0x21EF091D; }
  static constexpr unsigned GetTypeNameHash() { return 0x859FE93A; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &RefillGame::m_PlayersAssigned; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<RefillGame *>(obj); return &ptr->m_PlayersAssigned; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const RefillGame *>(obj); return &ptr->m_PlayersAssigned; }
};

template <typename Self>
struct StormReflTypeInfo<RefillGame>::field_data<3, Self> : public StormReflTypeInfo<RefillGame>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int [2]> & Get() { return self.m_PlayersAssigned; }
  std::add_const_t<std::remove_reference_t<int [2]>> & Get() const { return self.m_PlayersAssigned; }
};

template <>
struct StormReflTypeInfo<RefillGame>::field_data_static<4>
{
  using member_type = int [2]; // int [2]
  static constexpr auto GetName() { return "m_PlayersLeft"; }
  static constexpr auto GetType() { return "int [2]"; }
  static constexpr unsigned GetFieldNameHash() { return 0x9921DD84; }
  static constexpr unsigned GetTypeNameHash() { return 0x859FE93A; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &RefillGame::m_PlayersLeft; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<RefillGame *>(obj); return &ptr->m_PlayersLeft; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const RefillGame *>(obj); return &ptr->m_PlayersLeft; }
};

template <typename Self>
struct StormReflTypeInfo<RefillGame>::field_data<4, Self> : public StormReflTypeInfo<RefillGame>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int [2]> & Get() { return self.m_PlayersLeft; }
  std::add_const_t<std::remove_reference_t<int [2]>> & Get() const { return self.m_PlayersLeft; }
};

template <>
struct StormReflTypeInfo<RefillGameList>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "RefillGameList"; }
  static constexpr auto GetNameHash() { return 0xB7E70887; }
  static constexpr bool HasDefault() { return true; }
  static RefillGameList & GetDefault() { static RefillGameList def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<RefillGameList *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const RefillGameList *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<RefillGameList *>(ptr);
    if(typeid(RefillGameList).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const RefillGameList *>(ptr);
    if(typeid(RefillGameList).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<RefillGameList>::field_data_static<0>
{
  using member_type = std::vector<RefillGame>; // std::vector<RefillGame, std::allocator<RefillGame> >
  static constexpr auto GetName() { return "m_Games"; }
  static constexpr auto GetType() { return "std::vector<RefillGame, std::allocator<RefillGame> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x7215BB51; }
  static constexpr unsigned GetTypeNameHash() { return 0x552EC102; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &RefillGameList::m_Games; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<RefillGameList *>(obj); return &ptr->m_Games; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const RefillGameList *>(obj); return &ptr->m_Games; }
};

template <typename Self>
struct StormReflTypeInfo<RefillGameList>::field_data<0, Self> : public StormReflTypeInfo<RefillGameList>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<RefillGame>> & Get() { return self.m_Games; }
  std::add_const_t<std::remove_reference_t<std::vector<RefillGame>>> & Get() const { return self.m_Games; }
  void SetDefault() { self.m_Games = StormReflTypeInfo<RefillGameList>::GetDefault().m_Games; }
};

template <>
struct StormReflTypeInfo<Matchmaker>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "Matchmaker"; }
  static constexpr auto GetNameHash() { return 0xB50EBD0D; }
  static constexpr bool HasDefault() { return false; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<Matchmaker *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const Matchmaker *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<Matchmaker *>(ptr);
    if(typeid(Matchmaker).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const Matchmaker *>(ptr);
    if(typeid(Matchmaker).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflFuncInfo<Matchmaker>
{
  using MyBase = void;
  static constexpr int funcs_n = 5;
  template <int N> struct func_data_static {};
};

template <>
struct StormReflFuncInfo<Matchmaker>::func_data_static<0>
{
  using func_ptr_type = void (Matchmaker::*)(const PlaylistBucketUserList &, const UserZoneInfo &, uint32_t);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "AddCasualUser"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x95A31C02; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 0; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Matchmaker::AddCasualUser; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Matchmaker>::func_data_static<0>::param_info<0>
{
  using param_type = const PlaylistBucketUserList &;
  static constexpr auto GetName() { return "user"; }
  static constexpr auto GetType() { return "const PlaylistBucketUserList &"; }
  static constexpr unsigned GetNameHash() { return 0x8D93D649; }
  static constexpr unsigned GetTypeNameHash() { return 0xF122458A; }
};

template <>
struct StormReflFuncInfo<Matchmaker>::func_data_static<0>::param_info<1>
{
  using param_type = const UserZoneInfo &;
  static constexpr auto GetName() { return "zone_info"; }
  static constexpr auto GetType() { return "const UserZoneInfo &"; }
  static constexpr unsigned GetNameHash() { return 0x5971F0F2; }
  static constexpr unsigned GetTypeNameHash() { return 0x7A017F3C; }
};

template <>
struct StormReflFuncInfo<Matchmaker>::func_data_static<0>::param_info<2>
{
  using param_type = uint32_t;
  static constexpr auto GetName() { return "playlist_mask"; }
  static constexpr auto GetType() { return "uint32_t"; }
  static constexpr unsigned GetNameHash() { return 0xDF76F452; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E2AF381; }
};

template <>
struct StormReflFuncInfo<Matchmaker>::func_data_static<1>
{
  using func_ptr_type = void (Matchmaker::*)(const PlaylistBucketUserList &, const UserZoneInfo &, uint32_t);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "AddCompetitiveUser"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x2B9AA7B3; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 1; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Matchmaker::AddCompetitiveUser; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Matchmaker>::func_data_static<1>::param_info<0>
{
  using param_type = const PlaylistBucketUserList &;
  static constexpr auto GetName() { return "user"; }
  static constexpr auto GetType() { return "const PlaylistBucketUserList &"; }
  static constexpr unsigned GetNameHash() { return 0x8D93D649; }
  static constexpr unsigned GetTypeNameHash() { return 0xF122458A; }
};

template <>
struct StormReflFuncInfo<Matchmaker>::func_data_static<1>::param_info<1>
{
  using param_type = const UserZoneInfo &;
  static constexpr auto GetName() { return "zone_info"; }
  static constexpr auto GetType() { return "const UserZoneInfo &"; }
  static constexpr unsigned GetNameHash() { return 0x5971F0F2; }
  static constexpr unsigned GetTypeNameHash() { return 0x7A017F3C; }
};

template <>
struct StormReflFuncInfo<Matchmaker>::func_data_static<1>::param_info<2>
{
  using param_type = uint32_t;
  static constexpr auto GetName() { return "playlist_mask"; }
  static constexpr auto GetType() { return "uint32_t"; }
  static constexpr unsigned GetNameHash() { return 0xDF76F452; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E2AF381; }
};

template <>
struct StormReflFuncInfo<Matchmaker>::func_data_static<2>
{
  using func_ptr_type = void (Matchmaker::*)(DDSKey);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "RemoveCasualUser"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x1B3E132E; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 2; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Matchmaker::RemoveCasualUser; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Matchmaker>::func_data_static<2>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x8D93D649; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Matchmaker>::func_data_static<3>
{
  using func_ptr_type = void (Matchmaker::*)(DDSKey);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "RemoveCompetitiveUser"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x2703EB86; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 3; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Matchmaker::RemoveCompetitiveUser; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Matchmaker>::func_data_static<3>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x8D93D649; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Matchmaker>::func_data_static<4>
{
  using func_ptr_type = void (Matchmaker::*)(DDSKey, int, int);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "NotifyPlayerLeftCasualGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xC8D5FF0D; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 4; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Matchmaker::NotifyPlayerLeftCasualGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Matchmaker>::func_data_static<4>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Matchmaker>::func_data_static<4>::param_info<1>
{
  using param_type = int;
  static constexpr auto GetName() { return "team"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xC4E0A61F; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<Matchmaker>::func_data_static<4>::param_info<2>
{
  using param_type = int;
  static constexpr auto GetName() { return "zone"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xA0EBC007; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

namespace StormReflFileInfo
{
  struct Matchmaker
  {
    static const int types_n = 9;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct Matchmaker::type_info<0>
  {
    using type = ::PlaylistDatabaseElement;
  };

  template <>
  struct Matchmaker::type_info<1>
  {
    using type = ::PlaylistDatabaseObj;
  };

  template <>
  struct Matchmaker::type_info<2>
  {
    using type = ::PlaylistBucketUser;
  };

  template <>
  struct Matchmaker::type_info<3>
  {
    using type = ::PlaylistBucketUserList;
  };

  template <>
  struct Matchmaker::type_info<4>
  {
    using type = ::PlaylistBucket;
  };

  template <>
  struct Matchmaker::type_info<5>
  {
    using type = ::PlaylistBucketList;
  };

  template <>
  struct Matchmaker::type_info<6>
  {
    using type = ::RefillGame;
  };

  template <>
  struct Matchmaker::type_info<7>
  {
    using type = ::RefillGameList;
  };

  template <>
  struct Matchmaker::type_info<8>
  {
    using type = ::Matchmaker;
  };

}

