cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/.. ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/External)
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

add_library(StormExpr STATIC ${GENERIC_SRC_StormExpr} ${PLATFORM_SRC_StormExpr}
            ${GENERIC_HEADER_StormExpr} ${PLATFORM_HEADER_StormExpr})
