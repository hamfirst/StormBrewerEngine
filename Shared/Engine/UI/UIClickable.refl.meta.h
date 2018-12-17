#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "UIClickable.refl.h"


template <>
struct StormReflEnumInfo<UIClickableState>
{
  static constexpr int elems_n = 4;
  static constexpr auto GetName() { return "UIClickableState"; }
  static constexpr auto GetNameHash() { return 0x77E05A26; }
  template <int N> struct elems { };
};

template <>
struct StormReflEnumInfo<UIClickableState>::elems<0>
{
  static constexpr auto GetName() { return "kDisabled"; }
  static constexpr auto GetNameHash() { return 0x2095D80B; }
  static constexpr auto GetValue() { return UIClickableState::kDisabled; }
};

template <>
struct StormReflEnumInfo<UIClickableState>::elems<1>
{
  static constexpr auto GetName() { return "kActive"; }
  static constexpr auto GetNameHash() { return 0xE9AD9FF6; }
  static constexpr auto GetValue() { return UIClickableState::kActive; }
};

template <>
struct StormReflEnumInfo<UIClickableState>::elems<2>
{
  static constexpr auto GetName() { return "kHover"; }
  static constexpr auto GetNameHash() { return 0x2ECA31F7; }
  static constexpr auto GetValue() { return UIClickableState::kHover; }
};

template <>
struct StormReflEnumInfo<UIClickableState>::elems<3>
{
  static constexpr auto GetName() { return "kPressed"; }
  static constexpr auto GetNameHash() { return 0xA1263D1C; }
  static constexpr auto GetValue() { return UIClickableState::kPressed; }
};

template <>
struct StormReflTypeInfo<UIClickable>
{
  using MyBase = void;
  static constexpr int fields_n = 9;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UIClickable"; }
  static constexpr auto GetNameHash() { return 0x226F6A1C; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<UIClickable *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const UIClickable *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<UIClickable *>(ptr);
    if(typeid(UIClickable).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const UIClickable *>(ptr);
    if(typeid(UIClickable).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<UIClickable>::field_data_static<0>
{
  using member_type = ScriptClassDelegate<void, int, int>; // ScriptClassDelegate<void, int, int>
  static constexpr auto GetName() { return "OnStateChange"; }
  static constexpr auto GetType() { return "ScriptClassDelegate<void, int, int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06A110B7; }
  static constexpr unsigned GetTypeNameHash() { return 0xA7CB28B9; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UIClickable::OnStateChange; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UIClickable *>(obj); return &ptr->OnStateChange; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UIClickable *>(obj); return &ptr->OnStateChange; }
};

template <typename Self>
struct StormReflTypeInfo<UIClickable>::field_data<0, Self> : public StormReflTypeInfo<UIClickable>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, ScriptClassDelegate<void, int, int>> & Get() { return self.OnStateChange; }
  std::add_const_t<std::remove_reference_t<ScriptClassDelegate<void, int, int>>> & Get() const { return self.OnStateChange; }
};

template <>
struct StormReflTypeInfo<UIClickable>::field_data_static<1>
{
  using member_type = ScriptClassDelegate<void>; // ScriptClassDelegate<void>
  static constexpr auto GetName() { return "OnClick"; }
  static constexpr auto GetType() { return "ScriptClassDelegate<void>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA0C4AEFD; }
  static constexpr unsigned GetTypeNameHash() { return 0x3E032AB0; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UIClickable::OnClick; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UIClickable *>(obj); return &ptr->OnClick; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UIClickable *>(obj); return &ptr->OnClick; }
};

template <typename Self>
struct StormReflTypeInfo<UIClickable>::field_data<1, Self> : public StormReflTypeInfo<UIClickable>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, ScriptClassDelegate<void>> & Get() { return self.OnClick; }
  std::add_const_t<std::remove_reference_t<ScriptClassDelegate<void>>> & Get() const { return self.OnClick; }
};

template <>
struct StormReflTypeInfo<UIClickable>::field_data_static<2>
{
  using member_type = ScriptClassDelegate<void, float>; // ScriptClassDelegate<void, float>
  static constexpr auto GetName() { return "OnUpdate"; }
  static constexpr auto GetType() { return "ScriptClassDelegate<void, float>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x605DA97D; }
  static constexpr unsigned GetTypeNameHash() { return 0x9F54DD16; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UIClickable::OnUpdate; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UIClickable *>(obj); return &ptr->OnUpdate; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UIClickable *>(obj); return &ptr->OnUpdate; }
};

template <typename Self>
struct StormReflTypeInfo<UIClickable>::field_data<2, Self> : public StormReflTypeInfo<UIClickable>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, ScriptClassDelegate<void, float>> & Get() { return self.OnUpdate; }
  std::add_const_t<std::remove_reference_t<ScriptClassDelegate<void, float>>> & Get() const { return self.OnUpdate; }
};

template <>
struct StormReflTypeInfo<UIClickable>::field_data_static<3>
{
  using member_type = ScriptClassDelegate<void>; // ScriptClassDelegate<void>
  static constexpr auto GetName() { return "OnRender"; }
  static constexpr auto GetType() { return "ScriptClassDelegate<void>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6C24056F; }
  static constexpr unsigned GetTypeNameHash() { return 0x3E032AB0; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &UIClickable::OnRender; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UIClickable *>(obj); return &ptr->OnRender; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UIClickable *>(obj); return &ptr->OnRender; }
};

template <typename Self>
struct StormReflTypeInfo<UIClickable>::field_data<3, Self> : public StormReflTypeInfo<UIClickable>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, ScriptClassDelegate<void>> & Get() { return self.OnRender; }
  std::add_const_t<std::remove_reference_t<ScriptClassDelegate<void>>> & Get() const { return self.OnRender; }
};

template <>
struct StormReflTypeInfo<UIClickable>::field_data_static<4>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "Enabled"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x9F448218; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &UIClickable::Enabled; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UIClickable *>(obj); return &ptr->Enabled; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UIClickable *>(obj); return &ptr->Enabled; }
};

template <typename Self>
struct StormReflTypeInfo<UIClickable>::field_data<4, Self> : public StormReflTypeInfo<UIClickable>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.Enabled; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.Enabled; }
};

template <>
struct StormReflTypeInfo<UIClickable>::field_data_static<5>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "X"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB7B2364B; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &UIClickable::X; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UIClickable *>(obj); return &ptr->X; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UIClickable *>(obj); return &ptr->X; }
};

template <typename Self>
struct StormReflTypeInfo<UIClickable>::field_data<5, Self> : public StormReflTypeInfo<UIClickable>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.X; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.X; }
};

template <>
struct StormReflTypeInfo<UIClickable>::field_data_static<6>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "Y"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC0B506DD; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &UIClickable::Y; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UIClickable *>(obj); return &ptr->Y; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UIClickable *>(obj); return &ptr->Y; }
};

template <typename Self>
struct StormReflTypeInfo<UIClickable>::field_data<6, Self> : public StormReflTypeInfo<UIClickable>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.Y; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.Y; }
};

template <>
struct StormReflTypeInfo<UIClickable>::field_data_static<7>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "Width"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x4DDB6A2B; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &UIClickable::Width; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UIClickable *>(obj); return &ptr->Width; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UIClickable *>(obj); return &ptr->Width; }
};

template <typename Self>
struct StormReflTypeInfo<UIClickable>::field_data<7, Self> : public StormReflTypeInfo<UIClickable>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.Width; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.Width; }
};

template <>
struct StormReflTypeInfo<UIClickable>::field_data_static<8>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "Height"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF2E1E039; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 8; }
  static constexpr auto GetMemberPtr() { return &UIClickable::Height; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UIClickable *>(obj); return &ptr->Height; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UIClickable *>(obj); return &ptr->Height; }
};

template <typename Self>
struct StormReflTypeInfo<UIClickable>::field_data<8, Self> : public StormReflTypeInfo<UIClickable>::field_data_static<8>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.Height; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.Height; }
};

template <>
struct StormReflFuncInfo<UIClickable>
{
  using MyBase = void;
  static constexpr int funcs_n = 5;
  template <int N> struct func_data_static {};
};

template <>
struct StormReflFuncInfo<UIClickable>::func_data_static<0>
{
  using func_ptr_type = int (UIClickable::*)();
  using return_type = int;
  static constexpr int params_n = 0;
  static constexpr auto GetName() { return "GetState"; }
  static constexpr auto GetReturnType() { return "int"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xAB3732EA; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFunctionIndex() { return 0; }
  static constexpr func_ptr_type GetFunctionPtr() { return &UIClickable::GetState; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<UIClickable>::func_data_static<1>
{
  using func_ptr_type = ScriptClassRef<UIClickable> (UIClickable::*)();
  using return_type = ScriptClassRef<UIClickable>;
  static constexpr int params_n = 0;
  static constexpr auto GetName() { return "GetParent"; }
  static constexpr auto GetReturnType() { return "ScriptClassRef<UIClickable>"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x5736E45D; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0x658172AE; }
  static constexpr auto GetFunctionIndex() { return 1; }
  static constexpr func_ptr_type GetFunctionPtr() { return &UIClickable::GetParent; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<UIClickable>::func_data_static<2>
{
  using func_ptr_type = void (UIClickable::*)(ScriptClassRef<UIClickable> &);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "SetParent"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xA61AF720; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 2; }
  static constexpr func_ptr_type GetFunctionPtr() { return &UIClickable::SetParent; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<UIClickable>::func_data_static<2>::param_info<0>
{
  using param_type = ScriptClassRef<UIClickable> &;
  static constexpr auto GetName() { return "parent"; }
  static constexpr auto GetType() { return "ScriptClassRef<UIClickable> &"; }
  static constexpr unsigned GetNameHash() { return 0x3D8E604F; }
  static constexpr unsigned GetTypeNameHash() { return 0x88DF5756; }
};

template <>
struct StormReflFuncInfo<UIClickable>::func_data_static<3>
{
  using func_ptr_type = int (UIClickable::*)();
  using return_type = int;
  static constexpr int params_n = 0;
  static constexpr auto GetName() { return "GetNumChildren"; }
  static constexpr auto GetReturnType() { return "int"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xC5EEE173; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFunctionIndex() { return 3; }
  static constexpr func_ptr_type GetFunctionPtr() { return &UIClickable::GetNumChildren; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<UIClickable>::func_data_static<4>
{
  using func_ptr_type = ScriptClassRef<UIClickable> (UIClickable::*)(int);
  using return_type = ScriptClassRef<UIClickable>;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "GetChild"; }
  static constexpr auto GetReturnType() { return "ScriptClassRef<UIClickable>"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x2A17B438; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0x658172AE; }
  static constexpr auto GetFunctionIndex() { return 4; }
  static constexpr func_ptr_type GetFunctionPtr() { return &UIClickable::GetChild; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<UIClickable>::func_data_static<4>::param_info<0>
{
  using param_type = int;
  static constexpr auto GetName() { return "index"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x80736701; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

namespace StormReflFileInfo
{
  struct UIClickable
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct UIClickable::type_info<0>
  {
    using type = ::UIClickable;
  };

}

