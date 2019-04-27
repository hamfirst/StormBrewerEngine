#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "ServerManager.refl.h"
#include "LobbyShared/SharedTypes.refl.meta.h"
#include "GooglePlatform.refl.meta.h"
#include "GameServerMessages.refl.meta.h"


template <>
struct StormReflTypeInfo<ServerManager>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ServerManager"; }
  static constexpr auto GetNameHash() { return 0x06A88995; }
  static constexpr bool HasDefault() { return false; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ServerManager *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ServerManager *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ServerManager *>(ptr);
    if(typeid(ServerManager).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ServerManager *>(ptr);
    if(typeid(ServerManager).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflFuncInfo<ServerManager>
{
  using MyBase = void;
  static constexpr int funcs_n = 4;
  template <int N> struct func_data_static {};
};

template <>
struct StormReflFuncInfo<ServerManager>::func_data_static<0>
{
  using func_ptr_type = void (ServerManager::*)(DDSKey, int);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "AssignGameServer"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x7391CC0F; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 0; }
  static constexpr func_ptr_type GetFunctionPtr() { return &ServerManager::AssignGameServer; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<ServerManager>::func_data_static<0>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<ServerManager>::func_data_static<0>::param_info<1>
{
  using param_type = int;
  static constexpr auto GetName() { return "zone"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xA0EBC007; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<ServerManager>::func_data_static<1>
{
  using func_ptr_type = void (ServerManager::*)(DDSKey, const GameServerInfo &, int);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "HandleServerConnected"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x4736D5D6; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 1; }
  static constexpr func_ptr_type GetFunctionPtr() { return &ServerManager::HandleServerConnected; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<ServerManager>::func_data_static<1>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "game_server_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x5A85661E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<ServerManager>::func_data_static<1>::param_info<1>
{
  using param_type = const GameServerInfo &;
  static constexpr auto GetName() { return "server_info"; }
  static constexpr auto GetType() { return "const GameServerInfo &"; }
  static constexpr unsigned GetNameHash() { return 0x400940B7; }
  static constexpr unsigned GetTypeNameHash() { return 0x118784FD; }
};

template <>
struct StormReflFuncInfo<ServerManager>::func_data_static<1>::param_info<2>
{
  using param_type = int;
  static constexpr auto GetName() { return "num_active_games"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xD7B51670; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<ServerManager>::func_data_static<2>
{
  using func_ptr_type = void (ServerManager::*)(DDSKey);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "HandleServerDisconnected"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x34A264B4; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 2; }
  static constexpr func_ptr_type GetFunctionPtr() { return &ServerManager::HandleServerDisconnected; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<ServerManager>::func_data_static<2>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "game_server_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x5A85661E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<ServerManager>::func_data_static<3>
{
  using func_ptr_type = void (ServerManager::*)(DDSKey);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "HandleGameEnded"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x33B9E361; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 3; }
  static constexpr func_ptr_type GetFunctionPtr() { return &ServerManager::HandleGameEnded; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<ServerManager>::func_data_static<3>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "game_server_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x5A85661E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

namespace StormReflFileInfo
{
  struct ServerManager
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct ServerManager::type_info<0>
  {
    using type = ::ServerManager;
  };

}

