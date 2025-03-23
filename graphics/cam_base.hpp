#pragma once

#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include "types.hpp"
#include "disp_base.hpp"

namespace gp
{
    class CameraBase
    {
        public:
            CameraBase() = default;

            virtual void update(DisplayBase& display) = 0;

            virtual glm::mat4 getViewMatrix() const = 0;
            virtual glm::mat4 getPerspectiveMatrix() const = 0;

            ~CameraBase() = default;
    };
}
