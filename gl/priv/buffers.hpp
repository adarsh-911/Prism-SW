#pragma once

#include <iostream>
#include "stdint.h"
#include <vector>

#include "vertex.hpp"

namespace gl
{
    typedef uint16_t index_t;
    typedef std::vector<vertex_t> vertex_buffer_t;
    typedef std::vector<index_t> index_buffer_t;

    // the current vertex buffer
    inline vertex_buffer_t globalVertexBuffer;
    // The global index buffer
    inline index_buffer_t globalIndexBuffer;
}

