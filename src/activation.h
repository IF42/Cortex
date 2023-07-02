#ifndef _ACTIVATION_H_
#define _ACTIVATION_H_


typedef struct
{
    float (*act)(float);
    float (*prime)(float);
}Activation;


extern const Activation Linear;
extern const Activation Sigmoid;
extern const Activation ReLU;
extern const Activation TanH;

#endif
