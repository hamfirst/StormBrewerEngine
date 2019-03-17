
#include <StormData/StormDataChangePacket.h>

#include <HurricaneDDS/DDSResponderCall.h>

#include <hash/Hash64.h>
#include <sb/vector.h>

#include "BuiltInChannel.refl.meta.h"

#ifdef ENABLE_CHANNELS

STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(BuiltInChannelInfo);

BuiltInChannel::BuiltInChannel(DDSNodeInterface node_interface, BuiltInChannelDatabaseObject & db_object) :
  m_Interface(node_interface), m_Data(db_object)
{

}

void BuiltInChannel::GetChannelName(DDSResponder & responder)
{
  DDSResponderCall(responder, m_Data.m_ChannelInfo.m_ChannelName);
}

void BuiltInChannel::UpdateMotd(std::string motd)
{
  m_Data.m_ChannelInfo.m_Motd = motd;
}

#endif
