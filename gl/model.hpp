#pragma once
#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include "priv/BoundedObject.hpp"
#include "priv/triangle.hpp"

namespace gl
{
    class Model
    {
        public:
            vertex_buffer_t vertices;
            index_buffer_t indices;

            Model();

            // load a object from .obj file
            void from_file(const std::string filepath);

            ~Model();
    };
}