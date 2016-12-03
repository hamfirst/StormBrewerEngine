
#include <iostream>
#include <vector>
#include <functional>

#include <SDL/SDL.h>

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
#include "Engine/Asset/TextureAsset.h"
#include "Engine/Text/TextManager.h"
#include "Engine/Rendering/Rendering.h"
#include "Engine/Input/InputState.h"
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

int main()
{
  TestJson();

  EngineInit();

  auto window = g_WindowManager.CreateNewWindow("Window!", 1280, 720);

  EngineRenderInit();

  InputState input_state;

  const char * test_vshader = SHADER_LITERAL(
    attribute vec2 a_Position;
    attribute vec2 a_TexCoord;

    varying vec2 v_TexCoord;

    void main()
    {
      v_TexCoord = a_TexCoord;
      gl_Position = vec4(a_Position, 0, 1);
    }
  );

  const char * test_fshader = SHADER_LITERAL(

    uniform sampler2D u_Texture;

    varying vec2 v_TexCoord;

    void main()
    {
      vec4 color = texture2D(u_Texture, v_TexCoord);
      gl_FragColor = color + vec4(0.1, 0.1, 0.1, 0);
    }
  );

  RenderState render_state;
  render_state.InitRenderState(1280, 720);

  ShaderProgram shader = MakeQuickShaderProgram(test_vshader, test_fshader);
  QuadVertexBufferBuilder builder;
  builder.AddQuad(QuadVertexBuilderInfo{ {Vector2(-1, -1), Vector2(1,1)}, {Vector2(0, 0), Vector2(1, 1)}, Vector2(1,1), Color(1,1,1,1) });
  auto buffer = builder.CreateVertexBuffer();

  VertexArray ar;
  ar.CreateDefaultBinding(shader, buffer);

  auto texture = TextureAsset::Load("Images/test.png");

  g_TextManager.LoadFont("Fonts/arial.ttf", -1, 15);

  while (EngineWantsToQuit() == false)
  {
    EngineUpdate();

    shader.Bind();
    ar.Bind();

    if (texture.Resolve()->IsLoaded())
    {
      texture.Resolve()->GetTexture().BindTexture(0);
      shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Texture"), 0);
    }

    buffer.Draw();

    ar.Unbind();
    shader.Unbind();

    g_TextManager.RenderText("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890*&`", -1, Color(0, 0, 255, 255), Vector2(0, 10), render_state);
    window.Swap();
  }

  EngineCleanup();

  SDL_Quit();
  NetworkShutdown();

  return 0;
}
