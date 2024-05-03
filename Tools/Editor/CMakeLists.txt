cmake_minimum_required(VERSION 3.20.0)

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

set(CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_AUTOUIC_SEARCH_PATHS}" UI)
set(CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_AUTOUIC_SEARCH_PATHS}" UI/UtilityWidgets)
set(CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_AUTOUIC_SEARCH_PATHS}" AssetEditors/FrameEditor)
set(CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_AUTOUIC_SEARCH_PATHS}" AssetEditors/Atlas)
set(GENERIC_SRC_Editor 
            AssetEditors/Atlas/AtlasEditor.cpp
            AssetEditors/Atlas/AtlasElementEditor.cpp
            AssetEditors/Atlas/AtlasElementEditorContainer.cpp
            AssetEditors/Atlas/AtlasTextureEditor.cpp
            AssetEditors/Atlas/AtlasTextureImportDialog.cpp
            AssetEditors/Atlas/AtlasTextureImportDialog.ui
            AssetEditors/Atlas/AtlasTextureLoadList.cpp
            AssetEditors/Audio/AudioViewer.cpp
            AssetEditors/Config/ConfigEditor.cpp
            AssetEditors/DocumentEditor/DocumentEditorBase.cpp
            AssetEditors/DocumentEditor/DocumentEditorConfig.cpp
            AssetEditors/DocumentEditor/DocumentEditorWidgetBase.cpp
            AssetEditors/Entity/EntityEditor.cpp
            AssetEditors/Font/FontViewer.cpp
            AssetEditors/FrameEditor/AnimationFrameEditor.ui
            AssetEditors/FrameEditor/FrameEditorAnchorEditor.cpp
            AssetEditors/FrameEditor/FrameEditorAnchorManager.cpp
            AssetEditors/FrameEditor/FrameEditorBase.cpp
            AssetEditors/FrameEditor/FrameEditorContainer.cpp
            AssetEditors/FrameEditor/FrameEditorLowerEdge.cpp
            AssetEditors/FrameEditor/FrameEditorMultiBox.cpp
            AssetEditors/FrameEditor/FrameEditorSingleBox.cpp
            AssetEditors/FrameEditor/FrameEditorSingleLine.cpp
            AssetEditors/FrameEditor/FrameEditorUtil.cpp
            AssetEditors/GeometryEditor/GeometryEditorBase.cpp
            AssetEditors/MapEditor/MapEditor.cpp
            AssetEditors/MapEditor/MapEditorAnchor.cpp
            AssetEditors/MapEditor/MapEditorEffectLayer.cpp
            AssetEditors/MapEditor/MapEditorEntityLayerManager.cpp
            AssetEditors/MapEditor/MapEditorEntityManager.cpp
            AssetEditors/MapEditor/MapEditorEntitySelector.cpp
            AssetEditors/MapEditor/MapEditorLayerList.cpp
            AssetEditors/MapEditor/MapEditorParallaxLayer.cpp
            AssetEditors/MapEditor/MapEditorParallaxLayerManager.cpp
            AssetEditors/MapEditor/MapEditorParallaxObjectSelector.cpp
            AssetEditors/MapEditor/MapEditorPath.cpp
            AssetEditors/MapEditor/MapEditorPathManager.cpp
            AssetEditors/MapEditor/MapEditorSelector.cpp
            AssetEditors/MapEditor/MapEditorServerObjectManager.cpp
            AssetEditors/MapEditor/MapEditorServerObjectSelector.cpp
            AssetEditors/MapEditor/MapEditorTileLayerManager.cpp
            AssetEditors/MapEditor/MapEditorTileManager.cpp
            AssetEditors/MapEditor/MapEditorTileSelector.cpp
            AssetEditors/MapEditor/MapEditorToolAllLayers.cpp
            AssetEditors/MapEditor/MapEditorToolAnchorCreate.cpp
            AssetEditors/MapEditor/MapEditorToolAnchorEditor.cpp
            AssetEditors/MapEditor/MapEditorToolAnchorMultiEditor.cpp
            AssetEditors/MapEditor/MapEditorToolBase.cpp
            AssetEditors/MapEditor/MapEditorToolEntityLayerDraw.cpp
            AssetEditors/MapEditor/MapEditorToolEntityLayerSelect.cpp
            AssetEditors/MapEditor/MapEditorToolManualTileLayerDraw.cpp
            AssetEditors/MapEditor/MapEditorToolManualTileLayerPreview.cpp
            AssetEditors/MapEditor/MapEditorToolManualTileLayerSelect.cpp
            AssetEditors/MapEditor/MapEditorToolParallaxObjectLayerDraw.cpp
            AssetEditors/MapEditor/MapEditorToolParallaxObjectLayerSelect.cpp
            AssetEditors/MapEditor/MapEditorToolPathCreate.cpp
            AssetEditors/MapEditor/MapEditorToolPathEditor.cpp
            AssetEditors/MapEditor/MapEditorToolPathMultiEditor.cpp
            AssetEditors/MapEditor/MapEditorToolServerObjectLayerDraw.cpp
            AssetEditors/MapEditor/MapEditorToolServerObjectLayerSelect.cpp
            AssetEditors/MapEditor/MapEditorToolVolumeCreate.cpp
            AssetEditors/MapEditor/MapEditorToolVolumeEditor.cpp
            AssetEditors/MapEditor/MapEditorToolVolumeMultiEditor.cpp
            AssetEditors/MapEditor/MapEditorTypes.refl.cpp
            AssetEditors/MapEditor/MapEditorViewer.cpp
            AssetEditors/MapEditor/MapEditorVolume.cpp
            AssetEditors/MapEditor/MapEditorVolumeManager.cpp
            AssetEditors/ServerObject/ServerObjectEditor.cpp
            AssetEditors/SpriteBase/SpriteBaseAnimationEditor.cpp
            AssetEditors/SpriteBase/SpriteBaseAnimationEventEditorDialog.cpp
            AssetEditors/SpriteBase/SpriteBaseAnimationFrameListEditorDialog.cpp
            AssetEditors/SpriteBase/SpriteBaseAnimationListElement.cpp
            AssetEditors/SpriteBase/SpriteBaseAnimationListFrameElement.cpp
            AssetEditors/SpriteBase/SpriteBaseEditor.cpp
            AssetEditors/SpriteBase/SpriteBaseFrameDisplay.cpp
            AssetEditors/SpriteBase/SpriteBaseSkinEditor.cpp
            AssetEditors/SpriteBase/SpriteBaseSkinListElement.cpp
            AssetEditors/SpriteBase/SpriteBaseSkinListTextureElement.cpp
            AssetEditors/SpriteBase/SpriteBaseTextureEditor.cpp
            AssetEditors/SpriteBase/SpriteBaseTextureFrameElement.cpp
            AssetEditors/SpriteBase/SpriteBaseTextureFrameList.cpp
            AssetEditors/SpriteBase/SpriteBaseTextureImportDialog.cpp
            AssetEditors/SpriteBase/SpriteBaseTextureLoadList.cpp
            AssetEditors/SpriteBase/SpriteBaseTimeline.cpp
            AssetEditors/SpriteBase/SpriteBaseTimelineElement.cpp
            AssetEditors/SpriteEditor/SpriteEditor.cpp
            AssetEditors/Texture/TextureViewer.cpp
            AssetEditors/Texture/TextureViewerWidget.cpp
            AssetEditors/TileSheet/TileSheetEditor.cpp
            AssetEditors/UI/UIEditor.cpp
            AssetEditors/UI/UIEditorViewer.cpp
            AssetEditors/VisualEffect/VisualEffectEditor.cpp
            AssetEditors/VisualEffect/VisualEffectEditorEquationList.cpp
            AssetEditors/VisualEffect/VisualEffectEditorNodeList.cpp
            AssetEditors/VisualEffect/VisualEffectEditorPropertyContainer.cpp
            AssetEditors/VisualEffect/VisualEffectEditorViewer.cpp
            AssetEditors/VisualEffect/VisualEffectEquationEditor.cpp
            Distribution/DistributionContainer.cpp
            Distribution/DistributionList.cpp
            DocumentServer/ConnectingDialog.cpp
            DocumentServer/ConnectingDialog.ui
            DocumentServer/DocumentServerThread.cpp
            EditorContainer.cpp
            EditorContainer.qrc
            EditorContainer.ui
            EditorGL.cpp
            Game/GameClientWidget.cpp
            Game/GameHostWidget.cpp
            Game/GameServerWidget.cpp
            UI/GenericWidgets/GenericCheckbox.cpp
            UI/GenericWidgets/GenericComboBox.cpp
            UI/GenericWidgets/GenericFrame.cpp
            UI/GenericWidgets/GenericInput.cpp
            UI/GenericWidgets/GenericList.cpp
            UI/GenericWidgets/GenericListFrame.cpp
            UI/PropertyEditors/PropertyEditor.cpp
            UI/PropertyEditors/PropertyEditorBool.cpp
            UI/PropertyEditors/PropertyEditorEnum.cpp
            UI/PropertyEditors/PropertyEditorFile.cpp
            UI/PropertyEditors/PropertyEditorHandle.cpp
            UI/PropertyEditors/PropertyEditorList.cpp
            UI/PropertyEditors/PropertyEditorNumber.cpp
            UI/PropertyEditors/PropertyEditorPolymorphic.cpp
            UI/PropertyEditors/PropertyEditorString.cpp
            UI/PropertyEditors/PropertyEditorStruct.cpp
            UI/PropertyEditors/PropertyEditorWidget.cpp
            UI/QtStyle.cpp
            UI/UtilityWidgets/ScrollingPanel.cpp
            UI/UtilityWidgets/SelectFromListDialog.cpp
            UI/UtilityWidgets/SelectFromListDialog.ui
            UI/UtilityWidgets/SimpleLabelListElement.cpp
            UI/UtilityWidgets/SpriteTextureImportDialog.ui
            UI/UtilityWidgets/TextInputDialog.cpp
            UI/UtilityWidgets/TextInputDialog.ui
            Utility/DocumentListValueWatcher.cpp
            Utility/DocumentSubValueListMirror.cpp
            Utility/DocumentValueWatcher.cpp
            Utility/DrawUtil.cpp
            Utility/DrawUtilQt.cpp
            main.cpp
            #CPP_PLACEHOLDER
            )

set(GENERIC_HEADER_Editor 
            AssetEditors/Atlas/AtlasEditor.h
            AssetEditors/Atlas/AtlasElementEditor.h
            AssetEditors/Atlas/AtlasElementEditorContainer.h
            AssetEditors/Atlas/AtlasTextureEditor.h
            AssetEditors/Atlas/AtlasTextureImportDialog.h
            AssetEditors/Atlas/AtlasTextureLoadList.h
            AssetEditors/Audio/AudioViewer.h
            AssetEditors/Config/ConfigEditor.h
            AssetEditors/DocumentEditor/DocumentEditor.h
            AssetEditors/DocumentEditor/DocumentEditorBase.h
            AssetEditors/DocumentEditor/DocumentEditorConfig.h
            AssetEditors/DocumentEditor/DocumentEditorWidgetBase.h
            AssetEditors/Entity/EntityEditor.h
            AssetEditors/Font/FontViewer.h
            AssetEditors/FrameEditor/FrameEditorAnchorEditor.h
            AssetEditors/FrameEditor/FrameEditorAnchorManager.h
            AssetEditors/FrameEditor/FrameEditorBase.h
            AssetEditors/FrameEditor/FrameEditorContainer.h
            AssetEditors/FrameEditor/FrameEditorLowerEdge.h
            AssetEditors/FrameEditor/FrameEditorMultiBox.h
            AssetEditors/FrameEditor/FrameEditorSingleBox.h
            AssetEditors/FrameEditor/FrameEditorSingleLine.h
            AssetEditors/FrameEditor/FrameEditorTypes.refl.h
            AssetEditors/FrameEditor/FrameEditorTypes.refl.meta.h
            AssetEditors/FrameEditor/FrameEditorUtil.h
            AssetEditors/GeometryEditor/GeometryEditorBase.h
            AssetEditors/MapEditor/MapEditor.h
            AssetEditors/MapEditor/MapEditorAnchor.h
            AssetEditors/MapEditor/MapEditorEffectLayer.h
            AssetEditors/MapEditor/MapEditorEntityLayerManager.h
            AssetEditors/MapEditor/MapEditorEntityManager.h
            AssetEditors/MapEditor/MapEditorEntitySelector.h
            AssetEditors/MapEditor/MapEditorLayer.h
            AssetEditors/MapEditor/MapEditorLayerList.h
            AssetEditors/MapEditor/MapEditorLayerManager.h
            AssetEditors/MapEditor/MapEditorParallaxLayer.h
            AssetEditors/MapEditor/MapEditorParallaxLayerManager.h
            AssetEditors/MapEditor/MapEditorParallaxObjectSelector.h
            AssetEditors/MapEditor/MapEditorPath.h
            AssetEditors/MapEditor/MapEditorPathManager.h
            AssetEditors/MapEditor/MapEditorSelector.h
            AssetEditors/MapEditor/MapEditorServerObjectManager.h
            AssetEditors/MapEditor/MapEditorServerObjectSelector.h
            AssetEditors/MapEditor/MapEditorTileLayerManager.h
            AssetEditors/MapEditor/MapEditorTileManager.h
            AssetEditors/MapEditor/MapEditorTileSelector.h
            AssetEditors/MapEditor/MapEditorToolAllLayers.h
            AssetEditors/MapEditor/MapEditorToolAnchorCreate.h
            AssetEditors/MapEditor/MapEditorToolAnchorEditor.h
            AssetEditors/MapEditor/MapEditorToolAnchorMultiEditor.h
            AssetEditors/MapEditor/MapEditorToolBase.h
            AssetEditors/MapEditor/MapEditorToolEntityLayerDraw.h
            AssetEditors/MapEditor/MapEditorToolEntityLayerSelect.h
            AssetEditors/MapEditor/MapEditorToolManualTileLayerDraw.h
            AssetEditors/MapEditor/MapEditorToolManualTileLayerPreview.h
            AssetEditors/MapEditor/MapEditorToolManualTileLayerSelect.h
            AssetEditors/MapEditor/MapEditorToolParallaxObjectLayerDraw.h
            AssetEditors/MapEditor/MapEditorToolParallaxObjectLayerSelect.h
            AssetEditors/MapEditor/MapEditorToolPathCreate.h
            AssetEditors/MapEditor/MapEditorToolPathEditor.h
            AssetEditors/MapEditor/MapEditorToolPathMultiEditor.h
            AssetEditors/MapEditor/MapEditorToolServerObjectLayerDraw.h
            AssetEditors/MapEditor/MapEditorToolServerObjectLayerSelect.h
            AssetEditors/MapEditor/MapEditorToolVolumeCreate.h
            AssetEditors/MapEditor/MapEditorToolVolumeEditor.h
            AssetEditors/MapEditor/MapEditorToolVolumeMultiEditor.h
            AssetEditors/MapEditor/MapEditorTypes.refl.h
            AssetEditors/MapEditor/MapEditorTypes.refl.meta.h
            AssetEditors/MapEditor/MapEditorViewer.h
            AssetEditors/MapEditor/MapEditorVolume.h
            AssetEditors/MapEditor/MapEditorVolumeManager.h
            AssetEditors/ServerObject/ServerObjectEditor.h
            AssetEditors/SpriteBase/SpriteBaseAnimationEditor.h
            AssetEditors/SpriteBase/SpriteBaseAnimationEventEditorDialog.h
            AssetEditors/SpriteBase/SpriteBaseAnimationFrameListEditorDialog.h
            AssetEditors/SpriteBase/SpriteBaseAnimationListElement.h
            AssetEditors/SpriteBase/SpriteBaseAnimationListFrameElement.h
            AssetEditors/SpriteBase/SpriteBaseEditor.h
            AssetEditors/SpriteBase/SpriteBaseFrameDisplay.h
            AssetEditors/SpriteBase/SpriteBaseSkinEditor.h
            AssetEditors/SpriteBase/SpriteBaseSkinListElement.h
            AssetEditors/SpriteBase/SpriteBaseSkinListTextureElement.h
            AssetEditors/SpriteBase/SpriteBaseTextureEditor.h
            AssetEditors/SpriteBase/SpriteBaseTextureFrameElement.h
            AssetEditors/SpriteBase/SpriteBaseTextureFrameList.h
            AssetEditors/SpriteBase/SpriteBaseTextureImportDialog.h
            AssetEditors/SpriteBase/SpriteBaseTextureLoadList.h
            AssetEditors/SpriteBase/SpriteBaseTimeline.h
            AssetEditors/SpriteBase/SpriteBaseTimelineElement.h
            AssetEditors/SpriteEditor/SpriteEditor.h
            AssetEditors/Texture/TextureViewer.h
            AssetEditors/Texture/TextureViewerWidget.h
            AssetEditors/TileSheet/TileSheetEditor.h
            AssetEditors/UI/UIEditor.h
            AssetEditors/UI/UIEditorViewer.h
            AssetEditors/VisualEffect/VisualEffectEditor.h
            AssetEditors/VisualEffect/VisualEffectEditorEquationList.h
            AssetEditors/VisualEffect/VisualEffectEditorNodeList.h
            AssetEditors/VisualEffect/VisualEffectEditorNodeSelection.h
            AssetEditors/VisualEffect/VisualEffectEditorPropertyContainer.h
            AssetEditors/VisualEffect/VisualEffectEditorViewer.h
            AssetEditors/VisualEffect/VisualEffectEquationEditor.h
            Distribution/DistributionContainer.h
            Distribution/DistributionList.h
            DocumentServer/ConnectingDialog.h
            DocumentServer/DocumentServerThread.h
            EditorContainer.h
            Game/GameClientWidget.h
            Game/GameHostWidget.h
            Game/GameServerWidget.h
            UI/GenericWidgets/GenericCheckbox.h
            UI/GenericWidgets/GenericComboBox.h
            UI/GenericWidgets/GenericFrame.h
            UI/GenericWidgets/GenericInput.h
            UI/GenericWidgets/GenericList.h
            UI/GenericWidgets/GenericListCreate.h
            UI/GenericWidgets/GenericListFrame.h
            UI/PropertyEditors/PropertyEditor.h
            UI/PropertyEditors/PropertyEditorBool.h
            UI/PropertyEditors/PropertyEditorEnum.h
            UI/PropertyEditors/PropertyEditorFile.h
            UI/PropertyEditors/PropertyEditorHandle.h
            UI/PropertyEditors/PropertyEditorList.h
            UI/PropertyEditors/PropertyEditorNumber.h
            UI/PropertyEditors/PropertyEditorPolymorphic.h
            UI/PropertyEditors/PropertyEditorString.h
            UI/PropertyEditors/PropertyEditorStruct.h
            UI/PropertyEditors/PropertyEditorWidget.h
            UI/UtilityWidgets/ScrollingPanel.h
            UI/UtilityWidgets/SelectFromListDialog.h
            UI/UtilityWidgets/SimpleLabelList.h
            UI/UtilityWidgets/SimpleLabelListElement.h
            UI/UtilityWidgets/TextInputDialog.h
            Utility/DocumentListValueWatcher.h
            Utility/DocumentSubValueListMirror.h
            Utility/DocumentValueWatcher.h
            Utility/DrawUtil.h
            Utility/DrawUtilQt.h
            #HEADER_PLACEHOLDER
            )

set(GENERIC_REFL_Editor 
            AssetEditors/FrameEditor/FrameEditorTypes.refl.h
            AssetEditors/MapEditor/MapEditorTypes.refl.h
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


add_library(Editor STATIC ${GENERIC_SRC_Editor} ${PLATFORM_SRC_Editor}
            ${GENERIC_HEADER_Editor} ${PLATFORM_HEADER_Editor})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${GENERIC_SRC_Editor} ${PLATFORM_SRC_Editor}
            ${GENERIC_HEADER_Editor} ${PLATFORM_HEADER_Editor})

if(GENERATE_REFL)
  foreach(REFL_FILE ${GENERIC_REFL_Editor})
    string(REPLACE ".refl.h" ".refl.meta.h" META_FILE ${REFL_FILE})
    add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${META_FILE}
                       COMMAND stormrefl ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE} -- -I${CLANG_HEADER_PATH} "-I$<JOIN:$<TARGET_PROPERTY:Editor,INCLUDE_DIRECTORIES>,;-I>" -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -std=c++17 -x c++ -Wno-pragma-once-outside-header -D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
                       COMMAND_EXPAND_LISTS
                       VERBATIM
                       MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE}
                       IMPLICIT_DEPENDS CXX ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE})
  endforeach()
endif()

