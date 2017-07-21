#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "GameFullState.refl.h"
#include "Game/GameNetworkData.refl.meta.h"


template <>
struct StormReflTypeInfo<GameFullState>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameFullState"; }
  static constexpr auto GetNameHash() { return 0x0E9BE336; }
};

template <>
struct StormReflTypeInfo<GameFullState>::field_data_static<0>
{
  using member_type = ServerObjectManager; // ServerObjectManager
  static constexpr auto GetName() { return "m_ServerObjectManager"; }
  static constexpr auto GetType() { return "ServerObjectManager"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA597FEC7; }
  static constexpr unsigned GetTypeNameHash() { return 0x5CC26F4B; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameFullState::m_ServerObjectManager; }
};

template <typename Self>
struct StormReflTypeInfo<GameFullState>::field_data<0, Self> : public StormReflTypeInfo<GameFullState>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, ServerObjectManager> & Get() { return self.m_ServerObjectManager; }
  std::add_const_t<std::remove_reference_t<ServerObjectManager>> & Get() const { return self.m_ServerObjectManager; }
};

template <>
struct StormReflTypeInfo<GameFullState>::field_data_static<1>
{
  using member_type = GameInstanceData; // GameInstanceData
  static constexpr auto GetName() { return "m_GlobalData"; }
  static constexpr auto GetType() { return "GameInstanceData"; }
  static constexpr unsigned GetFieldNameHash() { return 0x4652C62B; }
  static constexpr unsigned GetTypeNameHash() { return 0xC7A440E6; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameFullState::m_GlobalData; }
};

template <typename Self>
struct StormReflTypeInfo<GameFullState>::field_data<1, Self> : public StormReflTypeInfo<GameFullState>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameInstanceData> & Get() { return self.m_GlobalData; }
  std::add_const_t<std::remove_reference_t<GameInstanceData>> & Get() const { return self.m_GlobalData; }
};

namespace StormReflFileInfo
{
  struct GameFullState
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct GameFullState::type_info<0>
  {
    using type = ::GameFullState;
  };

}

