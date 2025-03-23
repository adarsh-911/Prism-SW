#pragma once

#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include "types.hpp"

namespace gp
{
    struct uniform_t
    {
        glm::mat4 model;
        texture_id_t texture_id;
    };

    // Base class for all Graphics Processors
    class BaseGP
    {
        public:
            // Initialize the GPU
            virtual void init() = 0;
            // Clear the screen with some color
            virtual void clear(glm::vec3 color) = 0;
            // Generate a model
            virtual model_id_t generateModel(const vertex_buffer_t& vertices, const index_buffer_t& indices) = 0;
            // Load a texture
            virtual texture_id_t loadTextureData(void* tex_data) = 0;
            // Draw a model with it's uniform values
            virtual void drawModel(model_id_t model_id, uniform_t uniform_values) = 0;
            // Setup the global uniforms
            virtual void setGlobalUniforms(glm::mat4 view, glm::mat4 projection) = 0;
            // Render the scene
            virtual void render() = 0;
            // Swap the buffers
            virtual void swapBuffers() = 0;
            // Get the current buffer
            virtual void* getBuffer() = 0;
            // Destroy the GPU
            virtual void destroy() = 0;
    };
}



