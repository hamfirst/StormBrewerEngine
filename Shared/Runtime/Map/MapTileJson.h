#pragma once

#include "StormRefl/StormReflJson.h"

#include "Runtime/Map/MapTile.h"

template <>
struct StormReflJson<MapTile, void>
{
  template <class StringBuilder>
  static void Encode(const MapTile & t, StringBuilder & sb)
  {
    uint64_t x = (uint64_t)t.x;
    uint64_t y = (uint64_t)t.y;

    uint64_t p = (x << 32) | (y & 0xFFFFFFFF);
    uint64_t h = (uint64_t)t.m_TextureHash;
    uint64_t d = (h << 32) | t.m_FrameId;

    char val[512];
    snprintf(val, sizeof(val), "[%zu, %zu]", p, d);
    sb += val;
  }

  template <class StringBuilder>
  static void EncodePretty(const MapTile & t, StringBuilder & sb, int indent)
  {
    Encode(t, sb);
  }

  template <class StringBuilder>
  static void SerializeDefault(StringBuilder & sb)
  {
    sb += "[0,0]";
  }

  template <typename CharPtr>
  static bool Parse(MapTile & t, CharPtr str, CharPtr & result, bool additive)
  {
    if (*str != '[')
    {
      return false;
    }

    str++;
    uint64_t p;
    if (StormReflParseJson(p, str, str) == false)
    {
      return false;
    }

    StormReflJsonAdvanceWhiteSpace(str);
    if (*str != ',')
    {
      return false;
    }

    str++;

    uint64_t d;
    if (StormReflParseJson(d, str, str) == false)
    {
      return false;
    }

    StormReflJsonAdvanceWhiteSpace(str);
    if (*str != ']')
    {
      return false;
    }

    t.x = (int)(p >> 32);
    t.y = (int)(p & 0xFFFFFFFF);
    t.m_TextureHash = (uint32_t)(d >> 32);
    t.m_FrameId = (uint32_t)(d & 0xFFFFFFFF);

    str++;
    result = str;
    return true;
  }
};


template <>
struct StormReflJson<MapAnimatedTile, void>
{
  template <class StringBuilder>
  static void Encode(const MapAnimatedTile & t, StringBuilder & sb)
  {
    uint64_t x = (uint64_t)t.x;
    uint64_t y = (uint64_t)t.y;

    uint64_t p = (x << 32) | (y & 0xFFFFFFFF);
    uint64_t h = (uint64_t)t.m_Animation;
    uint64_t d = (h << 32) | t.m_FrameOffset;

    char val[512];
    snprintf(val, sizeof(val), "[%zu, %zu]", p, d);
    sb += val;
  }

  template <class StringBuilder>
  static void EncodePretty(const MapAnimatedTile & t, StringBuilder & sb, int indent)
  {
    Encode(t, sb);
  }

  template <class StringBuilder>
  static void SerializeDefault(StringBuilder & sb)
  {
    sb += "[0,0]";
  }

  template <typename CharPtr>
  static bool Parse(MapAnimatedTile & t, CharPtr str, CharPtr & result, bool additive)
  {
    if (*str != '[')
    {
      return false;
    }

    str++;
    uint64_t p;
    if (StormReflParseJson(p, str, str) == false)
    {
      return false;
    }

    StormReflJsonAdvanceWhiteSpace(str);
    if (*str != ',')
    {
      return false;
    }

    str++;

    uint64_t d;
    if (StormReflParseJson(d, str, str) == false)
    {
      return false;
    }

    StormReflJsonAdvanceWhiteSpace(str);
    if (*str != ']')
    {
      return false;
    }

    t.x = (int)(p >> 32);
    t.y = (int)(p & 0xFFFFFFFF);
    t.m_Animation = (uint32_t)(d >> 32);
    t.m_FrameOffset = (uint32_t)(d & 0xFFFFFFFF);

    str++;
    result = str;
    return true;
  }
};
