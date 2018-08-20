cmake_minimum_required(VERSION 3.0)

include_directories(. ../. .././External)
set(CMAKE_CXX_STANDARD 14)

set(GENERIC_SRC_QTUtil 
            ./AnimationTrack.cpp
            ./DraggableList.cpp
            ./ExpandableList.cpp
            ./FocusWatcher.cpp
            ./LerpVar.cpp
            ./QtLerpVar.cpp
            ./QTUtil.cpp
            ./GeneratedFiles/CoreOpt/moc_AnimationTrack.cpp
            ./GeneratedFiles/CoreOpt/moc_DraggableList.cpp
            ./GeneratedFiles/CoreOpt/moc_ExpandableList.cpp
            ./GeneratedFiles/CoreOpt/moc_FocusWatcher.cpp
            ./GeneratedFiles/CoreOpt/moc_QtLerpVar.cpp
            #CPP_PLACEHOLDER
            )
set(GENERIC_HEADER_QTUtil 
            ./AnimationTrack.h
            ./DraggableList.h
            ./ExpandableList.h
            ./FocusWatcher.h
            ./LerpVar.h
            ./QtLerpVar.h
            ./QTUtil.h
            ./qtutil_global.h
            ./VectorRearrange.h
            #HEADER_PLACEHOLDER
            )
set(GENERIC_REFL_QTUtil 
            #REFL_PLACEHOLDER
            )

if (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(.././External/Windows)
  set(PLATFORM_SRC_QTUtil 
            #CPP_WINDOWS_PLACEHOLDER
            )
endif()
if (WEB)
  add_definitions(-D_WEB)
  include_directories(.././External/Web)
  set(PLATFORM_SRC_QTUtil 
            #CPP_WEB_PLACEHOLDER
            )
endif()
if (IOS)
  add_definitions(-D_IOS)
  include_directories(.././External/IOS)
  set(PLATFORM_SRC_QTUtil 
            #CPP_IOS_PLACEHOLDER
            )
endif()
if (APPLE && NOT IOS)
  add_definitions(-D_MACOS)
  include_directories(.././External/MacOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_QTUtil 
            #CPP_MACOS_PLACEHOLDER
            )
endif()
if (ANDROID)
  add_definitions(-D_ANDROID)
  include_directories(.././External/Android)
  set(PLATFORM_SRC_QTUtil 
            #CPP_ANDROID_PLACEHOLDER
            )
endif()
if (UNIX AND NOT APPLE)
  add_definitions(-D_LINUX)
  include_directories(.././External/Linux)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_QTUtil 
            #CPP_LINUX_PLACEHOLDER
            )
endif()

foreach(REFL_FILE QTUtil ${GENERIC_REFL_QTUtil} ${PLATFORM_REFL_QTUtil})
  string(REPLACE ".refl.h" ".refl.meta.h" META_FILE ${REFIL_FILE})
  add_custom_command(OUTPUT ${META_FILE}
                     COMMAND StormRefl -- -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -x c++ -Wno-pragma-once-outside-header -I. -I../. -I.././External
                     MAIN_DEPENDENCY ${REFL_FILE}
                     IMPLICIT_DEPENDS CXX ${REFL_FILE})
endforeach()

add_library(QTUtil ${GENERIC_SRC_QTUtil} ${PLATFORM_SRC_QTUtil}
            QTUtil ${GENERIC_HEADER_QTUtil} ${PLATFORM_HEADER_QTUtil})