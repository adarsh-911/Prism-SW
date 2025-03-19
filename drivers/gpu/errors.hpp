#pragma once

#include <stdint.h>

// ok
#define GPU_OK 0

// Errors
#define GPU_ERR_NO_RESPONSE 0x1
#define GPU_ERR_TIMEOUT 0x2
#define GPU_ERR_INVALID_PARAMETER 0x3
#define GPU_ERR_UNKNOWN 0xFF

typedef uint8_t gpu_error;

