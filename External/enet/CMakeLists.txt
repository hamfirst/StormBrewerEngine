cmake_minimum_required(VERSION 3.5)

add_definitions(-D_LINUX)

set(CMAKE_CXX_STANDARD 14)

add_library(ENet STATIC
            callbacks.c
            compress.c
            host.c
            list.c
            packet.c
            peer.c
            protocol.c
            unix.c)
            