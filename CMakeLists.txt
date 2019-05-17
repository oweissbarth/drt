cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(drt)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules")

find_package(glm REQUIRED)

find_package(OpenImageIO REQUIRED)
include_directories(${OPENIMAGEIO_INCLUDE_DIRS})
link_directories(${OPENIMAGEIO_LIBRARIES})

set(SOURCE_FILES
        main.cpp
        Object.cpp
        Object.h
        Scene.cpp
        Scene.h
        Renderer.cpp
        Renderer.h
        Camera.h
        Camera.cpp
        Ray.h
        Image.h
        Image.cpp
        )


add_executable(drt ${SOURCE_FILES})
 
target_link_libraries(drt glm ${OPENIMAGEIO_LIBRARIES})
set_property(TARGET drt PROPERTY CXX_STANDARD 11)
