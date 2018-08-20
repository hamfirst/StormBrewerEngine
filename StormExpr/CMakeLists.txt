cmake_minimum_required(VERSION 3.0)

include_directories(. ../. .././External)
set(CMAKE_CXX_STANDARD 14)

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
            #CPP_PLACEHOLDER
            )
set(GENERIC_HEADER_StormExpr 
            ./StormExprBinding.h
            ./StormExprDynamicBlock.h
            ./StormExprEval.h
            ./StormExprEvalBuilder.h
            ./StormExprFunctionList.h
            ./StormExprFunctionReg.h
            ./StormExprHash.h
            ./StormExprLiteralBlock.h
            ./StormExprLiteralBlockBuilder.h
            ./StormExprOperator.h
            ./StormExprOps.h
            ./StormExprReflBlock.h
            ./StormExprStack.h
            ./StormExprStatementBlock.h
            ./StormExprStatementBlockElement.h
            ./StormExprValue.h
            ./StormExprValueBlock.h
            ./StormExprValueBlockList.h
            ./StormExprValueInitBlock.h
            ./StormExprValueInitBlockList.h
            ./StormExprValueProvider.h
            #HEADER_PLACEHOLDER
            )
set(GENERIC_REFL_StormExpr 
            #REFL_PLACEHOLDER
            )

if (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(.././External/Windows)
  set(PLATFORM_SRC_StormExpr 
            #CPP_WINDOWS_PLACEHOLDER
            )
endif()
if (WEB)
  add_definitions(-D_WEB)
  include_directories(.././External/Web)
  set(PLATFORM_SRC_StormExpr 
            #CPP_WEB_PLACEHOLDER
            )
endif()
if (IOS)
  add_definitions(-D_IOS)
  include_directories(.././External/IOS)
  set(PLATFORM_SRC_StormExpr 
            #CPP_IOS_PLACEHOLDER
            )
endif()
if (APPLE && NOT IOS)
  add_definitions(-D_MACOS)
  include_directories(.././External/MacOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_StormExpr 
            #CPP_MACOS_PLACEHOLDER
            )
endif()
if (ANDROID)
  add_definitions(-D_ANDROID)
  include_directories(.././External/Android)
  set(PLATFORM_SRC_StormExpr 
            #CPP_ANDROID_PLACEHOLDER
            )
endif()
if (UNIX AND NOT APPLE)
  add_definitions(-D_LINUX)
  include_directories(.././External/Linux)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_StormExpr 
            #CPP_LINUX_PLACEHOLDER
            )
endif()

foreach(REFL_FILE StormExpr ${GENERIC_REFL_StormExpr} ${PLATFORM_REFL_StormExpr})
  string(REPLACE ".refl.h" ".refl.meta.h" META_FILE ${REFIL_FILE})
  add_custom_command(OUTPUT ${META_FILE}
                     COMMAND StormRefl -- -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -x c++ -Wno-pragma-once-outside-header -I. -I../. -I.././External
                     MAIN_DEPENDENCY ${REFL_FILE}
                     IMPLICIT_DEPENDS CXX ${REFL_FILE})
endforeach()

add_library(StormExpr ${GENERIC_SRC_StormExpr} ${PLATFORM_SRC_StormExpr}
            StormExpr ${GENERIC_HEADER_StormExpr} ${PLATFORM_HEADER_StormExpr})