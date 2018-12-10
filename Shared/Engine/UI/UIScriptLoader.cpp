
#include "Engine/UI/UIScriptLoader.h"
#include "Engine/Text/TextManager.h"

#include "Runtime/BinaryResource/GenericBinaryResource.h"

#include "Foundation/Script/ScriptInterface.h"
#include "Foundation/FileSystem/Directory.h"
#include "Foundation/FileSystem/File.h"

UIScriptLoader::UIScriptLoader(NotNullPtr<ScriptState> script_state)
{
  m_State = kIdle;
  m_ScriptState = script_state;
}

void UIScriptLoader::InitLoad()
{
  m_State = kLoadingScripts;

  auto old_scripts = std::move(m_ScriptResources);

  auto script_files = GetFilesInDirectory("./UIs/Scripts/Init", "lua");
  for(auto & script_file : script_files)
  {
    m_ScriptResources.emplace_back(GenericBinaryResource::Load(script_file.c_str()));
  }

  script_files = GetFilesInDirectory("./UIs/Scripts", "lua");
  for(auto & script_file : script_files)
  {
    m_ScriptResources.emplace_back(GenericBinaryResource::Load(script_file.c_str()));
  }
}

void UIScriptLoader::Update()
{
  switch(m_State)
  {
    default:
    case kIdle:
    case kComplete:
      break;
    case kLoadingScripts:
      if(AllScriptsLoaded())
      {
        auto old_textures = std::move(m_TextureAssets);
        auto old_audio = std::move(m_AudioAssets);
        auto old_music = std::move(m_MusicAssets);
        auto old_fonts = std::move(m_FontAssets);
        auto old_atlases = std::move(m_AtlasAssets);
        auto old_sprites = std::move(m_SpriteAssets);

        for(auto & script_file : m_ScriptResources)
        {
          m_ScriptState->LoadScript(script_file->GetData(), script_file->GetLength(), script_file->GetFileName());
        }

        ScriptInterface loader_interface(m_ScriptState);

        loader_interface.AddFunction("LoadTexture",
                                     CreateDelegateFromLambda([this](std::string path){ LoadTexture(path); }));
        loader_interface.AddFunction("LoadAudio",
                                     CreateDelegateFromLambda([this](std::string path){ LoadAudio(path); }));
        loader_interface.AddFunction("LoadMusic",
                                     CreateDelegateFromLambda([this](std::string path){ LoadMusic(path); }));
        loader_interface.AddFunction("LoadFont",
                                     CreateDelegateFromLambda([this](std::string path){ LoadFont(path); }));
        loader_interface.AddFunction("LoadAtlas",
                                     CreateDelegateFromLambda([this](std::string path){ LoadAtlas(path); }));
        loader_interface.AddFunction("LoadSprite",
                                     CreateDelegateFromLambda([this](std::string path){ LoadSprite(path); }));

        m_ScriptState->Call("LoadAssets", { loader_interface.GetObject() });
        m_State = kLoadingAssets;
      }
      break;
    case kLoadingAssets:
      if(AllAssetsLoaded())
      {
        m_State = kComplete;
      }
      break;
  }
}

bool UIScriptLoader::AllScriptsLoaded() const
{
  for(auto & asset : m_ScriptResources)
  {
    if(asset.IsLoaded() == false)
    {
      return false;
    }
  }

  return true;
}

bool UIScriptLoader::AllAssetsLoaded() const
{
  for(auto & asset : m_TextureAssets)
  {
    if(asset.IsLoaded() == false)
    {
      return false;
    }
  }

  for(auto & asset : m_AudioAssets)
  {
    if(asset.IsLoaded() == false)
    {
      return false;
    }
  }

  for(auto & asset : m_MusicAssets)
  {
    if(asset.IsLoaded() == false)
    {
      return false;
    }
  }

  for(auto & asset : m_FontAssets)
  {
    if(asset.IsLoaded() == false)
    {
      return false;
    }
  }

  for(auto & asset : m_AtlasAssets)
  {
    if(asset.IsLoaded() == false)
    {
      return false;
    }
  }

  for(auto & asset : m_SpriteAssets)
  {
    if(asset.IsLoaded() == false)
    {
      return false;
    }
  }

  return true;
}

bool UIScriptLoader::Complete() const
{
  return m_State == kComplete;
}

int UIScriptLoader::LoadTexture(std::string path)
{
  int id = static_cast<int>(m_TextureAssets.size());
  m_TextureAssets.emplace_back(TextureAsset::Load(path.data()));
  return id;
}

int UIScriptLoader::LoadAudio(std::string path)
{
  int id = static_cast<int>(m_AudioAssets.size());
  m_AudioAssets.emplace_back(AudioAsset::Load(path.data()));
  return id;
}

int UIScriptLoader::LoadMusic(std::string path)
{
  int id = static_cast<int>(m_MusicAssets.size());
  m_MusicAssets.emplace_back(MusicAsset::Load(path.data()));
  return id;
}

int UIScriptLoader::LoadFont(std::string path)
{
  int id = static_cast<int>(m_FontAssets.size());
  m_FontAssets.emplace_back(FontAsset::Load(path.data()));
  return id;
}

int UIScriptLoader::LoadAtlas(std::string path)
{
  int id = static_cast<int>(m_AtlasAssets.size());
  m_AtlasAssets.emplace_back(AtlasResource::Load(path.data()));
  return id;
}

int UIScriptLoader::LoadSprite(std::string path)
{
  int id = static_cast<int>(m_AudioAssets.size());
  m_SpriteAssets.emplace_back(SpriteResource::Load(path.data()));
  return id;
}
