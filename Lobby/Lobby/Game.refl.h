#pragma once

#include <HurricaneDDS/DDSDataObject.h>
#include <HurricaneDDS/DDSConnectionId.h>

#include "SharedTypes.refl.h"
#include "LobbyConfig.h"

struct Game
{
  DDS_TEMPORARY_OBJECT(true, DDSDataObjectPriority::kLow);

  Game(DDSNodeInterface node_interface);

  void STORM_REFL_FUNC AddUser(DDSResponder & responder, DDSKey user_key, int admin_level);
  void STORM_REFL_FUNC RemoveUser(DDSKey user_key);
  void STORM_REFL_FUNC KickUser(DDSKey endpoint_id, DDSKey user_key, DDSKey src_user, int src_admin_level);

  void STORM_REFL_FUNC SendChat(DDSKey user_key, DDSKey endpoint_id, std::string message, std::string title);

  void STORM_REFL_FUNC HandleMemberUpdate(DDSKey user_key, std::string data);

  void STORM_REFL_FUNC GetInfo(DDSResponder & responder);


public:
  DDSKey m_AssignedServer;

private:
  DDSNodeInterface m_Interface;
};
