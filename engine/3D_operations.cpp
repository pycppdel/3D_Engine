#ifndef __3D_OP__
#include "3D_operations.h"
#endif

struct vector* cross_product(vector* a, vector* b){

  vector* back = new vector;

  back->x = a->y*b->z-b->y*a->z;
  back->y = a->z*b->x-a->x*b->z;
  back->z = a->x*b->y-a->y*b->x;

  return back;

}

struct vector* normalize(triangle& t){

  vector *back, *a, *b;

  a = t.vectors[1]-t.vectors[0];
  b = t.vectors[2]-t.vectors[1];

  back = cross_product(a, b);

  delete a;
  delete b;

  return back;

}

float dot_product(vector* a, vector*b){

  return (a->x*b->x+a->y*b->y+a->z*b->z);
}
