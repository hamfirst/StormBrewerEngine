#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "SteamServerMessages.refl.h"


template <>
struct StormReflTypeInfo<SteamValidationResponseParams>
{
  using MyBase = void;
  static constexpr int fields_n = 5;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "SteamValidationResponseParams"; }
  static constexpr auto GetNameHash() { return 0xCC2369E4; }
<<<<<<< HEAD
  static SteamValidationResponseParams & GetDefault() { static SteamValidationResponseParams def; return def; }
=======
  static constexpr bool HasDefault() { return true; }
  static SteamValidationResponseParams & GetDefault() { static SteamValidationResponseParams def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<SteamValidationResponseParams *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const SteamValidationResponseParams *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<SteamValidationResponseParams *>(ptr);
    if(typeid(SteamValidationResponseParams).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const SteamValidationResponseParams *>(ptr);
    if(typeid(SteamValidationResponseParams).hash_code() == type_id_hash) return c;
    return nullptr;
  }

>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <>
struct StormReflTypeInfo<SteamValidationResponseParams>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "result"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x136AC113; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SteamValidationResponseParams::result; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SteamValidationResponseParams::result; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SteamValidationResponseParams *>(obj); return &ptr->result; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SteamValidationResponseParams *>(obj); return &ptr->result; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<SteamValidationResponseParams>::field_data<0, Self> : public StormReflTypeInfo<SteamValidationResponseParams>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.result; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.result; }
  void SetDefault() { self.result = StormReflTypeInfo<SteamValidationResponseParams>::GetDefault().result; }
};

template <>
struct StormReflTypeInfo<SteamValidationResponseParams>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "steamid"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xBCF81F98; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &SteamValidationResponseParams::steamid; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &SteamValidationResponseParams::steamid; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SteamValidationResponseParams *>(obj); return &ptr->steamid; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SteamValidationResponseParams *>(obj); return &ptr->steamid; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<SteamValidationResponseParams>::field_data<1, Self> : public StormReflTypeInfo<SteamValidationResponseParams>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.steamid; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.steamid; }
  void SetDefault() { self.steamid = StormReflTypeInfo<SteamValidationResponseParams>::GetDefault().steamid; }
};

template <>
struct StormReflTypeInfo<SteamValidationResponseParams>::field_data_static<2>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "ownersteamid"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE031D445; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &SteamValidationResponseParams::ownersteamid; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &SteamValidationResponseParams::ownersteamid; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SteamValidationResponseParams *>(obj); return &ptr->ownersteamid; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SteamValidationResponseParams *>(obj); return &ptr->ownersteamid; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<SteamValidationResponseParams>::field_data<2, Self> : public StormReflTypeInfo<SteamValidationResponseParams>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.ownersteamid; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.ownersteamid; }
  void SetDefault() { self.ownersteamid = StormReflTypeInfo<SteamValidationResponseParams>::GetDefault().ownersteamid; }
};

template <>
struct StormReflTypeInfo<SteamValidationResponseParams>::field_data_static<3>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "vacbanned"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE924F4B9; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &SteamValidationResponseParams::vacbanned; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &SteamValidationResponseParams::vacbanned; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SteamValidationResponseParams *>(obj); return &ptr->vacbanned; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SteamValidationResponseParams *>(obj); return &ptr->vacbanned; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<SteamValidationResponseParams>::field_data<3, Self> : public StormReflTypeInfo<SteamValidationResponseParams>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.vacbanned; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.vacbanned; }
  void SetDefault() { self.vacbanned = StormReflTypeInfo<SteamValidationResponseParams>::GetDefault().vacbanned; }
};

template <>
struct StormReflTypeInfo<SteamValidationResponseParams>::field_data_static<4>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "publisherbanned"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE49F3CAD; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &SteamValidationResponseParams::publisherbanned; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &SteamValidationResponseParams::publisherbanned; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SteamValidationResponseParams *>(obj); return &ptr->publisherbanned; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SteamValidationResponseParams *>(obj); return &ptr->publisherbanned; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<SteamValidationResponseParams>::field_data<4, Self> : public StormReflTypeInfo<SteamValidationResponseParams>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.publisherbanned; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.publisherbanned; }
  void SetDefault() { self.publisherbanned = StormReflTypeInfo<SteamValidationResponseParams>::GetDefault().publisherbanned; }
};

template <>
struct StormReflTypeInfo<SteamValidationResponse>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "SteamValidationResponse"; }
  static constexpr auto GetNameHash() { return 0xD72966B7; }
<<<<<<< HEAD
  static SteamValidationResponse & GetDefault() { static SteamValidationResponse def; return def; }
=======
  static constexpr bool HasDefault() { return true; }
  static SteamValidationResponse & GetDefault() { static SteamValidationResponse def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<SteamValidationResponse *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const SteamValidationResponse *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<SteamValidationResponse *>(ptr);
    if(typeid(SteamValidationResponse).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const SteamValidationResponse *>(ptr);
    if(typeid(SteamValidationResponse).hash_code() == type_id_hash) return c;
    return nullptr;
  }

>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <>
struct StormReflTypeInfo<SteamValidationResponse>::field_data_static<0>
{
  using member_type = SteamValidationResponseParams; // SteamValidationResponseParams
  static constexpr auto GetName() { return "params"; }
  static constexpr auto GetType() { return "SteamValidationResponseParams"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8FCE0EF3; }
  static constexpr unsigned GetTypeNameHash() { return 0xCC2369E4; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SteamValidationResponse::params; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SteamValidationResponse::params; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SteamValidationResponse *>(obj); return &ptr->params; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SteamValidationResponse *>(obj); return &ptr->params; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<SteamValidationResponse>::field_data<0, Self> : public StormReflTypeInfo<SteamValidationResponse>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, SteamValidationResponseParams> & Get() { return self.params; }
  std::add_const_t<std::remove_reference_t<SteamValidationResponseParams>> & Get() const { return self.params; }
  void SetDefault() { self.params = StormReflTypeInfo<SteamValidationResponse>::GetDefault().params; }
};

template <>
struct StormReflTypeInfo<SteamValidation>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "SteamValidation"; }
  static constexpr auto GetNameHash() { return 0x3AE4132F; }
<<<<<<< HEAD
  static SteamValidation & GetDefault() { static SteamValidation def; return def; }
=======
  static constexpr bool HasDefault() { return true; }
  static SteamValidation & GetDefault() { static SteamValidation def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<SteamValidation *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const SteamValidation *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<SteamValidation *>(ptr);
    if(typeid(SteamValidation).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const SteamValidation *>(ptr);
    if(typeid(SteamValidation).hash_code() == type_id_hash) return c;
    return nullptr;
  }

>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <>
struct StormReflTypeInfo<SteamValidation>::field_data_static<0>
{
  using member_type = SteamValidationResponse; // SteamValidationResponse
  static constexpr auto GetName() { return "response"; }
  static constexpr auto GetType() { return "SteamValidationResponse"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3E7B0BFB; }
  static constexpr unsigned GetTypeNameHash() { return 0xD72966B7; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SteamValidation::response; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SteamValidation::response; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SteamValidation *>(obj); return &ptr->response; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SteamValidation *>(obj); return &ptr->response; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<SteamValidation>::field_data<0, Self> : public StormReflTypeInfo<SteamValidation>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, SteamValidationResponse> & Get() { return self.response; }
  std::add_const_t<std::remove_reference_t<SteamValidationResponse>> & Get() const { return self.response; }
  void SetDefault() { self.response = StormReflTypeInfo<SteamValidation>::GetDefault().response; }
};

template <>
struct StormReflTypeInfo<SteamOwnershipResponseParams>
{
  using MyBase = void;
  static constexpr int fields_n = 5;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "SteamOwnershipResponseParams"; }
  static constexpr auto GetNameHash() { return 0x00726BB0; }
<<<<<<< HEAD
  static SteamOwnershipResponseParams & GetDefault() { static SteamOwnershipResponseParams def; return def; }
=======
  static constexpr bool HasDefault() { return true; }
  static SteamOwnershipResponseParams & GetDefault() { static SteamOwnershipResponseParams def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<SteamOwnershipResponseParams *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const SteamOwnershipResponseParams *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<SteamOwnershipResponseParams *>(ptr);
    if(typeid(SteamOwnershipResponseParams).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const SteamOwnershipResponseParams *>(ptr);
    if(typeid(SteamOwnershipResponseParams).hash_code() == type_id_hash) return c;
    return nullptr;
  }

>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <>
struct StormReflTypeInfo<SteamOwnershipResponseParams>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "appid"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA35E1483; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SteamOwnershipResponseParams::appid; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SteamOwnershipResponseParams::appid; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SteamOwnershipResponseParams *>(obj); return &ptr->appid; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SteamOwnershipResponseParams *>(obj); return &ptr->appid; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<SteamOwnershipResponseParams>::field_data<0, Self> : public StormReflTypeInfo<SteamOwnershipResponseParams>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.appid; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.appid; }
  void SetDefault() { self.appid = StormReflTypeInfo<SteamOwnershipResponseParams>::GetDefault().appid; }
};

template <>
struct StormReflTypeInfo<SteamOwnershipResponseParams>::field_data_static<1>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "ownsapp"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x9F12B188; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &SteamOwnershipResponseParams::ownsapp; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &SteamOwnershipResponseParams::ownsapp; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SteamOwnershipResponseParams *>(obj); return &ptr->ownsapp; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SteamOwnershipResponseParams *>(obj); return &ptr->ownsapp; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<SteamOwnershipResponseParams>::field_data<1, Self> : public StormReflTypeInfo<SteamOwnershipResponseParams>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.ownsapp; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.ownsapp; }
  void SetDefault() { self.ownsapp = StormReflTypeInfo<SteamOwnershipResponseParams>::GetDefault().ownsapp; }
};

template <>
struct StormReflTypeInfo<SteamOwnershipResponseParams>::field_data_static<2>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "permanent"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDC9D8028; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &SteamOwnershipResponseParams::permanent; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &SteamOwnershipResponseParams::permanent; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SteamOwnershipResponseParams *>(obj); return &ptr->permanent; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SteamOwnershipResponseParams *>(obj); return &ptr->permanent; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<SteamOwnershipResponseParams>::field_data<2, Self> : public StormReflTypeInfo<SteamOwnershipResponseParams>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.permanent; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.permanent; }
  void SetDefault() { self.permanent = StormReflTypeInfo<SteamOwnershipResponseParams>::GetDefault().permanent; }
};

template <>
struct StormReflTypeInfo<SteamOwnershipResponseParams>::field_data_static<3>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "timestamp"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA5D6E63E; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &SteamOwnershipResponseParams::timestamp; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &SteamOwnershipResponseParams::timestamp; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SteamOwnershipResponseParams *>(obj); return &ptr->timestamp; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SteamOwnershipResponseParams *>(obj); return &ptr->timestamp; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<SteamOwnershipResponseParams>::field_data<3, Self> : public StormReflTypeInfo<SteamOwnershipResponseParams>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.timestamp; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.timestamp; }
  void SetDefault() { self.timestamp = StormReflTypeInfo<SteamOwnershipResponseParams>::GetDefault().timestamp; }
};

template <>
struct StormReflTypeInfo<SteamOwnershipResponseParams>::field_data_static<4>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "ownersteamid"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE031D445; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &SteamOwnershipResponseParams::ownersteamid; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &SteamOwnershipResponseParams::ownersteamid; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SteamOwnershipResponseParams *>(obj); return &ptr->ownersteamid; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SteamOwnershipResponseParams *>(obj); return &ptr->ownersteamid; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<SteamOwnershipResponseParams>::field_data<4, Self> : public StormReflTypeInfo<SteamOwnershipResponseParams>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.ownersteamid; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.ownersteamid; }
  void SetDefault() { self.ownersteamid = StormReflTypeInfo<SteamOwnershipResponseParams>::GetDefault().ownersteamid; }
};

template <>
struct StormReflTypeInfo<SteamOwnershipResponse>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "SteamOwnershipResponse"; }
  static constexpr auto GetNameHash() { return 0x66212007; }
<<<<<<< HEAD
  static SteamOwnershipResponse & GetDefault() { static SteamOwnershipResponse def; return def; }
=======
  static constexpr bool HasDefault() { return true; }
  static SteamOwnershipResponse & GetDefault() { static SteamOwnershipResponse def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<SteamOwnershipResponse *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const SteamOwnershipResponse *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<SteamOwnershipResponse *>(ptr);
    if(typeid(SteamOwnershipResponse).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const SteamOwnershipResponse *>(ptr);
    if(typeid(SteamOwnershipResponse).hash_code() == type_id_hash) return c;
    return nullptr;
  }

>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <>
struct StormReflTypeInfo<SteamOwnershipResponse>::field_data_static<0>
{
  using member_type = std::vector<SteamOwnershipResponseParams>; // std::vector<SteamOwnershipResponseParams, std::allocator<SteamOwnershipResponseParams> >
  static constexpr auto GetName() { return "apps"; }
  static constexpr auto GetType() { return "std::vector<SteamOwnershipResponseParams, std::allocator<SteamOwnershipResponseParams> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x101C7E5A; }
  static constexpr unsigned GetTypeNameHash() { return 0x6B4137CF; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SteamOwnershipResponse::apps; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SteamOwnershipResponse::apps; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SteamOwnershipResponse *>(obj); return &ptr->apps; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SteamOwnershipResponse *>(obj); return &ptr->apps; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<SteamOwnershipResponse>::field_data<0, Self> : public StormReflTypeInfo<SteamOwnershipResponse>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<SteamOwnershipResponseParams>> & Get() { return self.apps; }
  std::add_const_t<std::remove_reference_t<std::vector<SteamOwnershipResponseParams>>> & Get() const { return self.apps; }
  void SetDefault() { self.apps = StormReflTypeInfo<SteamOwnershipResponse>::GetDefault().apps; }
};

template <>
struct StormReflTypeInfo<SteamOwnership>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "SteamOwnership"; }
  static constexpr auto GetNameHash() { return 0x8946262A; }
<<<<<<< HEAD
  static SteamOwnership & GetDefault() { static SteamOwnership def; return def; }
=======
  static constexpr bool HasDefault() { return true; }
  static SteamOwnership & GetDefault() { static SteamOwnership def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<SteamOwnership *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const SteamOwnership *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<SteamOwnership *>(ptr);
    if(typeid(SteamOwnership).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const SteamOwnership *>(ptr);
    if(typeid(SteamOwnership).hash_code() == type_id_hash) return c;
    return nullptr;
  }

>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <>
struct StormReflTypeInfo<SteamOwnership>::field_data_static<0>
{
  using member_type = SteamOwnershipResponse; // SteamOwnershipResponse
  static constexpr auto GetName() { return "appownership"; }
  static constexpr auto GetType() { return "SteamOwnershipResponse"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3ED0C959; }
  static constexpr unsigned GetTypeNameHash() { return 0x66212007; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SteamOwnership::appownership; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SteamOwnership::appownership; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SteamOwnership *>(obj); return &ptr->appownership; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SteamOwnership *>(obj); return &ptr->appownership; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<SteamOwnership>::field_data<0, Self> : public StormReflTypeInfo<SteamOwnership>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, SteamOwnershipResponse> & Get() { return self.appownership; }
  std::add_const_t<std::remove_reference_t<SteamOwnershipResponse>> & Get() const { return self.appownership; }
  void SetDefault() { self.appownership = StormReflTypeInfo<SteamOwnership>::GetDefault().appownership; }
};

template <>
struct StormReflTypeInfo<SteamTxnUserInfoResponseParams>
{
  using MyBase = void;
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "SteamTxnUserInfoResponseParams"; }
  static constexpr auto GetNameHash() { return 0x54CE31D1; }
<<<<<<< HEAD
  static SteamTxnUserInfoResponseParams & GetDefault() { static SteamTxnUserInfoResponseParams def; return def; }
=======
  static constexpr bool HasDefault() { return true; }
  static SteamTxnUserInfoResponseParams & GetDefault() { static SteamTxnUserInfoResponseParams def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<SteamTxnUserInfoResponseParams *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const SteamTxnUserInfoResponseParams *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<SteamTxnUserInfoResponseParams *>(ptr);
    if(typeid(SteamTxnUserInfoResponseParams).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const SteamTxnUserInfoResponseParams *>(ptr);
    if(typeid(SteamTxnUserInfoResponseParams).hash_code() == type_id_hash) return c;
    return nullptr;
  }

>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <>
struct StormReflTypeInfo<SteamTxnUserInfoResponseParams>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "state"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA393D2FB; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SteamTxnUserInfoResponseParams::state; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SteamTxnUserInfoResponseParams::state; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SteamTxnUserInfoResponseParams *>(obj); return &ptr->state; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SteamTxnUserInfoResponseParams *>(obj); return &ptr->state; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<SteamTxnUserInfoResponseParams>::field_data<0, Self> : public StormReflTypeInfo<SteamTxnUserInfoResponseParams>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.state; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.state; }
  void SetDefault() { self.state = StormReflTypeInfo<SteamTxnUserInfoResponseParams>::GetDefault().state; }
};

template <>
struct StormReflTypeInfo<SteamTxnUserInfoResponseParams>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "country"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5373C966; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &SteamTxnUserInfoResponseParams::country; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &SteamTxnUserInfoResponseParams::country; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SteamTxnUserInfoResponseParams *>(obj); return &ptr->country; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SteamTxnUserInfoResponseParams *>(obj); return &ptr->country; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<SteamTxnUserInfoResponseParams>::field_data<1, Self> : public StormReflTypeInfo<SteamTxnUserInfoResponseParams>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.country; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.country; }
  void SetDefault() { self.country = StormReflTypeInfo<SteamTxnUserInfoResponseParams>::GetDefault().country; }
};

template <>
struct StormReflTypeInfo<SteamTxnUserInfoResponseParams>::field_data_static<2>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "currency"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6956883F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &SteamTxnUserInfoResponseParams::currency; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &SteamTxnUserInfoResponseParams::currency; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SteamTxnUserInfoResponseParams *>(obj); return &ptr->currency; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SteamTxnUserInfoResponseParams *>(obj); return &ptr->currency; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<SteamTxnUserInfoResponseParams>::field_data<2, Self> : public StormReflTypeInfo<SteamTxnUserInfoResponseParams>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.currency; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.currency; }
  void SetDefault() { self.currency = StormReflTypeInfo<SteamTxnUserInfoResponseParams>::GetDefault().currency; }
};

template <>
struct StormReflTypeInfo<SteamTxnUserInfoResponseParams>::field_data_static<3>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "status"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x7B00651C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &SteamTxnUserInfoResponseParams::status; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &SteamTxnUserInfoResponseParams::status; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SteamTxnUserInfoResponseParams *>(obj); return &ptr->status; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SteamTxnUserInfoResponseParams *>(obj); return &ptr->status; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<SteamTxnUserInfoResponseParams>::field_data<3, Self> : public StormReflTypeInfo<SteamTxnUserInfoResponseParams>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.status; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.status; }
  void SetDefault() { self.status = StormReflTypeInfo<SteamTxnUserInfoResponseParams>::GetDefault().status; }
};

template <>
struct StormReflTypeInfo<SteamTxnUserInfoResponse>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "SteamTxnUserInfoResponse"; }
  static constexpr auto GetNameHash() { return 0xB6DEF1DD; }
<<<<<<< HEAD
  static SteamTxnUserInfoResponse & GetDefault() { static SteamTxnUserInfoResponse def; return def; }
=======
  static constexpr bool HasDefault() { return true; }
  static SteamTxnUserInfoResponse & GetDefault() { static SteamTxnUserInfoResponse def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<SteamTxnUserInfoResponse *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const SteamTxnUserInfoResponse *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<SteamTxnUserInfoResponse *>(ptr);
    if(typeid(SteamTxnUserInfoResponse).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const SteamTxnUserInfoResponse *>(ptr);
    if(typeid(SteamTxnUserInfoResponse).hash_code() == type_id_hash) return c;
    return nullptr;
  }

>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <>
struct StormReflTypeInfo<SteamTxnUserInfoResponse>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "result"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x136AC113; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SteamTxnUserInfoResponse::result; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SteamTxnUserInfoResponse::result; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SteamTxnUserInfoResponse *>(obj); return &ptr->result; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SteamTxnUserInfoResponse *>(obj); return &ptr->result; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<SteamTxnUserInfoResponse>::field_data<0, Self> : public StormReflTypeInfo<SteamTxnUserInfoResponse>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.result; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.result; }
  void SetDefault() { self.result = StormReflTypeInfo<SteamTxnUserInfoResponse>::GetDefault().result; }
};

template <>
struct StormReflTypeInfo<SteamTxnUserInfoResponse>::field_data_static<1>
{
  using member_type = SteamTxnUserInfoResponseParams; // SteamTxnUserInfoResponseParams
  static constexpr auto GetName() { return "params"; }
  static constexpr auto GetType() { return "SteamTxnUserInfoResponseParams"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8FCE0EF3; }
  static constexpr unsigned GetTypeNameHash() { return 0x54CE31D1; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &SteamTxnUserInfoResponse::params; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &SteamTxnUserInfoResponse::params; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SteamTxnUserInfoResponse *>(obj); return &ptr->params; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SteamTxnUserInfoResponse *>(obj); return &ptr->params; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<SteamTxnUserInfoResponse>::field_data<1, Self> : public StormReflTypeInfo<SteamTxnUserInfoResponse>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, SteamTxnUserInfoResponseParams> & Get() { return self.params; }
  std::add_const_t<std::remove_reference_t<SteamTxnUserInfoResponseParams>> & Get() const { return self.params; }
  void SetDefault() { self.params = StormReflTypeInfo<SteamTxnUserInfoResponse>::GetDefault().params; }
};

template <>
struct StormReflTypeInfo<SteamTxnUserInfo>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "SteamTxnUserInfo"; }
  static constexpr auto GetNameHash() { return 0x04266DAE; }
<<<<<<< HEAD
  static SteamTxnUserInfo & GetDefault() { static SteamTxnUserInfo def; return def; }
=======
  static constexpr bool HasDefault() { return true; }
  static SteamTxnUserInfo & GetDefault() { static SteamTxnUserInfo def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<SteamTxnUserInfo *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const SteamTxnUserInfo *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<SteamTxnUserInfo *>(ptr);
    if(typeid(SteamTxnUserInfo).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const SteamTxnUserInfo *>(ptr);
    if(typeid(SteamTxnUserInfo).hash_code() == type_id_hash) return c;
    return nullptr;
  }

>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <>
struct StormReflTypeInfo<SteamTxnUserInfo>::field_data_static<0>
{
  using member_type = SteamTxnUserInfoResponse; // SteamTxnUserInfoResponse
  static constexpr auto GetName() { return "response"; }
  static constexpr auto GetType() { return "SteamTxnUserInfoResponse"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3E7B0BFB; }
  static constexpr unsigned GetTypeNameHash() { return 0xB6DEF1DD; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SteamTxnUserInfo::response; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SteamTxnUserInfo::response; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SteamTxnUserInfo *>(obj); return &ptr->response; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SteamTxnUserInfo *>(obj); return &ptr->response; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<SteamTxnUserInfo>::field_data<0, Self> : public StormReflTypeInfo<SteamTxnUserInfo>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, SteamTxnUserInfoResponse> & Get() { return self.response; }
  std::add_const_t<std::remove_reference_t<SteamTxnUserInfoResponse>> & Get() const { return self.response; }
  void SetDefault() { self.response = StormReflTypeInfo<SteamTxnUserInfo>::GetDefault().response; }
};

namespace StormReflFileInfo
{
  struct SteamServerMessages
  {
    static const int types_n = 9;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct SteamServerMessages::type_info<0>
  {
    using type = ::SteamValidationResponseParams;
  };

  template <>
  struct SteamServerMessages::type_info<1>
  {
    using type = ::SteamValidationResponse;
  };

  template <>
  struct SteamServerMessages::type_info<2>
  {
    using type = ::SteamValidation;
  };

  template <>
  struct SteamServerMessages::type_info<3>
  {
    using type = ::SteamOwnershipResponseParams;
  };

  template <>
  struct SteamServerMessages::type_info<4>
  {
    using type = ::SteamOwnershipResponse;
  };

  template <>
  struct SteamServerMessages::type_info<5>
  {
    using type = ::SteamOwnership;
  };

  template <>
  struct SteamServerMessages::type_info<6>
  {
    using type = ::SteamTxnUserInfoResponseParams;
  };

  template <>
  struct SteamServerMessages::type_info<7>
  {
    using type = ::SteamTxnUserInfoResponse;
  };

  template <>
  struct SteamServerMessages::type_info<8>
  {
    using type = ::SteamTxnUserInfo;
  };

}

