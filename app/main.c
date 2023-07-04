#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "../src/loss.h"
#include "../src/dense.h"


#define LAYER_SIZE (sizeof(struct _stack) / sizeof(void*))


typedef struct
{
    Loss loss;

    union
    {
        struct _stack
        {
            Dense * l1;
            Dense * l2;
            Dense * l3;
        }_stack;

        Layer * iterator[LAYER_SIZE];
    };
}Model;

#define Model(...)(Model){.loss=MSE, {._stack = __VA_ARGS__}}


static float *
predict(Model * self, float * X)
{
    float * output = X; 

    for(size_t i = 0; i < LAYER_SIZE; i++)
        output = layer_forward(self->iterator[i], output);

    return output;
}


static void
delete(Model * self)
{
    for(size_t i = 0; i < LAYER_SIZE; i++)
        layer_delete(self->iterator[i]);
}


int
main(void)
{
    float X[][2] = {{0,0}, {0, 1}, {1, 0}, {1, 1}};
    float y[]    = {0, 1, 1, 0};

    srand(time(NULL));

    Model model = 
        Model(
            {dense_new(2, 2, TanH)
            , dense_new(2, 2, TanH)
            , dense_new(2, 1, TanH)});
 
    printf("w1:%f, w2: %f, b: %f\n"
        , model._stack.l1->weight[0], model._stack.l1->weight[1], model._stack.l1->bias[0]);

    size_t epochs = 100000;
    float rate    = 0.01;

    for (size_t j = 0; j < epochs; j++) 
    {
        float loss = 0.0;
        
        for (size_t i = 0; i < 4; i++) 
        {
            // forward propagace
            float * predicted = predict(&model, X[i]); 

            // Výpočet loss
            loss += model.loss.accuracy(y[i], predicted[0]);
            
            // Backward propagace
            float output_gradient = model.loss.prime(y[i], predicted[0]);
            float * gradient      = &output_gradient;
            
            for(size_t k = LAYER_SIZE; k > 1; k--)
                gradient = layer_backward(model.iterator[k-1], rate, model.iterator[k-2]->output, gradient);

            gradient = layer_backward(model.iterator[0], rate, X[i], gradient);
        }
        
        if((j % 1000) == 0)
        {
            printf("Epoch: %zu, w1:%f, w2: %f, b: %f, Loss: %.4f\n"
                , j, model._stack.l1->weight[0], model._stack.l1->weight[1], model._stack.l1->bias[0], loss/4);
        }
    }
  

    for(size_t i = 0; i < 4; i++)
    {
        float * prediction = predict(&model, X[i]);
        printf("%d & %d = %f\n", (int) X[i][0], (int) X[i][1], prediction[0]);
    }

    delete(&model);

    printf("Program exit...\n");

    return EXIT_SUCCESS;
}





