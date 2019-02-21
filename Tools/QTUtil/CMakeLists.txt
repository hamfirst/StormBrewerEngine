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
set(GENERIC_SRC_QTUtil 
            FocusWatcher.cpp
            QTUtil.cpp
            DraggableList.cpp
            QtLerpVar.cpp
            LerpVar.cpp
            AnimationTrack.cpp
            ExpandableList.cpp
            )

set(GENERIC_HEADER_QTUtil 
            AnimationTrack.h
            FocusWatcher.h
            DraggableList.h
            VectorRearrange.h
            ExpandableList.h
            qtutil_global.h
            LerpVar.h
            QtLerpVar.h
            QTUtil.h
            )

add_library(QTUtil STATIC ${GENERIC_SRC_QTUtil} ${GENERIC_HEADER_QTUtil})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${GENERIC_SRC_QTUtil} ${GENERIC_HEADER_QTUtil})

