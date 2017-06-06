cmake_minimum_required(VERSION 3.0)

include_directories(. ../. .././External)
set(CMAKE_CXX_STANDARD 14)

if (WEB)
  add_definitions(-D_WEB)
  include_directories(.././External/Web)
  set(PLATFORM_SRC_Editor 
            )
elseif (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(.././External/Windows)
  set(PLATFORM_SRC_Editor 
            )
elseif (APPLE)
  add_definitions(-D_MACOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_Editor 
            )
elseif (UNIX)
  add_definitions(-D_LINUX)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_Editor 
            )
endif()

set(GENERIC_SRC_Editor 
            ./AudioViewer.cpp
            ./ConnectingDialog.cpp
            ./DocumentEditorBase.cpp
            ./DocumentEditorWidgetBase.cpp
            ./DocumentListValueWatcher.cpp
            ./DocumentServerThread.cpp
            ./DocumentSubValueListMirror.cpp
            ./DocumentValueWatcher.cpp
            ./DrawUtil.cpp
            ./EditorContainer.cpp
            ./EntityEditor.cpp
            ./FontViewer.cpp
            ./FrameEditorBase.cpp
            ./FrameEditorContainer.cpp
            ./FrameEditorMultiBox.cpp
            ./FrameEditorSingleBox.cpp
            ./FrameEditorSingleLine.cpp
            ./FrameEditorUtil.cpp
            ./GenericCheckbox.cpp
            ./GenericFrame.cpp
            ./GenericInput.cpp
            ./GenericList.cpp
            ./GenericListFrame.cpp
            ./main.cpp
            ./MapEditor.cpp
            ./MapEditorEntityLayerManager.cpp
            ./MapEditorEntityManager.cpp
            ./MapEditorEntitySelector.cpp
            ./MapEditorLayerList.cpp
            ./MapEditorParalaxLayer.cpp
            ./MapEditorParalaxLayerManager.cpp
            ./MapEditorPath.cpp
            ./MapEditorPathManager.cpp
            ./MapEditorSelector.cpp
            ./MapEditorTileLayerManager.cpp
            ./MapEditorTileManager.cpp
            ./MapEditorTileSelector.cpp
            ./MapEditorToolBase.cpp
            ./MapEditorToolEntityLayerDraw.cpp
            ./MapEditorToolEntityLayerSelect.cpp
            ./MapEditorToolManualTileLayerDraw.cpp
            ./MapEditorToolManualTileLayerSelect.cpp
            ./MapEditorToolPathCreate.cpp
            ./MapEditorToolPathEditor.cpp
            ./MapEditorToolVolumeCreate.cpp
            ./MapEditorToolVolumeEditor.cpp
            ./MapEditorViewer.cpp
            ./MapEditorVolume.cpp
            ./MapEditorVolumeManager.cpp
            ./PropertyEditor.cpp
            ./PropertyEditorBool.cpp
            ./PropertyEditorEnum.cpp
            ./PropertyEditorFile.cpp
            ./PropertyEditorList.cpp
            ./PropertyEditorNumber.cpp
            ./PropertyEditorPolymorphic.cpp
            ./PropertyEditorString.cpp
            ./PropertyEditorStruct.cpp
            ./PropertyEditorWidget.cpp
            ./ScrollingPanel.cpp
            ./SimpleLabelListElement.cpp
            ./SpriteBaseAnimationEditor.cpp
            ./SpriteBaseAnimationFrameListEditorDialog.cpp
            ./SpriteBaseAnimationListElement.cpp
            ./SpriteBaseAnimationListFrameElement.cpp
            ./SpriteBaseEditor.cpp
            ./SpriteBaseTextureEditor.cpp
            ./SpriteBaseTextureFrameElement.cpp
            ./SpriteBaseTextureFrameList.cpp
            ./SpriteBaseTextureImportDialog.cpp
            ./SpriteBaseTextureLoadList.cpp
            ./SpriteBaseTimeline.cpp
            ./SpriteBaseTimelineElement.cpp
            ./SpriteEditor.cpp
            ./TextureViewer.cpp
            ./TextureViewerWidget.cpp
            ./TileSheetEditor.cpp
            ./GeneratedFiles/qrc_EditorContainer.cpp
            )
add_library(Editor ${GENERIC_SRC_Editor} ${PLATFORM_SRC_Editor} )