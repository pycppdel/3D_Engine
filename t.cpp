#include "Engine.h"
#include <iostream>

cube cub;
mesh a, b, c, d;

matrix projection;
xmatrix xmat;
ymatrix ymat;
zmatrix zmat;

bool turning = false;

struct parameters params;

int m_x=0, m_y=0, last_m_x=0, last_m_y=0, h_x, h_y;

float xangle=0, yangle=0, zangle=0, xcommon=0, ycommon=0, zcommon=0;
float xspin = 0, yspin=0;


void draw(struct Display*);
int main(){

  SDL_Rect rect = {100,100, 800, 800};
  SDL_MANAGER m(&rect);

  triangle gt;
  gt.vectors[0] = {0, 0.1, 0};
  gt.vectors[1] = {1, 0, 0};
  gt.vectors[2] = {0, 1, 0};

  vector* ght = normalize(gt);

  std::cout << ght->x << " " << ght->y << " " << ght->z << std::endl;
  std::cout.flush();

  m.init("3D block");

  bool quit = false;
  SDL_Event e;

  m.setDrawMethod(draw);

  while(!quit){

    SDL_GetMouseState(&m_x, &m_y);


    SDL_PollEvent(&e);

    switch(e.type){

      case SDL_QUIT:
                    quit = true;
                    break;
      case SDL_MOUSEBUTTONDOWN:

                    switch(e.button.button){

                      case SDL_BUTTON_LEFT:
                      turning = true;

                      break;

                    }
                    break;
      case SDL_MOUSEBUTTONUP:

                    switch(e.button.button){

                      case SDL_BUTTON_LEFT:
                            turning = false;
                    }
    }

    if (turning){

      yspin = last_m_x-m_x;
      ycommon += yspin;
      xspin = last_m_y-m_y;
      xcommon += xspin;
    }


    xmat.set_angle(-xcommon);
    ymat.set_angle(-ycommon);
    zmat.set_angle(zcommon);

    xmat.transform_mesh(cub, a);
    ymat.transform_mesh(a, b);
    zmat.transform_mesh(b, c);
    for(auto& tri: c.triangles){

      for(int i=0;i<3;i++){
        tri.vectors[i].z += 4.0f;
      }
    }
    projection.transform_mesh(c, d);
    d.scale(params);

    m.draw();

        last_m_x = m_x;
        last_m_y = m_y;
  }

  m.deinit();

  return 0;
}

void draw(struct Display* display){

  SDL_Renderer* r = display->renderer;

  SDL_RenderClear(r);
  draw_mesh(r, d);
  SDL_SetRenderDrawColor(r, 0x0, 0x0, 0x0, 0x0);
  SDL_RenderPresent(r);


}
