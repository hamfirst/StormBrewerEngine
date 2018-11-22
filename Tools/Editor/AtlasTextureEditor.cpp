
#include <QPushButton>

#include <StormRefl/StormReflJson.h>
#include <StormData/StormDataJson.h>
#include <sb/vector.h>

#include "Runtime/Atlas/AtlasDef.refl.meta.h"

#include "AtlasTextureEditor.h"
#include "AtlasEditor.h"
#include "PropertyEditor.h"
#include "SimpleLabelList.h"
#include "AtlasTextureImportDialog.h"


AtlasTextureEditor::AtlasTextureEditor(NotNullPtr<AtlasEditor> editor, AtlasDef & atlas, Delegate<void, int> && add_element_cb, QWidget * parent) :
        QWidget(parent),
        m_Editor(editor),
        m_Atlas(atlas),
        m_AddElementCallback(std::move(add_element_cb)),
        m_Layout(std::make_unique<QGridLayout>()),
        m_Texture(std::make_unique<TextureViewerWidget>()),
        m_TextureListFrame(std::make_unique<GenericListFrame>("Texture Files", true, true, this)),
        m_AddNewElement(std::make_unique<QPushButton>("Add New Element", this)),
        m_SelectedTextureUpdater(editor)
{
  m_AddNewElement->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  connect(m_AddNewElement.get(), &QPushButton::pressed, this, &AtlasTextureEditor::handleAddElement);

  m_Layout->setColumnStretch(0, 2);
  m_Layout->setColumnMinimumWidth(0, 100);

  m_Layout->setColumnStretch(1, 1);
  m_Layout->setColumnMinimumWidth(1, 100);

  m_Layout->setRowStretch(0, 7);
  m_Layout->setRowMinimumHeight(0, 100);

  m_Layout->setRowStretch(1, 2);
  m_Layout->setRowMinimumHeight(1, 200);

  m_Layout->addWidget(m_Texture.get(), 0, 0, 1, 2);
  m_Layout->addWidget(m_TextureListFrame.get(), 1, 0);
  m_Layout->addWidget(m_AddNewElement.get(), 1, 1);


  m_TextureList = CreateSimpleLabelList<RMergeList, AtlasDefTexture>(m_Editor, m_Atlas.m_Textures,
          [](AtlasDefTexture & tex) { return tex.m_Filename.ToString(); }, m_TextureListFrame.get());

  m_TextureListFrame->SetAddDelegate([=] { OpenAddTextureFileDialog(); });
  m_TextureList->SetSelectionCallback(GenericListSelectionDelegate(&AtlasTextureEditor::HandleSelectionChanged, this));

  setLayout(m_Layout.get());
}

void AtlasTextureEditor::OpenAddTextureFileDialog()
{
  auto file_name = m_Editor->GetFileNameForAssetType("image");
  if (file_name)
  {
    auto dialog = std::make_unique<AtlasTextureImportDialog>(file_name.Value(), this);
    dialog->show();

    connect(dialog.get(), &AtlasTextureImportDialog::accepted, this, &AtlasTextureEditor::handleImportDialogAccepted);
    connect(dialog.get(), &AtlasTextureImportDialog::rejected, this, &AtlasTextureEditor::handleImportDialogClosed);
    connect(dialog.get(), &AtlasTextureImportDialog::closed, this, &AtlasTextureEditor::handleImportDialogClosed);

    m_ImportDialogs.emplace_back(std::move(dialog));
  }
}

void AtlasTextureEditor::handleImportDialogAccepted()
{
  auto dialog = static_cast<AtlasTextureImportDialog *>(QObject::sender());
  m_TextureList->AppendElement(&dialog->GetData());
  handleImportDialogClosed();
}

void AtlasTextureEditor::handleImportDialogClosed()
{
  auto dialog = static_cast<AtlasTextureImportDialog *>(QObject::sender());
  for (std::size_t index = 0, end = m_ImportDialogs.size(); index < end; ++index)
  {
    if (m_ImportDialogs[index].get() == dialog)
    {
      vremove_index_quick(m_ImportDialogs, index);
      return;
    }
  }
}

void AtlasTextureEditor::handleAddElement()
{
  if(m_Atlas.m_Textures.HighestIndex() < 0)
  {
    return;
  }

  m_AddElementCallback(m_TextureList->GetSelection());
}

void AtlasTextureEditor::HandleSelectionChanged(int selection)
{
  if (selection == -1)
  {
    m_Texture->UnloadTexture();

    m_SelectedTextureUpdater.ClearPath();
  }
  else
  {
    m_Texture->LoadTexture(m_Atlas.m_Textures[selection].m_Filename.data());

    auto texture_widget_update = [=]()
    {
      if (m_Atlas.m_Textures.HasAt(selection))
      {
        m_Texture->LoadTexture(m_Atlas.m_Textures[selection].m_Filename.data());
      }
    };

    std::string path = ".m_Textures[" + std::to_string(selection) + "]";
    m_SelectedTextureUpdater.SetPath(path.data(), true, true, [=] {return m_Atlas.m_Textures.HasAt(selection); });
    m_SelectedTextureUpdater.SetAllUpdateCallbacks(texture_widget_update);

    texture_widget_update();
  }
}
