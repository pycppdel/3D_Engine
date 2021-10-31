#include "utils.h"
#include "3D_engine.h"
#include "SDL_3D.h"


mesh a, b, c, d, hh, f, g;
cube cub, sec;
matrix m;
ymatrix x;
zmatrix x2;
xmatrix y, y2;


float angle = 1.0f, yangle=1.0f;
float angle2=1.0f, yangle2=1.0f;
void draw(struct Display*);

int main(){



  SDL_Rect rect = {100, 100, 800, 800};
  SDL_MANAGER manager(&rect);

  manager.init("3D");
  manager.setDrawMethod(draw);

  bool quit = false;
  SDL_Event e;
  parameters p;



  while (!quit){
    SDL_PollEvent(&e);

    switch(e.type){

      case SDL_QUIT:

      quit = true;
      break;

      case SDL_MOUSEBUTTONDOWN:
      break;
    }
    x.set_angle(angle);
    y.set_angle(yangle);
    angle += 0.005f;
    yangle += 0.005f;

    angle2 += 0.008f;
    yangle2 += 0.002f;

    x2.set_angle(angle2);
    y2.set_angle(yangle2);

    x.transform_mesh(cub, a);
    y.transform_mesh(a, c);
    x2.transform_mesh(sec, hh);
    y2.transform_mesh(hh, f);
    for(auto& tri: c.triangles){

      for(int i=0;i<3;i++){
        tri.vectors[i].z += 4.0f;
      }
    }

    for(auto& tri: f.triangles){

      for(int i=0;i<3;i++){
        tri.vectors[i].z += 9.0f;

      }
    }
    m.transform_mesh(c, b);
    m.transform_mesh(f, g);

    b.scale(p);
    g.scale(p);

    for(auto& tri: g.triangles){

      for(int i=0;i<3;i++){
        tri.vectors[i].x -= 200.0f;
        tri.vectors[i].y -= 200.0f;

      }
    }
    manager.draw();

  }

  manager.deinit();

  return 0;
}

void draw(struct Display* display){

  SDL_Renderer* r = display->renderer;

  SDL_RenderClear(r);
  SDL_SetRenderDrawColor(r, 0x00, 0x00, 0x00, 0x00);
  draw_mesh(r, b);
  draw_mesh(r, g);
  SDL_SetRenderDrawColor(r, 0x00, 0x00, 0x00, 0x00);
  SDL_RenderPresent(r);

}
