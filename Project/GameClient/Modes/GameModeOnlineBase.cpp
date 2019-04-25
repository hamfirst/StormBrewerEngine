
#include "GameClient/Modes/GameModeOnlineBase.h"
#include "GameClient/Modes/GameModeMainMenu.h"
#include "GameClient/GameContainer.h"

GameModeOnlineBase::GameModeOnlineBase(GameContainer & game) :
  GameMode(game)
{

}

GameModeOnlineBase::~GameModeOnlineBase()
{

}

bool GameModeOnlineBase::HandleDisconnect()
{
  if (StillOnline())
  {
    return false;
  }

  if (GetContainer().HasLobbyClient())
  {
    GetContainer().SwitchMode<GameModeMainMenu>(GetContainer().GetLobbyClient().GetConnectionError());
  }
  else
  {
    GetContainer().SwitchMode<GameModeMainMenu>();
  }
  return true;
}

bool GameModeOnlineBase::StillOnline()
{
  return GetContainer().HasLobbyClient() && GetContainer().GetLobbyClient().GetState() != LobbyClientState::kDisconnected;
}