#ifndef __DRAW_OPERATIONS__
#define __DRAW_OPERATIONS__

#ifndef SDL_UTILS_ALL
#include "utils.h"
#endif

#include <cmath>
#include <stack>

//encapsulated in namespace engine

namespace engine{

//draws circle from middle point with radius r and color color
void draw_circle(SDL_Renderer*, int, int, int, SDL_Color&);
//to save and reset a color


//methods
void push_color(SDL_Color&);
bool pop_color();
//Checks if color is here, if so then push
bool save_color_state();
bool set_global_color(SDL_Renderer*);

}

#endif
