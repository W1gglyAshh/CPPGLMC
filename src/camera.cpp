// this file is for implementing the functions declared in camera.h
//
// created by Gabriel LU on Mar 1, 2025
//

#include "camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 direction)
    : position(position), world_up(glm::vec3(0.0f, 1.0f, 0.0f)), yaw(-90.0f), pitch(0.0f), movement_speed(2.5f), mouse_sensitivity(0.1f), fov(45.0f),
      first_mouse(true), last_x(0.0f), last_y(0.0f)
{
    front = glm::normalize(direction);

    yaw = glm::degrees(atan2(front.z, front.x));
    pitch = glm::degrees(asin(glm::clamp(front.y, -1.0f, 1.0f)));

    updateCameraVectors();
}

void Camera::processKeyboardInput(GLFWwindow *window, float delta_time)
{
    float velocity = movement_speed * delta_time;
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        position += front * velocity;
    } else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        position -= front * velocity;
    } else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        position -= right * velocity;
    } else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        position += right * velocity;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        position -= up * velocity;
    } else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        position += up * velocity;
    }
}

void Camera::processMouseInput(float x, float y)
{
    if (first_mouse)
    {
        last_x = x;
        last_y = y;
        first_mouse = false;
    }
    
    float x_offset = x - last_x;
    float y_offset = last_y - y;
    
    last_x = x;
    last_y = y;
    
    x_offset *= mouse_sensitivity;
    y_offset *= mouse_sensitivity;
    
    yaw += x_offset;
    pitch += y_offset;
    
    if (pitch > 89.0f)
    {
        pitch = 89.0f;
    } else if (pitch < -89.0f)
    {
        pitch = -89.0f;
    }
    
    updateCameraVectors();
}

void Camera::updateCameraVectors()
{
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    
    front = glm::normalize(direction);
    right = glm::normalize(glm::cross(front, world_up));
    up = glm::normalize(glm::cross(right, front));
}

void Camera::setMovementSpeed(float speed)
{
    if (speed <= 0.0f)
    {
        std::cerr << "Invalid speed value! Ignoring request." << std::endl;
        return;
    }
    movement_speed = speed;
}

void Camera::setMouseSensitivity(float sensitivity)
{
    if (sensitivity <= 0.0f)
    {
        std::cerr << "Invalid sensitivity value! Ignoring request." << std::endl;
        return;
    }
    mouse_sensitivity = sensitivity;
}

void Camera::setFOV(float fov_in)
{
    if (fov_in <= 0.0f || fov_in >= 180.0f)
    {
        std::cerr << "Invalid FOV value! Ignoring request." << std::endl;
        return;
    }
    fov = fov_in;
}
