#pragma once

#include <QWidget>
#include <QScrollBar>

#include "Runtime/UI/UIDef.refl.h"

#include "DocumentValueWatcher.h"
#include "UIEditorNode.h"

class UIEditor;
class UIEditorNodeList;

class UIEditorNodeList : public QWidget
{
  Q_OBJECT;
public:
  UIEditorNodeList(NotNullPtr<UIEditor> editor, UIDef & ui, QWidget * parent = nullptr);

  void ChangeSelection(const UIEditorNodeSelection & layer);
  void ClearSelection();

protected:

  Vector2 VisitElements(Delegate<bool, const UIDef &, const UIEditorNodeSelection &, const std::string &, int, int> && visitor);
  bool TraverseElement(UIDef & ui, Delegate<bool, const UIDef &, const UIEditorNodeSelection &, const std::string &, int, int> & visitor, 
    const std::string & path, const std::string & name, int & x, int & y);
  Optional<UIEditorNodeSelection> GetNodeForPosition(int y);

  void NodeRemoved(const UIEditorNodeSelection & node);
  void UpdateScroll();

protected:
  void paintEvent(QPaintEvent * ev) override;
  void resizeEvent(QResizeEvent * ev) override;

  void keyPressEvent(QKeyEvent * ev) override;

  void mousePressEvent(QMouseEvent * ev) override;
  void wheelEvent(QWheelEvent * ev) override;

public slots:

  void scrollChanged();
  void linkElement();
  void addNewElement();
  void deleteSelection();

private:
  friend struct MapEditorLayerListElement;

  NotNullPtr<UIEditor> m_Editor;
  UIDef & m_UI;

  DocumentValueWatcher m_Watcher;
  Optional<UIEditorNodeSelection> m_Selection;

  std::unique_ptr<QScrollBar> m_ScrollBar;
};

