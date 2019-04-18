#pragma once

#include <HurricaneDDS/DDSDataObject.h>

#include "Game/GameNetworkData.refl.h"

#include "GameData.refl.h"
#include "LobbyConfig.h"


struct PlaylistDatabaseElement
{
  STORM_REFL;

  std::string m_Name;
  std::vector<GameInitSettings> m_GameModes;
};

struct PlaylistDatabaseObj
{
  STORM_REFL;
  std::vector<PlaylistDatabaseElement> m_Elements;
};

struct Playlist
{
public:
  DDS_SHARED_OBJECT;

  Playlist(DDSObjectInterface & obj_interface);

  void Initialize();

public:

  PlaylistDatabaseObj m_CasualPlaylist;
  PlaylistDatabaseObj m_CompetitivePlaylist;

private:
  STORM_REFL_IGNORE DDSObjectInterface & m_Interface;
};

