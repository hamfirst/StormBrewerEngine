cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}
                    ${PROJECT_SOURCE_DIR}/External
                    ${PROJECT_SOURCE_DIR}/StormTech
                    ${PROJECT_SOURCE_DIR}/Tools
                    ${PROJECT_SOURCE_DIR}/Shared
                    ${PROJECT_SOURCE_DIR}/Project
                    ${PROJECT_SOURCE_DIR}/Lobby)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
cmake_policy(SET CMP0071 OLD)
find_package(Qt5 REQUIRED COMPONENTS Core Widgets)
include_directories(${Qt5Widgets_INCLUDE_DIRS})
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(GENERIC_SRC_Editor 
            AnimationFrameEditor.ui
            AtlasEditor.cpp
            AtlasElementEditor.cpp
            AtlasElementEditorContainer.cpp
            AtlasTextureEditor.cpp
            AtlasTextureImportDialog.cpp
            AtlasTextureImportDialog.ui
            AtlasTextureLoadList.cpp
            AudioViewer.cpp
            ConfigEditor.cpp
            ConnectingDialog.cpp
            ConnectingDialog.ui
            DistributionContainer.cpp
            DistributionList.cpp
            DocumentEditorBase.cpp
            DocumentEditorConfig.cpp
            DocumentEditorWidgetBase.cpp
            DocumentListValueWatcher.cpp
            DocumentServerThread.cpp
            DocumentSubValueListMirror.cpp
            DocumentValueWatcher.cpp
            DrawUtil.cpp
            DrawUtilQt.cpp
            EditorContainer.cpp
            EditorContainer.qrc
            EditorContainer.ui
            EditorGL.cpp
            EntityEditor.cpp
            FontViewer.cpp
            FrameEditorAnchorEditor.cpp
            FrameEditorAnchorManager.cpp
            FrameEditorBase.cpp
            FrameEditorContainer.cpp
            FrameEditorLowerEdge.cpp
            FrameEditorMultiBox.cpp
            FrameEditorSingleBox.cpp
            FrameEditorSingleLine.cpp
            FrameEditorUtil.cpp
            GameClientWidget.cpp
            GameHostWidget.cpp
            GameServerWidget.cpp
            GenericCheckbox.cpp
            GenericComboBox.cpp
            GenericFrame.cpp
            GenericInput.cpp
            GenericList.cpp
            GenericListFrame.cpp
            GeometryEditorBase.cpp
            MapEditor.cpp
            MapEditorAnchor.cpp
            MapEditorEffectLayer.cpp
            MapEditorEntityLayerManager.cpp
            MapEditorEntityManager.cpp
            MapEditorEntitySelector.cpp
            MapEditorLayerList.cpp
            MapEditorParallaxLayer.cpp
            MapEditorParallaxLayerManager.cpp
            MapEditorParallaxObjectSelector.cpp
            MapEditorPath.cpp
            MapEditorPathManager.cpp
            MapEditorSelector.cpp
            MapEditorServerObjectManager.cpp
            MapEditorServerObjectSelector.cpp
            MapEditorTileLayerManager.cpp
            MapEditorTileManager.cpp
            MapEditorTileSelector.cpp
            MapEditorToolAllLayers.cpp
            MapEditorToolAnchorCreate.cpp
            MapEditorToolAnchorEditor.cpp
            MapEditorToolAnchorMultiEditor.cpp
            MapEditorToolBase.cpp
            MapEditorToolEntityLayerDraw.cpp
            MapEditorToolEntityLayerSelect.cpp
            MapEditorToolManualTileLayerDraw.cpp
            MapEditorToolManualTileLayerPreview.cpp
            MapEditorToolManualTileLayerSelect.cpp
            MapEditorToolParallaxObjectLayerDraw.cpp
            MapEditorToolParallaxObjectLayerSelect.cpp
            MapEditorToolPathCreate.cpp
            MapEditorToolPathEditor.cpp
            MapEditorToolPathMultiEditor.cpp
            MapEditorToolServerObjectLayerDraw.cpp
            MapEditorToolServerObjectLayerSelect.cpp
            MapEditorToolVolumeCreate.cpp
            MapEditorToolVolumeEditor.cpp
            MapEditorToolVolumeMultiEditor.cpp
            MapEditorTypes.refl.cpp
            MapEditorViewer.cpp
            MapEditorVolume.cpp
            MapEditorVolumeManager.cpp
            PropertyEditor.cpp
            PropertyEditorBool.cpp
            PropertyEditorEnum.cpp
            PropertyEditorFile.cpp
            PropertyEditorHandle.cpp
            PropertyEditorList.cpp
            PropertyEditorNumber.cpp
            PropertyEditorPolymorphic.cpp
            PropertyEditorString.cpp
            PropertyEditorStruct.cpp
            PropertyEditorWidget.cpp
            QtStyle.cpp
            ScrollingPanel.cpp
            SelectFromListDialog.cpp
            SelectFromListDialog.ui
            ServerObjectEditor.cpp
            SimpleLabelListElement.cpp
            SpriteBaseAnimationEditor.cpp
            SpriteBaseAnimationEventEditorDialog.cpp
            SpriteBaseAnimationFrameListEditorDialog.cpp
            SpriteBaseAnimationListElement.cpp
            SpriteBaseAnimationListFrameElement.cpp
            SpriteBaseEditor.cpp
            SpriteBaseFrameDisplay.cpp
            SpriteBaseSkinEditor.cpp
            SpriteBaseSkinListElement.cpp
            SpriteBaseSkinListTextureElement.cpp
            SpriteBaseTextureEditor.cpp
            SpriteBaseTextureFrameElement.cpp
            SpriteBaseTextureFrameList.cpp
            SpriteBaseTextureImportDialog.cpp
            SpriteBaseTextureLoadList.cpp
            SpriteBaseTimeline.cpp
            SpriteBaseTimelineElement.cpp
            SpriteEditor.cpp
            SpriteTextureImportDialog.ui
            TextInputDialog.cpp
            TextInputDialog.ui
            TextureViewer.cpp
            TextureViewerWidget.cpp
            TileSheetEditor.cpp
            UIEditor.cpp
            UIEditorViewer.cpp
            VisualEffectEditor.cpp
            VisualEffectEditorEquationList.cpp
            VisualEffectEditorNodeList.cpp
            VisualEffectEditorPropertyContainer.cpp
            VisualEffectEditorViewer.cpp
            VisualEffectEquationEditor.cpp
            main.cpp
            #CPP_PLACEHOLDER
            )

set(GENERIC_HEADER_Editor 
            AtlasEditor.h
            AtlasElementEditor.h
            AtlasElementEditorContainer.h
            AtlasTextureEditor.h
            AtlasTextureImportDialog.h
            AtlasTextureLoadList.h
            AudioViewer.h
            ConfigEditor.h
            ConnectingDialog.h
            DistributionContainer.h
            DistributionList.h
            DocumentEditor.h
            DocumentEditorBase.h
            DocumentEditorConfig.h
            DocumentEditorWidgetBase.h
            DocumentListValueWatcher.h
            DocumentServerThread.h
            DocumentSubValueListMirror.h
            DocumentValueWatcher.h
            DrawUtil.h
            DrawUtilQt.h
            EditorContainer.h
            EntityEditor.h
            FontViewer.h
            FrameEditorAnchorEditor.h
            FrameEditorAnchorManager.h
            FrameEditorBase.h
            FrameEditorContainer.h
            FrameEditorLowerEdge.h
            FrameEditorMultiBox.h
            FrameEditorSingleBox.h
            FrameEditorSingleLine.h
            FrameEditorTypes.refl.h
            FrameEditorUtil.h
            GameClientWidget.h
            GameHostWidget.h
            GameServerWidget.h
            GenericCheckbox.h
            GenericComboBox.h
            GenericFrame.h
            GenericInput.h
            GenericList.h
            GenericListCreate.h
            GenericListFrame.h
            GeometryEditorBase.h
            MapEditor.h
            MapEditorAnchor.h
            MapEditorEffectLayer.h
            MapEditorEntityLayerManager.h
            MapEditorEntityManager.h
            MapEditorEntitySelector.h
            MapEditorLayer.h
            MapEditorLayerList.h
            MapEditorLayerManager.h
            MapEditorParallaxLayer.h
            MapEditorParallaxLayerManager.h
            MapEditorParallaxObjectSelector.h
            MapEditorPath.h
            MapEditorPathManager.h
            MapEditorSelector.h
            MapEditorServerObjectManager.h
            MapEditorServerObjectSelector.h
            MapEditorTileLayerManager.h
            MapEditorTileManager.h
            MapEditorTileSelector.h
            MapEditorToolAllLayers.h
            MapEditorToolAnchorCreate.h
            MapEditorToolAnchorEditor.h
            MapEditorToolAnchorMultiEditor.h
            MapEditorToolBase.h
            MapEditorToolEntityLayerDraw.h
            MapEditorToolEntityLayerSelect.h
            MapEditorToolManualTileLayerDraw.h
            MapEditorToolManualTileLayerPreview.h
            MapEditorToolManualTileLayerSelect.h
            MapEditorToolParallaxObjectLayerDraw.h
            MapEditorToolParallaxObjectLayerSelect.h
            MapEditorToolPathCreate.h
            MapEditorToolPathEditor.h
            MapEditorToolPathMultiEditor.h
            MapEditorToolServerObjectLayerDraw.h
            MapEditorToolServerObjectLayerSelect.h
            MapEditorToolVolumeCreate.h
            MapEditorToolVolumeEditor.h
            MapEditorToolVolumeMultiEditor.h
            MapEditorTypes.refl.h
            MapEditorViewer.h
            MapEditorVolume.h
            MapEditorVolumeManager.h
            PropertyEditor.h
            PropertyEditorBool.h
            PropertyEditorEnum.h
            PropertyEditorFile.h
            PropertyEditorHandle.h
            PropertyEditorList.h
            PropertyEditorNumber.h
            PropertyEditorPolymorphic.h
            PropertyEditorString.h
            PropertyEditorStruct.h
            PropertyEditorWidget.h
            ScrollingPanel.h
            SelectFromListDialog.h
            ServerObjectEditor.h
            SimpleLabelList.h
            SimpleLabelListElement.h
            SpriteBaseAnimationEditor.h
            SpriteBaseAnimationEventEditorDialog.h
            SpriteBaseAnimationFrameListEditorDialog.h
            SpriteBaseAnimationListElement.h
            SpriteBaseAnimationListFrameElement.h
            SpriteBaseEditor.h
            SpriteBaseFrameDisplay.h
            SpriteBaseSkinEditor.h
            SpriteBaseSkinListElement.h
            SpriteBaseSkinListTextureElement.h
            SpriteBaseTextureEditor.h
            SpriteBaseTextureFrameElement.h
            SpriteBaseTextureFrameList.h
            SpriteBaseTextureImportDialog.h
            SpriteBaseTextureLoadList.h
            SpriteBaseTimeline.h
            SpriteBaseTimelineElement.h
            SpriteEditor.h
            TextInputDialog.h
            TextureViewer.h
            TextureViewerWidget.h
            TileSheetEditor.h
            UIEditor.h
            UIEditorViewer.h
            VisualEffectEditor.h
            VisualEffectEditorEquationList.h
            VisualEffectEditorNodeList.h
            VisualEffectEditorNodeSelection.h
            VisualEffectEditorPropertyContainer.h
            VisualEffectEditorViewer.h
            VisualEffectEquationEditor.h
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


if(GENERATE_REFL)
  foreach(REFL_FILE ${GENERIC_REFL_Editor})
    string(REPLACE ".refl.h" ".refl.meta.h" META_FILE ${REFL_FILE})
    add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${META_FILE}
                       COMMAND stormrefl ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE} -- -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -std=c++17 -x c++ -Wno-pragma-once-outside-header -I${CMAKE_CURRENT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR}/StormTech -I${PROJECT_SOURCE_DIR}/Tools -I${PROJECT_SOURCE_DIR}/Shared -I${PROJECT_SOURCE_DIR}/Project -I${PROJECT_SOURCE_DIR}/Lobby -I${PROJECT_SOURCE_DIR}/External -I${CLANG_HEADER_PATH} -D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
                       MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE}
                       IMPLICIT_DEPENDS CXX ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE})
  endforeach()
endif()

add_library(Editor STATIC ${GENERIC_SRC_Editor} ${PLATFORM_SRC_Editor}
            ${GENERIC_HEADER_Editor} ${PLATFORM_HEADER_Editor})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${GENERIC_SRC_Editor} ${PLATFORM_SRC_Editor}
            ${GENERIC_HEADER_Editor} ${PLATFORM_HEADER_Editor})

