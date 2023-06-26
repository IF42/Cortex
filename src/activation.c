#include "activation.h"

#include <math.h>


static float
__relu__(float x)
{
    return x > 0 ? x : 0;

}


static float 
__relu_derivative__(float x)
{
    return 0;
}


#define __sigmoid_exp__(x)(1 / (1 + exp(-x)))


static float 
__sigmoid__(float x)
{
    return __sigmoid_exp__(x);
}


static float
__sigmoid_derivative__(float x)
{
    return __sigmoid_exp__(x) * (1 - __sigmoid_exp__(x));
}



const Activation relu    = {__relu__, __relu_derivative__};
const Activation sigmoid = {__sigmoid__, __sigmoid_derivative__};
