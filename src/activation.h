#ifndef _ACTIVATION_H_
#define _ACTIVATION_H_ 


typedef struct
{
    float (*act)(float);
    float (*prime)(float);
}Activation;


extern const Activation relu;
extern const Activation sigmoid;


#endif
