// Window class implementation
//
// created by Gabriel LU on Mar 1, 2025
//

#include "window.h"

Window::Window(std::string title_in, int width_in, int height_in, bool resizable, bool fullscreen)
    : title(std::move(title_in)), width(width_in), height(height_in), is_resizable(resizable), is_fullscreen(fullscreen)
{
    log("Window info: " + title + " (" + std::to_string(width) + "x" + std::to_string(height) + ")");
    log("Creating window...");

    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    if (!mode)
    {
        log("Failed to get video mode! Defaulting to 640x480 windowed mode.");
        window = glfwCreateWindow(640, 480, title.c_str(), nullptr, nullptr);
    }

    if (!fullscreen)
    {
        log("Fullscreen mode is not enabled.");
        if (width <= 0 || height <= 0)
        {
            log("Given window size is invalid. Defaulting to native display size and keep the "
                "aspect ratio of 16:9.");

            // keep the aspect ratio of 16:9
            width = mode->width;
            height = width * 9 / 16;
        }

        log("Window size: " + std::to_string(width) + "x" + std::to_string(height));
        window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    }
    else
    {
        log("Fullscreen mode is enabled.");
#ifdef __APPLE__
        // Cocoa API fullscreen (Apple native fullscreen)
        log("GLFW does not natively support fullscreen mode on macOS. Using Cocoa API...");
        window = glfwCreateWindow(mode->width, mode->height, title.c_str(), nullptr, nullptr);

        if (window)
        {
            id ns_window = glfwGetCocoaWindow(window);
            if (ns_window)
            {
                SEL collection_behavior_sel = sel_getUid("setCollectionBehavior:");
                void (*set_collection_behavior)(id, SEL, NSUInteger) = (void (*)(id, SEL, NSUInteger))objc_msgSend;

                // NSWindowCollectionBehaviorFullScreenPrimary
                set_collection_behavior(ns_window, collection_behavior_sel, 1 << 7);

                // toggle fullscreen
                SEL toggle_fullscreen_sel = sel_getUid("toggleFullScreen:");
                void (*toggle_fullscreen)(id, SEL, id) = (void (*)(id, SEL, id))objc_msgSend;
                toggle_fullscreen(ns_window, toggle_fullscreen_sel, nil);
            }
            else
            {
                log("Failed to get Cocoa window!");
                glfwDestroyWindow(window);
                glfwTerminate();
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            log("Failed to create window for fullscreen!");
            glfwTerminate();
            exit(EXIT_FAILURE);
        }
#else
        // GLFW native borderless fullscreen
        window = glfwCreateWindow(mode->width, mode->height, title.c_str(), glfwGetPrimaryMonitor(), nullptr);
#endif
    }

    if (!window)
    {
        log("Failed to create window!");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwSetWindowAttrib(window, GLFW_RESIZABLE, is_resizable ? GLFW_TRUE : GLFW_FALSE);
    glfwMakeContextCurrent(window);

    log("Window created successfully!");
}

Window::~Window()
{
    std::cout << "Destroying window..." << std::endl;
    glfwDestroyWindow(window);
    std::cout << "Window destroyed successfully!" << std::endl;
}

void Window::setTitle(std::string title_in)
{
    log("Setting window title to: " + title_in);
    title = std::move(title_in);
    glfwSetWindowTitle(window, title.c_str());
    log("Window title set successfully!");
}

void Window::setSize(int width_in, int height_in)
{
    if (width_in <= 0 || height_in <= 0)
    {
        std::cerr << "Invalid window size: " << width_in << "x" << height_in << std::endl;
        return;
    }
    width = width_in;
    height = height_in;
    log("Setting window size to: " + std::to_string(width) + "x" + std::to_string(height));
    glfwSetWindowSize(window, width, height);
}

void Window::setResizable(bool resizable_in)
{
    log("Setting window resizable to: " + std::to_string(resizable_in));
    is_resizable = resizable_in;
    glfwSetWindowAttrib(window, GLFW_RESIZABLE, is_resizable ? GLFW_TRUE : GLFW_FALSE);
}

void Window::setFullscreen(bool fullscreen_in)
{
    log("Setting window fullscreen to: " + std::to_string(fullscreen_in));
    is_fullscreen = fullscreen_in;

#ifdef __APPLE__
    log("GLFW does not natively support fullscreen mode on macOS. Using Cocoa API...");

    id ns_window = glfwGetCocoaWindow(window);
    if (ns_window)
    {
        SEL is_fullscreen_sel = sel_getUid("isFullScreen");
        BOOL current_fullscreen = ((BOOL(*)(id, SEL))objc_msgSend)(ns_window, is_fullscreen_sel);

        if (current_fullscreen)
        {
            SEL toggle_fullscreen_sel = sel_getUid("toggleFullScreen:");
            void (*toggle_fullscreen)(id, SEL, id) = (void (*)(id, SEL, id))objc_msgSend;
            toggle_fullscreen(ns_window, toggle_fullscreen_sel, nil);
        }
    }
    else
    {
        log("Failed to get Cocoa window!");
    }
#else
    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    if (mode)
    {
        if (is_fullscreen)
        {
            glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, mode->refreshRate);
        }
        else
        {
            glfwSetWindowMonitor(window, nullptr, 0, 0, width, height, 0);
        }
    }
#endif
    log("Window fullscreen toggled successfully!");
}

void Window::updateViewport()
{
    int current_width, current_height;
    glfwGetFramebufferSize(window, &current_width, &current_height);

    width = current_width;
    height = current_height;
    glViewport(0, 0, width, height);
}

void Window::frameRateLimiter(double target_fps)
{
    static auto last_time = std::chrono::high_resolution_clock::now();
    double target_frame_time = 1.0 / target_fps;

    auto current_time = std::chrono::high_resolution_clock::now();
    double elapsed_time = std::chrono::duration<double>(current_time - last_time).count();

    if (elapsed_time < target_frame_time)
    {
        std::this_thread::sleep_for(std::chrono::duration<double>(target_frame_time - elapsed_time));
    }

    last_time = std::chrono::high_resolution_clock::now();
}
