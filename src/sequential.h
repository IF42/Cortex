#ifndef _SEQUENTIAL_H_
#define _SEQUENTIAL_H_

#include "model.h"
#include "layer.h"

#include <stddef.h>


typedef struct
{
    Model super;

    size_t n_layers;
    Layer * layers[];
}Sequential;


Sequential *
sequential_new(
    size_t n_layers
    , Layer * layers[n_layers]);


#endif
