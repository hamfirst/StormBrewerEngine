#pragma once

#include <memory>

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>

#include "Runtime/Atlas/AtlasDef.refl.h"

#include "AssetEditors/Texture/TextureViewerWidget.h"
#include "UI/PropertyEditors/PropertyEditor.h"
#include "UI/GenericWidgets/GenericFrame.h"
#include "UI/GenericWidgets/GenericListFrame.h"
#include "Tools/Editor/UI/UtilityWidgets/SimpleLabelList.h"
#include "Utility/DocumentValueWatcher.h"

class AtlasEditor;
class AtlasTextureImportDialog;

class AtlasTextureEditor : public QWidget
{
  Q_OBJECT;
public:
  AtlasTextureEditor(NotNullPtr<AtlasEditor> editor, AtlasDef & sprite, Delegate<void, int> && add_element_cb, QWidget * parent = nullptr);

protected:

  void OpenAddTextureFileDialog();
  void HandleSelectionChanged(int selection);

public slots:

  void handleImportDialogAccepted();
  void handleImportDialogClosed();
  void handleAddElement();


private:
  NotNullPtr<AtlasEditor> m_Editor;

  AtlasDef & m_Atlas;
  Delegate<void, int> m_AddElementCallback;

  std::unique_ptr<QGridLayout> m_Layout;
  std::unique_ptr<TextureViewerWidget> m_Texture;
  std::unique_ptr<GenericListFrame> m_TextureListFrame;
  std::unique_ptr<QPushButton> m_AddNewElement;

  std::vector<std::unique_ptr<AtlasTextureImportDialog>> m_ImportDialogs;

  GenericList * m_TextureList;

  DocumentValueWatcher m_SelectedTextureUpdater;
};

