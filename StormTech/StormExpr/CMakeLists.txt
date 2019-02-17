cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/External ${PROJECT_SOURCE_DIR}/StormTech ${PROJECT_SOURCE_DIR}/Tools ${PROJECT_SOURCE_DIR}/Shared ${PROJECT_SOURCE_DIR}/Project)
set(CMAKE_CXX_STANDARD 17)

set(GENERIC_SRC_StormExpr 
            StormExprLiteralBlockBuilder.cpp
            StormExprStatementBlock.cpp
            StormExprValueInitBlock.cpp
            StormExprValueBlockList.cpp
            StormExprValueBlock.cpp
            StormExprHash.cpp
            StormExprEval.cpp
            StormExprBinding.cpp
            StormExprOperator.cpp
            StormExprStack.cpp
            StormExprOps.cpp
            StormExprEvalBuilder.cpp
            StormExprValueInitBlockList.cpp
            StormExprValueProvider.cpp
            StormExprLiteralBlock.cpp
            StormExprStatementBlockElement.cpp
            StormExprValue.cpp
            StormExprDynamicBlock.cpp
            StormExprFunctionList.cpp
            )

set(GENERIC_HEADER_StormExpr 
            StormExprLiteralBlockBuilder.h
            StormExprFunctionReg.h
            StormExprEval.h
            StormExprStack.h
            StormExprValueInitBlockList.h
            StormExprStatementBlockElement.h
            StormExprValueBlock.h
            StormExprStatementBlock.h
            StormExprBinding.h
            StormExprLiteralBlock.h
            StormExprValueInitBlock.h
            StormExprOps.h
            StormExprValueBlockList.h
            StormExprFunctionList.h
            StormExprOperator.h
            StormExprEvalBuilder.h
            StormExprDynamicBlock.h
            StormExprValueProvider.h
            StormExprValue.h
            StormExprReflBlock.h
            StormExprHash.h
            )

add_library(StormExpr STATIC ${GENERIC_SRC_StormExpr} ${GENERIC_HEADER_StormExpr})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${GENERIC_SRC_StormExpr} ${GENERIC_HEADER_StormExpr})

