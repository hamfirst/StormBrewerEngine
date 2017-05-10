
#include <QPainter>

#include "PropertyEditor.h"
#include "PropertyEditorWidget.h"

PropertyEditor::PropertyEditor(QWidget * parent) :
  ScrollingPanel(parent)
{

}

void PropertyEditor::LoadObject(NotNullPtr<DocumentEditorWidgetBase> editor, NotNullPtr<PropertyField> prop, Delegate<void *> && data_ptr, const std::string & base_path)
{
  auto child = PropertyEditorCreate(editor, prop, std::move(data_ptr), base_path, Delegate<void>([this] { recalculate(); }), nullptr, nullptr);
  SetChildWidget(std::move(child));
}

void PropertyEditor::Unload()
{
  SetChildWidget({});
}

void PropertyEditor::resizeEvent(QResizeEvent * ev)
{
  ScrollingPanel::resizeEvent(ev);
}
