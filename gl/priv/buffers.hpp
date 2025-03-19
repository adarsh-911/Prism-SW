#pragma once

#include <iostream>
#include "stdint.h"
#include <vector>

#include "vertex.hpp"

namespace gl
{
    typedef std::vector<vertex_t> vertex_buffer_t;
    typedef uint16_t index_t;

    // the current vertex buffer
    inline vertex_buffer_t globalVertexBuffer;
}

