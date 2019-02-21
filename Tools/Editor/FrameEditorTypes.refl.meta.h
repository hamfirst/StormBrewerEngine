#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "FrameEditorTypes.refl.h"
#include "Runtime/FrameData/FrameData.refl.meta.h"


template <>
struct StormReflTypeInfo<FrameCopyData>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "FrameCopyData"; }
  static constexpr auto GetNameHash() { return 0x7053E070; }
  static constexpr bool HasDefault() { return true; }
  static FrameCopyData & GetDefault() { static FrameCopyData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<FrameCopyData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const FrameCopyData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<FrameCopyData *>(ptr);
    if(typeid(FrameCopyData).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const FrameCopyData *>(ptr);
    if(typeid(FrameCopyData).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<FrameCopyData>::field_data_static<0>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_Valid"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0131A59F; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &FrameCopyData::m_Valid; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<FrameCopyData *>(obj); return &ptr->m_Valid; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const FrameCopyData *>(obj); return &ptr->m_Valid; }
};

template <typename Self>
struct StormReflTypeInfo<FrameCopyData>::field_data<0, Self> : public StormReflTypeInfo<FrameCopyData>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_Valid; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_Valid; }
  void SetDefault() { self.m_Valid = StormReflTypeInfo<FrameCopyData>::GetDefault().m_Valid; }
};

template <>
struct StormReflTypeInfo<FrameCopyData>::field_data_static<1>
{
  using member_type = FrameDataDefType; // FrameDataDefType
  static constexpr auto GetName() { return "m_Type"; }
  static constexpr auto GetType() { return "FrameDataDefType"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB243C236; }
  static constexpr unsigned GetTypeNameHash() { return 0xCD6F2DAB; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &FrameCopyData::m_Type; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<FrameCopyData *>(obj); return &ptr->m_Type; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const FrameCopyData *>(obj); return &ptr->m_Type; }
};

template <typename Self>
struct StormReflTypeInfo<FrameCopyData>::field_data<1, Self> : public StormReflTypeInfo<FrameCopyData>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, FrameDataDefType> & Get() { return self.m_Type; }
  std::add_const_t<std::remove_reference_t<FrameDataDefType>> & Get() const { return self.m_Type; }
  void SetDefault() { self.m_Type = StormReflTypeInfo<FrameCopyData>::GetDefault().m_Type; }
};

template <>
struct StormReflTypeInfo<FrameCopyData>::field_data_static<2>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Data"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x936E667C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &FrameCopyData::m_Data; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<FrameCopyData *>(obj); return &ptr->m_Data; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const FrameCopyData *>(obj); return &ptr->m_Data; }
};

template <typename Self>
struct StormReflTypeInfo<FrameCopyData>::field_data<2, Self> : public StormReflTypeInfo<FrameCopyData>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Data; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Data; }
  void SetDefault() { self.m_Data = StormReflTypeInfo<FrameCopyData>::GetDefault().m_Data; }
};

namespace StormReflFileInfo
{
  struct FrameEditorTypes
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct FrameEditorTypes::type_info<0>
  {
    using type = ::FrameCopyData;
  };

}

