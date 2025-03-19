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
            std::vector<Triangle> triangle_buffer;

            Model();

            glm::AABB getBoundingBox(glm::mat4 model_mat);

            ~Model();
    };
}