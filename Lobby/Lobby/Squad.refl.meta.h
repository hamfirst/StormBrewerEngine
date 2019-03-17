#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "Squad.refl.h"
#include "HurricaneDDS/DDSThrottle.refl.meta.h"
#include "SharedTypes.refl.meta.h"


template <>
struct StormReflTypeInfo<SquadDatabaseMemberInfo>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "SquadDatabaseMemberInfo"; }
  static constexpr auto GetNameHash() { return 0x534C0B14; }
<<<<<<< HEAD
  static SquadDatabaseMemberInfo & GetDefault() { static SquadDatabaseMemberInfo def; return def; }
=======
  static constexpr bool HasDefault() { return true; }
  static SquadDatabaseMemberInfo & GetDefault() { static SquadDatabaseMemberInfo def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<SquadDatabaseMemberInfo *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const SquadDatabaseMemberInfo *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<SquadDatabaseMemberInfo *>(ptr);
    if(typeid(SquadDatabaseMemberInfo).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const SquadDatabaseMemberInfo *>(ptr);
    if(typeid(SquadDatabaseMemberInfo).hash_code() == type_id_hash) return c;
    return nullptr;
  }

>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <>
struct StormReflTypeInfo<SquadDatabaseMemberInfo>::field_data_static<0>
{
<<<<<<< HEAD
  using member_type = RKey; // RNumber<unsigned long long>
  static constexpr auto GetName() { return "m_UserKey"; }
  static constexpr auto GetType() { return "RNumber<unsigned long long>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE6008E39; }
  static constexpr unsigned GetTypeNameHash() { return 0x656FF0F1; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SquadDatabaseMemberInfo::m_UserKey; }
=======
  using member_type = RKey; // RNumber<unsigned long>
  static constexpr auto GetName() { return "m_UserKey"; }
  static constexpr auto GetType() { return "RNumber<unsigned long>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE6008E39; }
  static constexpr unsigned GetTypeNameHash() { return 0xFD825A3A; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SquadDatabaseMemberInfo::m_UserKey; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SquadDatabaseMemberInfo *>(obj); return &ptr->m_UserKey; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SquadDatabaseMemberInfo *>(obj); return &ptr->m_UserKey; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<SquadDatabaseMemberInfo>::field_data<0, Self> : public StormReflTypeInfo<SquadDatabaseMemberInfo>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RKey> & Get() { return self.m_UserKey; }
  std::add_const_t<std::remove_reference_t<RKey>> & Get() const { return self.m_UserKey; }
  void SetDefault() { self.m_UserKey = StormReflTypeInfo<SquadDatabaseMemberInfo>::GetDefault().m_UserKey; }
};

template <>
struct StormReflTypeInfo<SquadDatabaseMemberInfo>::field_data_static<1>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_Joined"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x18C25ECB; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &SquadDatabaseMemberInfo::m_Joined; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &SquadDatabaseMemberInfo::m_Joined; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SquadDatabaseMemberInfo *>(obj); return &ptr->m_Joined; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SquadDatabaseMemberInfo *>(obj); return &ptr->m_Joined; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<SquadDatabaseMemberInfo>::field_data<1, Self> : public StormReflTypeInfo<SquadDatabaseMemberInfo>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_Joined; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_Joined; }
  void SetDefault() { self.m_Joined = StormReflTypeInfo<SquadDatabaseMemberInfo>::GetDefault().m_Joined; }
};

template <>
struct StormReflTypeInfo<SquadDatabaseMemberInfo>::field_data_static<2>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_MembershipFlags"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5DCFBCE8; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &SquadDatabaseMemberInfo::m_MembershipFlags; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &SquadDatabaseMemberInfo::m_MembershipFlags; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SquadDatabaseMemberInfo *>(obj); return &ptr->m_MembershipFlags; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SquadDatabaseMemberInfo *>(obj); return &ptr->m_MembershipFlags; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<SquadDatabaseMemberInfo>::field_data<2, Self> : public StormReflTypeInfo<SquadDatabaseMemberInfo>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_MembershipFlags; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_MembershipFlags; }
  void SetDefault() { self.m_MembershipFlags = StormReflTypeInfo<SquadDatabaseMemberInfo>::GetDefault().m_MembershipFlags; }
};

template <>
struct StormReflTypeInfo<SquadDatabaseApplicantInfo>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "SquadDatabaseApplicantInfo"; }
  static constexpr auto GetNameHash() { return 0x94B74B6D; }
<<<<<<< HEAD
  static SquadDatabaseApplicantInfo & GetDefault() { static SquadDatabaseApplicantInfo def; return def; }
=======
  static constexpr bool HasDefault() { return true; }
  static SquadDatabaseApplicantInfo & GetDefault() { static SquadDatabaseApplicantInfo def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<SquadDatabaseApplicantInfo *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const SquadDatabaseApplicantInfo *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<SquadDatabaseApplicantInfo *>(ptr);
    if(typeid(SquadDatabaseApplicantInfo).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const SquadDatabaseApplicantInfo *>(ptr);
    if(typeid(SquadDatabaseApplicantInfo).hash_code() == type_id_hash) return c;
    return nullptr;
  }

>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <>
struct StormReflTypeInfo<SquadDatabaseApplicantInfo>::field_data_static<0>
{
<<<<<<< HEAD
  using member_type = RKey; // RNumber<unsigned long long>
  static constexpr auto GetName() { return "m_UserKey"; }
  static constexpr auto GetType() { return "RNumber<unsigned long long>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE6008E39; }
  static constexpr unsigned GetTypeNameHash() { return 0x656FF0F1; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SquadDatabaseApplicantInfo::m_UserKey; }
=======
  using member_type = RKey; // RNumber<unsigned long>
  static constexpr auto GetName() { return "m_UserKey"; }
  static constexpr auto GetType() { return "RNumber<unsigned long>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE6008E39; }
  static constexpr unsigned GetTypeNameHash() { return 0xFD825A3A; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SquadDatabaseApplicantInfo::m_UserKey; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SquadDatabaseApplicantInfo *>(obj); return &ptr->m_UserKey; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SquadDatabaseApplicantInfo *>(obj); return &ptr->m_UserKey; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<SquadDatabaseApplicantInfo>::field_data<0, Self> : public StormReflTypeInfo<SquadDatabaseApplicantInfo>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RKey> & Get() { return self.m_UserKey; }
  std::add_const_t<std::remove_reference_t<RKey>> & Get() const { return self.m_UserKey; }
  void SetDefault() { self.m_UserKey = StormReflTypeInfo<SquadDatabaseApplicantInfo>::GetDefault().m_UserKey; }
};

template <>
struct StormReflTypeInfo<SquadDatabaseInfo>
{
  using MyBase = void;
  static constexpr int fields_n = 7;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "SquadDatabaseInfo"; }
  static constexpr auto GetNameHash() { return 0x743E9D4A; }
<<<<<<< HEAD
  static SquadDatabaseInfo & GetDefault() { static SquadDatabaseInfo def; return def; }
=======
  static constexpr bool HasDefault() { return true; }
  static SquadDatabaseInfo & GetDefault() { static SquadDatabaseInfo def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<SquadDatabaseInfo *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const SquadDatabaseInfo *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<SquadDatabaseInfo *>(ptr);
    if(typeid(SquadDatabaseInfo).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const SquadDatabaseInfo *>(ptr);
    if(typeid(SquadDatabaseInfo).hash_code() == type_id_hash) return c;
    return nullptr;
  }

>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <>
struct StormReflTypeInfo<SquadDatabaseInfo>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SquadDatabaseInfo::m_Name; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SquadDatabaseInfo::m_Name; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SquadDatabaseInfo *>(obj); return &ptr->m_Name; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SquadDatabaseInfo *>(obj); return &ptr->m_Name; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<SquadDatabaseInfo>::field_data<0, Self> : public StormReflTypeInfo<SquadDatabaseInfo>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<SquadDatabaseInfo>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<SquadDatabaseInfo>::field_data_static<1>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Tag"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF06B7364; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &SquadDatabaseInfo::m_Tag; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &SquadDatabaseInfo::m_Tag; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SquadDatabaseInfo *>(obj); return &ptr->m_Tag; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SquadDatabaseInfo *>(obj); return &ptr->m_Tag; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<SquadDatabaseInfo>::field_data<1, Self> : public StormReflTypeInfo<SquadDatabaseInfo>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Tag; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Tag; }
  void SetDefault() { self.m_Tag = StormReflTypeInfo<SquadDatabaseInfo>::GetDefault().m_Tag; }
};

template <>
struct StormReflTypeInfo<SquadDatabaseInfo>::field_data_static<2>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Motd"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x9492F073; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &SquadDatabaseInfo::m_Motd; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &SquadDatabaseInfo::m_Motd; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SquadDatabaseInfo *>(obj); return &ptr->m_Motd; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SquadDatabaseInfo *>(obj); return &ptr->m_Motd; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<SquadDatabaseInfo>::field_data<2, Self> : public StormReflTypeInfo<SquadDatabaseInfo>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Motd; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Motd; }
  void SetDefault() { self.m_Motd = StormReflTypeInfo<SquadDatabaseInfo>::GetDefault().m_Motd; }
};

template <>
struct StormReflTypeInfo<SquadDatabaseInfo>::field_data_static<3>
{
  using member_type = RBool; // RBool
  static constexpr auto GetName() { return "m_Locked"; }
  static constexpr auto GetType() { return "RBool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA7ED9F59; }
  static constexpr unsigned GetTypeNameHash() { return 0x50062D06; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &SquadDatabaseInfo::m_Locked; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &SquadDatabaseInfo::m_Locked; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SquadDatabaseInfo *>(obj); return &ptr->m_Locked; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SquadDatabaseInfo *>(obj); return &ptr->m_Locked; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<SquadDatabaseInfo>::field_data<3, Self> : public StormReflTypeInfo<SquadDatabaseInfo>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RBool> & Get() { return self.m_Locked; }
  std::add_const_t<std::remove_reference_t<RBool>> & Get() const { return self.m_Locked; }
  void SetDefault() { self.m_Locked = StormReflTypeInfo<SquadDatabaseInfo>::GetDefault().m_Locked; }
};

template <>
struct StormReflTypeInfo<SquadDatabaseInfo>::field_data_static<4>
{
  using member_type = RMergeList<SquadDatabaseMemberInfo>; // RMergeList<SquadDatabaseMemberInfo>
  static constexpr auto GetName() { return "m_Users"; }
  static constexpr auto GetType() { return "RMergeList<SquadDatabaseMemberInfo>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x99B53589; }
  static constexpr unsigned GetTypeNameHash() { return 0x667A425A; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &SquadDatabaseInfo::m_Users; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &SquadDatabaseInfo::m_Users; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SquadDatabaseInfo *>(obj); return &ptr->m_Users; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SquadDatabaseInfo *>(obj); return &ptr->m_Users; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<SquadDatabaseInfo>::field_data<4, Self> : public StormReflTypeInfo<SquadDatabaseInfo>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<SquadDatabaseMemberInfo>> & Get() { return self.m_Users; }
  std::add_const_t<std::remove_reference_t<RMergeList<SquadDatabaseMemberInfo>>> & Get() const { return self.m_Users; }
  void SetDefault() { self.m_Users = StormReflTypeInfo<SquadDatabaseInfo>::GetDefault().m_Users; }
};

template <>
struct StormReflTypeInfo<SquadDatabaseInfo>::field_data_static<5>
{
  using member_type = RMergeList<SquadDatabaseApplicantInfo>; // RMergeList<SquadDatabaseApplicantInfo>
  static constexpr auto GetName() { return "m_Applications"; }
  static constexpr auto GetType() { return "RMergeList<SquadDatabaseApplicantInfo>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x504B1F96; }
  static constexpr unsigned GetTypeNameHash() { return 0x8031E0DF; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &SquadDatabaseInfo::m_Applications; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &SquadDatabaseInfo::m_Applications; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SquadDatabaseInfo *>(obj); return &ptr->m_Applications; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SquadDatabaseInfo *>(obj); return &ptr->m_Applications; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<SquadDatabaseInfo>::field_data<5, Self> : public StormReflTypeInfo<SquadDatabaseInfo>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<SquadDatabaseApplicantInfo>> & Get() { return self.m_Applications; }
  std::add_const_t<std::remove_reference_t<RMergeList<SquadDatabaseApplicantInfo>>> & Get() const { return self.m_Applications; }
  void SetDefault() { self.m_Applications = StormReflTypeInfo<SquadDatabaseInfo>::GetDefault().m_Applications; }
};

template <>
struct StormReflTypeInfo<SquadDatabaseInfo>::field_data_static<6>
{
  using member_type = RMergeList<SquadDatabaseApplicantInfo>; // RMergeList<SquadDatabaseApplicantInfo>
  static constexpr auto GetName() { return "m_Requests"; }
  static constexpr auto GetType() { return "RMergeList<SquadDatabaseApplicantInfo>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8DA9027F; }
  static constexpr unsigned GetTypeNameHash() { return 0x8031E0DF; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &SquadDatabaseInfo::m_Requests; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &SquadDatabaseInfo::m_Requests; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SquadDatabaseInfo *>(obj); return &ptr->m_Requests; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SquadDatabaseInfo *>(obj); return &ptr->m_Requests; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<SquadDatabaseInfo>::field_data<6, Self> : public StormReflTypeInfo<SquadDatabaseInfo>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<SquadDatabaseApplicantInfo>> & Get() { return self.m_Requests; }
  std::add_const_t<std::remove_reference_t<RMergeList<SquadDatabaseApplicantInfo>>> & Get() const { return self.m_Requests; }
  void SetDefault() { self.m_Requests = StormReflTypeInfo<SquadDatabaseInfo>::GetDefault().m_Requests; }
};

template <>
struct StormReflTypeInfo<SquadDatabaseObject>
{
  using MyBase = void;
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "SquadDatabaseObject"; }
  static constexpr auto GetNameHash() { return 0x88A19784; }
<<<<<<< HEAD
  static SquadDatabaseObject & GetDefault() { static SquadDatabaseObject def; return def; }
=======
  static constexpr bool HasDefault() { return true; }
  static SquadDatabaseObject & GetDefault() { static SquadDatabaseObject def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<SquadDatabaseObject *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const SquadDatabaseObject *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<SquadDatabaseObject *>(ptr);
    if(typeid(SquadDatabaseObject).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const SquadDatabaseObject *>(ptr);
    if(typeid(SquadDatabaseObject).hash_code() == type_id_hash) return c;
    return nullptr;
  }

>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <>
struct StormReflTypeInfo<SquadDatabaseObject>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_SquadNameLower"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x7E269B33; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SquadDatabaseObject::m_SquadNameLower; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SquadDatabaseObject::m_SquadNameLower; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SquadDatabaseObject *>(obj); return &ptr->m_SquadNameLower; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SquadDatabaseObject *>(obj); return &ptr->m_SquadNameLower; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<SquadDatabaseObject>::field_data<0, Self> : public StormReflTypeInfo<SquadDatabaseObject>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_SquadNameLower; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_SquadNameLower; }
  void SetDefault() { self.m_SquadNameLower = StormReflTypeInfo<SquadDatabaseObject>::GetDefault().m_SquadNameLower; }
};

template <>
struct StormReflTypeInfo<SquadDatabaseObject>::annotations<0>
{
  static constexpr int annotations_n = 1;
  template <int A> struct annoation { };
};

template <>
struct StormReflTypeInfo<SquadDatabaseObject>::annotations<0>::annoation<0>
{
  static constexpr const char * GetAnnotation() { return "UniqueIndex"; }
  static constexpr uint32_t GetAnnotationHash() { return 0x5C838CC5; }
};

template <>
struct StormReflTypeInfo<SquadDatabaseObject>::field_data_static<1>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_SquadTagLower"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x4329BAA5; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &SquadDatabaseObject::m_SquadTagLower; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &SquadDatabaseObject::m_SquadTagLower; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SquadDatabaseObject *>(obj); return &ptr->m_SquadTagLower; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SquadDatabaseObject *>(obj); return &ptr->m_SquadTagLower; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<SquadDatabaseObject>::field_data<1, Self> : public StormReflTypeInfo<SquadDatabaseObject>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_SquadTagLower; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_SquadTagLower; }
  void SetDefault() { self.m_SquadTagLower = StormReflTypeInfo<SquadDatabaseObject>::GetDefault().m_SquadTagLower; }
};

template <>
struct StormReflTypeInfo<SquadDatabaseObject>::annotations<1>
{
  static constexpr int annotations_n = 1;
  template <int A> struct annoation { };
};

template <>
struct StormReflTypeInfo<SquadDatabaseObject>::annotations<1>::annoation<0>
{
  static constexpr const char * GetAnnotation() { return "UniqueIndex"; }
  static constexpr uint32_t GetAnnotationHash() { return 0x5C838CC5; }
};

template <>
struct StormReflTypeInfo<SquadDatabaseObject>::field_data_static<2>
{
<<<<<<< HEAD
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_Creator"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x29F49FB6; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &SquadDatabaseObject::m_Creator; }
=======
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_Creator"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x29F49FB6; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &SquadDatabaseObject::m_Creator; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SquadDatabaseObject *>(obj); return &ptr->m_Creator; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SquadDatabaseObject *>(obj); return &ptr->m_Creator; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<SquadDatabaseObject>::field_data<2, Self> : public StormReflTypeInfo<SquadDatabaseObject>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_Creator; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_Creator; }
  void SetDefault() { self.m_Creator = StormReflTypeInfo<SquadDatabaseObject>::GetDefault().m_Creator; }
};

template <>
struct StormReflTypeInfo<SquadDatabaseObject>::field_data_static<3>
{
  using member_type = SquadDatabaseInfo; // SquadDatabaseInfo
  static constexpr auto GetName() { return "m_DatabaseInfo"; }
  static constexpr auto GetType() { return "SquadDatabaseInfo"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFB773733; }
  static constexpr unsigned GetTypeNameHash() { return 0x743E9D4A; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &SquadDatabaseObject::m_DatabaseInfo; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &SquadDatabaseObject::m_DatabaseInfo; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SquadDatabaseObject *>(obj); return &ptr->m_DatabaseInfo; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SquadDatabaseObject *>(obj); return &ptr->m_DatabaseInfo; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<SquadDatabaseObject>::field_data<3, Self> : public StormReflTypeInfo<SquadDatabaseObject>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, SquadDatabaseInfo> & Get() { return self.m_DatabaseInfo; }
  std::add_const_t<std::remove_reference_t<SquadDatabaseInfo>> & Get() const { return self.m_DatabaseInfo; }
  void SetDefault() { self.m_DatabaseInfo = StormReflTypeInfo<SquadDatabaseObject>::GetDefault().m_DatabaseInfo; }
};

template <>
struct StormReflTypeInfo<Squad>
{
  using MyBase = void;
  static constexpr int fields_n = 5;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "Squad"; }
  static constexpr auto GetNameHash() { return 0x0E11D0E3; }
<<<<<<< HEAD
=======
  static constexpr bool HasDefault() { return false; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<Squad *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const Squad *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<Squad *>(ptr);
    if(typeid(Squad).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const Squad *>(ptr);
    if(typeid(Squad).hash_code() == type_id_hash) return c;
    return nullptr;
  }

>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <>
struct StormReflTypeInfo<Squad>::field_data_static<0>
{
  using member_type = DDSThrottle; // DDSThrottle
  static constexpr auto GetName() { return "m_ChangeThrottle"; }
  static constexpr auto GetType() { return "DDSThrottle"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8C9BCB55; }
  static constexpr unsigned GetTypeNameHash() { return 0xA610F43B; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &Squad::m_ChangeThrottle; }
=======
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &Squad::m_ChangeThrottle; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<Squad *>(obj); return &ptr->m_ChangeThrottle; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const Squad *>(obj); return &ptr->m_ChangeThrottle; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<Squad>::field_data<0, Self> : public StormReflTypeInfo<Squad>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSThrottle> & Get() { return self.m_ChangeThrottle; }
  std::add_const_t<std::remove_reference_t<DDSThrottle>> & Get() const { return self.m_ChangeThrottle; }
};

template <>
struct StormReflTypeInfo<Squad>::field_data_static<1>
{
  using member_type = SquadInfo; // SquadInfo
  static constexpr auto GetName() { return "m_SquadInfo"; }
  static constexpr auto GetType() { return "SquadInfo"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC848E820; }
  static constexpr unsigned GetTypeNameHash() { return 0x96994B98; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &Squad::m_SquadInfo; }
=======
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &Squad::m_SquadInfo; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<Squad *>(obj); return &ptr->m_SquadInfo; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const Squad *>(obj); return &ptr->m_SquadInfo; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<Squad>::field_data<1, Self> : public StormReflTypeInfo<Squad>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, SquadInfo> & Get() { return self.m_SquadInfo; }
  std::add_const_t<std::remove_reference_t<SquadInfo>> & Get() const { return self.m_SquadInfo; }
};

template <>
struct StormReflTypeInfo<Squad>::field_data_static<2>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_PendingMemberLoads"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x36BF2BC9; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &Squad::m_PendingMemberLoads; }
=======
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &Squad::m_PendingMemberLoads; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<Squad *>(obj); return &ptr->m_PendingMemberLoads; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const Squad *>(obj); return &ptr->m_PendingMemberLoads; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<Squad>::field_data<2, Self> : public StormReflTypeInfo<Squad>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_PendingMemberLoads; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_PendingMemberLoads; }
};

template <>
struct StormReflTypeInfo<Squad>::field_data_static<3>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_PendingApplicationLoads"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0643EE38; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &Squad::m_PendingApplicationLoads; }
=======
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &Squad::m_PendingApplicationLoads; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<Squad *>(obj); return &ptr->m_PendingApplicationLoads; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const Squad *>(obj); return &ptr->m_PendingApplicationLoads; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<Squad>::field_data<3, Self> : public StormReflTypeInfo<Squad>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_PendingApplicationLoads; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_PendingApplicationLoads; }
};

template <>
struct StormReflTypeInfo<Squad>::field_data_static<4>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_PendingRequestLoads"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5997DC89; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &Squad::m_PendingRequestLoads; }
=======
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &Squad::m_PendingRequestLoads; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<Squad *>(obj); return &ptr->m_PendingRequestLoads; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const Squad *>(obj); return &ptr->m_PendingRequestLoads; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<Squad>::field_data<4, Self> : public StormReflTypeInfo<Squad>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_PendingRequestLoads; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_PendingRequestLoads; }
};

template <>
struct StormReflFuncInfo<Squad>
{
<<<<<<< HEAD
=======
  using MyBase = void;
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
  static constexpr int funcs_n = 21;
  template <int N> struct func_data_static {};
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<0>
{
  using func_ptr_type = void (Squad::*)(DDSResponder &, DDSKey, std::string);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "ApplyToSquad"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x373B4545; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 0; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Squad::ApplyToSquad; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<0>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<0>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xA76ED395; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<0>::param_info<2>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "user_name"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x24A232CF; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<1>
{
  using func_ptr_type = void (Squad::*)(DDSResponder &, DDSKey, DDSKey);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "AcceptApplicationToSquad"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xB60F6913; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 1; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Squad::AcceptApplicationToSquad; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<1>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<1>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_source"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x3AD8644E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<1>::param_info<2>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xA76ED395; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<2>
{
  using func_ptr_type = void (Squad::*)(DDSResponder &, DDSKey, DDSKey);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "DeclineApplicationToSquad"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xFD4E5206; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 2; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Squad::DeclineApplicationToSquad; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<2>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<2>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_source"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x3AD8644E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<2>::param_info<2>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xA76ED395; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<3>
{
  using func_ptr_type = void (Squad::*)(DDSResponder &, DDSKey);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "RescindApplicationToSquad"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xC488079A; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 3; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Squad::RescindApplicationToSquad; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<3>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<3>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xA76ED395; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<4>
{
  using func_ptr_type = void (Squad::*)(DDSResponder &, DDSKey, DDSKey, std::string);
  using return_type = void;
  static constexpr int params_n = 4;
  static constexpr auto GetName() { return "RequestUserToJoinSquad"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x66C141F0; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 4; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Squad::RequestUserToJoinSquad; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<4>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<4>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_source"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x3AD8644E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<4>::param_info<2>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xA76ED395; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<4>::param_info<3>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "user_name"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x24A232CF; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<5>
{
  using func_ptr_type = void (Squad::*)(DDSResponder &, DDSKey);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "AcceptRequestToJoinSquad"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x8A4206E7; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 5; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Squad::AcceptRequestToJoinSquad; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<5>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<5>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xA76ED395; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<6>
{
  using func_ptr_type = void (Squad::*)(DDSResponder &, DDSKey);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "DeclineRequestToJoinSquad"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xC1033DF2; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 6; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Squad::DeclineRequestToJoinSquad; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<6>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<6>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xA76ED395; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<7>
{
  using func_ptr_type = void (Squad::*)(DDSResponder &, DDSKey, DDSKey);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "RescindRequestToJoinSquad"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xF8C5686E; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 7; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Squad::RescindRequestToJoinSquad; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<7>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<7>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_source"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x3AD8644E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<7>::param_info<2>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xA76ED395; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<8>
{
  using func_ptr_type = void (Squad::*)(DDSResponder &, DDSKey);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "LeaveSquad"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x720BB790; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 8; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Squad::LeaveSquad; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<8>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<8>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xA76ED395; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<9>
{
  using func_ptr_type = void (Squad::*)(DDSResponder &, DDSKey, DDSKey);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "RemoveMember"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x58EE5C8B; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 9; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Squad::RemoveMember; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<9>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<9>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_source"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x3AD8644E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<9>::param_info<2>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xA76ED395; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<10>
{
  using func_ptr_type = void (Squad::*)(DDSResponder &, DDSKey, DDSKey, int);
  using return_type = void;
  static constexpr int params_n = 4;
  static constexpr auto GetName() { return "SetMemberPermissions"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x26BCE7D2; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 10; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Squad::SetMemberPermissions; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<10>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<10>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_source"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x3AD8644E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<10>::param_info<2>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xA76ED395; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<10>::param_info<3>
{
  using param_type = int;
  static constexpr auto GetName() { return "member_permissions"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xF4D0D8AD; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<11>
{
  using func_ptr_type = void (Squad::*)(DDSResponder &, DDSKey, std::string);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "SetMotd"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xF043E1FC; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 11; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Squad::SetMotd; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<11>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<11>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_source"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x3AD8644E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<11>::param_info<2>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "motd"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xAA0F656C; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<12>
{
  using func_ptr_type = void (Squad::*)(DDSResponder &, DDSKey, bool);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "SetChannelLock"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x64298072; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 12; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Squad::SetChannelLock; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<12>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<12>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_source"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x3AD8644E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<12>::param_info<2>
{
  using param_type = bool;
  static constexpr auto GetName() { return "locked"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetNameHash() { return 0xEAD2C891; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<13>
{
  using func_ptr_type = void (Squad::*)(DDSResponder &);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "GetSquadName"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x043597EF; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 13; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Squad::GetSquadName; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<13>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<14>
{
  using func_ptr_type = void (Squad::*)(DDSResponder &);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "KillSquad"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x8E79FCAA; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 14; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Squad::KillSquad; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<14>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<15>
{
  using func_ptr_type = void (Squad::*)();
  using return_type = void;
  static constexpr int params_n = 0;
  static constexpr auto GetName() { return "DestroySquad"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xAE970DCE; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 15; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Squad::DestroySquad; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<16>
{
  using func_ptr_type = void (Squad::*)(int, std::string);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "HandleMemberLoad"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x9AE8D45D; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 16; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Squad::HandleMemberLoad; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<16>::param_info<0>
{
  using param_type = int;
  static constexpr auto GetName() { return "member_index"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xE252F2F2; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<16>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "name"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x5E237E06; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<17>
{
  using func_ptr_type = void (Squad::*)(int, std::string);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "HandleApplicationLoad"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x75750C51; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 17; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Squad::HandleApplicationLoad; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<17>::param_info<0>
{
  using param_type = int;
  static constexpr auto GetName() { return "member_index"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xE252F2F2; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<17>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "name"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x5E237E06; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<18>
{
  using func_ptr_type = void (Squad::*)(int, std::string);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "HandleRequestLoad"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x137ACF76; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 18; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Squad::HandleRequestLoad; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<18>::param_info<0>
{
  using param_type = int;
  static constexpr auto GetName() { return "member_index"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xE252F2F2; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<18>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "name"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x5E237E06; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<19>
{
  using func_ptr_type = void (Squad::*)(std::string);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "UpdateMotd"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xDF6CAD1B; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 19; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Squad::UpdateMotd; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<19>::param_info<0>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "motd"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xAA0F656C; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<20>
{
  using func_ptr_type = void (Squad::*)(DDSResponder &);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "GetInfo"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x02540D1A; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 20; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Squad::GetInfo; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Squad>::func_data_static<20>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

namespace StormReflFileInfo
{
  struct Squad
  {
    static const int types_n = 5;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct Squad::type_info<0>
  {
    using type = ::SquadDatabaseMemberInfo;
  };

  template <>
  struct Squad::type_info<1>
  {
    using type = ::SquadDatabaseApplicantInfo;
  };

  template <>
  struct Squad::type_info<2>
  {
    using type = ::SquadDatabaseInfo;
  };

  template <>
  struct Squad::type_info<3>
  {
    using type = ::SquadDatabaseObject;
  };

  template <>
  struct Squad::type_info<4>
  {
    using type = ::Squad;
  };

}

