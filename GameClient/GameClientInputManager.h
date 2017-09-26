#pragma once

#include "Engine/Input/InputState.h"

#include "Game/GameNetworkData.refl.h"

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

  void BindGamepad(int local_player_index, int gamepad_index);

  void HandleMouseMove(PointerState & pointer_state);
  void HandleClick(bool state);
  void HandleButtonPress(bool state, int button);

private:

  GameContainer & m_GameContainer;

  PointerControlHandle m_PointerHandle;
  BinaryControlHandle m_MouseButtonHandle;
  KeyboardPassthroughCallbackLink m_KeyboardCallbackLink;

  int m_GamepadBindings[kMaxPlayers];

  bool m_UIBlocking = false;

  uint8_t m_PrevControls;
};

