// this file is for game related function implementation
//
// created by Gabriel LU on Mar 2, 2025
//

#include "game.h"
#include "block.h"
#include "camera.h"
#include "shader.h"

void game(std::unique_ptr<Window> &window)
{
    Shader shader("../../shaders/shader.frag", "../../shaders/shader.vert");
    shader.compile();

    Block block(BlockType::GRASS, "../../res/atlas.png");

    std::vector<glm::vec3> positions;
    for (int x = 0; x < 10; x++)
    {
        for (int z = 0; z < 10; z++)
        {
            positions.push_back(glm::vec3(x, 0, z));
        }
    }

    block.setPositions(positions);
    block.init();

    Camera camera(glm::vec3(5.0f, 8.0f, 15.0f), glm::vec3(0.0f, 0.0f, -1.0f));

    glm::mat4 projection = glm::perspective(glm::radians(camera.getFOV()), static_cast<float>(window->getWidth()) / window->getHeight(), 0.1f, 100.0f);

    double last_frame = glfwGetTime();
    
    shader.use();
    shader.setUniformVal("blockTexture", 0);

    while (!glfwWindowShouldClose(window->getWindow()))
    {
        double current_frame = glfwGetTime();
        float delta_time = static_cast<float>(current_frame - last_frame);
        last_frame = current_frame;

        camera.processKeyboardInput(window->getWindow(), delta_time);

        window->updateViewport();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 0.1f, 0.1f, 1.0f);

        shader.use();

        glm::mat4 view = glm::lookAt(camera.getPosition(), camera.getPosition() + camera.getFront(), camera.getUp());
        
        shader.setUniformVal("projection", projection);
        shader.setUniformVal("view", view);
        shader.setUniformVal("model", glm::mat4(1.0f));
        
        block.renderInstanced();
        
        glfwSwapBuffers(window->getWindow());
        glfwPollEvents();
        
        Window::frameRateLimiter(60.0);
    }
}
