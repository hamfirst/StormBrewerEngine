#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "DocumentServerMessages.refl.h"


template <>
struct StormReflEnumInfo<DocumentServerMessageType>
{
  static constexpr int elems_n = 9;
  static constexpr auto GetName() { return "DocumentServerMessageType"; }
  static constexpr auto GetNameHash() { return 0x2984BE49; }
  template <int N> struct elems { };
};

template <>
struct StormReflEnumInfo<DocumentServerMessageType>::elems<0>
{
  static constexpr auto GetName() { return "kUnknown"; }
  static constexpr auto GetNameHash() { return 0x175422A1; }
  static constexpr auto GetValue() { return DocumentServerMessageType::kUnknown; }
};

template <>
struct StormReflEnumInfo<DocumentServerMessageType>::elems<1>
{
  static constexpr auto GetName() { return "kNew"; }
  static constexpr auto GetNameHash() { return 0x618C74A9; }
  static constexpr auto GetValue() { return DocumentServerMessageType::kNew; }
};

template <>
struct StormReflEnumInfo<DocumentServerMessageType>::elems<2>
{
  static constexpr auto GetName() { return "kOpen"; }
  static constexpr auto GetNameHash() { return 0x0DC642C7; }
  static constexpr auto GetValue() { return DocumentServerMessageType::kOpen; }
};

template <>
struct StormReflEnumInfo<DocumentServerMessageType>::elems<3>
{
  static constexpr auto GetName() { return "kClose"; }
  static constexpr auto GetNameHash() { return 0xC71307E7; }
  static constexpr auto GetValue() { return DocumentServerMessageType::kClose; }
};

template <>
struct StormReflEnumInfo<DocumentServerMessageType>::elems<4>
{
  static constexpr auto GetName() { return "kDelete"; }
  static constexpr auto GetNameHash() { return 0x98A11F73; }
  static constexpr auto GetValue() { return DocumentServerMessageType::kDelete; }
};

template <>
struct StormReflEnumInfo<DocumentServerMessageType>::elems<5>
{
  static constexpr auto GetName() { return "kChange"; }
  static constexpr auto GetNameHash() { return 0xE2E49DD4; }
  static constexpr auto GetValue() { return DocumentServerMessageType::kChange; }
};

template <>
struct StormReflEnumInfo<DocumentServerMessageType>::elems<6>
{
  static constexpr auto GetName() { return "kSave"; }
  static constexpr auto GetNameHash() { return 0xFCD0FBBD; }
  static constexpr auto GetValue() { return DocumentServerMessageType::kSave; }
};

template <>
struct StormReflEnumInfo<DocumentServerMessageType>::elems<7>
{
  static constexpr auto GetName() { return "kUndo"; }
  static constexpr auto GetNameHash() { return 0x4AC67A91; }
  static constexpr auto GetValue() { return DocumentServerMessageType::kUndo; }
};

template <>
struct StormReflEnumInfo<DocumentServerMessageType>::elems<8>
{
  static constexpr auto GetName() { return "kRedo"; }
  static constexpr auto GetNameHash() { return 0xDB44ADC9; }
  static constexpr auto GetValue() { return DocumentServerMessageType::kRedo; }
};

template <>
struct StormReflEnumInfo<DocumentClientMessageType>
{
  static constexpr int elems_n = 8;
  static constexpr auto GetName() { return "DocumentClientMessageType"; }
  static constexpr auto GetNameHash() { return 0x6B1F13AF; }
  template <int N> struct elems { };
};

template <>
struct StormReflEnumInfo<DocumentClientMessageType>::elems<0>
{
  static constexpr auto GetName() { return "kUnknown"; }
  static constexpr auto GetNameHash() { return 0x175422A1; }
  static constexpr auto GetValue() { return DocumentClientMessageType::kUnknown; }
};

template <>
struct StormReflEnumInfo<DocumentClientMessageType>::elems<1>
{
  static constexpr auto GetName() { return "kNewFileError"; }
  static constexpr auto GetNameHash() { return 0x2637FE07; }
  static constexpr auto GetValue() { return DocumentClientMessageType::kNewFileError; }
};

template <>
struct StormReflEnumInfo<DocumentClientMessageType>::elems<2>
{
  static constexpr auto GetName() { return "kOpenFileError"; }
  static constexpr auto GetNameHash() { return 0x6E791BDD; }
  static constexpr auto GetValue() { return DocumentClientMessageType::kOpenFileError; }
};

template <>
struct StormReflEnumInfo<DocumentClientMessageType>::elems<3>
{
  static constexpr auto GetName() { return "kDocumentState"; }
  static constexpr auto GetNameHash() { return 0x3697C103; }
  static constexpr auto GetValue() { return DocumentClientMessageType::kDocumentState; }
};

template <>
struct StormReflEnumInfo<DocumentClientMessageType>::elems<4>
{
  static constexpr auto GetName() { return "kDocumentClosed"; }
  static constexpr auto GetNameHash() { return 0xB73433D9; }
  static constexpr auto GetValue() { return DocumentClientMessageType::kDocumentClosed; }
};

template <>
struct StormReflEnumInfo<DocumentClientMessageType>::elems<5>
{
  static constexpr auto GetName() { return "kChange"; }
  static constexpr auto GetNameHash() { return 0xE2E49DD4; }
  static constexpr auto GetValue() { return DocumentClientMessageType::kChange; }
};

template <>
struct StormReflEnumInfo<DocumentClientMessageType>::elems<6>
{
  static constexpr auto GetName() { return "kChangeOk"; }
  static constexpr auto GetNameHash() { return 0x87B2F4E3; }
  static constexpr auto GetValue() { return DocumentClientMessageType::kChangeOk; }
};

template <>
struct StormReflEnumInfo<DocumentClientMessageType>::elems<7>
{
  static constexpr auto GetName() { return "kChangeLinks"; }
  static constexpr auto GetNameHash() { return 0xE1BF87EE; }
  static constexpr auto GetValue() { return DocumentClientMessageType::kChangeLinks; }
};

namespace StormReflFileInfo
{
  struct DocumentServerMessages
  {
    static const int types_n = 0;
    template <int i> struct type_info { using type = void; };
  };

}

