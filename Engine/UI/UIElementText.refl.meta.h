#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "UIElementText.refl.h"
#include "Engine/UI/UICustomPropertyData.refl.meta.h"
#include "Runtime/UI/UIDef.refl.meta.h"


template <>
struct StormReflTypeInfo<UIElementTextInitData>
{
  using MyBase = UIElementInitDataBase;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "UIElementTextInitData"; }
  static constexpr auto GetNameHash() { return 0x797CBA08; }
  static UIElementTextInitData & GetDefault() { static UIElementTextInitData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<UIElementTextInitData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x17C45A05 == type_name_hash) return static_cast<UIElementInitDataBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const UIElementTextInitData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x17C45A05 == type_name_hash) return static_cast<const UIElementInitDataBase *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<UIElementTextInitData *>(ptr);
    if(typeid(UIElementTextInitData).hash_code() == type_id_hash) return c;
    if(typeid(UIElementInitDataBase).hash_code() == type_id_hash) return static_cast<UIElementInitDataBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const UIElementTextInitData *>(ptr);
    if(typeid(UIElementTextInitData).hash_code() == type_id_hash) return c;
    if(typeid(UIElementInitDataBase).hash_code() == type_id_hash) return static_cast<const UIElementInitDataBase *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<UIElementTextData>
{
  using MyBase = UIElementDataFrameCenter;
  static constexpr int fields_n = 14 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "UIElementTextData"; }
  static constexpr auto GetNameHash() { return 0xF2808E39; }
  static UIElementTextData & GetDefault() { static UIElementTextData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<UIElementTextData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x4076AA02 == type_name_hash) return static_cast<UIElementDataFrameCenter *>(c);
    if(0xC8F14E8A == type_name_hash) return static_cast<UIElementDataBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const UIElementTextData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x4076AA02 == type_name_hash) return static_cast<const UIElementDataFrameCenter *>(c);
    if(0xC8F14E8A == type_name_hash) return static_cast<const UIElementDataBase *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<UIElementTextData *>(ptr);
    if(typeid(UIElementTextData).hash_code() == type_id_hash) return c;
    if(typeid(UIElementDataFrameCenter).hash_code() == type_id_hash) return static_cast<UIElementDataFrameCenter *>(c);
    if(typeid(UIElementDataBase).hash_code() == type_id_hash) return static_cast<UIElementDataBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const UIElementTextData *>(ptr);
    if(typeid(UIElementTextData).hash_code() == type_id_hash) return c;
    if(typeid(UIElementDataFrameCenter).hash_code() == type_id_hash) return static_cast<const UIElementDataFrameCenter *>(c);
    if(typeid(UIElementDataBase).hash_code() == type_id_hash) return static_cast<const UIElementDataBase *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<UIElementTextData>::field_data_static<0 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Text"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x051632D8; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextData::m_Text; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextData>::field_data<0 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n, Self> : public StormReflTypeInfo<UIElementTextData>::field_data_static<0 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Text; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Text; }
  void SetDefault() { self.m_Text = StormReflTypeInfo<UIElementTextData>::GetDefault().m_Text; }
};

template <>
struct StormReflTypeInfo<UIElementTextData>::field_data_static<1 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_TextMode"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x9F050945; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 1 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextData::m_TextMode; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextData>::field_data<1 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n, Self> : public StormReflTypeInfo<UIElementTextData>::field_data_static<1 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_TextMode; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_TextMode; }
  void SetDefault() { self.m_TextMode = StormReflTypeInfo<UIElementTextData>::GetDefault().m_TextMode; }
};

template <>
struct StormReflTypeInfo<UIElementTextData>::field_data_static<2 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_FontId"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDA57EB01; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 2 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextData::m_FontId; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextData>::field_data<2 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n, Self> : public StormReflTypeInfo<UIElementTextData>::field_data_static<2 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_FontId; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_FontId; }
  void SetDefault() { self.m_FontId = StormReflTypeInfo<UIElementTextData>::GetDefault().m_FontId; }
};

template <>
struct StormReflTypeInfo<UIElementTextData>::field_data_static<3 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_Justify"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x7BE07DB0; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 3 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextData::m_Justify; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextData>::field_data<3 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n, Self> : public StormReflTypeInfo<UIElementTextData>::field_data_static<3 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_Justify; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_Justify; }
  void SetDefault() { self.m_Justify = StormReflTypeInfo<UIElementTextData>::GetDefault().m_Justify; }
};

template <>
struct StormReflTypeInfo<UIElementTextData>::field_data_static<4 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_Scale"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6170B5E4; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 4 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextData::m_Scale; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextData>::field_data<4 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n, Self> : public StormReflTypeInfo<UIElementTextData>::field_data_static<4 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_Scale; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_Scale; }
  void SetDefault() { self.m_Scale = StormReflTypeInfo<UIElementTextData>::GetDefault().m_Scale; }
};

template <>
struct StormReflTypeInfo<UIElementTextData>::field_data_static<5 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_EnableTextBounds"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x397C84F7; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 5 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextData::m_EnableTextBounds; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextData>::field_data<5 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n, Self> : public StormReflTypeInfo<UIElementTextData>::field_data_static<5 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_EnableTextBounds; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_EnableTextBounds; }
  void SetDefault() { self.m_EnableTextBounds = StormReflTypeInfo<UIElementTextData>::GetDefault().m_EnableTextBounds; }
};

template <>
struct StormReflTypeInfo<UIElementTextData>::field_data_static<6 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_TextBoundsStartX"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5F948DF6; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 6 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextData::m_TextBoundsStartX; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextData>::field_data<6 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n, Self> : public StormReflTypeInfo<UIElementTextData>::field_data_static<6 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_TextBoundsStartX; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_TextBoundsStartX; }
  void SetDefault() { self.m_TextBoundsStartX = StormReflTypeInfo<UIElementTextData>::GetDefault().m_TextBoundsStartX; }
};

template <>
struct StormReflTypeInfo<UIElementTextData>::field_data_static<7 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_TextBoundsStartY"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2893BD60; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 7 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextData::m_TextBoundsStartY; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextData>::field_data<7 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n, Self> : public StormReflTypeInfo<UIElementTextData>::field_data_static<7 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_TextBoundsStartY; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_TextBoundsStartY; }
  void SetDefault() { self.m_TextBoundsStartY = StormReflTypeInfo<UIElementTextData>::GetDefault().m_TextBoundsStartY; }
};

template <>
struct StormReflTypeInfo<UIElementTextData>::field_data_static<8 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_TextBoundsEndX"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC67E8723; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 8 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextData::m_TextBoundsEndX; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextData>::field_data<8 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n, Self> : public StormReflTypeInfo<UIElementTextData>::field_data_static<8 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_TextBoundsEndX; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_TextBoundsEndX; }
  void SetDefault() { self.m_TextBoundsEndX = StormReflTypeInfo<UIElementTextData>::GetDefault().m_TextBoundsEndX; }
};

template <>
struct StormReflTypeInfo<UIElementTextData>::field_data_static<9 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_TextBoundsEndY"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB179B7B5; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 9 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextData::m_TextBoundsEndY; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextData>::field_data<9 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n, Self> : public StormReflTypeInfo<UIElementTextData>::field_data_static<9 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_TextBoundsEndY; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_TextBoundsEndY; }
  void SetDefault() { self.m_TextBoundsEndY = StormReflTypeInfo<UIElementTextData>::GetDefault().m_TextBoundsEndY; }
};

template <>
struct StormReflTypeInfo<UIElementTextData>::field_data_static<10 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_SecondaryColorR"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAEE8788B; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 10 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextData::m_SecondaryColorR; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextData>::field_data<10 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n, Self> : public StormReflTypeInfo<UIElementTextData>::field_data_static<10 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_SecondaryColorR; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_SecondaryColorR; }
  void SetDefault() { self.m_SecondaryColorR = StormReflTypeInfo<UIElementTextData>::GetDefault().m_SecondaryColorR; }
};

template <>
struct StormReflTypeInfo<UIElementTextData>::field_data_static<11 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_SecondaryColorG"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC3359C60; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 11 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextData::m_SecondaryColorG; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextData>::field_data<11 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n, Self> : public StormReflTypeInfo<UIElementTextData>::field_data_static<11 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_SecondaryColorG; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_SecondaryColorG; }
  void SetDefault() { self.m_SecondaryColorG = StormReflTypeInfo<UIElementTextData>::GetDefault().m_SecondaryColorG; }
};

template <>
struct StormReflTypeInfo<UIElementTextData>::field_data_static<12 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_SecondaryColorB"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB35F68EF; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 12 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextData::m_SecondaryColorB; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextData>::field_data<12 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n, Self> : public StormReflTypeInfo<UIElementTextData>::field_data_static<12 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_SecondaryColorB; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_SecondaryColorB; }
  void SetDefault() { self.m_SecondaryColorB = StormReflTypeInfo<UIElementTextData>::GetDefault().m_SecondaryColorB; }
};

template <>
struct StormReflTypeInfo<UIElementTextData>::field_data_static<13 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_SecondaryColorA"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2A563955; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 13 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextData::m_SecondaryColorA; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextData>::field_data<13 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n, Self> : public StormReflTypeInfo<UIElementTextData>::field_data_static<13 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_SecondaryColorA; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_SecondaryColorA; }
  void SetDefault() { self.m_SecondaryColorA = StormReflTypeInfo<UIElementTextData>::GetDefault().m_SecondaryColorA; }
};

namespace StormReflFileInfo
{
  struct UIElementText
  {
    static const int types_n = 2;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct UIElementText::type_info<0>
  {
    using type = ::UIElementTextInitData;
  };

  template <>
  struct UIElementText::type_info<1>
  {
    using type = ::UIElementTextData;
  };

}

