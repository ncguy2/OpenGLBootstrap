cmake_minimum_required(VERSION 3.7)
project(OpenGLBootstrap)

# Versioning
set(MAJOR 1)
set(MINOR 0)
set(BUILD 1)
set(INCLUDE_UI TRUE)

set(BUILD_FILE ${CMAKE_SOURCE_DIR}/version.build)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

# Read build version
file(STRINGS "${BUILD_FILE}" BUILD)

add_definitions(-DMAJOR_VERSION=${MAJOR})
add_definitions(-DMINOR_VERSION=${MINOR})
add_definitions(-DBUILD_VERSION=${BUILD})

set(SOURCE_FILES)

include(./CMakeLibs.cmake)

set(UI_FILES include/ui/Actor.h include/ui/Group.h include/ui/components/Button.h include/ui/Stage.h src/ui/Stage.cpp src/ui/Actor.cpp src/ui/Group.cpp src/ui/components/Button.cpp)


set(SOURCE_FILES ${SOURCE_FILES} src/library.cpp include/library.h include/gl/OpenGLBootstrap.h src/gl/OpenGLBootstrap.cpp include/texture/TextureAtlas.h include/glyph/GlyphRenderer.h src/glyph/GlyphRenderer.cpp include/gl/Shader.h src/gl/Shader.cpp include/gl/ResourceManager.h include/gl/Texture.h src/gl/Texture.cpp src/gl/ResourceManager.cpp include/util/lodepng.h src/util/lodepng.cpp src/texture/TextureAtlas.cpp include/util/StringUtils.h src/util/StringUtils.cpp)

if(${INCLUDE_UI})
    set(SOURCE_FILES ${SOURCE_FILES} ${UI_FILES})
endif()

add_library(OpenGLBootstrap SHARED ${SOURCE_FILES})

file(WRITE "${BUILD_FILE}" "${BUILD}")

set(INC_SCRIPT "${CMAKE_SOURCE_DIR}/incrementBuild.bat")

add_custom_command(TARGET OpenGLBootstrap
        POST_BUILD
        COMMAND ${INC_SCRIPT} ${BUILD} > "${BUILD_FILE}"
        VERBATIM)