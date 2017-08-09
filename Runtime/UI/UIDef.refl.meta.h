#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "UIDef.refl.h"
#include "Runtime/UI/UITypes.refl.meta.h"


template <>
struct StormReflTypeInfo<UIElementDataBase>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UIElementDataBase"; }
  static constexpr auto GetNameHash() { return 0xC8F14E8A; }
  static UIElementDataBase & GetDefault() { static UIElementDataBase def; return def; }
};

template <>
struct StormReflTypeInfo<UIDefInputVariable>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UIDefInputVariable"; }
  static constexpr auto GetNameHash() { return 0x3CB97660; }
  static UIDefInputVariable & GetDefault() { static UIDefInputVariable def; return def; }
};

template <>
struct StormReflTypeInfo<UIDefInputVariable>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_VariableName"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x75DF746E; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UIDefInputVariable::m_VariableName; }
};

template <typename Self>
struct StormReflTypeInfo<UIDefInputVariable>::field_data<0, Self> : public StormReflTypeInfo<UIDefInputVariable>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_VariableName; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_VariableName; }
  void SetDefault() { self.m_VariableName = StormReflTypeInfo<UIDefInputVariable>::GetDefault().m_VariableName; }
};

template <>
struct StormReflTypeInfo<UIDefInputVariable>::field_data_static<1>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_DefaultEquation"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6D15D11D; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UIDefInputVariable::m_DefaultEquation; }
};

template <typename Self>
struct StormReflTypeInfo<UIDefInputVariable>::field_data<1, Self> : public StormReflTypeInfo<UIDefInputVariable>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_DefaultEquation; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_DefaultEquation; }
  void SetDefault() { self.m_DefaultEquation = StormReflTypeInfo<UIDefInputVariable>::GetDefault().m_DefaultEquation; }
};

template <>
struct StormReflTypeInfo<UIDefInputVariable>::field_data_static<2>
{
  using member_type = REnum<UIVariableType>; // REnum<UIVariableType>
  static constexpr auto GetName() { return "m_Type"; }
  static constexpr auto GetType() { return "REnum<UIVariableType>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB243C236; }
  static constexpr unsigned GetTypeNameHash() { return 0xB92748C6; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UIDefInputVariable::m_Type; }
};

template <typename Self>
struct StormReflTypeInfo<UIDefInputVariable>::field_data<2, Self> : public StormReflTypeInfo<UIDefInputVariable>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, REnum<UIVariableType>> & Get() { return self.m_Type; }
  std::add_const_t<std::remove_reference_t<REnum<UIVariableType>>> & Get() const { return self.m_Type; }
  void SetDefault() { self.m_Type = StormReflTypeInfo<UIDefInputVariable>::GetDefault().m_Type; }
};

template <>
struct StormReflTypeInfo<UIDefEquation>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UIDefEquation"; }
  static constexpr auto GetNameHash() { return 0xF7D63B3C; }
  static UIDefEquation & GetDefault() { static UIDefEquation def; return def; }
};

template <>
struct StormReflTypeInfo<UIDefEquation>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_VariableName"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x75DF746E; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UIDefEquation::m_VariableName; }
};

template <typename Self>
struct StormReflTypeInfo<UIDefEquation>::field_data<0, Self> : public StormReflTypeInfo<UIDefEquation>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_VariableName; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_VariableName; }
  void SetDefault() { self.m_VariableName = StormReflTypeInfo<UIDefEquation>::GetDefault().m_VariableName; }
};

template <>
struct StormReflTypeInfo<UIDefEquation>::field_data_static<1>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Equation"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x559340DB; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UIDefEquation::m_Equation; }
};

template <typename Self>
struct StormReflTypeInfo<UIDefEquation>::field_data<1, Self> : public StormReflTypeInfo<UIDefEquation>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Equation; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Equation; }
  void SetDefault() { self.m_Equation = StormReflTypeInfo<UIDefEquation>::GetDefault().m_Equation; }
};

template <>
struct StormReflTypeInfo<UIDefOutputEquation>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UIDefOutputEquation"; }
  static constexpr auto GetNameHash() { return 0x1E88E9E6; }
  static UIDefOutputEquation & GetDefault() { static UIDefOutputEquation def; return def; }
};

template <>
struct StormReflTypeInfo<UIDefOutputEquation>::field_data_static<0>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_ChildIndex"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x231F7221; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UIDefOutputEquation::m_ChildIndex; }
};

template <typename Self>
struct StormReflTypeInfo<UIDefOutputEquation>::field_data<0, Self> : public StormReflTypeInfo<UIDefOutputEquation>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_ChildIndex; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_ChildIndex; }
  void SetDefault() { self.m_ChildIndex = StormReflTypeInfo<UIDefOutputEquation>::GetDefault().m_ChildIndex; }
};

template <>
struct StormReflTypeInfo<UIDefOutputEquation>::field_data_static<1>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_VariableName"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x75DF746E; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UIDefOutputEquation::m_VariableName; }
};

template <typename Self>
struct StormReflTypeInfo<UIDefOutputEquation>::field_data<1, Self> : public StormReflTypeInfo<UIDefOutputEquation>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_VariableName; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_VariableName; }
  void SetDefault() { self.m_VariableName = StormReflTypeInfo<UIDefOutputEquation>::GetDefault().m_VariableName; }
};

template <>
struct StormReflTypeInfo<UIDefOutputEquation>::field_data_static<2>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Equation"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x559340DB; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UIDefOutputEquation::m_Equation; }
};

template <typename Self>
struct StormReflTypeInfo<UIDefOutputEquation>::field_data<2, Self> : public StormReflTypeInfo<UIDefOutputEquation>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Equation; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Equation; }
  void SetDefault() { self.m_Equation = StormReflTypeInfo<UIDefOutputEquation>::GetDefault().m_Equation; }
};

template <>
struct StormReflTypeInfo<UIDef>
{
  using MyBase = void;
  static constexpr int fields_n = 5;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UIDef"; }
  static constexpr auto GetNameHash() { return 0x1B05DE82; }
  static UIDef & GetDefault() { static UIDef def; return def; }
};

template <>
struct StormReflTypeInfo<UIDef>::field_data_static<0>
{
  using member_type = RPolymorphic<UIElementDataBase, UIElementTypeDatabase, UIElementDataTypeInfo>; // RPolymorphic<UIElementDataBase, UIElementTypeDatabase, UIElementDataTypeInfo>
  static constexpr auto GetName() { return "m_InitData"; }
  static constexpr auto GetType() { return "RPolymorphic<UIElementDataBase, UIElementTypeDatabase, UIElementDataTypeInfo>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x880F1CB3; }
  static constexpr unsigned GetTypeNameHash() { return 0x218B2ECC; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UIDef::m_InitData; }
};

template <typename Self>
struct StormReflTypeInfo<UIDef>::field_data<0, Self> : public StormReflTypeInfo<UIDef>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RPolymorphic<UIElementDataBase, UIElementTypeDatabase, UIElementDataTypeInfo>> & Get() { return self.m_InitData; }
  std::add_const_t<std::remove_reference_t<RPolymorphic<UIElementDataBase, UIElementTypeDatabase, UIElementDataTypeInfo>>> & Get() const { return self.m_InitData; }
  void SetDefault() { self.m_InitData = StormReflTypeInfo<UIDef>::GetDefault().m_InitData; }
};

template <>
struct StormReflTypeInfo<UIDef>::field_data_static<1>
{
  using member_type = RMergeList<UIDefInputVariable>; // RMergeList<UIDefInputVariable>
  static constexpr auto GetName() { return "m_Inputs"; }
  static constexpr auto GetType() { return "RMergeList<UIDefInputVariable>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x4E5EF786; }
  static constexpr unsigned GetTypeNameHash() { return 0xBF20B53C; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UIDef::m_Inputs; }
};

template <typename Self>
struct StormReflTypeInfo<UIDef>::field_data<1, Self> : public StormReflTypeInfo<UIDef>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<UIDefInputVariable>> & Get() { return self.m_Inputs; }
  std::add_const_t<std::remove_reference_t<RMergeList<UIDefInputVariable>>> & Get() const { return self.m_Inputs; }
  void SetDefault() { self.m_Inputs = StormReflTypeInfo<UIDef>::GetDefault().m_Inputs; }
};

template <>
struct StormReflTypeInfo<UIDef>::field_data_static<2>
{
  using member_type = RMergeList<UIDefEquation>; // RMergeList<UIDefEquation>
  static constexpr auto GetName() { return "m_Equations"; }
  static constexpr auto GetType() { return "RMergeList<UIDefEquation>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0A5A5717; }
  static constexpr unsigned GetTypeNameHash() { return 0x3B35649C; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UIDef::m_Equations; }
};

template <typename Self>
struct StormReflTypeInfo<UIDef>::field_data<2, Self> : public StormReflTypeInfo<UIDef>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<UIDefEquation>> & Get() { return self.m_Equations; }
  std::add_const_t<std::remove_reference_t<RMergeList<UIDefEquation>>> & Get() const { return self.m_Equations; }
  void SetDefault() { self.m_Equations = StormReflTypeInfo<UIDef>::GetDefault().m_Equations; }
};

template <>
struct StormReflTypeInfo<UIDef>::field_data_static<3>
{
  using member_type = RMergeList<UIDefOutputEquation>; // RMergeList<UIDefOutputEquation>
  static constexpr auto GetName() { return "m_Outputs"; }
  static constexpr auto GetType() { return "RMergeList<UIDefOutputEquation>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x9987DA89; }
  static constexpr unsigned GetTypeNameHash() { return 0x7B4104A8; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &UIDef::m_Outputs; }
};

template <typename Self>
struct StormReflTypeInfo<UIDef>::field_data<3, Self> : public StormReflTypeInfo<UIDef>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<UIDefOutputEquation>> & Get() { return self.m_Outputs; }
  std::add_const_t<std::remove_reference_t<RMergeList<UIDefOutputEquation>>> & Get() const { return self.m_Outputs; }
  void SetDefault() { self.m_Outputs = StormReflTypeInfo<UIDef>::GetDefault().m_Outputs; }
};

template <>
struct StormReflTypeInfo<UIDef>::field_data_static<4>
{
  using member_type = RMergeList<UIDefChild>; // RMergeList<UIDefChild>
  static constexpr auto GetName() { return "m_Children"; }
  static constexpr auto GetType() { return "RMergeList<UIDefChild>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x57BB6594; }
  static constexpr unsigned GetTypeNameHash() { return 0x0F12050C; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &UIDef::m_Children; }
};

template <typename Self>
struct StormReflTypeInfo<UIDef>::field_data<4, Self> : public StormReflTypeInfo<UIDef>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<UIDefChild>> & Get() { return self.m_Children; }
  std::add_const_t<std::remove_reference_t<RMergeList<UIDefChild>>> & Get() const { return self.m_Children; }
  void SetDefault() { self.m_Children = StormReflTypeInfo<UIDef>::GetDefault().m_Children; }
};

template <>
struct StormReflTypeInfo<UIDefChild>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UIDefChild"; }
  static constexpr auto GetNameHash() { return 0x41225F04; }
  static UIDefChild & GetDefault() { static UIDefChild def; return def; }
};

template <>
struct StormReflTypeInfo<UIDefChild>::field_data_static<0>
{
  using member_type = UIDef; // UIDef
  static constexpr auto GetName() { return "m_UI"; }
  static constexpr auto GetType() { return "UIDef"; }
  static constexpr unsigned GetFieldNameHash() { return 0x4724C96A; }
  static constexpr unsigned GetTypeNameHash() { return 0x1B05DE82; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UIDefChild::m_UI; }
};

template <typename Self>
struct StormReflTypeInfo<UIDefChild>::field_data<0, Self> : public StormReflTypeInfo<UIDefChild>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, UIDef> & Get() { return self.m_UI; }
  std::add_const_t<std::remove_reference_t<UIDef>> & Get() const { return self.m_UI; }
  void SetDefault() { self.m_UI = StormReflTypeInfo<UIDefChild>::GetDefault().m_UI; }
};

template <>
struct StormReflTypeInfo<UIDefChild>::field_data_static<1>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UIDefChild::m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<UIDefChild>::field_data<1, Self> : public StormReflTypeInfo<UIDefChild>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<UIDefChild>::GetDefault().m_Name; }
};

namespace StormReflFileInfo
{
  struct UIDef
  {
    static const int types_n = 6;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct UIDef::type_info<0>
  {
    using type = ::UIElementDataBase;
  };

  template <>
  struct UIDef::type_info<1>
  {
    using type = ::UIDefInputVariable;
  };

  template <>
  struct UIDef::type_info<2>
  {
    using type = ::UIDefEquation;
  };

  template <>
  struct UIDef::type_info<3>
  {
    using type = ::UIDefOutputEquation;
  };

  template <>
  struct UIDef::type_info<4>
  {
    using type = ::UIDef;
  };

  template <>
  struct UIDef::type_info<5>
  {
    using type = ::UIDefChild;
  };

}

