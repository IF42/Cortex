#include "dense.h"

#include <math.h>
#include <stdlib.h>


static float *
__forward__(
    Dense * self
    , float * X)
{
    for(size_t i = 0; i < self->neurons; i++)
    {
        self->super.output[i] = self->bias[i];

        for(size_t j = 0; j < self->inputs; j++)
            self->super.output[i] += self->weight[(i * self->inputs) + j] * X[j];

        self->super.output[i] = self->super.activation.act(self->super.output[i]);
    }

    return self->super.output;
}

#include <stdio.h>

static float *
__backward__(
    Dense * self
    , float rate
    , float * y
    , float * input_gradient)
{
    for (size_t i = 0; i < self->neurons; i++) 
    {
        float gradient = input_gradient[i] * self->super.activation.prime(self->super.output[i]);
        self->super.gradient[i] = gradient;
        
        for (size_t j = 0; j < self->inputs; j++) 
            self->weight[(i * self->inputs) + j] -= rate * gradient * y[j];
        
        self->bias[i] -= rate * gradient; 
    }

    return self->super.gradient;
}


Dense *
dense_new(
    size_t inputs
    , size_t neurons
    , const Activation activation)
{
    Dense * self = malloc(sizeof(Dense));

    if(self != NULL)
    {
        self->super.forward    = (LayerForwardCallback) __forward__;
        self->super.backward   = (LayerBackwardCallback) __backward__;
        self->super.delete     = (LayerDeleteCallback) free;
        self->super.activation = activation;

        self->inputs  = inputs;
        self->neurons = neurons;

        self->weight   = malloc(sizeof(float) * neurons * inputs);
        self->bias     = malloc(sizeof(float) * neurons);
        self->super.output   = malloc(sizeof(float) * neurons);
        self->super.gradient = malloc(sizeof(float) * neurons);

        for(size_t i = 0; i < inputs * neurons; i++)
            self->weight[i] = rand() / (float)RAND_MAX;

        for(size_t i = 0; i < neurons; i++)
            self->bias[i] = rand() / (float)RAND_MAX;
    }

    return self;
}



