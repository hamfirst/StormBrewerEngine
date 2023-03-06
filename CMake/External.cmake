
add_subdirectory("${PROJECT_SOURCE_DIR}/External/glm")
add_subdirectory("${PROJECT_SOURCE_DIR}/External/binpack")
add_subdirectory("${PROJECT_SOURCE_DIR}/External/lua")

set_target_properties(glm PROPERTIES FOLDER External)
set_target_properties(binpack PROPERTIES FOLDER External)
set_target_properties(lua PROPERTIES FOLDER External)

if(BUILD_CLIENT OR BUILD_TOOLS)
    add_subdirectory("${PROJECT_SOURCE_DIR}/External/gl3w")
    add_subdirectory("${PROJECT_SOURCE_DIR}/External/ogg")
    add_subdirectory("${PROJECT_SOURCE_DIR}/External/lodepng")
    add_subdirectory("${PROJECT_SOURCE_DIR}/External/vorbis")
    add_subdirectory("${PROJECT_SOURCE_DIR}/External/resample")

    set_target_properties(gl3w PROPERTIES FOLDER External)
    set_target_properties(ogg PROPERTIES FOLDER External)
    set_target_properties(vorbis PROPERTIES FOLDER External)
    set_target_properties(resample PROPERTIES FOLDER External)
    set_target_properties(lodepng PROPERTIES FOLDER External)

    add_subdirectory("${PROJECT_SOURCE_DIR}/External/yajl")
    add_subdirectory("${PROJECT_SOURCE_DIR}/External/libbson")
    add_subdirectory("${PROJECT_SOURCE_DIR}/External/mongoc")

    set_target_properties(yajl PROPERTIES FOLDER External)
    set_target_properties(libbson PROPERTIES FOLDER External)
    set_target_properties(mongoc PROPERTIES FOLDER External)
endif()

if(NOT WEB)
    add_subdirectory("${PROJECT_SOURCE_DIR}/External/enet")
    add_subdirectory("${PROJECT_SOURCE_DIR}/External/usrsctplib")
    add_subdirectory("${PROJECT_SOURCE_DIR}/External/mbedtls")
    add_subdirectory("${PROJECT_SOURCE_DIR}/External/asio")

    set_target_properties(ENet PROPERTIES FOLDER External)
    set_target_properties(usrsctp PROPERTIES FOLDER External)
    set_target_properties(usrsctp-static PROPERTIES FOLDER External)
    set_target_properties(mbedtls PROPERTIES FOLDER External)
    set_target_properties(asio PROPERTIES FOLDER External)
endif()

if(BUILD_TOOLS)
    add_subdirectory("${PROJECT_SOURCE_DIR}/External/libgit2")

    set_target_properties(git2 PROPERTIES FOLDER External)
    set_target_properties(git2internal PROPERTIES FOLDER External)
    set_target_properties(libgit2_clar PROPERTIES FOLDER External)
endif()


if(BUILD_CLIENT OR BUILD_TOOLS)
    if (MSVC)
        add_subdirectory("${PROJECT_SOURCE_DIR}/External/Windows/SDL_build")
        add_subdirectory("${PROJECT_SOURCE_DIR}/External/Windows/freetype2")

        set_target_properties(SDL2main PROPERTIES FOLDER External)
        set_target_properties(SDL2-static PROPERTIES FOLDER External)
        set_target_properties(freetype PROPERTIES FOLDER External)
    endif()

    if(ANDROID)
        add_subdirectory("${PROJECT_SOURCE_DIR}/External/Android/SDL_build")
        add_subdirectory("${PROJECT_SOURCE_DIR}/External/Android/freetype2")

        set_target_properties(SDL2main PROPERTIES FOLDER External)
        set_target_properties(SDL2-static PROPERTIES FOLDER External)
        set_target_properties(freetype PROPERTIES FOLDER External)
    endif()

    if(IOS)
        add_subdirectory("${PROJECT_SOURCE_DIR}/External/IOS/SDL_build")
        add_subdirectory("${PROJECT_SOURCE_DIR}/External/IOS/freetype2")

        set_target_properties(SDL2main PROPERTIES FOLDER External)
        set_target_properties(SDL2-static PROPERTIES FOLDER External)
        set_target_properties(freetype PROPERTIES FOLDER External)
    endif()

    if(UNIX AND NOT APPLE)
        add_subdirectory("${PROJECT_SOURCE_DIR}/External/Linux/SDL_build")

        set_target_properties(SDL2main PROPERTIES FOLDER External)
        set_target_properties(SDL2-static PROPERTIES FOLDER External)
    endif()
endif()

if(WEB)
    add_subdirectory("${PROJECT_SOURCE_DIR}/External/Web/freetype2")
endif()

if(MSVC)
    set_target_properties(zlib PROPERTIES FOLDER External)
    set_target_properties(regex PROPERTIES FOLDER External)
    set_target_properties(http-parser PROPERTIES FOLDER External)
endif()

