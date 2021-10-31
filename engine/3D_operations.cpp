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

void load_file(std::string name, mesh& into){

into.triangles.clear();
std::fstream file;
file.open(name.c_str(), std::ios::in);

std::vector<vector> vectors;


std::string number;
std::stringstream stream;

size_t pos1, pos2, pos3, pos4;
float num1, num2, num3, num4;


while(std::getline(file, number)){

if(number[0] == 'v'){

pos1 = number.find(" ");
pos2 = number.find(" ", pos1+1);
pos3 = number.find(" ", pos2+1);

stream << number.substr(pos1, pos2);
stream >> num1;
stream << number.substr(pos2, pos3);
stream >> num2;
stream << number.substr(pos3+1);
stream >> num3;


vector g = {num1, num2, num3};
vectors.push_back(g);


}
else if (number[0] == 'f'){

  pos1 = number.find(" ");
  pos2 = number.find(" ", pos1+1);
  pos3 = number.find(" ", pos2+1);
  pos4 = number.find(" ", pos4+1);

  stream << number.substr(pos1, pos2);
  stream >> num1;
  stream << number.substr(pos2, pos3);
  stream >> num2;
  stream << number.substr(pos3, pos4);
  stream >> num3;
  stream << number.substr(pos4+1);
  stream >> num4;

  triangle m, m2;

  m.vectors[0] = vectors[((int)num1)-1];
  m.vectors[1] = vectors[((int)num2)-1];
  m.vectors[2] = vectors[((int)num3)-1];

  m2.vectors[0] = vectors[((int)num1)-1];
  m2.vectors[1] = vectors[((int)num3)-1];
  m2.vectors[2] = vectors[((int)num4)-1];

  into.triangles.push_back(m);
  into.triangles.push_back(m2);




}

}

file.close();
}
