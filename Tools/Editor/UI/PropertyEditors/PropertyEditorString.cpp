
#include "PropertyEditorString.h"
#include "Tools/Editor/AssetEditors/DocumentEditor/DocumentEditorWidgetBase.h"

PropertyEditorString::PropertyEditorString(DocumentEditorWidgetBase * editor, PropertyField * prop, bool create_callback, 
  Delegate<void *> && data_ptr, const std::string & path, QWidget * parent) :
  QWidget(parent),
  m_Editor(editor),
  m_Property(prop),
  m_PropertyPtr(std::move(data_ptr)),
  m_PathHash(crc64(path)),
  m_LocalChange(false)
{
  m_Input = std::make_unique<GenericInput>(this);
  m_Input->SetUpdateCallback(Delegate<void>(&PropertyEditorString::HandleTextUpdate, this));
  m_Input->RemoteUpdate(static_cast<RString *>(m_PropertyPtr())->data());

  if (create_callback)
  {
    m_CallbackId = m_Editor->AddChangeCallback(m_PathHash, DocumentExternalChangeCallback(&PropertyEditorString::HandleServerUpdate, this));
  }
  else
  {
    m_CallbackId = 0;
  }

  setMinimumHeight(std::max(m_Input->minimumHeight(), 20));
}

PropertyEditorString::~PropertyEditorString()
{
  m_Editor->RemoveChangeCallback(m_PathHash, m_CallbackId);
}

void PropertyEditorString::resizeEvent(QResizeEvent * ev)
{
  m_Input->setGeometry(0, 0, width() - 1, height());
}

void PropertyEditorString::HandleTextUpdate()
{
  m_LocalChange = true;

  auto str = static_cast<RString *>(m_PropertyPtr());
  if (str != nullptr)
  {
    *str = m_Input->text().toStdString();
  }

  m_LocalChange = false;
}

void PropertyEditorString::HandleServerUpdate(const ReflectionChangeNotification & change)
{
  if (m_LocalChange)
  {
    return;
  }

  auto str = static_cast<RString *>(m_PropertyPtr());
  if (str != nullptr)
  {
    m_Input->RemoteUpdate(str->data());
  }
}
