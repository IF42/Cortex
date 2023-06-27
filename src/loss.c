#include "loss.h"


static float
__mse__(
    size_t length
    , float * prediction
    , float * desired_output)
{
    float error = 0;

    for(size_t i = 0; i < length; i++)
        error += pow(desired_output - predirction, 2);

    return error/length;
}


static float
__mse_prime__(
    size_t length
    , float * prediction
    , float * desired_output)
{
    float error = 0;

    for(size_t i = 0; i < length; i++)
        error += desired_output - prediction;

    return 2 * error / length; 
}


const Loss mse = 
{
    __mse__
    , __mse_prime__   
};

