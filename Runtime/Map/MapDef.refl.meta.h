#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "MapDef.refl.h"
#include "Foundation/BasicTypes/BasicTypes.refl.meta.h"
#include "Runtime/Entity/EntityDef.refl.meta.h"
#include "Runtime/Anchor/AnchorDef.refl.meta.h"
#include "Runtime/Path/PathDef.refl.meta.h"
#include "Runtime/Volume/VolumeDef.refl.meta.h"
#include "Runtime/Map/MapEffectLayerDef.refl.meta.h"


template <>
struct StormReflTypeInfo<MapManualTileLayer>
{
  using MyBase = void;
  static constexpr int fields_n = 6;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "MapManualTileLayer"; }
  static constexpr auto GetNameHash() { return 0x274F5F21; }
  static MapManualTileLayer & GetDefault() { static MapManualTileLayer def; return def; }
};

template <>
struct StormReflTypeInfo<MapManualTileLayer>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_TileSheet"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0xCC32ED7F; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &MapManualTileLayer::m_TileSheet; }
};

template <typename Self>
struct StormReflTypeInfo<MapManualTileLayer>::field_data<0, Self> : public StormReflTypeInfo<MapManualTileLayer>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_TileSheet; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_TileSheet; }
  void SetDefault() { self.m_TileSheet = StormReflTypeInfo<MapManualTileLayer>::GetDefault().m_TileSheet; }
};

template <>
struct StormReflTypeInfo<MapManualTileLayer>::annotations<0>
{
  static constexpr int annotations_n = 1;
  template <int A> struct annoation { };
};

template <>
struct StormReflTypeInfo<MapManualTileLayer>::annotations<0>::annoation<0>
{
  static constexpr const char * GetAnnotation() { return "file: tilesheet"; }
  static constexpr uint32_t GetAnnotationHash() { return 0x03667DA4; }
};

template <>
struct StormReflTypeInfo<MapManualTileLayer>::field_data_static<1>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &MapManualTileLayer::m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<MapManualTileLayer>::field_data<1, Self> : public StormReflTypeInfo<MapManualTileLayer>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<MapManualTileLayer>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<MapManualTileLayer>::field_data_static<2>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_LayerOrder"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3741FE10; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &MapManualTileLayer::m_LayerOrder; }
};

template <typename Self>
struct StormReflTypeInfo<MapManualTileLayer>::field_data<2, Self> : public StormReflTypeInfo<MapManualTileLayer>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_LayerOrder; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_LayerOrder; }
  void SetDefault() { self.m_LayerOrder = StormReflTypeInfo<MapManualTileLayer>::GetDefault().m_LayerOrder; }
};

template <>
struct StormReflTypeInfo<MapManualTileLayer>::field_data_static<3>
{
  using member_type = RBool; // RBool
  static constexpr auto GetName() { return "m_CollisionLayer"; }
  static constexpr auto GetType() { return "RBool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE22C9B0C; }
  static constexpr unsigned GetTypeNameHash() { return 0x50062D06; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &MapManualTileLayer::m_CollisionLayer; }
};

template <typename Self>
struct StormReflTypeInfo<MapManualTileLayer>::field_data<3, Self> : public StormReflTypeInfo<MapManualTileLayer>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RBool> & Get() { return self.m_CollisionLayer; }
  std::add_const_t<std::remove_reference_t<RBool>> & Get() const { return self.m_CollisionLayer; }
  void SetDefault() { self.m_CollisionLayer = StormReflTypeInfo<MapManualTileLayer>::GetDefault().m_CollisionLayer; }
};

template <>
struct StormReflTypeInfo<MapManualTileLayer>::field_data_static<4>
{
  using member_type = RSparseList<ROpaque<MapTile> >; // RSparseList<ROpaque<MapTile> >
  static constexpr auto GetName() { return "m_Tiles"; }
  static constexpr auto GetType() { return "RSparseList<ROpaque<MapTile> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x912314DB; }
  static constexpr unsigned GetTypeNameHash() { return 0x0B814CDB; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &MapManualTileLayer::m_Tiles; }
};

template <typename Self>
struct StormReflTypeInfo<MapManualTileLayer>::field_data<4, Self> : public StormReflTypeInfo<MapManualTileLayer>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RSparseList<ROpaque<MapTile> >> & Get() { return self.m_Tiles; }
  std::add_const_t<std::remove_reference_t<RSparseList<ROpaque<MapTile> >>> & Get() const { return self.m_Tiles; }
  void SetDefault() { self.m_Tiles = StormReflTypeInfo<MapManualTileLayer>::GetDefault().m_Tiles; }
};

template <>
struct StormReflTypeInfo<MapManualTileLayer>::annotations<4>
{
  static constexpr int annotations_n = 1;
  template <int A> struct annoation { };
};

template <>
struct StormReflTypeInfo<MapManualTileLayer>::annotations<4>::annoation<0>
{
  static constexpr const char * GetAnnotation() { return "noui"; }
  static constexpr uint32_t GetAnnotationHash() { return 0xDF10877E; }
};

template <>
struct StormReflTypeInfo<MapManualTileLayer>::field_data_static<5>
{
  using member_type = RSparseList<ROpaque<MapAnimatedTile> >; // RSparseList<ROpaque<MapAnimatedTile> >
  static constexpr auto GetName() { return "m_Animations"; }
  static constexpr auto GetType() { return "RSparseList<ROpaque<MapAnimatedTile> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1E5FEABD; }
  static constexpr unsigned GetTypeNameHash() { return 0x3B9D9349; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &MapManualTileLayer::m_Animations; }
};

template <typename Self>
struct StormReflTypeInfo<MapManualTileLayer>::field_data<5, Self> : public StormReflTypeInfo<MapManualTileLayer>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RSparseList<ROpaque<MapAnimatedTile> >> & Get() { return self.m_Animations; }
  std::add_const_t<std::remove_reference_t<RSparseList<ROpaque<MapAnimatedTile> >>> & Get() const { return self.m_Animations; }
  void SetDefault() { self.m_Animations = StormReflTypeInfo<MapManualTileLayer>::GetDefault().m_Animations; }
};

template <>
struct StormReflTypeInfo<MapManualTileLayer>::annotations<5>
{
  static constexpr int annotations_n = 1;
  template <int A> struct annoation { };
};

template <>
struct StormReflTypeInfo<MapManualTileLayer>::annotations<5>::annoation<0>
{
  static constexpr const char * GetAnnotation() { return "noui"; }
  static constexpr uint32_t GetAnnotationHash() { return 0xDF10877E; }
};

template <>
struct StormReflTypeInfo<MapEntity>
{
  using MyBase = void;
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "MapEntity"; }
  static constexpr auto GetNameHash() { return 0x81BB600D; }
  static MapEntity & GetDefault() { static MapEntity def; return def; }
};

template <>
struct StormReflTypeInfo<MapEntity>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &MapEntity::m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<MapEntity>::field_data<0, Self> : public StormReflTypeInfo<MapEntity>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<MapEntity>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<MapEntity>::field_data_static<1>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_XPosition"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAB2A0DB2; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &MapEntity::m_XPosition; }
};

template <typename Self>
struct StormReflTypeInfo<MapEntity>::field_data<1, Self> : public StormReflTypeInfo<MapEntity>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_XPosition; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_XPosition; }
  void SetDefault() { self.m_XPosition = StormReflTypeInfo<MapEntity>::GetDefault().m_XPosition; }
};

template <>
struct StormReflTypeInfo<MapEntity>::field_data_static<2>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_YPosition"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xBC5119F1; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &MapEntity::m_YPosition; }
};

template <typename Self>
struct StormReflTypeInfo<MapEntity>::field_data<2, Self> : public StormReflTypeInfo<MapEntity>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_YPosition; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_YPosition; }
  void SetDefault() { self.m_YPosition = StormReflTypeInfo<MapEntity>::GetDefault().m_YPosition; }
};

template <>
struct StormReflTypeInfo<MapEntity>::field_data_static<3>
{
  using member_type = EntityDef; // EntityDef
  static constexpr auto GetName() { return "m_EntityDef"; }
  static constexpr auto GetType() { return "EntityDef"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0FCD3EF7; }
  static constexpr unsigned GetTypeNameHash() { return 0x511C9D4F; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &MapEntity::m_EntityDef; }
};

template <typename Self>
struct StormReflTypeInfo<MapEntity>::field_data<3, Self> : public StormReflTypeInfo<MapEntity>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, EntityDef> & Get() { return self.m_EntityDef; }
  std::add_const_t<std::remove_reference_t<EntityDef>> & Get() const { return self.m_EntityDef; }
  void SetDefault() { self.m_EntityDef = StormReflTypeInfo<MapEntity>::GetDefault().m_EntityDef; }
};

template <>
struct StormReflTypeInfo<MapEntityLayer>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "MapEntityLayer"; }
  static constexpr auto GetNameHash() { return 0x0D3F8557; }
  static MapEntityLayer & GetDefault() { static MapEntityLayer def; return def; }
};

template <>
struct StormReflTypeInfo<MapEntityLayer>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &MapEntityLayer::m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<MapEntityLayer>::field_data<0, Self> : public StormReflTypeInfo<MapEntityLayer>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<MapEntityLayer>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<MapEntityLayer>::field_data_static<1>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_LayerOrder"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3741FE10; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &MapEntityLayer::m_LayerOrder; }
};

template <typename Self>
struct StormReflTypeInfo<MapEntityLayer>::field_data<1, Self> : public StormReflTypeInfo<MapEntityLayer>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_LayerOrder; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_LayerOrder; }
  void SetDefault() { self.m_LayerOrder = StormReflTypeInfo<MapEntityLayer>::GetDefault().m_LayerOrder; }
};

template <>
struct StormReflTypeInfo<MapEntityLayer>::field_data_static<2>
{
  using member_type = RMergeList<MapEntity>; // RMergeList<MapEntity>
  static constexpr auto GetName() { return "m_Entities"; }
  static constexpr auto GetType() { return "RMergeList<MapEntity>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA6C0B0CB; }
  static constexpr unsigned GetTypeNameHash() { return 0x31E722AE; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &MapEntityLayer::m_Entities; }
};

template <typename Self>
struct StormReflTypeInfo<MapEntityLayer>::field_data<2, Self> : public StormReflTypeInfo<MapEntityLayer>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<MapEntity>> & Get() { return self.m_Entities; }
  std::add_const_t<std::remove_reference_t<RMergeList<MapEntity>>> & Get() const { return self.m_Entities; }
  void SetDefault() { self.m_Entities = StormReflTypeInfo<MapEntityLayer>::GetDefault().m_Entities; }
};

template <>
struct StormReflTypeInfo<MapEntityLayer>::annotations<2>
{
  static constexpr int annotations_n = 1;
  template <int A> struct annoation { };
};

template <>
struct StormReflTypeInfo<MapEntityLayer>::annotations<2>::annoation<0>
{
  static constexpr const char * GetAnnotation() { return "noui"; }
  static constexpr uint32_t GetAnnotationHash() { return 0xDF10877E; }
};

template <>
struct StormReflTypeInfo<MapParalaxLayer>
{
  using MyBase = void;
  static constexpr int fields_n = 11;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "MapParalaxLayer"; }
  static constexpr auto GetNameHash() { return 0xF0494FF1; }
  static MapParalaxLayer & GetDefault() { static MapParalaxLayer def; return def; }
};

template <>
struct StormReflTypeInfo<MapParalaxLayer>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &MapParalaxLayer::m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<MapParalaxLayer>::field_data<0, Self> : public StormReflTypeInfo<MapParalaxLayer>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<MapParalaxLayer>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<MapParalaxLayer>::field_data_static<1>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_LayerOrder"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3741FE10; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &MapParalaxLayer::m_LayerOrder; }
};

template <typename Self>
struct StormReflTypeInfo<MapParalaxLayer>::field_data<1, Self> : public StormReflTypeInfo<MapParalaxLayer>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_LayerOrder; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_LayerOrder; }
  void SetDefault() { self.m_LayerOrder = StormReflTypeInfo<MapParalaxLayer>::GetDefault().m_LayerOrder; }
};

template <>
struct StormReflTypeInfo<MapParalaxLayer>::field_data_static<2>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Image"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x480B943F; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &MapParalaxLayer::m_Image; }
};

template <typename Self>
struct StormReflTypeInfo<MapParalaxLayer>::field_data<2, Self> : public StormReflTypeInfo<MapParalaxLayer>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Image; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Image; }
  void SetDefault() { self.m_Image = StormReflTypeInfo<MapParalaxLayer>::GetDefault().m_Image; }
};

template <>
struct StormReflTypeInfo<MapParalaxLayer>::annotations<2>
{
  static constexpr int annotations_n = 1;
  template <int A> struct annoation { };
};

template <>
struct StormReflTypeInfo<MapParalaxLayer>::annotations<2>::annoation<0>
{
  static constexpr const char * GetAnnotation() { return "file: image"; }
  static constexpr uint32_t GetAnnotationHash() { return 0xD4E8122A; }
};

template <>
struct StormReflTypeInfo<MapParalaxLayer>::field_data_static<3>
{
  using member_type = RBool; // RBool
  static constexpr auto GetName() { return "m_RepeatX"; }
  static constexpr auto GetType() { return "RBool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB98CD69D; }
  static constexpr unsigned GetTypeNameHash() { return 0x50062D06; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &MapParalaxLayer::m_RepeatX; }
};

template <typename Self>
struct StormReflTypeInfo<MapParalaxLayer>::field_data<3, Self> : public StormReflTypeInfo<MapParalaxLayer>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RBool> & Get() { return self.m_RepeatX; }
  std::add_const_t<std::remove_reference_t<RBool>> & Get() const { return self.m_RepeatX; }
  void SetDefault() { self.m_RepeatX = StormReflTypeInfo<MapParalaxLayer>::GetDefault().m_RepeatX; }
};

template <>
struct StormReflTypeInfo<MapParalaxLayer>::field_data_static<4>
{
  using member_type = RBool; // RBool
  static constexpr auto GetName() { return "m_RepeatY"; }
  static constexpr auto GetType() { return "RBool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xCE8BE60B; }
  static constexpr unsigned GetTypeNameHash() { return 0x50062D06; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &MapParalaxLayer::m_RepeatY; }
};

template <typename Self>
struct StormReflTypeInfo<MapParalaxLayer>::field_data<4, Self> : public StormReflTypeInfo<MapParalaxLayer>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RBool> & Get() { return self.m_RepeatY; }
  std::add_const_t<std::remove_reference_t<RBool>> & Get() const { return self.m_RepeatY; }
  void SetDefault() { self.m_RepeatY = StormReflTypeInfo<MapParalaxLayer>::GetDefault().m_RepeatY; }
};

template <>
struct StormReflTypeInfo<MapParalaxLayer>::field_data_static<5>
{
  using member_type = RFloat; // RNumber<float>
  static constexpr auto GetName() { return "m_OffsetX"; }
  static constexpr auto GetType() { return "RNumber<float>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA4CA9B80; }
  static constexpr unsigned GetTypeNameHash() { return 0x17411E4A; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &MapParalaxLayer::m_OffsetX; }
};

template <typename Self>
struct StormReflTypeInfo<MapParalaxLayer>::field_data<5, Self> : public StormReflTypeInfo<MapParalaxLayer>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RFloat> & Get() { return self.m_OffsetX; }
  std::add_const_t<std::remove_reference_t<RFloat>> & Get() const { return self.m_OffsetX; }
  void SetDefault() { self.m_OffsetX = StormReflTypeInfo<MapParalaxLayer>::GetDefault().m_OffsetX; }
};

template <>
struct StormReflTypeInfo<MapParalaxLayer>::field_data_static<6>
{
  using member_type = RFloat; // RNumber<float>
  static constexpr auto GetName() { return "m_OffsetY"; }
  static constexpr auto GetType() { return "RNumber<float>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD3CDAB16; }
  static constexpr unsigned GetTypeNameHash() { return 0x17411E4A; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &MapParalaxLayer::m_OffsetY; }
};

template <typename Self>
struct StormReflTypeInfo<MapParalaxLayer>::field_data<6, Self> : public StormReflTypeInfo<MapParalaxLayer>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RFloat> & Get() { return self.m_OffsetY; }
  std::add_const_t<std::remove_reference_t<RFloat>> & Get() const { return self.m_OffsetY; }
  void SetDefault() { self.m_OffsetY = StormReflTypeInfo<MapParalaxLayer>::GetDefault().m_OffsetY; }
};

template <>
struct StormReflTypeInfo<MapParalaxLayer>::field_data_static<7>
{
  using member_type = RFloat; // RNumber<float>
  static constexpr auto GetName() { return "m_ParalaxX"; }
  static constexpr auto GetType() { return "RNumber<float>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x4A94EC25; }
  static constexpr unsigned GetTypeNameHash() { return 0x17411E4A; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &MapParalaxLayer::m_ParalaxX; }
};

template <typename Self>
struct StormReflTypeInfo<MapParalaxLayer>::field_data<7, Self> : public StormReflTypeInfo<MapParalaxLayer>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RFloat> & Get() { return self.m_ParalaxX; }
  std::add_const_t<std::remove_reference_t<RFloat>> & Get() const { return self.m_ParalaxX; }
  void SetDefault() { self.m_ParalaxX = StormReflTypeInfo<MapParalaxLayer>::GetDefault().m_ParalaxX; }
};

template <>
struct StormReflTypeInfo<MapParalaxLayer>::field_data_static<8>
{
  using member_type = RFloat; // RNumber<float>
  static constexpr auto GetName() { return "m_ParalaxY"; }
  static constexpr auto GetType() { return "RNumber<float>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3D93DCB3; }
  static constexpr unsigned GetTypeNameHash() { return 0x17411E4A; }
  static constexpr auto GetFieldIndex() { return 8; }
  static constexpr auto GetMemberPtr() { return &MapParalaxLayer::m_ParalaxY; }
};

template <typename Self>
struct StormReflTypeInfo<MapParalaxLayer>::field_data<8, Self> : public StormReflTypeInfo<MapParalaxLayer>::field_data_static<8>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RFloat> & Get() { return self.m_ParalaxY; }
  std::add_const_t<std::remove_reference_t<RFloat>> & Get() const { return self.m_ParalaxY; }
  void SetDefault() { self.m_ParalaxY = StormReflTypeInfo<MapParalaxLayer>::GetDefault().m_ParalaxY; }
};

template <>
struct StormReflTypeInfo<MapParalaxLayer>::field_data_static<9>
{
  using member_type = RFloat; // RNumber<float>
  static constexpr auto GetName() { return "m_VelocityX"; }
  static constexpr auto GetType() { return "RNumber<float>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC426D4CA; }
  static constexpr unsigned GetTypeNameHash() { return 0x17411E4A; }
  static constexpr auto GetFieldIndex() { return 9; }
  static constexpr auto GetMemberPtr() { return &MapParalaxLayer::m_VelocityX; }
};

template <typename Self>
struct StormReflTypeInfo<MapParalaxLayer>::field_data<9, Self> : public StormReflTypeInfo<MapParalaxLayer>::field_data_static<9>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RFloat> & Get() { return self.m_VelocityX; }
  std::add_const_t<std::remove_reference_t<RFloat>> & Get() const { return self.m_VelocityX; }
  void SetDefault() { self.m_VelocityX = StormReflTypeInfo<MapParalaxLayer>::GetDefault().m_VelocityX; }
};

template <>
struct StormReflTypeInfo<MapParalaxLayer>::field_data_static<10>
{
  using member_type = RFloat; // RNumber<float>
  static constexpr auto GetName() { return "m_VelocityY"; }
  static constexpr auto GetType() { return "RNumber<float>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB321E45C; }
  static constexpr unsigned GetTypeNameHash() { return 0x17411E4A; }
  static constexpr auto GetFieldIndex() { return 10; }
  static constexpr auto GetMemberPtr() { return &MapParalaxLayer::m_VelocityY; }
};

template <typename Self>
struct StormReflTypeInfo<MapParalaxLayer>::field_data<10, Self> : public StormReflTypeInfo<MapParalaxLayer>::field_data_static<10>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RFloat> & Get() { return self.m_VelocityY; }
  std::add_const_t<std::remove_reference_t<RFloat>> & Get() const { return self.m_VelocityY; }
  void SetDefault() { self.m_VelocityY = StormReflTypeInfo<MapParalaxLayer>::GetDefault().m_VelocityY; }
};

template <>
struct StormReflTypeInfo<MapEffectLayer>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "MapEffectLayer"; }
  static constexpr auto GetNameHash() { return 0xD5960B85; }
  static MapEffectLayer & GetDefault() { static MapEffectLayer def; return def; }
};

template <>
struct StormReflTypeInfo<MapEffectLayer>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &MapEffectLayer::m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<MapEffectLayer>::field_data<0, Self> : public StormReflTypeInfo<MapEffectLayer>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<MapEffectLayer>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<MapEffectLayer>::field_data_static<1>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_LayerOrder"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3741FE10; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &MapEffectLayer::m_LayerOrder; }
};

template <typename Self>
struct StormReflTypeInfo<MapEffectLayer>::field_data<1, Self> : public StormReflTypeInfo<MapEffectLayer>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_LayerOrder; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_LayerOrder; }
  void SetDefault() { self.m_LayerOrder = StormReflTypeInfo<MapEffectLayer>::GetDefault().m_LayerOrder; }
};

template <>
struct StormReflTypeInfo<MapEffectLayer>::field_data_static<2>
{
  using member_type = RPolymorphic<MapEffectLayerInitData, MapEffectLayerTypeDatabase, MapEffectLayerDataTypeInfo>; // RPolymorphic<MapEffectLayerInitData, MapEffectLayerTypeDatabase, MapEffectLayerDataTypeInfo>
  static constexpr auto GetName() { return "m_EffectLayerData"; }
  static constexpr auto GetType() { return "RPolymorphic<MapEffectLayerInitData, MapEffectLayerTypeDatabase, MapEffectLayerDataTypeInfo>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE1AE0B1F; }
  static constexpr unsigned GetTypeNameHash() { return 0xAA22286A; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &MapEffectLayer::m_EffectLayerData; }
};

template <typename Self>
struct StormReflTypeInfo<MapEffectLayer>::field_data<2, Self> : public StormReflTypeInfo<MapEffectLayer>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RPolymorphic<MapEffectLayerInitData, MapEffectLayerTypeDatabase, MapEffectLayerDataTypeInfo>> & Get() { return self.m_EffectLayerData; }
  std::add_const_t<std::remove_reference_t<RPolymorphic<MapEffectLayerInitData, MapEffectLayerTypeDatabase, MapEffectLayerDataTypeInfo>>> & Get() const { return self.m_EffectLayerData; }
  void SetDefault() { self.m_EffectLayerData = StormReflTypeInfo<MapEffectLayer>::GetDefault().m_EffectLayerData; }
};

template <>
struct StormReflTypeInfo<MapAnchor>
{
  using MyBase = void;
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "MapAnchor"; }
  static constexpr auto GetNameHash() { return 0xE8C23518; }
  static MapAnchor & GetDefault() { static MapAnchor def; return def; }
};

template <>
struct StormReflTypeInfo<MapAnchor>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &MapAnchor::m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<MapAnchor>::field_data<0, Self> : public StormReflTypeInfo<MapAnchor>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<MapAnchor>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<MapAnchor>::field_data_static<1>
{
  using member_type = RPolymorphic<AnchorDataBase, AnchorTypeDatabase, AnchorDataTypeInfo>; // RPolymorphic<AnchorDataBase, AnchorTypeDatabase, AnchorDataTypeInfo>
  static constexpr auto GetName() { return "m_AnchorData"; }
  static constexpr auto GetType() { return "RPolymorphic<AnchorDataBase, AnchorTypeDatabase, AnchorDataTypeInfo>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x73BF9C78; }
  static constexpr unsigned GetTypeNameHash() { return 0x1AB33B8D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &MapAnchor::m_AnchorData; }
};

template <typename Self>
struct StormReflTypeInfo<MapAnchor>::field_data<1, Self> : public StormReflTypeInfo<MapAnchor>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RPolymorphic<AnchorDataBase, AnchorTypeDatabase, AnchorDataTypeInfo>> & Get() { return self.m_AnchorData; }
  std::add_const_t<std::remove_reference_t<RPolymorphic<AnchorDataBase, AnchorTypeDatabase, AnchorDataTypeInfo>>> & Get() const { return self.m_AnchorData; }
  void SetDefault() { self.m_AnchorData = StormReflTypeInfo<MapAnchor>::GetDefault().m_AnchorData; }
};

template <>
struct StormReflTypeInfo<MapAnchor>::field_data_static<2>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_X"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE7DD193C; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &MapAnchor::m_X; }
};

template <typename Self>
struct StormReflTypeInfo<MapAnchor>::field_data<2, Self> : public StormReflTypeInfo<MapAnchor>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_X; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_X; }
  void SetDefault() { self.m_X = StormReflTypeInfo<MapAnchor>::GetDefault().m_X; }
};

template <>
struct StormReflTypeInfo<MapAnchor>::field_data_static<3>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_Y"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x90DA29AA; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &MapAnchor::m_Y; }
};

template <typename Self>
struct StormReflTypeInfo<MapAnchor>::field_data<3, Self> : public StormReflTypeInfo<MapAnchor>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_Y; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_Y; }
  void SetDefault() { self.m_Y = StormReflTypeInfo<MapAnchor>::GetDefault().m_Y; }
};

template <>
struct StormReflTypeInfo<MapPathPoint>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "MapPathPoint"; }
  static constexpr auto GetNameHash() { return 0x90DF0F70; }
  static MapPathPoint & GetDefault() { static MapPathPoint def; return def; }
};

template <>
struct StormReflTypeInfo<MapPathPoint>::field_data_static<0>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_X"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE7DD193C; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &MapPathPoint::m_X; }
};

template <typename Self>
struct StormReflTypeInfo<MapPathPoint>::field_data<0, Self> : public StormReflTypeInfo<MapPathPoint>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_X; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_X; }
  void SetDefault() { self.m_X = StormReflTypeInfo<MapPathPoint>::GetDefault().m_X; }
};

template <>
struct StormReflTypeInfo<MapPathPoint>::field_data_static<1>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_Y"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x90DA29AA; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &MapPathPoint::m_Y; }
};

template <typename Self>
struct StormReflTypeInfo<MapPathPoint>::field_data<1, Self> : public StormReflTypeInfo<MapPathPoint>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_Y; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_Y; }
  void SetDefault() { self.m_Y = StormReflTypeInfo<MapPathPoint>::GetDefault().m_Y; }
};

template <>
struct StormReflTypeInfo<MapPath>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "MapPath"; }
  static constexpr auto GetNameHash() { return 0x08E80CDA; }
  static MapPath & GetDefault() { static MapPath def; return def; }
};

template <>
struct StormReflTypeInfo<MapPath>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &MapPath::m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<MapPath>::field_data<0, Self> : public StormReflTypeInfo<MapPath>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<MapPath>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<MapPath>::field_data_static<1>
{
  using member_type = RPolymorphic<PathDataBase, PathTypeDatabase, PathDataTypeInfo>; // RPolymorphic<PathDataBase, PathTypeDatabase, PathDataTypeInfo>
  static constexpr auto GetName() { return "m_PathData"; }
  static constexpr auto GetType() { return "RPolymorphic<PathDataBase, PathTypeDatabase, PathDataTypeInfo>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x07EB2D9C; }
  static constexpr unsigned GetTypeNameHash() { return 0xA5143125; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &MapPath::m_PathData; }
};

template <typename Self>
struct StormReflTypeInfo<MapPath>::field_data<1, Self> : public StormReflTypeInfo<MapPath>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RPolymorphic<PathDataBase, PathTypeDatabase, PathDataTypeInfo>> & Get() { return self.m_PathData; }
  std::add_const_t<std::remove_reference_t<RPolymorphic<PathDataBase, PathTypeDatabase, PathDataTypeInfo>>> & Get() const { return self.m_PathData; }
  void SetDefault() { self.m_PathData = StormReflTypeInfo<MapPath>::GetDefault().m_PathData; }
};

template <>
struct StormReflTypeInfo<MapPath>::field_data_static<2>
{
  using member_type = RMergeList<MapPathPoint>; // RMergeList<MapPathPoint>
  static constexpr auto GetName() { return "m_Points"; }
  static constexpr auto GetType() { return "RMergeList<MapPathPoint>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6A85D9E1; }
  static constexpr unsigned GetTypeNameHash() { return 0xE00E4311; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &MapPath::m_Points; }
};

template <typename Self>
struct StormReflTypeInfo<MapPath>::field_data<2, Self> : public StormReflTypeInfo<MapPath>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<MapPathPoint>> & Get() { return self.m_Points; }
  std::add_const_t<std::remove_reference_t<RMergeList<MapPathPoint>>> & Get() const { return self.m_Points; }
  void SetDefault() { self.m_Points = StormReflTypeInfo<MapPath>::GetDefault().m_Points; }
};

template <>
struct StormReflTypeInfo<MapVolume>
{
  using MyBase = void;
  static constexpr int fields_n = 6;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "MapVolume"; }
  static constexpr auto GetNameHash() { return 0x3609E9BB; }
  static MapVolume & GetDefault() { static MapVolume def; return def; }
};

template <>
struct StormReflTypeInfo<MapVolume>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &MapVolume::m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<MapVolume>::field_data<0, Self> : public StormReflTypeInfo<MapVolume>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<MapVolume>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<MapVolume>::field_data_static<1>
{
  using member_type = RPolymorphic<VolumeDataBase, VolumeTypeDatabase, VolumeDataTypeInfo>; // RPolymorphic<VolumeDataBase, VolumeTypeDatabase, VolumeDataTypeInfo>
  static constexpr auto GetName() { return "m_VolumeData"; }
  static constexpr auto GetType() { return "RPolymorphic<VolumeDataBase, VolumeTypeDatabase, VolumeDataTypeInfo>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE1971791; }
  static constexpr unsigned GetTypeNameHash() { return 0x252416A8; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &MapVolume::m_VolumeData; }
};

template <typename Self>
struct StormReflTypeInfo<MapVolume>::field_data<1, Self> : public StormReflTypeInfo<MapVolume>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RPolymorphic<VolumeDataBase, VolumeTypeDatabase, VolumeDataTypeInfo>> & Get() { return self.m_VolumeData; }
  std::add_const_t<std::remove_reference_t<RPolymorphic<VolumeDataBase, VolumeTypeDatabase, VolumeDataTypeInfo>>> & Get() const { return self.m_VolumeData; }
  void SetDefault() { self.m_VolumeData = StormReflTypeInfo<MapVolume>::GetDefault().m_VolumeData; }
};

template <>
struct StormReflTypeInfo<MapVolume>::field_data_static<2>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_XStart"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8316F451; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &MapVolume::m_XStart; }
};

template <typename Self>
struct StormReflTypeInfo<MapVolume>::field_data<2, Self> : public StormReflTypeInfo<MapVolume>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_XStart; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_XStart; }
  void SetDefault() { self.m_XStart = StormReflTypeInfo<MapVolume>::GetDefault().m_XStart; }
};

template <>
struct StormReflTypeInfo<MapVolume>::field_data_static<3>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_YStart"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x484A27F4; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &MapVolume::m_YStart; }
};

template <typename Self>
struct StormReflTypeInfo<MapVolume>::field_data<3, Self> : public StormReflTypeInfo<MapVolume>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_YStart; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_YStart; }
  void SetDefault() { self.m_YStart = StormReflTypeInfo<MapVolume>::GetDefault().m_YStart; }
};

template <>
struct StormReflTypeInfo<MapVolume>::field_data_static<4>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_XEnd"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x76A26E33; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &MapVolume::m_XEnd; }
};

template <typename Self>
struct StormReflTypeInfo<MapVolume>::field_data<4, Self> : public StormReflTypeInfo<MapVolume>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_XEnd; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_XEnd; }
  void SetDefault() { self.m_XEnd = StormReflTypeInfo<MapVolume>::GetDefault().m_XEnd; }
};

template <>
struct StormReflTypeInfo<MapVolume>::field_data_static<5>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_YEnd"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xCE1E0956; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &MapVolume::m_YEnd; }
};

template <typename Self>
struct StormReflTypeInfo<MapVolume>::field_data<5, Self> : public StormReflTypeInfo<MapVolume>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_YEnd; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_YEnd; }
  void SetDefault() { self.m_YEnd = StormReflTypeInfo<MapVolume>::GetDefault().m_YEnd; }
};

template <>
struct StormReflTypeInfo<MapDef>
{
  using MyBase = void;
  static constexpr int fields_n = 7;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "MapDef"; }
  static constexpr auto GetNameHash() { return 0x06A138E3; }
  static MapDef & GetDefault() { static MapDef def; return def; }
};

template <>
struct StormReflTypeInfo<MapDef>::field_data_static<0>
{
  using member_type = RMergeList<MapManualTileLayer>; // RMergeList<MapManualTileLayer>
  static constexpr auto GetName() { return "m_ManualTileLayers"; }
  static constexpr auto GetType() { return "RMergeList<MapManualTileLayer>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x64A8921A; }
  static constexpr unsigned GetTypeNameHash() { return 0xBEE03213; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &MapDef::m_ManualTileLayers; }
};

template <typename Self>
struct StormReflTypeInfo<MapDef>::field_data<0, Self> : public StormReflTypeInfo<MapDef>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<MapManualTileLayer>> & Get() { return self.m_ManualTileLayers; }
  std::add_const_t<std::remove_reference_t<RMergeList<MapManualTileLayer>>> & Get() const { return self.m_ManualTileLayers; }
  void SetDefault() { self.m_ManualTileLayers = StormReflTypeInfo<MapDef>::GetDefault().m_ManualTileLayers; }
};

template <>
struct StormReflTypeInfo<MapDef>::field_data_static<1>
{
  using member_type = RMergeList<MapEntityLayer>; // RMergeList<MapEntityLayer>
  static constexpr auto GetName() { return "m_EntityLayers"; }
  static constexpr auto GetType() { return "RMergeList<MapEntityLayer>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x606A4865; }
  static constexpr unsigned GetTypeNameHash() { return 0x0F0562FD; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &MapDef::m_EntityLayers; }
};

template <typename Self>
struct StormReflTypeInfo<MapDef>::field_data<1, Self> : public StormReflTypeInfo<MapDef>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<MapEntityLayer>> & Get() { return self.m_EntityLayers; }
  std::add_const_t<std::remove_reference_t<RMergeList<MapEntityLayer>>> & Get() const { return self.m_EntityLayers; }
  void SetDefault() { self.m_EntityLayers = StormReflTypeInfo<MapDef>::GetDefault().m_EntityLayers; }
};

template <>
struct StormReflTypeInfo<MapDef>::field_data_static<2>
{
  using member_type = RMergeList<MapParalaxLayer>; // RMergeList<MapParalaxLayer>
  static constexpr auto GetName() { return "m_ParalaxLayers"; }
  static constexpr auto GetType() { return "RMergeList<MapParalaxLayer>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x131DDD15; }
  static constexpr unsigned GetTypeNameHash() { return 0xA01CA52C; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &MapDef::m_ParalaxLayers; }
};

template <typename Self>
struct StormReflTypeInfo<MapDef>::field_data<2, Self> : public StormReflTypeInfo<MapDef>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<MapParalaxLayer>> & Get() { return self.m_ParalaxLayers; }
  std::add_const_t<std::remove_reference_t<RMergeList<MapParalaxLayer>>> & Get() const { return self.m_ParalaxLayers; }
  void SetDefault() { self.m_ParalaxLayers = StormReflTypeInfo<MapDef>::GetDefault().m_ParalaxLayers; }
};

template <>
struct StormReflTypeInfo<MapDef>::field_data_static<3>
{
  using member_type = RMergeList<MapEffectLayer>; // RMergeList<MapEffectLayer>
  static constexpr auto GetName() { return "m_EffectLayers"; }
  static constexpr auto GetType() { return "RMergeList<MapEffectLayer>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x086F5213; }
  static constexpr unsigned GetTypeNameHash() { return 0x6700788B; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &MapDef::m_EffectLayers; }
};

template <typename Self>
struct StormReflTypeInfo<MapDef>::field_data<3, Self> : public StormReflTypeInfo<MapDef>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<MapEffectLayer>> & Get() { return self.m_EffectLayers; }
  std::add_const_t<std::remove_reference_t<RMergeList<MapEffectLayer>>> & Get() const { return self.m_EffectLayers; }
  void SetDefault() { self.m_EffectLayers = StormReflTypeInfo<MapDef>::GetDefault().m_EffectLayers; }
};

template <>
struct StormReflTypeInfo<MapDef>::field_data_static<4>
{
  using member_type = RMergeList<MapAnchor>; // RMergeList<MapAnchor>
  static constexpr auto GetName() { return "m_Anchors"; }
  static constexpr auto GetType() { return "RMergeList<MapAnchor>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA02FE64E; }
  static constexpr unsigned GetTypeNameHash() { return 0x5C53BF10; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &MapDef::m_Anchors; }
};

template <typename Self>
struct StormReflTypeInfo<MapDef>::field_data<4, Self> : public StormReflTypeInfo<MapDef>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<MapAnchor>> & Get() { return self.m_Anchors; }
  std::add_const_t<std::remove_reference_t<RMergeList<MapAnchor>>> & Get() const { return self.m_Anchors; }
  void SetDefault() { self.m_Anchors = StormReflTypeInfo<MapDef>::GetDefault().m_Anchors; }
};

template <>
struct StormReflTypeInfo<MapDef>::field_data_static<5>
{
  using member_type = RMergeList<MapPath>; // RMergeList<MapPath>
  static constexpr auto GetName() { return "m_Paths"; }
  static constexpr auto GetType() { return "RMergeList<MapPath>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x068C1671; }
  static constexpr unsigned GetTypeNameHash() { return 0x65F883E4; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &MapDef::m_Paths; }
};

template <typename Self>
struct StormReflTypeInfo<MapDef>::field_data<5, Self> : public StormReflTypeInfo<MapDef>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<MapPath>> & Get() { return self.m_Paths; }
  std::add_const_t<std::remove_reference_t<RMergeList<MapPath>>> & Get() const { return self.m_Paths; }
  void SetDefault() { self.m_Paths = StormReflTypeInfo<MapDef>::GetDefault().m_Paths; }
};

template <>
struct StormReflTypeInfo<MapDef>::field_data_static<6>
{
  using member_type = RMergeList<MapVolume>; // RMergeList<MapVolume>
  static constexpr auto GetName() { return "m_Volumes"; }
  static constexpr auto GetType() { return "RMergeList<MapVolume>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xEF2EDFC0; }
  static constexpr unsigned GetTypeNameHash() { return 0x1352869E; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &MapDef::m_Volumes; }
};

template <typename Self>
struct StormReflTypeInfo<MapDef>::field_data<6, Self> : public StormReflTypeInfo<MapDef>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<MapVolume>> & Get() { return self.m_Volumes; }
  std::add_const_t<std::remove_reference_t<RMergeList<MapVolume>>> & Get() const { return self.m_Volumes; }
  void SetDefault() { self.m_Volumes = StormReflTypeInfo<MapDef>::GetDefault().m_Volumes; }
};

namespace StormReflFileInfo
{
  struct MapDef
  {
    static const int types_n = 10;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct MapDef::type_info<0>
  {
    using type = ::MapManualTileLayer;
  };

  template <>
  struct MapDef::type_info<1>
  {
    using type = ::MapEntity;
  };

  template <>
  struct MapDef::type_info<2>
  {
    using type = ::MapEntityLayer;
  };

  template <>
  struct MapDef::type_info<3>
  {
    using type = ::MapParalaxLayer;
  };

  template <>
  struct MapDef::type_info<4>
  {
    using type = ::MapEffectLayer;
  };

  template <>
  struct MapDef::type_info<5>
  {
    using type = ::MapAnchor;
  };

  template <>
  struct MapDef::type_info<6>
  {
    using type = ::MapPathPoint;
  };

  template <>
  struct MapDef::type_info<7>
  {
    using type = ::MapPath;
  };

  template <>
  struct MapDef::type_info<8>
  {
    using type = ::MapVolume;
  };

  template <>
  struct MapDef::type_info<9>
  {
    using type = ::MapDef;
  };

}

