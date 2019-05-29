cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(drt)

include_directories(extern/include/)




find_package(glm REQUIRED)



find_package(glfw3 3.3 REQUIRED)

find_package(OpenGL REQUIRED)



set(SOURCE_FILES
        Preview.cpp
        Preview.h
        PreviewSolid.cpp
        PreviewSolid.h
        PreviewLines.cpp
        PreviewLines.h
        PreviewObject.cpp
        PreviewObject.h
        )


add_library(preview ${SOURCE_FILES})

add_library(glad ../extern/src/glad.c)
target_include_directories(glad PUBLIC extern/include)

target_include_directories(preview PUBLIC ${OPENGL_INCLUDE_DIR})
target_link_libraries(preview ${GLM_LIBRARIES} ${OPENIMAGEIO_LIBRARIES} glfw ${OPENGL_gl_LIBRARY}  glad dl)

