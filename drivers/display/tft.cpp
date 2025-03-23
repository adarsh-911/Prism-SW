#include "tft.hpp"

#include <global/panic.hpp>

namespace drivers::disp
{
    Mode curr_mode;
    glm::uvec2 curr_res;
    size_t curr_pxcnt;

    void setMode(Mode disp_mode)
    {
        switch (disp_mode)
        {
            case Mode::FULL:
                curr_mode = disp_mode;
                curr_res = { 800, 480 };
                curr_pxcnt = 800 * 480;
                break;
            case Mode::HALF:
                curr_mode = disp_mode;
                curr_res = { 400, 240 };
                curr_pxcnt = 400 * 240;
                break;
            default:
                PANIC("invalid display mode");
                break;
        }
    }

    glm::uvec2 getResolution()
    {
        return curr_res;
    }

    size_t getPixelCount()
    {
        return curr_pxcnt;
    }
}