#include <stdio.h>
#include <stdlib.h>
#include <math.h>


float input[][2] = {{0,0}, {0,1}, {1,0}, {1,1}};
float output[][1] = {{0}, {0}, {0}, {1}};

#define SIZE sizeof(input)/sizeof(input[0])


float 
sigmoid(float x)
{
    return 1/(1 + expf(-x));
}

float 
relu(float x)
{
    if(x > 0)
        return x;
    else
        return 0;
}


float 
forward(float in1, float in2, float w1, float w2, float b)
{
    return sigmoid((w1*in1) + (w2 * in2) + b);
}


float
loss(float w1, float w2, float b)
{
    float error = 0;

    for(size_t i = 0; i < SIZE; i++)
        error += powf(output[i][0] - forward(input[i][0], input[i][1], w1, w2, b), 2);

    return error/SIZE;
}


int
main(void)
{   
    srand(69);
    
    float w1 = (float) rand() / (float)RAND_MAX;
    float w2 = (float) rand() / (float)RAND_MAX;
    float b  = (float) rand() / (float)RAND_MAX;

    printf("w1: %f, w2: %f, b:%f, loss: %f\n", w1, w2, b, loss(w1, w2, b)); 

    float delta = 0.00001;
    float rate  = 1;

    for(size_t i = 0; i < 3000000; i ++)
    {
        float error = loss(w1, w2, b);
 
        float dw1 = (loss(w1+delta, w2, b) - error) / delta;
        float dw2 = (loss(w1, w2+delta, b) - error) / delta;
        float db  = (loss(w1, w2, b+delta) - error) / delta;

        w1 -= rate * dw1;
        w2 -= rate * dw2;
        b  -= rate * db; 

        printf("w1: %f, w2: %f, b:%f, loss: %f\n", w1, w2, b, loss(w1, w2, b)); 
    }

    printf("\n");

    for(float i = 0; i < 2; i ++)
    {
        for(float j = 0; j < 2; j ++)
            printf("%d | %d = %f\n", (int) i, (int) j, forward(i, j, w1, w2, b));
    }

    return EXIT_SUCCESS;
}




