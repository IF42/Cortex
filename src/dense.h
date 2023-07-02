#ifndef _DENSE_H_
#define _DENSE_H_

#include "layer.h"

#include <stddef.h>


typedef struct
{
    Layer super;
    
    size_t inputs;
    size_t neurons;

    float * weight;
    float * bias;
}Dense;



Dense *
dense_new(
    size_t inputs
    , size_t neurons
    , const Activation activation);




#endif
