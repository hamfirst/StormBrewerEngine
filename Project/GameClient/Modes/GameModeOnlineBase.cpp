
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

  auto & container = GetContainer();
  if (container.HasLobbyClient())
  {
    auto & lobby_client = GetContainer().GetLobbyClient();
    auto connection_error = lobby_client.GetConnectionError();
    container.StopLobbyClient();
    container.SwitchMode<GameModeMainMenu>(connection_error);
  }
  else
  {
    container.SwitchMode<GameModeMainMenu>();
  }
  return true;
}

bool GameModeOnlineBase::StillOnline()
{
  if(GetContainer().HasLobbyClient())
  {
    GetContainer().GetLobbyClient().Update();
    if(GetContainer().GetLobbyClient().GetState() == LobbyClientState::kDisconnected)
    {
      return false;
    }
  }

  return true;
}