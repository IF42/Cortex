#include "layer.h"
#include <stdlib.h>


float *
layer_forward(
    Layer * self
    , float * X)
{
    if(self->forward != NULL)
        return self->forward(self, X);
    
    return NULL;
}


float *
layer_backward(
    Layer * self
    , float rate
    , float * y
    , float * gradient)
{
    if(self->backward != NULL)
        return self->backward(self, rate, y, gradient);
    
    return NULL;
}


void
layer_delete(Layer * self)
{
    if(self != NULL && self->delete != NULL)
        self->delete(self);
}
