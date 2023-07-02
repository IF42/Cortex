#include "activation.h"

#include <math.h>


static float 
__act_linear__(float x)
{
    return x;
}


static float
__prime_linear__(float)
{
    return 1.0;
}


const Activation Linear = 
{
    __act_linear__
    , __prime_linear__
};


static float
__act_sigmoid__(float x)
{
    return 1.0 / (1.0 + exp(-x));
}


static float
__prime_sigmoid__(float x)
{
    float sig = __act_sigmoid__(x);

    return sig * (1.0 - sig);
}


const Activation Sigmoid = 
{
    __act_sigmoid__
    , __prime_sigmoid__
};


static float 
__act_relu__(float x)
{
    return fmaxf(0, x);
}



static float 
__prime_relu__(float x)
{
    return x > 0 ? 1 : 0; 
}


const Activation ReLU = 
{
    __act_relu__
    , __prime_relu__
};


static float
__prime_tanh__(float x)
{
    return powf(1.0 / coshf(x), 2);
}


const Activation TanH = 
{   
    tanhf
    , __prime_tanh__
};

