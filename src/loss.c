#include "loss.h"

#include <math.h>



float
mse(size_t length, float * y, float * labels)
{
    float error = 0;

    for(size_t i = 0; i < length; i++)
        error += pow(labels[i] - y[i], 2);

    return error/length;
}
