#include "ogl_cam.hpp"
#include <algorithm>

#include <global/panic.hpp>

namespace gp
{
    OpenGLCamera::OpenGLCamera(float fov, float aspectRatio, float nearPlane, float farPlane) 
        : position(glm::vec3(0.0f, 0.0f, 3.0f)),
        front(glm::vec3(0.0f, 0.0f, -1.0f)),
        worldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
        prevMousePos(320.0f, 240.0f), // Default mouse position
        yaw(-90.0f),
        pitch(0.0f),
        movementSpeed(2.5f),
        mouseSensitivity(0.1f),
        fov(fov),
        aspectRatio(aspectRatio),
        nearPlane(nearPlane),
        farPlane(farPlane)
    {
        updateCameraVectors();
    }

    void OpenGLCamera::update(DisplayBase &display)
    {
        if(!display.getDisplayHandle())
        {
            PANIC("Display handle is null");
        }
        GLFWwindow* window = static_cast<GLFWwindow*>(display.getDisplayHandle());

        glfwPollEvents();

        // update camera
        processKeyboard(window, display.getDeltaTime());
        processMouse(window);
    }

    void OpenGLCamera::processKeyboard(GLFWwindow* window, float deltaTime) {
        float velocity = movementSpeed * deltaTime;
        
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            position += front * velocity;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            position -= front * velocity;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            position -= right * velocity;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            position += right * velocity;
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            position += worldUp * velocity;
        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            position -= worldUp * velocity;
    }

    void OpenGLCamera::processMouse(GLFWwindow* window) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        
        glm::vec2 currentMousePos(static_cast<float>(xpos), static_cast<float>(ypos));
        
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
            float xoffset = currentMousePos.x - prevMousePos.x;
            float yoffset = prevMousePos.y - currentMousePos.y; // Reversed since y-coordinates range from bottom to top
            
            xoffset *= mouseSensitivity;
            yoffset *= mouseSensitivity;
            
            yaw += xoffset;
            pitch += yoffset;
            
            // Make sure that when pitch is out of bounds, screen doesn't get flipped
            pitch = std::clamp(pitch, -89.0f, 89.0f);
            
            // Update front, right, and up Vectors
            updateCameraVectors();
        }
        
        prevMousePos = currentMousePos;
    }

    glm::mat4 OpenGLCamera::getViewMatrix() const  {
        return glm::lookAt(position, position + front, up);
    }

    glm::mat4 OpenGLCamera::getPerspectiveMatrix() const {
        return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
    }

    void OpenGLCamera::setPosition(const glm::vec3& pos) {
        position = pos;
    }

    glm::vec3 OpenGLCamera::getPosition() const {
        return position;
    }

    void OpenGLCamera::setFOV(float newFov) {
        fov = newFov;
    }

    float OpenGLCamera::getFOV() const {
        return fov;
    }

    void OpenGLCamera::setAspectRatio(float newAspectRatio) {
        aspectRatio = newAspectRatio;
    }

    void OpenGLCamera::updateCameraVectors() {
        // Calculate the new front vector
        glm::vec3 newFront;
        newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        newFront.y = sin(glm::radians(pitch));
        newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(newFront);
        
        // Also re-calculate the right and up vector
        right = glm::normalize(glm::cross(front, worldUp));
        up = glm::normalize(glm::cross(right, front));
    }
}

