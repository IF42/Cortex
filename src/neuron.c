#include "neuron.h"

#include <stdlib.h>


Neuron * 
neuron_new(size_t n_inputs)
{
    Neuron * self = malloc(sizeof(Neuron) + (sizeof(float) * n_inputs));

    if(self != NULL)
        self->n_inputs = n_inputs;

    return self;
}


void
neuron_delete(Neuron * self)
{
    if(self != NULL)
        free(self);
}


