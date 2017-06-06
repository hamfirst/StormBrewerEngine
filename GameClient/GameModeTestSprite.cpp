
#include "GameClient/GameModeTestSprite.h"
#include "GameClient/GameContainer.h"

#include "Runtime/Entity/Entity.h"
#include "Runtime/Sprite/SpriteResource.h"

#include "Engine/Input/InputState.h"
#include "Engine/Asset/AudioAsset.h"
#include "Engine/Asset/MusicAsset.h"
#include "Engine/Audio/AudioManager.h"
#include "Engine/Shader/ShaderManager.h"

#include "SDL2/SDL_scancode.h"

#include <Windows.h>

GameModeTestSprite::GameModeTestSprite(GameContainer & container) :
  m_Camera(Vector2(320, 240), container.GetWindow().GetSize())
{

}

void GameModeTestSprite::Initialize(GameContainer & container)
{
  GetAssets().LoadAsset<SpriteResource>("./Sprites/Test.sprite", "sprite");
  GetAssets().LoadAsset<MusicAsset>("./Music/music.ogg", "music");
  GetAssets().LoadAsset<AudioAsset>("./Sounds/Dude3Death.wav", "sfx");
}

void GameModeTestSprite::OnAssetsLoaded(GameContainer & container)
{
  auto music = MusicAsset::Load("./Music/music.ogg");
  if (music)
  {
    //g_AudioManager.PlayMusic(music);
    GetAssets().PlaySoundEffect("sfx");
  }
}

void GameModeTestSprite::Update(GameContainer & container)
{
  auto input_state = container.GetWindow().GetInputState();
  if (input_state->GetKeyPressedThisFrame(SDL_SCANCODE_SPACE))
  {
    GetAssets().PlaySoundEffect("sfx");
    OutputDebugString("Playing sound\n");
  }
}

void GameModeTestSprite::Render(GameContainer & container)
{
  container.GetRenderUtil().Clear();

  m_Camera.SetScreenResolution(container.GetWindow().GetSize());

  if (IsLoaded())
  {
    auto sprite = GetAssets().GetSprite("sprite");
    if (sprite)
    {
      EntityRenderState render_state;
      render_state.m_AnimIndex = 0;

      auto input_state = container.GetWindow().GetInputState();
      if (input_state)
      {
        auto mouse_state = input_state->GetPointerState();
        auto screen_pos = m_Camera.TransformFromScreenSpaceToWorldSpace(mouse_state.m_Pos);

        auto & shader = g_ShaderManager.GetDefaultShader();
        shader.Bind();

        m_Camera.BootstrapShader(shader);

        if (mouse_state.m_InFocus)
        {
          container.GetRenderState().SyncBlendMode();
          sprite->Render(render_state, screen_pos);
        }
      }
    }
  }
}
