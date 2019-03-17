

#include <HurricaneDDS/DDSDatabaseConnection.h>
#include <HurricaneDDS/DDSResponderCall.h>

#include <StormData/StormDataJson.h>

#include "WelcomeInfo.refl.meta.h"

#ifdef ENABLE_WELCOME_INFO

STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(WelcomeInfoTab);

WelcomeInfo::WelcomeInfo(DDSObjectInterface & obj_interface) :
  m_Interface(obj_interface)
{

}

void WelcomeInfo::Initialize()
{
  StormReflParseJson(m_Tabs, m_Interface.QueryDatabaseSingleton("welcome_info").c_str());

  if (m_Tabs.HighestIndex() == -1)
  {
    WelcomeInfoTab default_tab;
    default_tab.m_Name = "Welcome";
    default_tab.m_Info = "<iframe width=\"100%\" height=\"100%\" src=\"https://www.youtube.com/embed/mzBfvQfiRcQ\" frameborder=\"0\" allowfullscreen></iframe>";

    m_Tabs.EmplaceBack(default_tab);
  }
}

void WelcomeInfo::UpdateInfo(DDSResponder & responder, std::string tab_name, std::string info)
{
  for (auto tab : m_Tabs)
  {
    if (tab_name == tab.second.m_Name.ToString())
    {
      tab.second.m_Info = info;

      Save();
      DDSResponderCall(responder, "Welcome info updated");
      return;
    }
  }

  WelcomeInfoTab default_tab;
  default_tab.m_Name = tab_name;
  default_tab.m_Info = info;

  m_Tabs.EmplaceBack(default_tab);

  Save();
  DDSResponderCall(responder, "Welcome info updated");
}

void WelcomeInfo::RemoveTab(DDSResponder & responder, std::string tab_name)
{
  for (auto tab : m_Tabs)
  {
    if (tab_name == tab.second.m_Name.ToString())
    {
      m_Tabs.RemoveAt(tab.first);

      Save();
      DDSResponderCall(responder, "Tab removed");
      return;
    }
  }

  DDSResponderCall(responder, "Tab not found");
}


void WelcomeInfo::FetchWelcomeInfo(DDSResponder & responder)
{
  DDSResponderCall(responder, m_Tabs[0].m_Info.ToString());
}

void WelcomeInfo::Save()
{
  m_Interface.UpsertDatabaseSingleton("welcome_info", StormReflEncodeJson(m_Tabs).data());
}

#endif
