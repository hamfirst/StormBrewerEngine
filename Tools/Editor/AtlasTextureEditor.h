#pragma once

#include <memory>

#include <QWidget>
#include <QGridLayout>

#include "Runtime/Atlas/AtlasDef.refl.h"

#include "TextureViewerWidget.h"
#include "PropertyEditor.h"
#include "GenericFrame.h"
#include "GenericListFrame.h"
#include "SimpleLabelList.h"
#include "DocumentValueWatcher.h"

class AtlasEditor;
class AtlasTextureImportDialog;

class AtlasTextureEditor : public QWidget
{
  Q_OBJECT;
public:
  AtlasTextureEditor(NotNullPtr<AtlasEditor> editor, AtlasDef & sprite, QWidget * parent = nullptr);

protected:

  void OpenAddTextureFileDialog();
  void HandleSelectionChanged(int selection);

public slots:

  void handleImportDialogAccepted();
  void handleImportDialogClosed();


private:
  NotNullPtr<AtlasEditor> m_Editor;

  AtlasDef & m_Atlas;

  std::unique_ptr<QGridLayout> m_Layout;
  std::unique_ptr<TextureViewerWidget> m_Texture;
  std::unique_ptr<GenericListFrame> m_TextureListFrame;
  std::unique_ptr<GenericFrame> m_TextureProperties;

  std::vector<std::unique_ptr<AtlasTextureImportDialog>> m_ImportDialogs;

  GenericList * m_TextureList;
  PropertyEditor * m_PropertyEditor;

  DocumentValueWatcher m_SelectedTextureUpdater;
};

