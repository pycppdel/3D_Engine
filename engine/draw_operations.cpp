#ifndef __DRAW_OPERATIONS__
#include "draw_operations.h"
#endif

#include <iostream>

namespace engine{
//global color variable
std::stack<SDL_Color> saved_colors;

//variables for global color and if global color is set
SDL_Color GLOBAL_COLOR;
bool GLOBAL_COLOR_SET = false;
}

void engine::draw_circle(SDL_Renderer* r, int x, int y, int radius, SDL_Color& color){


save_color_state();
/*
push_color(color);
set_global_color(r);
pop_color();
*/
pop_color();



}


//to push a color
void engine::push_color(SDL_Color& color){


  saved_colors.push(color);
  if (!GLOBAL_COLOR_SET){
    GLOBAL_COLOR_SET = true;
  }

  GLOBAL_COLOR = saved_colors.top();


}

bool engine::pop_color(){

  if(!GLOBAL_COLOR_SET){

    return false;

  }

  GLOBAL_COLOR = saved_colors.top();
  saved_colors.pop();

  return true;

}

bool engine::save_color_state(){

  if(GLOBAL_COLOR_SET){

    push_color(GLOBAL_COLOR);
    return true;
  }
  else{
    return false;
  }


}
bool engine::set_global_color(SDL_Renderer* r){

  if(GLOBAL_COLOR_SET){

    SDL_SetRenderDrawColor(r, GLOBAL_COLOR.r, GLOBAL_COLOR.g, GLOBAL_COLOR.b, 0xFF);

    return true;
  }

  return false;

}
