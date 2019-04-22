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
  static constexpr int fields_n = 7;
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
  using member_type = GameServerInfo; // GameServerInfo
  static constexpr auto GetName() { return "m_ServerInfo"; }
  static constexpr auto GetType() { return "GameServerInfo"; }
  static constexpr unsigned GetFieldNameHash() { return 0x92A06404; }
  static constexpr unsigned GetTypeNameHash() { return 0x051A96DE; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GameServerConnection::m_ServerInfo; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerConnection *>(obj); return &ptr->m_ServerInfo; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerConnection *>(obj); return &ptr->m_ServerInfo; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerConnection>::field_data<2, Self> : public StormReflTypeInfo<GameServerConnection>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameServerInfo> & Get() { return self.m_ServerInfo; }
  std::add_const_t<std::remove_reference_t<GameServerInfo>> & Get() const { return self.m_ServerInfo; }
};

template <>
struct StormReflTypeInfo<GameServerConnection>::field_data_static<3>
{
  using member_type = uint64_t; // unsigned long
  static constexpr auto GetName() { return "m_ExpectedChallengeResponse"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2D8BE64A; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &GameServerConnection::m_ExpectedChallengeResponse; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerConnection *>(obj); return &ptr->m_ExpectedChallengeResponse; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerConnection *>(obj); return &ptr->m_ExpectedChallengeResponse; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerConnection>::field_data<3, Self> : public StormReflTypeInfo<GameServerConnection>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint64_t> & Get() { return self.m_ExpectedChallengeResponse; }
  std::add_const_t<std::remove_reference_t<uint64_t>> & Get() const { return self.m_ExpectedChallengeResponse; }
};

template <>
struct StormReflTypeInfo<GameServerConnection>::field_data_static<4>
{
  using member_type = std::vector<std::string>; // std::vector<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::allocator<std::basic_string<char, std::char_traits<char>, std::allocator<char> > > >
  static constexpr auto GetName() { return "m_PendingMessages"; }
  static constexpr auto GetType() { return "std::vector<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::allocator<std::basic_string<char, std::char_traits<char>, std::allocator<char> > > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2C42FDAA; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F698566; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &GameServerConnection::m_PendingMessages; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerConnection *>(obj); return &ptr->m_PendingMessages; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerConnection *>(obj); return &ptr->m_PendingMessages; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerConnection>::field_data<4, Self> : public StormReflTypeInfo<GameServerConnection>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<std::string>> & Get() { return self.m_PendingMessages; }
  std::add_const_t<std::remove_reference_t<std::vector<std::string>>> & Get() const { return self.m_PendingMessages; }
};

template <>
struct StormReflTypeInfo<GameServerConnection>::field_data_static<5>
{
  using member_type = std::vector<DDSKey>; // std::vector<unsigned long, std::allocator<unsigned long> >
  static constexpr auto GetName() { return "m_ActiveGameIds"; }
  static constexpr auto GetType() { return "std::vector<unsigned long, std::allocator<unsigned long> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC798BC51; }
  static constexpr unsigned GetTypeNameHash() { return 0x940F60C3; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &GameServerConnection::m_ActiveGameIds; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerConnection *>(obj); return &ptr->m_ActiveGameIds; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerConnection *>(obj); return &ptr->m_ActiveGameIds; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerConnection>::field_data<5, Self> : public StormReflTypeInfo<GameServerConnection>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<DDSKey>> & Get() { return self.m_ActiveGameIds; }
  std::add_const_t<std::remove_reference_t<std::vector<DDSKey>>> & Get() const { return self.m_ActiveGameIds; }
};

template <>
struct StormReflTypeInfo<GameServerConnection>::field_data_static<6>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_Error"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD0EB2C11; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &GameServerConnection::m_Error; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerConnection *>(obj); return &ptr->m_Error; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerConnection *>(obj); return &ptr->m_Error; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerConnection>::field_data<6, Self> : public StormReflTypeInfo<GameServerConnection>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_Error; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_Error; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>
{
  using MyBase = void;
  static constexpr int funcs_n = 8;
  template <int N> struct func_data_static {};
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<0>
{
  using func_ptr_type = void (GameServerConnection::*)(GameServerMessageType, std::string);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "GotMessage"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xD040732D; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 0; }
  static constexpr func_ptr_type GetFunctionPtr() { return &GameServerConnection::GotMessage; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<0>::param_info<0>
{
  using param_type = GameServerMessageType;
  static constexpr auto GetName() { return "cmd"; }
  static constexpr auto GetType() { return "GameServerMessageType"; }
  static constexpr unsigned GetNameHash() { return 0x2F5C1CC0; }
  static constexpr unsigned GetTypeNameHash() { return 0x51112183; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<0>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "data"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xADF3F363; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<1>
{
  using func_ptr_type = void (GameServerConnection::*)(const GameServerCreateGame &);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "CreateGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x9EA4204C; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 1; }
  static constexpr func_ptr_type GetFunctionPtr() { return &GameServerConnection::CreateGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<1>::param_info<0>
{
  using param_type = const GameServerCreateGame &;
  static constexpr auto GetName() { return "msg"; }
  static constexpr auto GetType() { return "const GameServerCreateGame &"; }
  static constexpr unsigned GetNameHash() { return 0x688A5FAF; }
  static constexpr unsigned GetTypeNameHash() { return 0x8EB555B4; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<2>
{
  using func_ptr_type = void (GameServerConnection::*)(const GameServerDestroyGame &);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "DestroyGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x0F26CB52; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 2; }
  static constexpr func_ptr_type GetFunctionPtr() { return &GameServerConnection::DestroyGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<2>::param_info<0>
{
  using param_type = const GameServerDestroyGame &;
  static constexpr auto GetName() { return "msg"; }
  static constexpr auto GetType() { return "const GameServerDestroyGame &"; }
  static constexpr unsigned GetNameHash() { return 0x688A5FAF; }
  static constexpr unsigned GetTypeNameHash() { return 0xA5869E9A; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<3>
{
  using func_ptr_type = void (GameServerConnection::*)(DDSKey, DDSKey);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "RemoveUserFromGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xD2BD9316; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 3; }
  static constexpr func_ptr_type GetFunctionPtr() { return &GameServerConnection::RemoveUserFromGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<3>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<3>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xA76ED395; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<4>
{
  using func_ptr_type = void (GameServerConnection::*)(DDSKey, const GameServerAuthenticateUserSuccess &);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "NotifyTokenRedeemedSuccess"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x054EBF07; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 4; }
  static constexpr func_ptr_type GetFunctionPtr() { return &GameServerConnection::NotifyTokenRedeemedSuccess; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<4>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<4>::param_info<1>
{
  using param_type = const GameServerAuthenticateUserSuccess &;
  static constexpr auto GetName() { return "msg"; }
  static constexpr auto GetType() { return "const GameServerAuthenticateUserSuccess &"; }
  static constexpr unsigned GetNameHash() { return 0x688A5FAF; }
  static constexpr unsigned GetTypeNameHash() { return 0x72DE6481; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<5>
{
  using func_ptr_type = void (GameServerConnection::*)(DDSKey, const GameServerAuthenticateUserFailure &);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "NotifyTokenRedeemedFailure"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x4BD56374; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 5; }
  static constexpr func_ptr_type GetFunctionPtr() { return &GameServerConnection::NotifyTokenRedeemedFailure; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<5>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<5>::param_info<1>
{
  using param_type = const GameServerAuthenticateUserFailure &;
  static constexpr auto GetName() { return "msg"; }
  static constexpr auto GetType() { return "const GameServerAuthenticateUserFailure &"; }
  static constexpr unsigned GetNameHash() { return 0x688A5FAF; }
  static constexpr unsigned GetTypeNameHash() { return 0xF9A99ED0; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<6>
{
  using func_ptr_type = void (GameServerConnection::*)(DDSKey, DDSKey, bool);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "NotifyUserQuitGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x8B12BEF0; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 6; }
  static constexpr func_ptr_type GetFunctionPtr() { return &GameServerConnection::NotifyUserQuitGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<6>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<6>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x6186CA22; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<6>::param_info<2>
{
  using param_type = bool;
  static constexpr auto GetName() { return "ban"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetNameHash() { return 0x62FED0E5; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<7>
{
  using func_ptr_type = void (GameServerConnection::*)(DDSKey);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "NotifyGameEnded"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x15129AE3; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 7; }
  static constexpr func_ptr_type GetFunctionPtr() { return &GameServerConnection::NotifyGameEnded; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<7>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
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

