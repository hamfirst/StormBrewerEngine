#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "UITypes.refl.h"


template <>
struct StormReflEnumInfo<UIVariableType>
{
  static constexpr int elems_n = 2;
  static constexpr auto GetName() { return "UIVariableType"; }
  static constexpr auto GetNameHash() { return 0x2B4F7EC4; }
  template <int N> struct elems { };
};

template <>
struct StormReflEnumInfo<UIVariableType>::elems<0>
{
  static constexpr auto GetName() { return "kFloat"; }
  static constexpr auto GetNameHash() { return 0x1DB7D8B6; }
  static constexpr auto GetValue() { return UIVariableType::kFloat; }
};

template <>
struct StormReflEnumInfo<UIVariableType>::elems<1>
{
  static constexpr auto GetName() { return "kString"; }
  static constexpr auto GetNameHash() { return 0x3C0DD15D; }
  static constexpr auto GetValue() { return UIVariableType::kString; }
};

template <>
struct StormReflEnumInfo<UIElementType>
{
  static constexpr int elems_n = 8;
  static constexpr auto GetName() { return "UIElementType"; }
  static constexpr auto GetNameHash() { return 0x6D4F033F; }
  template <int N> struct elems { };
};

template <>
struct StormReflEnumInfo<UIElementType>::elems<0>
{
  static constexpr auto GetName() { return "kContainer"; }
  static constexpr auto GetNameHash() { return 0x69D7EDE7; }
  static constexpr auto GetValue() { return UIElementType::kContainer; }
};

template <>
struct StormReflEnumInfo<UIElementType>::elems<1>
{
  static constexpr auto GetName() { return "kGradient"; }
  static constexpr auto GetNameHash() { return 0x6BAE4E1D; }
  static constexpr auto GetValue() { return UIElementType::kGradient; }
};

template <>
struct StormReflEnumInfo<UIElementType>::elems<2>
{
  static constexpr auto GetName() { return "kTextureSlice"; }
  static constexpr auto GetNameHash() { return 0x4D524F60; }
  static constexpr auto GetValue() { return UIElementType::kTextureSlice; }
};

template <>
struct StormReflEnumInfo<UIElementType>::elems<3>
{
  static constexpr auto GetName() { return "kSpriteFrame"; }
  static constexpr auto GetNameHash() { return 0xD6F4EE12; }
  static constexpr auto GetValue() { return UIElementType::kSpriteFrame; }
};

template <>
struct StormReflEnumInfo<UIElementType>::elems<4>
{
  static constexpr auto GetName() { return "kText"; }
  static constexpr auto GetNameHash() { return 0x923D66A4; }
  static constexpr auto GetValue() { return UIElementType::kText; }
};

template <>
struct StormReflEnumInfo<UIElementType>::elems<5>
{
  static constexpr auto GetName() { return "kShape"; }
  static constexpr auto GetNameHash() { return 0x092279FB; }
  static constexpr auto GetValue() { return UIElementType::kShape; }
};

template <>
struct StormReflEnumInfo<UIElementType>::elems<6>
{
  static constexpr auto GetName() { return "kFullTexture"; }
  static constexpr auto GetNameHash() { return 0xE12CBFCD; }
  static constexpr auto GetValue() { return UIElementType::kFullTexture; }
};

template <>
struct StormReflEnumInfo<UIElementType>::elems<7>
{
  static constexpr auto GetName() { return "kTextInput"; }
  static constexpr auto GetNameHash() { return 0xEDC71201; }
  static constexpr auto GetValue() { return UIElementType::kTextInput; }
};

namespace StormReflFileInfo
{
  struct UITypes
  {
    static const int types_n = 0;
    template <int i> struct type_info { using type = void; };
  };

}

