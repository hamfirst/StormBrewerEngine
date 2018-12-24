#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "AtlasDef.refl.h"


template <>
struct StormReflEnumInfo<AtlasDefType>
{
  static constexpr int elems_n = 5;
  static constexpr auto GetName() { return "AtlasDefType"; }
  static constexpr auto GetNameHash() { return 0xCF53918E; }
  template <int N> struct elems { };
};

template <>
struct StormReflEnumInfo<AtlasDefType>::elems<0>
{
  static constexpr auto GetName() { return "kImage"; }
  static constexpr auto GetNameHash() { return 0x112F827C; }
  static constexpr auto GetValue() { return AtlasDefType::kImage; }
};

template <>
struct StormReflEnumInfo<AtlasDefType>::elems<1>
{
  static constexpr auto GetName() { return "kRepeat"; }
  static constexpr auto GetNameHash() { return 0x0AE4D034; }
  static constexpr auto GetValue() { return AtlasDefType::kRepeat; }
};

template <>
struct StormReflEnumInfo<AtlasDefType>::elems<2>
{
  static constexpr auto GetName() { return "k3SliceVertical"; }
  static constexpr auto GetNameHash() { return 0x3629E125; }
  static constexpr auto GetValue() { return AtlasDefType::k3SliceVertical; }
};

template <>
struct StormReflEnumInfo<AtlasDefType>::elems<3>
{
  static constexpr auto GetName() { return "k3SliceHorizontal"; }
  static constexpr auto GetNameHash() { return 0xE661E82B; }
  static constexpr auto GetValue() { return AtlasDefType::k3SliceHorizontal; }
};

template <>
struct StormReflEnumInfo<AtlasDefType>::elems<4>
{
  static constexpr auto GetName() { return "k9Slice"; }
  static constexpr auto GetNameHash() { return 0x0DE531B8; }
  static constexpr auto GetValue() { return AtlasDefType::k9Slice; }
};

template <>
struct StormReflTypeInfo<AtlasDefTexture>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "AtlasDefTexture"; }
  static constexpr auto GetNameHash() { return 0x50F8C981; }
  static AtlasDefTexture & GetDefault() { static AtlasDefTexture def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<AtlasDefTexture *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const AtlasDefTexture *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<AtlasDefTexture *>(ptr);
    if(typeid(AtlasDefTexture).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const AtlasDefTexture *>(ptr);
    if(typeid(AtlasDefTexture).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<AtlasDefTexture>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Filename"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0xCA273D4B; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &AtlasDefTexture::m_Filename; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<AtlasDefTexture *>(obj); return &ptr->m_Filename; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const AtlasDefTexture *>(obj); return &ptr->m_Filename; }
};

template <typename Self>
struct StormReflTypeInfo<AtlasDefTexture>::field_data<0, Self> : public StormReflTypeInfo<AtlasDefTexture>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Filename; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Filename; }
  void SetDefault() { self.m_Filename = StormReflTypeInfo<AtlasDefTexture>::GetDefault().m_Filename; }
};

template <>
struct StormReflTypeInfo<AtlasDefTexture>::annotations<0>
{
  static constexpr int annotations_n = 1;
  template <int A> struct annoation { };
};

template <>
struct StormReflTypeInfo<AtlasDefTexture>::annotations<0>::annoation<0>
{
  static constexpr const char * GetAnnotation() { return "file: image"; }
  static constexpr uint32_t GetAnnotationHash() { return 0xD4E8122A; }
};

template <>
struct StormReflTypeInfo<AtlasDefElementPosition>
{
  using MyBase = void;
  static constexpr int fields_n = 11;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "AtlasDefElementPosition"; }
  static constexpr auto GetNameHash() { return 0xA116D4B1; }
  static AtlasDefElementPosition & GetDefault() { static AtlasDefElementPosition def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<AtlasDefElementPosition *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const AtlasDefElementPosition *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<AtlasDefElementPosition *>(ptr);
    if(typeid(AtlasDefElementPosition).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const AtlasDefElementPosition *>(ptr);
    if(typeid(AtlasDefElementPosition).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<AtlasDefElementPosition>::field_data_static<0>
{
  using member_type = REnum<AtlasDefType>; // REnum<AtlasDefType>
  static constexpr auto GetName() { return "m_Type"; }
  static constexpr auto GetType() { return "REnum<AtlasDefType>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB243C236; }
  static constexpr unsigned GetTypeNameHash() { return 0x10B463C8; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &AtlasDefElementPosition::m_Type; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<AtlasDefElementPosition *>(obj); return &ptr->m_Type; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const AtlasDefElementPosition *>(obj); return &ptr->m_Type; }
};

template <typename Self>
struct StormReflTypeInfo<AtlasDefElementPosition>::field_data<0, Self> : public StormReflTypeInfo<AtlasDefElementPosition>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, REnum<AtlasDefType>> & Get() { return self.m_Type; }
  std::add_const_t<std::remove_reference_t<REnum<AtlasDefType>>> & Get() const { return self.m_Type; }
  void SetDefault() { self.m_Type = StormReflTypeInfo<AtlasDefElementPosition>::GetDefault().m_Type; }
};

template <>
struct StormReflTypeInfo<AtlasDefElementPosition>::field_data_static<1>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_StartX"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x87158667; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &AtlasDefElementPosition::m_StartX; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<AtlasDefElementPosition *>(obj); return &ptr->m_StartX; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const AtlasDefElementPosition *>(obj); return &ptr->m_StartX; }
};

template <typename Self>
struct StormReflTypeInfo<AtlasDefElementPosition>::field_data<1, Self> : public StormReflTypeInfo<AtlasDefElementPosition>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_StartX; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_StartX; }
  void SetDefault() { self.m_StartX = StormReflTypeInfo<AtlasDefElementPosition>::GetDefault().m_StartX; }
};

template <>
struct StormReflTypeInfo<AtlasDefElementPosition>::field_data_static<2>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_StartY"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF012B6F1; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &AtlasDefElementPosition::m_StartY; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<AtlasDefElementPosition *>(obj); return &ptr->m_StartY; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const AtlasDefElementPosition *>(obj); return &ptr->m_StartY; }
};

template <typename Self>
struct StormReflTypeInfo<AtlasDefElementPosition>::field_data<2, Self> : public StormReflTypeInfo<AtlasDefElementPosition>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_StartY; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_StartY; }
  void SetDefault() { self.m_StartY = StormReflTypeInfo<AtlasDefElementPosition>::GetDefault().m_StartY; }
};

template <>
struct StormReflTypeInfo<AtlasDefElementPosition>::field_data_static<3>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_EndX"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3549DC7D; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &AtlasDefElementPosition::m_EndX; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<AtlasDefElementPosition *>(obj); return &ptr->m_EndX; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const AtlasDefElementPosition *>(obj); return &ptr->m_EndX; }
};

template <typename Self>
struct StormReflTypeInfo<AtlasDefElementPosition>::field_data<3, Self> : public StormReflTypeInfo<AtlasDefElementPosition>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_EndX; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_EndX; }
  void SetDefault() { self.m_EndX = StormReflTypeInfo<AtlasDefElementPosition>::GetDefault().m_EndX; }
};

template <>
struct StormReflTypeInfo<AtlasDefElementPosition>::field_data_static<4>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_EndY"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x424EECEB; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &AtlasDefElementPosition::m_EndY; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<AtlasDefElementPosition *>(obj); return &ptr->m_EndY; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const AtlasDefElementPosition *>(obj); return &ptr->m_EndY; }
};

template <typename Self>
struct StormReflTypeInfo<AtlasDefElementPosition>::field_data<4, Self> : public StormReflTypeInfo<AtlasDefElementPosition>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_EndY; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_EndY; }
  void SetDefault() { self.m_EndY = StormReflTypeInfo<AtlasDefElementPosition>::GetDefault().m_EndY; }
};

template <>
struct StormReflTypeInfo<AtlasDefElementPosition>::field_data_static<5>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_StartOffsetX"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6AFBDEBC; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &AtlasDefElementPosition::m_StartOffsetX; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<AtlasDefElementPosition *>(obj); return &ptr->m_StartOffsetX; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const AtlasDefElementPosition *>(obj); return &ptr->m_StartOffsetX; }
};

template <typename Self>
struct StormReflTypeInfo<AtlasDefElementPosition>::field_data<5, Self> : public StormReflTypeInfo<AtlasDefElementPosition>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_StartOffsetX; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_StartOffsetX; }
  void SetDefault() { self.m_StartOffsetX = StormReflTypeInfo<AtlasDefElementPosition>::GetDefault().m_StartOffsetX; }
};

template <>
struct StormReflTypeInfo<AtlasDefElementPosition>::field_data_static<6>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_StartOffsetY"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1DFCEE2A; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &AtlasDefElementPosition::m_StartOffsetY; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<AtlasDefElementPosition *>(obj); return &ptr->m_StartOffsetY; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const AtlasDefElementPosition *>(obj); return &ptr->m_StartOffsetY; }
};

template <typename Self>
struct StormReflTypeInfo<AtlasDefElementPosition>::field_data<6, Self> : public StormReflTypeInfo<AtlasDefElementPosition>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_StartOffsetY; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_StartOffsetY; }
  void SetDefault() { self.m_StartOffsetY = StormReflTypeInfo<AtlasDefElementPosition>::GetDefault().m_StartOffsetY; }
};

template <>
struct StormReflTypeInfo<AtlasDefElementPosition>::field_data_static<7>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_EndOffsetX"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFD14B24F; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &AtlasDefElementPosition::m_EndOffsetX; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<AtlasDefElementPosition *>(obj); return &ptr->m_EndOffsetX; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const AtlasDefElementPosition *>(obj); return &ptr->m_EndOffsetX; }
};

template <typename Self>
struct StormReflTypeInfo<AtlasDefElementPosition>::field_data<7, Self> : public StormReflTypeInfo<AtlasDefElementPosition>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_EndOffsetX; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_EndOffsetX; }
  void SetDefault() { self.m_EndOffsetX = StormReflTypeInfo<AtlasDefElementPosition>::GetDefault().m_EndOffsetX; }
};

template <>
struct StormReflTypeInfo<AtlasDefElementPosition>::field_data_static<8>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_EndOffsetY"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8A1382D9; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 8; }
  static constexpr auto GetMemberPtr() { return &AtlasDefElementPosition::m_EndOffsetY; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<AtlasDefElementPosition *>(obj); return &ptr->m_EndOffsetY; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const AtlasDefElementPosition *>(obj); return &ptr->m_EndOffsetY; }
};

template <typename Self>
struct StormReflTypeInfo<AtlasDefElementPosition>::field_data<8, Self> : public StormReflTypeInfo<AtlasDefElementPosition>::field_data_static<8>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_EndOffsetY; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_EndOffsetY; }
  void SetDefault() { self.m_EndOffsetY = StormReflTypeInfo<AtlasDefElementPosition>::GetDefault().m_EndOffsetY; }
};

template <>
struct StormReflTypeInfo<AtlasDefElementPosition>::field_data_static<9>
{
  using member_type = RBool; // RBool
  static constexpr auto GetName() { return "m_RepeatHorizontal"; }
  static constexpr auto GetType() { return "RBool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3AC5A533; }
  static constexpr unsigned GetTypeNameHash() { return 0x50062D06; }
  static constexpr auto GetFieldIndex() { return 9; }
  static constexpr auto GetMemberPtr() { return &AtlasDefElementPosition::m_RepeatHorizontal; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<AtlasDefElementPosition *>(obj); return &ptr->m_RepeatHorizontal; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const AtlasDefElementPosition *>(obj); return &ptr->m_RepeatHorizontal; }
};

template <typename Self>
struct StormReflTypeInfo<AtlasDefElementPosition>::field_data<9, Self> : public StormReflTypeInfo<AtlasDefElementPosition>::field_data_static<9>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RBool> & Get() { return self.m_RepeatHorizontal; }
  std::add_const_t<std::remove_reference_t<RBool>> & Get() const { return self.m_RepeatHorizontal; }
  void SetDefault() { self.m_RepeatHorizontal = StormReflTypeInfo<AtlasDefElementPosition>::GetDefault().m_RepeatHorizontal; }
};

template <>
struct StormReflTypeInfo<AtlasDefElementPosition>::field_data_static<10>
{
  using member_type = RBool; // RBool
  static constexpr auto GetName() { return "m_RepeatVertical"; }
  static constexpr auto GetType() { return "RBool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x71994AE3; }
  static constexpr unsigned GetTypeNameHash() { return 0x50062D06; }
  static constexpr auto GetFieldIndex() { return 10; }
  static constexpr auto GetMemberPtr() { return &AtlasDefElementPosition::m_RepeatVertical; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<AtlasDefElementPosition *>(obj); return &ptr->m_RepeatVertical; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const AtlasDefElementPosition *>(obj); return &ptr->m_RepeatVertical; }
};

template <typename Self>
struct StormReflTypeInfo<AtlasDefElementPosition>::field_data<10, Self> : public StormReflTypeInfo<AtlasDefElementPosition>::field_data_static<10>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RBool> & Get() { return self.m_RepeatVertical; }
  std::add_const_t<std::remove_reference_t<RBool>> & Get() const { return self.m_RepeatVertical; }
  void SetDefault() { self.m_RepeatVertical = StormReflTypeInfo<AtlasDefElementPosition>::GetDefault().m_RepeatVertical; }
};

template <>
struct StormReflTypeInfo<AtlasDefElement>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "AtlasDefElement"; }
  static constexpr auto GetNameHash() { return 0x93DE9ACA; }
  static AtlasDefElement & GetDefault() { static AtlasDefElement def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<AtlasDefElement *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const AtlasDefElement *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<AtlasDefElement *>(ptr);
    if(typeid(AtlasDefElement).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const AtlasDefElement *>(ptr);
    if(typeid(AtlasDefElement).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<AtlasDefElement>::field_data_static<0>
{
  using member_type = RUInt; // RNumber<unsigned int>
  static constexpr auto GetName() { return "m_TextureHash"; }
  static constexpr auto GetType() { return "RNumber<unsigned int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6D2A1F0B; }
  static constexpr unsigned GetTypeNameHash() { return 0x7B4FB98C; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &AtlasDefElement::m_TextureHash; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<AtlasDefElement *>(obj); return &ptr->m_TextureHash; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const AtlasDefElement *>(obj); return &ptr->m_TextureHash; }
};

template <typename Self>
struct StormReflTypeInfo<AtlasDefElement>::field_data<0, Self> : public StormReflTypeInfo<AtlasDefElement>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RUInt> & Get() { return self.m_TextureHash; }
  std::add_const_t<std::remove_reference_t<RUInt>> & Get() const { return self.m_TextureHash; }
  void SetDefault() { self.m_TextureHash = StormReflTypeInfo<AtlasDefElement>::GetDefault().m_TextureHash; }
};

template <>
struct StormReflTypeInfo<AtlasDefElement>::annotations<0>
{
  static constexpr int annotations_n = 1;
  template <int A> struct annoation { };
};

template <>
struct StormReflTypeInfo<AtlasDefElement>::annotations<0>::annoation<0>
{
  static constexpr const char * GetAnnotation() { return "noui"; }
  static constexpr uint32_t GetAnnotationHash() { return 0xDF10877E; }
};

template <>
struct StormReflTypeInfo<AtlasDefElement>::field_data_static<1>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &AtlasDefElement::m_Name; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<AtlasDefElement *>(obj); return &ptr->m_Name; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const AtlasDefElement *>(obj); return &ptr->m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<AtlasDefElement>::field_data<1, Self> : public StormReflTypeInfo<AtlasDefElement>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<AtlasDefElement>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<AtlasDefElement>::field_data_static<2>
{
  using member_type = AtlasDefElementPosition; // AtlasDefElementPosition
  static constexpr auto GetName() { return "m_Data"; }
  static constexpr auto GetType() { return "AtlasDefElementPosition"; }
  static constexpr unsigned GetFieldNameHash() { return 0x936E667C; }
  static constexpr unsigned GetTypeNameHash() { return 0xA116D4B1; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &AtlasDefElement::m_Data; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<AtlasDefElement *>(obj); return &ptr->m_Data; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const AtlasDefElement *>(obj); return &ptr->m_Data; }
};

template <typename Self>
struct StormReflTypeInfo<AtlasDefElement>::field_data<2, Self> : public StormReflTypeInfo<AtlasDefElement>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, AtlasDefElementPosition> & Get() { return self.m_Data; }
  std::add_const_t<std::remove_reference_t<AtlasDefElementPosition>> & Get() const { return self.m_Data; }
  void SetDefault() { self.m_Data = StormReflTypeInfo<AtlasDefElement>::GetDefault().m_Data; }
};

template <>
struct StormReflTypeInfo<AtlasDef>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "AtlasDef"; }
  static constexpr auto GetNameHash() { return 0xF114091F; }
  static AtlasDef & GetDefault() { static AtlasDef def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<AtlasDef *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const AtlasDef *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<AtlasDef *>(ptr);
    if(typeid(AtlasDef).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const AtlasDef *>(ptr);
    if(typeid(AtlasDef).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<AtlasDef>::field_data_static<0>
{
  using member_type = RMergeList<AtlasDefTexture>; // RMergeList<AtlasDefTexture>
  static constexpr auto GetName() { return "m_Textures"; }
  static constexpr auto GetType() { return "RMergeList<AtlasDefTexture>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x53AB6D38; }
  static constexpr unsigned GetTypeNameHash() { return 0xF0B96596; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &AtlasDef::m_Textures; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<AtlasDef *>(obj); return &ptr->m_Textures; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const AtlasDef *>(obj); return &ptr->m_Textures; }
};

template <typename Self>
struct StormReflTypeInfo<AtlasDef>::field_data<0, Self> : public StormReflTypeInfo<AtlasDef>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<AtlasDefTexture>> & Get() { return self.m_Textures; }
  std::add_const_t<std::remove_reference_t<RMergeList<AtlasDefTexture>>> & Get() const { return self.m_Textures; }
  void SetDefault() { self.m_Textures = StormReflTypeInfo<AtlasDef>::GetDefault().m_Textures; }
};

template <>
struct StormReflTypeInfo<AtlasDef>::field_data_static<1>
{
  using member_type = RMergeList<AtlasDefElement>; // RMergeList<AtlasDefElement>
  static constexpr auto GetName() { return "m_Elements"; }
  static constexpr auto GetType() { return "RMergeList<AtlasDefElement>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB266D373; }
  static constexpr unsigned GetTypeNameHash() { return 0x1174DBDD; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &AtlasDef::m_Elements; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<AtlasDef *>(obj); return &ptr->m_Elements; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const AtlasDef *>(obj); return &ptr->m_Elements; }
};

template <typename Self>
struct StormReflTypeInfo<AtlasDef>::field_data<1, Self> : public StormReflTypeInfo<AtlasDef>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<AtlasDefElement>> & Get() { return self.m_Elements; }
  std::add_const_t<std::remove_reference_t<RMergeList<AtlasDefElement>>> & Get() const { return self.m_Elements; }
  void SetDefault() { self.m_Elements = StormReflTypeInfo<AtlasDef>::GetDefault().m_Elements; }
};

namespace StormReflFileInfo
{
  struct AtlasDef
  {
    static const int types_n = 4;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct AtlasDef::type_info<0>
  {
    using type = ::AtlasDefTexture;
  };

  template <>
  struct AtlasDef::type_info<1>
  {
    using type = ::AtlasDefElementPosition;
  };

  template <>
  struct AtlasDef::type_info<2>
  {
    using type = ::AtlasDefElement;
  };

  template <>
  struct AtlasDef::type_info<3>
  {
    using type = ::AtlasDef;
  };

}

