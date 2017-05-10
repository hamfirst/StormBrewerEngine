#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "MapDef.refl.h"
#include "Foundation/BasicTypes/BasicTypes.refl.meta.h"
#include "Runtime/Entity/EntityDef.refl.meta.h"
#include "Runtime/Path/PathDef.refl.meta.h"
#include "Runtime/Volume/VolumeDef.refl.meta.h"


template <>
struct StormReflTypeInfo<MapManualTileLayer>
{
  using MyBase = void;
  static constexpr int fields_n = 5;
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
  static constexpr int fields_n = 7;
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
  static constexpr auto GetName() { return "m_ParalaxX"; }
  static constexpr auto GetType() { return "RNumber<float>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x4A94EC25; }
  static constexpr unsigned GetTypeNameHash() { return 0x17411E4A; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &MapParalaxLayer::m_ParalaxX; }
};

template <typename Self>
struct StormReflTypeInfo<MapParalaxLayer>::field_data<5, Self> : public StormReflTypeInfo<MapParalaxLayer>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RFloat> & Get() { return self.m_ParalaxX; }
  std::add_const_t<std::remove_reference_t<RFloat>> & Get() const { return self.m_ParalaxX; }
  void SetDefault() { self.m_ParalaxX = StormReflTypeInfo<MapParalaxLayer>::GetDefault().m_ParalaxX; }
};

template <>
struct StormReflTypeInfo<MapParalaxLayer>::field_data_static<6>
{
  using member_type = RFloat; // RNumber<float>
  static constexpr auto GetName() { return "m_ParalaxY"; }
  static constexpr auto GetType() { return "RNumber<float>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3D93DCB3; }
  static constexpr unsigned GetTypeNameHash() { return 0x17411E4A; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &MapParalaxLayer::m_ParalaxY; }
};

template <typename Self>
struct StormReflTypeInfo<MapParalaxLayer>::field_data<6, Self> : public StormReflTypeInfo<MapParalaxLayer>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RFloat> & Get() { return self.m_ParalaxY; }
  std::add_const_t<std::remove_reference_t<RFloat>> & Get() const { return self.m_ParalaxY; }
  void SetDefault() { self.m_ParalaxY = StormReflTypeInfo<MapParalaxLayer>::GetDefault().m_ParalaxY; }
};

template <>
struct StormReflTypeInfo<MapPath>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
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
  using member_type = ROpaque<std::vector<Vector2> >; // ROpaque<std::vector<Vector2, std::allocator<Vector2> > >
  static constexpr auto GetName() { return "m_Points"; }
  static constexpr auto GetType() { return "ROpaque<std::vector<Vector2, std::allocator<Vector2> > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6A85D9E1; }
  static constexpr unsigned GetTypeNameHash() { return 0x83D46565; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &MapPath::m_Points; }
};

template <typename Self>
struct StormReflTypeInfo<MapPath>::field_data<0, Self> : public StormReflTypeInfo<MapPath>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, ROpaque<std::vector<Vector2> >> & Get() { return self.m_Points; }
  std::add_const_t<std::remove_reference_t<ROpaque<std::vector<Vector2> >>> & Get() const { return self.m_Points; }
  void SetDefault() { self.m_Points = StormReflTypeInfo<MapPath>::GetDefault().m_Points; }
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
struct StormReflTypeInfo<MapVolume>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
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
  using member_type = ROpaque<Box>; // ROpaque<Box>
  static constexpr auto GetName() { return "m_Volume"; }
  static constexpr auto GetType() { return "ROpaque<Box>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF4A59A16; }
  static constexpr unsigned GetTypeNameHash() { return 0xE527A8B8; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &MapVolume::m_Volume; }
};

template <typename Self>
struct StormReflTypeInfo<MapVolume>::field_data<0, Self> : public StormReflTypeInfo<MapVolume>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, ROpaque<Box>> & Get() { return self.m_Volume; }
  std::add_const_t<std::remove_reference_t<ROpaque<Box>>> & Get() const { return self.m_Volume; }
  void SetDefault() { self.m_Volume = StormReflTypeInfo<MapVolume>::GetDefault().m_Volume; }
};

template <>
struct StormReflTypeInfo<MapVolume>::field_data_static<1>
{
  using member_type = RPolymorphic<PathDataBase, PathTypeDatabase, PathDataTypeInfo>; // RPolymorphic<PathDataBase, PathTypeDatabase, PathDataTypeInfo>
  static constexpr auto GetName() { return "m_VolumeData"; }
  static constexpr auto GetType() { return "RPolymorphic<PathDataBase, PathTypeDatabase, PathDataTypeInfo>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE1971791; }
  static constexpr unsigned GetTypeNameHash() { return 0xA5143125; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &MapVolume::m_VolumeData; }
};

template <typename Self>
struct StormReflTypeInfo<MapVolume>::field_data<1, Self> : public StormReflTypeInfo<MapVolume>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RPolymorphic<PathDataBase, PathTypeDatabase, PathDataTypeInfo>> & Get() { return self.m_VolumeData; }
  std::add_const_t<std::remove_reference_t<RPolymorphic<PathDataBase, PathTypeDatabase, PathDataTypeInfo>>> & Get() const { return self.m_VolumeData; }
  void SetDefault() { self.m_VolumeData = StormReflTypeInfo<MapVolume>::GetDefault().m_VolumeData; }
};

template <>
struct StormReflTypeInfo<MapDef>
{
  using MyBase = void;
  static constexpr int fields_n = 5;
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
  using member_type = RMergeList<MapPath>; // RMergeList<MapPath>
  static constexpr auto GetName() { return "m_Paths"; }
  static constexpr auto GetType() { return "RMergeList<MapPath>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x068C1671; }
  static constexpr unsigned GetTypeNameHash() { return 0x65F883E4; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &MapDef::m_Paths; }
};

template <typename Self>
struct StormReflTypeInfo<MapDef>::field_data<3, Self> : public StormReflTypeInfo<MapDef>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<MapPath>> & Get() { return self.m_Paths; }
  std::add_const_t<std::remove_reference_t<RMergeList<MapPath>>> & Get() const { return self.m_Paths; }
  void SetDefault() { self.m_Paths = StormReflTypeInfo<MapDef>::GetDefault().m_Paths; }
};

template <>
struct StormReflTypeInfo<MapDef>::field_data_static<4>
{
  using member_type = RMergeList<MapVolume>; // RMergeList<MapVolume>
  static constexpr auto GetName() { return "m_Volumes"; }
  static constexpr auto GetType() { return "RMergeList<MapVolume>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xEF2EDFC0; }
  static constexpr unsigned GetTypeNameHash() { return 0x1352869E; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &MapDef::m_Volumes; }
};

template <typename Self>
struct StormReflTypeInfo<MapDef>::field_data<4, Self> : public StormReflTypeInfo<MapDef>::field_data_static<4>
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
    static const int types_n = 7;
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
    using type = ::MapPath;
  };

  template <>
  struct MapDef::type_info<5>
  {
    using type = ::MapVolume;
  };

  template <>
  struct MapDef::type_info<6>
  {
    using type = ::MapDef;
  };

}

