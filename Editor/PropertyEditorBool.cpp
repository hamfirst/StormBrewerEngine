
#include "PropertyEditorBool.h"
#include "DocumentEditorWidgetBase.h"

PropertyEditorBool::PropertyEditorBool(DocumentEditorWidgetBase * editor, PropertyField * prop, Delegate<void *> && data_ptr, const std::string & path, QWidget * parent) :
  QWidget(parent),
  m_Editor(editor),
  m_Property(prop),
  m_PropertyPtr(std::move(data_ptr)),
  m_PathHash(crc64(path)),
  m_LocalChange(false)
{
  m_Input = std::make_unique<GenericCheckbox>(this);
  m_Input->SetUpdateCallback(Delegate<void>(&PropertyEditorBool::HandleTextUpdate, this));
  m_Input->RemoteUpdate(*static_cast<RBool *>(m_PropertyPtr()));

  m_CallbackId = m_Editor->AddChangeCallback(m_PathHash, DocumentExternalChangeCallback(&PropertyEditorBool::HandleServerUpdate, this));

  setMinimumHeight(std::max(m_Input->minimumHeight(), 20));
}

PropertyEditorBool::~PropertyEditorBool()
{
  m_Editor->RemoveChangeCallback(m_PathHash, m_CallbackId);
}

void PropertyEditorBool::resizeEvent(QResizeEvent * ev)
{
  m_Input->setGeometry(0, 0, width() - 1, height());
}

void PropertyEditorBool::HandleTextUpdate()
{
  m_LocalChange = true;

  RBool * b = static_cast<RBool *>(m_PropertyPtr());
  if (b != nullptr)
  {
    *b = m_Input->GetChecked();
  }

  m_LocalChange = false;
}

void PropertyEditorBool::HandleServerUpdate(const ReflectionChangeNotification & change)
{
  if (m_LocalChange)
  {
    return;
  }

  RBool * b = static_cast<RBool *>(m_PropertyPtr());

  if (b != nullptr)
  {
    m_Input->RemoteUpdate(*b);
  }
}
