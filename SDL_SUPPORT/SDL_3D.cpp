#ifndef __SDL_3D__
#include "SDL_3D.h"
#endif
#include <iostream>

struct Camera cam;

void draw_triangle(SDL_Renderer* r, triangle& t){



vector* norm = normalize(t);
if(dot_product(&cam.view, norm) < 1){

SDL_SetRenderDrawColor(r, 0xFF, 0xFF, 0xFF, 0xFF);
SDL_RenderDrawLine(r, t.vectors[0].x, t.vectors[0].y, t.vectors[1].x, t.vectors[1].y);
SDL_RenderDrawLine(r, t.vectors[1].x, t.vectors[1].y, t.vectors[2].x, t.vectors[2].y);
SDL_RenderDrawLine(r, t.vectors[2].x, t.vectors[2].y, t.vectors[0].x, t.vectors[0].y);
SDL_SetRenderDrawColor(r, 0x00, 0x00, 0x00, 0x00);
}

delete norm;

}

void draw_mesh(SDL_Renderer* r, mesh& m){

SDL_SetRenderDrawColor(r, 0xFF, 0xFF, 0xFF, 0xFF);
for(auto triang: m.triangles){

  draw_triangle(r, triang);

}
SDL_SetRenderDrawColor(r, 0x00, 0x00, 0x00, 0x00);
}
