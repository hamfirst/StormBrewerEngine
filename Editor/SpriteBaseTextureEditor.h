#pragma once

#include <memory>

#include <QWidget>
#include <QGridLayout>

#include "Runtime/SpriteBase/SpriteBaseDef.refl.h"

#include "TextureViewerWidget.h"
#include "PropertyEditor.h"
#include "GenericFrame.h"
#include "GenericListFrame.h"
#include "SimpleLabelList.h"
#include "DocumentValueWatcher.h"

class SpriteBaseEditor;
class SpriteBaseTextureImportDialog;

class SpriteBaseTextureEditor : public QWidget
{
  Q_OBJECT;
public:
  SpriteBaseTextureEditor(NotNullPtr<SpriteBaseEditor> editor, SpriteBaseDef & sprite, QWidget * parent = nullptr);

protected:

  void OpenAddTextureFileDialog();
  void HandleSelectionChanged(int selection);

public slots:
  
  void handleImportDialogAccepted();
  void handleImportDialogClosed();


private:
  NotNullPtr<SpriteBaseEditor> m_Editor;

  SpriteBaseDef & m_Sprite;

  std::unique_ptr<QGridLayout> m_Layout;
  std::unique_ptr<TextureViewerWidget> m_Texture;
  std::unique_ptr<GenericListFrame> m_TextureListFrame;
  std::unique_ptr<GenericFrame> m_TextureProperties;

  std::vector<std::unique_ptr<SpriteBaseTextureImportDialog>> m_ImportDialogs;

  GenericList * m_TextureList;
  PropertyEditor * m_PropertyEditor;

  DocumentValueWatcher m_SelectedTextureUpdater;
};

