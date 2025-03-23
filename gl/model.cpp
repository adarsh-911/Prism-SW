#include "model.hpp"

#include <global/panic.hpp>

namespace gl
{
    void Model::from_file(const std::string filepath)
    {
        // TODO: load from object file
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

