// header file for the window class - window management
//
// created by Gabriel LU on Mar 1, 2025
//

#pragma once

#include "include.h"

class Window
{
  private:
    GLFWwindow *window;
    std::string title;
    int width, height;

    bool is_resizable;
    bool is_fullscreen;

  public:
    Window(std::string title_in, int width_in, int height_in, bool resizable = false, bool fullscreen = false);
    ~Window();

    void setTitle(std::string title_in);
    void setSize(int width_in, int height_in);
    void setResizable(bool resizable_in);
    void setFullscreen(bool fullscreen_in);

    GLFWwindow *getWindow() const { return window; }
    std::string getTitle() const { return title; }
    glm::ivec2 getSize() const { return glm::ivec2(width, height); }

    void updateViewport();
    static void frameRateLimiter(double target_fps);
};
