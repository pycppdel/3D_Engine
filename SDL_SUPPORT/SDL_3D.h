
#ifndef __SDL_3D__
#define __SDL_3D__

#ifndef __3D_ENGINE__
#include "3D_engine.h"
#endif

#ifndef SDL_UTILS_ALL
#include "utils.h"
#endif

#ifndef __3D_OP__
#include "3D_operations.h"
#endif

void draw_triangle(SDL_Renderer*, triangle& );
void draw_mesh(SDL_Renderer*, mesh&);

#endif
