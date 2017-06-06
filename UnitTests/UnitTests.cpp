
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
#include "Foundation/Math/Intersection.h"

#include "StormData/StormDataJson.h"
#include "StormNet/NetReflectionFixedPoint.h"
#include "StormNet/NetReflectionFixedPointLUT.h"

#include "Engine/Engine.h"
#include "Engine/Asset/AssetLoader.h"
#include "Engine/Asset/TextureAsset.h"
#include "Engine/Text/TextManager.h"
#include "Engine/Rendering/Rendering.h"
#include "Engine/Rendering/RenderUtil.h"
#include "Engine/Rendering/GeometryVertexBufferBuilder.h"
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

  int a, b, c;
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

INIT_LUT_DATA(int, 32, 24);

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

  for (auto val : CreateFixedPointRange(NetFixedPoint<int, 32, 24>(1), 4))
  {
    printf("%f\n", (float)val);
  }

  using Fixed = NetFixedPoint<int, 32, 24>;
  Intersection<Fixed>::VecType vec(5, 5);

  float init_val = 0.78215f;
  auto s = cosf(init_val);

  Camera camera(Vector2(480, 270));

  VertexBuffer draw_buffer(true);

  Entity * entity = nullptr;

  RenderVec2 start = { 50, 30 };
  RenderVec2 end = { 30, 10 };

  auto line = Intersection<float>::CollisionLine(start, end);
  auto circle = Intersection<float>::CollisionCircle(start, 4.0f);

  RenderVec2 cursor_start = { 0, 10 };
  RenderVec2 cursor_end = { 0, 10 };

  while (EngineWantsToQuit() == false)
  {
    EngineUpdate();

    RenderUtil::Clear();
    GeometryVertexBufferBuilder builder;

    auto pointer_state = input_state.GetPointerState();
    cursor_end = camera.TransformFromScreenSpaceToWorldSpace(pointer_state.m_Pos, render_state, render_util);

    if (input_state.GetMouseButtonState(1))
    {
      cursor_start = cursor_end;
    }

    auto sweep = Intersection<float>::CollisionLine(cursor_start, cursor_end);
    builder.Line(start, end, 1.0f, Color(0.0f, 0.0f, 1.0f, 1.0f));

    IntersectionResult<Intersection<float>::VecType> result;
    if (Intersection<float>::SweptCircleToSweptCircleTest(sweep, line, circle.m_Radius * 2, result))
    {
      builder.Line(cursor_start, cursor_end, circle.m_Radius * 2 + 1.0f, Color(1.0f, 1.0f, 1.0f, 1.0f));
      builder.FilledCircle(cursor_start, circle.m_Radius + 1.0f, Color(1.0f, 1.0f, 1.0f, 1.0f), 20);
      builder.FilledCircle(cursor_end, circle.m_Radius + 1.0f, Color(1.0f, 1.0f, 1.0f, 1.0f), 20);
    }
    //builder.FilledCircle(start, circle.m_Radius, Color(1.0f, 1.0f, 0.0f, 1.0f), 20);
    builder.Line(cursor_start, cursor_end, circle.m_Radius * 2, Color(0.0f, 0.0f, 1.0f, 1.0f));
    builder.FilledCircle(cursor_start, circle.m_Radius, Color(0.0f, 0.0f, 1.0f, 1.0f), 20);
    builder.FilledCircle(cursor_end, circle.m_Radius, Color(0.0f, 0.0f, 1.0f, 1.0f), 20);

    builder.FillVertexBuffer(draw_buffer);

    auto & shader = g_ShaderManager.GetDefaultShader();

    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_ScreenSize"), camera.GetResolution());
    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), camera.GetPosition());
    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), RenderVec4{ 1, 0, 0, 1 });
    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), RenderVec4{ 1, 1, 1, 1 });
    shader.Bind();

    render_util.GetDefaultTexture().BindTexture(0);

    draw_buffer.Bind();
    draw_buffer.CreateDefaultBinding(shader);
    draw_buffer.Draw();

    /*
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

    */
    window.Swap();
  }

  EngineCleanup();

  SDL_Quit();
  return 0;
}
