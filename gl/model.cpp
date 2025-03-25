#include "model.hpp"

#include <global/panic.hpp>
#include "gl/obj_loader.hpp"

namespace gl
{
    void Model::from_file(const std::string filepath)
    {
        // Check file extension to determine type
        size_t dot_pos = filepath.find_last_of('.');
        if (dot_pos == std::string::npos) {
            PANIC("Invalid file format for model: " + filepath);
            return;
        }
        
        std::string extension = filepath.substr(dot_pos + 1);
        
        for (auto& c : extension) c = std::tolower(c);
        
        if (extension == "obj") {
            // Load OBJ file
            if (!OBJLoader::loadOBJ(filepath, this, this->vertices, this->indices, this->backend_handle)) {
                PANIC("Failed to load OBJ file: " + filepath);
            }
        } else {
            PANIC("Unsupported model file format: " + extension);
        }
    }

    glm::AABB Model::bounding_box(glm::mat4 model) const
    {
        glm::AABB boundingBox;
        boundingBox.setNull();

        for(auto& vertex : this->vertices)
        {
            auto transformed_vertex = glm::vec3(model * glm::vec4(vertex.position, 1.0f));
            boundingBox.extend(transformed_vertex);
        }

        return boundingBox;
    }

    void Model::draw(gp::uniform_t uniform) const
    {
        if(backend == nullptr)
        {
            PANIC("No backend set for model");
            return;
        }

        backend->drawModel(this->backend_handle, uniform);
    }

}

