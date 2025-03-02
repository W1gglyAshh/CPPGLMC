// this file is for implementing the functions declared in include.h to avoid apple clang duplicate symbol error
//
// created by Gabriel LU on Mar 1, 2025
//

#include "include.h"

std::fstream log_file;

void initGLFW()
{
    log("Initializing GLFW...");
    if (!glfwInit())
    {
        log("Failed to initialize GLFW!");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    log("GLFW initialized successfully!");
}

void initGLAD()
{
    log("Initializing GLAD...");
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        log("Failed to initialize GLAD!");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    log("GLAD initialized successfully!");
    log("OpenGL Version: " + std::string(reinterpret_cast<const char *>(glGetString(GL_VERSION))));
}

void log(const std::string &message)
{
    log_file << "Game [" << getCurrentTime() << "]: " << message << std::endl;
    std::cout << "Game [" << getCurrentTime() << "]: " << message << std::endl;
}

void startLog()
{
    log_file.open("game_log.txt", std::ios::out | std::ios::app);
    log_file << std::endl;
    log("Program [Game] Started.");
    log("Game Version: " + std::to_string(GAME_VERSION_MAJOR) + "." + std::to_string(GAME_VERSION_MINOR));
}

void endLog()
{
    log("Program [Game] Ended.");
    log_file.close();
}

std::string getCurrentTime()
{
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S"); // format: YYYY-MM-DD HH:MM:SS
    
    return ss.str();
}
