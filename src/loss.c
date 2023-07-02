#include "loss.h"
#include <math.h>


static float
__mse__(
    float target
    , float predicted)
{
    return powf(target - predicted, 2); 
}


static float 
__mse_prime__(
    float target
    , float predicted)
{
    return 2.0 * (predicted - target);
}


const Loss MSE = 
{
    __mse__
    , __mse_prime__  
};
