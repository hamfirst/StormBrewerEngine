
#include <QMenu>
#include <QKeyEvent>
#include <QPainter>
#include <QStyle>
#include <QStyleOptionFrame>
#include <QMouseEvent>

#include <StormRefl/StormReflJson.h>
#include <StormData/StormDataJson.h>

#include "VisualEffectEditor.h"
#include "VisualEffectEditorEquationList.h"

#include "Engine/VisualEffect/VisualEffectTypes.refl.meta.h"

VisualEffectEditorEquationList::VisualEffectEditorEquationList(NotNullPtr<VisualEffectEditor> editor, 
                                                               VisualEffectDef & vfx, VisualEffectEquationListType type, 
                                                               Delegate<void> && size_change_cb, QWidget * parent) :
  QWidget(parent),
  m_Editor(editor),
  m_VisualEffect(vfx),
  m_Type(type),
  m_SizeChanged(std::move(size_change_cb)),
  m_Watcher(editor)
{
  setFocusPolicy(Qt::ClickFocus);
}

void VisualEffectEditorEquationList::ChangeSelection(const VisualEffectEditorNodeSelection & selection)
{
  ClearSelection();

  auto emitter = m_VisualEffect.m_Emitters.TryGet(selection.m_Emitter);
  if (emitter == nullptr)
  {
    return;
  }

  //auto path = StormDataGetPath(ui->m_InitData) + ".T";
  //m_Watcher.SetPath(path.data(), true, false, [this]() { return m_Selection && VisualEffectEditor::GetVisualEffectForPath(m_VisualEffect, m_Selection->m_NodePath.data()); });
  //m_Watcher.SetAllUpdateCallbacks([this]() { RefreshElements(); });

  m_Selection = selection;
  RefreshElements();
}

void VisualEffectEditorEquationList::ClearSelection()
{
  m_Editors.clear();
  m_Selection.Clear();

  SizeChanged();
}

void VisualEffectEditorEquationList::RefreshElements()
{
  m_Editors.clear();

  auto emitter = m_VisualEffect.m_Emitters.TryGet(m_Selection->m_Emitter);
  if (emitter != nullptr)
  {
    std::vector<std::string> variables;
    std::string path;
    switch (m_Type)
    {
    case VisualEffectEquationListType::kEmitter:
      StormReflVisitStatic<VisualEffectInstanceEmitterScriptData>::VisitEach([&](auto f) { variables.push_back(f.GetName()); });
      path = StormDataGetPath(emitter->m_EmitterEquations);
      break;
    case VisualEffectEquationListType::kSpawn:
      StormReflVisitStatic<VisualEffectInstanceEmitterSpawnData>::VisitEach([&](auto f) { variables.push_back(f.GetName()); });
      path = StormDataGetPath(emitter->m_SpawnEquations);
      break;
    case VisualEffectEquationListType::kParticle:
      StormReflVisitStatic<VisualEffectInstanceParticleScriptData>::VisitEach([&](auto f) { variables.push_back(f.GetName()); });
      path = StormDataGetPath(emitter->m_ParticleEquations);
      break;
    }

    for (auto & var : variables)
    {
      auto data_ptr = [this]() -> NullOptPtr<RMap<uint32_t, VisualEffectDefEquation>>
      {
        auto emitter = m_VisualEffect.m_Emitters.TryGet(m_Selection->m_Emitter);
        if (emitter == nullptr)
        {
          return nullptr;
        }

        switch (m_Type)
        {
        case VisualEffectEquationListType::kEmitter:
          return &emitter->m_EmitterEquations;
        case VisualEffectEquationListType::kSpawn:
          return &emitter->m_SpawnEquations;
        case VisualEffectEquationListType::kParticle:
          return &emitter->m_ParticleEquations;
        }
        return nullptr;
      };

      m_Editors.emplace_back(std::make_unique<VisualEffectEquationEditor>(m_Editor, var.data(), path.data(), std::move(data_ptr), this));
      m_Editors.back()->show();
    }
  }

  SizeChanged();
}

void VisualEffectEditorEquationList::RepositionChildren()
{
  int height = 0;
  int w = width() - 1;

  for (auto & elem : m_Editors)
  {
    elem->setGeometry(0, height, w, 20);
    height += 20;
  }

  setMinimumHeight(height);
}

void VisualEffectEditorEquationList::SizeChanged()
{
  RepositionChildren();
  m_SizeChanged();
}

void VisualEffectEditorEquationList::resizeEvent(QResizeEvent * ev)
{
  RepositionChildren();
}
