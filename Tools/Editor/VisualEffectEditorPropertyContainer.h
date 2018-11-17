#pragma once

#include <QWidget>
#include <QScrollBar>

#include "Runtime/VisualEffect/VisualEffectDef.refl.h"

#include "PropertyEditorWidget.h"
#include "DocumentValueWatcher.h"
#include "VisualEffectEditorNodeSelection.h"
#include "VisualEffectEditorEquationList.h"

class VisualEffectEditor;
class VisualEffectEditorNodeList;
class VisualEffectEditorEquationList;
class VisualEffectEditorOutputEquationList;

class VisualEffectEditorPropertyContainer : public QWidget
{
  Q_OBJECT;

public:
  VisualEffectEditorPropertyContainer(NotNullPtr<VisualEffectEditor> editor, VisualEffectDef & ui, Delegate<void> && size_change_cb, QWidget * parent = nullptr);

  void ChangeSelection(const VisualEffectEditorNodeSelection & selection);
  void ClearSelection();

protected:
  void RepositionChildren();
  void SizeChanged();

protected:

  void resizeEvent(QResizeEvent * ev);

private:
  NotNullPtr<VisualEffectEditor> m_Editor;
  VisualEffectDef & m_VisualEffect;

  Delegate<void> m_SizeChanged;

  std::unique_ptr<QWidget> m_EmitterProperties;
  std::unique_ptr<QWidget> m_InputsList;
  std::unique_ptr<VisualEffectEditorEquationList> m_EmitterEquations;
  std::unique_ptr<VisualEffectEditorEquationList> m_SpawnEquations;
  std::unique_ptr<VisualEffectEditorEquationList> m_ParticleEquations;
};
