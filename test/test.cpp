#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define USE_OPENGL_BACKEND
#include <graphics/gp.hpp>

int local_test()
{
    gp::OpenGLDisplay display;
    display.init();

    // triangle vertices
    gp::vertex_buffer_t vertices = {
        {{0.0f, 0.5f, 1.0f}, {0.0f, 0.0f}},
        {{0.5f, -0.5f, 1.0f}, {0.0f, 1.0f}},
        {{-0.5f, -0.5f, 1.0f}, {1.0f, 0.0f}}
    };

    // triangle indices
    gp::index_buffer_t indices = {0, 1, 2};

    // Create a camera
    gp::OpenGLCamera camera(60.0f, 800.0f / 600.0f, 0.1f, 100.0f);
    
    // Make a camera looking at the triangle
    glm::mat4 model = glm::mat4(1.0f);
    
    // send the model to the GPU
    gp::OpenGLGP gp;
    gp.init();

    // generate the model
    gp::model_id_t model_id = gp.generateModel(vertices, indices);

    while (display.isOpen())
    {
        camera.update(display);
        gp.clear({0.0f, 0.0f, 0.0f});

        // Set the global uniforms
        gp.setGlobalUniforms(camera.getViewMatrix(), camera.getPerspectiveMatrix());

        // Draw the model
        gp.drawModel(model_id, {model, 0});

        // render the scene
        gp.render();

        display.draw(gp.getBuffer());
    }

    gp.destroy();
    display.destroy();

    return 0;
}


