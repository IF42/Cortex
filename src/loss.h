#ifndef _LOSS_H_
#define _LOSS_H_


#include <stddef.h>


typedef struct
{
    float (*error)(size_t, float *, float *);
    float (*error_prime)(size_t, float*, float*);
}Loss;


extern const Loss mse;

#endif
