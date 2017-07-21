#pragma once

#include "Engine/Input/InputState.h"

class GameContainer;
class GameClientEventSender;

class RenderState;
class RenderUtil;

class GameCamera;
class Camera;

struct PointerState;

class GameClientInputManager
{
public:
  GameClientInputManager(GameContainer & container);
  ~GameClientInputManager();

  void Update();
  void Render();

  void HandleMouseMove(PointerState & pointer_state);
  void HandleClick(bool state);
  void HandleButtonPress(bool state, int button);

private:

  GameContainer & m_GameContainer;

  PointerControlHandle m_PointerHandle;
  BinaryControlHandle m_MouseButtonHandle;
  KeyboardPassthroughCallbackLink m_KeyboardCallbackLink;

  bool m_UIBlocking = false;
};

