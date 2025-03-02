// this file is for organizing all the required library for the project
//
// created by Gabriel LU on Feb 28, 2025
//

#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <unordered_map>
#include <vector>
#include <algorithm>

#include <chrono>
#include <memory>
#include <thread>

#include <glad/glad.h>

#ifdef __APPLE__
#define GLFW_EXPOSE_NATIVE_COCOA
#endif

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb_image/stb_image.h>

// platform specific
#ifdef __APPLE__
#include <Cocoa/Cocoa.h>
#include <objc/message.h>
#include <objc/objc-runtime.h>
#endif

#define GAME_VERSION_MAJOR 0
#define GAME_VERSION_MINOR 1

extern std::fstream log_file;

void initGLFW();
void initGLAD();

void startLog();
void log(const std::string &message);
void endLog();

std::string getCurrentTime();

enum class BlockType : int
{
    GRASS = 0,
    DIRT,
    STONE,
    BEDROCK,
    WOOD,
    LEAF,
    SAND,
    WATER,
    LAVA,
    OBSIDIAN,
    BLOCK_COUNT
};

enum class BlockFace : int
{
    TOP = 0,
    BOTTOM,
    FRONT,
    BACK,
    LEFT,
    RIGHT,
    FACE_COUNT
};

enum class PlayerPrivileges : int
{
    ADMIN = 0,
    PLAYER,
    ADVENTURER,
    GUEST,
    SUPERUSER = 777
};
