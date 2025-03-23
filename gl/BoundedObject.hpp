#pragma once
#include <iostream>

#include <glm/glm.hpp>
#include <glm-aabb/AABB.hpp>

namespace gl
{
    // virutal class
    class BoundedGeometry
    {
        public:
            virtual glm::AABB getBoundingBox() const = 0;
    };
}




