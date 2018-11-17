
#include <QPushButton>

#include <StormRefl/StormReflJson.h>
#include <StormData/StormDataJson.h>
#include <sb/vector.h>

#include "Runtime/Sprite/SpriteDef.refl.meta.h"

#include "SpriteBaseTextureEditor.h"
#include "SpriteBaseEditor.h"
#include "PropertyEditor.h"
#include "SimpleLabelList.h"
#include "SpriteBaseTextureImportDialog.h"


SpriteBaseTextureEditor::SpriteBaseTextureEditor(NotNullPtr<SpriteBaseEditor> editor, SpriteBaseDef & sprite, QWidget * parent) :
  QWidget(parent),
  m_Editor(editor),
  m_Sprite(sprite),
  m_Layout(std::make_unique<QGridLayout>()),
  m_Texture(std::make_unique<TextureViewerWidget>()),
  m_TextureListFrame(std::make_unique<GenericListFrame>("Texture Files", true, true, this)),
  m_TextureProperties(std::make_unique<GenericFrame>("Properties", this)),
  m_SelectedTextureUpdater(editor)
{
  m_Layout->setColumnStretch(0, 2);
  m_Layout->setColumnMinimumWidth(0, 100);

  m_Layout->setColumnStretch(1, 1);
  m_Layout->setColumnMinimumWidth(1, 100);

  m_Layout->setRowStretch(0, 3);
  m_Layout->setRowMinimumHeight(0, 100);

  m_Layout->setRowStretch(1, 2);
  m_Layout->setRowMinimumHeight(1, 100);

  m_Layout->addWidget(m_Texture.get(), 0, 0, 1, 2);
  m_Layout->addWidget(m_TextureListFrame.get(), 1, 0);
  m_Layout->addWidget(m_TextureProperties.get(), 1, 1);

  m_PropertyEditor = m_TextureProperties->CreateWidget<PropertyEditor>();

  m_TextureList = CreateSimpleLabelList<RMergeList, SpriteBaseDefTexture>(m_Editor, m_Sprite.m_Textures, 
    [](SpriteBaseDefTexture & tex) { return tex.m_Filename.ToString(); }, m_TextureListFrame.get());

  m_TextureListFrame->SetAddDelegate([=] { OpenAddTextureFileDialog(); });
  m_TextureList->SetSelectionCallback(GenericListSelectionDelegate(&SpriteBaseTextureEditor::HandleSelectionChanged, this));

  setLayout(m_Layout.get());
}

void SpriteBaseTextureEditor::OpenAddTextureFileDialog()
{
  auto file_name = m_Editor->GetFileNameForAssetType("image");
  if (file_name)
  {
    auto dialog = std::make_unique<SpriteBaseTextureImportDialog>(file_name.Value(), this);
    dialog->show();

    connect(dialog.get(), &SpriteBaseTextureImportDialog::accepted, this, &SpriteBaseTextureEditor::handleImportDialogAccepted);
    connect(dialog.get(), &SpriteBaseTextureImportDialog::rejected, this, &SpriteBaseTextureEditor::handleImportDialogClosed);
    connect(dialog.get(), &SpriteBaseTextureImportDialog::closed, this, &SpriteBaseTextureEditor::handleImportDialogClosed);

    m_ImportDialogs.emplace_back(std::move(dialog));
  }
}

void SpriteBaseTextureEditor::handleImportDialogAccepted()
{
  auto dialog = static_cast<SpriteBaseTextureImportDialog *>(QObject::sender());
  m_TextureList->AppendElement(&dialog->GetData());
  handleImportDialogClosed();
}

void SpriteBaseTextureEditor::handleImportDialogClosed()
{
  auto dialog = static_cast<SpriteBaseTextureImportDialog *>(QObject::sender());
  for (std::size_t index = 0, end = m_ImportDialogs.size(); index < end; ++index)
  {
    if (m_ImportDialogs[index].get() == dialog)
    {
      vremove_index_quick(m_ImportDialogs, index);
      return;
    }
  }
}

void SpriteBaseTextureEditor::HandleSelectionChanged(int selection)
{
  if (selection == -1)
  {
    m_Texture->UnloadTexture();
    m_PropertyEditor->Unload();

    m_SelectedTextureUpdater.ClearPath();
  }
  else
  {
    m_Texture->LoadTexture(m_Sprite.m_Textures[selection].m_Filename.data());
    m_PropertyEditor->LoadStruct(m_Editor, m_Sprite.m_Textures[selection], true);

    auto texture_widget_update = [=]() 
    { 
      if (m_Sprite.m_Textures.HasAt(selection)) 
      { 
        m_Texture->LoadTexture(m_Sprite.m_Textures[selection].m_Filename.data()); 
        m_Texture->SetGridWidth(m_Sprite.m_Textures[selection].m_FrameWidth);
        m_Texture->SetGridHeight(m_Sprite.m_Textures[selection].m_FrameHeight);
      } 
    };

    std::string path = ".m_Textures[" + std::to_string(selection) + "]";
    m_SelectedTextureUpdater.SetPath(path.data(), true, true, [=] {return m_Sprite.m_Textures.HasAt(selection); });
    m_SelectedTextureUpdater.SetAllUpdateCallbacks(texture_widget_update);

    texture_widget_update();
  }
}
