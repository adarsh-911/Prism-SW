#include <stdexcept>
#include <global/panic.hpp>
#include "ogl_disp.hpp"

namespace gp
{
    void OpenGLDisplay::init()
    {
        // Initialize GLFW
        if (!glfwInit())
        {
            PANIC("Failed to initialize GLFW");
        }

        // Configure GLFW
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        
        // Create window
        window = glfwCreateWindow(800, 600, "OpenGL Window", nullptr, nullptr);
        if (window == nullptr)
        {
            glfwTerminate();
            PANIC("Failed to create GLFW window");
        }
        
        glfwMakeContextCurrent(window);
        
        // Initialize GLEW
        if (glewInit() != GLEW_OK)
        {
            glfwTerminate();
            PANIC("Failed to initialize GLEW");
        }
        
        // Set vsync on by default
        //glfwSwapInterval(1);
        
        // Initialize time
        lastFrame = glfwGetTime();

        this->deltaTime = false;
    }
    
    void OpenGLDisplay::set_vsync(bool do_vsync)
    {
        //glfwSwapInterval(do_vsync ? 1 : 0);
    }
    
    float OpenGLDisplay::getDeltaTime()
    {
        return deltaTime;
    }

    void OpenGLDisplay::draw(void *buffer)
    {
        glfwSwapBuffers(window);
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
    }

    void OpenGLDisplay::destroy()
    {
        glfwTerminate();
    }

    void* OpenGLDisplay::getDisplayHandle()
    {
        return window;
    }
    bool OpenGLDisplay::isOpen()
    {
        return !glfwWindowShouldClose(window);
    }
}
