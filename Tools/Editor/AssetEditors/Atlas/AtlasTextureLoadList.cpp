
#include "AssetEditors/Atlas/AtlasTextureLoadList.h"
#include "AssetEditors/Atlas/AtlasEditor.h"

AtlasTextureLoadList::AtlasTextureLoadList(NotNullPtr<AtlasEditor> editor, AtlasDef & atlas) :
        m_Editor(editor),
        m_Atlas(atlas),
        m_TextureList(m_Editor)
{
  m_GetTexture = CreateMirrorList<RMergeList, AtlasDefTexture, RString, AssetSync<TextureAsset>, AtlasTextureLoadList>(
          m_TextureList,
                  m_Atlas.m_Textures,
                  ".m_Filename",
                  [](AtlasDefTexture & elem, NotNullPtr<AtlasTextureLoadList>) -> RString & { return elem.m_Filename; },
                  [](RString & filename, AssetSync<TextureAsset> & tex, std::size_t, NotNullPtr<AtlasTextureLoadList>) {},
                  [](RString & filename, AssetSync<TextureAsset> & tex, std::size_t, NotNullPtr<AtlasTextureLoadList>) { tex.LoadFile(filename.data()); },
                  this
  );
}

NullOptPtr<TextureAsset> AtlasTextureLoadList::GetTexture(std::size_t index)
{
  auto asset_sync = m_GetTexture(index);
  if (asset_sync == nullptr)
  {
    return nullptr;
  }

  return asset_sync->GetAsset();
}

DelegateLink<void> AtlasTextureLoadList::AddUpdateCallback(Delegate<void> && del)
{
  return m_UpdateCallbacks.AddDelegate(std::move(del));
}

void AtlasTextureLoadList::HandleTextureUpdate()
{
  m_UpdateCallbacks.Call();
}
