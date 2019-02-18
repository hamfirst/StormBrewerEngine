cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/External ${PROJECT_SOURCE_DIR}/StormTech ${PROJECT_SOURCE_DIR}/Tools ${PROJECT_SOURCE_DIR}/Shared ${PROJECT_SOURCE_DIR}/Project)
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
            )

add_library(StormExpr STATIC ${GENERIC_SRC_StormExpr} ${GENERIC_HEADER_StormExpr})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${GENERIC_SRC_StormExpr} ${GENERIC_HEADER_StormExpr})

