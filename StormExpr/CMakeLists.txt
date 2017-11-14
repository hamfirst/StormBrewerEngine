cmake_minimum_required(VERSION 3.0)

include_directories(. ../. .././External)
set(CMAKE_CXX_STANDARD 14)

if (WEB)
  add_definitions(-D_WEB)
  include_directories(.././External/Web)
  set(PLATFORM_SRC_StormExpr 
            )
elseif (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(.././External/Windows)
  set(PLATFORM_SRC_StormExpr 
            )
elseif (IOS)
  add_definitions(-D_IOS)
  include_directories(.././External/IOS)
  set(PLATFORM_SRC_StormExpr 
            )
elseif (APPLE)
  add_definitions(-D_MACOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_StormExpr 
            )
elseif (ANDROID)
  add_definitions(-D_ANDROID)
  include_directories(.././External/Android)
  set(PLATFORM_SRC_StormExpr 
            )
elseif (UNIX)
  add_definitions(-D_LINUX)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_StormExpr 
            )
endif()

set(GENERIC_SRC_StormExpr 
            ./StormExprBinding.cpp
            ./StormExprDynamicBlock.cpp
            ./StormExprEval.cpp
            ./StormExprEvalBuilder.cpp
            ./StormExprFunctionList.cpp
            ./StormExprHash.cpp
            ./StormExprLiteralBlock.cpp
            ./StormExprLiteralBlockBuilder.cpp
            ./StormExprOperator.cpp
            ./StormExprOps.cpp
            ./StormExprStack.cpp
            ./StormExprStatementBlock.cpp
            ./StormExprStatementBlockElement.cpp
            ./StormExprValue.cpp
            ./StormExprValueBlock.cpp
            ./StormExprValueBlockList.cpp
            ./StormExprValueInitBlock.cpp
            ./StormExprValueInitBlockList.cpp
            ./StormExprValueProvider.cpp
            )
add_library(StormExpr ${GENERIC_SRC_StormExpr} ${PLATFORM_SRC_StormExpr} )