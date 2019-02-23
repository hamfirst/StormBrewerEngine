#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "BotConnection.refl.h"


template <>
struct StormReflEnumInfo<BotConnectionState>
{
  static constexpr int elems_n = 3;
  static constexpr auto GetName() { return "BotConnectionState"; }
  static constexpr auto GetNameHash() { return 0xC003F84C; }
  template <int N> struct elems { };
};

template <>
struct StormReflEnumInfo<BotConnectionState>::elems<0>
{
  static constexpr auto GetName() { return "kWaitingForConnection"; }
  static constexpr auto GetNameHash() { return 0x3A061D29; }
  static constexpr auto GetValue() { return BotConnectionState::kWaitingForConnection; }
};

template <>
struct StormReflEnumInfo<BotConnectionState>::elems<1>
{
  static constexpr auto GetName() { return "kAuthenticating"; }
  static constexpr auto GetNameHash() { return 0xC9B5A1FD; }
  static constexpr auto GetValue() { return BotConnectionState::kAuthenticating; }
};

template <>
struct StormReflEnumInfo<BotConnectionState>::elems<2>
{
  static constexpr auto GetName() { return "kConnected"; }
  static constexpr auto GetNameHash() { return 0xB4C21949; }
  static constexpr auto GetValue() { return BotConnectionState::kConnected; }
};

template <>
struct StormReflTypeInfo<BotConnection>
{
  using MyBase = void;
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "BotConnection"; }
  static constexpr auto GetNameHash() { return 0x43B8A8AA; }
  static constexpr bool HasDefault() { return false; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<BotConnection *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const BotConnection *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<BotConnection *>(ptr);
    if(typeid(BotConnection).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const BotConnection *>(ptr);
    if(typeid(BotConnection).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<BotConnection>::field_data_static<0>
{
  using member_type = BotConnectionState; // BotConnectionState
  static constexpr auto GetName() { return "m_State"; }
  static constexpr auto GetType() { return "BotConnectionState"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2EA5429B; }
  static constexpr unsigned GetTypeNameHash() { return 0xC003F84C; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &BotConnection::m_State; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<BotConnection *>(obj); return &ptr->m_State; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const BotConnection *>(obj); return &ptr->m_State; }
};

template <typename Self>
struct StormReflTypeInfo<BotConnection>::field_data<0, Self> : public StormReflTypeInfo<BotConnection>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, BotConnectionState> & Get() { return self.m_State; }
  std::add_const_t<std::remove_reference_t<BotConnectionState>> & Get() const { return self.m_State; }
};

template <>
struct StormReflTypeInfo<BotConnection>::field_data_static<1>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_Error"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD0EB2C11; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &BotConnection::m_Error; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<BotConnection *>(obj); return &ptr->m_Error; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const BotConnection *>(obj); return &ptr->m_Error; }
};

template <typename Self>
struct StormReflTypeInfo<BotConnection>::field_data<1, Self> : public StormReflTypeInfo<BotConnection>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_Error; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_Error; }
};

template <>
struct StormReflTypeInfo<BotConnection>::field_data_static<2>
{
  using member_type = std::vector<std::string>; // std::vector<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::allocator<std::basic_string<char, std::char_traits<char>, std::allocator<char> > > >
  static constexpr auto GetName() { return "m_PendingMessages"; }
  static constexpr auto GetType() { return "std::vector<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::allocator<std::basic_string<char, std::char_traits<char>, std::allocator<char> > > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2C42FDAA; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F698566; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &BotConnection::m_PendingMessages; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<BotConnection *>(obj); return &ptr->m_PendingMessages; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const BotConnection *>(obj); return &ptr->m_PendingMessages; }
};

template <typename Self>
struct StormReflTypeInfo<BotConnection>::field_data<2, Self> : public StormReflTypeInfo<BotConnection>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<std::string>> & Get() { return self.m_PendingMessages; }
  std::add_const_t<std::remove_reference_t<std::vector<std::string>>> & Get() const { return self.m_PendingMessages; }
};

template <>
struct StormReflTypeInfo<BotConnection>::field_data_static<3>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_BotId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF33F3584; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &BotConnection::m_BotId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<BotConnection *>(obj); return &ptr->m_BotId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const BotConnection *>(obj); return &ptr->m_BotId; }
};

template <typename Self>
struct StormReflTypeInfo<BotConnection>::field_data<3, Self> : public StormReflTypeInfo<BotConnection>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_BotId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_BotId; }
};

template <>
struct StormReflFuncInfo<BotConnection>
{
  using MyBase = void;
  static constexpr int funcs_n = 5;
  template <int N> struct func_data_static {};
};

template <>
struct StormReflFuncInfo<BotConnection>::func_data_static<0>
{
  using func_ptr_type = void (BotConnection::*)(std::string, std::string);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "LoadBot"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x3160D8B6; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 0; }
  static constexpr func_ptr_type GetFunctionPtr() { return &BotConnection::LoadBot; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<BotConnection>::func_data_static<0>::param_info<0>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "user_name"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x24A232CF; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<BotConnection>::func_data_static<0>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "password"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x35C246D5; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<BotConnection>::func_data_static<1>
{
  using func_ptr_type = void (BotConnection::*)(std::string, std::string);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "GotMessage"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xD040732D; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 1; }
  static constexpr func_ptr_type GetFunctionPtr() { return &BotConnection::GotMessage; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<BotConnection>::func_data_static<1>::param_info<0>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "cmd"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x2F5C1CC0; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<BotConnection>::func_data_static<1>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "data"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xADF3F363; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<BotConnection>::func_data_static<2>
{
  using func_ptr_type = void (BotConnection::*)(bool);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "HandleBotLoad"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x21EBEA97; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 2; }
  static constexpr func_ptr_type GetFunctionPtr() { return &BotConnection::HandleBotLoad; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<BotConnection>::func_data_static<2>::param_info<0>
{
  using param_type = bool;
  static constexpr auto GetName() { return "success"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetNameHash() { return 0x6F00DFB2; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
};

template <>
struct StormReflFuncInfo<BotConnection>::func_data_static<3>
{
  using func_ptr_type = void (BotConnection::*)();
  using return_type = void;
  static constexpr int params_n = 0;
  static constexpr auto GetName() { return "HandleBotLoadFail"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x53143265; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 3; }
  static constexpr func_ptr_type GetFunctionPtr() { return &BotConnection::HandleBotLoadFail; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<BotConnection>::func_data_static<4>
{
  using func_ptr_type = void (BotConnection::*)(std::string);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "SendData"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x15CC74E8; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 4; }
  static constexpr func_ptr_type GetFunctionPtr() { return &BotConnection::SendData; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<BotConnection>::func_data_static<4>::param_info<0>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "data"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xADF3F363; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

namespace StormReflFileInfo
{
  struct BotConnection
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct BotConnection::type_info<0>
  {
    using type = ::BotConnection;
  };

}

