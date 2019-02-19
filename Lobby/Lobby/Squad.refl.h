#pragma once

#include <StormData/StormData.h>
#include <StormData/StormDataTypes.h>

#include <HurricaneDDS/DDSDataObject.h>
#include <HurricaneDDS/DDSThrottle.refl.h>

#include "SharedTypes.refl.h"

static const int kSquadNonMember = 0;
static const int kSquadHonoraryMember = 1;
static const int kSquadMember = 2;
static const int kSquadLeader = 3;
static const int kSquadManager = 4;
static const int kSquadCreator = 5;

struct SquadDatabaseMemberInfo
{
  STORM_DATA_DEFAULT_CONSTRUCTION(SquadDatabaseMemberInfo);

  RKey m_UserKey;
  RInt m_Joined;
  RInt m_MembershipFlags;
};

struct SquadDatabaseApplicantInfo
{
  STORM_DATA_DEFAULT_CONSTRUCTION(SquadDatabaseApplicantInfo);

  RKey m_UserKey;
};

struct SquadDatabaseInfo
{
  STORM_DATA_DEFAULT_CONSTRUCTION(SquadDatabaseInfo);

  RString m_Name;
  RString m_Tag;

  RString m_Motd;

  RBool m_Locked;

  RMergeList<SquadDatabaseMemberInfo> m_Users;

  RMergeList<SquadDatabaseApplicantInfo> m_Applications;
  RMergeList<SquadDatabaseApplicantInfo> m_Requests;
};

struct SquadDatabaseObject
{
  DDS_DATABASE_OBJECT(Squad);

  STORM_REFL_ATTR(UniqueIndex) RString m_SquadNameLower;
  STORM_REFL_ATTR(UniqueIndex) RString m_SquadTagLower;

  DDSKey m_Creator;

  SquadDatabaseInfo m_DatabaseInfo;
};

struct Squad
{
public:
  DDS_DATA_OBJECT(DDSDataObjectPriority::kLow);
  Squad(DDSNodeInterface node_interface, SquadDatabaseObject & db_object);

public:

  void BeginLoad();
  void CheckCompleteLoad();

public:

  void STORM_REFL_FUNC ApplyToSquad(DDSResponder & responder, DDSKey user_id, std::string user_name);
  void STORM_REFL_FUNC AcceptApplicationToSquad(DDSResponder & responder, DDSKey user_source, DDSKey user_id);
  void STORM_REFL_FUNC DeclineApplicationToSquad(DDSResponder & responder, DDSKey user_source, DDSKey user_id);
  void STORM_REFL_FUNC RescindApplicationToSquad(DDSResponder & responder, DDSKey user_id);

  void STORM_REFL_FUNC RequestUserToJoinSquad(DDSResponder & responder, DDSKey user_source, DDSKey user_id, std::string user_name);
  void STORM_REFL_FUNC AcceptRequestToJoinSquad(DDSResponder & responder, DDSKey user_id);
  void STORM_REFL_FUNC DeclineRequestToJoinSquad(DDSResponder & responder, DDSKey user_id);
  void STORM_REFL_FUNC RescindRequestToJoinSquad(DDSResponder & responder, DDSKey user_source, DDSKey user_id);

  void STORM_REFL_FUNC LeaveSquad(DDSResponder & responder, DDSKey user_id);
  void STORM_REFL_FUNC RemoveMember(DDSResponder & responder, DDSKey user_source, DDSKey user_id);

  void STORM_REFL_FUNC SetMemberPermissions(DDSResponder & responder, DDSKey user_source, DDSKey user_id, int member_permissions);
  void STORM_REFL_FUNC SetMotd(DDSResponder & responder, DDSKey user_source, std::string motd);
  void STORM_REFL_FUNC SetChannelLock(DDSResponder & responder, DDSKey user_source, bool locked);

  void STORM_REFL_FUNC GetSquadName(DDSResponder & responder);
  void STORM_REFL_FUNC KillSquad(DDSResponder & responder);
  void STORM_REFL_FUNC DestroySquad();


  void STORM_REFL_FUNC HandleMemberLoad(int member_index, std::string name);
  void STORM_REFL_FUNC HandleApplicationLoad(int member_index, std::string name);
  void STORM_REFL_FUNC HandleRequestLoad(int member_index, std::string name);

  void STORM_REFL_FUNC UpdateMotd(std::string motd);
  void STORM_REFL_FUNC GetInfo(DDSResponder & responder);

public:

  int GetSquadMemberFlags(DDSKey user_key);
  void PutUserInSquad(DDSKey user_id, std::string name, int member_flags);

public:

  DDSThrottle m_ChangeThrottle;

  SquadInfo m_SquadInfo;

  int m_PendingMemberLoads = 0;
  int m_PendingApplicationLoads = 0;
  int m_PendingRequestLoads = 0;



private:
  STORM_REFL_IGNORE DDSNodeInterface m_Interface;
  STORM_REFL_IGNORE SquadDatabaseObject & m_Data;
};
