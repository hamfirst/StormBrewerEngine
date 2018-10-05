#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "MapDef.refl.h"
#include "Foundation/BasicTypes/BasicTypes.refl.meta.h"
#include "Runtime/Entity/EntityDef.refl.meta.h"
#include "Runtime/ServerObject/ServerObjectDef.refl.meta.h"
#include "Runtime/Anchor/AnchorDef.refl.meta.h"
#include "Runtime/Path/PathDef.refl.meta.h"
#include "Runtime/Volume/VolumeDef.refl.meta.h"
#include "Runtime/Map/MapEffectLayerDef.refl.meta.h"
#include "Runtime/Map/MapPropertiesDef.refl.meta.h"


template <>
struct StormReflEnumInfo<MapParalaxLayerObjectType>
{
  static constexpr int elems_n = 3;
  static constexpr auto GetName() { return "MapParalaxLayerObjectType"; }
  static constexpr auto GetNameHash() { return 0x459896D6; }
  template <int N> struct elems { };
};

template <>
struct StormReflEnumInfo<MapParalaxLayerObjectType>::elems<0>
{
  static constexpr auto GetName() { return "kTexture"; }
  static constexpr auto GetNameHash() { return 0x38148814; }
  static constexpr auto GetValue() { return MapParalaxLayerObjectType::kTexture; }
};

template <>
struct StormReflEnumInfo<MapParalaxLayerObjectType>::elems<1>
{
  static constexpr auto GetName() { return "kSprite"; }
  static constexpr auto GetNameHash() { return 0x97AEEC6A; }
  static constexpr auto GetValue() { return MapParalaxLayerObjectType::kSprite; }
};

template <>
struct StormReflEnumInfo<MapParalaxLayerObjectType>::elems<2>
{
  static constexpr auto GetName() { return "kVfx"; }
  static constexpr auto GetNameHash() { return 0xC82BC833; }
  static constexpr auto GetValue() { return MapParalaxLayerObjectType::kVfx; }
};

template <>
struct StormReflTypeInfo<MapPropertiesInfo>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "MapPropertiesInfo"; }
  static constexpr auto GetNameHash() { return 0x3D3EA581; }
  static MapPropertiesInfo & GetDefault() { static MapPropertiesInfo def; return def; }
};

template <>
struct StormReflTypeInfo<MapPropertiesInfo>::field_data_static<0>
{
  using member_type = RPolymorphic<MapPropertiesDef, void, true>; // RPolymorphicBase<MapPropertiesDef, TypeDatabase<MapPropertiesDef, void>, TypeDatabaseTypeInfo<MapPropertiesDef, void>, true>
  static constexpr auto GetName() { return "m_MapProperties"; }
  static constexpr auto GetType() { return "RPolymorphicBase<MapPropertiesDef, TypeDatabase<MapPropertiesDef, void>, TypeDatabaseTypeInfo<MapPropertiesDef, void>, true>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x841C9243; }
  static constexpr unsigned GetTypeNameHash() { return 0x6DB54CE0; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &MapPropertiesInfo::m_MapProperties; }
};

template <typename Self>
struct StormReflTypeInfo<MapPropertiesInfo>::field_data<0, Self> : public StormReflTypeInfo<MapPropertiesInfo>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RPolymorphic<MapPropertiesDef, void, true>> & Get() { return self.m_MapProperties; }
  std::add_const_t<std::remove_reference_t<RPolymorphic<MapPropertiesDef, void, true>>> & Get() const { return self.m_MapProperties; }
  void SetDefault() { self.m_MapProperties = StormReflTypeInfo<MapPropertiesInfo>::GetDefault().m_MapProperties; }
};

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
  static constexpr int fields_n = 5;
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
  using member_type = RUInt; // RNumber<unsigned int>
  static constexpr auto GetName() { return "m_GUID"; }
  static constexpr auto GetType() { return "RNumber<unsigned int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x83551827; }
  static constexpr unsigned GetTypeNameHash() { return 0x7B4FB98C; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &MapEntity::m_GUID; }
};

template <typename Self>
struct StormReflTypeInfo<MapEntity>::field_data<1, Self> : public StormReflTypeInfo<MapEntity>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RUInt> & Get() { return self.m_GUID; }
  std::add_const_t<std::remove_reference_t<RUInt>> & Get() const { return self.m_GUID; }
  void SetDefault() { self.m_GUID = StormReflTypeInfo<MapEntity>::GetDefault().m_GUID; }
};

template <>
struct StormReflTypeInfo<MapEntity>::annotations<1>
{
  static constexpr int annotations_n = 1;
  template <int A> struct annoation { };
};

template <>
struct StormReflTypeInfo<MapEntity>::annotations<1>::annoation<0>
{
  static constexpr const char * GetAnnotation() { return "noui"; }
  static constexpr uint32_t GetAnnotationHash() { return 0xDF10877E; }
};

template <>
struct StormReflTypeInfo<MapEntity>::field_data_static<2>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_XPosition"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAB2A0DB2; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &MapEntity::m_XPosition; }
};

template <typename Self>
struct StormReflTypeInfo<MapEntity>::field_data<2, Self> : public StormReflTypeInfo<MapEntity>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_XPosition; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_XPosition; }
  void SetDefault() { self.m_XPosition = StormReflTypeInfo<MapEntity>::GetDefault().m_XPosition; }
};

template <>
struct StormReflTypeInfo<MapEntity>::field_data_static<3>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_YPosition"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xBC5119F1; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &MapEntity::m_YPosition; }
};

template <typename Self>
struct StormReflTypeInfo<MapEntity>::field_data<3, Self> : public StormReflTypeInfo<MapEntity>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_YPosition; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_YPosition; }
  void SetDefault() { self.m_YPosition = StormReflTypeInfo<MapEntity>::GetDefault().m_YPosition; }
};

template <>
struct StormReflTypeInfo<MapEntity>::field_data_static<4>
{
  using member_type = EntityDef; // EntityDef
  static constexpr auto GetName() { return "m_EntityDef"; }
  static constexpr auto GetType() { return "EntityDef"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0FCD3EF7; }
  static constexpr unsigned GetTypeNameHash() { return 0x511C9D4F; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &MapEntity::m_EntityDef; }
};

template <typename Self>
struct StormReflTypeInfo<MapEntity>::field_data<4, Self> : public StormReflTypeInfo<MapEntity>::field_data_static<4>
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
struct StormReflTypeInfo<MapServerObject>
{
  using MyBase = void;
  static constexpr int fields_n = 5;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "MapServerObject"; }
  static constexpr auto GetNameHash() { return 0xAC5C2595; }
  static MapServerObject & GetDefault() { static MapServerObject def; return def; }
};

template <>
struct StormReflTypeInfo<MapServerObject>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &MapServerObject::m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<MapServerObject>::field_data<0, Self> : public StormReflTypeInfo<MapServerObject>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<MapServerObject>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<MapServerObject>::field_data_static<1>
{
  using member_type = RUInt; // RNumber<unsigned int>
  static constexpr auto GetName() { return "m_GUID"; }
  static constexpr auto GetType() { return "RNumber<unsigned int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x83551827; }
  static constexpr unsigned GetTypeNameHash() { return 0x7B4FB98C; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &MapServerObject::m_GUID; }
};

template <typename Self>
struct StormReflTypeInfo<MapServerObject>::field_data<1, Self> : public StormReflTypeInfo<MapServerObject>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RUInt> & Get() { return self.m_GUID; }
  std::add_const_t<std::remove_reference_t<RUInt>> & Get() const { return self.m_GUID; }
  void SetDefault() { self.m_GUID = StormReflTypeInfo<MapServerObject>::GetDefault().m_GUID; }
};

template <>
struct StormReflTypeInfo<MapServerObject>::annotations<1>
{
  static constexpr int annotations_n = 1;
  template <int A> struct annoation { };
};

template <>
struct StormReflTypeInfo<MapServerObject>::annotations<1>::annoation<0>
{
  static constexpr const char * GetAnnotation() { return "noui"; }
  static constexpr uint32_t GetAnnotationHash() { return 0xDF10877E; }
};

template <>
struct StormReflTypeInfo<MapServerObject>::field_data_static<2>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_XPosition"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAB2A0DB2; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &MapServerObject::m_XPosition; }
};

template <typename Self>
struct StormReflTypeInfo<MapServerObject>::field_data<2, Self> : public StormReflTypeInfo<MapServerObject>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_XPosition; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_XPosition; }
  void SetDefault() { self.m_XPosition = StormReflTypeInfo<MapServerObject>::GetDefault().m_XPosition; }
};

template <>
struct StormReflTypeInfo<MapServerObject>::field_data_static<3>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_YPosition"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xBC5119F1; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &MapServerObject::m_YPosition; }
};

template <typename Self>
struct StormReflTypeInfo<MapServerObject>::field_data<3, Self> : public StormReflTypeInfo<MapServerObject>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_YPosition; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_YPosition; }
  void SetDefault() { self.m_YPosition = StormReflTypeInfo<MapServerObject>::GetDefault().m_YPosition; }
};

template <>
struct StormReflTypeInfo<MapServerObject>::field_data_static<4>
{
  using member_type = ServerObjectDef; // ServerObjectDef
  static constexpr auto GetName() { return "m_ServerObject"; }
  static constexpr auto GetType() { return "ServerObjectDef"; }
  static constexpr unsigned GetFieldNameHash() { return 0x223A5929; }
  static constexpr unsigned GetTypeNameHash() { return 0x97B44C7B; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &MapServerObject::m_ServerObject; }
};

template <typename Self>
struct StormReflTypeInfo<MapServerObject>::field_data<4, Self> : public StormReflTypeInfo<MapServerObject>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, ServerObjectDef> & Get() { return self.m_ServerObject; }
  std::add_const_t<std::remove_reference_t<ServerObjectDef>> & Get() const { return self.m_ServerObject; }
  void SetDefault() { self.m_ServerObject = StormReflTypeInfo<MapServerObject>::GetDefault().m_ServerObject; }
};

template <>
struct StormReflTypeInfo<MapServerObjectLayer>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "MapServerObjectLayer"; }
  static constexpr auto GetNameHash() { return 0xCC04DD43; }
  static MapServerObjectLayer & GetDefault() { static MapServerObjectLayer def; return def; }
};

template <>
struct StormReflTypeInfo<MapServerObjectLayer>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &MapServerObjectLayer::m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<MapServerObjectLayer>::field_data<0, Self> : public StormReflTypeInfo<MapServerObjectLayer>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<MapServerObjectLayer>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<MapServerObjectLayer>::field_data_static<1>
{
  using member_type = RMergeList<MapServerObject>; // RMergeList<MapServerObject>
  static constexpr auto GetName() { return "m_Objects"; }
  static constexpr auto GetType() { return "RMergeList<MapServerObject>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x27E8B926; }
  static constexpr unsigned GetTypeNameHash() { return 0xEA9F1507; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &MapServerObjectLayer::m_Objects; }
};

template <typename Self>
struct StormReflTypeInfo<MapServerObjectLayer>::field_data<1, Self> : public StormReflTypeInfo<MapServerObjectLayer>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<MapServerObject>> & Get() { return self.m_Objects; }
  std::add_const_t<std::remove_reference_t<RMergeList<MapServerObject>>> & Get() const { return self.m_Objects; }
  void SetDefault() { self.m_Objects = StormReflTypeInfo<MapServerObjectLayer>::GetDefault().m_Objects; }
};

template <>
struct StormReflTypeInfo<MapServerObjectLayer>::annotations<1>
{
  static constexpr int annotations_n = 1;
  template <int A> struct annoation { };
};

template <>
struct StormReflTypeInfo<MapServerObjectLayer>::annotations<1>::annoation<0>
{
  static constexpr const char * GetAnnotation() { return "noui"; }
  static constexpr uint32_t GetAnnotationHash() { return 0xDF10877E; }
};

template <>
struct StormReflTypeInfo<MapParalaxLayerObject>
{
  using MyBase = void;
  static constexpr int fields_n = 7;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "MapParalaxLayerObject"; }
  static constexpr auto GetNameHash() { return 0xF8B4CF99; }
  static MapParalaxLayerObject & GetDefault() { static MapParalaxLayerObject def; return def; }
};

template <>
struct StormReflTypeInfo<MapParalaxLayerObject>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &MapParalaxLayerObject::m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<MapParalaxLayerObject>::field_data<0, Self> : public StormReflTypeInfo<MapParalaxLayerObject>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<MapParalaxLayerObject>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<MapParalaxLayerObject>::field_data_static<1>
{
  using member_type = REnum<MapParalaxLayerObjectType>; // REnum<MapParalaxLayerObjectType>
  static constexpr auto GetName() { return "m_Type"; }
  static constexpr auto GetType() { return "REnum<MapParalaxLayerObjectType>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB243C236; }
  static constexpr unsigned GetTypeNameHash() { return 0xEA67D680; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &MapParalaxLayerObject::m_Type; }
};

template <typename Self>
struct StormReflTypeInfo<MapParalaxLayerObject>::field_data<1, Self> : public StormReflTypeInfo<MapParalaxLayerObject>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, REnum<MapParalaxLayerObjectType>> & Get() { return self.m_Type; }
  std::add_const_t<std::remove_reference_t<REnum<MapParalaxLayerObjectType>>> & Get() const { return self.m_Type; }
  void SetDefault() { self.m_Type = StormReflTypeInfo<MapParalaxLayerObject>::GetDefault().m_Type; }
};

template <>
struct StormReflTypeInfo<MapParalaxLayerObject>::field_data_static<2>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_File"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB202A30F; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &MapParalaxLayerObject::m_File; }
};

template <typename Self>
struct StormReflTypeInfo<MapParalaxLayerObject>::field_data<2, Self> : public StormReflTypeInfo<MapParalaxLayerObject>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_File; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_File; }
  void SetDefault() { self.m_File = StormReflTypeInfo<MapParalaxLayerObject>::GetDefault().m_File; }
};

template <>
struct StormReflTypeInfo<MapParalaxLayerObject>::annotations<2>
{
  static constexpr int annotations_n = 1;
  template <int A> struct annoation { };
};

template <>
struct StormReflTypeInfo<MapParalaxLayerObject>::annotations<2>::annoation<0>
{
  static constexpr const char * GetAnnotation() { return "file: paralax"; }
  static constexpr uint32_t GetAnnotationHash() { return 0x774D48F8; }
};

template <>
struct StormReflTypeInfo<MapParalaxLayerObject>::field_data_static<3>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Animation"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5172A5C7; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &MapParalaxLayerObject::m_Animation; }
};

template <typename Self>
struct StormReflTypeInfo<MapParalaxLayerObject>::field_data<3, Self> : public StormReflTypeInfo<MapParalaxLayerObject>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Animation; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Animation; }
  void SetDefault() { self.m_Animation = StormReflTypeInfo<MapParalaxLayerObject>::GetDefault().m_Animation; }
};

template <>
struct StormReflTypeInfo<MapParalaxLayerObject>::field_data_static<4>
{
  using member_type = RFloat; // RNumber<float>
  static constexpr auto GetName() { return "m_PresimTime"; }
  static constexpr auto GetType() { return "RNumber<float>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA41F8E10; }
  static constexpr unsigned GetTypeNameHash() { return 0x17411E4A; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &MapParalaxLayerObject::m_PresimTime; }
};

template <typename Self>
struct StormReflTypeInfo<MapParalaxLayerObject>::field_data<4, Self> : public StormReflTypeInfo<MapParalaxLayerObject>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RFloat> & Get() { return self.m_PresimTime; }
  std::add_const_t<std::remove_reference_t<RFloat>> & Get() const { return self.m_PresimTime; }
  void SetDefault() { self.m_PresimTime = StormReflTypeInfo<MapParalaxLayerObject>::GetDefault().m_PresimTime; }
};

template <>
struct StormReflTypeInfo<MapParalaxLayerObject>::field_data_static<5>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_XPosition"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAB2A0DB2; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &MapParalaxLayerObject::m_XPosition; }
};

template <typename Self>
struct StormReflTypeInfo<MapParalaxLayerObject>::field_data<5, Self> : public StormReflTypeInfo<MapParalaxLayerObject>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_XPosition; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_XPosition; }
  void SetDefault() { self.m_XPosition = StormReflTypeInfo<MapParalaxLayerObject>::GetDefault().m_XPosition; }
};

template <>
struct StormReflTypeInfo<MapParalaxLayerObject>::field_data_static<6>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_YPosition"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xBC5119F1; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &MapParalaxLayerObject::m_YPosition; }
};

template <typename Self>
struct StormReflTypeInfo<MapParalaxLayerObject>::field_data<6, Self> : public StormReflTypeInfo<MapParalaxLayerObject>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_YPosition; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_YPosition; }
  void SetDefault() { self.m_YPosition = StormReflTypeInfo<MapParalaxLayerObject>::GetDefault().m_YPosition; }
};

template <>
struct StormReflTypeInfo<MapParalaxLayer>
{
  using MyBase = void;
  static constexpr int fields_n = 12;
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
struct StormReflTypeInfo<MapParalaxLayer>::field_data_static<11>
{
  using member_type = RMergeList<MapParalaxLayerObject>; // RMergeList<MapParalaxLayerObject>
  static constexpr auto GetName() { return "m_Objects"; }
  static constexpr auto GetType() { return "RMergeList<MapParalaxLayerObject>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x27E8B926; }
  static constexpr unsigned GetTypeNameHash() { return 0xAA26087C; }
  static constexpr auto GetFieldIndex() { return 11; }
  static constexpr auto GetMemberPtr() { return &MapParalaxLayer::m_Objects; }
};

template <typename Self>
struct StormReflTypeInfo<MapParalaxLayer>::field_data<11, Self> : public StormReflTypeInfo<MapParalaxLayer>::field_data_static<11>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<MapParalaxLayerObject>> & Get() { return self.m_Objects; }
  std::add_const_t<std::remove_reference_t<RMergeList<MapParalaxLayerObject>>> & Get() const { return self.m_Objects; }
  void SetDefault() { self.m_Objects = StormReflTypeInfo<MapParalaxLayer>::GetDefault().m_Objects; }
};

template <>
struct StormReflTypeInfo<MapParalaxLayer>::annotations<11>
{
  static constexpr int annotations_n = 1;
  template <int A> struct annoation { };
};

template <>
struct StormReflTypeInfo<MapParalaxLayer>::annotations<11>::annoation<0>
{
  static constexpr const char * GetAnnotation() { return "noui"; }
  static constexpr uint32_t GetAnnotationHash() { return 0xDF10877E; }
};

template <>
struct StormReflTypeInfo<MapEffectLayer>
{
  using MyBase = void;
  static constexpr int fields_n = 4;
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
  using member_type = RUInt; // RNumber<unsigned int>
  static constexpr auto GetName() { return "m_GUID"; }
  static constexpr auto GetType() { return "RNumber<unsigned int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x83551827; }
  static constexpr unsigned GetTypeNameHash() { return 0x7B4FB98C; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &MapEffectLayer::m_GUID; }
};

template <typename Self>
struct StormReflTypeInfo<MapEffectLayer>::field_data<1, Self> : public StormReflTypeInfo<MapEffectLayer>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RUInt> & Get() { return self.m_GUID; }
  std::add_const_t<std::remove_reference_t<RUInt>> & Get() const { return self.m_GUID; }
  void SetDefault() { self.m_GUID = StormReflTypeInfo<MapEffectLayer>::GetDefault().m_GUID; }
};

template <>
struct StormReflTypeInfo<MapEffectLayer>::annotations<1>
{
  static constexpr int annotations_n = 1;
  template <int A> struct annoation { };
};

template <>
struct StormReflTypeInfo<MapEffectLayer>::annotations<1>::annoation<0>
{
  static constexpr const char * GetAnnotation() { return "noui"; }
  static constexpr uint32_t GetAnnotationHash() { return 0xDF10877E; }
};

template <>
struct StormReflTypeInfo<MapEffectLayer>::field_data_static<2>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_LayerOrder"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3741FE10; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &MapEffectLayer::m_LayerOrder; }
};

template <typename Self>
struct StormReflTypeInfo<MapEffectLayer>::field_data<2, Self> : public StormReflTypeInfo<MapEffectLayer>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_LayerOrder; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_LayerOrder; }
  void SetDefault() { self.m_LayerOrder = StormReflTypeInfo<MapEffectLayer>::GetDefault().m_LayerOrder; }
};

template <>
struct StormReflTypeInfo<MapEffectLayer>::field_data_static<3>
{
  using member_type = RPolymorphic<MapEffectLayerInitData, MapEffectLayerLogicBase>; // RPolymorphicBase<MapEffectLayerInitData, TypeDatabase<MapEffectLayerInitData, MapEffectLayerLogicBase>, TypeDatabaseTypeInfo<MapEffectLayerInitData, MapEffectLayerLogicBase>, false>
  static constexpr auto GetName() { return "m_EffectLayerData"; }
  static constexpr auto GetType() { return "RPolymorphicBase<MapEffectLayerInitData, TypeDatabase<MapEffectLayerInitData, MapEffectLayerLogicBase>, TypeDatabaseTypeInfo<MapEffectLayerInitData, MapEffectLayerLogicBase>, false>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE1AE0B1F; }
  static constexpr unsigned GetTypeNameHash() { return 0x2FE182EA; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &MapEffectLayer::m_EffectLayerData; }
};

template <typename Self>
struct StormReflTypeInfo<MapEffectLayer>::field_data<3, Self> : public StormReflTypeInfo<MapEffectLayer>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RPolymorphic<MapEffectLayerInitData, MapEffectLayerLogicBase>> & Get() { return self.m_EffectLayerData; }
  std::add_const_t<std::remove_reference_t<RPolymorphic<MapEffectLayerInitData, MapEffectLayerLogicBase>>> & Get() const { return self.m_EffectLayerData; }
  void SetDefault() { self.m_EffectLayerData = StormReflTypeInfo<MapEffectLayer>::GetDefault().m_EffectLayerData; }
};

template <>
struct StormReflTypeInfo<MapAnchor>
{
  using MyBase = void;
  static constexpr int fields_n = 6;
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
  using member_type = RUInt; // RNumber<unsigned int>
  static constexpr auto GetName() { return "m_GUID"; }
  static constexpr auto GetType() { return "RNumber<unsigned int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x83551827; }
  static constexpr unsigned GetTypeNameHash() { return 0x7B4FB98C; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &MapAnchor::m_GUID; }
};

template <typename Self>
struct StormReflTypeInfo<MapAnchor>::field_data<1, Self> : public StormReflTypeInfo<MapAnchor>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RUInt> & Get() { return self.m_GUID; }
  std::add_const_t<std::remove_reference_t<RUInt>> & Get() const { return self.m_GUID; }
  void SetDefault() { self.m_GUID = StormReflTypeInfo<MapAnchor>::GetDefault().m_GUID; }
};

template <>
struct StormReflTypeInfo<MapAnchor>::annotations<1>
{
  static constexpr int annotations_n = 1;
  template <int A> struct annoation { };
};

template <>
struct StormReflTypeInfo<MapAnchor>::annotations<1>::annoation<0>
{
  static constexpr const char * GetAnnotation() { return "noui"; }
  static constexpr uint32_t GetAnnotationHash() { return 0xDF10877E; }
};

template <>
struct StormReflTypeInfo<MapAnchor>::field_data_static<2>
{
  using member_type = RPolymorphic<AnchorDataBase>; // RPolymorphicBase<AnchorDataBase, TypeDatabase<AnchorDataBase, void>, TypeDatabaseTypeInfo<AnchorDataBase, void>, false>
  static constexpr auto GetName() { return "m_AnchorData"; }
  static constexpr auto GetType() { return "RPolymorphicBase<AnchorDataBase, TypeDatabase<AnchorDataBase, void>, TypeDatabaseTypeInfo<AnchorDataBase, void>, false>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x73BF9C78; }
  static constexpr unsigned GetTypeNameHash() { return 0xDC04E34E; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &MapAnchor::m_AnchorData; }
};

template <typename Self>
struct StormReflTypeInfo<MapAnchor>::field_data<2, Self> : public StormReflTypeInfo<MapAnchor>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RPolymorphic<AnchorDataBase>> & Get() { return self.m_AnchorData; }
  std::add_const_t<std::remove_reference_t<RPolymorphic<AnchorDataBase>>> & Get() const { return self.m_AnchorData; }
  void SetDefault() { self.m_AnchorData = StormReflTypeInfo<MapAnchor>::GetDefault().m_AnchorData; }
};

template <>
struct StormReflTypeInfo<MapAnchor>::field_data_static<3>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Sprite"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x7822D856; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &MapAnchor::m_Sprite; }
};

template <typename Self>
struct StormReflTypeInfo<MapAnchor>::field_data<3, Self> : public StormReflTypeInfo<MapAnchor>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Sprite; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Sprite; }
  void SetDefault() { self.m_Sprite = StormReflTypeInfo<MapAnchor>::GetDefault().m_Sprite; }
};

template <>
struct StormReflTypeInfo<MapAnchor>::annotations<3>
{
  static constexpr int annotations_n = 1;
  template <int A> struct annoation { };
};

template <>
struct StormReflTypeInfo<MapAnchor>::annotations<3>::annoation<0>
{
  static constexpr const char * GetAnnotation() { return "file: sprite"; }
  static constexpr uint32_t GetAnnotationHash() { return 0x1563DF3B; }
};

template <>
struct StormReflTypeInfo<MapAnchor>::field_data_static<4>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_X"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE7DD193C; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &MapAnchor::m_X; }
};

template <typename Self>
struct StormReflTypeInfo<MapAnchor>::field_data<4, Self> : public StormReflTypeInfo<MapAnchor>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_X; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_X; }
  void SetDefault() { self.m_X = StormReflTypeInfo<MapAnchor>::GetDefault().m_X; }
};

template <>
struct StormReflTypeInfo<MapAnchor>::field_data_static<5>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_Y"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x90DA29AA; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &MapAnchor::m_Y; }
};

template <typename Self>
struct StormReflTypeInfo<MapAnchor>::field_data<5, Self> : public StormReflTypeInfo<MapAnchor>::field_data_static<5>
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
  static constexpr int fields_n = 4;
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
  using member_type = RUInt; // RNumber<unsigned int>
  static constexpr auto GetName() { return "m_GUID"; }
  static constexpr auto GetType() { return "RNumber<unsigned int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x83551827; }
  static constexpr unsigned GetTypeNameHash() { return 0x7B4FB98C; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &MapPath::m_GUID; }
};

template <typename Self>
struct StormReflTypeInfo<MapPath>::field_data<1, Self> : public StormReflTypeInfo<MapPath>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RUInt> & Get() { return self.m_GUID; }
  std::add_const_t<std::remove_reference_t<RUInt>> & Get() const { return self.m_GUID; }
  void SetDefault() { self.m_GUID = StormReflTypeInfo<MapPath>::GetDefault().m_GUID; }
};

template <>
struct StormReflTypeInfo<MapPath>::annotations<1>
{
  static constexpr int annotations_n = 1;
  template <int A> struct annoation { };
};

template <>
struct StormReflTypeInfo<MapPath>::annotations<1>::annoation<0>
{
  static constexpr const char * GetAnnotation() { return "noui"; }
  static constexpr uint32_t GetAnnotationHash() { return 0xDF10877E; }
};

template <>
struct StormReflTypeInfo<MapPath>::field_data_static<2>
{
  using member_type = RPolymorphic<PathDataBase>; // RPolymorphicBase<PathDataBase, TypeDatabase<PathDataBase, void>, TypeDatabaseTypeInfo<PathDataBase, void>, false>
  static constexpr auto GetName() { return "m_PathData"; }
  static constexpr auto GetType() { return "RPolymorphicBase<PathDataBase, TypeDatabase<PathDataBase, void>, TypeDatabaseTypeInfo<PathDataBase, void>, false>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x07EB2D9C; }
  static constexpr unsigned GetTypeNameHash() { return 0x404592FC; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &MapPath::m_PathData; }
};

template <typename Self>
struct StormReflTypeInfo<MapPath>::field_data<2, Self> : public StormReflTypeInfo<MapPath>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RPolymorphic<PathDataBase>> & Get() { return self.m_PathData; }
  std::add_const_t<std::remove_reference_t<RPolymorphic<PathDataBase>>> & Get() const { return self.m_PathData; }
  void SetDefault() { self.m_PathData = StormReflTypeInfo<MapPath>::GetDefault().m_PathData; }
};

template <>
struct StormReflTypeInfo<MapPath>::field_data_static<3>
{
  using member_type = RMergeList<MapPathPoint>; // RMergeList<MapPathPoint>
  static constexpr auto GetName() { return "m_Points"; }
  static constexpr auto GetType() { return "RMergeList<MapPathPoint>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6A85D9E1; }
  static constexpr unsigned GetTypeNameHash() { return 0xE00E4311; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &MapPath::m_Points; }
};

template <typename Self>
struct StormReflTypeInfo<MapPath>::field_data<3, Self> : public StormReflTypeInfo<MapPath>::field_data_static<3>
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
  static constexpr int fields_n = 7;
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
  using member_type = RUInt; // RNumber<unsigned int>
  static constexpr auto GetName() { return "m_GUID"; }
  static constexpr auto GetType() { return "RNumber<unsigned int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x83551827; }
  static constexpr unsigned GetTypeNameHash() { return 0x7B4FB98C; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &MapVolume::m_GUID; }
};

template <typename Self>
struct StormReflTypeInfo<MapVolume>::field_data<1, Self> : public StormReflTypeInfo<MapVolume>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RUInt> & Get() { return self.m_GUID; }
  std::add_const_t<std::remove_reference_t<RUInt>> & Get() const { return self.m_GUID; }
  void SetDefault() { self.m_GUID = StormReflTypeInfo<MapVolume>::GetDefault().m_GUID; }
};

template <>
struct StormReflTypeInfo<MapVolume>::annotations<1>
{
  static constexpr int annotations_n = 1;
  template <int A> struct annoation { };
};

template <>
struct StormReflTypeInfo<MapVolume>::annotations<1>::annoation<0>
{
  static constexpr const char * GetAnnotation() { return "noui"; }
  static constexpr uint32_t GetAnnotationHash() { return 0xDF10877E; }
};

template <>
struct StormReflTypeInfo<MapVolume>::field_data_static<2>
{
  using member_type = RPolymorphic<VolumeDataBase>; // RPolymorphicBase<VolumeDataBase, TypeDatabase<VolumeDataBase, void>, TypeDatabaseTypeInfo<VolumeDataBase, void>, false>
  static constexpr auto GetName() { return "m_VolumeData"; }
  static constexpr auto GetType() { return "RPolymorphicBase<VolumeDataBase, TypeDatabase<VolumeDataBase, void>, TypeDatabaseTypeInfo<VolumeDataBase, void>, false>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE1971791; }
  static constexpr unsigned GetTypeNameHash() { return 0xF08E00EE; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &MapVolume::m_VolumeData; }
};

template <typename Self>
struct StormReflTypeInfo<MapVolume>::field_data<2, Self> : public StormReflTypeInfo<MapVolume>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RPolymorphic<VolumeDataBase>> & Get() { return self.m_VolumeData; }
  std::add_const_t<std::remove_reference_t<RPolymorphic<VolumeDataBase>>> & Get() const { return self.m_VolumeData; }
  void SetDefault() { self.m_VolumeData = StormReflTypeInfo<MapVolume>::GetDefault().m_VolumeData; }
};

template <>
struct StormReflTypeInfo<MapVolume>::field_data_static<3>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_XStart"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8316F451; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &MapVolume::m_XStart; }
};

template <typename Self>
struct StormReflTypeInfo<MapVolume>::field_data<3, Self> : public StormReflTypeInfo<MapVolume>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_XStart; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_XStart; }
  void SetDefault() { self.m_XStart = StormReflTypeInfo<MapVolume>::GetDefault().m_XStart; }
};

template <>
struct StormReflTypeInfo<MapVolume>::field_data_static<4>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_YStart"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x484A27F4; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &MapVolume::m_YStart; }
};

template <typename Self>
struct StormReflTypeInfo<MapVolume>::field_data<4, Self> : public StormReflTypeInfo<MapVolume>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_YStart; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_YStart; }
  void SetDefault() { self.m_YStart = StormReflTypeInfo<MapVolume>::GetDefault().m_YStart; }
};

template <>
struct StormReflTypeInfo<MapVolume>::field_data_static<5>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_XEnd"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x76A26E33; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &MapVolume::m_XEnd; }
};

template <typename Self>
struct StormReflTypeInfo<MapVolume>::field_data<5, Self> : public StormReflTypeInfo<MapVolume>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_XEnd; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_XEnd; }
  void SetDefault() { self.m_XEnd = StormReflTypeInfo<MapVolume>::GetDefault().m_XEnd; }
};

template <>
struct StormReflTypeInfo<MapVolume>::field_data_static<6>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_YEnd"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xCE1E0956; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &MapVolume::m_YEnd; }
};

template <typename Self>
struct StormReflTypeInfo<MapVolume>::field_data<6, Self> : public StormReflTypeInfo<MapVolume>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_YEnd; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_YEnd; }
  void SetDefault() { self.m_YEnd = StormReflTypeInfo<MapVolume>::GetDefault().m_YEnd; }
};

template <>
struct StormReflTypeInfo<MapPathfindingSurface>
{
  using MyBase = void;
  static constexpr int fields_n = 7;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "MapPathfindingSurface"; }
  static constexpr auto GetNameHash() { return 0x98EE40AC; }
  static MapPathfindingSurface & GetDefault() { static MapPathfindingSurface def; return def; }
};

template <>
struct StormReflTypeInfo<MapPathfindingSurface>::field_data_static<0>
{
  using member_type = Vector2; // Vector2
  static constexpr auto GetName() { return "m_P1"; }
  static constexpr auto GetType() { return "Vector2"; }
  static constexpr unsigned GetFieldNameHash() { return 0x648DC421; }
  static constexpr unsigned GetTypeNameHash() { return 0x29CA61A5; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &MapPathfindingSurface::m_P1; }
};

template <typename Self>
struct StormReflTypeInfo<MapPathfindingSurface>::field_data<0, Self> : public StormReflTypeInfo<MapPathfindingSurface>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, Vector2> & Get() { return self.m_P1; }
  std::add_const_t<std::remove_reference_t<Vector2>> & Get() const { return self.m_P1; }
  void SetDefault() { self.m_P1 = StormReflTypeInfo<MapPathfindingSurface>::GetDefault().m_P1; }
};

template <>
struct StormReflTypeInfo<MapPathfindingSurface>::field_data_static<1>
{
  using member_type = Vector2; // Vector2
  static constexpr auto GetName() { return "m_P2"; }
  static constexpr auto GetType() { return "Vector2"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFD84959B; }
  static constexpr unsigned GetTypeNameHash() { return 0x29CA61A5; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &MapPathfindingSurface::m_P2; }
};

template <typename Self>
struct StormReflTypeInfo<MapPathfindingSurface>::field_data<1, Self> : public StormReflTypeInfo<MapPathfindingSurface>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, Vector2> & Get() { return self.m_P2; }
  std::add_const_t<std::remove_reference_t<Vector2>> & Get() const { return self.m_P2; }
  void SetDefault() { self.m_P2 = StormReflTypeInfo<MapPathfindingSurface>::GetDefault().m_P2; }
};

template <>
struct StormReflTypeInfo<MapPathfindingSurface>::field_data_static<2>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_Clearance"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF36CEACD; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &MapPathfindingSurface::m_Clearance; }
};

template <typename Self>
struct StormReflTypeInfo<MapPathfindingSurface>::field_data<2, Self> : public StormReflTypeInfo<MapPathfindingSurface>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_Clearance; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_Clearance; }
  void SetDefault() { self.m_Clearance = StormReflTypeInfo<MapPathfindingSurface>::GetDefault().m_Clearance; }
};

template <>
struct StormReflTypeInfo<MapPathfindingSurface>::field_data_static<3>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_StartConnections1"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF1F70C29; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &MapPathfindingSurface::m_StartConnections1; }
};

template <typename Self>
struct StormReflTypeInfo<MapPathfindingSurface>::field_data<3, Self> : public StormReflTypeInfo<MapPathfindingSurface>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_StartConnections1; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_StartConnections1; }
  void SetDefault() { self.m_StartConnections1 = StormReflTypeInfo<MapPathfindingSurface>::GetDefault().m_StartConnections1; }
};

template <>
struct StormReflTypeInfo<MapPathfindingSurface>::field_data_static<4>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_EndConnections1"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x132DE55F; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &MapPathfindingSurface::m_EndConnections1; }
};

template <typename Self>
struct StormReflTypeInfo<MapPathfindingSurface>::field_data<4, Self> : public StormReflTypeInfo<MapPathfindingSurface>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_EndConnections1; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_EndConnections1; }
  void SetDefault() { self.m_EndConnections1 = StormReflTypeInfo<MapPathfindingSurface>::GetDefault().m_EndConnections1; }
};

template <>
struct StormReflTypeInfo<MapPathfindingSurface>::field_data_static<5>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_StartConnections2"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x68FE5D93; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &MapPathfindingSurface::m_StartConnections2; }
};

template <typename Self>
struct StormReflTypeInfo<MapPathfindingSurface>::field_data<5, Self> : public StormReflTypeInfo<MapPathfindingSurface>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_StartConnections2; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_StartConnections2; }
  void SetDefault() { self.m_StartConnections2 = StormReflTypeInfo<MapPathfindingSurface>::GetDefault().m_StartConnections2; }
};

template <>
struct StormReflTypeInfo<MapPathfindingSurface>::field_data_static<6>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_EndConnections2"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8A24B4E5; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &MapPathfindingSurface::m_EndConnections2; }
};

template <typename Self>
struct StormReflTypeInfo<MapPathfindingSurface>::field_data<6, Self> : public StormReflTypeInfo<MapPathfindingSurface>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_EndConnections2; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_EndConnections2; }
  void SetDefault() { self.m_EndConnections2 = StormReflTypeInfo<MapPathfindingSurface>::GetDefault().m_EndConnections2; }
};

template <>
struct StormReflTypeInfo<MapPathfindingSurfaceConnection>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "MapPathfindingSurfaceConnection"; }
  static constexpr auto GetNameHash() { return 0x412196E6; }
  static MapPathfindingSurfaceConnection & GetDefault() { static MapPathfindingSurfaceConnection def; return def; }
};

template <>
struct StormReflTypeInfo<MapPathfindingSurfaceConnection>::field_data_static<0>
{
  using member_type = uint32_t; // unsigned int
  static constexpr auto GetName() { return "m_SurfaceIndex"; }
  static constexpr auto GetType() { return "unsigned int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA485689B; }
  static constexpr unsigned GetTypeNameHash() { return 0x562EF932; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &MapPathfindingSurfaceConnection::m_SurfaceIndex; }
};

template <typename Self>
struct StormReflTypeInfo<MapPathfindingSurfaceConnection>::field_data<0, Self> : public StormReflTypeInfo<MapPathfindingSurfaceConnection>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint32_t> & Get() { return self.m_SurfaceIndex; }
  std::add_const_t<std::remove_reference_t<uint32_t>> & Get() const { return self.m_SurfaceIndex; }
  void SetDefault() { self.m_SurfaceIndex = StormReflTypeInfo<MapPathfindingSurfaceConnection>::GetDefault().m_SurfaceIndex; }
};

template <>
struct StormReflTypeInfo<MapPathfindingSurfaceConnection>::field_data_static<1>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_P1"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x648DC421; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &MapPathfindingSurfaceConnection::m_P1; }
};

template <typename Self>
struct StormReflTypeInfo<MapPathfindingSurfaceConnection>::field_data<1, Self> : public StormReflTypeInfo<MapPathfindingSurfaceConnection>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_P1; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_P1; }
  void SetDefault() { self.m_P1 = StormReflTypeInfo<MapPathfindingSurfaceConnection>::GetDefault().m_P1; }
};

template <>
struct StormReflTypeInfo<MapPathfindingCalculatedInfo>
{
  using MyBase = void;
  static constexpr int fields_n = 8;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "MapPathfindingCalculatedInfo"; }
  static constexpr auto GetNameHash() { return 0x68B8A4ED; }
  static MapPathfindingCalculatedInfo & GetDefault() { static MapPathfindingCalculatedInfo def; return def; }
};

template <>
struct StormReflTypeInfo<MapPathfindingCalculatedInfo>::field_data_static<0>
{
  using member_type = uint32_t; // unsigned int
  static constexpr auto GetName() { return "m_Id"; }
  static constexpr auto GetType() { return "unsigned int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE48CC842; }
  static constexpr unsigned GetTypeNameHash() { return 0x562EF932; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &MapPathfindingCalculatedInfo::m_Id; }
};

template <typename Self>
struct StormReflTypeInfo<MapPathfindingCalculatedInfo>::field_data<0, Self> : public StormReflTypeInfo<MapPathfindingCalculatedInfo>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint32_t> & Get() { return self.m_Id; }
  std::add_const_t<std::remove_reference_t<uint32_t>> & Get() const { return self.m_Id; }
  void SetDefault() { self.m_Id = StormReflTypeInfo<MapPathfindingCalculatedInfo>::GetDefault().m_Id; }
};

template <>
struct StormReflTypeInfo<MapPathfindingCalculatedInfo>::field_data_static<1>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_GridWidth"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xEAEC9679; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &MapPathfindingCalculatedInfo::m_GridWidth; }
};

template <typename Self>
struct StormReflTypeInfo<MapPathfindingCalculatedInfo>::field_data<1, Self> : public StormReflTypeInfo<MapPathfindingCalculatedInfo>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_GridWidth; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_GridWidth; }
  void SetDefault() { self.m_GridWidth = StormReflTypeInfo<MapPathfindingCalculatedInfo>::GetDefault().m_GridWidth; }
};

template <>
struct StormReflTypeInfo<MapPathfindingCalculatedInfo>::field_data_static<2>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_GridHeight"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x7723E71D; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &MapPathfindingCalculatedInfo::m_GridHeight; }
};

template <typename Self>
struct StormReflTypeInfo<MapPathfindingCalculatedInfo>::field_data<2, Self> : public StormReflTypeInfo<MapPathfindingCalculatedInfo>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_GridHeight; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_GridHeight; }
  void SetDefault() { self.m_GridHeight = StormReflTypeInfo<MapPathfindingCalculatedInfo>::GetDefault().m_GridHeight; }
};

template <>
struct StormReflTypeInfo<MapPathfindingCalculatedInfo>::field_data_static<3>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_StartX"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x87158667; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &MapPathfindingCalculatedInfo::m_StartX; }
};

template <typename Self>
struct StormReflTypeInfo<MapPathfindingCalculatedInfo>::field_data<3, Self> : public StormReflTypeInfo<MapPathfindingCalculatedInfo>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_StartX; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_StartX; }
  void SetDefault() { self.m_StartX = StormReflTypeInfo<MapPathfindingCalculatedInfo>::GetDefault().m_StartX; }
};

template <>
struct StormReflTypeInfo<MapPathfindingCalculatedInfo>::field_data_static<4>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_StartY"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF012B6F1; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &MapPathfindingCalculatedInfo::m_StartY; }
};

template <typename Self>
struct StormReflTypeInfo<MapPathfindingCalculatedInfo>::field_data<4, Self> : public StormReflTypeInfo<MapPathfindingCalculatedInfo>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_StartY; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_StartY; }
  void SetDefault() { self.m_StartY = StormReflTypeInfo<MapPathfindingCalculatedInfo>::GetDefault().m_StartY; }
};

template <>
struct StormReflTypeInfo<MapPathfindingCalculatedInfo>::field_data_static<5>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_SizeX"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x9714EE49; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &MapPathfindingCalculatedInfo::m_SizeX; }
};

template <typename Self>
struct StormReflTypeInfo<MapPathfindingCalculatedInfo>::field_data<5, Self> : public StormReflTypeInfo<MapPathfindingCalculatedInfo>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_SizeX; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_SizeX; }
  void SetDefault() { self.m_SizeX = StormReflTypeInfo<MapPathfindingCalculatedInfo>::GetDefault().m_SizeX; }
};

template <>
struct StormReflTypeInfo<MapPathfindingCalculatedInfo>::field_data_static<6>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_SizeY"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE013DEDF; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &MapPathfindingCalculatedInfo::m_SizeY; }
};

template <typename Self>
struct StormReflTypeInfo<MapPathfindingCalculatedInfo>::field_data<6, Self> : public StormReflTypeInfo<MapPathfindingCalculatedInfo>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_SizeY; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_SizeY; }
  void SetDefault() { self.m_SizeY = StormReflTypeInfo<MapPathfindingCalculatedInfo>::GetDefault().m_SizeY; }
};

template <>
struct StormReflTypeInfo<MapPathfindingCalculatedInfo>::field_data_static<7>
{
  using member_type = std::vector<std::tuple<uint8_t, uint8_t, uint8_t> >; // std::vector<std::tuple<unsigned char, unsigned char, unsigned char>, std::allocator<std::tuple<unsigned char, unsigned char, unsigned char> > >
  static constexpr auto GetName() { return "m_GridInfo"; }
  static constexpr auto GetType() { return "std::vector<std::tuple<unsigned char, unsigned char, unsigned char>, std::allocator<std::tuple<unsigned char, unsigned char, unsigned char> > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3B61AD8D; }
  static constexpr unsigned GetTypeNameHash() { return 0x496EAD29; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &MapPathfindingCalculatedInfo::m_GridInfo; }
};

template <typename Self>
struct StormReflTypeInfo<MapPathfindingCalculatedInfo>::field_data<7, Self> : public StormReflTypeInfo<MapPathfindingCalculatedInfo>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<std::tuple<uint8_t, uint8_t, uint8_t> >> & Get() { return self.m_GridInfo; }
  std::add_const_t<std::remove_reference_t<std::vector<std::tuple<uint8_t, uint8_t, uint8_t> >>> & Get() const { return self.m_GridInfo; }
  void SetDefault() { self.m_GridInfo = StormReflTypeInfo<MapPathfindingCalculatedInfo>::GetDefault().m_GridInfo; }
};

template <>
struct StormReflTypeInfo<MapPathfindingInfo>
{
  using MyBase = void;
  static constexpr int fields_n = 7;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "MapPathfindingInfo"; }
  static constexpr auto GetNameHash() { return 0xD6EED399; }
  static MapPathfindingInfo & GetDefault() { static MapPathfindingInfo def; return def; }
};

template <>
struct StormReflTypeInfo<MapPathfindingInfo>::field_data_static<0>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_GridWidth"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xEAEC9679; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &MapPathfindingInfo::m_GridWidth; }
};

template <typename Self>
struct StormReflTypeInfo<MapPathfindingInfo>::field_data<0, Self> : public StormReflTypeInfo<MapPathfindingInfo>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_GridWidth; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_GridWidth; }
  void SetDefault() { self.m_GridWidth = StormReflTypeInfo<MapPathfindingInfo>::GetDefault().m_GridWidth; }
};

template <>
struct StormReflTypeInfo<MapPathfindingInfo>::field_data_static<1>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_GridHeight"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x7723E71D; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &MapPathfindingInfo::m_GridHeight; }
};

template <typename Self>
struct StormReflTypeInfo<MapPathfindingInfo>::field_data<1, Self> : public StormReflTypeInfo<MapPathfindingInfo>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_GridHeight; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_GridHeight; }
  void SetDefault() { self.m_GridHeight = StormReflTypeInfo<MapPathfindingInfo>::GetDefault().m_GridHeight; }
};

template <>
struct StormReflTypeInfo<MapPathfindingInfo>::field_data_static<2>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_MaximumClearanceX"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xCDFD06F2; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &MapPathfindingInfo::m_MaximumClearanceX; }
};

template <typename Self>
struct StormReflTypeInfo<MapPathfindingInfo>::field_data<2, Self> : public StormReflTypeInfo<MapPathfindingInfo>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_MaximumClearanceX; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_MaximumClearanceX; }
  void SetDefault() { self.m_MaximumClearanceX = StormReflTypeInfo<MapPathfindingInfo>::GetDefault().m_MaximumClearanceX; }
};

template <>
struct StormReflTypeInfo<MapPathfindingInfo>::field_data_static<3>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_MaximumClearanceY"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xBAFA3664; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &MapPathfindingInfo::m_MaximumClearanceY; }
};

template <typename Self>
struct StormReflTypeInfo<MapPathfindingInfo>::field_data<3, Self> : public StormReflTypeInfo<MapPathfindingInfo>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_MaximumClearanceY; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_MaximumClearanceY; }
  void SetDefault() { self.m_MaximumClearanceY = StormReflTypeInfo<MapPathfindingInfo>::GetDefault().m_MaximumClearanceY; }
};

template <>
struct StormReflTypeInfo<MapPathfindingInfo>::field_data_static<4>
{
  using member_type = RMergeList<RString>; // RMergeList<RString>
  static constexpr auto GetName() { return "m_CollisionMask"; }
  static constexpr auto GetType() { return "RMergeList<RString>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3E60CA75; }
  static constexpr unsigned GetTypeNameHash() { return 0x8C9238EC; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &MapPathfindingInfo::m_CollisionMask; }
};

template <typename Self>
struct StormReflTypeInfo<MapPathfindingInfo>::field_data<4, Self> : public StormReflTypeInfo<MapPathfindingInfo>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<RString>> & Get() { return self.m_CollisionMask; }
  std::add_const_t<std::remove_reference_t<RMergeList<RString>>> & Get() const { return self.m_CollisionMask; }
  void SetDefault() { self.m_CollisionMask = StormReflTypeInfo<MapPathfindingInfo>::GetDefault().m_CollisionMask; }
};

template <>
struct StormReflTypeInfo<MapPathfindingInfo>::field_data_static<5>
{
  using member_type = RBool; // RBool
  static constexpr auto GetName() { return "m_Valid"; }
  static constexpr auto GetType() { return "RBool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0131A59F; }
  static constexpr unsigned GetTypeNameHash() { return 0x50062D06; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &MapPathfindingInfo::m_Valid; }
};

template <typename Self>
struct StormReflTypeInfo<MapPathfindingInfo>::field_data<5, Self> : public StormReflTypeInfo<MapPathfindingInfo>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RBool> & Get() { return self.m_Valid; }
  std::add_const_t<std::remove_reference_t<RBool>> & Get() const { return self.m_Valid; }
  void SetDefault() { self.m_Valid = StormReflTypeInfo<MapPathfindingInfo>::GetDefault().m_Valid; }
};

template <>
struct StormReflTypeInfo<MapPathfindingInfo>::annotations<5>
{
  static constexpr int annotations_n = 1;
  template <int A> struct annoation { };
};

template <>
struct StormReflTypeInfo<MapPathfindingInfo>::annotations<5>::annoation<0>
{
  static constexpr const char * GetAnnotation() { return "noui"; }
  static constexpr uint32_t GetAnnotationHash() { return 0xDF10877E; }
};

template <>
struct StormReflTypeInfo<MapPathfindingInfo>::field_data_static<6>
{
  using member_type = ROpaque<MapPathfindingCalculatedInfo>; // ROpaque<MapPathfindingCalculatedInfo>
  static constexpr auto GetName() { return "m_CalculatedInfo"; }
  static constexpr auto GetType() { return "ROpaque<MapPathfindingCalculatedInfo>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDC57C505; }
  static constexpr unsigned GetTypeNameHash() { return 0x3AAC98AB; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &MapPathfindingInfo::m_CalculatedInfo; }
};

template <typename Self>
struct StormReflTypeInfo<MapPathfindingInfo>::field_data<6, Self> : public StormReflTypeInfo<MapPathfindingInfo>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, ROpaque<MapPathfindingCalculatedInfo>> & Get() { return self.m_CalculatedInfo; }
  std::add_const_t<std::remove_reference_t<ROpaque<MapPathfindingCalculatedInfo>>> & Get() const { return self.m_CalculatedInfo; }
  void SetDefault() { self.m_CalculatedInfo = StormReflTypeInfo<MapPathfindingInfo>::GetDefault().m_CalculatedInfo; }
};

template <>
struct StormReflTypeInfo<MapPathfindingInfo>::annotations<6>
{
  static constexpr int annotations_n = 1;
  template <int A> struct annoation { };
};

template <>
struct StormReflTypeInfo<MapPathfindingInfo>::annotations<6>::annoation<0>
{
  static constexpr const char * GetAnnotation() { return "noui"; }
  static constexpr uint32_t GetAnnotationHash() { return 0xDF10877E; }
};

template <>
struct StormReflTypeInfo<MapDef>
{
  using MyBase = void;
  static constexpr int fields_n = 10;
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
  using member_type = MapPropertiesInfo; // MapPropertiesInfo
  static constexpr auto GetName() { return "m_PropertiesInfo"; }
  static constexpr auto GetType() { return "MapPropertiesInfo"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2CFDF744; }
  static constexpr unsigned GetTypeNameHash() { return 0x3D3EA581; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &MapDef::m_PropertiesInfo; }
};

template <typename Self>
struct StormReflTypeInfo<MapDef>::field_data<0, Self> : public StormReflTypeInfo<MapDef>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, MapPropertiesInfo> & Get() { return self.m_PropertiesInfo; }
  std::add_const_t<std::remove_reference_t<MapPropertiesInfo>> & Get() const { return self.m_PropertiesInfo; }
  void SetDefault() { self.m_PropertiesInfo = StormReflTypeInfo<MapDef>::GetDefault().m_PropertiesInfo; }
};

template <>
struct StormReflTypeInfo<MapDef>::field_data_static<1>
{
  using member_type = MapPathfindingInfo; // MapPathfindingInfo
  static constexpr auto GetName() { return "m_PathfingindInfo"; }
  static constexpr auto GetType() { return "MapPathfindingInfo"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF4DE5BC7; }
  static constexpr unsigned GetTypeNameHash() { return 0xD6EED399; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &MapDef::m_PathfingindInfo; }
};

template <typename Self>
struct StormReflTypeInfo<MapDef>::field_data<1, Self> : public StormReflTypeInfo<MapDef>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, MapPathfindingInfo> & Get() { return self.m_PathfingindInfo; }
  std::add_const_t<std::remove_reference_t<MapPathfindingInfo>> & Get() const { return self.m_PathfingindInfo; }
  void SetDefault() { self.m_PathfingindInfo = StormReflTypeInfo<MapDef>::GetDefault().m_PathfingindInfo; }
};

template <>
struct StormReflTypeInfo<MapDef>::field_data_static<2>
{
  using member_type = RMergeList<MapManualTileLayer>; // RMergeList<MapManualTileLayer>
  static constexpr auto GetName() { return "m_ManualTileLayers"; }
  static constexpr auto GetType() { return "RMergeList<MapManualTileLayer>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x64A8921A; }
  static constexpr unsigned GetTypeNameHash() { return 0xBEE03213; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &MapDef::m_ManualTileLayers; }
};

template <typename Self>
struct StormReflTypeInfo<MapDef>::field_data<2, Self> : public StormReflTypeInfo<MapDef>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<MapManualTileLayer>> & Get() { return self.m_ManualTileLayers; }
  std::add_const_t<std::remove_reference_t<RMergeList<MapManualTileLayer>>> & Get() const { return self.m_ManualTileLayers; }
  void SetDefault() { self.m_ManualTileLayers = StormReflTypeInfo<MapDef>::GetDefault().m_ManualTileLayers; }
};

template <>
struct StormReflTypeInfo<MapDef>::field_data_static<3>
{
  using member_type = RMergeList<MapServerObjectLayer>; // RMergeList<MapServerObjectLayer>
  static constexpr auto GetName() { return "m_ServerObjectLayers"; }
  static constexpr auto GetType() { return "RMergeList<MapServerObjectLayer>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x50DB9B69; }
  static constexpr unsigned GetTypeNameHash() { return 0x27E07A3E; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &MapDef::m_ServerObjectLayers; }
};

template <typename Self>
struct StormReflTypeInfo<MapDef>::field_data<3, Self> : public StormReflTypeInfo<MapDef>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<MapServerObjectLayer>> & Get() { return self.m_ServerObjectLayers; }
  std::add_const_t<std::remove_reference_t<RMergeList<MapServerObjectLayer>>> & Get() const { return self.m_ServerObjectLayers; }
  void SetDefault() { self.m_ServerObjectLayers = StormReflTypeInfo<MapDef>::GetDefault().m_ServerObjectLayers; }
};

template <>
struct StormReflTypeInfo<MapDef>::field_data_static<4>
{
  using member_type = RMergeList<MapEntityLayer>; // RMergeList<MapEntityLayer>
  static constexpr auto GetName() { return "m_EntityLayers"; }
  static constexpr auto GetType() { return "RMergeList<MapEntityLayer>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x606A4865; }
  static constexpr unsigned GetTypeNameHash() { return 0x0F0562FD; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &MapDef::m_EntityLayers; }
};

template <typename Self>
struct StormReflTypeInfo<MapDef>::field_data<4, Self> : public StormReflTypeInfo<MapDef>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<MapEntityLayer>> & Get() { return self.m_EntityLayers; }
  std::add_const_t<std::remove_reference_t<RMergeList<MapEntityLayer>>> & Get() const { return self.m_EntityLayers; }
  void SetDefault() { self.m_EntityLayers = StormReflTypeInfo<MapDef>::GetDefault().m_EntityLayers; }
};

template <>
struct StormReflTypeInfo<MapDef>::field_data_static<5>
{
  using member_type = RMergeList<MapParalaxLayer>; // RMergeList<MapParalaxLayer>
  static constexpr auto GetName() { return "m_ParalaxLayers"; }
  static constexpr auto GetType() { return "RMergeList<MapParalaxLayer>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x131DDD15; }
  static constexpr unsigned GetTypeNameHash() { return 0xA01CA52C; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &MapDef::m_ParalaxLayers; }
};

template <typename Self>
struct StormReflTypeInfo<MapDef>::field_data<5, Self> : public StormReflTypeInfo<MapDef>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<MapParalaxLayer>> & Get() { return self.m_ParalaxLayers; }
  std::add_const_t<std::remove_reference_t<RMergeList<MapParalaxLayer>>> & Get() const { return self.m_ParalaxLayers; }
  void SetDefault() { self.m_ParalaxLayers = StormReflTypeInfo<MapDef>::GetDefault().m_ParalaxLayers; }
};

template <>
struct StormReflTypeInfo<MapDef>::field_data_static<6>
{
  using member_type = RMergeList<MapEffectLayer>; // RMergeList<MapEffectLayer>
  static constexpr auto GetName() { return "m_EffectLayers"; }
  static constexpr auto GetType() { return "RMergeList<MapEffectLayer>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x086F5213; }
  static constexpr unsigned GetTypeNameHash() { return 0x6700788B; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &MapDef::m_EffectLayers; }
};

template <typename Self>
struct StormReflTypeInfo<MapDef>::field_data<6, Self> : public StormReflTypeInfo<MapDef>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<MapEffectLayer>> & Get() { return self.m_EffectLayers; }
  std::add_const_t<std::remove_reference_t<RMergeList<MapEffectLayer>>> & Get() const { return self.m_EffectLayers; }
  void SetDefault() { self.m_EffectLayers = StormReflTypeInfo<MapDef>::GetDefault().m_EffectLayers; }
};

template <>
struct StormReflTypeInfo<MapDef>::field_data_static<7>
{
  using member_type = RMergeList<MapAnchor>; // RMergeList<MapAnchor>
  static constexpr auto GetName() { return "m_Anchors"; }
  static constexpr auto GetType() { return "RMergeList<MapAnchor>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA02FE64E; }
  static constexpr unsigned GetTypeNameHash() { return 0x5C53BF10; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &MapDef::m_Anchors; }
};

template <typename Self>
struct StormReflTypeInfo<MapDef>::field_data<7, Self> : public StormReflTypeInfo<MapDef>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<MapAnchor>> & Get() { return self.m_Anchors; }
  std::add_const_t<std::remove_reference_t<RMergeList<MapAnchor>>> & Get() const { return self.m_Anchors; }
  void SetDefault() { self.m_Anchors = StormReflTypeInfo<MapDef>::GetDefault().m_Anchors; }
};

template <>
struct StormReflTypeInfo<MapDef>::field_data_static<8>
{
  using member_type = RMergeList<MapPath>; // RMergeList<MapPath>
  static constexpr auto GetName() { return "m_Paths"; }
  static constexpr auto GetType() { return "RMergeList<MapPath>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x068C1671; }
  static constexpr unsigned GetTypeNameHash() { return 0x65F883E4; }
  static constexpr auto GetFieldIndex() { return 8; }
  static constexpr auto GetMemberPtr() { return &MapDef::m_Paths; }
};

template <typename Self>
struct StormReflTypeInfo<MapDef>::field_data<8, Self> : public StormReflTypeInfo<MapDef>::field_data_static<8>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<MapPath>> & Get() { return self.m_Paths; }
  std::add_const_t<std::remove_reference_t<RMergeList<MapPath>>> & Get() const { return self.m_Paths; }
  void SetDefault() { self.m_Paths = StormReflTypeInfo<MapDef>::GetDefault().m_Paths; }
};

template <>
struct StormReflTypeInfo<MapDef>::field_data_static<9>
{
  using member_type = RMergeList<MapVolume>; // RMergeList<MapVolume>
  static constexpr auto GetName() { return "m_Volumes"; }
  static constexpr auto GetType() { return "RMergeList<MapVolume>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xEF2EDFC0; }
  static constexpr unsigned GetTypeNameHash() { return 0x1352869E; }
  static constexpr auto GetFieldIndex() { return 9; }
  static constexpr auto GetMemberPtr() { return &MapDef::m_Volumes; }
};

template <typename Self>
struct StormReflTypeInfo<MapDef>::field_data<9, Self> : public StormReflTypeInfo<MapDef>::field_data_static<9>
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
    static const int types_n = 18;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct MapDef::type_info<0>
  {
    using type = ::MapPropertiesInfo;
  };

  template <>
  struct MapDef::type_info<1>
  {
    using type = ::MapManualTileLayer;
  };

  template <>
  struct MapDef::type_info<2>
  {
    using type = ::MapEntity;
  };

  template <>
  struct MapDef::type_info<3>
  {
    using type = ::MapEntityLayer;
  };

  template <>
  struct MapDef::type_info<4>
  {
    using type = ::MapServerObject;
  };

  template <>
  struct MapDef::type_info<5>
  {
    using type = ::MapServerObjectLayer;
  };

  template <>
  struct MapDef::type_info<6>
  {
    using type = ::MapParalaxLayerObject;
  };

  template <>
  struct MapDef::type_info<7>
  {
    using type = ::MapParalaxLayer;
  };

  template <>
  struct MapDef::type_info<8>
  {
    using type = ::MapEffectLayer;
  };

  template <>
  struct MapDef::type_info<9>
  {
    using type = ::MapAnchor;
  };

  template <>
  struct MapDef::type_info<10>
  {
    using type = ::MapPathPoint;
  };

  template <>
  struct MapDef::type_info<11>
  {
    using type = ::MapPath;
  };

  template <>
  struct MapDef::type_info<12>
  {
    using type = ::MapVolume;
  };

  template <>
  struct MapDef::type_info<13>
  {
    using type = ::MapPathfindingSurface;
  };

  template <>
  struct MapDef::type_info<14>
  {
    using type = ::MapPathfindingSurfaceConnection;
  };

  template <>
  struct MapDef::type_info<15>
  {
    using type = ::MapPathfindingCalculatedInfo;
  };

  template <>
  struct MapDef::type_info<16>
  {
    using type = ::MapPathfindingInfo;
  };

  template <>
  struct MapDef::type_info<17>
  {
    using type = ::MapDef;
  };

}

