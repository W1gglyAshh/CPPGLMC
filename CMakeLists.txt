cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (WIN32)
    set(CMAKE_PREFIX_PATH "E:/library/glfw-3.4.WIN64/" ${CMAKE_PREFIX_PATH}
endif()

project(Game)

find_package(OpenGL REQUIRED)
find_package(GLFW3 3.3 REQUIRED)
find_package(glm REQUIRED)

add_executable(Game 
    src/main.cpp
    src/stb_image.cpp
    src/include.cpp
    src/include.h
    src/game.cpp
    src/game.h
    src/shader.cpp
    src/shader.h
    src/world.cpp
    src/world.h
    src/block.cpp
    src/block.h
    src/camera.cpp
    src/camera.h
    src/window.cpp
    src/window.h
)

add_library(glad STATIC src/glad.c)

include_directories(include)
target_link_libraries(Game PRIVATE OpenGL::GL glm::glm glfw glad)

if (APPLE)
    # clang-tidy for macOS
    set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*,-clang-analyzer-alpha.*,-llvm-*")

    # link Cocoa library on macOS to ensure GLFW fullscreen support
    find_library(COCOA_LIBRARY Cocoa)
    if (NOT COCOA_LIBRARY)
        message(FATAL_ERROR "Cocoa library not found")
    endif()
    target_link_libraries(Game PRIVATE ${COCOA_LIBRARY})
endif()

# make shader files visible in Xcode and VS2022
set(SHADER_FILES
    shaders/shader.vert
    shaders/shader.frag
)
source_group("Shaders" FILES ${SHADER_FILES})
add_custom_target(Shaders SOURCES ${SHADER_FILES})
