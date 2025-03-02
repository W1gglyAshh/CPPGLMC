// this file is for defining the camera class
//
// created by Gabriel LU on Mar 1, 2025
//

#pragma once

#include "include.h"

class Camera
{
  private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 world_up;

    float yaw;
    float pitch;

    float movement_speed;
    float mouse_sensitivity;
    float fov;

    float last_x, last_y;

    void updateCameraVectors();

  public:
    bool first_mouse;
    
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 direction = glm::vec3(0.0f, 0.0f, -1.0f));
    ~Camera() = default;
    
    glm::mat4 getViewMatrix() const { return glm::lookAt(position, position + front, up); }
    glm::mat4 getProjectionMatrix(float aspect_ratio) const { return glm::perspective(glm::radians(fov), aspect_ratio, 0.1f, 100.0f); }
    
    void processKeyboardInput(GLFWwindow *&window, float delta_time);
    void processMouseInput(float x, float y);
    
    void setMovementSpeed(float speed);
    void setMouseSensitivity(float sensitivity);
    void setFOV(float fov);
    
    glm::vec3 getPosition() const { return position; }
    glm::vec3 getFront() const { return front; }
    glm::vec3 getUp() const { return up; }
    glm::vec3 getRight() const { return right; }
};
