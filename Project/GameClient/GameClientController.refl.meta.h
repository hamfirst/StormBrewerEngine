#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "GameClientController.refl.h"
#include "Game/GameNetworkData.refl.meta.h"
#include "Game/GameNetworkEvents.refl.meta.h"


template <>
struct StormReflTypeInfo<GameClientController>
{
  using MyBase = StormRelfEmptyBase;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "GameClientController"; }
  static constexpr auto GetNameHash() { return 0xAABB1F25; }
  static constexpr bool HasDefault() { return false; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameClientController *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x657920D0 == type_name_hash) return static_cast<StormRelfEmptyBase *>(c);
    if(0x20B281C7 == type_name_hash) return static_cast<GameSimulationEventCallbacks *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameClientController *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x657920D0 == type_name_hash) return static_cast<const StormRelfEmptyBase *>(c);
    if(0x20B281C7 == type_name_hash) return static_cast<const GameSimulationEventCallbacks *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameClientController *>(ptr);
    if(typeid(GameClientController).hash_code() == type_id_hash) return c;
    if(typeid(StormRelfEmptyBase).hash_code() == type_id_hash) return static_cast<StormRelfEmptyBase *>(c);
    if(typeid(GameSimulationEventCallbacks).hash_code() == type_id_hash) return static_cast<GameSimulationEventCallbacks *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameClientController *>(ptr);
    if(typeid(GameClientController).hash_code() == type_id_hash) return c;
    if(typeid(StormRelfEmptyBase).hash_code() == type_id_hash) return static_cast<const StormRelfEmptyBase *>(c);
    if(typeid(GameSimulationEventCallbacks).hash_code() == type_id_hash) return static_cast<const GameSimulationEventCallbacks *>(c);
    return nullptr;
  }

};

template <>
struct StormReflFuncInfo<GameClientController>
{
  using MyBase = StormRelfEmptyBase;
  static constexpr int funcs_n = 5 + StormReflFuncInfo<MyBase>::funcs_n;
  template <int N> struct func_data_static : public StormReflFuncInfo<MyBase>::func_data_static<N> {};
};

template <>
struct StormReflFuncInfo<GameClientController>::func_data_static<0 + StormReflFuncInfo<StormRelfEmptyBase>::funcs_n>
{
  using func_ptr_type = void (GameClientController::*)(const CreateEntityGlobalEvent &);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "HandleCreateEntityGlobalEvent"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x72551B58; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 0 + StormReflFuncInfo<StormRelfEmptyBase>::funcs_n; }
  static constexpr func_ptr_type GetFunctionPtr() { return &GameClientController::HandleCreateEntityGlobalEvent; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<GameClientController>::func_data_static<0 + StormReflFuncInfo<StormRelfEmptyBase>::funcs_n>::param_info<0>
{
  using param_type = const CreateEntityGlobalEvent &;
  static constexpr auto GetName() { return "ev"; }
  static constexpr auto GetType() { return "const CreateEntityGlobalEvent &"; }
  static constexpr unsigned GetNameHash() { return 0xE0355914; }
  static constexpr unsigned GetTypeNameHash() { return 0xA60BE0D8; }
};

template <>
struct StormReflFuncInfo<GameClientController>::func_data_static<1 + StormReflFuncInfo<StormRelfEmptyBase>::funcs_n>
{
  using func_ptr_type = void (GameClientController::*)(const CameraShakeEvent &);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "HandleCameraShakeEvent"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x26098FD9; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 1 + StormReflFuncInfo<StormRelfEmptyBase>::funcs_n; }
  static constexpr func_ptr_type GetFunctionPtr() { return &GameClientController::HandleCameraShakeEvent; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<GameClientController>::func_data_static<1 + StormReflFuncInfo<StormRelfEmptyBase>::funcs_n>::param_info<0>
{
  using param_type = const CameraShakeEvent &;
  static constexpr auto GetName() { return "ev"; }
  static constexpr auto GetType() { return "const CameraShakeEvent &"; }
  static constexpr unsigned GetNameHash() { return 0xE0355914; }
  static constexpr unsigned GetTypeNameHash() { return 0x9E87A74F; }
};

template <>
struct StormReflFuncInfo<GameClientController>::func_data_static<2 + StormReflFuncInfo<StormRelfEmptyBase>::funcs_n>
{
  using func_ptr_type = void (GameClientController::*)(const PlaySoundGlobalEvent &);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "HandlePlaySoundGlobalEvent"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x3AABCC55; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 2 + StormReflFuncInfo<StormRelfEmptyBase>::funcs_n; }
  static constexpr func_ptr_type GetFunctionPtr() { return &GameClientController::HandlePlaySoundGlobalEvent; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<GameClientController>::func_data_static<2 + StormReflFuncInfo<StormRelfEmptyBase>::funcs_n>::param_info<0>
{
  using param_type = const PlaySoundGlobalEvent &;
  static constexpr auto GetName() { return "ev"; }
  static constexpr auto GetType() { return "const PlaySoundGlobalEvent &"; }
  static constexpr unsigned GetNameHash() { return 0xE0355914; }
  static constexpr unsigned GetTypeNameHash() { return 0xB19FA391; }
};

template <>
struct StormReflFuncInfo<GameClientController>::func_data_static<3 + StormReflFuncInfo<StormRelfEmptyBase>::funcs_n>
{
  using func_ptr_type = void (GameClientController::*)(const PlayVfxGlobalEvent &);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "HandlePlayVfxGlobalEvent"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x1780638E; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 3 + StormReflFuncInfo<StormRelfEmptyBase>::funcs_n; }
  static constexpr func_ptr_type GetFunctionPtr() { return &GameClientController::HandlePlayVfxGlobalEvent; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<GameClientController>::func_data_static<3 + StormReflFuncInfo<StormRelfEmptyBase>::funcs_n>::param_info<0>
{
  using param_type = const PlayVfxGlobalEvent &;
  static constexpr auto GetName() { return "ev"; }
  static constexpr auto GetType() { return "const PlayVfxGlobalEvent &"; }
  static constexpr unsigned GetNameHash() { return 0xE0355914; }
  static constexpr unsigned GetTypeNameHash() { return 0x062D1694; }
};

template <>
struct StormReflFuncInfo<GameClientController>::func_data_static<4 + StormReflFuncInfo<StormRelfEmptyBase>::funcs_n>
{
  using func_ptr_type = void (GameClientController::*)(const PlaceholderServerAuthEvent &);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "HandlePlaceholderAuthEvent"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x872AEDE1; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 4 + StormReflFuncInfo<StormRelfEmptyBase>::funcs_n; }
  static constexpr func_ptr_type GetFunctionPtr() { return &GameClientController::HandlePlaceholderAuthEvent; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<GameClientController>::func_data_static<4 + StormReflFuncInfo<StormRelfEmptyBase>::funcs_n>::param_info<0>
{
  using param_type = const PlaceholderServerAuthEvent &;
  static constexpr auto GetName() { return "ev"; }
  static constexpr auto GetType() { return "const PlaceholderServerAuthEvent &"; }
  static constexpr unsigned GetNameHash() { return 0xE0355914; }
  static constexpr unsigned GetTypeNameHash() { return 0x87E001A3; }
};

namespace StormReflFileInfo
{
  struct GameClientController
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct GameClientController::type_info<0>
  {
    using type = ::GameClientController;
  };

}

