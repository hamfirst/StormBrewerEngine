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
struct StormReflTypeInfo<GoToTownEvent>
{
  using MyBase = ClientNetworkEvent;
  static constexpr int fields_n = 1 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "GoToTownEvent"; }
  static constexpr auto GetNameHash() { return 0x7CCE230F; }
  static GoToTownEvent & GetDefault() { static GoToTownEvent def; return def; }
};

template <>
struct StormReflTypeInfo<GoToTownEvent>::field_data_static<0 + StormReflTypeInfo<ClientNetworkEvent>::fields_n>
{
  using member_type = uint8_t; // unsigned char
  static constexpr auto GetName() { return "m_Town"; }
  static constexpr auto GetType() { return "unsigned char"; }
  static constexpr unsigned GetFieldNameHash() { return 0x727B52BB; }
  static constexpr unsigned GetTypeNameHash() { return 0xF80DFA26; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<ClientNetworkEvent>::fields_n; }
  static constexpr auto GetMemberPtr() { return &GoToTownEvent::m_Town; }
};

template <typename Self>
struct StormReflTypeInfo<GoToTownEvent>::field_data<0 + StormReflTypeInfo<ClientNetworkEvent>::fields_n, Self> : public StormReflTypeInfo<GoToTownEvent>::field_data_static<0 + StormReflTypeInfo<ClientNetworkEvent>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint8_t> & Get() { return self.m_Town; }
  std::add_const_t<std::remove_reference_t<uint8_t>> & Get() const { return self.m_Town; }
  void SetDefault() { self.m_Town = StormReflTypeInfo<GoToTownEvent>::GetDefault().m_Town; }
};

namespace StormReflFileInfo
{
  struct GameNetworkEvents
  {
    static const int types_n = 7;
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
    using type = ::TargetNetworkEvent;
  };

  template <>
  struct GameNetworkEvents::type_info<3>
  {
    using type = ::PlaceholderTargetEvent;
  };

  template <>
  struct GameNetworkEvents::type_info<4>
  {
    using type = ::ClientNetworkEvent;
  };

  template <>
  struct GameNetworkEvents::type_info<5>
  {
    using type = ::PlaceholderClientEvent;
  };

  template <>
  struct GameNetworkEvents::type_info<6>
  {
    using type = ::GoToTownEvent;
  };

}

