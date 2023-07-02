#ifndef _LOSS_H_
#define _LOSS_H_ 

typedef struct
{
    float (*accuracy)(float, float);
    float (*prime)(float, float);
}Loss;


extern const Loss MSE;


#endif
