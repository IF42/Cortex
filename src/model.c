#include "model.h"


void
model_save(Model * self, FILE * stream)
{
    if(self->save != NULL && stream != NULL)
        self->save(self, stream);
}


void
model_fit(
    Model * self
    , size_t length
    , float * inputs)
{
    if(self->fit != NULL)
        self->fit(self, length, inputs);
}


void
model_delete(Model * self)
{
    if(self != NULL && self->delete != NULL)
        self->delete(self);
}
