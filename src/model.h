#ifndef _MODEL_H_
#define _MODEL_H_ 

#include <stddef.h>
#include <stdio.h>


typedef struct Model Model;


typedef void
(*ModelSave)(
    Model * self
    , FILE * stream);


typedef void
(*ModelDelete)(Model * self);


typedef void
(*ModelFit)(
    Model * self
    , size_t length
    , float * inputs);


struct Model
{
    ModelSave save;
    ModelFit fit;
    ModelDelete delete;
};


void
model_save(
    Model * self
    , FILE * stream);


void
model_fit(
    Model * self
    , size_t length
    , float * inputs);


void
model_delete(Model * self);


#endif
