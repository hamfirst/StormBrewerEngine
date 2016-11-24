
#include <iostream>
#include <vector>
#include <functional>

#include "Foundation/Common.h"
#include "Foundation/Delegate/Delegate.h"
#include "Foundation/Network/Network.h"
#include "Foundation/Network/WebSocket.h"

#include <SDL/SDL.h>
#undef main

#include <gl3w/gl3w.h>

#include "Engine/Engine.h"
#include "Engine/Asset/TextureAsset.h"
#include "Engine/Text/TextManager.h"
#include "Engine/Rendering/Rendering.h"

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

int main()
{
  NetworkInit();
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK) < 0)
  {
    fprintf(stderr, "Could not start SDL");
    return 0;
  }

  auto window = SDL_CreateWindow("Window!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
  auto context = SDL_GL_CreateContext(window);

  EngineInit();

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

  auto texture = TextureAsset::Load("test.png");

  g_TextManager.LoadFont("C:\\Windows\\Fonts\\arial.ttf", -1, 15);

  while (EngineWantsToQuit() == false)
  {
    EngineUpdate();

    shader.Bind();
    ar.Bind();

    if (texture.Resolve()->IsLoaded())
    {
      //texture.Resolve()->GetTexture().BindTexture(0);
      shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Texture"), 0);
    }

    buffer.Draw();

    ar.Unbind();
    shader.Unbind();

    g_TextManager.RenderText("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890*&`", -1, Color(0, 0, 255, 255), Vector2(0, 10), render_state);

    SDL_GL_SwapWindow(window);
  }

  EngineCleanup();

  SDL_Quit();
  NetworkShutdown();

  return 0;
}
