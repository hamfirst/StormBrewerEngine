
#include <QPushButton>

#include <StormRefl/StormReflJson.h>
#include <StormData/StormDataJson.h>
#include <sb/vector.h>

#include "Runtime/Atlas/AtlasDef.refl.meta.h"

#include "AtlasElementEditorContainer.h"
#include "AtlasEditor.h"
#include "PropertyEditor.h"
#include "SimpleLabelList.h"


AtlasElementEditorContainer::AtlasElementEditorContainer(NotNullPtr<AtlasEditor> editor, AtlasDef & atlas, AtlasTextureLoadList & texture_access, QWidget * parent) :
        QWidget(parent),
        m_Editor(editor),
        m_Atlas(atlas),
        m_Layout(std::make_unique<QGridLayout>()),
        m_ElementEditor(std::make_unique<AtlasElementEditor>(editor, atlas, texture_access, this)),
        m_ElemListFrame(std::make_unique<GenericListFrame>("Elements", true, true, this)),
        m_ElemProperties(std::make_unique<GenericFrame>("Properties", this)),
        m_SelectedElemUpdater(editor)
{
  m_Layout->setColumnStretch(0, 2);
  m_Layout->setColumnMinimumWidth(0, 100);

  m_Layout->setColumnStretch(1, 1);
  m_Layout->setColumnMinimumWidth(1, 100);

  m_Layout->setRowStretch(0, 3);
  m_Layout->setRowMinimumHeight(0, 100);

  m_Layout->setRowStretch(1, 2);
  m_Layout->setRowMinimumHeight(1, 100);

  m_Layout->addWidget(m_ElementEditor.get(), 0, 0, 1, 2);
  m_Layout->addWidget(m_ElemListFrame.get(), 1, 0);
  m_Layout->addWidget(m_ElemProperties.get(), 1, 1);

  m_PropertyEditor = m_ElemProperties->CreateWidget<PropertyEditor>();

  m_ElemList = CreateSimpleLabelList<RMergeList, AtlasDefElement>(m_Editor, m_Atlas.m_Elements,
          [](AtlasDefElement & elem) { return elem.m_Name.ToString(); }, m_ElemListFrame.get());

  m_ElemListFrame->SetAddDelegate([=] { AddNewElement(); });
  m_ElemList->SetSelectionCallback(GenericListSelectionDelegate(&AtlasElementEditorContainer::HandleSelectionChanged, this));

  setLayout(m_Layout.get());
}

void AtlasElementEditorContainer::SetSelectedElement(int selection)
{
  m_ElemList->SetSelection(selection);
}

void AtlasElementEditorContainer::AddNewElement()
{
  auto elem_index = m_ElemList->GetSelection();
  if(m_Atlas.m_Elements.HasAt(elem_index) == false)
  {
    return;
  }

  auto texture_hash = m_Atlas.m_Elements[elem_index].m_TextureHash;
  for(auto tex : m_Atlas.m_Textures)
  {
    if(crc32lowercase(tex.second.m_Filename.ToString()) == texture_hash)
    {
      AddNewElement(tex.first);
      return;
    }
  }
}

void AtlasElementEditorContainer::AddNewElement(int tex_index)
{
  if(m_Atlas.m_Textures.HasAt(tex_index) == false)
  {
    return;
  }

  auto texture_name_hash = crc32lowercase(m_Atlas.m_Textures[tex_index].m_Filename.ToString());
  AtlasDefElement elem;

  elem.m_Name = "New Element";
  elem.m_TextureHash = texture_name_hash;
  m_Atlas.m_Elements.EmplaceBack(std::move(elem));

  m_ElementEditor->SetSelectedElement(m_Atlas.m_Elements.HighestIndex());
}

void AtlasElementEditorContainer::HandleSelectionChanged(int selection)
{
  m_ElementEditor->SetSelectedElement(selection);

  if (selection == -1)
  {
    m_PropertyEditor->Unload();
  }
  else
  {
    m_PropertyEditor->LoadStruct(m_Editor, m_Atlas.m_Elements[selection], true);
  }
}
