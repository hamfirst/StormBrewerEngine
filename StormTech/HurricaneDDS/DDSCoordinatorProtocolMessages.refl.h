#pragma once

#include <cstdint>

#include "DDSNodeId.h"
#include "DDSSharedMessages.refl.h"

#include <StormRefl/StormRefl.h>
#include <StormRefl/StormReflJsonStd.h>

#include <StormData/StormDataChangeType.refl.h>

enum class STORM_REFL_ENUM DDSCoordinatorProtocolMessageType
{
  kUnknown,
  kHandshakeRequest,
  kHandshakeResponse,
  kHandshakeFinalize,
  kNodeInit,
  kRoutingTable,
  kRoutingTableAck,
  kSyncAllClear,
  kShutDown,
  kSharedObjectDelta,
  kCPUUsage,
  kResponderCall,
  kTargetedMessage,
  kTargetedMessageResponder,
  kCreateSubscription,
  kDestroySubscription,
  kSubscriptionDeleted,
};

struct DDSCoordinatorHandshakeRequest
{
  STORM_REFL;
  static const DDSCoordinatorProtocolMessageType Type = DDSCoordinatorProtocolMessageType::kHandshakeRequest;

  uint64_t m_Challenge;
  int m_Version;
};

struct DDSCoordinatorHandshakeResponse
{
  STORM_REFL;
  static const DDSCoordinatorProtocolMessageType Type = DDSCoordinatorProtocolMessageType::kHandshakeResponse;
  uint64_t m_ChallengeResponse;
  uint64_t m_ChallengeRequest;
};

struct DDSCoordinatorHandshakeFinalize
{
  STORM_REFL;
  static const DDSCoordinatorProtocolMessageType Type = DDSCoordinatorProtocolMessageType::kHandshakeFinalize;

  uint64_t m_ChallengeResponse;
  uint32_t m_PublicIp;
  uint16_t m_NodePort;

  std::vector<DDSNodePort> m_EndpointPorts;
  std::vector<DDSNodePort> m_WebsitePorts;
};

struct DDSCoordinatorNodeInitialization
{
  STORM_REFL;
  static const DDSCoordinatorProtocolMessageType Type = DDSCoordinatorProtocolMessageType::kNodeInit;

  DDSNodeId m_NodeId;
  uint64_t m_ClientSecret;
  uint64_t m_ServerSecret;
  bool m_InitialNode;
  int64_t m_NetworkTime;

  std::vector<std::string> m_SharedObjects;
};

struct DDSCoordinatorRoutingTableAck
{
  STORM_REFL;
  static const DDSCoordinatorProtocolMessageType Type = DDSCoordinatorProtocolMessageType::kRoutingTableAck;
  int m_TableGen;
};

struct DDSCoordinatorSyncAllClear
{
  STORM_REFL;
  static const DDSCoordinatorProtocolMessageType Type = DDSCoordinatorProtocolMessageType::kSyncAllClear;
  int m_TableGen;
};


struct DDSCoordinatorNodeShutdown
{
  STORM_REFL;
  static const DDSCoordinatorProtocolMessageType Type = DDSCoordinatorProtocolMessageType::kShutDown;
};

struct DDSCoordinatorNodeCPUUsage
{
  STORM_REFL;
  static const DDSCoordinatorProtocolMessageType Type = DDSCoordinatorProtocolMessageType::kCPUUsage;
  float m_Usage;
};

struct DDSCoordinatorSharedObjectDeltaMessage
{
  STORM_REFL;
  ReflectionNotifyChangeType m_Type;
  std::string m_Path;
  uint64_t m_Index;
  std::string m_Data;
};

struct DDSCoordinatorSharedObjectDelta
{
  STORM_REFL;
  static const DDSCoordinatorProtocolMessageType Type = DDSCoordinatorProtocolMessageType::kSharedObjectDelta;

  int m_SharedObjectType;
  std::vector<DDSCoordinatorSharedObjectDeltaMessage> m_Deltas;
};

struct DDSCoordinatorResponderCallData : public DDSResponderCallBase
{
  STORM_REFL;
  static const DDSCoordinatorProtocolMessageType Type = DDSCoordinatorProtocolMessageType::kResponderCall;
};

struct DDSCoordinatorTargetedMessage : public DDSTargetedMessageBase
{
  STORM_REFL;
  static const DDSCoordinatorProtocolMessageType Type = DDSCoordinatorProtocolMessageType::kTargetedMessage;
};

struct DDSCoordinatorTargetedMessageWithResponder : public DDSTargetedMessageWithResponderBase
{
  STORM_REFL;
  static const DDSCoordinatorProtocolMessageType Type = DDSCoordinatorProtocolMessageType::kTargetedMessageResponder;
};

struct DDSCoordinatorCreateSubscription : public DDSCreateSubscriptionBase
{
  STORM_REFL;
  static const DDSCoordinatorProtocolMessageType Type = DDSCoordinatorProtocolMessageType::kCreateSubscription;
};

struct DDSCoordinatorDestroySubscription : public DDSDestroySubscriptionBase
{
  STORM_REFL;
  static const DDSCoordinatorProtocolMessageType Type = DDSCoordinatorProtocolMessageType::kDestroySubscription;
};

struct DDSCoordinatorSubscriptionDeleted : public DDSSubscriptionDeletedBase
{
  STORM_REFL;
  static const DDSCoordinatorProtocolMessageType Type = DDSCoordinatorProtocolMessageType::kSubscriptionDeleted;
};

