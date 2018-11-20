cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/External ${PROJECT_SOURCE_DIR}/StormTech ${PROJECT_SOURCE_DIR}/Tools ${PROJECT_SOURCE_DIR}/Shared ${PROJECT_SOURCE_DIR}/Project)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
cmake_policy(SET CMP0071 OLD)
find_package(Qt5 REQUIRED COMPONENTS Core Widgets)
include_directories(${Qt5Widgets_INCLUDE_DIRS})
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(GENERIC_SRC_Editor 
            UIEditorPropertyContainer.cpp
            PropertyEditorFile.cpp
            MapEditorToolAnchorCreate.cpp
            EditorGL.cpp
            PropertyEditorEnum.cpp
            ScrollingPanel.cpp
            MapEditorEntityManager.cpp
            SpriteEditor.cpp
            SpriteBaseAnimationListFrameElement.cpp
            MapEditorPathManager.cpp
            SpriteBaseTextureFrameElement.cpp
            UIOutputEquationEditor.cpp
            DrawUtilQt.cpp
            ConnectingDialog.ui
            MapEditorToolVolumeMultiEditor.cpp
            MapEditorEffectLayer.cpp
            VisualEffectEditorNodeList.cpp
            MapEditorToolAnchorEditor.cpp
            MapEditorEntityLayerManager.cpp
            UIEditorNodeList.cpp
            FrameEditorAnchorManager.cpp
            SpriteBaseAnimationEditor.cpp
            SpriteBaseSkinListElement.cpp
            DocumentEditorWidgetBase.cpp
            GameClientWidget.cpp
            MapEditorToolParalaxObjectLayerDraw.cpp
            MapEditorViewer.cpp
            DrawUtil.cpp
            SpriteBaseTimelineElement.cpp
            PropertyEditorList.cpp
            SpriteBaseAnimationFrameListEditorDialog.cpp
            UIEditor.cpp
            SpriteBaseTextureLoadList.cpp
            EditorContainer.ui
            MapEditorAnchor.cpp
            PropertyEditor.cpp
            TextInputDialog.ui
            MapEditorPath.cpp
            MapEditorToolAnchorMultiEditor.cpp
            VisualEffectEditor.cpp
            MapEditorTypes.refl.cpp
            SpriteBaseAnimationListElement.cpp
            ServerObjectEditor.cpp
            GameHostWidget.cpp
            MapEditorEntitySelector.cpp
            SpriteBaseSkinEditor.cpp
            MapEditorVolume.cpp
            MapEditorToolServerObjectLayerSelect.cpp
            MapEditorToolPathCreate.cpp
            MapEditorToolServerObjectLayerDraw.cpp
            VisualEffectEditorViewer.cpp
            SpriteTextureImportDialog.ui
            MapEditorToolVolumeEditor.cpp
            SpriteBaseSkinListTextureElement.cpp
            DocumentServerThread.cpp
            SpriteBaseTextureImportDialog.cpp
            MapEditorServerObjectManager.cpp
            FrameEditorAnchorEditor.cpp
            MapEditorVolumeManager.cpp
            MapEditorToolEntityLayerDraw.cpp
            TextureViewer.cpp
            FontViewer.cpp
            VisualEffectEditorEquationList.cpp
            ConfigEditor.cpp
            PropertyEditorPolymorphic.cpp
            MapEditorTileManager.cpp
            MapEditor.cpp
            FrameEditorMultiBox.cpp
            MapEditorToolEntityLayerSelect.cpp
            MapEditorParalaxLayerManager.cpp
            FrameEditorSingleBox.cpp
            DocumentEditorBase.cpp
            MapEditorLayerList.cpp
            UIEditorOutputEquationList.cpp
            MapEditorToolManualTileLayerDraw.cpp
            SpriteBaseEditor.cpp
            DocumentEditorConfig.cpp
            MapEditorToolBase.cpp
            FrameEditorSingleLine.cpp
            MapEditorServerObjectSelector.cpp
            DocumentSubValueListMirror.cpp
            SpriteBaseTextureEditor.cpp
            main.cpp
            GenericInput.cpp
            MapEditorToolManualTileLayerSelect.cpp
            FrameEditorBase.cpp
            MapEditorSelector.cpp
            VisualEffectEquationEditor.cpp
            MapEditorParalaxObjectSelector.cpp
            MapEditorTileSelector.cpp
            UIEquationEditor.cpp
            GenericList.cpp
            VisualEffectEditorPropertyContainer.cpp
            UIEditorEquationList.cpp
            SimpleLabelListElement.cpp
            SelectFromListDialog.ui
            UIEditorViewer.cpp
            EditorContainer.qrc
            FrameEditorUtil.cpp
            TileSheetEditor.cpp
            PropertyEditorString.cpp
            TextInputDialog.cpp
            GenericFrame.cpp
            GenericCheckbox.cpp
            MapEditorParalaxLayer.cpp
            MapEditorToolAllLayers.cpp
            GameServerWidget.cpp
            ConnectingDialog.cpp
            PropertyEditorNumber.cpp
            MapEditorTileLayerManager.cpp
            MapEditorToolPathEditor.cpp
            SpriteBaseTextureFrameList.cpp
            MapEditorToolVolumeCreate.cpp
            MapEditorToolPathMultiEditor.cpp
            PropertyEditorHandle.cpp
            GenericListFrame.cpp
            SpriteBaseTimeline.cpp
            EditorContainer.cpp
            SelectFromListDialog.cpp
            DocumentListValueWatcher.cpp
            FrameEditorLowerEdge.cpp
            DocumentValueWatcher.cpp
            AudioViewer.cpp
            AnimationFrameEditor.ui
            MapEditorToolParalaxObjectLayerSelect.cpp
            PropertyEditorStruct.cpp
            TextureViewerWidget.cpp
            EntityEditor.cpp
            PropertyEditorBool.cpp
            SpriteBaseFrameDisplay.cpp
            SpriteBaseAnimationEventEditorDialog.cpp
            MapEditorToolManualTileLayerPreview.cpp
            FrameEditorContainer.cpp
            PropertyEditorWidget.cpp
            GenericComboBox.cpp
            AtlasEditor.cpp
            AtlasTextureLoadList.cpp
            AtlasTextureEditor.cpp
            AtlasTextureImportDialog.cpp
            GeometryEditorBase.cpp
            AtlasElementEditor.cpp
            #CPP_PLACEHOLDER
            )

set(GENERIC_HEADER_Editor 
            PropertyEditorStruct.h
            DocumentEditorWidgetBase.h
            MapEditorToolPathEditor.h
            PropertyEditorNumber.h
            DrawUtil.h
            MapEditorLayer.h
            SpriteBaseAnimationFrameListEditorDialog.h
            MapEditorParalaxLayer.h
            UIEditor.h
            MapEditorToolParalaxObjectLayerSelect.h
            MapEditorToolServerObjectLayerSelect.h
            ConnectingDialog.h
            UIEditorPropertyContainer.h
            FrameEditorAnchorEditor.h
            VisualEffectEditorNodeSelection.h
            SpriteBaseTextureImportDialog.h
            MapEditorToolAnchorMultiEditor.h
            PropertyEditorString.h
            PropertyEditorFile.h
            FrameEditorLowerEdge.h
            UIEditorNode.h
            MapEditorViewer.h
            UIEditorEquationList.h
            SpriteBaseSkinEditor.h
            MapEditorTileSelector.h
            MapEditorToolBase.h
            MapEditorEntityLayerManager.h
            GameClientWidget.h
            ScrollingPanel.h
            MapEditorToolAnchorCreate.h
            SpriteBaseFrameDisplay.h
            VisualEffectEditorPropertyContainer.h
            MapEditorPath.h
            SpriteBaseAnimationEditor.h
            FrameEditorSingleLine.h
            UIOutputEquationEditor.h
            SpriteBaseEditor.h
            MapEditorToolServerObjectLayerDraw.h
            ConfigEditor.h
            MapEditorToolManualTileLayerPreview.h
            MapEditorToolPathCreate.h
            VisualEffectEquationEditor.h
            EditorContainer.h
            MapEditorToolParalaxObjectLayerDraw.h
            TextInputDialog.h
            UIEditorNodeList.h
            FrameEditorTypes.refl.h
            MapEditorServerObjectManager.h
            MapEditorSelector.h
            SpriteBaseAnimationListFrameElement.h
            TileSheetEditor.h
            MapEditorToolManualTileLayerSelect.h
            GameHostWidget.h
            TextureViewer.h
            GenericFrame.h
            MapEditorLayerList.h
            FrameEditorContainer.h
            SpriteBaseTextureFrameElement.h
            DocumentValueWatcher.h
            PropertyEditorEnum.h
            MapEditorVolume.h
            MapEditorTypes.refl.h
            FrameEditorAnchorManager.h
            SpriteBaseTimeline.h
            DocumentSubValueListMirror.h
            DocumentServerThread.h
            MapEditor.h
            FrameEditorUtil.h
            VisualEffectEditorEquationList.h
            MapEditorEntitySelector.h
            FrameEditorTypes.refl.meta.h
            SpriteBaseTextureFrameList.h
            GenericInput.h
            MapEditorParalaxLayerManager.h
            MapEditorTileLayerManager.h
            VisualEffectEditorNodeList.h
            UIEditorViewer.h
            UIEquationEditor.h
            MapEditorEntityManager.h
            SpriteBaseAnimationListElement.h
            MapEditorParalaxObjectSelector.h
            MapEditorToolAllLayers.h
            PropertyEditorBool.h
            FrameEditorMultiBox.h
            PropertyEditor.h
            MapEditorToolAnchorEditor.h
            VisualEffectEditorViewer.h
            DocumentEditorConfig.h
            SpriteBaseSkinListTextureElement.h
            MapEditorServerObjectSelector.h
            PropertyEditorWidget.h
            MapEditorLayerManager.h
            MapEditorTileManager.h
            FrameEditorBase.h
            GameServerWidget.h
            MapEditorToolVolumeCreate.h
            SpriteBaseAnimationEventEditorDialog.h
            MapEditorVolumeManager.h
            MapEditorToolVolumeMultiEditor.h
            PropertyEditorList.h
            PropertyEditorHandle.h
            UIEditorOutputEquationList.h
            SimpleLabelListElement.h
            GenericListCreate.h
            MapEditorToolEntityLayerSelect.h
            GenericComboBox.h
            MapEditorEffectLayer.h
            GenericCheckbox.h
            TextureViewerWidget.h
            PropertyEditorPolymorphic.h
            SelectFromListDialog.h
            MapEditorToolEntityLayerDraw.h
            MapEditorTypes.refl.meta.h
            GenericList.h
            DocumentEditorBase.h
            MapEditorToolVolumeEditor.h
            MapEditorAnchor.h
            SpriteBaseTextureEditor.h
            DrawUtilQt.h
            DocumentListValueWatcher.h
            AudioViewer.h
            DocumentEditor.h
            SpriteEditor.h
            SpriteBaseTimelineElement.h
            MapEditorToolPathMultiEditor.h
            GenericListFrame.h
            MapEditorToolManualTileLayerDraw.h
            MapEditorPathManager.h
            SpriteBaseTextureLoadList.h
            SimpleLabelList.h
            ServerObjectEditor.h
            FontViewer.h
            EntityEditor.h
            SpriteBaseSkinListElement.h
            VisualEffectEditor.h
            FrameEditorSingleBox.h
            AtlasEditor.h
            AtlasTextureLoadList.h
            AtlasTextureEditor.h
            AtlasTextureImportDialog.h
            GeometryEditorBase.h
            AtlasElementEditor.h
            #HEADER_PLACEHOLDER
            )

set(GENERIC_REFL_Editor 
            FrameEditorTypes.refl.h
            MapEditorTypes.refl.h
            #REFL_PLACEHOLDER
            )

if (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(${PROJECT_SOURCE_DIR}/External/Windows)
  set(PLATFORM_SRC_Editor 
            )

set(PLATFORM_HEADER_Editor 
            )
endif()
if (WEB)
  add_definitions(-D_WEB)
  include_directories(${PROJECT_SOURCE_DIR}/External/Web)
  set(PLATFORM_SRC_Editor 
            )

set(PLATFORM_HEADER_Editor 
            )
endif()
if (IOS)
  add_definitions(-D_IOS)
  include_directories(${PROJECT_SOURCE_DIR}/External/IOS)
  set(PLATFORM_SRC_Editor 
            )

set(PLATFORM_HEADER_Editor 
            )
endif()
if (APPLE AND NOT IOS)
  add_definitions(-D_MACOS)
  include_directories(${PROJECT_SOURCE_DIR}/External/MacOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_Editor 
            )

set(PLATFORM_HEADER_Editor 
            )
endif()
if (ANDROID)
  add_definitions(-D_ANDROID)
  include_directories(${PROJECT_SOURCE_DIR}/External/Android)
  set(PLATFORM_SRC_Editor 
            )

set(PLATFORM_HEADER_Editor 
            )
endif()
if (UNIX AND NOT APPLE)
  add_definitions(-D_LINUX)
  include_directories(${PROJECT_SOURCE_DIR}/External/Linux)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_Editor 
            )

set(PLATFORM_HEADER_Editor 
            )
endif()


foreach(REFL_FILE ${GENERIC_REFL_Editor})
  string(REPLACE ".refl.h" ".refl.meta.h" META_FILE ${REFL_FILE})
  add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${META_FILE}
                     COMMAND stormrefl ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE} -- -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -std=c++17 -x c++ -Wno-pragma-once-outside-header -I${CMAKE_CURRENT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR}/StormTech -I${PROJECT_SOURCE_DIR}/Tools -I${PROJECT_SOURCE_DIR}/Shared -I${PROJECT_SOURCE_DIR}/Project -I${PROJECT_SOURCE_DIR}/External -I${CLANG_HEADER_PATH} -D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
                     MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE}
                     IMPLICIT_DEPENDS CXX ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE})
endforeach()

add_library(Editor STATIC ${GENERIC_SRC_Editor} ${PLATFORM_SRC_Editor}
            ${GENERIC_HEADER_Editor} ${PLATFORM_HEADER_Editor})
