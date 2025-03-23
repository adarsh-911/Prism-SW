#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <graphics/gp.hpp>
#include "Camera.hpp"

int local_test()
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr);

    if (!window)
    {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }

    /*
    struct vertex_t
    {
        glm::vec3 position;
        glm::vec2 texture_uv;

        vertex_t() = default;
    } __attribute__((__packed__));
    */
    // triangle vertices
    gp::vertex_buffer_t vertices = {
        {{0.0f, 0.5f, 1.0f}, {0.0f, 0.0f}},
        {{0.5f, -0.5f, 1.0f}, {0.0f, 1.0f}},
        {{-0.5f, -0.5f, 1.0f}, {1.0f, 0.0f}}
    };

    // triangle indices
    gp::index_buffer_t indices = {0, 1, 2};

    // Create a camera
    Camera camera(60.0f, 800.0f / 600.0f, 0.1f, 100.0f);
    
    // Make a camera looking at the triangle
    /*
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective(glm::radians(60.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    */
    glm::mat4 model = glm::mat4(1.0f);
    
    // send the model to the GPU
    gp::OpenGLGP gp;
    gp.init();

    // generate the model
    gp::model_id_t model_id = gp.generateModel(vertices, indices);

    // deltaTime
    float deltaTime = 1/60.0f;
    float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        gp.clear({0.0f, 0.0f, 0.0f});

        // Render a color triangle
        /*
        glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(0.0f, 0.5f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(0.5f, -0.5f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(-0.5f, -0.5f);
        glEnd();
        */

        camera.processKeyboard(window, deltaTime);
        camera.processMouse(window);

        // Set the global uniforms
        gp.setGlobalUniforms(camera.getViewMatrix(), camera.getPerspectiveMatrix());

        // Draw the model
        gp.drawModel(model_id, {model, 0});

        // render the scene
        gp.render();

        glfwSwapBuffers(window);

        // update deltaTime
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
    }

    glfwTerminate();

    return 0;
}


