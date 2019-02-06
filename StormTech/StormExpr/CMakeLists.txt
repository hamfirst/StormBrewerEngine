cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/External ${PROJECT_SOURCE_DIR}/StormTech ${PROJECT_SOURCE_DIR}/Tools ${PROJECT_SOURCE_DIR}/Shared ${PROJECT_SOURCE_DIR}/Project)
set(CMAKE_CXX_STANDARD 17)

set(GENERIC_SRC_StormExpr 
            StormExprBinding.cpp
            StormExprDynamicBlock.cpp
            StormExprEval.cpp
            StormExprEvalBuilder.cpp
            StormExprFunctionList.cpp
            StormExprHash.cpp
            StormExprLiteralBlock.cpp
            StormExprLiteralBlockBuilder.cpp
            StormExprOperator.cpp
            StormExprOps.cpp
            StormExprStack.cpp
            StormExprStatementBlock.cpp
            StormExprStatementBlockElement.cpp
            StormExprValue.cpp
            StormExprValueBlock.cpp
            StormExprValueBlockList.cpp
            StormExprValueInitBlock.cpp
            StormExprValueInitBlockList.cpp
            StormExprValueProvider.cpp
            )

set(GENERIC_HEADER_StormExpr 
            StormExprBinding.h
            StormExprDynamicBlock.h
            StormExprEval.h
            StormExprEvalBuilder.h
            StormExprFunctionList.h
            StormExprFunctionReg.h
            StormExprHash.h
            StormExprLiteralBlock.h
            StormExprLiteralBlockBuilder.h
            StormExprOperator.h
            StormExprOps.h
            StormExprReflBlock.h
            StormExprStack.h
            StormExprStatementBlock.h
            StormExprStatementBlockElement.h
            StormExprValue.h
            StormExprValueBlock.h
            StormExprValueBlockList.h
            StormExprValueInitBlock.h
            StormExprValueInitBlockList.h
            StormExprValueProvider.h
            )

add_library(StormExpr STATIC ${GENERIC_SRC_StormExpr} ${GENERIC_HEADER_StormExpr})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${GENERIC_SRC_StormExpr} ${GENERIC_HEADER_StormExpr})

