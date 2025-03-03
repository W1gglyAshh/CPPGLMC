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
    src/player.cpp
    src/player.h
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
    target_link_libraries(Game PRIVATE ${GLFW_LIBRARY})
endif()

if (APPLE)
    # set path to local GLFW library
    set(GLFW_LIBRARY "${CMAKE_SOURCE_DIR}/libs/libglfw.3.dylib")
    
    # link required libraries
    find_library(COCOA_LIBRARY Cocoa REQUIRED)
    target_link_libraries(Game PRIVATE ${COCOA_LIBRARY} ${GLFW_LIBRARY})
endif()

target_link_libraries(Game PRIVATE OpenGL::GL glad)

# make shader files visible in Xcode and VS2022
set(SHADER_FILES
    shaders/shader.vert
    shaders/shader.frag
)
source_group("Shaders" FILES ${SHADER_FILES})
add_custom_target(Shaders SOURCES ${SHADER_FILES})

