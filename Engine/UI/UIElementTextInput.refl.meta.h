#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "UIElementTextInput.refl.h"
#include "Engine/UI/UICustomPropertyData.refl.meta.h"
#include "Runtime/UI/UIDef.refl.meta.h"


template <>
struct StormReflTypeInfo<UIElementTextInputInitData>
{
  using MyBase = UIElementInitDataBase;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "UIElementTextInputInitData"; }
  static constexpr auto GetNameHash() { return 0x167AED4B; }
  static UIElementTextInputInitData & GetDefault() { static UIElementTextInputInitData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<UIElementTextInputInitData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x17C45A05 == type_name_hash) return static_cast<UIElementInitDataBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const UIElementTextInputInitData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x17C45A05 == type_name_hash) return static_cast<const UIElementInitDataBase *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<UIElementTextInputInitData *>(ptr);
    if(typeid(UIElementTextInputInitData).hash_code() == type_id_hash) return c;
    if(typeid(UIElementInitDataBase).hash_code() == type_id_hash) return static_cast<UIElementInitDataBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const UIElementTextInputInitData *>(ptr);
    if(typeid(UIElementTextInputInitData).hash_code() == type_id_hash) return c;
    if(typeid(UIElementInitDataBase).hash_code() == type_id_hash) return static_cast<const UIElementInitDataBase *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<UIElementTextInputData>
{
  using MyBase = UIElementDataFrameCenter;
  static constexpr int fields_n = 23 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "UIElementTextInputData"; }
  static constexpr auto GetNameHash() { return 0xC49A2076; }
  static UIElementTextInputData & GetDefault() { static UIElementTextInputData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<UIElementTextInputData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x4076AA02 == type_name_hash) return static_cast<UIElementDataFrameCenter *>(c);
    if(0xC8F14E8A == type_name_hash) return static_cast<UIElementDataBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const UIElementTextInputData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x4076AA02 == type_name_hash) return static_cast<const UIElementDataFrameCenter *>(c);
    if(0xC8F14E8A == type_name_hash) return static_cast<const UIElementDataBase *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<UIElementTextInputData *>(ptr);
    if(typeid(UIElementTextInputData).hash_code() == type_id_hash) return c;
    if(typeid(UIElementDataFrameCenter).hash_code() == type_id_hash) return static_cast<UIElementDataFrameCenter *>(c);
    if(typeid(UIElementDataBase).hash_code() == type_id_hash) return static_cast<UIElementDataBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const UIElementTextInputData *>(ptr);
    if(typeid(UIElementTextInputData).hash_code() == type_id_hash) return c;
    if(typeid(UIElementDataFrameCenter).hash_code() == type_id_hash) return static_cast<const UIElementDataFrameCenter *>(c);
    if(typeid(UIElementDataBase).hash_code() == type_id_hash) return static_cast<const UIElementDataBase *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<UIElementTextInputData>::field_data_static<0 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Prompt"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2FD03BF0; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextInputData::m_Prompt; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextInputData>::field_data<0 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n, Self> : public StormReflTypeInfo<UIElementTextInputData>::field_data_static<0 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Prompt; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Prompt; }
  void SetDefault() { self.m_Prompt = StormReflTypeInfo<UIElementTextInputData>::GetDefault().m_Prompt; }
};

template <>
struct StormReflTypeInfo<UIElementTextInputData>::field_data_static<1 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_TextMode"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x9F050945; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 1 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextInputData::m_TextMode; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextInputData>::field_data<1 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n, Self> : public StormReflTypeInfo<UIElementTextInputData>::field_data_static<1 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_TextMode; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_TextMode; }
  void SetDefault() { self.m_TextMode = StormReflTypeInfo<UIElementTextInputData>::GetDefault().m_TextMode; }
};

template <>
struct StormReflTypeInfo<UIElementTextInputData>::field_data_static<2 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_FontId"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDA57EB01; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 2 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextInputData::m_FontId; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextInputData>::field_data<2 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n, Self> : public StormReflTypeInfo<UIElementTextInputData>::field_data_static<2 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_FontId; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_FontId; }
  void SetDefault() { self.m_FontId = StormReflTypeInfo<UIElementTextInputData>::GetDefault().m_FontId; }
};

template <>
struct StormReflTypeInfo<UIElementTextInputData>::field_data_static<3 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_Justify"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x7BE07DB0; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 3 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextInputData::m_Justify; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextInputData>::field_data<3 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n, Self> : public StormReflTypeInfo<UIElementTextInputData>::field_data_static<3 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_Justify; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_Justify; }
  void SetDefault() { self.m_Justify = StormReflTypeInfo<UIElementTextInputData>::GetDefault().m_Justify; }
};

template <>
struct StormReflTypeInfo<UIElementTextInputData>::field_data_static<4 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_Scale"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6170B5E4; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 4 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextInputData::m_Scale; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextInputData>::field_data<4 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n, Self> : public StormReflTypeInfo<UIElementTextInputData>::field_data_static<4 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_Scale; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_Scale; }
  void SetDefault() { self.m_Scale = StormReflTypeInfo<UIElementTextInputData>::GetDefault().m_Scale; }
};

template <>
struct StormReflTypeInfo<UIElementTextInputData>::field_data_static<5 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_EnableTextBounds"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x397C84F7; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 5 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextInputData::m_EnableTextBounds; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextInputData>::field_data<5 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n, Self> : public StormReflTypeInfo<UIElementTextInputData>::field_data_static<5 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_EnableTextBounds; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_EnableTextBounds; }
  void SetDefault() { self.m_EnableTextBounds = StormReflTypeInfo<UIElementTextInputData>::GetDefault().m_EnableTextBounds; }
};

template <>
struct StormReflTypeInfo<UIElementTextInputData>::field_data_static<6 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_TextBoundsStartX"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5F948DF6; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 6 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextInputData::m_TextBoundsStartX; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextInputData>::field_data<6 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n, Self> : public StormReflTypeInfo<UIElementTextInputData>::field_data_static<6 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_TextBoundsStartX; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_TextBoundsStartX; }
  void SetDefault() { self.m_TextBoundsStartX = StormReflTypeInfo<UIElementTextInputData>::GetDefault().m_TextBoundsStartX; }
};

template <>
struct StormReflTypeInfo<UIElementTextInputData>::field_data_static<7 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_TextBoundsStartY"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2893BD60; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 7 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextInputData::m_TextBoundsStartY; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextInputData>::field_data<7 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n, Self> : public StormReflTypeInfo<UIElementTextInputData>::field_data_static<7 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_TextBoundsStartY; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_TextBoundsStartY; }
  void SetDefault() { self.m_TextBoundsStartY = StormReflTypeInfo<UIElementTextInputData>::GetDefault().m_TextBoundsStartY; }
};

template <>
struct StormReflTypeInfo<UIElementTextInputData>::field_data_static<8 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_TextBoundsEndX"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC67E8723; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 8 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextInputData::m_TextBoundsEndX; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextInputData>::field_data<8 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n, Self> : public StormReflTypeInfo<UIElementTextInputData>::field_data_static<8 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_TextBoundsEndX; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_TextBoundsEndX; }
  void SetDefault() { self.m_TextBoundsEndX = StormReflTypeInfo<UIElementTextInputData>::GetDefault().m_TextBoundsEndX; }
};

template <>
struct StormReflTypeInfo<UIElementTextInputData>::field_data_static<9 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_TextBoundsEndY"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB179B7B5; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 9 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextInputData::m_TextBoundsEndY; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextInputData>::field_data<9 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n, Self> : public StormReflTypeInfo<UIElementTextInputData>::field_data_static<9 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_TextBoundsEndY; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_TextBoundsEndY; }
  void SetDefault() { self.m_TextBoundsEndY = StormReflTypeInfo<UIElementTextInputData>::GetDefault().m_TextBoundsEndY; }
};

template <>
struct StormReflTypeInfo<UIElementTextInputData>::field_data_static<10 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_SecondaryColorR"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAEE8788B; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 10 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextInputData::m_SecondaryColorR; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextInputData>::field_data<10 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n, Self> : public StormReflTypeInfo<UIElementTextInputData>::field_data_static<10 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_SecondaryColorR; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_SecondaryColorR; }
  void SetDefault() { self.m_SecondaryColorR = StormReflTypeInfo<UIElementTextInputData>::GetDefault().m_SecondaryColorR; }
};

template <>
struct StormReflTypeInfo<UIElementTextInputData>::field_data_static<11 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_SecondaryColorG"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC3359C60; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 11 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextInputData::m_SecondaryColorG; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextInputData>::field_data<11 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n, Self> : public StormReflTypeInfo<UIElementTextInputData>::field_data_static<11 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_SecondaryColorG; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_SecondaryColorG; }
  void SetDefault() { self.m_SecondaryColorG = StormReflTypeInfo<UIElementTextInputData>::GetDefault().m_SecondaryColorG; }
};

template <>
struct StormReflTypeInfo<UIElementTextInputData>::field_data_static<12 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_SecondaryColorB"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB35F68EF; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 12 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextInputData::m_SecondaryColorB; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextInputData>::field_data<12 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n, Self> : public StormReflTypeInfo<UIElementTextInputData>::field_data_static<12 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_SecondaryColorB; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_SecondaryColorB; }
  void SetDefault() { self.m_SecondaryColorB = StormReflTypeInfo<UIElementTextInputData>::GetDefault().m_SecondaryColorB; }
};

template <>
struct StormReflTypeInfo<UIElementTextInputData>::field_data_static<13 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_SecondaryColorA"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2A563955; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 13 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextInputData::m_SecondaryColorA; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextInputData>::field_data<13 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n, Self> : public StormReflTypeInfo<UIElementTextInputData>::field_data_static<13 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_SecondaryColorA; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_SecondaryColorA; }
  void SetDefault() { self.m_SecondaryColorA = StormReflTypeInfo<UIElementTextInputData>::GetDefault().m_SecondaryColorA; }
};

template <>
struct StormReflTypeInfo<UIElementTextInputData>::field_data_static<14 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_SelectionColorR"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x718AAD92; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 14 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextInputData::m_SelectionColorR; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextInputData>::field_data<14 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n, Self> : public StormReflTypeInfo<UIElementTextInputData>::field_data_static<14 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_SelectionColorR; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_SelectionColorR; }
  void SetDefault() { self.m_SelectionColorR = StormReflTypeInfo<UIElementTextInputData>::GetDefault().m_SelectionColorR; }
};

template <>
struct StormReflTypeInfo<UIElementTextInputData>::field_data_static<15 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_SelectionColorG"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1C574979; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 15 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextInputData::m_SelectionColorG; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextInputData>::field_data<15 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n, Self> : public StormReflTypeInfo<UIElementTextInputData>::field_data_static<15 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_SelectionColorG; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_SelectionColorG; }
  void SetDefault() { self.m_SelectionColorG = StormReflTypeInfo<UIElementTextInputData>::GetDefault().m_SelectionColorG; }
};

template <>
struct StormReflTypeInfo<UIElementTextInputData>::field_data_static<16 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_SelectionColorB"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6C3DBDF6; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 16 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextInputData::m_SelectionColorB; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextInputData>::field_data<16 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n, Self> : public StormReflTypeInfo<UIElementTextInputData>::field_data_static<16 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_SelectionColorB; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_SelectionColorB; }
  void SetDefault() { self.m_SelectionColorB = StormReflTypeInfo<UIElementTextInputData>::GetDefault().m_SelectionColorB; }
};

template <>
struct StormReflTypeInfo<UIElementTextInputData>::field_data_static<17 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_SelectionColorA"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF534EC4C; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 17 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextInputData::m_SelectionColorA; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextInputData>::field_data<17 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n, Self> : public StormReflTypeInfo<UIElementTextInputData>::field_data_static<17 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_SelectionColorA; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_SelectionColorA; }
  void SetDefault() { self.m_SelectionColorA = StormReflTypeInfo<UIElementTextInputData>::GetDefault().m_SelectionColorA; }
};

template <>
struct StormReflTypeInfo<UIElementTextInputData>::field_data_static<18 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_SelectionBkgColorR"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA529ED79; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 18 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextInputData::m_SelectionBkgColorR; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextInputData>::field_data<18 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n, Self> : public StormReflTypeInfo<UIElementTextInputData>::field_data_static<18 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_SelectionBkgColorR; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_SelectionBkgColorR; }
  void SetDefault() { self.m_SelectionBkgColorR = StormReflTypeInfo<UIElementTextInputData>::GetDefault().m_SelectionBkgColorR; }
};

template <>
struct StormReflTypeInfo<UIElementTextInputData>::field_data_static<19 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_SelectionBkgColorG"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC8F40992; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 19 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextInputData::m_SelectionBkgColorG; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextInputData>::field_data<19 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n, Self> : public StormReflTypeInfo<UIElementTextInputData>::field_data_static<19 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_SelectionBkgColorG; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_SelectionBkgColorG; }
  void SetDefault() { self.m_SelectionBkgColorG = StormReflTypeInfo<UIElementTextInputData>::GetDefault().m_SelectionBkgColorG; }
};

template <>
struct StormReflTypeInfo<UIElementTextInputData>::field_data_static<20 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_SelectionBkgColorB"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB89EFD1D; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 20 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextInputData::m_SelectionBkgColorB; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextInputData>::field_data<20 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n, Self> : public StormReflTypeInfo<UIElementTextInputData>::field_data_static<20 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_SelectionBkgColorB; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_SelectionBkgColorB; }
  void SetDefault() { self.m_SelectionBkgColorB = StormReflTypeInfo<UIElementTextInputData>::GetDefault().m_SelectionBkgColorB; }
};

template <>
struct StormReflTypeInfo<UIElementTextInputData>::field_data_static<21 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_SelectionBkgColorA"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2197ACA7; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 21 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextInputData::m_SelectionBkgColorA; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextInputData>::field_data<21 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n, Self> : public StormReflTypeInfo<UIElementTextInputData>::field_data_static<21 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_SelectionBkgColorA; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_SelectionBkgColorA; }
  void SetDefault() { self.m_SelectionBkgColorA = StormReflTypeInfo<UIElementTextInputData>::GetDefault().m_SelectionBkgColorA; }
};

template <>
struct StormReflTypeInfo<UIElementTextInputData>::field_data_static<22 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_Active"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0621ABCA; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 22 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextInputData::m_Active; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextInputData>::field_data<22 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n, Self> : public StormReflTypeInfo<UIElementTextInputData>::field_data_static<22 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_Active; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_Active; }
  void SetDefault() { self.m_Active = StormReflTypeInfo<UIElementTextInputData>::GetDefault().m_Active; }
};

namespace StormReflFileInfo
{
  struct UIElementTextInput
  {
    static const int types_n = 2;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct UIElementTextInput::type_info<0>
  {
    using type = ::UIElementTextInputInitData;
  };

  template <>
  struct UIElementTextInput::type_info<1>
  {
    using type = ::UIElementTextInputData;
  };

}

