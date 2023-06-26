#ifndef _LOSS_H_
#define _LOSS_H_


#include <stddef.h>

typedef float
(*Loss)(size_t, float *, float *);


float
mse(size_t length, float * y, float * labels);


#endif
