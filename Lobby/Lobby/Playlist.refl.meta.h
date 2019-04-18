#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "Playlist.refl.h"
#include "Game/GameNetworkData.refl.meta.h"
#include "GameData.refl.meta.h"


template <>
struct StormReflTypeInfo<PlaylistDatabaseElement>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "PlaylistDatabaseElement"; }
  static constexpr auto GetNameHash() { return 0x5E943D5F; }
  static constexpr bool HasDefault() { return true; }
  static PlaylistDatabaseElement & GetDefault() { static PlaylistDatabaseElement def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<PlaylistDatabaseElement *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const PlaylistDatabaseElement *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<PlaylistDatabaseElement *>(ptr);
    if(typeid(PlaylistDatabaseElement).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const PlaylistDatabaseElement *>(ptr);
    if(typeid(PlaylistDatabaseElement).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<PlaylistDatabaseElement>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &PlaylistDatabaseElement::m_Name; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlaylistDatabaseElement *>(obj); return &ptr->m_Name; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlaylistDatabaseElement *>(obj); return &ptr->m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<PlaylistDatabaseElement>::field_data<0, Self> : public StormReflTypeInfo<PlaylistDatabaseElement>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<PlaylistDatabaseElement>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<PlaylistDatabaseElement>::field_data_static<1>
{
  using member_type = std::vector<GameInitSettings>; // std::vector<GameInitSettings, std::allocator<GameInitSettings> >
  static constexpr auto GetName() { return "m_GameModes"; }
  static constexpr auto GetType() { return "std::vector<GameInitSettings, std::allocator<GameInitSettings> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF14C6D04; }
  static constexpr unsigned GetTypeNameHash() { return 0xC7D24044; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &PlaylistDatabaseElement::m_GameModes; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlaylistDatabaseElement *>(obj); return &ptr->m_GameModes; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlaylistDatabaseElement *>(obj); return &ptr->m_GameModes; }
};

template <typename Self>
struct StormReflTypeInfo<PlaylistDatabaseElement>::field_data<1, Self> : public StormReflTypeInfo<PlaylistDatabaseElement>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<GameInitSettings>> & Get() { return self.m_GameModes; }
  std::add_const_t<std::remove_reference_t<std::vector<GameInitSettings>>> & Get() const { return self.m_GameModes; }
  void SetDefault() { self.m_GameModes = StormReflTypeInfo<PlaylistDatabaseElement>::GetDefault().m_GameModes; }
};

template <>
struct StormReflTypeInfo<PlaylistDatabaseObj>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "PlaylistDatabaseObj"; }
  static constexpr auto GetNameHash() { return 0x89C7D86E; }
  static constexpr bool HasDefault() { return true; }
  static PlaylistDatabaseObj & GetDefault() { static PlaylistDatabaseObj def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<PlaylistDatabaseObj *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const PlaylistDatabaseObj *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<PlaylistDatabaseObj *>(ptr);
    if(typeid(PlaylistDatabaseObj).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const PlaylistDatabaseObj *>(ptr);
    if(typeid(PlaylistDatabaseObj).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<PlaylistDatabaseObj>::field_data_static<0>
{
  using member_type = std::vector<PlaylistDatabaseElement>; // std::vector<PlaylistDatabaseElement, std::allocator<PlaylistDatabaseElement> >
  static constexpr auto GetName() { return "m_Elements"; }
  static constexpr auto GetType() { return "std::vector<PlaylistDatabaseElement, std::allocator<PlaylistDatabaseElement> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB266D373; }
  static constexpr unsigned GetTypeNameHash() { return 0x18F69FD1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &PlaylistDatabaseObj::m_Elements; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlaylistDatabaseObj *>(obj); return &ptr->m_Elements; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlaylistDatabaseObj *>(obj); return &ptr->m_Elements; }
};

template <typename Self>
struct StormReflTypeInfo<PlaylistDatabaseObj>::field_data<0, Self> : public StormReflTypeInfo<PlaylistDatabaseObj>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<PlaylistDatabaseElement>> & Get() { return self.m_Elements; }
  std::add_const_t<std::remove_reference_t<std::vector<PlaylistDatabaseElement>>> & Get() const { return self.m_Elements; }
  void SetDefault() { self.m_Elements = StormReflTypeInfo<PlaylistDatabaseObj>::GetDefault().m_Elements; }
};

template <>
struct StormReflTypeInfo<Playlist>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "Playlist"; }
  static constexpr auto GetNameHash() { return 0x2EF4737B; }
  static constexpr bool HasDefault() { return false; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<Playlist *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const Playlist *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<Playlist *>(ptr);
    if(typeid(Playlist).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const Playlist *>(ptr);
    if(typeid(Playlist).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<Playlist>::field_data_static<0>
{
  using member_type = PlaylistDatabaseObj; // PlaylistDatabaseObj
  static constexpr auto GetName() { return "m_CasualPlaylist"; }
  static constexpr auto GetType() { return "PlaylistDatabaseObj"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFB196E8C; }
  static constexpr unsigned GetTypeNameHash() { return 0x89C7D86E; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &Playlist::m_CasualPlaylist; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<Playlist *>(obj); return &ptr->m_CasualPlaylist; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const Playlist *>(obj); return &ptr->m_CasualPlaylist; }
};

template <typename Self>
struct StormReflTypeInfo<Playlist>::field_data<0, Self> : public StormReflTypeInfo<Playlist>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, PlaylistDatabaseObj> & Get() { return self.m_CasualPlaylist; }
  std::add_const_t<std::remove_reference_t<PlaylistDatabaseObj>> & Get() const { return self.m_CasualPlaylist; }
};

template <>
struct StormReflTypeInfo<Playlist>::field_data_static<1>
{
  using member_type = PlaylistDatabaseObj; // PlaylistDatabaseObj
  static constexpr auto GetName() { return "m_CompetitivePlaylist"; }
  static constexpr auto GetType() { return "PlaylistDatabaseObj"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC33681CF; }
  static constexpr unsigned GetTypeNameHash() { return 0x89C7D86E; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &Playlist::m_CompetitivePlaylist; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<Playlist *>(obj); return &ptr->m_CompetitivePlaylist; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const Playlist *>(obj); return &ptr->m_CompetitivePlaylist; }
};

template <typename Self>
struct StormReflTypeInfo<Playlist>::field_data<1, Self> : public StormReflTypeInfo<Playlist>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, PlaylistDatabaseObj> & Get() { return self.m_CompetitivePlaylist; }
  std::add_const_t<std::remove_reference_t<PlaylistDatabaseObj>> & Get() const { return self.m_CompetitivePlaylist; }
};

template <>
struct StormReflFuncInfo<Playlist>
{
  using MyBase = void;
  static constexpr int funcs_n = 0;
  template <int N> struct func_data_static {};
};

namespace StormReflFileInfo
{
  struct Playlist
  {
    static const int types_n = 3;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct Playlist::type_info<0>
  {
    using type = ::PlaylistDatabaseElement;
  };

  template <>
  struct Playlist::type_info<1>
  {
    using type = ::PlaylistDatabaseObj;
  };

  template <>
  struct Playlist::type_info<2>
  {
    using type = ::Playlist;
  };

}

