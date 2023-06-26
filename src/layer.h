#ifndef _LAYER_H_
#define _LAYER_H_

#include "activation.h"

#include <stddef.h>

typedef struct Layer Layer;


typedef void
(*LayerForward)(
    Layer * self
    , float * input);


typedef void
(*LayerBackward)(
    Layer * self
    , float * output_gradient
    , float rate);


typedef void
(*LayerDelete)(Layer * self);


#define LAYER(T)((Layer *)T)


struct Layer
{
    LayerForward forward;
    LayerBackward backward;
    Activation activation;
    LayerDelete delete;

    size_t n_neurons;
    float * output;
};



void
layer_forward(
    Layer * self
    , float * input);


void
layer_backward(
    Layer * self
    , float * output_gradient
    , float rate);


void
layer_delete(Layer * self);

#endif
