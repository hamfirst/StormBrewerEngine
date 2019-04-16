#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "GameList.refl.h"


template <>
struct StormReflTypeInfo<GameListGame>
{
  using MyBase = void;
  static constexpr int fields_n = 6;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameListGame"; }
  static constexpr auto GetNameHash() { return 0xDF3C3C99; }
  static constexpr bool HasDefault() { return true; }
  static GameListGame & GetDefault() { static GameListGame def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameListGame *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameListGame *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameListGame *>(ptr);
    if(typeid(GameListGame).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameListGame *>(ptr);
    if(typeid(GameListGame).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameListGame>::field_data_static<0>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_MaxPlayers"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0D18B4FD; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameListGame::m_MaxPlayers; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameListGame *>(obj); return &ptr->m_MaxPlayers; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameListGame *>(obj); return &ptr->m_MaxPlayers; }
};

template <typename Self>
struct StormReflTypeInfo<GameListGame>::field_data<0, Self> : public StormReflTypeInfo<GameListGame>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_MaxPlayers; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_MaxPlayers; }
  void SetDefault() { self.m_MaxPlayers = StormReflTypeInfo<GameListGame>::GetDefault().m_MaxPlayers; }
};

template <>
struct StormReflTypeInfo<GameListGame>::field_data_static<1>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_CurPlayers"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x733D8BFB; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameListGame::m_CurPlayers; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameListGame *>(obj); return &ptr->m_CurPlayers; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameListGame *>(obj); return &ptr->m_CurPlayers; }
};

template <typename Self>
struct StormReflTypeInfo<GameListGame>::field_data<1, Self> : public StormReflTypeInfo<GameListGame>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_CurPlayers; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_CurPlayers; }
  void SetDefault() { self.m_CurPlayers = StormReflTypeInfo<GameListGame>::GetDefault().m_CurPlayers; }
};

template <>
struct StormReflTypeInfo<GameListGame>::field_data_static<2>
{
  using member_type = RBool; // RBool
  static constexpr auto GetName() { return "m_PasswordProtected"; }
  static constexpr auto GetType() { return "RBool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x536AB58A; }
  static constexpr unsigned GetTypeNameHash() { return 0x50062D06; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GameListGame::m_PasswordProtected; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameListGame *>(obj); return &ptr->m_PasswordProtected; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameListGame *>(obj); return &ptr->m_PasswordProtected; }
};

template <typename Self>
struct StormReflTypeInfo<GameListGame>::field_data<2, Self> : public StormReflTypeInfo<GameListGame>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RBool> & Get() { return self.m_PasswordProtected; }
  std::add_const_t<std::remove_reference_t<RBool>> & Get() const { return self.m_PasswordProtected; }
  void SetDefault() { self.m_PasswordProtected = StormReflTypeInfo<GameListGame>::GetDefault().m_PasswordProtected; }
};

template <>
struct StormReflTypeInfo<GameListGame>::field_data_static<3>
{
  using member_type = RBool; // RBool
  static constexpr auto GetName() { return "m_Started"; }
  static constexpr auto GetType() { return "RBool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2164E30F; }
  static constexpr unsigned GetTypeNameHash() { return 0x50062D06; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &GameListGame::m_Started; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameListGame *>(obj); return &ptr->m_Started; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameListGame *>(obj); return &ptr->m_Started; }
};

template <typename Self>
struct StormReflTypeInfo<GameListGame>::field_data<3, Self> : public StormReflTypeInfo<GameListGame>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RBool> & Get() { return self.m_Started; }
  std::add_const_t<std::remove_reference_t<RBool>> & Get() const { return self.m_Started; }
  void SetDefault() { self.m_Started = StormReflTypeInfo<GameListGame>::GetDefault().m_Started; }
};

template <>
struct StormReflTypeInfo<GameListGame>::field_data_static<4>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Map"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x604F6E5C; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &GameListGame::m_Map; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameListGame *>(obj); return &ptr->m_Map; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameListGame *>(obj); return &ptr->m_Map; }
};

template <typename Self>
struct StormReflTypeInfo<GameListGame>::field_data<4, Self> : public StormReflTypeInfo<GameListGame>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Map; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Map; }
  void SetDefault() { self.m_Map = StormReflTypeInfo<GameListGame>::GetDefault().m_Map; }
};

template <>
struct StormReflTypeInfo<GameListGame>::field_data_static<5>
{
  using member_type = RUInt; // RNumber<unsigned int>
  static constexpr auto GetName() { return "m_JoinCode"; }
  static constexpr auto GetType() { return "RNumber<unsigned int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x50415C3C; }
  static constexpr unsigned GetTypeNameHash() { return 0x7B4FB98C; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &GameListGame::m_JoinCode; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameListGame *>(obj); return &ptr->m_JoinCode; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameListGame *>(obj); return &ptr->m_JoinCode; }
};

template <typename Self>
struct StormReflTypeInfo<GameListGame>::field_data<5, Self> : public StormReflTypeInfo<GameListGame>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RUInt> & Get() { return self.m_JoinCode; }
  std::add_const_t<std::remove_reference_t<RUInt>> & Get() const { return self.m_JoinCode; }
  void SetDefault() { self.m_JoinCode = StormReflTypeInfo<GameListGame>::GetDefault().m_JoinCode; }
};

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
  static constexpr int funcs_n = 4;
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

namespace StormReflFileInfo
{
  struct GameList
  {
    static const int types_n = 2;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct GameList::type_info<0>
  {
    using type = ::GameListGame;
  };

  template <>
  struct GameList::type_info<1>
  {
    using type = ::GameList;
  };

}

