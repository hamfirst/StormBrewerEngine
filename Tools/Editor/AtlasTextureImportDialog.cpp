
#include "AtlasTextureImportDialog.h"

#include "Engine/Asset/AssetLoader.h"

static unsigned GCD(unsigned u, unsigned v) {
  while (v != 0) {
    unsigned r = u % v;
    u = v;
    v = r;
  }
  return u;
}

AtlasTextureImportDialog::AtlasTextureImportDialog(const std::string & file, QWidget *parent)
{
  ui.setupUi(this);

  connect(ui.frameWidth, &QLineEdit::textChanged, this, &AtlasTextureImportDialog::handleFrameWidthChanged);
  connect(ui.frameHeight, &QLineEdit::textChanged, this, &AtlasTextureImportDialog::handleFrameHeightChanged);

  m_Data.m_Filename = file;

  m_TextureView = std::make_unique<TextureViewerWidget>(this);
  m_TextureView->LoadTexture(file.data());
  m_TextureView->setGeometry(0, 0, width() - 1, height() - 100);

  TextureAsset::LoadWithCallback(file.data(), TextureAsset::LoadCallback(&AtlasTextureImportDialog::TextureLoaded, this), m_TextureReference);
}

AtlasDefTexture & AtlasTextureImportDialog::GetData()
{
  return m_Data;
}

void AtlasTextureImportDialog::TextureLoaded(NullOptPtr<TextureAsset> asset)
{
  if (asset->IsLoaded() == false)
  {
    return;
  }

  int width = asset->GetWidth();
  int height = asset->GetHeight();

  int test_size = GCD(width, height);

  if (test_size > 1)
  {
    ui.frameWidth->setText(QString::number(test_size));
    ui.frameHeight->setText(QString::number(test_size));
  }
}

void AtlasTextureImportDialog::closeEvent(QCloseEvent * ev)
{
  emit closed();
}

void AtlasTextureImportDialog::handleFrameWidthChanged(const QString & val)
{
  bool valid = false;
  auto int_val = val.toInt(&valid);
  if (valid)
  {
    m_TextureView->SetGridWidth(int_val);
  }
}

void AtlasTextureImportDialog::handleFrameHeightChanged(const QString & val)
{
  bool valid = false;
  auto int_val = val.toInt(&valid);
  if (valid)
  {
    m_TextureView->SetGridHeight(int_val);
  }
}