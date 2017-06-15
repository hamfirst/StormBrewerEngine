#pragma once

#include "Shared/AssetBundle/AssetBundle.h"

#include "Engine/Rendering/RenderState.h"
#include "Engine/Rendering/RenderUtil.h"

class GameContainer;

class GameMode
{
public:

  GameMode();
  ~GameMode();

  virtual void Initialize(GameContainer & container);
  virtual void OnAssetsLoaded(GameContainer & container);

  virtual void Update(GameContainer & container);
  virtual void Render(GameContainer & container);

  bool IsLoaded();
  void Step(GameContainer & container);

protected:

  AssetBundle & GetAssets();

private:

  bool m_Loaded;
  AssetBundle m_Assets;
};
