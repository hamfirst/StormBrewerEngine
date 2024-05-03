#pragma once

#include <QWidget>
#include <QScrollBar>

#include "Runtime/VisualEffect/VisualEffectDef.refl.h"

#include "Tools/Editor/Utility/DocumentValueWatcher.h"
#include "VisualEffectEditorNodeSelection.h"

class VisualEffectEditor;
class VisualEffectEditorNodeList;

class VisualEffectEditorNodeList : public QWidget
{
  Q_OBJECT;
public:
  VisualEffectEditorNodeList(NotNullPtr<VisualEffectEditor> editor, VisualEffectDef & ui, QWidget * parent = nullptr);

  void ChangeSelection(const VisualEffectEditorNodeSelection & layer);
  void ClearSelection();

protected:

  Vector2 VisitElements(Delegate<bool, const VisualEffectEditorNodeSelection &, const std::string &, int, int> && visitor);
  Optional<VisualEffectEditorNodeSelection> GetNodeForPosition(int y);

  void NodeRemoved(const VisualEffectEditorNodeSelection & node);
  void UpdateScroll();

protected:
  void paintEvent(QPaintEvent * ev) override;
  void resizeEvent(QResizeEvent * ev) override;

  void keyPressEvent(QKeyEvent * ev) override;

  void mousePressEvent(QMouseEvent * ev) override;
  void wheelEvent(QWheelEvent * ev) override;

  public slots:

  void scrollChanged();
  void addNewElement();
  void deleteSelection();

private:
  friend struct MapEditorLayerListElement;

  NotNullPtr<VisualEffectEditor> m_Editor;
  VisualEffectDef & m_VisualEffect;

  DocumentValueWatcher m_Watcher;
  Optional<VisualEffectEditorNodeSelection> m_Selection;

  std::unique_ptr<QScrollBar> m_ScrollBar;
};

