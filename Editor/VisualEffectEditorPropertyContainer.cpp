
#include <QMenu>
#include <QKeyEvent>
#include <QPainter>
#include <QStyle>
#include <QStyleOptionFrame>
#include <QMouseEvent>

#include <StormRefl/StormReflJson.h>
#include <StormData/StormDataJson.h>

#include "VisualEffectEditor.h"
#include "VisualEffectEditorPropertyContainer.h"

VisualEffectEditorPropertyContainer::VisualEffectEditorPropertyContainer(NotNullPtr<VisualEffectEditor> editor, VisualEffectDef & ui, Delegate<void> && size_change_cb, QWidget * parent) :
  QWidget(parent),
  m_Editor(editor),
  m_VisualEffect(ui),
  m_SizeChanged(std::move(size_change_cb))
{
  setFocusPolicy(Qt::ClickFocus);
}

void VisualEffectEditorPropertyContainer::ChangeSelection(const VisualEffectEditorNodeSelection & selection)
{
  auto emitter = m_VisualEffect.m_Emitters.TryGet(selection.m_Emitter);
  if (emitter == nullptr)
  {
    ClearSelection();
    return;
  }

  auto & prop_db = m_Editor->GetPropertyFieldDatabase();
  auto vfx_prop_def = prop_db.FindStructData(crc32("VisualEffectDef"));
  auto emitter_prop_def = prop_db.FindStructData(crc32("VisualEffectDefEmitterProperties"));

  if (vfx_prop_def == nullptr || emitter_prop_def == nullptr)
  {
    ClearSelection();
    return;
  }

  NullOptPtr<PropertyField> input_props;

  for (auto & elem : vfx_prop_def->m_Struct.m_StructData->m_Members)
  {
    if (elem.m_Name == "m_Inputs")
    {
      input_props = elem.m_FieldData;
      break;
    }
  }

  if (input_props == nullptr)
  {
    ClearSelection();
    return;
  }

  auto emitter_props_ptr = [this, sel = selection]() -> void * 
  { 
    auto emitter = m_VisualEffect.m_Emitters.TryGet(sel.m_Emitter); 
    if (emitter == nullptr)
    {
      return nullptr;
    }

    return &emitter->m_Properties;
  };

  auto props_path = StormDataGetPath(emitter->m_Properties);
  m_EmitterProperties = PropertyEditorCreate(m_Editor, emitter_prop_def, true, std::move(emitter_props_ptr), props_path.data(), [this] { SizeChanged(); }, "Properties", this);
  m_EmitterProperties->show();

  m_InputsList = PropertyEditorCreate(m_Editor, input_props, true, [this]() -> void * { return &m_VisualEffect.m_Inputs; }, ".m_Inputs", [this] { SizeChanged(); }, "Inputs", this);
  m_InputsList->show();

  m_EmitterEquations = std::make_unique<VisualEffectEditorEquationList>(m_Editor, m_VisualEffect, VisualEffectEquationListType::kEmitter, [this] { SizeChanged(); }, this);
  m_EmitterEquations->ChangeSelection(selection);
  m_EmitterEquations->show();

  m_SpawnEquations = std::make_unique<VisualEffectEditorEquationList>(m_Editor, m_VisualEffect, VisualEffectEquationListType::kSpawn, [this] { SizeChanged(); }, this);
  m_SpawnEquations->ChangeSelection(selection);
  m_SpawnEquations->show();

  m_ParticleEquations = std::make_unique<VisualEffectEditorEquationList>(m_Editor, m_VisualEffect, VisualEffectEquationListType::kParticle, [this] { SizeChanged(); }, this);
  m_ParticleEquations->ChangeSelection(selection);
  m_ParticleEquations->show();

  SizeChanged();
}

void VisualEffectEditorPropertyContainer::ClearSelection()
{
  m_EmitterProperties.reset();
  m_InputsList.reset();

  SizeChanged();
}

void VisualEffectEditorPropertyContainer::RepositionChildren()
{
  int height = 0;
  int w = width() - 1;

  if (m_EmitterProperties)
  {
    auto elem_height = m_EmitterProperties->minimumHeight();
    m_EmitterProperties->setGeometry(0, height, w, elem_height);
    height += elem_height + 10;
  }

  if (m_InputsList)
  {
    auto elem_height = m_InputsList->minimumHeight();
    m_InputsList->setGeometry(0, height, w, elem_height);
    height += elem_height;
  }

  if (m_EmitterEquations)
  {
    auto elem_height = m_EmitterEquations->minimumHeight();
    m_EmitterEquations->setGeometry(0, height, w, elem_height);
    height += elem_height;
  }

  if (m_SpawnEquations)
  {
    auto elem_height = m_SpawnEquations->minimumHeight();
    m_SpawnEquations->setGeometry(0, height, w, elem_height);
    height += elem_height;
  }

  if (m_ParticleEquations)
  {
    auto elem_height = m_ParticleEquations->minimumHeight();
    m_ParticleEquations->setGeometry(0, height, w, elem_height);
    height += elem_height;
  }

  setMinimumHeight(height);
}

void VisualEffectEditorPropertyContainer::SizeChanged()
{
  RepositionChildren();
  m_SizeChanged();
}

void VisualEffectEditorPropertyContainer::resizeEvent(QResizeEvent * ev)
{
  RepositionChildren();
}
