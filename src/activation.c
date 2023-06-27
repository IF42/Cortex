#include "activation.h"

#include <math.h>


static float
__relu__(float x)
{
    return x > 0.0f ? x : 0.0f;

}


static float 
__relu_derivative__(float x)
{
    return 0.0f;
}


#define __sigmoid_exp__(x)(1.0f / (1.0f + exp(-x)))


static float 
__sigmoid__(float x)
{
    return __sigmoid_exp__(x);
}


static float
__sigmoid_derivative__(float x)
{
    return __sigmoid_exp__(x) * (1.0f - __sigmoid_exp__(x));
}



const Activation relu    = {__relu__, __relu_derivative__};
const Activation sigmoid = {__sigmoid__, __sigmoid_derivative__};
