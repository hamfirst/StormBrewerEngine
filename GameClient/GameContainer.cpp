
#include "GameClient/GameContainer.h"
#include "GameClient/GameModeTestSprite.h"

#include "Engine/Text/TextManager.h"


GameContainer::GameContainer(const Window & window) :
  m_LevelList(),
  m_Window(window)
{
  auto resolution = m_Window.GetSize();
  m_RenderState.InitRenderState(resolution.x, resolution.y);
  m_RenderState.EnableBlendMode();

  m_RenderUtil.SetClearColor(Color(100, 149, 237, 255));
  m_RenderUtil.LoadShaders();

  m_Mode = std::make_unique<GameModeTestSprite>(*this);
  m_Mode->Initialize(*this);
}

GameContainer::~GameContainer()
{

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