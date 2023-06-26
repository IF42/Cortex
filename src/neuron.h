#ifndef _NEURON_H_
#define _NEURON_H_


#include <stddef.h>


typedef struct
{
    size_t n_inputs;
    float bias;
    float weights[];
}Neuron;


Neuron * 
neuron_new(size_t n_inputs);


void
neuron_delete(Neuron * self);



#endif
