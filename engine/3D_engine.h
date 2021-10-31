#ifndef __3D_ENGINE__
#define __3D_ENGINE__
#include <vector>
#include <cmath>

#define PI 3.1416

struct parameters{

int width = 800;
int height = 800;

float aspect_ratio = 1.0;

float theta = 90.0;

float ffar = 100;
float fnear = 0.001;
float ffovRad = 1/tanf((theta/2/180.0*PI));

};

struct vector{

  float x, y, z;

  friend struct vector* operator-(struct vector& a, struct vector& b){

    vector* back = new vector;
    back->x = a.x-b.x;
    back->y = a.y-b.y;
    back->z = a.z-b.z;

    return back;
  }

};

struct triangle{

vector vectors[3];

};

struct mesh{

std::vector<triangle> triangles;

void scale(struct parameters p){
  for (auto& tri: triangles){

    for(int i=0;i<3;i++){
      tri.vectors[i].x += 1.0f;
      tri.vectors[i].y += 1.0f;
      tri.vectors[i].x *= 0.5*p.width;
      tri.vectors[i].y *= 0.5*p.height;
    }

  }
}

};


struct matrix{

float projection_matrix[4][4] = {0};
parameters p;

matrix(){
  parameters g;
  set_parameters(g);

}

void set_parameters(struct parameters n){

  for(int i=0;i<4;i++){
    for(int z=0;z<4;z++){
      projection_matrix[i][z] = 0;
    }
  }
  p = n;
  projection_matrix[0][0] = p.aspect_ratio*p.ffovRad;
  projection_matrix[1][1] = p.ffovRad;
  projection_matrix[2][2] = (p.ffar)/(p.ffar-p.fnear);
  projection_matrix[2][3] = ((-p.ffar*p.fnear)/(p.ffar-p.fnear));
  projection_matrix[3][2] = 1.0f;
}

void transform(vector& from, vector& target){

  target.x = from.x*projection_matrix[0][0]+from.y*projection_matrix[0][1]+from.z*projection_matrix[0][2]+projection_matrix[0][3];
  target.y = from.x*projection_matrix[1][0]+from.y*projection_matrix[1][1]+from.z*projection_matrix[1][2]+projection_matrix[1][3];
  target.z = from.x*projection_matrix[2][0]+from.y*projection_matrix[2][1]+from.z*projection_matrix[2][2]+projection_matrix[2][3];

  float fourth = from.x*projection_matrix[3][0]+from.y*projection_matrix[3][1]+from.z*projection_matrix[3][2]+projection_matrix[3][3];

  if(fourth != 0.0){

    target.x /= fourth;
    target.y /= fourth;
    target.z /= fourth;
  }
}

void transform_triangle(triangle& from, triangle& to){

  transform(from.vectors[0], to.vectors[0]);
  transform(from.vectors[1], to.vectors[1]);
  transform(from.vectors[2], to.vectors[2]);
}

void transform_mesh(mesh& from, mesh& to){

int index =0;


if(to.triangles.empty()){
  for(auto& tri: from.triangles){
    triangle m;
    to.triangles.push_back(m);
  }
}
for(auto& tri: from.triangles){

  try{
    transform_triangle(tri, to.triangles[index++]);
  }
  catch(...){
    triangle m;
    to.triangles.push_back(m);
    transform_triangle(tri, to.triangles[index-1]);
  }
}

}

};

struct xmatrix: matrix{


float angle=20.0;

xmatrix(){

  set_angle(20.0);

}

void set_angle(float a){

  for(int i=0;i<4;i++){
    for(int z=0;z<4;z++){
      projection_matrix[i][z] = 0;
    }
  }
  angle = a;
  projection_matrix[0][0] = 1.0;
  projection_matrix[1][1] = cosf(angle/180*PI);
  projection_matrix[1][2] = sinf(angle/180*PI);
  projection_matrix[2][1] = -sinf(angle/180*PI);
  projection_matrix[2][2] = cosf(angle/180*PI);
  projection_matrix[3][3] = 1.0f;
}

};

struct zmatrix: matrix{


float angle=20.0;

zmatrix(){

  set_angle(20.0);

}

void set_angle(float a){

  for(int i=0;i<4;i++){
    for(int z=0;z<4;z++){
      projection_matrix[i][z] = 0;
    }
  }
  angle = a;
  projection_matrix[0][0] = cosf(angle/180*PI);
  projection_matrix[0][1] = sinf(angle/180*PI);
  projection_matrix[1][0] = -sinf(angle/180*PI);
  projection_matrix[1][1] = cosf(angle/180*PI);
  projection_matrix[2][2] = 1.0f;
  projection_matrix[3][3] = 1.0f;
}

};

struct ymatrix: matrix{


float angle=20.0;

ymatrix(){

  set_angle(20.0);

}

void set_angle(float a){
  for(int i=0;i<4;i++){
    for(int z=0;z<4;z++){
      projection_matrix[i][z] = 0;
    }
  }
  angle = a;
  projection_matrix[0][0] = cosf(angle/180*PI);
  projection_matrix[0][2] = -sinf(angle/180*PI);
  projection_matrix[1][1] = 1.0f;
  projection_matrix[2][0] = sinf(angle/180*PI);
  projection_matrix[2][2] = cosf(angle/180*PI);
  projection_matrix[3][3] = 1.0f;
}

};

struct cube: mesh{

cube(){

  triangle a, b, c, d, e, f, g, h, i, j, k, l;
  a.vectors[0] = {0, 0,0};
  a.vectors[1] = {0, 1, 0};
  a.vectors[2] = {1, 1, 0};

  b.vectors[0] = {0, 0 ,0};
  b.vectors[1] = {1, 1, 0};
  b.vectors[2] = {1, 0, 0};

  c.vectors[0] = {1, 0, 0};
  c.vectors[1] = {1, 1, 0};
  c.vectors[2] = {1, 1, 1};

  d.vectors[0] = {1, 0,0};
  d.vectors[1] = {1, 1, 1};
  d.vectors[2] = {1, 0, 1};


  e.vectors[0] = {1, 0 ,1};
  e.vectors[1] = {1, 1, 1};
  e.vectors[2] = {0, 1, 1};

  f.vectors[0] = {1, 0, 1};
  f.vectors[1] = {0, 1, 1};
  f.vectors[2] = {0, 0, 1};


  g.vectors[0] = {0, 0,1};
  g.vectors[1] = {0, 1, 1};
  g.vectors[2] = {0, 1, 0};

  h.vectors[0] = {0, 0,1};
  h.vectors[1] = {0, 1, 0};
  h.vectors[2] = {0, 0, 0};

  //

  i.vectors[0] = {0, 1,0};
  i.vectors[1] = {0, 1, 1};
  i.vectors[2] = {1, 1, 1};

  j.vectors[0] = {0, 1,0};
  j.vectors[1] = {1, 1, 1};
  j.vectors[2] = {1, 1, 0};



  k.vectors[0] = {1, 0,1};
  k.vectors[1] = {0, 0, 1};
  k.vectors[2] = {0, 0, 0};

  l.vectors[0] = {1, 0,1};
  l.vectors[1] = {0, 0, 0};
  l.vectors[2] = {1, 0, 0};



  triangles.push_back(a);
  triangles.push_back(b);
  triangles.push_back(c);
  triangles.push_back(d);

  triangles.push_back(e);
  triangles.push_back(f);
  triangles.push_back(g);
  triangles.push_back(h);
  triangles.push_back(i);
  triangles.push_back(j);

  triangles.push_back(k);
  triangles.push_back(l);



}

};

struct Camera{

vector view = {0, 0, 1};

};


#endif
