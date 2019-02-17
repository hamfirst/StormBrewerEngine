#pragma once

#include "StormRefl/StormReflJson.h"
#include "StormNet/NetReflectionFixedPoint.h"

#include "Foundation/Math/Intersection.h"

template <typename StorageType, StorageType NumBits, StorageType FractionalBits>
struct StormReflJson<NetFixedPoint<StorageType, NumBits, FractionalBits>, void>
{
  template <class StringBuilder>
  static void Encode(const NetFixedPoint<StorageType, NumBits, FractionalBits> & t, StringBuilder & sb)
  {
    StormReflJson<StorageType>::Encode(t, sb);
  }

  template <class StringBuilder>
  static void EncodePretty(const NetFixedPoint<StorageType, NumBits, FractionalBits> & t, StringBuilder & sb, int indent)
  {
    StormReflJson<StorageType>::Encode(t, sb);
  }

  template <class StringBuilder>
  static void SerializeDefault(StringBuilder & sb)
  {
    sb += "0";
  }

  template <typename CharPtr>
  static bool Parse(NetFixedPoint<StorageType, NumBits, FractionalBits> & t, CharPtr str, CharPtr & result, bool additive)
  {
    StorageType val;
    if (StormReflJson<StorageType>::Parse(val, str, result, additive) == false)
    {
      return false;
    }

    t = val;
    return true;
  }
};


template <typename VecCompType>
struct StormReflJson<IntersectionVecType<VecCompType>, void>
{
  template <class StringBuilder>
  static void Encode(const IntersectionVecType<VecCompType> & t, StringBuilder & sb)
  {
    sb += '[';
    StormReflJson<VecCompType>::Encode(t.x, sb);
    sb += ',';
    StormReflJson<VecCompType>::Encode(t.y, sb);
    sb += ']';
  }

  template <class StringBuilder>
  static void EncodePretty(const IntersectionVecType<VecCompType> & t, StringBuilder & sb, int indent)
  {
    sb += '[';
    StormReflJson<VecCompType>::Encode(t.x, sb);
    sb += ',';
    StormReflJson<VecCompType>::Encode(t.y, sb);
    sb += ']';
  }

  template <class StringBuilder>
  static void SerializeDefault(StringBuilder & sb)
  {
    sb += "[0, 0]";
  }

  template <typename CharPtr>
  static bool Parse(IntersectionVecType<VecCompType> & t, CharPtr str, CharPtr & result, bool additive)
  {
    StormReflJsonAdvanceWhiteSpace(str);
    if (*str != '[')
    {
      return false;
    }

    str++;    
    if (StormReflParseJson(t.x, str, str, additive) == false)
    {
      return false;
    }

    StormReflJsonAdvanceWhiteSpace(str);
    if (*str != ',')
    {
      return false;
    }

    str++;
    StormReflJsonAdvanceWhiteSpace(str);
    if (StormReflParseJson(t.y, str, str, additive) == false)
    {
      return false;
    }

    StormReflJsonAdvanceWhiteSpace(str);
    if (*str != ']')
    {
      return false;
    }

    str++;
    result = str;
    return true;
  }
};
