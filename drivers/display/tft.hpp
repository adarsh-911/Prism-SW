#pragma once

#include <iostream>
#include <stdint.h>

#include <glm/glm.hpp>

namespace drivers::disp
{
    enum class Mode : uint8_t
    {
        FULL = 0,       // full res 800 x 480
        HALF,   // 400 x 240
    };

    inline void setMode(Mode disp_mode);

    inline size_t getPixelCount();
    inline glm::uvec2 getResolution();

    // assuems buffer is getPixelCount() big.
    glm::uvec2 displayFramebuffer(uint8_t* buffer);
}

