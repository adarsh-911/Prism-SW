#pragma once

#include <iostream>
#include <vector>

#include <glm/glm.hpp>

namespace gp
{
    struct vertex_t
    {
        glm::vec3 position;
        glm::vec2 texture_uv;

        vertex_t() = default;
    };

    typedef uint16_t index_t;
    typedef uint16_t model_id_t;
    typedef uint32_t texture_id_t;
    typedef std::vector<vertex_t> vertex_buffer_t;
    typedef std::vector<index_t> index_buffer_t;
}