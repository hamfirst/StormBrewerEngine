#pragma once

#include <QDialog>
#include <QTabWidget>

#include "Foundation/Common.h"

#include "Runtime/FrameData/FrameData.refl.h"
#include "Runtime/SpriteBase/SpriteBaseDef.refl.h"

class SpriteBaseEditor;
class SpriteBaseTextureLoadList;

class FrameEditorContainer : public QDialog
{
  Q_OBJECT;
public:
  FrameEditorContainer(
    NotNullPtr<SpriteBaseEditor> editor,
    SpriteBaseDef & sprite,
    SpriteBaseTextureLoadList & texture_access,
    Delegate<NullOptPtr<FrameData>> && get_frame_data,
    Delegate<NullOptPtr<FrameData>> && get_default_data,
    uint64_t frame_id,
    const std::vector<FrameDataDefElem> & frame_data_def, 
    QWidget * parent = nullptr);

  static void CreateFrameEditorTabs(
    NotNullPtr<SpriteBaseEditor> editor, 
    SpriteBaseDef & sprite, 
    SpriteBaseTextureLoadList & texture_access,
    NotNullPtr<QTabWidget> tab_widget,
    NotNullPtr<Delegate<NullOptPtr<FrameData>>> get_frame_data,
    NullOptPtr<Delegate<NullOptPtr<FrameData>>> default_data,
    uint64_t frame_id,
    const std::vector<FrameDataDefElem> & frame_data_def);

protected:

  virtual void resizeEvent(QResizeEvent * ev) override;

private:

  Delegate<NullOptPtr<FrameData>> m_Getter;
  Delegate<NullOptPtr<FrameData>> m_Default;
  std::unique_ptr<QTabWidget> m_TabWidget;
};

