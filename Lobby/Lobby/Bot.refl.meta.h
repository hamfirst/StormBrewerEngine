#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "Bot.refl.h"
#include "HurricaneDDS/DDSThrottle.refl.meta.h"
#include "SharedTypes.refl.meta.h"
#include "GameData.refl.meta.h"
#include "GameServerMessages.refl.meta.h"


template <>
struct StormReflTypeInfo<BotDatabaseObject>
{
  using MyBase = void;
  static constexpr int fields_n = 5;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "BotDatabaseObject"; }
  static constexpr auto GetNameHash() { return 0x3DE0625C; }
  static BotDatabaseObject & GetDefault() { static BotDatabaseObject def; return def; }
};

template <>
struct StormReflTypeInfo<BotDatabaseObject>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_UserName"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAE407D67; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &BotDatabaseObject::m_UserName; }
};

template <typename Self>
struct StormReflTypeInfo<BotDatabaseObject>::field_data<0, Self> : public StormReflTypeInfo<BotDatabaseObject>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_UserName; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_UserName; }
  void SetDefault() { self.m_UserName = StormReflTypeInfo<BotDatabaseObject>::GetDefault().m_UserName; }
};

template <>
struct StormReflTypeInfo<BotDatabaseObject>::field_data_static<1>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_UserNameLower"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3D029B9C; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &BotDatabaseObject::m_UserNameLower; }
};

template <typename Self>
struct StormReflTypeInfo<BotDatabaseObject>::field_data<1, Self> : public StormReflTypeInfo<BotDatabaseObject>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_UserNameLower; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_UserNameLower; }
  void SetDefault() { self.m_UserNameLower = StormReflTypeInfo<BotDatabaseObject>::GetDefault().m_UserNameLower; }
};

template <>
struct StormReflTypeInfo<BotDatabaseObject>::annotations<1>
{
  static constexpr int annotations_n = 1;
  template <int A> struct annoation { };
};

template <>
struct StormReflTypeInfo<BotDatabaseObject>::annotations<1>::annoation<0>
{
  static constexpr const char * GetAnnotation() { return "UniqueIndex"; }
  static constexpr uint32_t GetAnnotationHash() { return 0x5C838CC5; }
};

template <>
struct StormReflTypeInfo<BotDatabaseObject>::field_data_static<2>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Password"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC3EE92FB; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &BotDatabaseObject::m_Password; }
};

template <typename Self>
struct StormReflTypeInfo<BotDatabaseObject>::field_data<2, Self> : public StormReflTypeInfo<BotDatabaseObject>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Password; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Password; }
  void SetDefault() { self.m_Password = StormReflTypeInfo<BotDatabaseObject>::GetDefault().m_Password; }
};

template <>
struct StormReflTypeInfo<BotDatabaseObject>::field_data_static<3>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Channel"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x370BFB92; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &BotDatabaseObject::m_Channel; }
};

template <typename Self>
struct StormReflTypeInfo<BotDatabaseObject>::field_data<3, Self> : public StormReflTypeInfo<BotDatabaseObject>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Channel; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Channel; }
  void SetDefault() { self.m_Channel = StormReflTypeInfo<BotDatabaseObject>::GetDefault().m_Channel; }
};

template <>
struct StormReflTypeInfo<BotDatabaseObject>::field_data_static<4>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_WelcomeInfoTab"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x84AB0A93; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &BotDatabaseObject::m_WelcomeInfoTab; }
};

template <typename Self>
struct StormReflTypeInfo<BotDatabaseObject>::field_data<4, Self> : public StormReflTypeInfo<BotDatabaseObject>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_WelcomeInfoTab; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_WelcomeInfoTab; }
  void SetDefault() { self.m_WelcomeInfoTab = StormReflTypeInfo<BotDatabaseObject>::GetDefault().m_WelcomeInfoTab; }
};

template <>
struct StormReflTypeInfo<Bot>
{
  using MyBase = void;
  static constexpr int fields_n = 5;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "Bot"; }
  static constexpr auto GetNameHash() { return 0x395242F1; }
};

template <>
struct StormReflTypeInfo<Bot>::field_data_static<0>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_HasChannelInfo"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x629E7450; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &Bot::m_HasChannelInfo; }
};

template <typename Self>
struct StormReflTypeInfo<Bot>::field_data<0, Self> : public StormReflTypeInfo<Bot>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_HasChannelInfo; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_HasChannelInfo; }
};

template <>
struct StormReflTypeInfo<Bot>::field_data_static<1>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_ChannelKey"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2CD0601E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &Bot::m_ChannelKey; }
};

template <typename Self>
struct StormReflTypeInfo<Bot>::field_data<1, Self> : public StormReflTypeInfo<Bot>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_ChannelKey; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_ChannelKey; }
};

template <>
struct StormReflTypeInfo<Bot>::field_data_static<2>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_EndpointKey"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x106C51AB; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &Bot::m_EndpointKey; }
};

template <typename Self>
struct StormReflTypeInfo<Bot>::field_data<2, Self> : public StormReflTypeInfo<Bot>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_EndpointKey; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_EndpointKey; }
};

template <>
struct StormReflTypeInfo<Bot>::field_data_static<3>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_ChannelSubscriptionId"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8E28A0F3; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &Bot::m_ChannelSubscriptionId; }
};

template <typename Self>
struct StormReflTypeInfo<Bot>::field_data<3, Self> : public StormReflTypeInfo<Bot>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_ChannelSubscriptionId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_ChannelSubscriptionId; }
};

template <>
struct StormReflTypeInfo<Bot>::field_data_static<4>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_ServerListSubscriptionId"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xEBF8AFBA; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &Bot::m_ServerListSubscriptionId; }
};

template <typename Self>
struct StormReflTypeInfo<Bot>::field_data<4, Self> : public StormReflTypeInfo<Bot>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_ServerListSubscriptionId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_ServerListSubscriptionId; }
};

template <>
struct StormReflFuncInfo<Bot>
{
  static constexpr int funcs_n = 14;
  template <int N> struct func_data_static {};
};

template <>
struct StormReflFuncInfo<Bot>::func_data_static<0>
{
  using func_ptr_type = void (Bot::*)(DDSResponder &, DDSKey, std::string, std::string);
  using return_type = void;
  static constexpr int params_n = 4;
  static constexpr auto GetName() { return "AddEndpoint"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xFDD4B125; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 0; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Bot::AddEndpoint; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Bot>::func_data_static<0>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<Bot>::func_data_static<0>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x8A90ABA9; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Bot>::func_data_static<0>::param_info<2>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "user_name"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x24A232CF; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<Bot>::func_data_static<0>::param_info<3>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "password"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x35C246D5; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<Bot>::func_data_static<1>
{
  using func_ptr_type = void (Bot::*)(DDSKey);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "RemoveEndpoint"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xC46693D2; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 1; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Bot::RemoveEndpoint; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Bot>::func_data_static<1>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x8A90ABA9; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Bot>::func_data_static<2>
{
  using func_ptr_type = void (Bot::*)(DDSKey, DDSKey, std::string, std::string);
  using return_type = void;
  static constexpr int params_n = 4;
  static constexpr auto GetName() { return "GotChat"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x0DDBED81; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 2; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Bot::GotChat; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Bot>::func_data_static<2>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xA76ED395; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Bot>::func_data_static<2>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Bot>::func_data_static<2>::param_info<2>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "user_name"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x24A232CF; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<Bot>::func_data_static<2>::param_info<3>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "message"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xB6BD307F; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<Bot>::func_data_static<3>
{
  using func_ptr_type = void (Bot::*)(std::string);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "HandleChannelUpdate"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x58A6FC95; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 3; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Bot::HandleChannelUpdate; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Bot>::func_data_static<3>::param_info<0>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "data"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xADF3F363; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<Bot>::func_data_static<4>
{
  using func_ptr_type = void (Bot::*)(std::string);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "HandleServerListUpdate"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x18C4F9FE; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 4; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Bot::HandleServerListUpdate; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Bot>::func_data_static<4>::param_info<0>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "data"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xADF3F363; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<Bot>::func_data_static<5>
{
  using func_ptr_type = void (Bot::*)(std::string);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "SendChatToChannel"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x3FFA1AC4; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 5; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Bot::SendChatToChannel; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Bot>::func_data_static<5>::param_info<0>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "message"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xB6BD307F; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<Bot>::func_data_static<6>
{
  using func_ptr_type = void (Bot::*)(DDSKey, std::string);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "SendChatToUser"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xAEAB6374; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 6; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Bot::SendChatToUser; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Bot>::func_data_static<6>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xA76ED395; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Bot>::func_data_static<6>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "message"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xB6BD307F; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<Bot>::func_data_static<7>
{
  using func_ptr_type = void (Bot::*)(DDSKey, std::string);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "SendChatToEndpoint"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xB06EDE75; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 7; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Bot::SendChatToEndpoint; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Bot>::func_data_static<7>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Bot>::func_data_static<7>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "message"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xB6BD307F; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<Bot>::func_data_static<8>
{
  using func_ptr_type = void (Bot::*)(std::string);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "SetChannelMotd"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x49A97E10; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 8; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Bot::SetChannelMotd; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Bot>::func_data_static<8>::param_info<0>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "motd"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xAA0F656C; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<Bot>::func_data_static<9>
{
  using func_ptr_type = void (Bot::*)(DDSResponder &, std::string);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "SetWelcomeInfoTab"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x9D501059; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 9; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Bot::SetWelcomeInfoTab; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Bot>::func_data_static<9>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<Bot>::func_data_static<9>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "tab"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x73E3430C; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<Bot>::func_data_static<10>
{
  using func_ptr_type = void (Bot::*)(std::string);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "UpdateWelcomeInfo"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xEBDD5ACF; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 10; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Bot::UpdateWelcomeInfo; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Bot>::func_data_static<10>::param_info<0>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "info"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xCB893157; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<Bot>::func_data_static<11>
{
  using func_ptr_type = void (Bot::*)(std::string);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "HandleWelcomeInfoUpdateResponse"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x4BEE58F9; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 11; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Bot::HandleWelcomeInfoUpdateResponse; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Bot>::func_data_static<11>::param_info<0>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "data"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xADF3F363; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<Bot>::func_data_static<12>
{
  using func_ptr_type = void (Bot::*)(GameServerGameResult, DDSKey);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "ProcessGameResult"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x1AE683E9; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 12; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Bot::ProcessGameResult; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Bot>::func_data_static<12>::param_info<0>
{
  using param_type = GameServerGameResult;
  static constexpr auto GetName() { return "result"; }
  static constexpr auto GetType() { return "GameServerGameResult"; }
  static constexpr unsigned GetNameHash() { return 0x136AC113; }
  static constexpr unsigned GetTypeNameHash() { return 0x63B1A2A0; }
};

template <>
struct StormReflFuncInfo<Bot>::func_data_static<12>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Bot>::func_data_static<13>
{
  using func_ptr_type = void (Bot::*)(DDSResponder &);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "GetInfo"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x02540D1A; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 13; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Bot::GetInfo; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Bot>::func_data_static<13>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

namespace StormReflFileInfo
{
  struct Bot
  {
    static const int types_n = 2;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct Bot::type_info<0>
  {
    using type = ::BotDatabaseObject;
  };

  template <>
  struct Bot::type_info<1>
  {
    using type = ::Bot;
  };

}

