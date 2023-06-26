#ifndef _ACTIVATION_H_
#define _ACTIVATION_H_ 


typedef struct
{
    float (*activation)(float);
    float (*derivative)(float);
}Activation;


extern const Activation relu;
extern const Activation sigmoid;


#endif
