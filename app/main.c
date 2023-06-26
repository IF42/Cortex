#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/loss.h"
#include "../src/dense.h"


typedef union
{
    struct
    {
        Dense * l1;
    }layers;

    Layer * iterator[1];
}Model;

#define Model(...) (Model){{__VA_ARGS__}}
#define SIZE(iterator)(sizeof(iterator)/sizeof(void*))


static inline void *
memdup(void * src, size_t len)
{
    void * dest = malloc(len);
    memcpy(dest, src, len);

    return dest;
}


static inline void
forward(Model * self, float * inputs)
{
    for(size_t i = 0; i < SIZE(self->iterator); i++)
    {
        if(i == 0)
            layer_forward(self->iterator[i], inputs);
        else
            layer_forward(self->iterator[i], self->iterator[i-1]->output);
    }
}

static inline float *
evaluate(Model * self, float * inputs)
{
    forward(self, inputs);

    return memdup(
            LAYER(self->layers.l1)->output
            , sizeof(float)*LAYER(self->layers.l1)->n_neurons);
}


static inline float
backward(Model * self, float rate, float * X, float * y)
{
    forward(self, X);

    float error = 
        mse(LAYER(self->layers.l1)->n_neurons
                , LAYER(self->layers.l1)->output
                , y);

    self->layers.l1->neurons[0]->weights[0] -= rate;
    self->layers.l1->neurons[0]->weights[1] -= rate;
    self->layers.l1->neurons[0]->bias -= rate;

    return error;
}


static inline void
show_output(size_t length, float * output)
{
    printf("{");

    for(size_t i = 0; i < length; i++)
        printf(i == 0 ? "%f" : ", %f", output[i]);
    
    printf("}");
}


int
main(void)
{
    /*
    ** prepare model
    */
    Model sequential = 
        Model(dense_new(2, 1, sigmoid));

    /*
    ** prepare test input
    */
    float X[][2] = {{0,0}, {0,1}, {1,0}, {1,1}};
    float y[][1] = {{0}, {1}, {1}, {1}};

    /*
    ** fit input data
    */
    
    /*
    ** show output layer
    */
    for(size_t i = 0; i < 3000; i++)
    {
        float *output = evaluate(&sequential, &X[1][0]);
        float error = backward(&sequential, 0.01, &X[1][0], &y[1][0]);

        show_output(1, output);
        printf(" loss: %f\n", error);

        free(output);

        if(error < 0.000001)
            break;
    }

    /*
    ** release resources
    */
    for(size_t i = 0; i < SIZE(sequential.iterator); i++)
        layer_delete(sequential.iterator[i]);

    printf("Program exit...\n");

    return EXIT_SUCCESS;
}



