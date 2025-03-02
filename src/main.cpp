// main file for glfw and glad initialization
//
// created by Gabriel LU on Feb 28, 2025
//

#include "include.h"
#include "window.h"
#include "game.h"

int main(int argc, char *argv[])
{
    startLog();
    
    // initialization
    initGLFW();

    // window creation
    std::unique_ptr<Window> window =
        std::make_unique<Window>("Game - " + std::to_string(GAME_VERSION_MAJOR) + "." + std::to_string(GAME_VERSION_MINOR), 0, 0, false, true);
    initGLAD();
    
    game(window);

    endLog();
    return 0;
}
