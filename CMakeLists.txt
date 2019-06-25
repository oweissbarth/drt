cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(drt)

set(OpenGL_GL_PREFERENCE GLVND)

include_directories(extern/include/)


list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules")

find_package(glm REQUIRED)

find_package(openshading )

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
        gltf.h
        gltf.cpp
        BVH.cpp
        BVH.h
        BVHNode.cpp
        BVHNode.h
        MeshBVH.h
        MeshBVH.cpp
        MeshBVHNode.h
        MeshBVHNode.cpp
        SceneBVH.h
        SceneBVH.cpp
        SceneBVHNode.cpp
        SceneBVHNode.h
        AABB.h
        AABB.cpp
        utils.h
        Intersection.h
        Intersection.cpp
	Material.cpp
	Material.h
	Mesh.cpp
	Mesh.h
        )

add_subdirectory(preview)

add_executable(drt ${SOURCE_FILES})

target_link_libraries(drt ${GLM_LIBRARIES} ${OPENIMAGEIO_LIBRARIES} preview)
set_property(TARGET drt PROPERTY CXX_STANDARD 11)
