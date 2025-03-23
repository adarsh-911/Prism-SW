// filepath: /home/sabo/uni/ee2504/project/prism-sw/graphics/gl_gp.hpp
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <global/panic.hpp>
#include "../gp_base.hpp"

namespace gp
{
    class OpenGLGP : public BaseGP
    {
        private:
            size_t model_cnt;

            std::vector<GLuint> vaos;
            std::vector<GLuint> vbos;
            std::vector<GLuint> ibos;

            glm::mat4 view;
            glm::mat4 projection;

            GLuint shader_program; // Shader program
            
            // Shader utility functions
            GLuint compileShader(GLenum type, const std::string& source);
            GLuint createShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
            
        public:
            OpenGLGP();
            
            void init() override;
            
            void clear(glm::vec3 color) override;

            // Generate a model
            model_id_t generateModel(const vertex_buffer_t& vertices, const index_buffer_t& indices);
            // Load a texture
            texture_id_t loadTextureData(void* tex_data);
            // Draw a model with it's uniform values
            void drawModel(model_id_t model_id, uniform_t uniforms);
            // Setup the global uniforms
            void setGlobalUniforms(glm::mat4 view, glm::mat4 projection);
            
            void render() override;
            void swapBuffers() override;
            void* getBuffer() override;
            
            void destroy() override;

            ~OpenGLGP();
    };
}