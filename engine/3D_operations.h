#ifndef __3D_OP__
#define __3D_OP__

#ifndef __3D_ENGINE__
#include "3D_engine.h"
#endif

struct vector* cross_product(struct vector*, struct vector*);
struct vector* normalize(struct triangle&);
float dot_product(vector*, vector*);


#endif
