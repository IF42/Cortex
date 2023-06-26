#include "sequential.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static void
__delete__(Sequential * self)
{
    if(self != NULL)
    {
        for(size_t i = 0; i < self->n_layers; i++)
            layer_delete(self->layers[i]);

        free(self);
    }   
}

#include <stdio.h>

static void
__fit__(
    Sequential * self
    , size_t length
    , float * inputs)
{
    for(size_t i = 0; i < self->n_layers; i++)
    {
        if(i == 0)
            layer_forward(self->layers[i], inputs);
        else
            layer_forward(self->layers[i], self->layers[i-1]->output);
    }
}


static void
__save__(
    Sequential * self
    , FILE * stream)
{

}


Sequential *
sequential_new(
    size_t n_layers
    , Layer * layers[n_layers])
{
    size_t memsize    = sizeof(Layer *)*n_layers;
    Sequential * self = malloc(sizeof(Sequential) + memsize);

    if(self != NULL)
    {
        self->super.delete = (ModelDelete) __delete__;
        self->super.fit    = (ModelFit) __fit__;
        self->super.save   = (ModelSave) __save__;

        self->n_layers = n_layers;
        memcpy(self->layers, layers, memsize);
    }

    return self;
}



