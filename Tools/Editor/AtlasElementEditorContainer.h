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
#include "AtlasElementEditor.h"
#include "AtlasTextureLoadList.h"

class AtlasEditor;
class AtlasTextureImportDialog;

class AtlasElementEditorContainer : public QWidget
{
Q_OBJECT;
public:
  AtlasElementEditorContainer(NotNullPtr<AtlasEditor> editor, AtlasDef & sprite, AtlasTextureLoadList & texture_access, QWidget * parent = nullptr);

  void SetSelectedElement(int selection);

  void AddNewElement();
  void AddNewElement(int tex_index);

protected:

  void HandleSelectionChanged(int selection);

public slots:

private:
  NotNullPtr<AtlasEditor> m_Editor;

  AtlasDef & m_Atlas;

  std::unique_ptr<QGridLayout> m_Layout;
  std::unique_ptr<AtlasElementEditor> m_ElementEditor;
  std::unique_ptr<GenericListFrame> m_ElemListFrame;
  std::unique_ptr<GenericFrame> m_ElemProperties;

  GenericList * m_ElemList;
  PropertyEditor * m_PropertyEditor;

  DocumentValueWatcher m_SelectedElemUpdater;
};

