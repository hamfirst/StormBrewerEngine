#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "GameServerConnection.refl.h"
#include "SharedTypes.refl.meta.h"
#include "GameServerMessages.refl.meta.h"


template <>
struct StormReflEnumInfo<GameServerConnectionState>
{
  static constexpr int elems_n = 3;
  static constexpr auto GetName() { return "GameServerConnectionState"; }
  static constexpr auto GetNameHash() { return 0x227BBB92; }
  template <int N> struct elems { };
};

template <>
struct StormReflEnumInfo<GameServerConnectionState>::elems<0>
{
  static constexpr auto GetName() { return "kWaitingForConnection"; }
  static constexpr auto GetNameHash() { return 0x3A061D29; }
  static constexpr auto GetValue() { return GameServerConnectionState::kWaitingForConnection; }
};

template <>
struct StormReflEnumInfo<GameServerConnectionState>::elems<1>
{
  static constexpr auto GetName() { return "kAuthenticating"; }
  static constexpr auto GetNameHash() { return 0xC9B5A1FD; }
  static constexpr auto GetValue() { return GameServerConnectionState::kAuthenticating; }
};

template <>
struct StormReflEnumInfo<GameServerConnectionState>::elems<2>
{
  static constexpr auto GetName() { return "kConnected"; }
  static constexpr auto GetNameHash() { return 0xB4C21949; }
  static constexpr auto GetValue() { return GameServerConnectionState::kConnected; }
};

template <>
struct StormReflTypeInfo<GameServerConnection>
{
  using MyBase = void;
  static constexpr int fields_n = 10;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameServerConnection"; }
  static constexpr auto GetNameHash() { return 0xE68B80F0; }
  static constexpr bool HasDefault() { return false; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameServerConnection *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerConnection *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameServerConnection *>(ptr);
    if(typeid(GameServerConnection).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerConnection *>(ptr);
    if(typeid(GameServerConnection).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameServerConnection>::field_data_static<0>
{
  using member_type = RMergeList<RKey>; // RMergeList<RNumber<unsigned long> >
  static constexpr auto GetName() { return "m_Games"; }
  static constexpr auto GetType() { return "RMergeList<RNumber<unsigned long> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x7215BB51; }
  static constexpr unsigned GetTypeNameHash() { return 0xD4BB98ED; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameServerConnection::m_Games; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerConnection *>(obj); return &ptr->m_Games; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerConnection *>(obj); return &ptr->m_Games; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerConnection>::field_data<0, Self> : public StormReflTypeInfo<GameServerConnection>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<RKey>> & Get() { return self.m_Games; }
  std::add_const_t<std::remove_reference_t<RMergeList<RKey>>> & Get() const { return self.m_Games; }
};

template <>
struct StormReflTypeInfo<GameServerConnection>::field_data_static<1>
{
  using member_type = GameServerConnectionState; // GameServerConnectionState
  static constexpr auto GetName() { return "m_State"; }
  static constexpr auto GetType() { return "GameServerConnectionState"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2EA5429B; }
  static constexpr unsigned GetTypeNameHash() { return 0x227BBB92; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameServerConnection::m_State; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerConnection *>(obj); return &ptr->m_State; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerConnection *>(obj); return &ptr->m_State; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerConnection>::field_data<1, Self> : public StormReflTypeInfo<GameServerConnection>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameServerConnectionState> & Get() { return self.m_State; }
  std::add_const_t<std::remove_reference_t<GameServerConnectionState>> & Get() const { return self.m_State; }
};

template <>
struct StormReflTypeInfo<GameServerConnection>::field_data_static<2>
{
  using member_type = uint64_t; // unsigned long
  static constexpr auto GetName() { return "m_ExpectedChallengeResponse"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2D8BE64A; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GameServerConnection::m_ExpectedChallengeResponse; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerConnection *>(obj); return &ptr->m_ExpectedChallengeResponse; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerConnection *>(obj); return &ptr->m_ExpectedChallengeResponse; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerConnection>::field_data<2, Self> : public StormReflTypeInfo<GameServerConnection>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint64_t> & Get() { return self.m_ExpectedChallengeResponse; }
  std::add_const_t<std::remove_reference_t<uint64_t>> & Get() const { return self.m_ExpectedChallengeResponse; }
};

template <>
struct StormReflTypeInfo<GameServerConnection>::field_data_static<3>
{
  using member_type = std::vector<std::string>; // std::vector<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::allocator<std::basic_string<char, std::char_traits<char>, std::allocator<char> > > >
  static constexpr auto GetName() { return "m_PendingMessages"; }
  static constexpr auto GetType() { return "std::vector<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::allocator<std::basic_string<char, std::char_traits<char>, std::allocator<char> > > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2C42FDAA; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F698566; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &GameServerConnection::m_PendingMessages; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerConnection *>(obj); return &ptr->m_PendingMessages; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerConnection *>(obj); return &ptr->m_PendingMessages; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerConnection>::field_data<3, Self> : public StormReflTypeInfo<GameServerConnection>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<std::string>> & Get() { return self.m_PendingMessages; }
  std::add_const_t<std::remove_reference_t<std::vector<std::string>>> & Get() const { return self.m_PendingMessages; }
};

template <>
struct StormReflTypeInfo<GameServerConnection>::field_data_static<4>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_RemoteHost"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x345B4DA6; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &GameServerConnection::m_RemoteHost; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerConnection *>(obj); return &ptr->m_RemoteHost; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerConnection *>(obj); return &ptr->m_RemoteHost; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerConnection>::field_data<4, Self> : public StormReflTypeInfo<GameServerConnection>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_RemoteHost; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_RemoteHost; }
};

template <>
struct StormReflTypeInfo<GameServerConnection>::field_data_static<5>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_Error"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD0EB2C11; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &GameServerConnection::m_Error; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerConnection *>(obj); return &ptr->m_Error; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerConnection *>(obj); return &ptr->m_Error; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerConnection>::field_data<5, Self> : public StormReflTypeInfo<GameServerConnection>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_Error; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_Error; }
};

template <>
struct StormReflTypeInfo<GameServerConnection>::field_data_static<6>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_ServerName"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x070A2B55; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &GameServerConnection::m_ServerName; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerConnection *>(obj); return &ptr->m_ServerName; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerConnection *>(obj); return &ptr->m_ServerName; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerConnection>::field_data<6, Self> : public StormReflTypeInfo<GameServerConnection>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_ServerName; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_ServerName; }
};

template <>
struct StormReflTypeInfo<GameServerConnection>::field_data_static<7>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_ServerZone"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF9C29554; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &GameServerConnection::m_ServerZone; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerConnection *>(obj); return &ptr->m_ServerZone; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerConnection *>(obj); return &ptr->m_ServerZone; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerConnection>::field_data<7, Self> : public StormReflTypeInfo<GameServerConnection>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_ServerZone; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_ServerZone; }
};

template <>
struct StormReflTypeInfo<GameServerConnection>::field_data_static<8>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_ServerResourceId"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x484BB3D8; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 8; }
  static constexpr auto GetMemberPtr() { return &GameServerConnection::m_ServerResourceId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerConnection *>(obj); return &ptr->m_ServerResourceId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerConnection *>(obj); return &ptr->m_ServerResourceId; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerConnection>::field_data<8, Self> : public StormReflTypeInfo<GameServerConnection>::field_data_static<8>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_ServerResourceId; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_ServerResourceId; }
};

template <>
struct StormReflTypeInfo<GameServerConnection>::field_data_static<9>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_ServerExternalIp"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x7914B77A; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 9; }
  static constexpr auto GetMemberPtr() { return &GameServerConnection::m_ServerExternalIp; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerConnection *>(obj); return &ptr->m_ServerExternalIp; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerConnection *>(obj); return &ptr->m_ServerExternalIp; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerConnection>::field_data<9, Self> : public StormReflTypeInfo<GameServerConnection>::field_data_static<9>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_ServerExternalIp; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_ServerExternalIp; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>
{
  using MyBase = void;
  static constexpr int funcs_n = 7;
  template <int N> struct func_data_static {};
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<0>
{
  using func_ptr_type = void (GameServerConnection::*)(std::string);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "SetRemoteHost"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x570BE899; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 0; }
  static constexpr func_ptr_type GetFunctionPtr() { return &GameServerConnection::SetRemoteHost; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<0>::param_info<0>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "host"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xCF2713FD; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<1>
{
  using func_ptr_type = void (GameServerConnection::*)(GameServerMessageType, std::string);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "GotMessage"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xD040732D; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 1; }
  static constexpr func_ptr_type GetFunctionPtr() { return &GameServerConnection::GotMessage; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<1>::param_info<0>
{
  using param_type = GameServerMessageType;
  static constexpr auto GetName() { return "cmd"; }
  static constexpr auto GetType() { return "GameServerMessageType"; }
  static constexpr unsigned GetNameHash() { return 0x2F5C1CC0; }
  static constexpr unsigned GetTypeNameHash() { return 0x51112183; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<1>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "data"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xADF3F363; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<2>
{
  using func_ptr_type = void (GameServerConnection::*)(GameInitSettings);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "CreateGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x9EA4204C; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 2; }
  static constexpr func_ptr_type GetFunctionPtr() { return &GameServerConnection::CreateGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<2>::param_info<0>
{
  using param_type = GameInitSettings;
  static constexpr auto GetName() { return "game_creation_data"; }
  static constexpr auto GetType() { return "GameInitSettings"; }
  static constexpr unsigned GetNameHash() { return 0xDA61292C; }
  static constexpr unsigned GetTypeNameHash() { return 0xBAC6DD28; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<3>
{
  using func_ptr_type = void (GameServerConnection::*)(int);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "DestroyGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x0F26CB52; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 3; }
  static constexpr func_ptr_type GetFunctionPtr() { return &GameServerConnection::DestroyGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<3>::param_info<0>
{
  using param_type = int;
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<4>
{
  using func_ptr_type = void (GameServerConnection::*)(int, DDSKey);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "UserLeaveGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x38A2B0E9; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 4; }
  static constexpr func_ptr_type GetFunctionPtr() { return &GameServerConnection::UserLeaveGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<4>::param_info<0>
{
  using param_type = int;
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<4>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x6186CA22; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<5>
{
  using func_ptr_type = void (GameServerConnection::*)(int, DDSKey, DDSKey);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "SendLaunchGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xCDBB7E33; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 5; }
  static constexpr func_ptr_type GetFunctionPtr() { return &GameServerConnection::SendLaunchGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<5>::param_info<0>
{
  using param_type = int;
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<5>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xA76ED395; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<5>::param_info<2>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<6>
{
  using func_ptr_type = void (GameServerConnection::*)(RKey, RKey, uint32_t, bool);
  using return_type = void;
  static constexpr int params_n = 4;
  static constexpr auto GetName() { return "NotifyTokenRedeemed"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x94458591; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 6; }
  static constexpr func_ptr_type GetFunctionPtr() { return &GameServerConnection::NotifyTokenRedeemed; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<6>::param_info<0>
{
  using param_type = RKey;
  static constexpr auto GetName() { return "user_key"; }
  static constexpr auto GetType() { return "RKey"; }
  static constexpr unsigned GetNameHash() { return 0x6186CA22; }
  static constexpr unsigned GetTypeNameHash() { return 0x0DDC2C6E; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<6>::param_info<1>
{
  using param_type = RKey;
  static constexpr auto GetName() { return "game_key"; }
  static constexpr auto GetType() { return "RKey"; }
  static constexpr unsigned GetNameHash() { return 0x91CAB86C; }
  static constexpr unsigned GetTypeNameHash() { return 0x0DDC2C6E; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<6>::param_info<2>
{
  using param_type = uint32_t;
  static constexpr auto GetName() { return "response_id"; }
  static constexpr auto GetType() { return "uint32_t"; }
  static constexpr unsigned GetNameHash() { return 0xFBF32840; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E2AF381; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<6>::param_info<3>
{
  using param_type = bool;
  static constexpr auto GetName() { return "success"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetNameHash() { return 0x6F00DFB2; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
};

namespace StormReflFileInfo
{
  struct GameServerConnection
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct GameServerConnection::type_info<0>
  {
    using type = ::GameServerConnection;
  };

}

