
#include "Engine/UI/UIScriptLoader.h"
#include "Engine/Text/TextManager.h"

#include "Runtime/BinaryResource/GenericBinaryResource.h"

#include "Foundation/Script/ScriptInterface.h"
#include "Foundation/FileSystem/Directory.h"
#include "Foundation/FileSystem/File.h"
#include "Foundation/FileSystem/Path.h"

int UIScriptLoader::m_NextFontId = 100;

UIScriptLoader::UIScriptLoader(NotNullPtr<ScriptState> script_state) :
  m_LoaderInterface(script_state)
{
  m_State = kIdle;
  m_ScriptState = script_state;

  BIND_SCRIPT_INTERFACE(m_LoaderInterface, this, DebugPrint);
  BIND_SCRIPT_INTERFACE(m_LoaderInterface, this, LoadTexture);
  BIND_SCRIPT_INTERFACE(m_LoaderInterface, this, LoadAudio);
  BIND_SCRIPT_INTERFACE(m_LoaderInterface, this, LoadMusic);
  BIND_SCRIPT_INTERFACE(m_LoaderInterface, this, LoadFont);
  BIND_SCRIPT_INTERFACE(m_LoaderInterface, this, LoadAtlas);
  BIND_SCRIPT_INTERFACE(m_LoaderInterface, this, LoadSprite);

  m_ScriptState->SetGlobal("loader", m_LoaderInterface.GetObject());
}

void UIScriptLoader::InitLoad(bool immediate_load, Delegate<void> && load_complete_callback)
{

  auto old_scripts = std::move(m_ScriptResources);
  m_LoadCompleteCallback = std::move(load_complete_callback);

  if(immediate_load)
  {
    auto root_path = GetCanonicalRootPath();

    auto script_files = GetFilesInDirectory("./UIs/Scripts/Init", "lua");
    std::sort(script_files.begin(), script_files.end());
    for(auto & script_file : script_files)
    {
      auto script_binary_file = FileReadFull(GetFullPath(script_file, root_path).c_str());
      if(script_binary_file)
      {
        m_ScriptState->LoadScript(script_binary_file->Get(), script_binary_file->GetSize(), script_file.c_str());
      }
    }

    script_files = GetFilesInDirectory("./UIs/Scripts/Elements", "lua");
    std::sort(script_files.begin(), script_files.end());
    for(auto & script_file : script_files)
    {
      auto script_binary_file = FileReadFull(GetFullPath(script_file, root_path).c_str());
      if(script_binary_file)
      {
        m_ScriptState->LoadScript(script_binary_file->Get(), script_binary_file->GetSize(), script_file.c_str());
      }
    }

    script_files = GetFilesInDirectory("./UIs/Scripts/Custom", "lua");
    std::sort(script_files.begin(), script_files.end());
    for(auto & script_file : script_files)
    {
      auto script_binary_file = FileReadFull(GetFullPath(script_file, root_path).c_str());
      if(script_binary_file)
      {
        m_ScriptState->LoadScript(script_binary_file->Get(), script_binary_file->GetSize(), script_file.c_str());
      }
    }

    script_files = GetFilesInDirectory("./UIs/Scripts", "lua");
    std::sort(script_files.begin(), script_files.end());
    for(auto & script_file : script_files)
    {
      auto script_binary_file = FileReadFull(GetFullPath(script_file, root_path).c_str());
      if(script_binary_file)
      {
        m_ScriptState->LoadScript(script_binary_file->Get(), script_binary_file->GetSize(), script_file.c_str());
      }
    }

    m_State = kLoadingAssets;
    return;
  }

  m_State = kLoadingScripts;

  auto script_files = GetFilesInDirectory("./UIs/Scripts/Init", "lua");
  std::sort(script_files.begin(), script_files.end());
  for(auto & script_file : script_files)
  {
    m_ScriptResources.emplace_back(GenericBinaryResource::Load(script_file.c_str()));
  }

  script_files = GetFilesInDirectory("./UIs/Scripts/Elements", "lua");
  std::sort(script_files.begin(), script_files.end());
  for(auto & script_file : script_files)
  {
    m_ScriptResources.emplace_back(GenericBinaryResource::Load(script_file.c_str()));
  }

  script_files = GetFilesInDirectory("./UIs/Scripts/Custom", "lua");
  std::sort(script_files.begin(), script_files.end());
  for(auto & script_file : script_files)
  {
    m_ScriptResources.emplace_back(GenericBinaryResource::Load(script_file.c_str()));
  }

  script_files = GetFilesInDirectory("./UIs/Scripts", "lua");
  std::sort(script_files.begin(), script_files.end());
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
        for(auto & script_file : m_ScriptResources)
        {
          m_ScriptState->LoadScript(script_file->GetData(), script_file->GetLength(), script_file->GetFileName());
        }

        m_State = kLoadingAssets;
      }
      break;
    case kLoadingAssets:
      if(AllAssetsLoaded())
      {
        m_ScriptState->Call("FinalizeLoad", {});
        if(AllAssetsLoaded())
        {
          m_LoadCompleteCallback();
          m_State = kComplete;
        }
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

  if(g_TextManager.AllFontsLoaded() == false)
  {
    return false;
  }

  return true;
}

bool UIScriptLoader::Complete() const
{
  return m_State == kComplete;
}

void UIScriptLoader::DebugPrint()
{
  printf("Textures:\n");
  for(std::size_t index = 0, end = m_TextureAssets.size(); index < end; ++index)
  {
    auto & elem = m_TextureAssets[index];
    printf("%zd. %s\n", index, elem->GetFileName().c_str());
  }
  printf("\n");

  printf("Sounds:\n");
  for(std::size_t index = 0, end = m_AudioAssets.size(); index < end; ++index)
  {
    auto & elem = m_AudioAssets[index];
    printf("%zd. %s\n", index, elem->GetFileName().c_str());
  }
  printf("\n");

  printf("Music:\n");
  for(std::size_t index = 0, end = m_MusicAssets.size(); index < end; ++index)
  {
    auto & elem = m_MusicAssets[index];
    printf("%zd. %s\n", index, elem->GetFileName().c_str());
  }
  printf("\n");

  printf("Atlases:\n");
  for(std::size_t index = 0, end = m_AtlasAssets.size(); index < end; ++index)
  {
    auto & elem = m_AtlasAssets[index];
    printf("%zd. %s\n", index, elem->GetFileName());
  }
  printf("\n");

  printf("Sprites:\n");
  for(std::size_t index = 0, end = m_SpriteAssets.size(); index < end; ++index)
  {
    auto & elem = m_SpriteAssets[index];
    printf("%zd. %s\n", index, elem->GetFileName());
  }
  printf("\n");
}

int UIScriptLoader::LoadTexture(std::string path)
{
  int id = static_cast<int>(m_TextureAssets.size());
  m_TextureAssets.emplace_back(TextureAsset::Load(path.data()));
  return id | kTextureId;
}

int UIScriptLoader::LoadAudio(std::string path)
{
  int id = static_cast<int>(m_AudioAssets.size());
  m_AudioAssets.emplace_back(AudioAsset::Load(path.data()));
  return id | kAudioId;
}

int UIScriptLoader::LoadMusic(std::string path)
{
  int id = static_cast<int>(m_MusicAssets.size());
  m_MusicAssets.emplace_back(MusicAsset::Load(path.data()));
  return id | kMusicId;
}

int UIScriptLoader::LoadFont(std::string path, int size)
{
  auto test_font_id = g_TextManager.FindFontId(path.c_str(), size);
  if(test_font_id)
  {
    return test_font_id.Value() | kFontId;
  }

  g_TextManager.LoadFont(path.c_str(), m_NextFontId, size);
  auto id = m_NextFontId;
  m_NextFontId++;
  return id | kFontId;
}

int UIScriptLoader::LoadAtlas(std::string path)
{
  int id = static_cast<int>(m_AtlasAssets.size());
  m_AtlasAssets.emplace_back(AtlasResource::Load(path.data()));
  return id | kAtlasId;
}

int UIScriptLoader::LoadSprite(std::string path)
{
  int id = static_cast<int>(m_AudioAssets.size());
  m_SpriteAssets.emplace_back(SpriteResource::Load(path.data()));
  return id | kSpriteId;
}
