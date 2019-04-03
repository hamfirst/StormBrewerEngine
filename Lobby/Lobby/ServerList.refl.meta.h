#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "ServerList.refl.h"


template <>
struct StormReflTypeInfo<ServerListGame>
{
  using MyBase = void;
  static constexpr int fields_n = 7;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ServerListGame"; }
  static constexpr auto GetNameHash() { return 0xEDD5FB2A; }
  static constexpr bool HasDefault() { return true; }
  static ServerListGame & GetDefault() { static ServerListGame def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ServerListGame *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ServerListGame *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ServerListGame *>(ptr);
    if(typeid(ServerListGame).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ServerListGame *>(ptr);
    if(typeid(ServerListGame).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ServerListGame>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_MaxPlayers"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0D18B4FD; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &ServerListGame::m_MaxPlayers; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ServerListGame *>(obj); return &ptr->m_MaxPlayers; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ServerListGame *>(obj); return &ptr->m_MaxPlayers; }
};

template <typename Self>
struct StormReflTypeInfo<ServerListGame>::field_data<0, Self> : public StormReflTypeInfo<ServerListGame>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_MaxPlayers; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_MaxPlayers; }
  void SetDefault() { self.m_MaxPlayers = StormReflTypeInfo<ServerListGame>::GetDefault().m_MaxPlayers; }
};

template <>
struct StormReflTypeInfo<ServerListGame>::field_data_static<1>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_CurPlayers"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x733D8BFB; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &ServerListGame::m_CurPlayers; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ServerListGame *>(obj); return &ptr->m_CurPlayers; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ServerListGame *>(obj); return &ptr->m_CurPlayers; }
};

template <typename Self>
struct StormReflTypeInfo<ServerListGame>::field_data<1, Self> : public StormReflTypeInfo<ServerListGame>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_CurPlayers; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_CurPlayers; }
  void SetDefault() { self.m_CurPlayers = StormReflTypeInfo<ServerListGame>::GetDefault().m_CurPlayers; }
};

template <>
struct StormReflTypeInfo<ServerListGame>::field_data_static<2>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_CurObservers"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xBF51EB7C; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &ServerListGame::m_CurObservers; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ServerListGame *>(obj); return &ptr->m_CurObservers; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ServerListGame *>(obj); return &ptr->m_CurObservers; }
};

template <typename Self>
struct StormReflTypeInfo<ServerListGame>::field_data<2, Self> : public StormReflTypeInfo<ServerListGame>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_CurObservers; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_CurObservers; }
  void SetDefault() { self.m_CurObservers = StormReflTypeInfo<ServerListGame>::GetDefault().m_CurObservers; }
};

template <>
struct StormReflTypeInfo<ServerListGame>::field_data_static<3>
{
  using member_type = RBool; // RBool
  static constexpr auto GetName() { return "m_Started"; }
  static constexpr auto GetType() { return "RBool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2164E30F; }
  static constexpr unsigned GetTypeNameHash() { return 0x50062D06; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &ServerListGame::m_Started; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ServerListGame *>(obj); return &ptr->m_Started; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ServerListGame *>(obj); return &ptr->m_Started; }
};

template <typename Self>
struct StormReflTypeInfo<ServerListGame>::field_data<3, Self> : public StormReflTypeInfo<ServerListGame>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RBool> & Get() { return self.m_Started; }
  std::add_const_t<std::remove_reference_t<RBool>> & Get() const { return self.m_Started; }
  void SetDefault() { self.m_Started = StormReflTypeInfo<ServerListGame>::GetDefault().m_Started; }
};

template <>
struct StormReflTypeInfo<ServerListGame>::field_data_static<4>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &ServerListGame::m_Name; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ServerListGame *>(obj); return &ptr->m_Name; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ServerListGame *>(obj); return &ptr->m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<ServerListGame>::field_data<4, Self> : public StormReflTypeInfo<ServerListGame>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<ServerListGame>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<ServerListGame>::field_data_static<5>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Map"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x604F6E5C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &ServerListGame::m_Map; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ServerListGame *>(obj); return &ptr->m_Map; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ServerListGame *>(obj); return &ptr->m_Map; }
};

template <typename Self>
struct StormReflTypeInfo<ServerListGame>::field_data<5, Self> : public StormReflTypeInfo<ServerListGame>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Map; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Map; }
  void SetDefault() { self.m_Map = StormReflTypeInfo<ServerListGame>::GetDefault().m_Map; }
};

template <>
struct StormReflTypeInfo<ServerListGame>::field_data_static<6>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_PasswordProtected"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x536AB58A; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &ServerListGame::m_PasswordProtected; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ServerListGame *>(obj); return &ptr->m_PasswordProtected; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ServerListGame *>(obj); return &ptr->m_PasswordProtected; }
};

template <typename Self>
struct StormReflTypeInfo<ServerListGame>::field_data<6, Self> : public StormReflTypeInfo<ServerListGame>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_PasswordProtected; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_PasswordProtected; }
  void SetDefault() { self.m_PasswordProtected = StormReflTypeInfo<ServerListGame>::GetDefault().m_PasswordProtected; }
};

template <>
struct StormReflTypeInfo<ServerList>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ServerList"; }
  static constexpr auto GetNameHash() { return 0xD8054756; }
  static constexpr bool HasDefault() { return false; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ServerList *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ServerList *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ServerList *>(ptr);
    if(typeid(ServerList).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ServerList *>(ptr);
    if(typeid(ServerList).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ServerList>::field_data_static<0>
{
  using member_type = RMap<DDSKey, ServerListGame>; // RMap<unsigned long, ServerListGame>
  static constexpr auto GetName() { return "m_GameList"; }
  static constexpr auto GetType() { return "RMap<unsigned long, ServerListGame>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x44E78937; }
  static constexpr unsigned GetTypeNameHash() { return 0x470AEEFD; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &ServerList::m_GameList; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ServerList *>(obj); return &ptr->m_GameList; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ServerList *>(obj); return &ptr->m_GameList; }
};

template <typename Self>
struct StormReflTypeInfo<ServerList>::field_data<0, Self> : public StormReflTypeInfo<ServerList>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMap<DDSKey, ServerListGame>> & Get() { return self.m_GameList; }
  std::add_const_t<std::remove_reference_t<RMap<DDSKey, ServerListGame>>> & Get() const { return self.m_GameList; }
};

template <>
struct StormReflFuncInfo<ServerList>
{
  using MyBase = void;
  static constexpr int funcs_n = 4;
  template <int N> struct func_data_static {};
};

template <>
struct StormReflFuncInfo<ServerList>::func_data_static<0>
{
  using func_ptr_type = void (ServerList::*)(DDSKey, std::string, std::string, int, int, bool);
  using return_type = void;
  static constexpr int params_n = 6;
  static constexpr auto GetName() { return "AddGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x229A7CDC; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 0; }
  static constexpr func_ptr_type GetFunctionPtr() { return &ServerList::AddGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<ServerList>::func_data_static<0>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "game_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x91CAB86C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<ServerList>::func_data_static<0>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "name"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x5E237E06; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<ServerList>::func_data_static<0>::param_info<2>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "map"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x93ADAABB; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<ServerList>::func_data_static<0>::param_info<3>
{
  using param_type = int;
  static constexpr auto GetName() { return "cur_players"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x5BA099E8; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<ServerList>::func_data_static<0>::param_info<4>
{
  using param_type = int;
  static constexpr auto GetName() { return "max_players"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xB2BD19E2; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<ServerList>::func_data_static<0>::param_info<5>
{
  using param_type = bool;
  static constexpr auto GetName() { return "password"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetNameHash() { return 0x35C246D5; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
};

template <>
struct StormReflFuncInfo<ServerList>::func_data_static<1>
{
  using func_ptr_type = void (ServerList::*)(DDSKey, int, int);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "UpdateGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x5648F9FB; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 1; }
  static constexpr func_ptr_type GetFunctionPtr() { return &ServerList::UpdateGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<ServerList>::func_data_static<1>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "game_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x91CAB86C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<ServerList>::func_data_static<1>::param_info<1>
{
  using param_type = int;
  static constexpr auto GetName() { return "cur_players"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x5BA099E8; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<ServerList>::func_data_static<1>::param_info<2>
{
  using param_type = int;
  static constexpr auto GetName() { return "cur_observer"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x0A76C6AA; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<ServerList>::func_data_static<2>
{
  using func_ptr_type = void (ServerList::*)(DDSKey);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "StartGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x40E81A4D; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 2; }
  static constexpr func_ptr_type GetFunctionPtr() { return &ServerList::StartGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<ServerList>::func_data_static<2>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "game_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x91CAB86C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<ServerList>::func_data_static<3>
{
  using func_ptr_type = void (ServerList::*)(DDSKey);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "RemoveGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x507B24C1; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 3; }
  static constexpr func_ptr_type GetFunctionPtr() { return &ServerList::RemoveGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<ServerList>::func_data_static<3>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "game_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x91CAB86C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

namespace StormReflFileInfo
{
  struct ServerList
  {
    static const int types_n = 2;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct ServerList::type_info<0>
  {
    using type = ::ServerListGame;
  };

  template <>
  struct ServerList::type_info<1>
  {
    using type = ::ServerList;
  };

}

