#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "GameController.refl.h"
#include "Game/GameNetworkData.refl.meta.h"
#include "Game/GameNetworkEvents.refl.meta.h"
#include "Game/GameNetworkExternals.refl.meta.h"
#include "Game/GameFullState.refl.meta.h"


template <>
struct StormReflTypeInfo<GameController>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameController"; }
  static constexpr auto GetNameHash() { return 0x51F17D8D; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameController *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameController *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameController *>(ptr);
    if(typeid(GameController).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameController *>(ptr);
    if(typeid(GameController).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflFuncInfo<GameController>
{
  using MyBase = void;
  static constexpr int funcs_n = 3;
  template <int N> struct func_data_static {};
};

template <>
struct StormReflFuncInfo<GameController>::func_data_static<0>
{
  using func_ptr_type = void (GameController::*)(const PlaceholderClientEvent &, std::size_t, GameLogicContainer &);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "HandlePlaceholderEvent"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xB51A771F; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 0; }
  static constexpr func_ptr_type GetFunctionPtr() { return &GameController::HandlePlaceholderEvent; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<GameController>::func_data_static<0>::param_info<0>
{
  using param_type = const PlaceholderClientEvent &;
  static constexpr auto GetName() { return "ev"; }
  static constexpr auto GetType() { return "const PlaceholderClientEvent &"; }
  static constexpr unsigned GetNameHash() { return 0xE0355914; }
  static constexpr unsigned GetTypeNameHash() { return 0x57B971C6; }
};

template <>
struct StormReflFuncInfo<GameController>::func_data_static<0>::param_info<1>
{
  using param_type = size_t;
  static constexpr auto GetName() { return "player_index"; }
  static constexpr auto GetType() { return "size_t"; }
  static constexpr unsigned GetNameHash() { return 0x3F011C47; }
  static constexpr unsigned GetTypeNameHash() { return 0x8883767D; }
};

template <>
struct StormReflFuncInfo<GameController>::func_data_static<0>::param_info<2>
{
  using param_type = GameLogicContainer &;
  static constexpr auto GetName() { return "game"; }
  static constexpr auto GetType() { return "GameLogicContainer &"; }
  static constexpr unsigned GetNameHash() { return 0x232B318C; }
  static constexpr unsigned GetTypeNameHash() { return 0xBFBDFC4E; }
};

template <>
struct StormReflFuncInfo<GameController>::func_data_static<1>
{
  using func_ptr_type = void (GameController::*)(const JumpEvent &, std::size_t, GameLogicContainer &);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "HandleJumpEvent"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x03307427; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 1; }
  static constexpr func_ptr_type GetFunctionPtr() { return &GameController::HandleJumpEvent; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<GameController>::func_data_static<1>::param_info<0>
{
  using param_type = const JumpEvent &;
  static constexpr auto GetName() { return "ev"; }
  static constexpr auto GetType() { return "const JumpEvent &"; }
  static constexpr unsigned GetNameHash() { return 0xE0355914; }
  static constexpr unsigned GetTypeNameHash() { return 0x75ED4460; }
};

template <>
struct StormReflFuncInfo<GameController>::func_data_static<1>::param_info<1>
{
  using param_type = size_t;
  static constexpr auto GetName() { return "player_index"; }
  static constexpr auto GetType() { return "size_t"; }
  static constexpr unsigned GetNameHash() { return 0x3F011C47; }
  static constexpr unsigned GetTypeNameHash() { return 0x8883767D; }
};

template <>
struct StormReflFuncInfo<GameController>::func_data_static<1>::param_info<2>
{
  using param_type = GameLogicContainer &;
  static constexpr auto GetName() { return "game"; }
  static constexpr auto GetType() { return "GameLogicContainer &"; }
  static constexpr unsigned GetNameHash() { return 0x232B318C; }
  static constexpr unsigned GetTypeNameHash() { return 0xBFBDFC4E; }
};

template <>
struct StormReflFuncInfo<GameController>::func_data_static<2>
{
  using func_ptr_type = void (GameController::*)(const PlaceholderServerAuthEvent &, GameLogicContainer &);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "HandlePlaceholderAuthEvent"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x872AEDE1; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 2; }
  static constexpr func_ptr_type GetFunctionPtr() { return &GameController::HandlePlaceholderAuthEvent; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<GameController>::func_data_static<2>::param_info<0>
{
  using param_type = const PlaceholderServerAuthEvent &;
  static constexpr auto GetName() { return "ev"; }
  static constexpr auto GetType() { return "const PlaceholderServerAuthEvent &"; }
  static constexpr unsigned GetNameHash() { return 0xE0355914; }
  static constexpr unsigned GetTypeNameHash() { return 0x87E001A3; }
};

template <>
struct StormReflFuncInfo<GameController>::func_data_static<2>::param_info<1>
{
  using param_type = GameLogicContainer &;
  static constexpr auto GetName() { return "game"; }
  static constexpr auto GetType() { return "GameLogicContainer &"; }
  static constexpr unsigned GetNameHash() { return 0x232B318C; }
  static constexpr unsigned GetTypeNameHash() { return 0xBFBDFC4E; }
};

namespace StormReflFileInfo
{
  struct GameController
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct GameController::type_info<0>
  {
    using type = ::GameController;
  };

}

