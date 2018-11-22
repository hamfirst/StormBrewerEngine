
#include "StormData/StormDataParent.h"

#include "Runtime/Atlas/AtlasDef.refl.meta.h"

#include "AtlasEditor.h"
#include "AtlasTextureImportDialog.h"
#include "EditorContainer.h"
#include "DocumentEditor.h"

AtlasEditor::AtlasEditor(EditorContainer & editor_container, PropertyFieldDatabase & property_db, const std::string & root_path, AtlasDef & atlas,
                                   DocumentChangeLinkDelegate && change_link_callback,  DocumentBeginTransactionDelegate && begin_transaction_callback, DocumentCommitChangesDelegate && commit_change_callback, QWidget *parent) :
        DocumentEditorWidgetBase(editor_container, property_db, root_path, std::move(change_link_callback), std::move(begin_transaction_callback), std::move(commit_change_callback), parent),
        m_Atlas(atlas),
        m_TextureAccess(this, m_Atlas),
        m_TabWidget(std::make_unique<QTabWidget>()),
        m_Layout(std::make_unique<QHBoxLayout>()),
        m_TextureEditor(std::make_unique<AtlasTextureEditor>(this, atlas, [this](int tex_index) { AddNewElement(tex_index); })),
        m_ElementEditor(std::make_unique<AtlasElementEditorContainer>(this, atlas, m_TextureAccess))
{
  m_TabWidget->addTab(m_TextureEditor.get(), "Textures");
  m_TabWidget->addTab(m_ElementEditor.get(), "Atlas Elements");
  m_TabWidget->setTabPosition(QTabWidget::West);

  m_Layout->addWidget(m_TabWidget.get());
  setLayout(m_Layout.get());
}

void AtlasEditor::AddNewElement(int texture_index)
{
  if(m_Atlas.m_Textures.HasAt(texture_index) == false)
  {
    return;
  }

  m_ElementEditor->AddNewElement(texture_index);
  m_TabWidget->setCurrentIndex(1);
}

REGISTER_EDITOR("Atlas", AtlasEditor, AtlasDef, ".atlas", "UIs");

