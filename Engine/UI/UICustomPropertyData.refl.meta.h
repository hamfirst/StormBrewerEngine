#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "UICustomPropertyData.refl.h"


template <>
struct StormReflEnumInfo<UICustomPropertyDataType>
{
  static constexpr int elems_n = 2;
  static constexpr auto GetName() { return "UICustomPropertyDataType"; }
  static constexpr auto GetNameHash() { return 0x51D3AC54; }
  template <int N> struct elems { };
};

template <>
struct StormReflEnumInfo<UICustomPropertyDataType>::elems<0>
{
  static constexpr auto GetName() { return "kNumber"; }
  static constexpr auto GetNameHash() { return 0x34237CA0; }
  static constexpr auto GetValue() { return UICustomPropertyDataType::kNumber; }
};

template <>
struct StormReflEnumInfo<UICustomPropertyDataType>::elems<1>
{
  static constexpr auto GetName() { return "kString"; }
  static constexpr auto GetNameHash() { return 0x3C0DD15D; }
  static constexpr auto GetValue() { return UICustomPropertyDataType::kString; }
};

namespace StormReflFileInfo
{
  struct UICustomPropertyData
  {
    static const int types_n = 0;
    template <int i> struct type_info { using type = void; };
  };

}

