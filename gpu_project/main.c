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
    int input_layer = 3;
    int hidden_layer = 4;
    int classes = 3;
    int batch_size = 5;
    double *input;
    double *weights_i_h;
    double *weights_h_o;
    double *output;
    double *hidden_unit;
    
    input = (double*)malloc(batch_size * input_layer * sizeof(double));
    weights_i_h = (double*)malloc(input_layer * hidden_layer * sizeof(double));
    weights_h_o = (double*)malloc(hidden_layer * classes * sizeof(double));
    hidden_unit = (double*)malloc(batch_size * hidden_layer * sizeof(double));
    output = (double*)malloc(batch_size * classes * sizeof(double));
    
//    for (i =0;i<batch_size;i++)
//    {
//        for(j = 0;j<input_layer;j++)
//            input[j+batch_size * i] = j+batch_size * i;
//    }
    weight_initialize(input, batch_size, input_layer, 0.1, 0);
    weight_initialize(weights_i_h, input_layer,hidden_layer,0.1, 0);
//  weight_initialize(output,hidden_layer,classes,0.1,0);
    weight_initialize(weights_h_o,hidden_layer,classes,0.1,0);
//    weight_initialize(weights_h_o, classes,hidden_layer, 0.1, 0);
//    zero_intializer(weights_i_h,input_layer,hidden_layer);
    
    matrix_multiply(input,weights_i_h,hidden_unit,batch_size,input_layer,input_layer,hidden_layer);
    sigmoid_activation(hidden_unit,batch_size,hidden_layer);
    matrix_multiply(hidden_unit,weights_h_o,output,batch_size,hidden_layer,hidden_layer,classes);
    print_matrix(input,input_layer,batch_size);
    printf("------\n");
    print_matrix(weights_i_h,input_layer,hidden_layer);
    printf("------\n");
    print_matrix(hidden_unit,batch_size,hidden_layer);
    printf("------\n");
    print_matrix(output,batch_size,classes);
//    print_matrix(weights_h_o,hidden_layer,classes);
    return 0;
}
