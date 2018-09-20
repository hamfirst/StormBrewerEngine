cmake_minimum_required(VERSION 3.1.0)

include_directories(. ../../. ../.././External/libgit2/include)
set(CMAKE_CXX_STANDARD 17)

add_library(TemplateLib STATIC TemplateLib.cpp TemplateLib.h)

