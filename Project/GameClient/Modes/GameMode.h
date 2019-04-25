#pragma once


#include "Engine/Rendering/RenderState.h"
#include "Engine/Asset/AssetBundle.h"

class GameContainer;

class GameMode
{
public:

  explicit GameMode(GameContainer & game);
  virtual ~GameMode();

  virtual void Initialize();
  virtual void OnAssetsLoaded();
  virtual void InputEvent();

  virtual void Update();
  virtual void Render();

  virtual bool IsLoaded();

  bool AssetLoadingComplete();
  void Step();

protected:

  GameContainer & GetContainer();
  AssetBundle & GetAssets();

private:
  GameContainer & m_GameContainer;

  bool m_Loaded;
  AssetBundle m_Assets;
};
