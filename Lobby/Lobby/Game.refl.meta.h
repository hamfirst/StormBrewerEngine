#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "Game.refl.h"
#include "SharedTypes.refl.meta.h"
#include "GameServerMessages.refl.meta.h"


template <>
struct StormReflTypeInfo<GameToken>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameToken"; }
  static constexpr auto GetNameHash() { return 0xAA3710AB; }
  static constexpr bool HasDefault() { return true; }
  static GameToken & GetDefault() { static GameToken def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameToken *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameToken *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameToken *>(ptr);
    if(typeid(GameToken).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameToken *>(ptr);
    if(typeid(GameToken).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameToken>::field_data_static<0>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_UserKey"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE6008E39; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameToken::m_UserKey; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameToken *>(obj); return &ptr->m_UserKey; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameToken *>(obj); return &ptr->m_UserKey; }
};

template <typename Self>
struct StormReflTypeInfo<GameToken>::field_data<0, Self> : public StormReflTypeInfo<GameToken>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_UserKey; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_UserKey; }
  void SetDefault() { self.m_UserKey = StormReflTypeInfo<GameToken>::GetDefault().m_UserKey; }
};

template <>
struct StormReflTypeInfo<Game>
{
  using MyBase = void;
  static constexpr int fields_n = 5;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "Game"; }
  static constexpr auto GetNameHash() { return 0x83199EB2; }
  static constexpr bool HasDefault() { return false; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<Game *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const Game *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<Game *>(ptr);
    if(typeid(Game).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const Game *>(ptr);
    if(typeid(Game).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<Game>::field_data_static<0>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_AssignedServer"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x090FAC25; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &Game::m_AssignedServer; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<Game *>(obj); return &ptr->m_AssignedServer; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const Game *>(obj); return &ptr->m_AssignedServer; }
};

template <typename Self>
struct StormReflTypeInfo<Game>::field_data<0, Self> : public StormReflTypeInfo<Game>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_AssignedServer; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_AssignedServer; }
};

template <>
struct StormReflTypeInfo<Game>::field_data_static<1>
{
  using member_type = GameInfo; // GameInfo
  static constexpr auto GetName() { return "m_GameInfo"; }
  static constexpr auto GetType() { return "GameInfo"; }
  static constexpr unsigned GetFieldNameHash() { return 0xCBA64078; }
  static constexpr unsigned GetTypeNameHash() { return 0xC4FCF600; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &Game::m_GameInfo; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<Game *>(obj); return &ptr->m_GameInfo; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const Game *>(obj); return &ptr->m_GameInfo; }
};

template <typename Self>
struct StormReflTypeInfo<Game>::field_data<1, Self> : public StormReflTypeInfo<Game>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameInfo> & Get() { return self.m_GameInfo; }
  std::add_const_t<std::remove_reference_t<GameInfo>> & Get() const { return self.m_GameInfo; }
};

template <>
struct StormReflTypeInfo<Game>::field_data_static<2>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_GameCreateTime"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x575F4BA1; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &Game::m_GameCreateTime; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<Game *>(obj); return &ptr->m_GameCreateTime; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const Game *>(obj); return &ptr->m_GameCreateTime; }
};

template <typename Self>
struct StormReflTypeInfo<Game>::field_data<2, Self> : public StormReflTypeInfo<Game>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_GameCreateTime; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_GameCreateTime; }
};

template <>
struct StormReflTypeInfo<Game>::field_data_static<3>
{
  using member_type = std::map<DDSKey, DDSKey>; // std::map<unsigned long, unsigned long, std::less<unsigned long>, std::allocator<std::pair<const unsigned long, unsigned long> > >
  static constexpr auto GetName() { return "m_MemberSubscriptionIds"; }
  static constexpr auto GetType() { return "std::map<unsigned long, unsigned long, std::less<unsigned long>, std::allocator<std::pair<const unsigned long, unsigned long> > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8369B12E; }
  static constexpr unsigned GetTypeNameHash() { return 0x9D5C622D; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &Game::m_MemberSubscriptionIds; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<Game *>(obj); return &ptr->m_MemberSubscriptionIds; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const Game *>(obj); return &ptr->m_MemberSubscriptionIds; }
};

template <typename Self>
struct StormReflTypeInfo<Game>::field_data<3, Self> : public StormReflTypeInfo<Game>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::map<DDSKey, DDSKey>> & Get() { return self.m_MemberSubscriptionIds; }
  std::add_const_t<std::remove_reference_t<std::map<DDSKey, DDSKey>>> & Get() const { return self.m_MemberSubscriptionIds; }
};

template <>
struct StormReflTypeInfo<Game>::field_data_static<4>
{
  using member_type = std::map<DDSKey, GameToken>; // std::map<unsigned long, GameToken, std::less<unsigned long>, std::allocator<std::pair<const unsigned long, GameToken> > >
  static constexpr auto GetName() { return "m_Tokens"; }
  static constexpr auto GetType() { return "std::map<unsigned long, GameToken, std::less<unsigned long>, std::allocator<std::pair<const unsigned long, GameToken> > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE7654646; }
  static constexpr unsigned GetTypeNameHash() { return 0x3BCA3037; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &Game::m_Tokens; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<Game *>(obj); return &ptr->m_Tokens; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const Game *>(obj); return &ptr->m_Tokens; }
};

template <typename Self>
struct StormReflTypeInfo<Game>::field_data<4, Self> : public StormReflTypeInfo<Game>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::map<DDSKey, GameToken>> & Get() { return self.m_Tokens; }
  std::add_const_t<std::remove_reference_t<std::map<DDSKey, GameToken>>> & Get() const { return self.m_Tokens; }
};

template <>
struct StormReflFuncInfo<Game>
{
  using MyBase = void;
  static constexpr int funcs_n = 16;
  template <int N> struct func_data_static {};
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<0>
{
  using func_ptr_type = void (Game::*)(GameInitSettings);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "Init"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x66464B4A; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 0; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::Init; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<0>::param_info<0>
{
  using param_type = GameInitSettings;
  static constexpr auto GetName() { return "settings"; }
  static constexpr auto GetType() { return "GameInitSettings"; }
  static constexpr unsigned GetNameHash() { return 0xE545A0C5; }
  static constexpr unsigned GetTypeNameHash() { return 0xBAC6DD28; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<1>
{
  using func_ptr_type = void (Game::*)();
  using return_type = void;
  static constexpr int params_n = 0;
  static constexpr auto GetName() { return "Cleanup"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x05F50D45; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 1; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::Cleanup; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<2>
{
  using func_ptr_type = void (Game::*)();
  using return_type = void;
  static constexpr int params_n = 0;
  static constexpr auto GetName() { return "Update"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x9F89304E; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 2; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::Update; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<3>
{
  using func_ptr_type = void (Game::*)(uint32_t);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "SetJoinCode"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x2A636209; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 3; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::SetJoinCode; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<3>::param_info<0>
{
  using param_type = uint32_t;
  static constexpr auto GetName() { return "join_code"; }
  static constexpr auto GetType() { return "uint32_t"; }
  static constexpr unsigned GetNameHash() { return 0xE64D7D01; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E2AF381; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<4>
{
  using func_ptr_type = void (Game::*)(DDSResponder &, DDSKey);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "AddUser"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x8C229B19; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 4; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::AddUser; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<4>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<4>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x6186CA22; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<5>
{
  using func_ptr_type = void (Game::*)(DDSKey);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "RemoveUser"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xFEC3C304; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 5; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::RemoveUser; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<5>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x6186CA22; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<6>
{
  using func_ptr_type = void (Game::*)(DDSKey, bool);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "ChangeReady"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x513A1CDC; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 6; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::ChangeReady; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<6>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x6186CA22; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<6>::param_info<1>
{
  using param_type = bool;
  static constexpr auto GetName() { return "ready"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetNameHash() { return 0x289585AF; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<7>
{
  using func_ptr_type = void (Game::*)();
  using return_type = void;
  static constexpr int params_n = 0;
  static constexpr auto GetName() { return "StartGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x40E81A4D; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 7; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::StartGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<8>
{
  using func_ptr_type = void (Game::*)(DDSKey);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "RequestStartGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x8C32C475; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 8; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::RequestStartGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<8>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x6186CA22; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<9>
{
  using func_ptr_type = void (Game::*)();
  using return_type = void;
  static constexpr int params_n = 0;
  static constexpr auto GetName() { return "RandomizeTeams"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x26B146D3; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 9; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::RandomizeTeams; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<10>
{
  using func_ptr_type = void (Game::*)(DDSKey, DDSKey, std::string, std::string);
  using return_type = void;
  static constexpr int params_n = 4;
  static constexpr auto GetName() { return "SendChat"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xDDA27521; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 10; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::SendChat; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<10>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x6186CA22; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<10>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<10>::param_info<2>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "message"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xB6BD307F; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<10>::param_info<3>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "title"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x2B36786B; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<11>
{
  using func_ptr_type = void (Game::*)(DDSKey, GameInitSettings);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "UpdateSettings"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xE2AE42CF; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 11; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::UpdateSettings; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<11>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x6186CA22; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<11>::param_info<1>
{
  using param_type = GameInitSettings;
  static constexpr auto GetName() { return "settings"; }
  static constexpr auto GetType() { return "GameInitSettings"; }
  static constexpr unsigned GetNameHash() { return 0xE545A0C5; }
  static constexpr unsigned GetTypeNameHash() { return 0xBAC6DD28; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<12>
{
  using func_ptr_type = void (Game::*)();
  using return_type = void;
  static constexpr int params_n = 0;
  static constexpr auto GetName() { return "UpdateGameList"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xB520BF13; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 12; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::UpdateGameList; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<13>
{
  using func_ptr_type = void (Game::*)(DDSKey, DDSKey, uint32_t, DDSKey);
  using return_type = void;
  static constexpr int params_n = 4;
  static constexpr auto GetName() { return "RedeemToken"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xD02F62AE; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 13; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::RedeemToken; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<13>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x6186CA22; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<13>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "token"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x5F37A13B; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<13>::param_info<2>
{
  using param_type = uint32_t;
  static constexpr auto GetName() { return "response_id"; }
  static constexpr auto GetType() { return "uint32_t"; }
  static constexpr unsigned GetNameHash() { return 0xFBF32840; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E2AF381; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<13>::param_info<3>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "server_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xB459A1F3; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<14>
{
  using func_ptr_type = void (Game::*)(DDSKey);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "ExpireToken"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x6D1B9FA1; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 14; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::ExpireToken; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<14>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "token"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x5F37A13B; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<15>
{
  using func_ptr_type = void (Game::*)(DDSKey, std::string);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "HandleMemberUpdate"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x4E85F53F; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 15; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::HandleMemberUpdate; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<15>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x6186CA22; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<15>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "data"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xADF3F363; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

namespace StormReflFileInfo
{
  struct Game
  {
    static const int types_n = 2;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct Game::type_info<0>
  {
    using type = ::GameToken;
  };

  template <>
  struct Game::type_info<1>
  {
    using type = ::Game;
  };

}

