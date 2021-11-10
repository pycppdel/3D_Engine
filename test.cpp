#include <iostream>
#include "utils.h"

#define width 800
#define height 800
#define X 100
#define Y 100
#define APP_NAME "__"


void draw(struct Display*);


int main(int argc, char** argv){

SDL_Rect rect = {X, Y, width, height};

SDL_MANAGER manager(&rect);
manager.init(APP_NAME);
manager.setDrawMethod(draw);

bool quit = false;
SDL_Event evt;

while(!quit){

SDL_PollEvent(&evt);

switch(evt.type){

case SDL_QUIT:
              //do something
              quit = true;
              break;
}

manager.draw();

}

manager.deinit();

return 0;

}


void draw(struct Display* display){

SDL_Renderer* r = display->renderer;

SDL_RenderClear(r);
SDL_SetRenderDrawColor(r, 0x0, 0x0, 0x0, 0x0);
SDL_RenderPresent(r);

}
