#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "VisualEffectDef.refl.h"
#include "Runtime/UI/UITypes.refl.meta.h"


template <>
struct StormReflTypeInfo<VisualEffectDefInputVariable>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "VisualEffectDefInputVariable"; }
  static constexpr auto GetNameHash() { return 0xE6E02AA9; }
  static VisualEffectDefInputVariable & GetDefault() { static VisualEffectDefInputVariable def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<VisualEffectDefInputVariable *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const VisualEffectDefInputVariable *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<VisualEffectDefInputVariable *>(ptr);
    if(typeid(VisualEffectDefInputVariable).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const VisualEffectDefInputVariable *>(ptr);
    if(typeid(VisualEffectDefInputVariable).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<VisualEffectDefInputVariable>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_VariableName"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x75DF746E; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &VisualEffectDefInputVariable::m_VariableName; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectDefInputVariable>::field_data<0, Self> : public StormReflTypeInfo<VisualEffectDefInputVariable>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_VariableName; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_VariableName; }
  void SetDefault() { self.m_VariableName = StormReflTypeInfo<VisualEffectDefInputVariable>::GetDefault().m_VariableName; }
};

template <>
struct StormReflTypeInfo<VisualEffectDefEquation>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "VisualEffectDefEquation"; }
  static constexpr auto GetNameHash() { return 0xF9958751; }
  static VisualEffectDefEquation & GetDefault() { static VisualEffectDefEquation def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<VisualEffectDefEquation *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const VisualEffectDefEquation *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<VisualEffectDefEquation *>(ptr);
    if(typeid(VisualEffectDefEquation).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const VisualEffectDefEquation *>(ptr);
    if(typeid(VisualEffectDefEquation).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<VisualEffectDefEquation>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_VariableName"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x75DF746E; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &VisualEffectDefEquation::m_VariableName; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectDefEquation>::field_data<0, Self> : public StormReflTypeInfo<VisualEffectDefEquation>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_VariableName; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_VariableName; }
  void SetDefault() { self.m_VariableName = StormReflTypeInfo<VisualEffectDefEquation>::GetDefault().m_VariableName; }
};

template <>
struct StormReflTypeInfo<VisualEffectDefEquation>::field_data_static<1>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Equation"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x559340DB; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &VisualEffectDefEquation::m_Equation; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectDefEquation>::field_data<1, Self> : public StormReflTypeInfo<VisualEffectDefEquation>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Equation; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Equation; }
  void SetDefault() { self.m_Equation = StormReflTypeInfo<VisualEffectDefEquation>::GetDefault().m_Equation; }
};

template <>
struct StormReflTypeInfo<VisualEffectDefEmitterProperties>
{
  using MyBase = void;
  static constexpr int fields_n = 7;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "VisualEffectDefEmitterProperties"; }
  static constexpr auto GetNameHash() { return 0x7362FF01; }
  static VisualEffectDefEmitterProperties & GetDefault() { static VisualEffectDefEmitterProperties def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<VisualEffectDefEmitterProperties *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const VisualEffectDefEmitterProperties *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<VisualEffectDefEmitterProperties *>(ptr);
    if(typeid(VisualEffectDefEmitterProperties).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const VisualEffectDefEmitterProperties *>(ptr);
    if(typeid(VisualEffectDefEmitterProperties).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<VisualEffectDefEmitterProperties>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &VisualEffectDefEmitterProperties::m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectDefEmitterProperties>::field_data<0, Self> : public StormReflTypeInfo<VisualEffectDefEmitterProperties>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<VisualEffectDefEmitterProperties>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<VisualEffectDefEmitterProperties>::field_data_static<1>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Texture"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x179478A7; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &VisualEffectDefEmitterProperties::m_Texture; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectDefEmitterProperties>::field_data<1, Self> : public StormReflTypeInfo<VisualEffectDefEmitterProperties>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Texture; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Texture; }
  void SetDefault() { self.m_Texture = StormReflTypeInfo<VisualEffectDefEmitterProperties>::GetDefault().m_Texture; }
};

template <>
struct StormReflTypeInfo<VisualEffectDefEmitterProperties>::annotations<1>
{
  static constexpr int annotations_n = 1;
  template <int A> struct annoation { };
};

template <>
struct StormReflTypeInfo<VisualEffectDefEmitterProperties>::annotations<1>::annoation<0>
{
  static constexpr const char * GetAnnotation() { return "file: image"; }
  static constexpr uint32_t GetAnnotationHash() { return 0xD4E8122A; }
};

template <>
struct StormReflTypeInfo<VisualEffectDefEmitterProperties>::field_data_static<2>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_PrespawnParticles"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA801CC5E; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &VisualEffectDefEmitterProperties::m_PrespawnParticles; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectDefEmitterProperties>::field_data<2, Self> : public StormReflTypeInfo<VisualEffectDefEmitterProperties>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_PrespawnParticles; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_PrespawnParticles; }
  void SetDefault() { self.m_PrespawnParticles = StormReflTypeInfo<VisualEffectDefEmitterProperties>::GetDefault().m_PrespawnParticles; }
};

template <>
struct StormReflTypeInfo<VisualEffectDefEmitterProperties>::field_data_static<3>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_UpdateDelay"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1F4D8FFF; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &VisualEffectDefEmitterProperties::m_UpdateDelay; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectDefEmitterProperties>::field_data<3, Self> : public StormReflTypeInfo<VisualEffectDefEmitterProperties>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_UpdateDelay; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_UpdateDelay; }
  void SetDefault() { self.m_UpdateDelay = StormReflTypeInfo<VisualEffectDefEmitterProperties>::GetDefault().m_UpdateDelay; }
};

template <>
struct StormReflTypeInfo<VisualEffectDefEmitterProperties>::field_data_static<4>
{
  using member_type = RBool; // RBool
  static constexpr auto GetName() { return "m_Additive"; }
  static constexpr auto GetType() { return "RBool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x10171727; }
  static constexpr unsigned GetTypeNameHash() { return 0x50062D06; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &VisualEffectDefEmitterProperties::m_Additive; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectDefEmitterProperties>::field_data<4, Self> : public StormReflTypeInfo<VisualEffectDefEmitterProperties>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RBool> & Get() { return self.m_Additive; }
  std::add_const_t<std::remove_reference_t<RBool>> & Get() const { return self.m_Additive; }
  void SetDefault() { self.m_Additive = StormReflTypeInfo<VisualEffectDefEmitterProperties>::GetDefault().m_Additive; }
};

template <>
struct StormReflTypeInfo<VisualEffectDefEmitterProperties>::field_data_static<5>
{
  using member_type = RBool; // RBool
  static constexpr auto GetName() { return "m_LinearFilter"; }
  static constexpr auto GetType() { return "RBool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAD505CBA; }
  static constexpr unsigned GetTypeNameHash() { return 0x50062D06; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &VisualEffectDefEmitterProperties::m_LinearFilter; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectDefEmitterProperties>::field_data<5, Self> : public StormReflTypeInfo<VisualEffectDefEmitterProperties>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RBool> & Get() { return self.m_LinearFilter; }
  std::add_const_t<std::remove_reference_t<RBool>> & Get() const { return self.m_LinearFilter; }
  void SetDefault() { self.m_LinearFilter = StormReflTypeInfo<VisualEffectDefEmitterProperties>::GetDefault().m_LinearFilter; }
};

template <>
struct StormReflTypeInfo<VisualEffectDefEmitterProperties>::field_data_static<6>
{
  using member_type = RBool; // RBool
  static constexpr auto GetName() { return "m_Trail"; }
  static constexpr auto GetType() { return "RBool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3F5E15EF; }
  static constexpr unsigned GetTypeNameHash() { return 0x50062D06; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &VisualEffectDefEmitterProperties::m_Trail; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectDefEmitterProperties>::field_data<6, Self> : public StormReflTypeInfo<VisualEffectDefEmitterProperties>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RBool> & Get() { return self.m_Trail; }
  std::add_const_t<std::remove_reference_t<RBool>> & Get() const { return self.m_Trail; }
  void SetDefault() { self.m_Trail = StormReflTypeInfo<VisualEffectDefEmitterProperties>::GetDefault().m_Trail; }
};

template <>
struct StormReflTypeInfo<VisualEffectDefEmitter>
{
  using MyBase = void;
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "VisualEffectDefEmitter"; }
  static constexpr auto GetNameHash() { return 0x5A4272CF; }
  static VisualEffectDefEmitter & GetDefault() { static VisualEffectDefEmitter def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<VisualEffectDefEmitter *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const VisualEffectDefEmitter *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<VisualEffectDefEmitter *>(ptr);
    if(typeid(VisualEffectDefEmitter).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const VisualEffectDefEmitter *>(ptr);
    if(typeid(VisualEffectDefEmitter).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<VisualEffectDefEmitter>::field_data_static<0>
{
  using member_type = VisualEffectDefEmitterProperties; // VisualEffectDefEmitterProperties
  static constexpr auto GetName() { return "m_Properties"; }
  static constexpr auto GetType() { return "VisualEffectDefEmitterProperties"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0D7AD80A; }
  static constexpr unsigned GetTypeNameHash() { return 0x7362FF01; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &VisualEffectDefEmitter::m_Properties; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectDefEmitter>::field_data<0, Self> : public StormReflTypeInfo<VisualEffectDefEmitter>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, VisualEffectDefEmitterProperties> & Get() { return self.m_Properties; }
  std::add_const_t<std::remove_reference_t<VisualEffectDefEmitterProperties>> & Get() const { return self.m_Properties; }
  void SetDefault() { self.m_Properties = StormReflTypeInfo<VisualEffectDefEmitter>::GetDefault().m_Properties; }
};

template <>
struct StormReflTypeInfo<VisualEffectDefEmitter>::field_data_static<1>
{
  using member_type = RMap<uint32_t, VisualEffectDefEquation>; // RMap<unsigned int, VisualEffectDefEquation>
  static constexpr auto GetName() { return "m_EmitterEquations"; }
  static constexpr auto GetType() { return "RMap<unsigned int, VisualEffectDefEquation>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0BCE4887; }
  static constexpr unsigned GetTypeNameHash() { return 0x1FFFEAB5; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &VisualEffectDefEmitter::m_EmitterEquations; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectDefEmitter>::field_data<1, Self> : public StormReflTypeInfo<VisualEffectDefEmitter>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMap<uint32_t, VisualEffectDefEquation>> & Get() { return self.m_EmitterEquations; }
  std::add_const_t<std::remove_reference_t<RMap<uint32_t, VisualEffectDefEquation>>> & Get() const { return self.m_EmitterEquations; }
  void SetDefault() { self.m_EmitterEquations = StormReflTypeInfo<VisualEffectDefEmitter>::GetDefault().m_EmitterEquations; }
};

template <>
struct StormReflTypeInfo<VisualEffectDefEmitter>::field_data_static<2>
{
  using member_type = RMap<uint32_t, VisualEffectDefEquation>; // RMap<unsigned int, VisualEffectDefEquation>
  static constexpr auto GetName() { return "m_SpawnEquations"; }
  static constexpr auto GetType() { return "RMap<unsigned int, VisualEffectDefEquation>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFE7D8233; }
  static constexpr unsigned GetTypeNameHash() { return 0x1FFFEAB5; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &VisualEffectDefEmitter::m_SpawnEquations; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectDefEmitter>::field_data<2, Self> : public StormReflTypeInfo<VisualEffectDefEmitter>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMap<uint32_t, VisualEffectDefEquation>> & Get() { return self.m_SpawnEquations; }
  std::add_const_t<std::remove_reference_t<RMap<uint32_t, VisualEffectDefEquation>>> & Get() const { return self.m_SpawnEquations; }
  void SetDefault() { self.m_SpawnEquations = StormReflTypeInfo<VisualEffectDefEmitter>::GetDefault().m_SpawnEquations; }
};

template <>
struct StormReflTypeInfo<VisualEffectDefEmitter>::field_data_static<3>
{
  using member_type = RMap<uint32_t, VisualEffectDefEquation>; // RMap<unsigned int, VisualEffectDefEquation>
  static constexpr auto GetName() { return "m_ParticleEquations"; }
  static constexpr auto GetType() { return "RMap<unsigned int, VisualEffectDefEquation>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6DF1B904; }
  static constexpr unsigned GetTypeNameHash() { return 0x1FFFEAB5; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &VisualEffectDefEmitter::m_ParticleEquations; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectDefEmitter>::field_data<3, Self> : public StormReflTypeInfo<VisualEffectDefEmitter>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMap<uint32_t, VisualEffectDefEquation>> & Get() { return self.m_ParticleEquations; }
  std::add_const_t<std::remove_reference_t<RMap<uint32_t, VisualEffectDefEquation>>> & Get() const { return self.m_ParticleEquations; }
  void SetDefault() { self.m_ParticleEquations = StormReflTypeInfo<VisualEffectDefEmitter>::GetDefault().m_ParticleEquations; }
};

template <>
struct StormReflTypeInfo<VisualEffectDef>
{
  using MyBase = void;
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "VisualEffectDef"; }
  static constexpr auto GetNameHash() { return 0x7BB44461; }
  static VisualEffectDef & GetDefault() { static VisualEffectDef def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<VisualEffectDef *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const VisualEffectDef *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<VisualEffectDef *>(ptr);
    if(typeid(VisualEffectDef).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const VisualEffectDef *>(ptr);
    if(typeid(VisualEffectDef).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<VisualEffectDef>::field_data_static<0>
{
  using member_type = RMergeList<VisualEffectDefInputVariable>; // RMergeList<VisualEffectDefInputVariable>
  static constexpr auto GetName() { return "m_Inputs"; }
  static constexpr auto GetType() { return "RMergeList<VisualEffectDefInputVariable>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x4E5EF786; }
  static constexpr unsigned GetTypeNameHash() { return 0x8CCF59A8; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &VisualEffectDef::m_Inputs; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectDef>::field_data<0, Self> : public StormReflTypeInfo<VisualEffectDef>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<VisualEffectDefInputVariable>> & Get() { return self.m_Inputs; }
  std::add_const_t<std::remove_reference_t<RMergeList<VisualEffectDefInputVariable>>> & Get() const { return self.m_Inputs; }
  void SetDefault() { self.m_Inputs = StormReflTypeInfo<VisualEffectDef>::GetDefault().m_Inputs; }
};

template <>
struct StormReflTypeInfo<VisualEffectDef>::field_data_static<1>
{
  using member_type = RMergeList<VisualEffectDefEmitter>; // RMergeList<VisualEffectDefEmitter>
  static constexpr auto GetName() { return "m_Emitters"; }
  static constexpr auto GetType() { return "RMergeList<VisualEffectDefEmitter>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xBC8995D2; }
  static constexpr unsigned GetTypeNameHash() { return 0x38BD84A3; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &VisualEffectDef::m_Emitters; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectDef>::field_data<1, Self> : public StormReflTypeInfo<VisualEffectDef>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<VisualEffectDefEmitter>> & Get() { return self.m_Emitters; }
  std::add_const_t<std::remove_reference_t<RMergeList<VisualEffectDefEmitter>>> & Get() const { return self.m_Emitters; }
  void SetDefault() { self.m_Emitters = StormReflTypeInfo<VisualEffectDef>::GetDefault().m_Emitters; }
};

template <>
struct StormReflTypeInfo<VisualEffectDef>::field_data_static<2>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_UpdateBoundsX"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2D7E5E58; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &VisualEffectDef::m_UpdateBoundsX; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectDef>::field_data<2, Self> : public StormReflTypeInfo<VisualEffectDef>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_UpdateBoundsX; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_UpdateBoundsX; }
  void SetDefault() { self.m_UpdateBoundsX = StormReflTypeInfo<VisualEffectDef>::GetDefault().m_UpdateBoundsX; }
};

template <>
struct StormReflTypeInfo<VisualEffectDef>::field_data_static<3>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_UpdateBoundsY"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5A796ECE; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &VisualEffectDef::m_UpdateBoundsY; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectDef>::field_data<3, Self> : public StormReflTypeInfo<VisualEffectDef>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_UpdateBoundsY; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_UpdateBoundsY; }
  void SetDefault() { self.m_UpdateBoundsY = StormReflTypeInfo<VisualEffectDef>::GetDefault().m_UpdateBoundsY; }
};

namespace StormReflFileInfo
{
  struct VisualEffectDef
  {
    static const int types_n = 5;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct VisualEffectDef::type_info<0>
  {
    using type = ::VisualEffectDefInputVariable;
  };

  template <>
  struct VisualEffectDef::type_info<1>
  {
    using type = ::VisualEffectDefEquation;
  };

  template <>
  struct VisualEffectDef::type_info<2>
  {
    using type = ::VisualEffectDefEmitterProperties;
  };

  template <>
  struct VisualEffectDef::type_info<3>
  {
    using type = ::VisualEffectDefEmitter;
  };

  template <>
  struct VisualEffectDef::type_info<4>
  {
    using type = ::VisualEffectDef;
  };

}

