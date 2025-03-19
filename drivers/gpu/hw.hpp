#pragma once

#include "errors.hpp"

namespace driver::hw
{
    enum class cmd : uint8_t
    {
        SET
    };

    gpu_error reset();

    namespace dma
    {
        gpu_error core_buffers(void* addr, uint32_t size_in_bytes);
        gpu_error schdl_buffer(void* addr, uint32_t size_in_bytes);
    }

    gpu_error execute_cmd();

    gpu_error kill();

}


