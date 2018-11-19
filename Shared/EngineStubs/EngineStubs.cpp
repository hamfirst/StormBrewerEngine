
#include "Foundation/Common.h"
#include "Foundation/Any/Any.h"
#include "Foundation/FileSystem/File.h"
#include "Foundation/FileSystem/Path.h"
#include "Foundation/Document/Document.h"
#include "Foundation/Document/DocumentCompiler.h"

#include "Runtime/Atlas/AtlasDef.refl.h"
#include "Runtime/Sprite/SpriteDef.refl.h"
#include "Runtime/Animation/AnimationState.h"
#include "Runtime/Map/MapDef.refl.h"
#include "Runtime/VisualEffect/VisualEffectDef.refl.h"
#include "Runtime/DocumentResource/DocumentResourceLoader.h"

#include <experimental/filesystem>

class RenderState;

class DefaultDocumentAssetLoader : public DocumentLoader
{
public:
  DefaultDocumentAssetLoader()
  {
    m_RootPath = GetCanonicalRootPath();
  }

  virtual void LoadDocument(czstr path, uint32_t file_hash, DocumentLoadCallback callback)
  {
    auto path_str = GetFullPath(path, m_RootPath);

    File file = FileOpen(path_str.data(), FileOpenMode::kRead);
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
  
private:
  std::string m_RootPath;
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
    load_callback(crc32lowercase(path), &doc_data, user_ptr);
    return{};
  }

  virtual void UnloadResource(uint32_t path_hash, Any && load_data) override
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

Any CreateAtlasEngineData(AtlasDef & Atlas)
{
  return {};
}

void UpdateAtlasEngineData(Any & engine_data)
{
}

void RenderAtlas(Any & engine_data, RenderState & render_state, czstr name, const Box & position, const Color & color)
{
}


Any CreateSpriteEngineData(SpriteBaseDef & sprite)
{
  return{};
}

void UpdateSpriteEngineData(Any & engine_data)
{

}

void RenderSprite(Any & engine_data, RenderState & render_state, EntityRenderState & entity_render_state, const Vector2 & position)
{

}

Any CreateMapEngineData(MapDef & map_def)
{
  return{};
}

Any CreateVisualEffectEngineData(VisualEffectDef & visual_effect)
{
  return{};
}

DefaultDocumentResourceLoader g_DefaultLoader;
DocumentResourceLoader * g_ResourceLoader = &g_DefaultLoader;
