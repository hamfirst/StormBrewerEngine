#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "GameNetworkEvents.refl.h"


template <>
struct StormReflTypeInfo<GlobalNetworkEvent>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GlobalNetworkEvent"; }
  static constexpr auto GetNameHash() { return 0xBD3E127B; }
  static GlobalNetworkEvent & GetDefault() { static GlobalNetworkEvent def; return def; }
};

template <>
struct StormReflTypeInfo<PlaceholderGlobalEvent>
{
  using MyBase = GlobalNetworkEvent;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "PlaceholderGlobalEvent"; }
  static constexpr auto GetNameHash() { return 0x3E75F02A; }
  static PlaceholderGlobalEvent & GetDefault() { static PlaceholderGlobalEvent def; return def; }
};

template <>
struct StormReflTypeInfo<ServerAuthNetworkEvent>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ServerAuthNetworkEvent"; }
  static constexpr auto GetNameHash() { return 0xE24857C1; }
  static ServerAuthNetworkEvent & GetDefault() { static ServerAuthNetworkEvent def; return def; }
};

template <>
struct StormReflTypeInfo<PlaceholderServerAuthEvent>
{
  using MyBase = ServerAuthNetworkEvent;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "PlaceholderServerAuthEvent"; }
  static constexpr auto GetNameHash() { return 0x29691225; }
  static PlaceholderServerAuthEvent & GetDefault() { static PlaceholderServerAuthEvent def; return def; }
};

template <>
struct StormReflTypeInfo<TargetNetworkEvent>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "TargetNetworkEvent"; }
  static constexpr auto GetNameHash() { return 0x40E708F3; }
  static TargetNetworkEvent & GetDefault() { static TargetNetworkEvent def; return def; }
};

template <>
struct StormReflTypeInfo<TargetNetworkEvent>::field_data_static<0>
{
  using member_type = NetRangedNumber<int, 0, 255>; // NetRangedNumber<int, 0, 255>
  static constexpr auto GetName() { return "m_Target"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, 0, 255>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0B507834; }
  static constexpr unsigned GetTypeNameHash() { return 0x4CE63414; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &TargetNetworkEvent::m_Target; }
};

template <typename Self>
struct StormReflTypeInfo<TargetNetworkEvent>::field_data<0, Self> : public StormReflTypeInfo<TargetNetworkEvent>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRangedNumber<int, 0, 255>> & Get() { return self.m_Target; }
  std::add_const_t<std::remove_reference_t<NetRangedNumber<int, 0, 255>>> & Get() const { return self.m_Target; }
  void SetDefault() { self.m_Target = StormReflTypeInfo<TargetNetworkEvent>::GetDefault().m_Target; }
};

template <>
struct StormReflTypeInfo<PlaceholderTargetEvent>
{
  using MyBase = TargetNetworkEvent;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "PlaceholderTargetEvent"; }
  static constexpr auto GetNameHash() { return 0xF23AD6F7; }
  static PlaceholderTargetEvent & GetDefault() { static PlaceholderTargetEvent def; return def; }
};

template <>
struct StormReflTypeInfo<ClientNetworkEvent>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ClientNetworkEvent"; }
  static constexpr auto GetNameHash() { return 0xC69662C2; }
  static ClientNetworkEvent & GetDefault() { static ClientNetworkEvent def; return def; }
};

template <>
struct StormReflTypeInfo<PlaceholderClientEvent>
{
  using MyBase = ClientNetworkEvent;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "PlaceholderClientEvent"; }
  static constexpr auto GetNameHash() { return 0xEEBE0324; }
  static PlaceholderClientEvent & GetDefault() { static PlaceholderClientEvent def; return def; }
};

template <>
struct StormReflTypeInfo<JumpEvent>
{
  using MyBase = ClientNetworkEvent;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "JumpEvent"; }
  static constexpr auto GetNameHash() { return 0x940BF099; }
  static JumpEvent & GetDefault() { static JumpEvent def; return def; }
};

namespace StormReflFileInfo
{
  struct GameNetworkEvents
  {
    static const int types_n = 9;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct GameNetworkEvents::type_info<0>
  {
    using type = ::GlobalNetworkEvent;
  };

  template <>
  struct GameNetworkEvents::type_info<1>
  {
    using type = ::PlaceholderGlobalEvent;
  };

  template <>
  struct GameNetworkEvents::type_info<2>
  {
    using type = ::ServerAuthNetworkEvent;
  };

  template <>
  struct GameNetworkEvents::type_info<3>
  {
    using type = ::PlaceholderServerAuthEvent;
  };

  template <>
  struct GameNetworkEvents::type_info<4>
  {
    using type = ::TargetNetworkEvent;
  };

  template <>
  struct GameNetworkEvents::type_info<5>
  {
    using type = ::PlaceholderTargetEvent;
  };

  template <>
  struct GameNetworkEvents::type_info<6>
  {
    using type = ::ClientNetworkEvent;
  };

  template <>
  struct GameNetworkEvents::type_info<7>
  {
    using type = ::PlaceholderClientEvent;
  };

  template <>
  struct GameNetworkEvents::type_info<8>
  {
    using type = ::JumpEvent;
  };

}

