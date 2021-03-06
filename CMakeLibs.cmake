# GLFW3
include_directories(${CMAKE_SOURCE_DIR}/ext/glfw3/include)
link_libraries(${CMAKE_SOURCE_DIR}/ext/glfw3/lib-mingw/glfw3.dll)

# GLEW
include_directories(${CMAKE_SOURCE_DIR}/ext/glew/include)
#link_libraries(${CMAKE_SOURCE_DIR}/ext/glew/bin/Release/Win32/glew32.dll)
set(SOURCE_FILES ext/glew/src/glew.c ext/glew/src/glew.h)
add_definitions(-DGLEW_STATIC)

# OPENGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
link_libraries(${OPENGL_LIBRARIES})

# GLM
include_directories(${CMAKE_SOURCE_DIR}/ext/glm/include)

# FREETYPE
include_directories(${CMAKE_SOURCE_DIR}/ext/freetype/include)
#link_libraries(${CMAKE_SOURCE_DIR}/ext/freetype/bin/freetype6.dll)
link_libraries(${CMAKE_SOURCE_DIR}/ext/freetype/bin/freetype.lib)

set(SOURCE_FILES ${SOURCE_FILES}
        ext/SOIL/image_DXT.h
        ext/SOIL/image_DXT.c
        ext/SOIL/image_helper.h
        ext/SOIL/image_helper.c
        ext/SOIL/SOIL.h
        ext/SOIL/SOIL.c
        ext/SOIL/stb_image_aug.h
        ext/SOIL/stb_image_aug.c
        ext/SOIL/stbi_DDS_aug.h
        ext/SOIL/stbi_DDS_aug_c.h
        )