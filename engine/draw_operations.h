#ifndef __DRAW_OPERATIONS__
#define __DRAW_OPERATIONS__

#ifndef SDL_UTILS_ALL
#include "utils.h"
#endif

#include <cmath>
#include <stack>
#include <cinttypes>

//encapsulated in namespace engine

namespace engine{

  struct Color{

  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t alpha=0xFF;

  };

//draws circle from middle point with radius r and color color
void draw_circle(SDL_Renderer*, int, int, int, Color&);
//to save and reset a color


//methods
void push_color(Color&);
bool pop_color();
//Checks if color is here, if so then push
bool save_color_state();
bool set_global_color(SDL_Renderer*);
void to_SDL_Color(Color&, SDL_Color&);

}

#endif
