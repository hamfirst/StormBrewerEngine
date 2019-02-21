#pragma once

#include <optional>

#include <HurricaneDDS/DDSDataObject.h>
#include <HurricaneDDS/DDSConnectionId.h>

enum STORM_REFL_ENUM class BotConnectionState
{
  kWaitingForConnection,
  kAuthenticating,
  kConnected,
};

struct BotConnection
{
  DDS_TEMPORARY_OBJECT(false, DDSDataObjectPriority::kHigh);

  BotConnection(DDSNodeInterface node_interface);

  void STORM_REFL_FUNC LoadBot(std::string user_name, std::string password);
  void STORM_REFL_FUNC GotMessage(std::string cmd, std::string data);

  void STORM_REFL_FUNC HandleBotLoad(bool success);
  void STORM_REFL_FUNC HandleBotLoadFail();

  void STORM_REFL_FUNC SendData(std::string data);

public:

  void ConnectToEndpoint(DDSConnectionId connection_id);
  void ParseError();

  void PreDestroy();
  void PreMoveObject();

private:

  template <typename T>
  void SendPacket(const T & t);

public:

  BotConnectionState m_State;
  bool m_Error;

  std::vector<std::string> m_PendingMessages;

  DDSKey m_BotId;

private:
  DDSNodeInterface m_Interface;
  std::optional<DDSConnectionId> m_ConnectionId;

  bool m_Relocating;
};

