// main file for glfw and glad initialization
//
// created by Gabriel LU on Feb 28, 2025
//

#include "include.h"
#include "window.h"
#include "game.h"

#define GAME_VERSION_MAJOR 0
#define GAME_VERSION_MINOR 1

int main(int argc, char *argv[])
{
    // call endLog() after the destructors are called
    atexit(endLog());
    startLog();
    
    // initialization
    initGLFW();

    // window creation
    std::unique_ptr<Window> window =
        std::make_unique<Window>("Game - " + std::to_string(GAME_VERSION_MAJOR) + "." + std::to_string(GAME_VERSION_MINOR), 0, 0, false, true);
    initGLAD();
    
    game(window);

    return 0;
}
