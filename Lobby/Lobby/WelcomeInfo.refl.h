#pragma once

#include <HurricaneDDS/DDSDataObject.h>

<<<<<<< HEAD
=======
#include "LobbyConfig.h"

#ifdef ENABLE_WELCOME_INFO

>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
struct WelcomeInfoTab
{
  STORM_DATA_DEFAULT_CONSTRUCTION(WelcomeInfoTab);
  RString m_Name;
  RString m_Info;
};

struct WelcomeInfo
{
public:
  DDS_SHARED_OBJECT;

  WelcomeInfo(DDSObjectInterface & obj_interface);

  void STORM_REFL_FUNC UpdateInfo(DDSResponder & responder, std::string tab_name, std::string info);
  void STORM_REFL_FUNC RemoveTab(DDSResponder & responder, std::string tab_name);
  void STORM_REFL_FUNC FetchWelcomeInfo(DDSResponder & responder);

private:

  void Save();

public:

  RMergeList<WelcomeInfoTab> m_Tabs;


private:

  STORM_REFL_IGNORE DDSObjectInterface & m_Interface;
};
<<<<<<< HEAD
=======

#endif
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
