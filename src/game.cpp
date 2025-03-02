// this file is for game related function implementation
//
// created by Gabriel LU on Mar 2, 2025
//

#include "game.h"

void game(std::unique_ptr<Window> &window)
{
    while (!glfwWindowShouldClose(window->getWindow()))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 0.1f, 0.1f, 1.0f);
        
        glfwSwapBuffers(window->getWindow());
        glfwPollEvents();
    }
}
