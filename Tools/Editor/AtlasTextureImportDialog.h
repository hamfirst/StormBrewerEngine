#pragma once

#include <QWidget>
#include <QDialog>

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Asset/AssetReference.h"

#include "Runtime/Atlas/AtlasDef.refl.h"

#include "TextureViewerWidget.h"

#include "ui_AtlasTextureImportDialog.h"

class AtlasTextureImportDialog : public QDialog
{
Q_OBJECT;
public:
  AtlasTextureImportDialog(const std::string & file, QWidget *parent = nullptr);

  AtlasDefTexture & GetData();

protected:

  virtual void closeEvent(QCloseEvent * ev) override;

signals:
  void closed();

private:

  Ui::AtlasTextureImport ui;

  TextureAsset::AssetRef m_TextureReference;
  std::unique_ptr<TextureViewerWidget> m_TextureView;

  AtlasDefTexture m_Data;
};
