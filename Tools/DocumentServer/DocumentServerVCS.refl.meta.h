#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "DocumentServerVCS.refl.h"


template <>
struct StormReflEnumInfo<DocumentServerVCSType>
{
  static constexpr int elems_n = 1;
  static constexpr auto GetName() { return "DocumentServerVCSType"; }
  static constexpr auto GetNameHash() { return 0x75F91A91; }
  template <int N> struct elems { };
};

template <>
struct StormReflEnumInfo<DocumentServerVCSType>::elems<0>
{
  static constexpr auto GetName() { return "Git"; }
  static constexpr auto GetNameHash() { return 0x69C3279C; }
  static constexpr auto GetValue() { return Git; }
};

template <>
struct StormReflTypeInfo<DocumentServerVCSInitData>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DocumentServerVCSInitData"; }
  static constexpr auto GetNameHash() { return 0xC00348A6; }
  static constexpr bool HasDefault() { return true; }
  static DocumentServerVCSInitData & GetDefault() { static DocumentServerVCSInitData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DocumentServerVCSInitData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DocumentServerVCSInitData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DocumentServerVCSInitData *>(ptr);
    if(typeid(DocumentServerVCSInitData).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DocumentServerVCSInitData *>(ptr);
    if(typeid(DocumentServerVCSInitData).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DocumentServerVCSInitData>::field_data_static<0>
{
  using member_type = DocumentServerVCSType; // DocumentServerVCSType
  static constexpr auto GetName() { return "Type"; }
  static constexpr auto GetType() { return "DocumentServerVCSType"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2CECF817; }
  static constexpr unsigned GetTypeNameHash() { return 0x75F91A91; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DocumentServerVCSInitData::Type; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DocumentServerVCSInitData *>(obj); return &ptr->Type; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DocumentServerVCSInitData *>(obj); return &ptr->Type; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerVCSInitData>::field_data<0, Self> : public StormReflTypeInfo<DocumentServerVCSInitData>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DocumentServerVCSType> & Get() { return self.Type; }
  std::add_const_t<std::remove_reference_t<DocumentServerVCSType>> & Get() const { return self.Type; }
  void SetDefault() { self.Type = StormReflTypeInfo<DocumentServerVCSInitData>::GetDefault().Type; }
};

namespace StormReflFileInfo
{
  struct DocumentServerVCS
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct DocumentServerVCS::type_info<0>
  {
    using type = ::DocumentServerVCSInitData;
  };

}

