
#include "Foundation/Common.h"
#include "Foundation/Any/Any.h"
#include "Foundation/FileSystem/File.h"
#include "Foundation/FileSystem/Path.h"
#include "Foundation/Document/Document.h"
#include "Foundation/Document/DocumentDefaultLoader.h"
#include "Foundation/Document/DocumentCompiler.h"

#include "Runtime/Atlas/AtlasDef.refl.h"
#include "Runtime/Sprite/SpriteDef.refl.h"
#include "Runtime/Animation/AnimationState.h"
#include "Runtime/Map/MapDef.refl.h"
#include "Runtime/VisualEffect/VisualEffectDef.refl.h"
#include "Runtime/DocumentResource/DocumentResourceLoader.h"
#include "Runtime/BinaryResource/BinaryResourceLoader.h"

#include <filesystem>

class RenderState;



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

  DocumentDefaultLoader m_AssetLoader;
  DocumentCompiler m_Compiler;
};

class DefaultBinaryResourceLoader : public BinaryResourceLoader
{
public:
  DefaultBinaryResourceLoader()
  {
    m_RootPath = GetCanonicalRootPath();
  }

  struct BinaryData
  {
    Buffer m_AssetData;
    uint32_t m_PathHash;
  };


  virtual Any LoadResource(czstr path, BinaryResourceLoaderCallback load_callback, void * user_ptr) override
  {
    auto path_str = GetFullPath(path, m_RootPath);

    File file = FileOpen(path_str.data(), FileOpenMode::kRead);
    if (file.GetFileOpenError() != 0)
    {
      load_callback(crc32lowercase(path), nullptr, 0, user_ptr);
      return {};
    }

    BinaryData data;
    data.m_AssetData = file.ReadFileFull();
    data.m_PathHash = crc32lowercase(path);
    FileClose(file);

    std::error_code ec;
    load_callback(data.m_PathHash, data.m_AssetData.Get(), data.m_AssetData.GetSize(), user_ptr);

    m_LoadedBinaries.emplace(std::make_pair(data.m_PathHash, std::move(data)));
    return {};
  }

  virtual void UnloadResource(uint32_t path_hash, Any && load_data) override
  {
    auto itr = m_LoadedBinaries.find(path_hash);
    if(itr != m_LoadedBinaries.end())
    {
      m_LoadedBinaries.erase(itr);
    }
  }

private:

  std::string m_RootPath;
  std::unordered_map<uint32_t, BinaryData> m_LoadedBinaries;
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

void RenderSprite(Any & engine_data, RenderState & render_state, EntityRenderState & entity_render_state, const RenderVec2 & position)
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

DefaultDocumentResourceLoader g_DefaultDocumentLoader;
DocumentResourceLoader * g_DocumentResourceLoader = &g_DefaultDocumentLoader;

DefaultBinaryResourceLoader g_DefaultBinaryLoader;
BinaryResourceLoader * g_BinaryResourceLoader = &g_DefaultBinaryLoader;

