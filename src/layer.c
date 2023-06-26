#include "layer.h"


void
layer_forward(
    Layer * self
    , float * input)
{
    if(self->forward != NULL)
        self->forward(self, input);
}


void
layer_backward(
    Layer * self
    , float * output_gradient
    , float rate)
{
    if(self->backward != NULL)
        self->backward(self, output_gradient, rate);
}


void
layer_delete(Layer * self)
{
    if(self != NULL && self->delete != NULL)
        self->delete(self);
}

