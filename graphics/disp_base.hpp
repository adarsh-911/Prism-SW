#pragma once

#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include "types.hpp"

namespace gp
{
    class DisplayBase
    {
        public:
            DisplayBase() = default;

            virtual void init() = 0;

            // set the vsync
            virtual void set_vsync(bool do_vsync) = 0;

            // get the current delta time
            virtual float getDeltaTime() = 0;

            // return underlying engine handle
            virtual void* getDisplayHandle() = 0;

            virtual bool isOpen() = 0;

            // Draw
            virtual void draw(void* buffer) = 0;

            virtual void destroy() = 0;

            ~DisplayBase() = default;
    };
}

