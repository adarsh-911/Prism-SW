#pragma once

#include "types.hpp"
#include "gp_base.hpp"
#include "cam_base.hpp"
#include "disp_base.hpp"

#ifdef USE_OPENGL_BACKEND
#include "OpenGL/ogl_gp.hpp"
#include "OpenGL/ogl_cam.hpp"
#include "OpenGL/ogl_disp.hpp"
#else
// another backend
#endif

