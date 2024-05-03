#pragma once

#include <QDialog>
#include <QTabWidget>
#include <QMenuBar>
#include <QMenu>

#include "Foundation/Common.h"

#include "Runtime/FrameData/FrameData.refl.h"
#include "Runtime/SpriteBase/SpriteBaseDef.refl.h"

class FrameEditorBase;
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
    Delegate<NullOptPtr<FrameData>, uint64_t> && get_frame_data,
    Delegate<NullOptPtr<FrameData>> && get_default_data,
    uint64_t frame_id,
    const std::vector<FrameDataDefElem> & frame_data_def,
    bool create_anchor_manager_tab,
    bool create_anchor_editor_tab,
    QWidget * parent = nullptr);

  void Finalize();

  bool IncFrame();
  bool DecFrame();

  static void CreateFrameEditorTabs(
    NotNullPtr<SpriteBaseEditor> editor, 
    SpriteBaseDef & sprite, 
    SpriteBaseTextureLoadList & texture_access,
    NotNullPtr<QTabWidget> tab_widget,
    NotNullPtr<std::vector<FrameEditorBase *>> child_widgets,
    NotNullPtr<Delegate<NullOptPtr<FrameData>, uint64_t>> get_frame_data,
    NullOptPtr<Delegate<NullOptPtr<FrameData>>> default_data,
    uint64_t frame_id,
    const std::vector<FrameDataDefElem> & frame_data_def,
    bool create_anchor_manager_tab,
    bool create_anchor_editor_tab);

public slots:

  void magnificationChanged(int mag);

  void undo();
  void redo();

  void copy();
  void copyPrev();
  void paste();

  void nextFrame();
  void prevFrame();

protected:

  void UpdateChildFrames();

private:
  NotNullPtr<SpriteBaseEditor> m_Editor;
  SpriteBaseDef & m_Sprite;
  SpriteBaseTextureLoadList & m_TextureAccess;

  Delegate<NullOptPtr<FrameData>, uint64_t> m_Getter;
  Delegate<NullOptPtr<FrameData>> m_Default;
  std::unique_ptr<QTabWidget> m_TabWidget;
  std::vector<FrameEditorBase *> m_ChildWidgets;

  uint64_t m_FrameId;

  std::unique_ptr<QMenuBar> m_Menu;
};

