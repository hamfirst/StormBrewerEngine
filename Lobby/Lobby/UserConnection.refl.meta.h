#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "UserConnection.refl.h"


template <>
struct StormReflEnumInfo<UserConnectionState>
{
  static constexpr int elems_n = 4;
  static constexpr auto GetName() { return "UserConnectionState"; }
  static constexpr auto GetNameHash() { return 0xE0DA4082; }
  template <int N> struct elems { };
};

template <>
struct StormReflEnumInfo<UserConnectionState>::elems<0>
{
  static constexpr auto GetName() { return "kLoadingUser"; }
  static constexpr auto GetNameHash() { return 0xCA358B30; }
  static constexpr auto GetValue() { return UserConnectionState::kLoadingUser; }
};

template <>
struct StormReflEnumInfo<UserConnectionState>::elems<1>
{
  static constexpr auto GetName() { return "kRequestingUserName"; }
  static constexpr auto GetNameHash() { return 0x79965D49; }
  static constexpr auto GetValue() { return UserConnectionState::kRequestingUserName; }
};

template <>
struct StormReflEnumInfo<UserConnectionState>::elems<2>
{
  static constexpr auto GetName() { return "kCreatingNewUser"; }
  static constexpr auto GetNameHash() { return 0xD911358F; }
  static constexpr auto GetValue() { return UserConnectionState::kCreatingNewUser; }
};

template <>
struct StormReflEnumInfo<UserConnectionState>::elems<3>
{
  static constexpr auto GetName() { return "kLoaded"; }
  static constexpr auto GetNameHash() { return 0xE93424D3; }
  static constexpr auto GetValue() { return UserConnectionState::kLoaded; }
};

template <>
struct StormReflTypeInfo<UserConnection>
{
  using MyBase = void;
  static constexpr int fields_n = 12;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserConnection"; }
  static constexpr auto GetNameHash() { return 0xE6B22497; }
  static constexpr bool HasDefault() { return false; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<UserConnection *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const UserConnection *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<UserConnection *>(ptr);
    if(typeid(UserConnection).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const UserConnection *>(ptr);
    if(typeid(UserConnection).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<UserConnection>::field_data_static<0>
{
  using member_type = uint64_t; // unsigned long
  static constexpr auto GetName() { return "m_PlatformId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0ED94F3C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserConnection::m_PlatformId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserConnection *>(obj); return &ptr->m_PlatformId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserConnection *>(obj); return &ptr->m_PlatformId; }
};

template <typename Self>
struct StormReflTypeInfo<UserConnection>::field_data<0, Self> : public StormReflTypeInfo<UserConnection>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint64_t> & Get() { return self.m_PlatformId; }
  std::add_const_t<std::remove_reference_t<uint64_t>> & Get() const { return self.m_PlatformId; }
};

template <>
struct StormReflTypeInfo<UserConnection>::field_data_static<1>
{
  using member_type = uint64_t; // unsigned long
  static constexpr auto GetName() { return "m_UserId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x29891A04; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserConnection::m_UserId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserConnection *>(obj); return &ptr->m_UserId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserConnection *>(obj); return &ptr->m_UserId; }
};

template <typename Self>
struct StormReflTypeInfo<UserConnection>::field_data<1, Self> : public StormReflTypeInfo<UserConnection>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint64_t> & Get() { return self.m_UserId; }
  std::add_const_t<std::remove_reference_t<uint64_t>> & Get() const { return self.m_UserId; }
};

template <>
struct StormReflTypeInfo<UserConnection>::field_data_static<2>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_GamePreviewServerId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD9A1366A; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UserConnection::m_GamePreviewServerId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserConnection *>(obj); return &ptr->m_GamePreviewServerId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserConnection *>(obj); return &ptr->m_GamePreviewServerId; }
};

template <typename Self>
struct StormReflTypeInfo<UserConnection>::field_data<2, Self> : public StormReflTypeInfo<UserConnection>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_GamePreviewServerId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_GamePreviewServerId; }
};

template <>
struct StormReflTypeInfo<UserConnection>::field_data_static<3>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_GamePreviewSubscription"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6172774D; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &UserConnection::m_GamePreviewSubscription; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserConnection *>(obj); return &ptr->m_GamePreviewSubscription; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserConnection *>(obj); return &ptr->m_GamePreviewSubscription; }
};

template <typename Self>
struct StormReflTypeInfo<UserConnection>::field_data<3, Self> : public StormReflTypeInfo<UserConnection>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_GamePreviewSubscription; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_GamePreviewSubscription; }
};

template <>
struct StormReflTypeInfo<UserConnection>::field_data_static<4>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_GamePreviewRequestId"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x21415485; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &UserConnection::m_GamePreviewRequestId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserConnection *>(obj); return &ptr->m_GamePreviewRequestId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserConnection *>(obj); return &ptr->m_GamePreviewRequestId; }
};

template <typename Self>
struct StormReflTypeInfo<UserConnection>::field_data<4, Self> : public StormReflTypeInfo<UserConnection>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_GamePreviewRequestId; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_GamePreviewRequestId; }
};

template <>
struct StormReflTypeInfo<UserConnection>::field_data_static<5>
{
  using member_type = UserConnectionState; // UserConnectionState
  static constexpr auto GetName() { return "m_State"; }
  static constexpr auto GetType() { return "UserConnectionState"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2EA5429B; }
  static constexpr unsigned GetTypeNameHash() { return 0xE0DA4082; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &UserConnection::m_State; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserConnection *>(obj); return &ptr->m_State; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserConnection *>(obj); return &ptr->m_State; }
};

template <typename Self>
struct StormReflTypeInfo<UserConnection>::field_data<5, Self> : public StormReflTypeInfo<UserConnection>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, UserConnectionState> & Get() { return self.m_State; }
  std::add_const_t<std::remove_reference_t<UserConnectionState>> & Get() const { return self.m_State; }
};

template <>
struct StormReflTypeInfo<UserConnection>::field_data_static<6>
{
  using member_type = std::vector<std::string>; // std::vector<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::allocator<std::basic_string<char, std::char_traits<char>, std::allocator<char> > > >
  static constexpr auto GetName() { return "m_PendingMessages"; }
  static constexpr auto GetType() { return "std::vector<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::allocator<std::basic_string<char, std::char_traits<char>, std::allocator<char> > > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2C42FDAA; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F698566; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &UserConnection::m_PendingMessages; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserConnection *>(obj); return &ptr->m_PendingMessages; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserConnection *>(obj); return &ptr->m_PendingMessages; }
};

template <typename Self>
struct StormReflTypeInfo<UserConnection>::field_data<6, Self> : public StormReflTypeInfo<UserConnection>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<std::string>> & Get() { return self.m_PendingMessages; }
  std::add_const_t<std::remove_reference_t<std::vector<std::string>>> & Get() const { return self.m_PendingMessages; }
};

template <>
struct StormReflTypeInfo<UserConnection>::field_data_static<7>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_Error"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD0EB2C11; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &UserConnection::m_Error; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserConnection *>(obj); return &ptr->m_Error; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserConnection *>(obj); return &ptr->m_Error; }
};

template <typename Self>
struct StormReflTypeInfo<UserConnection>::field_data<7, Self> : public StormReflTypeInfo<UserConnection>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_Error; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_Error; }
};

template <>
struct StormReflTypeInfo<UserConnection>::field_data_static<8>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_RemoteIP"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xEB6C9948; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 8; }
  static constexpr auto GetMemberPtr() { return &UserConnection::m_RemoteIP; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserConnection *>(obj); return &ptr->m_RemoteIP; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserConnection *>(obj); return &ptr->m_RemoteIP; }
};

template <typename Self>
struct StormReflTypeInfo<UserConnection>::field_data<8, Self> : public StormReflTypeInfo<UserConnection>::field_data_static<8>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_RemoteIP; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_RemoteIP; }
};

template <>
struct StormReflTypeInfo<UserConnection>::field_data_static<9>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_RemoteHost"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x345B4DA6; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 9; }
  static constexpr auto GetMemberPtr() { return &UserConnection::m_RemoteHost; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserConnection *>(obj); return &ptr->m_RemoteHost; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserConnection *>(obj); return &ptr->m_RemoteHost; }
};

template <typename Self>
struct StormReflTypeInfo<UserConnection>::field_data<9, Self> : public StormReflTypeInfo<UserConnection>::field_data_static<9>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_RemoteHost; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_RemoteHost; }
};

template <>
struct StormReflTypeInfo<UserConnection>::field_data_static<10>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_CountryCode"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x443BB729; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 10; }
  static constexpr auto GetMemberPtr() { return &UserConnection::m_CountryCode; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserConnection *>(obj); return &ptr->m_CountryCode; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserConnection *>(obj); return &ptr->m_CountryCode; }
};

template <typename Self>
struct StormReflTypeInfo<UserConnection>::field_data<10, Self> : public StormReflTypeInfo<UserConnection>::field_data_static<10>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_CountryCode; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_CountryCode; }
};

template <>
struct StormReflTypeInfo<UserConnection>::field_data_static<11>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_CurrencyCode"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xEF446721; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 11; }
  static constexpr auto GetMemberPtr() { return &UserConnection::m_CurrencyCode; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserConnection *>(obj); return &ptr->m_CurrencyCode; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserConnection *>(obj); return &ptr->m_CurrencyCode; }
};

template <typename Self>
struct StormReflTypeInfo<UserConnection>::field_data<11, Self> : public StormReflTypeInfo<UserConnection>::field_data_static<11>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_CurrencyCode; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_CurrencyCode; }
};

template <>
struct StormReflFuncInfo<UserConnection>
{
  using MyBase = void;
  static constexpr int funcs_n = 16;
  template <int N> struct func_data_static {};
};

template <>
struct StormReflFuncInfo<UserConnection>::func_data_static<0>
{
  using func_ptr_type = void (UserConnection::*)(uint64_t, uint64_t, std::string, std::string, std::string, std::string);
  using return_type = void;
  static constexpr int params_n = 6;
  static constexpr auto GetName() { return "LoadUser"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xC5119FDE; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 0; }
  static constexpr func_ptr_type GetFunctionPtr() { return &UserConnection::LoadUser; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<UserConnection>::func_data_static<0>::param_info<0>
{
  using param_type = uint64_t;
  static constexpr auto GetName() { return "platform_id"; }
  static constexpr auto GetType() { return "uint64_t"; }
  static constexpr unsigned GetNameHash() { return 0xFFE6496F; }
  static constexpr unsigned GetTypeNameHash() { return 0x3D797F01; }
};

template <>
struct StormReflFuncInfo<UserConnection>::func_data_static<0>::param_info<1>
{
  using param_type = uint64_t;
  static constexpr auto GetName() { return "user_id"; }
  static constexpr auto GetType() { return "uint64_t"; }
  static constexpr unsigned GetNameHash() { return 0xA76ED395; }
  static constexpr unsigned GetTypeNameHash() { return 0x3D797F01; }
};

template <>
struct StormReflFuncInfo<UserConnection>::func_data_static<0>::param_info<2>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "remote_ip"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x30E448E9; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<UserConnection>::func_data_static<0>::param_info<3>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "remote_host"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x4ADEBF24; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<UserConnection>::func_data_static<0>::param_info<4>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "country_code"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xF026BB7C; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<UserConnection>::func_data_static<0>::param_info<5>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "currency_code"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xFDA273EC; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<UserConnection>::func_data_static<1>
{
  using func_ptr_type = void (UserConnection::*)(std::string, std::string);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "GotMessage"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xD040732D; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 1; }
  static constexpr func_ptr_type GetFunctionPtr() { return &UserConnection::GotMessage; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<UserConnection>::func_data_static<1>::param_info<0>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "cmd"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x2F5C1CC0; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<UserConnection>::func_data_static<1>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "data"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xADF3F363; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<UserConnection>::func_data_static<2>
{
  using func_ptr_type = void (UserConnection::*)();
  using return_type = void;
  static constexpr int params_n = 0;
  static constexpr auto GetName() { return "UserDoesntExist"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x34E69674; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 2; }
  static constexpr func_ptr_type GetFunctionPtr() { return &UserConnection::UserDoesntExist; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<UserConnection>::func_data_static<3>
{
  using func_ptr_type = void (UserConnection::*)(std::string);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "SendData"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x15CC74E8; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 3; }
  static constexpr func_ptr_type GetFunctionPtr() { return &UserConnection::SendData; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<UserConnection>::func_data_static<3>::param_info<0>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "data"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xADF3F363; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<UserConnection>::func_data_static<4>
{
  using func_ptr_type = void (UserConnection::*)(std::string);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "SendNotification"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x292FCD97; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 4; }
  static constexpr func_ptr_type GetFunctionPtr() { return &UserConnection::SendNotification; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<UserConnection>::func_data_static<4>::param_info<0>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "msg"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x688A5FAF; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<UserConnection>::func_data_static<5>
{
  using func_ptr_type = void (UserConnection::*)(std::string);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "SendServerText"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xFCAFD49F; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 5; }
  static constexpr func_ptr_type GetFunctionPtr() { return &UserConnection::SendServerText; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<UserConnection>::func_data_static<5>::param_info<0>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "msg"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x688A5FAF; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<UserConnection>::func_data_static<6>
{
  using func_ptr_type = void (UserConnection::*)(std::string);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "SendRuntimeError"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xEF0956C6; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 6; }
  static constexpr func_ptr_type GetFunctionPtr() { return &UserConnection::SendRuntimeError; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<UserConnection>::func_data_static<6>::param_info<0>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "msg"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x688A5FAF; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<UserConnection>::func_data_static<7>
{
  using func_ptr_type = void (UserConnection::*)(std::string);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "SendConnectionError"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xA3AB86E6; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 7; }
  static constexpr func_ptr_type GetFunctionPtr() { return &UserConnection::SendConnectionError; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<UserConnection>::func_data_static<7>::param_info<0>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "msg"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x688A5FAF; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<UserConnection>::func_data_static<8>
{
  using func_ptr_type = void (UserConnection::*)(std::string, int, uint64_t);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "SendLaunchGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xCDBB7E33; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 8; }
  static constexpr func_ptr_type GetFunctionPtr() { return &UserConnection::SendLaunchGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<UserConnection>::func_data_static<8>::param_info<0>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "ip_addr"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x41FDCEBA; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<UserConnection>::func_data_static<8>::param_info<1>
{
  using param_type = int;
  static constexpr auto GetName() { return "port"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x43915DCC; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<UserConnection>::func_data_static<8>::param_info<2>
{
  using param_type = uint64_t;
  static constexpr auto GetName() { return "token"; }
  static constexpr auto GetType() { return "uint64_t"; }
  static constexpr unsigned GetNameHash() { return 0x5F37A13B; }
  static constexpr unsigned GetTypeNameHash() { return 0x3D797F01; }
};

template <>
struct StormReflFuncInfo<UserConnection>::func_data_static<9>
{
  using func_ptr_type = void (UserConnection::*)(int);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "HandleUserInsert"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xC9892AD8; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 9; }
  static constexpr func_ptr_type GetFunctionPtr() { return &UserConnection::HandleUserInsert; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<UserConnection>::func_data_static<9>::param_info<0>
{
  using param_type = int;
  static constexpr auto GetName() { return "ec"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x8DE8BDFF; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<UserConnection>::func_data_static<10>
{
  using func_ptr_type = void (UserConnection::*)(std::string);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "HandleLocalDataUpdate"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x949DB6C0; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 10; }
  static constexpr func_ptr_type GetFunctionPtr() { return &UserConnection::HandleLocalDataUpdate; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<UserConnection>::func_data_static<10>::param_info<0>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "data"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xADF3F363; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<UserConnection>::func_data_static<11>
{
  using func_ptr_type = void (UserConnection::*)(std::string);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "HandleServerListUpdate"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x18C4F9FE; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 11; }
  static constexpr func_ptr_type GetFunctionPtr() { return &UserConnection::HandleServerListUpdate; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<UserConnection>::func_data_static<11>::param_info<0>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "data"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xADF3F363; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<UserConnection>::func_data_static<12>
{
  using func_ptr_type = void (UserConnection::*)(std::string);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "HandleWelcomeInfoUpdate"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xA8794B77; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 12; }
  static constexpr func_ptr_type GetFunctionPtr() { return &UserConnection::HandleWelcomeInfoUpdate; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<UserConnection>::func_data_static<12>::param_info<0>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "data"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xADF3F363; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<UserConnection>::func_data_static<13>
{
  using func_ptr_type = void (UserConnection::*)(std::string);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "HandleBanListUpdate"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x4A4DBF66; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 13; }
  static constexpr func_ptr_type GetFunctionPtr() { return &UserConnection::HandleBanListUpdate; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<UserConnection>::func_data_static<13>::param_info<0>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "data"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xADF3F363; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<UserConnection>::func_data_static<14>
{
  using func_ptr_type = void (UserConnection::*)(int, std::string);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "HandleGamePreviewUpdate"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x53822572; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 14; }
  static constexpr func_ptr_type GetFunctionPtr() { return &UserConnection::HandleGamePreviewUpdate; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<UserConnection>::func_data_static<14>::param_info<0>
{
  using param_type = int;
  static constexpr auto GetName() { return "request_id"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x427EB8A5; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<UserConnection>::func_data_static<14>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "data"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xADF3F363; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<UserConnection>::func_data_static<15>
{
  using func_ptr_type = void (UserConnection::*)(int);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "HandleGamePreviewDestroyed"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xD47B7339; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 15; }
  static constexpr func_ptr_type GetFunctionPtr() { return &UserConnection::HandleGamePreviewDestroyed; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<UserConnection>::func_data_static<15>::param_info<0>
{
  using param_type = int;
  static constexpr auto GetName() { return "request_id"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x427EB8A5; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

namespace StormReflFileInfo
{
  struct UserConnection
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct UserConnection::type_info<0>
  {
    using type = ::UserConnection;
  };

}

