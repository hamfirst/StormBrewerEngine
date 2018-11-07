cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/External)
set(CMAKE_CXX_STANDARD 17)

set(GENERIC_SRC_UnitTests 
            UnitTests.cpp
            TestComponent/TestComponent.refl.reg.cpp
            TestComponent/TestComponent.refl.cpp
            #CPP_PLACEHOLDER
            )

set(GENERIC_HEADER_UnitTests 
            TestTypes.refl.h
            TestTypes.refl.meta.h
            targetver.h
            stdafx.h
            TestComponent/TestComponent.refl.meta.h
            TestComponent/TestComponent.refl.h
            #HEADER_PLACEHOLDER
            )

set(GENERIC_REFL_UnitTests 
            TestTypes.refl.h
            TestComponent/TestComponent.refl.h
            #REFL_PLACEHOLDER
            )


foreach(REFL_FILE ${GENERIC_REFL_UnitTests})
  string(REPLACE ".refl.h" ".refl.meta.h" META_FILE ${REFL_FILE})
  add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${META_FILE}
                     COMMAND stormrefl ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE} -- -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -std=c++17 -x c++ -Wno-pragma-once-outside-header -I${CMAKE_CURRENT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR}/External -I${CLANG_HEADER_PATH} -D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
                     MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE}
                     IMPLICIT_DEPENDS CXX ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE})
endforeach()

add_library(UnitTests STATIC ${GENERIC_SRC_UnitTests} ${GENERIC_HEADER_UnitTests})

