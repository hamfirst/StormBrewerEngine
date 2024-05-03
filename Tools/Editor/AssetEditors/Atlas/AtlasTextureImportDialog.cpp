
#include "AssetEditors/Atlas/AtlasTextureImportDialog.h"

#include "Engine/Asset/AssetLoader.h"

AtlasTextureImportDialog::AtlasTextureImportDialog(const std::string & file, QWidget *parent)
{
  ui.setupUi(this);

  m_Data.m_Filename = file;

  m_TextureView = std::make_unique<TextureViewerWidget>(this);
  m_TextureView->LoadTexture(file.data());
  m_TextureView->setGeometry(0, 0, width() - 1, height() - 100);

  m_TextureReference = TextureAsset::Load(file.data(), m_TextureReference);
}

AtlasDefTexture & AtlasTextureImportDialog::GetData()
{
  return m_Data;
}

void AtlasTextureImportDialog::closeEvent(QCloseEvent * ev)
{
  emit closed();
}

