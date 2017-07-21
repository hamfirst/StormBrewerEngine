#pragma once


#include "Engine/Rendering/RenderState.h"
#include "Engine/Rendering/RenderUtil.h"
#include "Engine/Asset/AssetBundle.h"

class GameContainer;

class GameMode
{
public:

  GameMode(GameContainer & game);
  virtual ~GameMode();

  virtual void Initialize();
  virtual void OnAssetsLoaded();

  virtual void Update();
  virtual void Render();

  bool IsLoaded();
  void Step();

protected:

  GameContainer & GetContainer();
  AssetBundle & GetAssets();

private:
  GameContainer & m_GameContainer;

  bool m_Loaded;
  AssetBundle m_Assets;
};
