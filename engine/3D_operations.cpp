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



bool load_file(std::string name, mesh& into){

into.triangles.clear();

std::ifstream stream;

try{
  stream.open(name.c_str(), std::ios::in);
}

catch(...){
  return false;
}

size_t pos, second_pos;
std::string delim = " ";
std::string second_delim = "/";
std::string line;
std::string code;
std::string token;
std::vector<vector> vectors;
std::stringstream stringstr;

while(std::getline(stream, line, '\n')){

  token = line.substr(0, 1);
  //clearing token from line
  line.erase(0, 2);

  if (token == "v"){

    vector neu;
    int runde = 0;
    float r;

    while((pos=line.find(delim)) != std::string::npos){

      stringstr << line.substr(0, pos);
      stringstr >> r;
      switch(runde){
        case 0: neu.x = r;
                break;
        case 1: neu.y = r;
                break;
      }
      runde++;
      stringstr.clear();
      line.erase(0, pos+delim.length());

    }
    //finding last one
    stringstr << line;
    stringstr >> r;
    neu.z = r;
    stringstr.clear();

    // vector is determined
    vectors.push_back(neu);
  }

  else if(token == "f"){

    triangle tri, tri2;
    float edges[4];
    int round = 0;
    while((pos=line.find(delim)) != std::string::npos){

      code = line.substr(0, pos);
      second_pos = code.find(second_delim);
      stringstr << code.substr(0, second_pos);
      stringstr >> edges[round];
      edges[round]--;
      stringstr.clear();
      round++;
      line.erase(0, pos+delim.length());

    }
    if(line[0] != std::string::npos){
    code = line.substr(0, pos);
    second_pos = code.find(second_delim);
    stringstr << code.substr(0, second_pos);
    stringstr >> edges[round];
    edges[round]--;
    stringstr.clear();
  }
    // for third one

    //now constructing triangles
    tri.vectors[0] = vectors[edges[0]];
    tri.vectors[1] = vectors[edges[1]];
    tri.vectors[2] = vectors[edges[2]];

    if(line[0] != std::string::npos){

    tri2.vectors[0] = vectors[edges[0]];
    tri2.vectors[1] = vectors[edges[2]];
    tri2.vectors[2] = vectors[edges[3]];

  }

  into.triangles.push_back(tri);

  if(line[0] != std::string::npos){
    into.triangles.push_back(tri2);
  }

  }

}


stream.close();

return true;
}
