#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "GameList.refl.h"
#include "LobbyShared/SharedTypes.refl.meta.h"


template <>
struct StormReflTypeInfo<GameList>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameList"; }
  static constexpr auto GetNameHash() { return 0x4BBD3F4F; }
  static constexpr bool HasDefault() { return false; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameList *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameList *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameList *>(ptr);
    if(typeid(GameList).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameList *>(ptr);
    if(typeid(GameList).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameList>::field_data_static<0>
{
  using member_type = RMap<DDSKey, GameListGame>; // RMap<unsigned long, GameListGame>
  static constexpr auto GetName() { return "m_GameList"; }
  static constexpr auto GetType() { return "RMap<unsigned long, GameListGame>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x44E78937; }
  static constexpr unsigned GetTypeNameHash() { return 0x01B92204; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameList::m_GameList; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameList *>(obj); return &ptr->m_GameList; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameList *>(obj); return &ptr->m_GameList; }
};

template <typename Self>
struct StormReflTypeInfo<GameList>::field_data<0, Self> : public StormReflTypeInfo<GameList>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMap<DDSKey, GameListGame>> & Get() { return self.m_GameList; }
  std::add_const_t<std::remove_reference_t<RMap<DDSKey, GameListGame>>> & Get() const { return self.m_GameList; }
};

template <>
struct StormReflTypeInfo<GameList>::field_data_static<1>
{
  using member_type = std::map<uint32_t, DDSKey>; // std::map<unsigned int, unsigned long, std::less<unsigned int>, std::allocator<std::pair<const unsigned int, unsigned long> > >
  static constexpr auto GetName() { return "m_JoinCodeLookup"; }
  static constexpr auto GetType() { return "std::map<unsigned int, unsigned long, std::less<unsigned int>, std::allocator<std::pair<const unsigned int, unsigned long> > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x36FF40C7; }
  static constexpr unsigned GetTypeNameHash() { return 0x0A2B6D7F; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameList::m_JoinCodeLookup; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameList *>(obj); return &ptr->m_JoinCodeLookup; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameList *>(obj); return &ptr->m_JoinCodeLookup; }
};

template <typename Self>
struct StormReflTypeInfo<GameList>::field_data<1, Self> : public StormReflTypeInfo<GameList>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::map<uint32_t, DDSKey>> & Get() { return self.m_JoinCodeLookup; }
  std::add_const_t<std::remove_reference_t<std::map<uint32_t, DDSKey>>> & Get() const { return self.m_JoinCodeLookup; }
};

template <>
struct StormReflFuncInfo<GameList>
{
  using MyBase = void;
  static constexpr int funcs_n = 5;
  template <int N> struct func_data_static {};
};

template <>
struct StormReflFuncInfo<GameList>::func_data_static<0>
{
  using func_ptr_type = void (GameList::*)(DDSKey, int, int, std::string, uint32_t, bool, bool);
  using return_type = void;
  static constexpr int params_n = 7;
  static constexpr auto GetName() { return "AddGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x229A7CDC; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 0; }
  static constexpr func_ptr_type GetFunctionPtr() { return &GameList::AddGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<GameList>::func_data_static<0>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "game_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x91CAB86C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<GameList>::func_data_static<0>::param_info<1>
{
  using param_type = int;
  static constexpr auto GetName() { return "cur_players"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x5BA099E8; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<GameList>::func_data_static<0>::param_info<2>
{
  using param_type = int;
  static constexpr auto GetName() { return "max_players"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xB2BD19E2; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<GameList>::func_data_static<0>::param_info<3>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "map"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x93ADAABB; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<GameList>::func_data_static<0>::param_info<4>
{
  using param_type = uint32_t;
  static constexpr auto GetName() { return "join_code"; }
  static constexpr auto GetType() { return "uint32_t"; }
  static constexpr unsigned GetNameHash() { return 0xE64D7D01; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E2AF381; }
};

template <>
struct StormReflFuncInfo<GameList>::func_data_static<0>::param_info<5>
{
  using param_type = bool;
  static constexpr auto GetName() { return "password"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetNameHash() { return 0x35C246D5; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
};

template <>
struct StormReflFuncInfo<GameList>::func_data_static<0>::param_info<6>
{
  using param_type = bool;
  static constexpr auto GetName() { return "started"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetNameHash() { return 0xB49696DA; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
};

template <>
struct StormReflFuncInfo<GameList>::func_data_static<1>
{
  using func_ptr_type = void (GameList::*)(DDSKey, int, int, std::string, bool);
  using return_type = void;
  static constexpr int params_n = 5;
  static constexpr auto GetName() { return "UpdateGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x5648F9FB; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 1; }
  static constexpr func_ptr_type GetFunctionPtr() { return &GameList::UpdateGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<GameList>::func_data_static<1>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "game_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x91CAB86C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<GameList>::func_data_static<1>::param_info<1>
{
  using param_type = int;
  static constexpr auto GetName() { return "cur_players"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x5BA099E8; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<GameList>::func_data_static<1>::param_info<2>
{
  using param_type = int;
  static constexpr auto GetName() { return "max_players"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xB2BD19E2; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<GameList>::func_data_static<1>::param_info<3>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "map"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x93ADAABB; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<GameList>::func_data_static<1>::param_info<4>
{
  using param_type = bool;
  static constexpr auto GetName() { return "started"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetNameHash() { return 0xB49696DA; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
};

template <>
struct StormReflFuncInfo<GameList>::func_data_static<2>
{
  using func_ptr_type = void (GameList::*)(DDSKey);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "RemoveGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x507B24C1; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 2; }
  static constexpr func_ptr_type GetFunctionPtr() { return &GameList::RemoveGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<GameList>::func_data_static<2>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "game_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x91CAB86C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<GameList>::func_data_static<3>
{
  using func_ptr_type = void (GameList::*)(DDSKey);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "AssignJoinCode"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xEFDDF4A1; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 3; }
  static constexpr func_ptr_type GetFunctionPtr() { return &GameList::AssignJoinCode; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<GameList>::func_data_static<3>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "game_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x91CAB86C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<GameList>::func_data_static<4>
{
  using func_ptr_type = void (GameList::*)(DDSResponder &, uint32_t, const UserGameJoinInfo &);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "LookupJoinCode"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x60BD4A51; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 4; }
  static constexpr func_ptr_type GetFunctionPtr() { return &GameList::LookupJoinCode; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<GameList>::func_data_static<4>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<GameList>::func_data_static<4>::param_info<1>
{
  using param_type = uint32_t;
  static constexpr auto GetName() { return "join_code"; }
  static constexpr auto GetType() { return "uint32_t"; }
  static constexpr unsigned GetNameHash() { return 0xE64D7D01; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E2AF381; }
};

template <>
struct StormReflFuncInfo<GameList>::func_data_static<4>::param_info<2>
{
  using param_type = const UserGameJoinInfo &;
  static constexpr auto GetName() { return "join_info"; }
  static constexpr auto GetType() { return "const UserGameJoinInfo &"; }
  static constexpr unsigned GetNameHash() { return 0x5AD17CCE; }
  static constexpr unsigned GetTypeNameHash() { return 0xEFC3F2A3; }
};

namespace StormReflFileInfo
{
  struct GameList
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct GameList::type_info<0>
  {
    using type = ::GameList;
  };

}

