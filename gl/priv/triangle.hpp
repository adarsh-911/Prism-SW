#pragma once
#include <iostream>

#include <glm/glm.hpp>

#include "buffers.hpp"
#include "BoundedObject.hpp"
#include "vertex.hpp"

namespace gl
{
    class Triangle
    {
        private:
            static size_t triangle_cnt;
        public:
            // index to vertex
            index_t indices[3];

            static void init();

            Triangle() = default;
            Triangle(index_t v[3]);

            glm::AABB getBoundingBox(glm::mat4 model_mat);

            ~Triangle();
    };
}

