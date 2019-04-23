#pragma once

#include <optional>

#include <HurricaneDDS/DDSDataObject.h>
#include <HurricaneDDS/DDSConnectionId.h>
#include "LobbyConfig.h"


enum STORM_REFL_ENUM class UserConnectionState
{
  kRequestingUserName,
  kLoadingUser,
  kCreatingNewUser,
  kLoaded,
};

struct UserConnection
{
  DDS_TEMPORARY_OBJECT(false, DDSDataObjectPriority::kHigh);

  UserConnection(DDSNodeInterface node_interface);

  void STORM_REFL_FUNC LoadUser(std::string platform, uint64_t platform_id, uint64_t user_id, std::string remote_ip,
      std::string remote_host, std::string country_code, std::string currency_code, bool guest, std::string chosen_user_name);
  void STORM_REFL_FUNC GotMessage(std::string cmd, std::string data);

  void STORM_REFL_FUNC UserDoesntExist();

  void STORM_REFL_FUNC SendData(std::string data);
  void STORM_REFL_FUNC SendNotification(std::string msg);
  void STORM_REFL_FUNC SendServerText(std::string msg);
  void STORM_REFL_FUNC SendRuntimeError(std::string msg);
  void STORM_REFL_FUNC SendConnectionError(std::string msg);

  void STORM_REFL_FUNC HandleUserInsert(int ec);
  void STORM_REFL_FUNC HandleLocalDataUpdate(std::string data);


#ifdef ENABLE_GAME_LIST
  void STORM_REFL_FUNC HandleGameListUpdate(std::string data);
#endif

#ifdef ENABLE_WELCOME_INFO
  void STORM_REFL_FUNC HandleWelcomeInfoUpdate(std::string data);
#endif

#ifdef ENABLE_BAN_LIST
  void STORM_REFL_FUNC HandleBanListUpdate(std::string data);
#endif

#ifdef ENABLE_GAME_LIST
  void STORM_REFL_FUNC HandleGamePreviewUpdate(int request_id, std::string data);
  void STORM_REFL_FUNC HandleGamePreviewDestroyed(int request_id);
#endif

public:

  void CreateUserObject(const std::string & name);
  void ConnectToEndpoint(DDSConnectionId connection_id);
  void FinalizeUserLoaded();
  void PreDestroy();
  void PreMoveObject();

public:

  std::string m_Platform;
  uint64_t m_PlatformId;
  uint64_t m_UserId;

#ifdef ENABLE_GAME_LIST
  DDSKey m_GamePreviewServerId = 0;
  DDSKey m_GamePreviewSubscription = 0;
  int m_GamePreviewRequestId = 0;
#endif

  UserConnectionState m_State;

  std::vector<std::string> m_PendingMessages;
  bool m_Error;

  std::string m_UserName;
  std::string m_RemoteIP;
  std::string m_RemoteHost;

  std::string m_CountryCode;
  std::string m_CurrencyCode;

private:
  DDSNodeInterface m_Interface;
  std::optional<DDSConnectionId> m_ConnectionId;

  bool m_Relocating;
};

