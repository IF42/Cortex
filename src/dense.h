#ifndef _DENSE_H_
#define _DENSE_H_ 

#include "layer.h"
#include "neuron.h"
#include "activation.h"

#include <stddef.h>


typedef struct 
{
    Layer super;

    size_t n_inputs;
    float weights[];
}Dense;



Dense *
dense_new(
    size_t n_inputs
    , size_t n_neurons
    , Activation activation);


#endif
