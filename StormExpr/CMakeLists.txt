cmake_minimum_required(VERSION 3.1.0)

include_directories(. ../. .././External)
set(CMAKE_CXX_STANDARD 14)

set(GENERIC_SRC_StormExpr 
            ./StormExprLiteralBlockBuilder.cpp
            ./StormExprStatementBlock.cpp
            ./StormExprValueInitBlock.cpp
            ./StormExprValueBlockList.cpp
            ./StormExprValueBlock.cpp
            ./StormExprHash.cpp
            ./StormExprEval.cpp
            ./StormExprBinding.cpp
            ./StormExprOperator.cpp
            ./StormExprStack.cpp
            ./StormExprOps.cpp
            ./StormExprEvalBuilder.cpp
            ./StormExprValueInitBlockList.cpp
            ./StormExprValueProvider.cpp
            ./StormExprLiteralBlock.cpp
            ./StormExprStatementBlockElement.cpp
            ./StormExprValue.cpp
            ./StormExprDynamicBlock.cpp
            ./StormExprFunctionList.cpp
            #CPP_PLACEHOLDER
            )
set(GENERIC_HEADER_StormExpr 
            ./StormExprLiteralBlockBuilder.h
            ./StormExprFunctionReg.h
            ./StormExprEval.h
            ./StormExprStack.h
            ./StormExprValueInitBlockList.h
            ./StormExprStatementBlockElement.h
            ./StormExprValueBlock.h
            ./StormExprStatementBlock.h
            ./StormExprBinding.h
            ./StormExprLiteralBlock.h
            ./StormExprValueInitBlock.h
            ./StormExprOps.h
            ./StormExprValueBlockList.h
            ./StormExprFunctionList.h
            ./StormExprOperator.h
            ./StormExprEvalBuilder.h
            ./StormExprDynamicBlock.h
            ./StormExprValueProvider.h
            ./StormExprValue.h
            ./StormExprReflBlock.h
            ./StormExprHash.h
            #HEADER_PLACEHOLDER
            )
set(GENERIC_REFL_StormExpr 
            #REFL_PLACEHOLDER
            )

if (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(.././External/Windows)
  set(PLATFORM_SRC_StormExpr 
            )

set(PLATFORM_HEADER_StormExpr 
            )
endif()
if (WEB)
  add_definitions(-D_WEB)
  include_directories(.././External/Web)
  set(PLATFORM_SRC_StormExpr 
            )

set(PLATFORM_HEADER_StormExpr 
            )
endif()
if (IOS)
  add_definitions(-D_IOS)
  include_directories(.././External/IOS)
  set(PLATFORM_SRC_StormExpr 
            )

set(PLATFORM_HEADER_StormExpr 
            )
endif()
if (APPLE AND NOT IOS)
  add_definitions(-D_MACOS)
  include_directories(.././External/MacOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_StormExpr 
            )

set(PLATFORM_HEADER_StormExpr 
            )
endif()
if (ANDROID)
  add_definitions(-D_ANDROID)
  include_directories(.././External/Android)
  set(PLATFORM_SRC_StormExpr 
            )

set(PLATFORM_HEADER_StormExpr 
            )
endif()
if (UNIX AND NOT APPLE)
  add_definitions(-D_LINUX)
  include_directories(.././External/Linux)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_StormExpr 
            )

set(PLATFORM_HEADER_StormExpr 
            )
endif()

foreach(REFL_FILE ${GENERIC_REFL_StormExpr})
  string(REPLACE ".refl.h" ".refl.meta.h" META_FILE ${REFL_FILE})
  add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${META_FILE}
                     COMMAND stormrefl ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE} -- -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -x c++ -Wno-pragma-once-outside-header -I${CMAKE_CURRENT_SOURCE_DIR} -I${CMAKE_CURRENT_SOURCE_DIR}/../. -I${CMAKE_CURRENT_SOURCE_DIR}/.././External -I${CLANG_HEADER_PATH}
                     MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE}
                     IMPLICIT_DEPENDS CXX ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE})
endforeach()

add_library(StormExpr ${GENERIC_SRC_StormExpr} ${PLATFORM_SRC_StormExpr}
            ${GENERIC_HEADER_StormExpr} ${PLATFORM_HEADER_StormExpr})