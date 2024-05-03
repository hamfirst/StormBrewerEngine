#pragma once

#include <QWidget>
#include <QScrollBar>

#include "Runtime/VisualEffect/VisualEffectDef.refl.h"

#include "Tools/Editor/UI/PropertyEditors/PropertyEditorWidget.h"
#include "Tools/Editor/Utility/DocumentValueWatcher.h"
#include "VisualEffectEditorNodeSelection.h"
#include "VisualEffectEquationEditor.h"

class VisualEffectEditor;
class VisualEffectEditorNodeList;
class VisualEffectEquationEditor;

enum VisualEffectEquationListType
{
  kEmitter,
  kSpawn,
  kParticle,
};

class VisualEffectEditorEquationList : public QWidget
{
  Q_OBJECT;

public:
  VisualEffectEditorEquationList(NotNullPtr<VisualEffectEditor> editor, VisualEffectDef & vfx, VisualEffectEquationListType type, Delegate<void> && size_change_cb, QWidget * parent = nullptr);

  void ChangeSelection(const VisualEffectEditorNodeSelection & selection);
  void ClearSelection();

protected:
  void RefreshElements();
  void RepositionChildren();
  void SizeChanged();

protected:

  void resizeEvent(QResizeEvent * ev);

private:
  NotNullPtr<VisualEffectEditor> m_Editor;
  VisualEffectDef & m_VisualEffect;
  VisualEffectEquationListType m_Type;

  Delegate<void> m_SizeChanged;
  DocumentValueWatcher m_Watcher;

  Optional<VisualEffectEditorNodeSelection> m_Selection;
  std::vector<std::unique_ptr<VisualEffectEquationEditor>> m_Editors;
};
