#ifndef _LAYER_H_
#define _LAYER_H_

#include "activation.h"


typedef struct Layer Layer;

typedef float *
(*LayerForwardCallback)(Layer *, float *);


typedef float *
(*LayerBackwardCallback)(Layer *, float, float *, float *);


typedef void
(*LayerBackward_Ptr_Callback)(Layer *, float, float **, float **);




typedef void
(*LayerDeleteCallback)(Layer *);


struct Layer
{
    LayerForwardCallback forward;
    LayerBackwardCallback backward;
    LayerDeleteCallback delete;

    Activation activation;

    float * output;
    float * gradient;
};


float *
layer_forward(
    Layer * self
    , float * X);


float *
layer_backward(
    Layer * self
    , float rate
    , float * y
    , float * gradient);


void
layer_delete(Layer * self);


#endif



