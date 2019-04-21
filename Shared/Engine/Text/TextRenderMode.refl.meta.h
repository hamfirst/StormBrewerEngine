#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "TextRenderMode.refl.h"


template <>
struct StormReflEnumInfo<TextRenderMode>
{
  static constexpr int elems_n = 3;
  static constexpr auto GetName() { return "TextRenderMode"; }
  static constexpr auto GetNameHash() { return 0x4C67D059; }
  template <int N> struct elems { };
};

template <>
struct StormReflEnumInfo<TextRenderMode>::elems<0>
{
  static constexpr auto GetName() { return "kNormal"; }
  static constexpr auto GetNameHash() { return 0x83360B10; }
  static constexpr auto GetValue() { return TextRenderMode::kNormal; }
};

template <>
struct StormReflEnumInfo<TextRenderMode>::elems<1>
{
  static constexpr auto GetName() { return "kShadowed"; }
  static constexpr auto GetNameHash() { return 0x947B5321; }
  static constexpr auto GetValue() { return TextRenderMode::kShadowed; }
};

template <>
struct StormReflEnumInfo<TextRenderMode>::elems<2>
{
  static constexpr auto GetName() { return "kOutlined"; }
  static constexpr auto GetNameHash() { return 0xEC919581; }
  static constexpr auto GetValue() { return TextRenderMode::kOutlined; }
};

namespace StormReflFileInfo
{
  struct TextRenderMode
  {
    static const int types_n = 0;
    template <int i> struct type_info { using type = void; };
  };

}

