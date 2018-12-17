#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "UITextInput.refl.h"


template <>
struct StormReflTypeInfo<UITextInput>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UITextInput"; }
  static constexpr auto GetNameHash() { return 0x278B6910; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<UITextInput *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const UITextInput *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<UITextInput *>(ptr);
    if(typeid(UITextInput).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const UITextInput *>(ptr);
    if(typeid(UITextInput).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<UITextInput>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "Prompt"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6543690E; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UITextInput::Prompt; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UITextInput *>(obj); return &ptr->Prompt; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UITextInput *>(obj); return &ptr->Prompt; }
};

template <typename Self>
struct StormReflTypeInfo<UITextInput>::field_data<0, Self> : public StormReflTypeInfo<UITextInput>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.Prompt; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.Prompt; }
};

template <>
struct StormReflTypeInfo<UITextInput>::field_data_static<1>
{
  using member_type = ScriptClassDelegate<bool, std::string>; // ScriptClassDelegate<bool, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >
  static constexpr auto GetName() { return "IsInvalidInput"; }
  static constexpr auto GetType() { return "ScriptClassDelegate<bool, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF3892A1B; }
  static constexpr unsigned GetTypeNameHash() { return 0x9B8BB67A; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UITextInput::IsInvalidInput; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UITextInput *>(obj); return &ptr->IsInvalidInput; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UITextInput *>(obj); return &ptr->IsInvalidInput; }
};

template <typename Self>
struct StormReflTypeInfo<UITextInput>::field_data<1, Self> : public StormReflTypeInfo<UITextInput>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, ScriptClassDelegate<bool, std::string>> & Get() { return self.IsInvalidInput; }
  std::add_const_t<std::remove_reference_t<ScriptClassDelegate<bool, std::string>>> & Get() const { return self.IsInvalidInput; }
};

template <>
struct StormReflFuncInfo<UITextInput>
{
  using MyBase = void;
  static constexpr int funcs_n = 2;
  template <int N> struct func_data_static {};
};

template <>
struct StormReflFuncInfo<UITextInput>::func_data_static<0>
{
  using func_ptr_type = void (UITextInput::*)(ScriptClassRef<UIClickable>);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "MakeCurrent"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x8061E905; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 0; }
  static constexpr func_ptr_type GetFunctionPtr() { return &UITextInput::MakeCurrent; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<UITextInput>::func_data_static<0>::param_info<0>
{
  using param_type = ScriptClassRef<UIClickable>;
  static constexpr auto GetName() { return "container"; }
  static constexpr auto GetType() { return "ScriptClassRef<UIClickable>"; }
  static constexpr unsigned GetNameHash() { return 0xC7A2EC1B; }
  static constexpr unsigned GetTypeNameHash() { return 0x658172AE; }
};

template <>
struct StormReflFuncInfo<UITextInput>::func_data_static<1>
{
  using func_ptr_type = std::string (UITextInput::*)();
  using return_type = std::string;
  static constexpr int params_n = 0;
  static constexpr auto GetName() { return "GetText"; }
  static constexpr auto GetReturnType() { return "std::string"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xF2569B8A; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xC508D6F7; }
  static constexpr auto GetFunctionIndex() { return 1; }
  static constexpr func_ptr_type GetFunctionPtr() { return &UITextInput::GetText; }
  template <int i>
  struct param_info { };
};

namespace StormReflFileInfo
{
  struct UITextInput
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct UITextInput::type_info<0>
  {
    using type = ::UITextInput;
  };

}

