#pragma once

#include <QWidget>
#include <QDialog>

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Asset/AssetReference.h"

#include "Runtime/SpriteBase/SpriteBaseDef.refl.h"

#include "TextureViewerWidget.h"

#include "ui_SpriteTextureImportDialog.h"

class SpriteBaseTextureImportDialog : public QDialog
{
  Q_OBJECT;
public:
  SpriteBaseTextureImportDialog(const std::string & file, QWidget *parent = nullptr);

  SpriteBaseDefTexture & GetData();

protected:

  void TextureLoaded(NullOptPtr<TextureAsset> asset);

  virtual void closeEvent(QCloseEvent * ev) override;

public slots:
  void handleFrameWidthChanged(const QString & val);
  void handleFrameHeightChanged(const QString & val);

signals:
  void closed();

private:

  Ui::SpriteTextureImport ui;

  TextureAsset::LoadCallbackLink m_TextureReference;
  std::unique_ptr<TextureViewerWidget> m_TextureView;

  SpriteBaseDefTexture m_Data;
};
