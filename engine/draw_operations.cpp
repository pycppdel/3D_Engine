#ifndef __DRAW_OPERATIONS__
#include "draw_operations.h"
#endif

#include <iostream>

namespace engine{

//global color variable
std::stack<Color> saved_colors;

//variables for global color and if global color is set
Color GLOBAL_COLOR;
bool GLOBAL_COLOR_SET = false;
}

void engine::draw_circle(SDL_Renderer* r, int x, int y, int radius, Color& color){


}


//to push a color
void engine::push_color(Color& color){


}

bool engine::pop_color(){

return true;
}

bool engine::save_color_state(){

return true;

}
bool engine::set_global_color(SDL_Renderer* r){


return true;

}

void engine::to_SDL_Color(Color&, SDL_Color&){
  
}
