#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "Channel.refl.h"
#include "SharedTypes.refl.meta.h"
#include "Squad.refl.meta.h"
#include "BuiltInChannel.refl.meta.h"


template <>
struct StormReflEnumInfo<ChannelState>
{
  static constexpr int elems_n = 6;
  static constexpr auto GetName() { return "ChannelState"; }
  static constexpr auto GetNameHash() { return 0xBB12F562; }
  template <int N> struct elems { };
};

template <>
struct StormReflEnumInfo<ChannelState>::elems<0>
{
  static constexpr auto GetName() { return "kCheckingForBuiltIn"; }
  static constexpr auto GetNameHash() { return 0x7732287C; }
  static constexpr auto GetValue() { return ChannelState::kCheckingForBuiltIn; }
};

template <>
struct StormReflEnumInfo<ChannelState>::elems<1>
{
  static constexpr auto GetName() { return "kCheckingForSquad"; }
  static constexpr auto GetNameHash() { return 0xA766EA56; }
  static constexpr auto GetValue() { return ChannelState::kCheckingForSquad; }
};

template <>
struct StormReflEnumInfo<ChannelState>::elems<2>
{
  static constexpr auto GetName() { return "kWaitingForFirstMember"; }
  static constexpr auto GetNameHash() { return 0x3A43B8B7; }
  static constexpr auto GetValue() { return ChannelState::kWaitingForFirstMember; }
};

template <>
struct StormReflEnumInfo<ChannelState>::elems<3>
{
  static constexpr auto GetName() { return "kTemporary"; }
  static constexpr auto GetNameHash() { return 0x3BEAF2C0; }
  static constexpr auto GetValue() { return ChannelState::kTemporary; }
};

template <>
struct StormReflEnumInfo<ChannelState>::elems<4>
{
  static constexpr auto GetName() { return "kBuiltIn"; }
  static constexpr auto GetNameHash() { return 0x5D43BEBE; }
  static constexpr auto GetValue() { return ChannelState::kBuiltIn; }
};

template <>
struct StormReflEnumInfo<ChannelState>::elems<5>
{
  static constexpr auto GetName() { return "kSquad"; }
  static constexpr auto GetNameHash() { return 0x1BC279C4; }
  static constexpr auto GetValue() { return ChannelState::kSquad; }
};

template <>
struct StormReflTypeInfo<Channel>
{
  using MyBase = void;
  static constexpr int fields_n = 6;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "Channel"; }
  static constexpr auto GetNameHash() { return 0x6D44B7DB; }
  static constexpr bool HasDefault() { return false; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<Channel *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const Channel *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<Channel *>(ptr);
    if(typeid(Channel).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const Channel *>(ptr);
    if(typeid(Channel).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<Channel>::field_data_static<0>
{
  using member_type = REnum<ChannelState>; // REnum<ChannelState>
  static constexpr auto GetName() { return "m_State"; }
  static constexpr auto GetType() { return "REnum<ChannelState>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2EA5429B; }
  static constexpr unsigned GetTypeNameHash() { return 0xB97C8CFF; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &Channel::m_State; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<Channel *>(obj); return &ptr->m_State; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const Channel *>(obj); return &ptr->m_State; }
};

template <typename Self>
struct StormReflTypeInfo<Channel>::field_data<0, Self> : public StormReflTypeInfo<Channel>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, REnum<ChannelState>> & Get() { return self.m_State; }
  std::add_const_t<std::remove_reference_t<REnum<ChannelState>>> & Get() const { return self.m_State; }
};

template <>
struct StormReflTypeInfo<Channel>::field_data_static<1>
{
  using member_type = ChannelInfo; // ChannelInfo
  static constexpr auto GetName() { return "m_ChannelInfo"; }
  static constexpr auto GetType() { return "ChannelInfo"; }
  static constexpr unsigned GetFieldNameHash() { return 0x9E2A57B3; }
  static constexpr unsigned GetTypeNameHash() { return 0xFDE9DF80; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &Channel::m_ChannelInfo; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<Channel *>(obj); return &ptr->m_ChannelInfo; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const Channel *>(obj); return &ptr->m_ChannelInfo; }
};

template <typename Self>
struct StormReflTypeInfo<Channel>::field_data<1, Self> : public StormReflTypeInfo<Channel>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, ChannelInfo> & Get() { return self.m_ChannelInfo; }
  std::add_const_t<std::remove_reference_t<ChannelInfo>> & Get() const { return self.m_ChannelInfo; }
};

template <>
struct StormReflTypeInfo<Channel>::field_data_static<2>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_ChannelSubscription"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2341156C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &Channel::m_ChannelSubscription; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<Channel *>(obj); return &ptr->m_ChannelSubscription; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const Channel *>(obj); return &ptr->m_ChannelSubscription; }
};

template <typename Self>
struct StormReflTypeInfo<Channel>::field_data<2, Self> : public StormReflTypeInfo<Channel>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_ChannelSubscription; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_ChannelSubscription; }
};

template <>
struct StormReflTypeInfo<Channel>::field_data_static<3>
{
  using member_type = BuiltInChannelInfo; // BuiltInChannelInfo
  static constexpr auto GetName() { return "m_BuiltInChannelInfo"; }
  static constexpr auto GetType() { return "BuiltInChannelInfo"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD9310CF4; }
  static constexpr unsigned GetTypeNameHash() { return 0x357FEF68; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &Channel::m_BuiltInChannelInfo; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<Channel *>(obj); return &ptr->m_BuiltInChannelInfo; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const Channel *>(obj); return &ptr->m_BuiltInChannelInfo; }
};

template <typename Self>
struct StormReflTypeInfo<Channel>::field_data<3, Self> : public StormReflTypeInfo<Channel>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, BuiltInChannelInfo> & Get() { return self.m_BuiltInChannelInfo; }
  std::add_const_t<std::remove_reference_t<BuiltInChannelInfo>> & Get() const { return self.m_BuiltInChannelInfo; }
};

template <>
struct StormReflTypeInfo<Channel>::field_data_static<4>
{
  using member_type = SquadDatabaseInfo; // SquadDatabaseInfo
  static constexpr auto GetName() { return "m_SquadInfo"; }
  static constexpr auto GetType() { return "SquadDatabaseInfo"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC848E820; }
  static constexpr unsigned GetTypeNameHash() { return 0x743E9D4A; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &Channel::m_SquadInfo; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<Channel *>(obj); return &ptr->m_SquadInfo; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const Channel *>(obj); return &ptr->m_SquadInfo; }
};

template <typename Self>
struct StormReflTypeInfo<Channel>::field_data<4, Self> : public StormReflTypeInfo<Channel>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, SquadDatabaseInfo> & Get() { return self.m_SquadInfo; }
  std::add_const_t<std::remove_reference_t<SquadDatabaseInfo>> & Get() const { return self.m_SquadInfo; }
};

template <>
struct StormReflTypeInfo<Channel>::field_data_static<5>
{
  using member_type = std::map<DDSKey, DDSKey>; // std::map<unsigned long, unsigned long, std::less<unsigned long>, std::allocator<std::pair<const unsigned long, unsigned long> > >
  static constexpr auto GetName() { return "m_MemberSubscriptionIds"; }
  static constexpr auto GetType() { return "std::map<unsigned long, unsigned long, std::less<unsigned long>, std::allocator<std::pair<const unsigned long, unsigned long> > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8369B12E; }
  static constexpr unsigned GetTypeNameHash() { return 0x9D5C622D; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &Channel::m_MemberSubscriptionIds; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<Channel *>(obj); return &ptr->m_MemberSubscriptionIds; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const Channel *>(obj); return &ptr->m_MemberSubscriptionIds; }
};

template <typename Self>
struct StormReflTypeInfo<Channel>::field_data<5, Self> : public StormReflTypeInfo<Channel>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::map<DDSKey, DDSKey>> & Get() { return self.m_MemberSubscriptionIds; }
  std::add_const_t<std::remove_reference_t<std::map<DDSKey, DDSKey>>> & Get() const { return self.m_MemberSubscriptionIds; }
};

template <>
struct StormReflFuncInfo<Channel>
{
  using MyBase = void;
  static constexpr int funcs_n = 15;
  template <int N> struct func_data_static {};
};

template <>
struct StormReflFuncInfo<Channel>::func_data_static<0>
{
  using func_ptr_type = void (Channel::*)(DDSResponder &, DDSKey, int, std::string);
  using return_type = void;
  static constexpr int params_n = 4;
  static constexpr auto GetName() { return "AddUser"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x8C229B19; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 0; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Channel::AddUser; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Channel>::func_data_static<0>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<Channel>::func_data_static<0>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x6186CA22; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Channel>::func_data_static<0>::param_info<2>
{
  using param_type = int;
  static constexpr auto GetName() { return "admin_level"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x3AC037E9; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<Channel>::func_data_static<0>::param_info<3>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "channel_name"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xC277DD78; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<Channel>::func_data_static<1>
{
  using func_ptr_type = void (Channel::*)(DDSKey);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "RemoveUser"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xFEC3C304; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 1; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Channel::RemoveUser; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Channel>::func_data_static<1>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x6186CA22; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Channel>::func_data_static<2>
{
  using func_ptr_type = void (Channel::*)(DDSKey, DDSKey, DDSKey, int);
  using return_type = void;
  static constexpr int params_n = 4;
  static constexpr auto GetName() { return "KickUser"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x639C9527; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 2; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Channel::KickUser; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Channel>::func_data_static<2>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Channel>::func_data_static<2>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x6186CA22; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Channel>::func_data_static<2>::param_info<2>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "src_user"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xA4FEA4A3; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Channel>::func_data_static<2>::param_info<3>
{
  using param_type = int;
  static constexpr auto GetName() { return "src_admin_level"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x67623132; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<Channel>::func_data_static<3>
{
  using func_ptr_type = void (Channel::*)(DDSKey, DDSKey, std::string, int);
  using return_type = void;
  static constexpr int params_n = 4;
  static constexpr auto GetName() { return "SendChatToChannel"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x3FFA1AC4; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 3; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Channel::SendChatToChannel; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Channel>::func_data_static<3>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x6186CA22; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Channel>::func_data_static<3>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Channel>::func_data_static<3>::param_info<2>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "message"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xB6BD307F; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<Channel>::func_data_static<3>::param_info<3>
{
  using param_type = int;
  static constexpr auto GetName() { return "title"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x2B36786B; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<Channel>::func_data_static<4>
{
  using func_ptr_type = void (Channel::*)(DDSKey, std::string);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "AddBot"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x6B235250; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 4; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Channel::AddBot; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Channel>::func_data_static<4>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "bot_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x920A147D; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Channel>::func_data_static<4>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "user_name"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x24A232CF; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<Channel>::func_data_static<5>
{
  using func_ptr_type = void (Channel::*)(DDSKey);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "RemoveBot"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x8D1CCA96; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 5; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Channel::RemoveBot; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Channel>::func_data_static<5>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "bot_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x920A147D; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Channel>::func_data_static<6>
{
  using func_ptr_type = void (Channel::*)(DDSKey, std::string);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "SendBotChatToChannel"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x04584812; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 6; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Channel::SendBotChatToChannel; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Channel>::func_data_static<6>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "bot_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x920A147D; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Channel>::func_data_static<6>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "message"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xB6BD307F; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<Channel>::func_data_static<7>
{
  using func_ptr_type = void (Channel::*)();
  using return_type = void;
  static constexpr int params_n = 0;
  static constexpr auto GetName() { return "HandleSquadDoesntExist"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x34F5A228; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 7; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Channel::HandleSquadDoesntExist; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Channel>::func_data_static<8>
{
  using func_ptr_type = void (Channel::*)();
  using return_type = void;
  static constexpr int params_n = 0;
  static constexpr auto GetName() { return "HandleBuiltinDoesntExist"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xFE37A21F; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 8; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Channel::HandleBuiltinDoesntExist; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Channel>::func_data_static<9>
{
  using func_ptr_type = void (Channel::*)(std::string);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "HandleBuiltInChannelUpdate"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xCAA20178; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 9; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Channel::HandleBuiltInChannelUpdate; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Channel>::func_data_static<9>::param_info<0>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "data"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xADF3F363; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<Channel>::func_data_static<10>
{
  using func_ptr_type = void (Channel::*)(std::string);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "HandleSquadUpdate"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xF40468FF; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 10; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Channel::HandleSquadUpdate; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Channel>::func_data_static<10>::param_info<0>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "data"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xADF3F363; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<Channel>::func_data_static<11>
{
  using func_ptr_type = void (Channel::*)(DDSKey, std::string);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "HandleMemberUpdate"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x4E85F53F; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 11; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Channel::HandleMemberUpdate; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Channel>::func_data_static<11>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x6186CA22; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Channel>::func_data_static<11>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "data"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xADF3F363; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<Channel>::func_data_static<12>
{
  using func_ptr_type = void (Channel::*)(DDSResponder &);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "FetchChannelMotd"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x79A1854C; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 12; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Channel::FetchChannelMotd; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Channel>::func_data_static<12>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<Channel>::func_data_static<13>
{
  using func_ptr_type = void (Channel::*)(DDSResponder &, std::string);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "UpdateChannelMotd"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x4CF42B23; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 13; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Channel::UpdateChannelMotd; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Channel>::func_data_static<13>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<Channel>::func_data_static<13>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "motd"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xAA0F656C; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<Channel>::func_data_static<14>
{
  using func_ptr_type = void (Channel::*)(DDSResponder &);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "GetInfo"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x02540D1A; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 14; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Channel::GetInfo; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Channel>::func_data_static<14>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

namespace StormReflFileInfo
{
  struct Channel
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct Channel::type_info<0>
  {
    using type = ::Channel;
  };

}

