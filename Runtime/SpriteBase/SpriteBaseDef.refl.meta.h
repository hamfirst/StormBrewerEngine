#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "SpriteBaseDef.refl.h"
#include "Runtime/FrameData/FrameData.refl.meta.h"


template <>
struct StormReflTypeInfo<SpriteBaseDefTexture>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "SpriteBaseDefTexture"; }
  static constexpr auto GetNameHash() { return 0xEFFE2CC8; }
  static SpriteBaseDefTexture & GetDefault() { static SpriteBaseDefTexture def; return def; }
};

template <>
struct StormReflTypeInfo<SpriteBaseDefTexture>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Filename"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0xCA273D4B; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SpriteBaseDefTexture::m_Filename; }
};

template <typename Self>
struct StormReflTypeInfo<SpriteBaseDefTexture>::field_data<0, Self> : public StormReflTypeInfo<SpriteBaseDefTexture>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Filename; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Filename; }
  void SetDefault() { self.m_Filename = StormReflTypeInfo<SpriteBaseDefTexture>::GetDefault().m_Filename; }
};

template <>
struct StormReflTypeInfo<SpriteBaseDefTexture>::annotations<0>
{
  static constexpr int annotations_n = 1;
  template <int A> struct annoation { };
};

template <>
struct StormReflTypeInfo<SpriteBaseDefTexture>::annotations<0>::annoation<0>
{
  static constexpr const char * GetAnnotation() { return "file: image"; }
  static constexpr uint32_t GetAnnotationHash() { return 0xD4E8122A; }
};

template <>
struct StormReflTypeInfo<SpriteBaseDefTexture>::field_data_static<1>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_FrameWidth"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x4E7F9000; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &SpriteBaseDefTexture::m_FrameWidth; }
};

template <typename Self>
struct StormReflTypeInfo<SpriteBaseDefTexture>::field_data<1, Self> : public StormReflTypeInfo<SpriteBaseDefTexture>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_FrameWidth; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_FrameWidth; }
  void SetDefault() { self.m_FrameWidth = StormReflTypeInfo<SpriteBaseDefTexture>::GetDefault().m_FrameWidth; }
};

template <>
struct StormReflTypeInfo<SpriteBaseDefTexture>::field_data_static<2>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_FrameHeight"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5E5EBD83; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &SpriteBaseDefTexture::m_FrameHeight; }
};

template <typename Self>
struct StormReflTypeInfo<SpriteBaseDefTexture>::field_data<2, Self> : public StormReflTypeInfo<SpriteBaseDefTexture>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_FrameHeight; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_FrameHeight; }
  void SetDefault() { self.m_FrameHeight = StormReflTypeInfo<SpriteBaseDefTexture>::GetDefault().m_FrameHeight; }
};

template <>
struct StormReflTypeInfo<SpriteBaseDefAnimFrame>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "SpriteBaseDefAnimFrame"; }
  static constexpr auto GetNameHash() { return 0x226CF952; }
  static SpriteBaseDefAnimFrame & GetDefault() { static SpriteBaseDefAnimFrame def; return def; }
};

template <>
struct StormReflTypeInfo<SpriteBaseDefAnimFrame>::field_data_static<0>
{
  using member_type = RNumber<uint64_t>; // RNumber<unsigned long long>
  static constexpr auto GetName() { return "m_FrameId"; }
  static constexpr auto GetType() { return "RNumber<unsigned long long>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xEE74565B; }
  static constexpr unsigned GetTypeNameHash() { return 0x656FF0F1; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SpriteBaseDefAnimFrame::m_FrameId; }
};

template <typename Self>
struct StormReflTypeInfo<SpriteBaseDefAnimFrame>::field_data<0, Self> : public StormReflTypeInfo<SpriteBaseDefAnimFrame>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RNumber<uint64_t>> & Get() { return self.m_FrameId; }
  std::add_const_t<std::remove_reference_t<RNumber<uint64_t>>> & Get() const { return self.m_FrameId; }
  void SetDefault() { self.m_FrameId = StormReflTypeInfo<SpriteBaseDefAnimFrame>::GetDefault().m_FrameId; }
};

template <>
struct StormReflTypeInfo<SpriteBaseDefAnimFrame>::field_data_static<1>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_FrameDuration"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x74D92552; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &SpriteBaseDefAnimFrame::m_FrameDuration; }
};

template <typename Self>
struct StormReflTypeInfo<SpriteBaseDefAnimFrame>::field_data<1, Self> : public StormReflTypeInfo<SpriteBaseDefAnimFrame>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_FrameDuration; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_FrameDuration; }
  void SetDefault() { self.m_FrameDuration = StormReflTypeInfo<SpriteBaseDefAnimFrame>::GetDefault().m_FrameDuration; }
};

template <>
struct StormReflTypeInfo<SpriteBaseDefAnimation>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "SpriteBaseDefAnimation"; }
  static constexpr auto GetNameHash() { return 0xDF11BF28; }
  static SpriteBaseDefAnimation & GetDefault() { static SpriteBaseDefAnimation def; return def; }
};

template <>
struct StormReflTypeInfo<SpriteBaseDefAnimation>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SpriteBaseDefAnimation::m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<SpriteBaseDefAnimation>::field_data<0, Self> : public StormReflTypeInfo<SpriteBaseDefAnimation>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<SpriteBaseDefAnimation>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<SpriteBaseDefAnimation>::field_data_static<1>
{
  using member_type = RMergeList<SpriteBaseDefAnimFrame>; // RMergeList<SpriteBaseDefAnimFrame>
  static constexpr auto GetName() { return "m_Frames"; }
  static constexpr auto GetType() { return "RMergeList<SpriteBaseDefAnimFrame>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB351DEF2; }
  static constexpr unsigned GetTypeNameHash() { return 0xB67B45D1; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &SpriteBaseDefAnimation::m_Frames; }
};

template <typename Self>
struct StormReflTypeInfo<SpriteBaseDefAnimation>::field_data<1, Self> : public StormReflTypeInfo<SpriteBaseDefAnimation>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<SpriteBaseDefAnimFrame>> & Get() { return self.m_Frames; }
  std::add_const_t<std::remove_reference_t<RMergeList<SpriteBaseDefAnimFrame>>> & Get() const { return self.m_Frames; }
  void SetDefault() { self.m_Frames = StormReflTypeInfo<SpriteBaseDefAnimation>::GetDefault().m_Frames; }
};

template <>
struct StormReflTypeInfo<SpriteBaseDef>
{
  using MyBase = void;
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "SpriteBaseDef"; }
  static constexpr auto GetNameHash() { return 0x48F83F55; }
  static SpriteBaseDef & GetDefault() { static SpriteBaseDef def; return def; }
};

template <>
struct StormReflTypeInfo<SpriteBaseDef>::field_data_static<0>
{
  using member_type = RMergeList<SpriteBaseDefTexture>; // RMergeList<SpriteBaseDefTexture>
  static constexpr auto GetName() { return "m_Textures"; }
  static constexpr auto GetType() { return "RMergeList<SpriteBaseDefTexture>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x53AB6D38; }
  static constexpr unsigned GetTypeNameHash() { return 0x5DA9DA67; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SpriteBaseDef::m_Textures; }
};

template <typename Self>
struct StormReflTypeInfo<SpriteBaseDef>::field_data<0, Self> : public StormReflTypeInfo<SpriteBaseDef>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<SpriteBaseDefTexture>> & Get() { return self.m_Textures; }
  std::add_const_t<std::remove_reference_t<RMergeList<SpriteBaseDefTexture>>> & Get() const { return self.m_Textures; }
  void SetDefault() { self.m_Textures = StormReflTypeInfo<SpriteBaseDef>::GetDefault().m_Textures; }
};

template <>
struct StormReflTypeInfo<SpriteBaseDef>::field_data_static<1>
{
  using member_type = RMergeList<SpriteBaseDefAnimation>; // RMergeList<SpriteBaseDefAnimation>
  static constexpr auto GetName() { return "m_Animations"; }
  static constexpr auto GetType() { return "RMergeList<SpriteBaseDefAnimation>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1E5FEABD; }
  static constexpr unsigned GetTypeNameHash() { return 0x0656A0B5; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &SpriteBaseDef::m_Animations; }
};

template <typename Self>
struct StormReflTypeInfo<SpriteBaseDef>::field_data<1, Self> : public StormReflTypeInfo<SpriteBaseDef>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<SpriteBaseDefAnimation>> & Get() { return self.m_Animations; }
  std::add_const_t<std::remove_reference_t<RMergeList<SpriteBaseDefAnimation>>> & Get() const { return self.m_Animations; }
  void SetDefault() { self.m_Animations = StormReflTypeInfo<SpriteBaseDef>::GetDefault().m_Animations; }
};

template <>
struct StormReflTypeInfo<SpriteBaseDef>::field_data_static<2>
{
  using member_type = FrameData; // FrameData
  static constexpr auto GetName() { return "m_InstanceData"; }
  static constexpr auto GetType() { return "FrameData"; }
  static constexpr unsigned GetFieldNameHash() { return 0xEFC069F9; }
  static constexpr unsigned GetTypeNameHash() { return 0x4108D867; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &SpriteBaseDef::m_InstanceData; }
};

template <typename Self>
struct StormReflTypeInfo<SpriteBaseDef>::field_data<2, Self> : public StormReflTypeInfo<SpriteBaseDef>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, FrameData> & Get() { return self.m_InstanceData; }
  std::add_const_t<std::remove_reference_t<FrameData>> & Get() const { return self.m_InstanceData; }
  void SetDefault() { self.m_InstanceData = StormReflTypeInfo<SpriteBaseDef>::GetDefault().m_InstanceData; }
};

template <>
struct StormReflTypeInfo<SpriteBaseDef>::field_data_static<3>
{
  using member_type = RMap<uint64_t, FrameData>; // RMap<unsigned long long, FrameData>
  static constexpr auto GetName() { return "m_FrameData"; }
  static constexpr auto GetType() { return "RMap<unsigned long long, FrameData>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1FD97BDF; }
  static constexpr unsigned GetTypeNameHash() { return 0xDE01B17E; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &SpriteBaseDef::m_FrameData; }
};

template <typename Self>
struct StormReflTypeInfo<SpriteBaseDef>::field_data<3, Self> : public StormReflTypeInfo<SpriteBaseDef>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMap<uint64_t, FrameData>> & Get() { return self.m_FrameData; }
  std::add_const_t<std::remove_reference_t<RMap<uint64_t, FrameData>>> & Get() const { return self.m_FrameData; }
  void SetDefault() { self.m_FrameData = StormReflTypeInfo<SpriteBaseDef>::GetDefault().m_FrameData; }
};

namespace StormReflFileInfo
{
  struct SpriteBaseDef
  {
    static const int types_n = 4;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct SpriteBaseDef::type_info<0>
  {
    using type = ::SpriteBaseDefTexture;
  };

  template <>
  struct SpriteBaseDef::type_info<1>
  {
    using type = ::SpriteBaseDefAnimFrame;
  };

  template <>
  struct SpriteBaseDef::type_info<2>
  {
    using type = ::SpriteBaseDefAnimation;
  };

  template <>
  struct SpriteBaseDef::type_info<3>
  {
    using type = ::SpriteBaseDef;
  };

}

