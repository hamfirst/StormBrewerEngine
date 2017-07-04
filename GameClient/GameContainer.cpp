
#include "GameClient/GameContainer.h"
#include "GameClient/GameModeLogo.h"
#include "GameClient/GameNetworkClient.h"

#include "Engine/Text/TextManager.h"


GameContainer::GameContainer(const Window & window) :
  m_EngineState(this),
  m_LevelList(),
  m_Window(window)
{
  auto resolution = m_Window.GetSize();
  m_RenderState.InitRenderState(resolution.x, resolution.y);
  m_RenderState.EnableBlendMode();

  m_RenderUtil.SetClearColor(Color(100, 149, 237, 255));
  m_RenderUtil.LoadShaders();

  SetInitialMode();
}

GameContainer::~GameContainer()
{

}

void GameContainer::SetInitialMode()
{
  m_Mode = std::make_unique<GameModeLogo>();
  m_Mode->Initialize(*this);
}

EngineState & GameContainer::GetEngineState()
{
  return m_EngineState;
}

Window & GameContainer::GetWindow()
{
  return m_Window;
}

GameLevelList & GameContainer::GetLevelList()
{
  return m_LevelList;
}

RenderState & GameContainer::GetRenderState()
{
  return m_RenderState;
}

RenderUtil & GameContainer::GetRenderUtil()
{
  return m_RenderUtil;
}

void GameContainer::StartNetworkClient(const char * remote_ip, int remote_port)
{
  m_Client = std::make_unique<GameNetworkClient>(*this, remote_ip, remote_port);
}

void GameContainer::StopNetworkClient()
{
  m_Client.reset();
}

GameNetworkClient & GameContainer::GetClient()
{
  ASSERT(m_Client, "Attempting to get client when network client has not been started");
  return *m_Client.get();
}

bool GameContainer::AllGlobalResourcesLoaded()
{
  return m_LevelList.IsLevelListLoaded() && m_GlobalResources.AreAllAssetsLoaded();
}

void GameContainer::Update()
{
  if (m_Mode)
  {
    m_Mode->Step(*this);
  }
}

void GameContainer::Render()
{
  if (m_Mode)
  {
    m_Mode->Render(*this);
  }
  else
  {
    m_RenderUtil.Clear();
    g_TextManager.SetTextPos(Vector2(20, 20));
    g_TextManager.RenderText("No mode set", -1, m_RenderState);
  }

  m_Window.Swap();
}
