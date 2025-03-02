cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Game)

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
find_package(OpenGL REQUIRED)

include_directories(include)

if (WIN32)
    # Windows VS2022 configuration
    set(GLFW_INCLUDE_DIR "E:/library/glfw-3.4.bin.WIN64/include")
    set(GLFW_LIBRARY_DIR "E:/library/glfw-3.4.bin.WIN64/lib-vc2022")
    
    # full path to the GLFW library
    set(GLFW_LIBRARY "${GLFW_LIBRARY_DIR}/glfw3.lib")
    
    # verify the library exists
    if(NOT EXISTS ${GLFW_LIBRARY})
        message(FATAL_ERROR "GLFW library not found at: ${GLFW_LIBRARY}")
    endif()
    
    include_directories(${GLFW_INCLUDE_DIR})
    
    # link with the full path to the library
    target_link_libraries(Game PRIVATE ${GLFW_LIBRARY})
endif()

if (APPLE)
    find_package(GLFW3 3.3 REQUIRED)

    # clang-tidy for macOS
    set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*,-clang-analyzer-alpha.*,-llvm-*")

    # link Cocoa library on macOS to ensure GLFW fullscreen support
    find_library(COCOA_LIBRARY Cocoa)
    if (NOT COCOA_LIBRARY)
        message(FATAL_ERROR "Cocoa library not found")
    endif()

    target_link_libraries(Game PRIVATE ${COCOA_LIBRARY} glfw)
endif()

target_link_libraries(Game PRIVATE OpenGL::GL glad)

# make shader files visible in Xcode and VS2022
set(SHADER_FILES
    shaders/shader.vert
    shaders/shader.frag
)
source_group("Shaders" FILES ${SHADER_FILES})
add_custom_target(Shaders SOURCES ${SHADER_FILES})