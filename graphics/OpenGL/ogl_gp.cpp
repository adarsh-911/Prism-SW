// filepath: /home/sabo/uni/ee2504/project/prism-sw/graphics/OpenGL/ogl_gp.cpp
#include "ogl_gp.hpp"

#include <global/panic.hpp>
#include <glm/gtc/type_ptr.hpp>

// Macro to call OpenGL functions and check for errors
#define Call(x) \
    x; \
    if (gl_check_error()) { \
        gl_handle_error(); \
    }

bool gl_check_error() {
    GLenum error = glGetError();
    return error != GL_NO_ERROR;
}

bool gl_check_error();
void gl_handle_error();

void gl_handle_error() {
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::string error_string;
        
        switch (error) {
            case GL_INVALID_ENUM:
                error_string = "GL_INVALID_ENUM";
                break;
            case GL_INVALID_VALUE:
                error_string = "GL_INVALID_VALUE";
                break;
            case GL_INVALID_OPERATION:
                error_string = "GL_INVALID_OPERATION";
                break;
            case GL_OUT_OF_MEMORY:
                error_string = "GL_OUT_OF_MEMORY";
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                error_string = "GL_INVALID_FRAMEBUFFER_OPERATION";
                break;
            default:
                // TODO: specify error code
                error_string = "UNKNOWN_ERROR";
                break;
        }
        
        PANIC("OpenGL Error: " + error_string);
    }
}

namespace gp {

OpenGLGP::OpenGLGP() : shader_program(0) {}

void OpenGLGP::init()
{
    // Initialize vertex and fragment shaders
    const std::string vertexShaderSrc = 
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec2 aTexCoord;\n"
        "uniform mat4 model;\n"
        "uniform mat4 view;\n"
        "uniform mat4 projection;\n"
        "out vec2 TexCoord;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
        "    TexCoord = aTexCoord;\n"
        "}\n";

    const std::string fragmentShaderSrc = 
        "#version 330 core\n"
        "in vec2 TexCoord;\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "    FragColor = vec4(TexCoord.xy, 1.0f - TexCoord.x - TexCoord.y, 1.0f);\n"
        "}\n";

    // Create shader program
    shader_program = createShaderProgram(vertexShaderSrc, fragmentShaderSrc);

    // Enable depth testing
    Call(glEnable(GL_DEPTH_TEST));
}

void OpenGLGP::clear(glm::vec3 color) {
    Call(glClearColor(color.r, color.g, color.b, 1.0f));
    Call(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

model_id_t OpenGLGP::generateModel(const vertex_buffer_t &vertices, const index_buffer_t &indices)
{
    GLuint m_vbo, m_vao, m_ibo;

    // Generate and bind VAO
    Call(glGenVertexArrays(1, &m_vao));
    Call(glBindVertexArray(m_vao));

    // Generate and bind VBO
    Call(glGenBuffers(1, &m_vbo));
    Call(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
    Call(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex_t), vertices.data(), GL_STATIC_DRAW));

    // Generate and bind IBO
    Call(glGenBuffers(1, &m_ibo));
    Call(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo));
    Call(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint16_t), indices.data(), GL_STATIC_DRAW));

    this->vbos.push_back(m_vbo);
    this->vaos.push_back(m_vao);
    this->ibos.push_back(m_ibo);

    return this->model_cnt++;
}

texture_id_t OpenGLGP::loadTextureData(void *tex_data)
{
    return texture_id_t();
}

void OpenGLGP::drawModel(model_id_t model_id, uniform_t uniform)
{
    // Bind VAO
    Call(glBindVertexArray(vaos[model_id]));

    // Configure vertex attribute pointers
    // Position attribute
    Call(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, position)));
    Call(glEnableVertexAttribArray(0));

    // Texture coordinate attribute
    Call(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, texture_uv)));
    Call(glEnableVertexAttribArray(1));

    Call(glUseProgram(shader_program));

    GLuint view_loc = glGetUniformLocation(shader_program, "view");
    Call(glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view)));
    
    GLuint projection_loc = glGetUniformLocation(shader_program, "projection");
    Call(glUniformMatrix4fv(projection_loc, 1, GL_FALSE, glm::value_ptr(projection)));

    GLuint model_loc = glGetUniformLocation(shader_program, "model");
    Call(glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(uniform.model)));

    GLsizei buffer_size;
    Call(glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &buffer_size));

    Call(glDrawElements(GL_TRIANGLES, buffer_size, GL_UNSIGNED_SHORT, 0));
}

void OpenGLGP::setGlobalUniforms(glm::mat4 view, glm::mat4 projection)
{
    this->view = view;
    this->projection = projection;
}

void OpenGLGP::render()
{
    // This function is usually handled by GLFW, so we leave it empty
    // as the window's render function should be called externally
}

void OpenGLGP::swapBuffers() {
    // This function is usually handled by GLFW, so we leave it empty
    // as the window's swapBuffers function should be called externally
}

void* OpenGLGP::getBuffer() {
    // This is typically used for software rendering. For OpenGL, we return nullptr
    // as the buffer is managed by the GPU
    return nullptr;
}

void OpenGLGP::destroy() {

    // Clean up VAOs, VBOs, IBOs
    for (size_t i = 0; i < vaos.size(); i++) {
        Call(glDeleteVertexArrays(1, &vaos[i]));
        Call(glDeleteBuffers(1, &ibos[i]));
        Call(glDeleteBuffers(1, &vbos[i]));
    }
    Call(glDeleteProgram(shader_program));
}

GLuint OpenGLGP::compileShader(GLenum type, const std::string& source) {
    GLuint shader = glCreateShader(type);
    const char* src = source.c_str();
    
    Call(glShaderSource(shader, 1, &src, nullptr));
    Call(glCompileShader(shader));
    
    // Check for shader compilation errors
    GLint success;
    Call(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
    
    if (!success) {
        GLchar info_log[512];
        Call(glGetShaderInfoLog(shader, sizeof(info_log), nullptr, info_log));
        PANIC(std::string("Shader compilation failed: ") + info_log);
    }
    
    return shader;
}

GLuint OpenGLGP::createShaderProgram(const std::string& vertexShader, const std::string& fragmentShader) {
    GLuint vertex_shader = compileShader(GL_VERTEX_SHADER, vertexShader);
    GLuint fragment_shader = compileShader(GL_FRAGMENT_SHADER, fragmentShader);
    
    GLuint program = glCreateProgram();
    Call(glAttachShader(program, vertex_shader));
    Call(glAttachShader(program, fragment_shader));
    Call(glLinkProgram(program));
    
    // Check for linking errors
    GLint success;
    Call(glGetProgramiv(program, GL_LINK_STATUS, &success));
    
    if (!success) {
        GLchar info_log[512];
        Call(glGetProgramInfoLog(program, sizeof(info_log), nullptr, info_log));
        PANIC(std::string("Shader program linking failed: ") + info_log);
    }
    
    // Clean up shaders after linking
    Call(glDeleteShader(vertex_shader));
    Call(glDeleteShader(fragment_shader));
    
    return program;
}

OpenGLGP::~OpenGLGP() {
    // Clean up is handled by destroy(), which should be called explicitly
}

}  // namespace gp