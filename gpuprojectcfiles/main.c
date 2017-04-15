//helper functions
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "helper_functions.h"

//int main(int argc, const char * argv[]) {
//    double *matrix_a;
//    double *matrix_b;
//    double *matrix_c;
//    double *norm_result;
//    int dim_a_1 = 5,dim_a_2 = 5;
//    int dim_b_1 = 5,dim_b_2 = 5;
//    //int i = 0,j = 0;
//    //int count = 0;
//    matrix_a = (double*)malloc(dim_a_1 * dim_a_2 * sizeof(double));
//    matrix_b = (double*)malloc(dim_b_1 * dim_b_2 * sizeof(double));
//    matrix_c = (double*)malloc(dim_b_1 * dim_a_2 * sizeof(double));
//    populate_matrix(matrix_a,dim_a_1,dim_a_2);
//    populate_matrix(matrix_b, dim_a_1, dim_a_2);
//    //populate_matrix(matrix_b,dim_b_1,dim_b_2);
//    //weight_initialize(matrix_a,dim_a_1,dim_a_2,0.1,0);
//    //weight_initialize(matrix_b, dim_b_1, dim_b_2, 0.1, 0);
//    matrix_multiply(matrix_a, matrix_b, matrix_c,dim_a_1, dim_a_2, dim_b_1, dim_b_2);
//    matrix_e_multiply(matrix_a, matrix_b,matrix_c, dim_a_1, dim_a_2);
//    //print_matrix(matrix_b,dim_a_1,dim_a_2);
//    print_matrix(matrix_c,dim_a_1,dim_a_2);
//    return 0;
//}
int main(int argc,const char * argv[])
{
    int i,j;
    int input_layer = 50;
    int hidden_layer = 70;
    int classes = 10;
    int batch_size = 5;
    double *input;
    double *weights_i_h;
    double *weights_h_o;
    double *output;
    double *input2layer1;
    double *input2layer2;
    double *activationlayer1;
    double *activationlayer2;
    double *cost_deriv;
    double *outputact_deriv; 
    double *error1; 
    double *error2;
    double *dw2;
    double *dw1;
    double *w2transpose;
    double *w1transpose;
    double *acttrans1;
    

    double *inptrans;

    double o[classes][batch_size] ;
    double *out;
    out = &o;
    print_matrix(out,3,5);
    printf("------\n");

    double output_deriv[3][5];
     
    input = (double*)malloc(batch_size * input_layer * sizeof(double));
    weights_i_h = (double*)malloc(input_layer * hidden_layer * sizeof(double));
    weights_h_o = (double*)malloc(hidden_layer * classes * sizeof(double));
    input2layer1 = (double*)malloc(batch_size * hidden_layer * sizeof(double));
    activationlayer1 = (double*)malloc(batch_size * hidden_layer * sizeof(double));
    input2layer2 = (double*)malloc(batch_size * classes * sizeof(double));
    activationlayer2 = (double*)malloc(batch_size * classes * sizeof(double));
    outputact_deriv = (double*)malloc (batch_size * classes * sizeof(double));
    cost_deriv = (double*)malloc (batch_size * classes * sizeof(double));
    dw1 = (double*) malloc ( hidden_layer * input_layer * sizeof(double));
    dw2 =(double*) malloc ( classes * hidden_layer * sizeof(double));
    w2transpose = (double*)malloc(hidden_layer * classes * sizeof(double));
    inptrans = (double*)malloc(batch_size * input_layer * sizeof(double));
    acttrans1 = (double*)malloc(batch_size * hidden_layer * sizeof(double));
    error2 = (double*) malloc ( classes * batch_size * sizeof(double));
    error1 =(double*)malloc(batch_size * hidden_layer * sizeof(double));




//weights initialization
    
    weight_initialize(input, input_layer, batch_size);
    weight_initialize(weights_i_h, hidden_layer,input_layer);
    weight_initialize(weights_h_o,classes,hidden_layer);


// forward pass

    matrix_multiply(weights_i_h, input ,input2layer1,hidden_layer,input_layer,input_layer,batch_size);

    print_matrix(input2layer1,hidden_layer,batch_size);
    printf("------\n");
    sigmoid_activation(input2layer1,activationlayer1,hidden_layer,batch_size);
    
    print_matrix(activationlayer1,hidden_layer,batch_size);
    printf("------\n");

    matrix_multiply(weights_h_o,activationlayer1,input2layer2,classes,hidden_layer,hidden_layer,batch_size);

    print_matrix(input2layer2,classes,batch_size);
    printf("------\n");

    sigmoid_activation(input2layer2,activationlayer2,classes,batch_size); 



// backpropagation
    
    matrix_subtract( activationlayer2,out,cost_deriv,classes,batch_size);

    activation_derivative(input2layer2,outputact_deriv,classes,batch_size);
    matrix_e_multiply (cost_deriv,outputact_deriv,error2,classes,batch_size);

    matrix_transpose (activationlayer1,acttrans1,hidden_layer,batch_size);
    

    matrix_multiply ( error2, acttrans1,dw2, classes,batch_size,batch_size, hidden_layer);

    printf("dw2:\n");
    print_matrix( dw2, classes, hidden_layer);
   
    matrix_transpose (weights_h_o,w2transpose,classes,hidden_layer);

    matrix_multiply(w2transpose,error2,error1,hidden_layer,classes,classes,batch_size);

    matrix_e_multiply(error1,input2layer1,error1,hidden_layer,batch_size);

    matrix_transpose (input,inptrans,hidden_layer,input_layer);

    matrix_multiply ( error1,inptrans,dw1, hidden_layer,batch_size,batch_size, input_layer);
     printf("dw1:\n");

   print_matrix( dw1,hidden_layer,input_layer);
   
    return 0;
}
