cmake_minimum_required(VERSION 2.6)

project(ogg)
add_library(ogg STATIC bitwise.c framing.c)
