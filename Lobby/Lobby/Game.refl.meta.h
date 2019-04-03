#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "Game.refl.h"
#include "SharedTypes.refl.meta.h"


template <>
struct StormReflTypeInfo<Game>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
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
struct StormReflFuncInfo<Game>
{
  using MyBase = void;
  static constexpr int funcs_n = 6;
  template <int N> struct func_data_static {};
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<0>
{
  using func_ptr_type = void (Game::*)(DDSResponder &, DDSKey, int);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "AddUser"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x8C229B19; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 0; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::AddUser; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<0>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<0>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x6186CA22; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<0>::param_info<2>
{
  using param_type = int;
  static constexpr auto GetName() { return "admin_level"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x3AC037E9; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<1>
{
  using func_ptr_type = void (Game::*)(DDSKey);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "RemoveUser"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xFEC3C304; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 1; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::RemoveUser; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<1>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x6186CA22; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<2>
{
  using func_ptr_type = void (Game::*)(DDSKey, DDSKey, DDSKey, int);
  using return_type = void;
  static constexpr int params_n = 4;
  static constexpr auto GetName() { return "KickUser"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x639C9527; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 2; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::KickUser; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<2>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<2>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x6186CA22; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<2>::param_info<2>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "src_user"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xA4FEA4A3; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<2>::param_info<3>
{
  using param_type = int;
  static constexpr auto GetName() { return "src_admin_level"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x67623132; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<3>
{
  using func_ptr_type = void (Game::*)(DDSKey, DDSKey, std::string, std::string);
  using return_type = void;
  static constexpr int params_n = 4;
  static constexpr auto GetName() { return "SendChat"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xDDA27521; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 3; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::SendChat; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<3>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x6186CA22; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<3>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<3>::param_info<2>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "message"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xB6BD307F; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<3>::param_info<3>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "title"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x2B36786B; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<4>
{
  using func_ptr_type = void (Game::*)(DDSKey, std::string);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "HandleMemberUpdate"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x4E85F53F; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 4; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::HandleMemberUpdate; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<4>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x6186CA22; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<4>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "data"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xADF3F363; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<5>
{
  using func_ptr_type = void (Game::*)(DDSResponder &);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "GetInfo"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x02540D1A; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 5; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::GetInfo; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<5>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

namespace StormReflFileInfo
{
  struct Game
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct Game::type_info<0>
  {
    using type = ::Game;
  };

}

