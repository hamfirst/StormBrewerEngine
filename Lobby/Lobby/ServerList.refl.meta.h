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
  static ServerListGame & GetDefault() { static ServerListGame def; return def; }
};

template <>
struct StormReflTypeInfo<ServerListGame>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_MaxPlayers"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0D18B4FD; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &ServerListGame::m_MaxPlayers; }
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
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &ServerListGame::m_CurPlayers; }
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
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &ServerListGame::m_CurObservers; }
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
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &ServerListGame::m_Started; }
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
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &ServerListGame::m_Name; }
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
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &ServerListGame::m_Map; }
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
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &ServerListGame::m_PasswordProtected; }
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
struct StormReflTypeInfo<ServerListServer>
{
  using MyBase = void;
  static constexpr int fields_n = 5;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ServerListServer"; }
  static constexpr auto GetNameHash() { return 0xD9812BC9; }
  static ServerListServer & GetDefault() { static ServerListServer def; return def; }
};

template <>
struct StormReflTypeInfo<ServerListServer>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &ServerListServer::m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<ServerListServer>::field_data<0, Self> : public StormReflTypeInfo<ServerListServer>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<ServerListServer>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<ServerListServer>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Location"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA8B25DE5; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &ServerListServer::m_Location; }
};

template <typename Self>
struct StormReflTypeInfo<ServerListServer>::field_data<1, Self> : public StormReflTypeInfo<ServerListServer>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Location; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Location; }
  void SetDefault() { self.m_Location = StormReflTypeInfo<ServerListServer>::GetDefault().m_Location; }
};

template <>
struct StormReflTypeInfo<ServerListServer>::field_data_static<2>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Host"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF1BA86E2; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &ServerListServer::m_Host; }
};

template <typename Self>
struct StormReflTypeInfo<ServerListServer>::field_data<2, Self> : public StormReflTypeInfo<ServerListServer>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Host; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Host; }
  void SetDefault() { self.m_Host = StormReflTypeInfo<ServerListServer>::GetDefault().m_Host; }
};

template <>
struct StormReflTypeInfo<ServerListServer>::field_data_static<3>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_PingPort"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFA7B7B78; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &ServerListServer::m_PingPort; }
};

template <typename Self>
struct StormReflTypeInfo<ServerListServer>::field_data<3, Self> : public StormReflTypeInfo<ServerListServer>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_PingPort; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_PingPort; }
  void SetDefault() { self.m_PingPort = StormReflTypeInfo<ServerListServer>::GetDefault().m_PingPort; }
};

template <>
struct StormReflTypeInfo<ServerListServer>::field_data_static<4>
{
  using member_type = RMergeList<ServerListGame>; // RMergeList<ServerListGame>
  static constexpr auto GetName() { return "m_Games"; }
  static constexpr auto GetType() { return "RMergeList<ServerListGame>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x7215BB51; }
  static constexpr unsigned GetTypeNameHash() { return 0x21518502; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &ServerListServer::m_Games; }
};

template <typename Self>
struct StormReflTypeInfo<ServerListServer>::field_data<4, Self> : public StormReflTypeInfo<ServerListServer>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<ServerListGame>> & Get() { return self.m_Games; }
  std::add_const_t<std::remove_reference_t<RMergeList<ServerListGame>>> & Get() const { return self.m_Games; }
  void SetDefault() { self.m_Games = StormReflTypeInfo<ServerListServer>::GetDefault().m_Games; }
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
};

template <>
struct StormReflTypeInfo<ServerList>::field_data_static<0>
{
  using member_type = RMap<DDSKey, ServerListServer>; // RMap<unsigned long long, ServerListServer>
  static constexpr auto GetName() { return "m_ServerList"; }
  static constexpr auto GetType() { return "RMap<unsigned long long, ServerListServer>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1DE1AD4B; }
  static constexpr unsigned GetTypeNameHash() { return 0xC4E3D3E9; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &ServerList::m_ServerList; }
};

template <typename Self>
struct StormReflTypeInfo<ServerList>::field_data<0, Self> : public StormReflTypeInfo<ServerList>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMap<DDSKey, ServerListServer>> & Get() { return self.m_ServerList; }
  std::add_const_t<std::remove_reference_t<RMap<DDSKey, ServerListServer>>> & Get() const { return self.m_ServerList; }
};

template <>
struct StormReflFuncInfo<ServerList>
{
  static constexpr int funcs_n = 7;
  template <int N> struct func_data_static {};
};

template <>
struct StormReflFuncInfo<ServerList>::func_data_static<0>
{
  using func_ptr_type = void (ServerList::*)(DDSKey, std::string, std::string, std::string, int);
  using return_type = void;
  static constexpr int params_n = 5;
  static constexpr auto GetName() { return "AddServer"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xE8BBB43E; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 0; }
  static constexpr func_ptr_type GetFunctionPtr() { return &ServerList::AddServer; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<ServerList>::func_data_static<0>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "server_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xB459A1F3; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<ServerList>::func_data_static<0>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "server_name"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xD5A30FE6; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<ServerList>::func_data_static<0>::param_info<2>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "location"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x5E9E89CB; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<ServerList>::func_data_static<0>::param_info<3>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "server_host"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x44A7621D; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<ServerList>::func_data_static<0>::param_info<4>
{
  using param_type = int;
  static constexpr auto GetName() { return "ping_port"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xCFE0BE7B; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<ServerList>::func_data_static<1>
{
  using func_ptr_type = void (ServerList::*)(DDSKey);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "RemoveServer"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x72677305; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 1; }
  static constexpr func_ptr_type GetFunctionPtr() { return &ServerList::RemoveServer; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<ServerList>::func_data_static<1>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "server_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xB459A1F3; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<ServerList>::func_data_static<2>
{
  using func_ptr_type = void (ServerList::*)(DDSKey, int, std::string, std::string, int, int, bool);
  using return_type = void;
  static constexpr int params_n = 7;
  static constexpr auto GetName() { return "AddGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x229A7CDC; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 2; }
  static constexpr func_ptr_type GetFunctionPtr() { return &ServerList::AddGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<ServerList>::func_data_static<2>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "server_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xB459A1F3; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<ServerList>::func_data_static<2>::param_info<1>
{
  using param_type = int;
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<ServerList>::func_data_static<2>::param_info<2>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "name"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x5E237E06; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<ServerList>::func_data_static<2>::param_info<3>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "map"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x93ADAABB; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<ServerList>::func_data_static<2>::param_info<4>
{
  using param_type = int;
  static constexpr auto GetName() { return "cur_players"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x5BA099E8; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<ServerList>::func_data_static<2>::param_info<5>
{
  using param_type = int;
  static constexpr auto GetName() { return "max_players"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xB2BD19E2; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<ServerList>::func_data_static<2>::param_info<6>
{
  using param_type = bool;
  static constexpr auto GetName() { return "password"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetNameHash() { return 0x35C246D5; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
};

template <>
struct StormReflFuncInfo<ServerList>::func_data_static<3>
{
  using func_ptr_type = void (ServerList::*)(DDSKey, int, int, int);
  using return_type = void;
  static constexpr int params_n = 4;
  static constexpr auto GetName() { return "UpdateGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x5648F9FB; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 3; }
  static constexpr func_ptr_type GetFunctionPtr() { return &ServerList::UpdateGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<ServerList>::func_data_static<3>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "server_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xB459A1F3; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<ServerList>::func_data_static<3>::param_info<1>
{
  using param_type = int;
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<ServerList>::func_data_static<3>::param_info<2>
{
  using param_type = int;
  static constexpr auto GetName() { return "cur_players"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x5BA099E8; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<ServerList>::func_data_static<3>::param_info<3>
{
  using param_type = int;
  static constexpr auto GetName() { return "cur_observer"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x0A76C6AA; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<ServerList>::func_data_static<4>
{
  using func_ptr_type = void (ServerList::*)(DDSKey, int);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "StartGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x40E81A4D; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 4; }
  static constexpr func_ptr_type GetFunctionPtr() { return &ServerList::StartGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<ServerList>::func_data_static<4>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "server_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xB459A1F3; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<ServerList>::func_data_static<4>::param_info<1>
{
  using param_type = int;
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<ServerList>::func_data_static<5>
{
  using func_ptr_type = void (ServerList::*)(DDSKey, int);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "RemoveGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x507B24C1; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 5; }
  static constexpr func_ptr_type GetFunctionPtr() { return &ServerList::RemoveGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<ServerList>::func_data_static<5>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "server_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xB459A1F3; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<ServerList>::func_data_static<5>::param_info<1>
{
  using param_type = int;
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<ServerList>::func_data_static<6>
{
  using func_ptr_type = void (ServerList::*)();
  using return_type = void;
  static constexpr int params_n = 0;
  static constexpr auto GetName() { return "HangUpAllServers"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x751F7D64; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 6; }
  static constexpr func_ptr_type GetFunctionPtr() { return &ServerList::HangUpAllServers; }
  template <int i>
  struct param_info { };
};

namespace StormReflFileInfo
{
  struct ServerList
  {
    static const int types_n = 3;
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
    using type = ::ServerListServer;
  };

  template <>
  struct ServerList::type_info<2>
  {
    using type = ::ServerList;
  };

}

