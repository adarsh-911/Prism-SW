#pragma once

#include <iostream>
#include "stdint.h"

#include <glm/glm.hpp>

namespace gl
{
    struct vertex_t
    {
        glm::vec3 position;
        glm::vec2 texture_uv;

        vertex_t() = default;
    } __attribute__((__packed__));
}

