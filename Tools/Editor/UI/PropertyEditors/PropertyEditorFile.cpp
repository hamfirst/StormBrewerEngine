
#include <QFileDialog>

#include "Foundation/FileSystem/Path.h"

#include "PropertyEditorFile.h"
#include "Tools/Editor/AssetEditors/DocumentEditor/DocumentEditorWidgetBase.h"

PropertyEditorFile::PropertyEditorFile(DocumentEditorWidgetBase * editor, PropertyField * prop, bool create_callback, 
  Delegate<void *> && data_ptr, const std::string & path, QWidget * parent) :
  QWidget(parent),
  m_Editor(editor),
  m_Property(prop),
  m_PropertyPtr(std::move(data_ptr)),
  m_PathHash(crc64(path)),
  m_LocalChange(false)
{
  m_Input = std::make_unique<GenericInput>(this);
  m_Input->setReadOnly(true);
  m_Input->SetUpdateCallback(Delegate<void>(&PropertyEditorFile::HandleTextUpdate, this));
  m_Input->RemoteUpdate(static_cast<RString *>(m_PropertyPtr())->data());

  m_FileButton = std::make_unique<QPushButton>(this);
  m_FileButton->setText("...");

  connect(m_FileButton.get(), &QPushButton::pressed, this, &PropertyEditorFile::handleFileButtonPress);

  if (create_callback)
  {
    m_CallbackId = m_Editor->AddChangeCallback(m_PathHash, DocumentExternalChangeCallback(&PropertyEditorFile::HandleServerUpdate, this));
  }
  else
  {
    m_CallbackId = 0;
  }

  setMinimumHeight(std::max(m_Input->minimumHeight(), 20));
}

PropertyEditorFile::~PropertyEditorFile()
{
  m_Editor->RemoveChangeCallback(m_PathHash, m_CallbackId);
}

void PropertyEditorFile::resizeEvent(QResizeEvent * ev)
{
  m_Input->setGeometry(0, 0, width() - 2 - 30, height());
  m_FileButton->setGeometry(width() - 1 - 30, 0, 30, height());
}

void PropertyEditorFile::HandleTextUpdate()
{

}

void PropertyEditorFile::HandleServerUpdate(const ReflectionChangeNotification & change)
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

void PropertyEditorFile::handleFileButtonPress()
{
  auto file_name = m_Editor->GetFileNameForAssetType(m_Property->m_File.m_Extension);

  if (file_name)
  {
    m_LocalChange = true;

    auto str = static_cast<RString *>(m_PropertyPtr());
    if (str != nullptr)
    {
      *str = file_name.Value();
    }

    m_LocalChange = false;
    m_Input->RemoteUpdate(file_name->data());
  }
}
