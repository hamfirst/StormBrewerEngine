cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/External)
set(CMAKE_CXX_STANDARD 17)

set(GENERIC_SRC_StormExpr 
            StormExprEval.cpp
            StormExprValueInitBlockList.cpp
            StormExprBinding.cpp
            StormExprHash.cpp
            StormExprEvalBuilder.cpp
            StormExprOps.cpp
            StormExprStatementBlockElement.cpp
            StormExprLiteralBlockBuilder.cpp
            StormExprValueBlock.cpp
            StormExprFunctionList.cpp
            StormExprDynamicBlock.cpp
            StormExprValueProvider.cpp
            StormExprStatementBlock.cpp
            StormExprOperator.cpp
            StormExprValueInitBlock.cpp
            StormExprValue.cpp
            StormExprValueBlockList.cpp
            StormExprLiteralBlock.cpp
            StormExprStack.cpp
            #CPP_PLACEHOLDER
            )
set(GENERIC_HEADER_StormExpr 
            StormExprEvalBuilder.h
            StormExprFunctionList.h
            StormExprValueBlock.h
            StormExprValueBlockList.h
            StormExprValueProvider.h
            StormExprLiteralBlockBuilder.h
            StormExprValueInitBlock.h
            StormExprEval.h
            StormExprDynamicBlock.h
            StormExprLiteralBlock.h
            StormExprStack.h
            StormExprStatementBlock.h
            StormExprFunctionReg.h
            StormExprOperator.h
            StormExprValue.h
            StormExprHash.h
            StormExprValueInitBlockList.h
            StormExprReflBlock.h
            StormExprOps.h
            StormExprStatementBlockElement.h
            StormExprBinding.h
            #HEADER_PLACEHOLDER
            )
set(GENERIC_REFL_StormExpr 
            #REFL_PLACEHOLDER
            )

if (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(${PROJECT_SOURCE_DIR}/External/Windows)
  set(PLATFORM_SRC_StormExpr 
            )

set(PLATFORM_HEADER_StormExpr 
            )
endif()
if (WEB)
  add_definitions(-D_WEB)
  include_directories(${PROJECT_SOURCE_DIR}/External/Web)
  set(PLATFORM_SRC_StormExpr 
            )

set(PLATFORM_HEADER_StormExpr 
            )
endif()
if (IOS)
  add_definitions(-D_IOS)
  include_directories(${PROJECT_SOURCE_DIR}/External/IOS)
  set(PLATFORM_SRC_StormExpr 
            )

set(PLATFORM_HEADER_StormExpr 
            )
endif()
if (APPLE AND NOT IOS)
  add_definitions(-D_MACOS)
  include_directories(${PROJECT_SOURCE_DIR}/External/MacOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_StormExpr 
            )

set(PLATFORM_HEADER_StormExpr 
            )
endif()
if (ANDROID)
  add_definitions(-D_ANDROID)
  include_directories(${PROJECT_SOURCE_DIR}/External/Android)
  set(PLATFORM_SRC_StormExpr 
            )

set(PLATFORM_HEADER_StormExpr 
            )
endif()
if (UNIX AND NOT APPLE)
  add_definitions(-D_LINUX)
  include_directories(${PROJECT_SOURCE_DIR}/External/Linux)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_StormExpr 
            )

set(PLATFORM_HEADER_StormExpr 
            )
endif()

foreach(REFL_FILE ${GENERIC_REFL_StormExpr})
  string(REPLACE ".refl.h" ".refl.meta.h" META_FILE ${REFL_FILE})
  add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${META_FILE}
                     COMMAND stormrefl ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE} -- -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -std=c++17 -x c++ -Wno-pragma-once-outside-header -I${CMAKE_CURRENT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR}/External -I${CLANG_HEADER_PATH}
                     MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE}
                     IMPLICIT_DEPENDS CXX ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE})
endforeach()

add_library(StormExpr ${GENERIC_SRC_StormExpr} ${PLATFORM_SRC_StormExpr}
            ${GENERIC_HEADER_StormExpr} ${PLATFORM_HEADER_StormExpr})