#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "GameClientSaveFileData.refl.h"


template <>
struct StormReflTypeInfo<GameClientSaveData>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameClientSaveData"; }
  static constexpr auto GetNameHash() { return 0x80854010; }
  static GameClientSaveData & GetDefault() { static GameClientSaveData def; return def; }
};

template <>
struct StormReflTypeInfo<GameClientSaveData>::field_data_static<0>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_WatchedTutorial"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x49A5AD55; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameClientSaveData::m_WatchedTutorial; }
};

template <typename Self>
struct StormReflTypeInfo<GameClientSaveData>::field_data<0, Self> : public StormReflTypeInfo<GameClientSaveData>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_WatchedTutorial; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_WatchedTutorial; }
  void SetDefault() { self.m_WatchedTutorial = StormReflTypeInfo<GameClientSaveData>::GetDefault().m_WatchedTutorial; }
};

namespace StormReflFileInfo
{
  struct GameClientSaveFileData
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct GameClientSaveFileData::type_info<0>
  {
    using type = ::GameClientSaveData;
  };

}

