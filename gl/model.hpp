#pragma once
#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm-aabb/AABB.hpp>

#include "common.hpp"

namespace gl
{
    class Model
    {
        public:
            gp::vertex_buffer_t vertices;
            gp::index_buffer_t indices;
            
            gp::model_id_t backend_handle;
        
            Model() = default;

            // load a object from .obj file
            void from_file(const std::string filepath);

            // calculate the bounding box of the model
            glm::AABB bounding_box(glm::mat4 model) const;

            // drae the model
            void draw(gp::uniform_t uniform) const;

            ~Model() = default;
    };
}