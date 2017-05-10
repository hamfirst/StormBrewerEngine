
#include <iostream>
#include <vector>
#include <functional>

#include <SDL2/SDL.h>

#include <gl3w/gl3w.h>

#undef main
#undef max
#undef min

#include "Foundation/Common.h"
#include "Foundation/Delegate/Delegate.h"
#include "Foundation/Network/Network.h"
#include "Foundation/Network/WebSocket.h"
#include "Foundation/Json/Json.h"

#include <StormData/StormDataJson.h>

#include "Engine/Engine.h"
#include "Engine/Asset/AssetLoader.h"
#include "Engine/Asset/TextureAsset.h"
#include "Engine/Text/TextManager.h"
#include "Engine/Rendering/Rendering.h"
#include "Engine/Rendering/RenderUtil.h"
#include "Engine/Input/InputState.h"
#include "Engine/Input/TextInputContext.h"
#include "Engine/Window/WindowManager.h"
#include "Engine/Shader/ShaderManager.h"
#include "Engine/Sprite/SpriteEngineData.h"
#include "Engine/Map/MapRender.h"
#include "Engine/Entity/EntityRender.h"
#include "Engine/Camera/Camera.h"

#include "Runtime/RuntimeState.h"
#include "Runtime/Entity/Entity.h"
#include "Runtime/Entity/EntityResource.h"
#include "Runtime/Sprite/SpriteResource.h"
#include "Runtime/Map/MapResource.h"
#include "Runtime/Mover/Mover.h"

#include "Shared/AssetBundle/AssetBundle.h"

#include "TestTypes.refl.meta.h"

#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "Imm32.lib")
#pragma comment(lib, "Version.lib")
#pragma comment(lib, "Opengl32.lib")


int crap()
{
  return 1;
}


struct S
{
  int blah()
  {
    return 1;
  }
};

int TestDelegate()
{
  S s;

  int x = 0;
  auto l = [&]() { return ++x; };

  int t = std::is_class<decltype(l)>::value;

  Delegate<int> del(&crap);
  Delegate<int> del2(&S::blah, &s);
  Delegate<int> del3(l);

  Delegate<int> del4(del);
  return del3.Call();
}

void TestWebsocket()
{
  NetworkInit();
  WebSocket ws("localhost", 27801, "/", "localhost");

  ws.SendString("test.png");
  auto response = ws.RecvPacket();

  NetworkShutdown();
}

void TestJson()
{
  Json json;

  TestType obj{};
  //obj.m_Sub.m_List.InsertAt(200, 1);
  obj.m_Sub.m_List.InsertAt(200, 4);

  std::string data = StormReflEncodeJson(obj);
  json.Parse(data.data());

  const char * test_data = "{\"m_Sub\":{\"m_List\":{\"+4\":null,\"3\":100}}}";
  Json test_additive;
  test_additive.Parse(test_data);

  std::string test_result;
  test_additive.EncodePretty(test_result);
  printf("%s\n", test_result.data());

  json.ApplyJson(test_additive);

  std::string result;
  json.EncodePretty(result);

  printf("%s\n", result.data());
}

static Vector2 cursor_pos;
static bool cursor_pressed;

void UpdateCursorPos(PointerState p)
{
  cursor_pos = p.m_Pos;
}

void UpdateButtonState(bool pressed)
{
  cursor_pressed = pressed;
  Box box = { { 50, 50 }, { 100, 100 } };
}

int main()
{
  //TestJson();

  EngineInit(true);

  auto window = g_WindowManager.CreateNewWindow("Window!", 1280, 720);
  window.MakeCurrent();

  EngineRenderInit();

  RenderState render_state;
  render_state.InitRenderState(1280, 720);

  RenderUtil render_util;
  render_util.SetClearColor(Color(100, 149, 237, 255));
  render_util.LoadShaders();

  auto texture = TextureAsset::Load("Images/test.png");
  g_TextManager.LoadFont("Fonts/arial.ttf", -1, 15);

  //g_AssetLoader.DisableNetworkLoading();

  auto & input_state = *window.GetInputState();
  input_state.BindBinaryControl(CreateMouseButtonBinding(kMouseRightButton), 0, ControlBindingMode::kIgnoreLowerPriority, { UpdateButtonState });
  input_state.BindPointerControl(CreateMousePointerBinding(), 0, ControlBindingMode::kIgnoreLowerPriority, { UpdateCursorPos });

  MouseState::SetCursorVisibility(false);

  auto input_context = window.CreateTextInputContext();
  input_context->MakeCurrent(nullptr);

  int frame = 0;

  RuntimeState runtime_state;

  AssetBundle bundle;
  bundle.LoadAsset<EntityResource>("./Entities/Entity.entity");
  bundle.LoadAsset<MapResource>("./Maps/Test.map");
  bool loaded = false;

  Camera camera(Vector2(480, 270));


  Entity * entity = nullptr;

  while (EngineWantsToQuit() == false)
  {
    EngineUpdate();

    RenderUtil::Clear();

    if (loaded == false && bundle.AllLoadedSuccessfully())
    {
      auto map = MapResource::Load("./Maps/Test.map");
      runtime_state.LoadMap(map.GetResource());

      auto entity_resource = EntityResource::Load("./Entities/Entity.entity");
      entity = runtime_state.CreateEntity(entity_resource.GetResource());
      entity->GetPosition().x = 30;
      entity->GetPosition().y = 100;
      loaded = true;
    }

    if(loaded)
    {
      Box move_box = { {-8, -20}, {8, 20} };
      entity->GetMoverState().m_Velocity.y -= 10;
      Mover::UpdateMover(entity, move_box, 0xF);

      entity->FrameAdvance(COMPILE_TIME_CRC32_STR("Idle"));

      camera.SetPosition(entity->GetPosition());
      //camera.DebugDraw(render_util, move_box, entity->GetPosition(), Color(255, 255, 0, 255));
      //camera.DebugDrawCollision(&runtime_state, 0, render_util, Color(255, 255, 255, 255));
    }

    if (texture->IsLoaded())
    {
      texture->GetTexture().BindTexture(0);
      render_util.DrawTexturedQuad(cursor_pos, Color(255, 255, 255, 255), texture->GetTexture(), render_state.GetScreenSize());
    }

    g_TextManager.SetTextPos(cursor_pos);
    //g_TextManager.RenderText(g_TextInputManager.GetCurrentInput().data(), -1, render_state);

    g_TextManager.SetTextPos(Vector2(0, 20));
    g_TextManager.RenderInputText(input_context, -1, render_state);
    window.Swap();
  }

  EngineCleanup();

  SDL_Quit();
  return 0;
}
