
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
#include "Foundation/Json/JsonSchemaSerialize.h"


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
  auto schema = GetJsonSchema<TestType>();
  auto schema_data = SerializeJsonSchema(schema);

  std::unique_ptr<JsonSchema[]> schema_list;
  std::unique_ptr<JsonChildSchemaList[]> child_list;

  auto backup_schema = DeserializeJsonSchema(schema_data, schema_list, child_list);

  Json json(schema);

  TestType obj{};
  //obj.m_Sub.m_List.InsertAt(200, 1);
  obj.m_Sub.m_List.InsertAt(200, 4);

  std::string data = StormReflEncodeJson(obj);
  std::vector<std::pair<std::string, std::string>> schema_errors;
  json.Parse(data.data(), schema_errors);

  const char * test_data = "{\"m_Sub\":{\"m_List\":{\"+4\":null,\"3\":100}}}";
  Json test_additive(schema);
  test_additive.Parse(test_data, schema_errors);

  std::string test_result;
  test_additive.EncodePretty(test_result);
  printf("%s\n", test_result.data());

  json.ApplyJson(test_additive);
  json.RevertDataAtPath(".m_Sub.m_List[3]");
  json.RevertDataAtPath(".m_Int");

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
  TestJson();

  EngineInit(true);

  auto window = g_WindowManager.CreateNewWindow("Window!", 1280, 720);

  EngineRenderInit();

  RenderState render_state;
  render_state.InitRenderState(1280, 720);

  RenderUtil render_util;
  render_util.LoadShaders();

  auto texture = TextureAsset::Load("Images/test.png");
  g_TextManager.LoadFont("Fonts/arial.ttf", -1, 15);

  g_AssetLoader.DisableNetworkLoading();

  auto & input_state = *window.GetInputState();
  input_state.BindBinaryControl(CreateMouseButtonBinding(kMouseRightButton), 0, ControlBindingMode::kIgnoreLowerPriority, { UpdateButtonState });
  input_state.BindPointerControl(CreateMousePointerBinding(), 0, ControlBindingMode::kIgnoreLowerPriority, { UpdateCursorPos });

  MouseState::SetCursorVisibility(false);

  auto input_context = window.CreateTextInputContext();
  input_context->MakeCurrent(nullptr);

  while (EngineWantsToQuit() == false)
  {
    EngineUpdate();

    RenderUtil::Clear();

    if (texture->IsLoaded())
    {
      texture->GetTexture().BindTexture(0);
      render_util.DrawTexturedQuad(cursor_pos, Color(255, 255, 255, 255), texture->GetTexture(), render_state, false);
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
