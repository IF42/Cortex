#include "dense.h"

#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <stdio.h>


static void
__forward__(
    Dense * self
    , float * input)
{
    for(size_t i = 0; i < LAYER(self)->n_neurons; i ++)
    {
        LAYER(self)->output[i] = self->neurons[i]->bias;
        
        for(size_t j = 0; j < self->neurons[i]->n_inputs; j++)
            LAYER(self)->output[i] += self->neurons[i]->weights[j] * input[j];

        LAYER(self)->output[i] = LAYER(self)->activation.activation(LAYER(self)->output[i]);
    }
}


static void
__backward__(
    Dense * self
    , float * output_gradient
    , float rate)
{

}


static void
__delete__(Dense * self)
{
    if(self != NULL)
    {
        for(size_t i = 0; i < LAYER(self)->n_neurons; i ++)
            neuron_delete(self->neurons[i]);

        if(LAYER(self)->output != NULL)
            free(LAYER(self)->output);

        free(self);
    }
}


Dense *
dense_new(
      size_t n_inputs
    , size_t n_neurons
    , Activation activation)
{
    Dense * self = malloc(sizeof(Dense) + (sizeof(Neuron*) * n_neurons)); 

    if(self != NULL)
    {
        self->super.forward    = (LayerForward) __forward__;
        self->super.backward   = (LayerBackward) __backward__;
        self->super.activation = activation;
        self->super.delete     = (LayerDelete) __delete__;

        self->super.n_neurons = n_neurons;
        self->super.output    = malloc(sizeof(float) * n_neurons);

        srand(time(NULL));

        for(size_t i = 0; i < n_neurons; i++)
        {
            self->neurons[i] = neuron_new(n_inputs);

            self->neurons[i]->bias = ((float) rand()) / ((float)RAND_MAX);

            for(size_t j = 0; j < n_inputs; j ++)
                self->neurons[i]->weights[j] = ((float) rand()) / ((float)RAND_MAX);
        }
    }

    return self;
}


