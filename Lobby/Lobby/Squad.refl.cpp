#include <StormData/StormDataChangePacket.h>

#include <HurricaneDDS/DDSResponderCall.h>

#include <hash/Hash64.h>
#include <sb/vector.h>

#include "Squad.refl.meta.h"
#include "UserConnection.refl.meta.h"
#include "User.refl.meta.h"
#include "Channel.refl.meta.h"

STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(SquadDatabaseMemberInfo);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(SquadDatabaseApplicantInfo);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(SquadDatabaseInfo);

Squad::Squad(DDSNodeInterface node_interface, SquadDatabaseObject & db_object) :
  m_Interface(node_interface), 
  m_Data(db_object),
  m_ChangeThrottle(10, 1)
{
  m_SquadInfo.m_Name = m_Data.m_DatabaseInfo.m_Name;
  m_SquadInfo.m_Tag = m_Data.m_DatabaseInfo.m_Tag;
  m_SquadInfo.m_Locked = m_Data.m_DatabaseInfo.m_Locked;
  m_SquadInfo.m_Motd = m_Data.m_DatabaseInfo.m_Motd;
  m_SquadInfo.m_SquadKey = m_Interface.GetLocalKey();

  printf("Loading squad: %s\n", m_SquadInfo.m_Name.c_str());
}

void Squad::ApplyToSquad(DDSResponder & responder, DDSKey user_id, std::string user_name)
{
  for (auto user : m_Data.m_DatabaseInfo.m_Users)
  {
    if (user.second.m_UserKey == user_id)
    {
      DDSResponderCall(responder, "You are already in that squad");
      return;
    }
  }

  for (auto user : m_Data.m_DatabaseInfo.m_Applications)
  {
    if (user.second.m_UserKey == user_id)
    {
      DDSResponderCall(responder, "You have already applied to that squad");
      return;
    }
  }

  SquadApplication new_application;
  new_application.m_UserKey = user_id;
  new_application.m_UserName = user_name;

  m_SquadInfo.m_Applicants.EmplaceBack(new_application);

  SquadDatabaseApplicantInfo db_app;
  db_app.m_UserKey = user_id;
  m_Data.m_DatabaseInfo.m_Applications.EmplaceBack(db_app);

  m_Interface.Call(&User::AddApplicationInternal, user_id, m_Interface.GetLocalKey(), 
    m_Data.m_DatabaseInfo.m_Name.ToString(), m_Data.m_DatabaseInfo.m_Tag.ToString());

  DDSResponderCall(responder, "Successfully applied to squad");
}

void Squad::AcceptApplicationToSquad(DDSResponder & responder, DDSKey user_source, DDSKey user_id)
{
  if (GetSquadMemberFlags(user_source) <= kSquadLeader)
  {
    DDSResponderCall(responder, "You do not have permission for that");
    return;
  }

  for (auto user : m_SquadInfo.m_Applicants)
  {
    if (user.second.m_UserKey == user_id)
    {
      PutUserInSquad(user_id, user.second.m_UserName.ToString(), kSquadMember);
      DDSResponderCall(responder, "Successfully accepted invite");
    }
  }
}

void Squad::DeclineApplicationToSquad(DDSResponder & responder, DDSKey user_source, DDSKey user_id)
{
  if (GetSquadMemberFlags(user_source) <= kSquadLeader)
  {
    DDSResponderCall(responder, "You do not have permission for that");
    return;
  }

  for (auto user : m_Data.m_DatabaseInfo.m_Applications)
  {
    if (user.second.m_UserKey == user_id)
    {
      auto user_key = m_SquadInfo.m_Applicants[user.first].m_UserKey;
      auto user_name = m_SquadInfo.m_Applicants[user.first].m_UserName;

      m_Data.m_DatabaseInfo.m_Applications.RemoveAt(user.first);
      m_SquadInfo.m_Applicants.RemoveAt(user.first);

      m_Interface.Call(&User::CancelApplicationInternal, user_id, m_Interface.GetLocalKey());
      DDSResponderCall(responder, "Successfully declined application");
      return;
    }
  }

  DDSResponderCall(responder, "That user has not applied to your squad");
}

void Squad::RescindApplicationToSquad(DDSResponder & responder, DDSKey user_id)
{
  for (auto user : m_Data.m_DatabaseInfo.m_Applications)
  {
    if (user.second.m_UserKey == user_id)
    {
      auto user_key = m_SquadInfo.m_Applicants[user.first].m_UserKey;
      auto user_name = m_SquadInfo.m_Applicants[user.first].m_UserName;

      m_Data.m_DatabaseInfo.m_Applications.RemoveAt(user.first);
      m_SquadInfo.m_Applicants.RemoveAt(user.first);

      m_Interface.Call(&User::CancelApplicationInternal, user_id, m_Interface.GetLocalKey());
      DDSResponderCall(responder, "Successfully rescinded application");
      return;
    }
  }

  DDSResponderCall(responder, "You have not applied to that squad");
}

void Squad::RequestUserToJoinSquad(DDSResponder & responder, DDSKey user_source, DDSKey user_id, std::string user_name)
{
  if (GetSquadMemberFlags(user_source) <= kSquadLeader)
  {
    DDSResponderCall(responder, "You do not have permission for that");
    return;
  }

  for (auto user : m_Data.m_DatabaseInfo.m_Users)
  {
    if (user.second.m_UserKey == user_id)
    {
      DDSResponderCall(responder, "That user is already in the squad");
      return;
    }
  }

  for (auto user : m_Data.m_DatabaseInfo.m_Requests)
  {
    if (user.second.m_UserKey == user_id)
    {
      DDSResponderCall(responder, "That user has already been requested to join");
      return;
    }
  }

  SquadApplication new_application;
  new_application.m_UserKey = user_id;
  new_application.m_UserName = user_name;

  m_SquadInfo.m_Requests.EmplaceBack(new_application);

  SquadDatabaseApplicantInfo db_app;
  db_app.m_UserKey = user_id;
  m_Data.m_DatabaseInfo.m_Requests.EmplaceBack(db_app);

  m_Interface.Call(&User::AddSquadRequestInternal, user_id, m_Interface.GetLocalKey(), 
    m_Data.m_DatabaseInfo.m_Name.ToString(), m_Data.m_DatabaseInfo.m_Tag.ToString());

  DDSResponderCall(responder, "Successfully requested user to join");
}

void Squad::AcceptRequestToJoinSquad(DDSResponder & responder, DDSKey user_id)
{
  for (auto user : m_SquadInfo.m_Requests)
  {
    if (user.second.m_UserKey == user_id)
    {
      PutUserInSquad(user_id, user.second.m_UserName.ToString(), kSquadMember);
      return;
    }
  }

  DDSResponderCall(responder, "You were not invited to join");
}

void Squad::DeclineRequestToJoinSquad(DDSResponder & responder, DDSKey user_id)
{
  for (auto user : m_Data.m_DatabaseInfo.m_Requests)
  {
    if (user.second.m_UserKey == user_id)
    {
      auto user_key = m_SquadInfo.m_Requests[user.first].m_UserKey;
      auto user_name = m_SquadInfo.m_Requests[user.first].m_UserName;

      m_Data.m_DatabaseInfo.m_Requests.RemoveAt(user.first);
      m_SquadInfo.m_Requests.RemoveAt(user.first);

      m_Interface.Call(&User::CancelSquadRequestInternal, user_id, m_Interface.GetLocalKey());
      DDSResponderCall(responder, "Successfully declined squad request");
      return;
    }
  }

  DDSResponderCall(responder, "You were not invited to join");
}

void Squad::RescindRequestToJoinSquad(DDSResponder & responder, DDSKey user_source, DDSKey user_id)
{
  if (GetSquadMemberFlags(user_source) <= kSquadLeader)
  {
    DDSResponderCall(responder, "You do not have permission for that");
    return;
  }

  for (auto user : m_Data.m_DatabaseInfo.m_Requests)
  {
    if (user.second.m_UserKey == user_id)
    {
      auto user_key = m_SquadInfo.m_Requests[user.first].m_UserKey;
      auto user_name = m_SquadInfo.m_Requests[user.first].m_UserName;

      m_Data.m_DatabaseInfo.m_Requests.RemoveAt(user.first);
      m_SquadInfo.m_Requests.RemoveAt(user.first);

      m_Interface.Call(&User::CancelSquadRequestInternal, user_id, m_Interface.GetLocalKey());
      DDSResponderCall(responder, "Successfully rescinded invite");
      return;
    }
  }

  DDSResponderCall(responder, "That use has not been invited");
}

void Squad::LeaveSquad(DDSResponder & responder, DDSKey user_id)
{
  if (user_id == m_Data.m_Creator)
  {
    DDSResponderCall(responder, "The owner must disband the squad if they want to leave");
    return;
  }

  for (auto user : m_Data.m_DatabaseInfo.m_Users)
  {
    if (user.second.m_UserKey == user_id)
    {
      m_Data.m_DatabaseInfo.m_Users.RemoveAt(user.first);
      m_SquadInfo.m_Users.RemoveAt(user.first);

      m_Interface.Call(&User::RemoveSquadInternal, user_id, m_Interface.GetLocalKey());

      DDSResponderCall(responder, "Successfully left squad");
      return;
    }
  }

  DDSResponderCall(responder, "You are not in that squad");
}

void Squad::RemoveMember(DDSResponder & responder, DDSKey user_source, DDSKey user_id)
{
  if (user_id == m_Data.m_Creator)
  {
    DDSResponderCall(responder, "You cannot remove the owner of the squad");
    return;
  }

  if (user_id == user_source)
  {
    DDSResponderCall(responder, "You cannot remove yourself from the squad");
    return;
  }

  if (GetSquadMemberFlags(user_source) <= kSquadLeader)
  {
    DDSResponderCall(responder, "You do not have permission for that");
    return;
  }

  for (auto user : m_Data.m_DatabaseInfo.m_Users)
  {
    if (user.second.m_UserKey == user_id)
    {
      m_Data.m_DatabaseInfo.m_Users.RemoveAt(user.first);
      m_SquadInfo.m_Users.RemoveAt(user.first);

      m_Interface.Call(&User::RemoveSquadInternal, user_id, m_Interface.GetLocalKey());

      DDSResponderCall(responder, "Successfully removed member");
      return;
    }
  }

  DDSResponderCall(responder, "That user is not in that squad");
}

void Squad::SetMemberPermissions(DDSResponder & responder, DDSKey user_source, DDSKey user_id, int member_permissions)
{
  if (GetSquadMemberFlags(user_source) <= kSquadLeader)
  {
    DDSResponderCall(responder, "You do not have permission for that");
    return;
  }

  if (member_permissions < 0 || member_permissions >= kSquadCreator)
  {
    DDSResponderCall(responder, "Invalid permissions");
    return;
  }

  if (user_id == m_Data.m_Creator)
  {
    DDSResponderCall(responder, "You cannot edit the owner's permissions");
    return;
  }

  if (user_source == user_id)
  {
    DDSResponderCall(responder, "You cannot edit your own permissions");
    return;
  }

  for (auto user : m_Data.m_DatabaseInfo.m_Users)
  {
    if (user.second.m_UserKey == user_id)
    {
      user.second.m_MembershipFlags = member_permissions;
      m_SquadInfo.m_Users[user.first].m_MembershipFlags = member_permissions;
      DDSResponderCall(responder, "Successuflly changed permissions");
      return;
    }
  }

  DDSResponderCall(responder, "That user is not in the squad");
}

void Squad::SetMotd(DDSResponder & responder, DDSKey user_source, std::string motd)
{
  if (GetSquadMemberFlags(user_source) < kSquadLeader)
  {
    DDSResponderCall(responder, "You do not have permission for that");
    return;
  }

  if (m_ChangeThrottle.GrabCredits(m_Interface.GetNetworkTime(), 1) == false)
  {
    DDSResponderCall(responder, "You must wait before doing that");
    return;
  }

  if (motd.length() > 2000)
  {
    DDSResponderCall(responder, "Channel info is too long.  Maximum 2000 characters");
    return;
  }

  UpdateMotd(motd);
}

void Squad::SetChannelLock(DDSResponder & responder, DDSKey user_source, bool locked)
{
  if (GetSquadMemberFlags(user_source) < kSquadLeader)
  {
    DDSResponderCall(responder, "You do not have permission for that");
    return;
  }

  if (m_ChangeThrottle.GrabCredits(m_Interface.GetNetworkTime(), 1) == false)
  {
    DDSResponderCall(responder, "You must wait before doing that");
    return;
  }

  m_SquadInfo.m_Locked = locked;
  m_Data.m_DatabaseInfo.m_Locked = locked;
}

void Squad::GetSquadName(DDSResponder & responder)
{
  DDSResponderCall(responder, m_Data.m_DatabaseInfo.m_Name.ToString(), m_Data.m_DatabaseInfo.m_Tag.ToString());
}

void Squad::KillSquad(DDSResponder & responder)
{
  DDSResponderCall(responder, "Squad " + m_SquadInfo.m_Name.ToString() + " was disbanded");
  DestroySquad();
}

void Squad::DestroySquad()
{
  for (auto user : m_Data.m_DatabaseInfo.m_Users)
  {
    m_Interface.Call(&User::RemoveSquadInternal, user.second.m_UserKey, m_Interface.GetLocalKey());
  }

  for (auto user : m_Data.m_DatabaseInfo.m_Applications)
  {
    m_Interface.Call(&User::CancelApplicationInternal, user.second.m_UserKey, m_Interface.GetLocalKey());
  }

  for (auto user : m_Data.m_DatabaseInfo.m_Requests)
  {
    m_Interface.Call(&User::CancelSquadRequestInternal, user.second.m_UserKey, m_Interface.GetLocalKey());
  }

  m_Interface.DestroySelf();
}

void Squad::BeginLoad()
{
  for (auto user : m_Data.m_DatabaseInfo.m_Users)
  {
    m_PendingMemberLoads++;
    m_Interface.CreateDataSubscription(DDSSubscriptionTarget<User>{}, user.second.m_UserKey, ".m_UserName", &Squad::HandleMemberLoad, false, (int)user.first);

    printf("Loading member %llu for squad %s\n", (DDSKey)user.second.m_UserKey, m_SquadInfo.m_Name.c_str());
  }

  for (auto user : m_Data.m_DatabaseInfo.m_Applications)
  {
    m_PendingApplicationLoads++;
    m_Interface.CreateDataSubscription(DDSSubscriptionTarget<User>{}, user.second.m_UserKey, ".m_UserName", &Squad::HandleApplicationLoad, false, (int)user.first);
  }

  for (auto user : m_Data.m_DatabaseInfo.m_Requests)
  {
    m_PendingRequestLoads++;
    m_Interface.CreateDataSubscription(DDSSubscriptionTarget<User>{}, user.second.m_UserKey, ".m_UserName", &Squad::HandleRequestLoad, false, (int)user.first);
  }

  CheckCompleteLoad();
}

void Squad::CheckCompleteLoad()
{
  if (m_PendingMemberLoads == 0 && m_PendingApplicationLoads == 0 && m_PendingRequestLoads == 0)
  {
    m_Interface.FinalizeObjectLoad();
  }
}

void Squad::HandleMemberLoad(int member_index, std::string name)
{
  SquadMember squad_member;
  squad_member.m_UserKey = m_Data.m_DatabaseInfo.m_Users[member_index].m_UserKey;
  squad_member.m_MembershipFlags = m_Data.m_DatabaseInfo.m_Users[member_index].m_MembershipFlags;
  squad_member.m_Joined = m_Data.m_DatabaseInfo.m_Users[member_index].m_Joined;
  StormReflParseJson(squad_member.m_Name, name.c_str());

  printf("Got member infor %llu for squad %s\n", (DDSKey)m_Data.m_DatabaseInfo.m_Users[member_index].m_UserKey, m_SquadInfo.m_Name.c_str());

  m_SquadInfo.m_Users.EmplaceAt(member_index, squad_member);

  if (m_PendingMemberLoads)
  {
    m_PendingMemberLoads--;
    CheckCompleteLoad();
  }
}

void Squad::HandleApplicationLoad(int member_index, std::string name)
{
  SquadApplication squad_app;
  squad_app.m_UserKey = m_Data.m_DatabaseInfo.m_Applications[member_index].m_UserKey;
  StormReflParseJson(squad_app.m_UserName, name.c_str());

  m_SquadInfo.m_Applicants.InsertAt(member_index, squad_app);

  if (m_PendingApplicationLoads)
  {
    m_PendingApplicationLoads--;
    CheckCompleteLoad();
  }
}

void Squad::HandleRequestLoad(int member_index, std::string name)
{
  SquadApplication squad_app;
  squad_app.m_UserKey = m_Data.m_DatabaseInfo.m_Requests[member_index].m_UserKey;
  StormReflParseJson(squad_app.m_UserName, name.c_str());

  m_SquadInfo.m_Requests.InsertAt(member_index, squad_app);

  if (m_PendingRequestLoads)
  {
    m_PendingRequestLoads--;
    CheckCompleteLoad();
  }
}

int Squad::GetSquadMemberFlags(DDSKey user_id)
{
  for (auto user : m_Data.m_DatabaseInfo.m_Users)
  {
    if (user.second.m_UserKey == user_id)
    {
      return user.second.m_MembershipFlags;
    }
  }

  return kSquadNonMember;
}

void Squad::PutUserInSquad(DDSKey user_key, std::string user_name, int member_flags)
{
  for (auto user : m_Data.m_DatabaseInfo.m_Requests)
  {
    if (user.second.m_UserKey == user_key)
    {
      m_Data.m_DatabaseInfo.m_Requests.RemoveAt(user.first);
      m_SquadInfo.m_Requests.RemoveAt(user.first);

      m_Interface.Call(&User::CancelSquadRequestInternal, user_key, m_Interface.GetLocalKey());
      break;
    }
  }

  for (auto user : m_Data.m_DatabaseInfo.m_Applications)
  {
    if (user.second.m_UserKey == user_key)
    {
      m_Data.m_DatabaseInfo.m_Applications.RemoveAt(user.first);
      m_SquadInfo.m_Applicants.RemoveAt(user.first);

      m_Interface.Call(&User::CancelApplicationInternal, user_key, m_Interface.GetLocalKey());
      break;
    }
  }

  int join_time = (int)time(nullptr);

  SquadMember new_member;
  new_member.m_MembershipFlags = member_flags;
  new_member.m_Name = user_name;
  new_member.m_UserKey = user_key;
  new_member.m_Joined = join_time;
  m_SquadInfo.m_Users.EmplaceBack(new_member);

  SquadDatabaseMemberInfo db_member;
  db_member.m_MembershipFlags = 0;
  db_member.m_UserKey = user_key;
  db_member.m_Joined = join_time;
  m_Data.m_DatabaseInfo.m_Users.EmplaceBack(db_member);

  m_Interface.Call(&User::AddSquadInternal, user_key, m_Interface.GetLocalKey());
  m_Interface.Call(&User::JoinChannel, user_key, 0, m_SquadInfo.m_Tag.ToString());

  std::string welcome = std::string("You are now in the squad ") + m_SquadInfo.m_Name.ToString();
  m_Interface.Call(&User::SendNotification, user_key, welcome);
}

void Squad::UpdateMotd(std::string motd)
{
  m_SquadInfo.m_Motd.SetIfDifferent(motd);
  m_Data.m_DatabaseInfo.m_Motd.SetIfDifferent(motd);
}

void Squad::GetInfo(DDSResponder & responder)
{
  std::string info = "Info for squad " + m_SquadInfo.m_Name.ToString() + "\n";
  StormReflEncodePrettyJson(m_SquadInfo, info);
  info += "\nDatabase Info\n";
  StormReflEncodePrettyJson(m_Data.m_DatabaseInfo, info);
  DDSResponderCall(responder, info);
}
