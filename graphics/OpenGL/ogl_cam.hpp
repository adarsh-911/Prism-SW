#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../cam_base.hpp"

namespace gp
{
    class OpenGLCamera : public CameraBase
    {
        public:
            // Constructor with default parameters
            OpenGLCamera(float fov = 45.0f, float aspectRatio = 16.0f/9.0f, float nearPlane = 0.1f, float farPlane = 100.0f);
            
            // Update
            void update(DisplayBase& display) override;

            // Matrix getters
            glm::mat4 getViewMatrix() const override;
            glm::mat4 getPerspectiveMatrix() const override;
            
            // Setters and getters
            void setPosition(const glm::vec3& pos);
            glm::vec3 getPosition() const;
            void setFOV(float fov);
            float getFOV() const;
            void setAspectRatio(float aspectRatio);
            
        private:
            // Camera attributes
            glm::vec3 position;
            glm::vec3 front;
            glm::vec3 up;
            glm::vec3 right;
            glm::vec3 worldUp;
            
            glm::vec2 prevMousePos;
            
            // Euler angles
            float yaw;
            float pitch;
            
            // Camera options
            float movementSpeed;
            float mouseSensitivity;
            float fov;
            float aspectRatio;
            float nearPlane;
            float farPlane;
            
            // Camera control with GLFW input
            void processKeyboard(GLFWwindow* window, float deltaTime);
            void processMouse(GLFWwindow* window);

            // Calculates the front, right and up vectors from the camera's Euler angles
            void updateCameraVectors();
    };
}


