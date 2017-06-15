
#include "Foundation/Common.h"
#include "Foundation/Any/Any.h"
#include "Foundation/FileSystem/File.h"
#include "Foundation/Document/Document.h"
#include "Foundation/Document/DocumentCompiler.h"

#include "Runtime/Sprite/SpriteDef.refl.h"
#include "Runtime/Animation/AnimationState.h"
#include "Runtime/Map/MapDef.refl.h"
#include "Runtime/DocumentResource/DocumentResourceLoader.h"

#include "Shared/AssetBundle/AssetBundle.h"

#include <experimental/filesystem>

class DefaultDocumentAssetLoader : public DocumentLoader
{
public:
  virtual void LoadDocument(czstr path, uint64_t file_hash, DocumentLoadCallback callback)
  {
    File file = FileOpen(path, FileOpenMode::kRead);
    if (file.GetFileOpenError() != 0)
    {
      callback(file_hash, Optional<Buffer>{}, std::chrono::system_clock::time_point{});
      return;
    }

    auto buffer = file.ReadFileFull();
    FileClose(file);

    std::error_code ec;
    callback(file_hash, Optional<Buffer>(std::move(buffer)), std::experimental::filesystem::last_write_time(path, ec));
  }
};

class DefaultDocumentResourceLoader : public DocumentResourceLoader
{
public:
  DefaultDocumentResourceLoader() :
    m_Compiler(&m_AssetLoader)
  {

  }

  virtual Any LoadResource(czstr path, DocumentResourceLoaderCallback load_callback, void * user_ptr) override
  {
    auto document = m_Compiler.GetDocument(path);
    document->AddRef();

    auto doc_data = document->GetDocumentJson();
    load_callback(crc64(path), &doc_data, user_ptr);
    return{};
  }

  virtual void UnloadResource(uint64_t path_hash, Any && load_data) override
  {
    auto document = m_Compiler.GetDocument(path_hash);
    if (document)
    {
      document->DecRef();
    }
  }

private:

  DefaultDocumentAssetLoader m_AssetLoader;
  DocumentCompiler m_Compiler;
};


Any CreateSpriteEngineData(SpriteBaseDef & sprite)
{
  return{};
}

void UpdateSpriteEngineData(Any & engine_data)
{

}

void RenderSprite(Any & engine_data, EntityRenderState & render_state, Vector2 & position)
{

}

Any CreateMapEngineData(MapDef & map_def)
{
  return{};
}

NullOptPtr<TextureAsset> GetAssetBundleTexture(Any & load_data)
{
  return nullptr;
}

void DrawAssetBundleTexture(Any & load_data, Vector2 pos, RenderState & render_state, RenderUtil & render_util)
{

}

void PlayAssetBundleSound(Any & load_data, float volume, float pan)
{

}

DefaultDocumentResourceLoader g_DefaultLoader;
DocumentResourceLoader * g_ResourceLoader = &g_DefaultLoader;
