#pragma once

#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "../disp_base.hpp"

namespace gp
{
    class OpenGLDisplay : public DisplayBase
    {
        private:
            GLFWwindow* window;

            float deltaTime = 0.0f;
            float lastFrame = 0.0f;

        public:
            OpenGLDisplay() = default;

            void init() override;

            // set the vsync
            void set_vsync(bool do_vsync) override;

            // get the current delta time
            float getDeltaTime() override;

            // return underlying engine handle
            void* getDisplayHandle() override;

            // is the window open
            bool isOpen() override;

            // Draw
            void draw(void* buffer) override;

            void destroy() override;

            ~OpenGLDisplay() = default;
    };
}

