#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "Rewards.refl.h"
#include "GameData.refl.meta.h"


template <>
struct StormReflTypeInfo<RewardsRank>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "RewardsRank"; }
  static constexpr auto GetNameHash() { return 0xABF79A92; }
  static constexpr bool HasDefault() { return true; }
  static RewardsRank & GetDefault() { static RewardsRank def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<RewardsRank *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const RewardsRank *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<RewardsRank *>(ptr);
    if(typeid(RewardsRank).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const RewardsRank *>(ptr);
    if(typeid(RewardsRank).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<RewardsRank>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_XP"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x96E11FE7; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &RewardsRank::m_XP; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<RewardsRank *>(obj); return &ptr->m_XP; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const RewardsRank *>(obj); return &ptr->m_XP; }
};

template <typename Self>
struct StormReflTypeInfo<RewardsRank>::field_data<0, Self> : public StormReflTypeInfo<RewardsRank>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_XP; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_XP; }
  void SetDefault() { self.m_XP = StormReflTypeInfo<RewardsRank>::GetDefault().m_XP; }
};

template <>
struct StormReflTypeInfo<RewardsRank>::field_data_static<1>
{
  using member_type = UserRewards; // UserRewards
  static constexpr auto GetName() { return "m_Rewards"; }
  static constexpr auto GetType() { return "UserRewards"; }
  static constexpr unsigned GetFieldNameHash() { return 0x7CD06BE2; }
  static constexpr unsigned GetTypeNameHash() { return 0x3C6254C2; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &RewardsRank::m_Rewards; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<RewardsRank *>(obj); return &ptr->m_Rewards; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const RewardsRank *>(obj); return &ptr->m_Rewards; }
};

template <typename Self>
struct StormReflTypeInfo<RewardsRank>::field_data<1, Self> : public StormReflTypeInfo<RewardsRank>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, UserRewards> & Get() { return self.m_Rewards; }
  std::add_const_t<std::remove_reference_t<UserRewards>> & Get() const { return self.m_Rewards; }
  void SetDefault() { self.m_Rewards = StormReflTypeInfo<RewardsRank>::GetDefault().m_Rewards; }
};

template <>
struct StormReflTypeInfo<RewardsDatabaseObj>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "RewardsDatabaseObj"; }
  static constexpr auto GetNameHash() { return 0x3BB4122B; }
  static constexpr bool HasDefault() { return true; }
  static RewardsDatabaseObj & GetDefault() { static RewardsDatabaseObj def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<RewardsDatabaseObj *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const RewardsDatabaseObj *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<RewardsDatabaseObj *>(ptr);
    if(typeid(RewardsDatabaseObj).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const RewardsDatabaseObj *>(ptr);
    if(typeid(RewardsDatabaseObj).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<RewardsDatabaseObj>::field_data_static<0>
{
  using member_type = std::vector<RewardsRank>; // std::vector<RewardsRank, std::allocator<RewardsRank> >
  static constexpr auto GetName() { return "m_Ranks"; }
  static constexpr auto GetType() { return "std::vector<RewardsRank, std::allocator<RewardsRank> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x46D03074; }
  static constexpr unsigned GetTypeNameHash() { return 0xC502B46C; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &RewardsDatabaseObj::m_Ranks; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<RewardsDatabaseObj *>(obj); return &ptr->m_Ranks; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const RewardsDatabaseObj *>(obj); return &ptr->m_Ranks; }
};

template <typename Self>
struct StormReflTypeInfo<RewardsDatabaseObj>::field_data<0, Self> : public StormReflTypeInfo<RewardsDatabaseObj>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<RewardsRank>> & Get() { return self.m_Ranks; }
  std::add_const_t<std::remove_reference_t<std::vector<RewardsRank>>> & Get() const { return self.m_Ranks; }
  void SetDefault() { self.m_Ranks = StormReflTypeInfo<RewardsDatabaseObj>::GetDefault().m_Ranks; }
};

template <>
struct StormReflTypeInfo<Rewards>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "Rewards"; }
  static constexpr auto GetNameHash() { return 0x269F27AB; }
  static constexpr bool HasDefault() { return false; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<Rewards *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const Rewards *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<Rewards *>(ptr);
    if(typeid(Rewards).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const Rewards *>(ptr);
    if(typeid(Rewards).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<Rewards>::field_data_static<0>
{
  using member_type = RewardsDatabaseObj; // RewardsDatabaseObj
  static constexpr auto GetName() { return "m_Info"; }
  static constexpr auto GetType() { return "RewardsDatabaseObj"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF514A448; }
  static constexpr unsigned GetTypeNameHash() { return 0x3BB4122B; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &Rewards::m_Info; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<Rewards *>(obj); return &ptr->m_Info; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const Rewards *>(obj); return &ptr->m_Info; }
};

template <typename Self>
struct StormReflTypeInfo<Rewards>::field_data<0, Self> : public StormReflTypeInfo<Rewards>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RewardsDatabaseObj> & Get() { return self.m_Info; }
  std::add_const_t<std::remove_reference_t<RewardsDatabaseObj>> & Get() const { return self.m_Info; }
};

template <>
struct StormReflFuncInfo<Rewards>
{
  using MyBase = void;
  static constexpr int funcs_n = 0;
  template <int N> struct func_data_static {};
};

namespace StormReflFileInfo
{
  struct Rewards
  {
    static const int types_n = 3;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct Rewards::type_info<0>
  {
    using type = ::RewardsRank;
  };

  template <>
  struct Rewards::type_info<1>
  {
    using type = ::RewardsDatabaseObj;
  };

  template <>
  struct Rewards::type_info<2>
  {
    using type = ::Rewards;
  };

}

