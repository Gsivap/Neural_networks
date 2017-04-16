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

void forward_pass(double *input,double *weights_i_h,double *weights_h_o,int input_layer,int hidden_layer,int classes,int batch_size);
int main(int argc,const char * argv[])
{
    int i,j;
    int input_layer = 10;
    int hidden_layer = 10;
    int classes = 1;
    int batch_size = 1;
    double *input;
    double *weights_i_h;
    double *weights_h_o;
    double *out;
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
    double *learning_rate_w1;
    double *learning_rate_w2;
    double *inptrans;
    double *input_test;
    
    //variables for reading file
    FILE *fp,*fp1;
    int x_rows = 100;
    int x_columns = input_layer;
    int y_rows = 100;
    int y_columns = classes;
    float x_train[x_rows][x_columns];
    float y_train[y_rows][y_columns];
    
    //overflow flags
    int x_overflow = 0;
    int temp = 0;
    
    //new_variables
    int num_of_iterations = 5000;
    float learning_rate = 0.01;
    double loss;
    
    //reading text file for training data
    fp = fopen("x_train.txt","r");
    for(int i = 0;i<x_rows;i++)
    {
        for(int j = 0;j<x_columns;j++)
        {
            fscanf(fp,"%f",&x_train[i][j]);
        }
    }
    
    //readin text file for training labels
    fp1 = fopen("y_train.txt","r");
    for (int i = 0;i<y_rows;i++)
    {
        for(int j = 0;j<y_columns;j++)
        {
            fscanf(fp1,"%f",&y_train[i][j]);
        }
    }
    
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
    learning_rate_w1 = (double*)malloc(hidden_layer * input_layer * sizeof(double));
    learning_rate_w2 = (double*)malloc(classes * hidden_layer * sizeof(double));
    out = (double*)malloc(classes * batch_size * sizeof(double));
    input_test = (double*)malloc(batch_size * input_layer * sizeof(double));




//weights initialization
    
//    weight_initialize(input, input_layer, batch_size);
    weight_initialize(weights_i_h, hidden_layer,input_layer);
    weight_initialize(weights_h_o,classes,hidden_layer);
    
//creating learning rate matrix
    matrix_create(learning_rate_w1,learning_rate,hidden_layer,input_layer);
    matrix_create(learning_rate_w2,learning_rate,classes,hidden_layer);
    
//printf("printing input matrix");
    printf("---input layer---\n");
//    print_matrix(input,input_layer,batch_size);
    printf("----weights_1--\n");
    print_matrix(weights_i_h,hidden_layer,input_layer);
    printf("---weights_2---\n");
    print_matrix(weights_h_o,classes,hidden_layer);
    
    printf("end of initialization");
    
for(int count = 0;count < num_of_iterations;count++)
{
    

// reading the batch_wise input data
    if((temp+batch_size) > x_rows)
    {
        x_overflow = 0;
        printf("\nx overflow detected!\n");
    }
    for(int data_row = temp;data_row<(batch_size+temp);data_row++)
    {
        for(int data_column = 0;data_column<input_layer;data_column++)
        {
            input[data_row*batch_size+data_column] = x_train[data_row][data_column];
        }
        x_overflow++;
        printf("\nx:%d\n",x_overflow);
    }
    

//reading batch_wise input labels
    for(int data_row = temp;data_row<(batch_size+temp);data_row++)
    {
        for(int data_column = 0;data_column<classes;data_column++)
        {
            out[data_row*batch_size+data_column] = y_train[data_row][data_column];
        }
    }
    
    temp = x_overflow;

// forward pass
    printf("\n------------------------ITERATION - %d-----------------------------------\n",count+1);
    matrix_multiply(weights_i_h, input ,input2layer1,hidden_layer,input_layer,input_layer,batch_size);

//    print_matrix(input2layer1,hidden_layer,batch_size);
//    printf("------\n");
    sigmoid_activation(input2layer1,activationlayer1,hidden_layer,batch_size);
    
//    print_matrix(activationlayer1,hidden_layer,batch_size);
//    printf("------\n");

    matrix_multiply(weights_h_o,activationlayer1,input2layer2,classes,hidden_layer,hidden_layer,batch_size);

//    print_matrix(input2layer2,classes,batch_size);
//    printf("------\n");

    sigmoid_activation(input2layer2,activationlayer2,classes,batch_size); 



// backpropagation
    
    matrix_subtract( activationlayer2,out,cost_deriv,classes,batch_size);

    activation_derivative(input2layer2,outputact_deriv,classes,batch_size);
    matrix_e_multiply (cost_deriv,outputact_deriv,error2,classes,batch_size);

    matrix_transpose (activationlayer1,acttrans1,hidden_layer,batch_size);
    

    matrix_multiply ( error2, acttrans1,dw2, classes,batch_size,batch_size, hidden_layer);

//    printf("dw2:\n");
//    print_matrix( dw2, classes, hidden_layer);
   
    matrix_transpose (weights_h_o,w2transpose,classes,hidden_layer);

    matrix_multiply(w2transpose,error2,error1,hidden_layer,classes,classes,batch_size);

    matrix_e_multiply(error1,input2layer1,error1,hidden_layer,batch_size);

    matrix_transpose (input,inptrans,hidden_layer,input_layer);

    matrix_multiply ( error1,inptrans,dw1, hidden_layer,batch_size,batch_size, input_layer);
//     printf("dw1:\n");

//   print_matrix( dw1,hidden_layer,input_layer);
    
    //updating w_1
    matrix_e_multiply(dw1,learning_rate_w1,dw1,hidden_layer,input_layer);
    matrix_subtract(weights_i_h,dw1,weights_i_h,hidden_layer,input_layer);
    
    //updating w_2
    matrix_e_multiply(dw2,learning_rate_w2,dw2,classes,hidden_layer);
    matrix_subtract(weights_h_o,dw2,weights_h_o,classes,hidden_layer);
    
    //loss calculation
    matrix_subtract(activationlayer2,out,activationlayer2,classes,batch_size);
    matrix_e_multiply(activationlayer2,activationlayer2,activationlayer2,classes,batch_size);
//    printf("\nfinal output matrix\n");
//    print_matrix(activationlayer2,classes,batch_size);
    loss = reduce_sum(activationlayer2,classes,batch_size);
    
    printf("\nlos:%lf\n",loss);

}
    //test_run
    input_test[0] = 0.95;
    input_test[1] = 0.21;
    input_test[2] = 0.29;
    input_test[3] = 0.12;
    input_test[4] = 0.15;
    input_test[5] = 0.34;
    input_test[6] = 0.23;
    input_test[7] = 0.16;
    input_test[8] = 0.22;
    input_test[9] = 0.15;
    input[9] = 0.87;
    matrix_multiply(weights_i_h, input ,input2layer1,hidden_layer,input_layer,input_layer,batch_size);
    sigmoid_activation(input2layer1,activationlayer1,hidden_layer,batch_size);
    matrix_multiply(weights_h_o,activationlayer1,input2layer2,classes,hidden_layer,hidden_layer,batch_size);
    sigmoid_activation(input2layer2,activationlayer2,classes,batch_size);
    print_matrix(input,input_layer,batch_size);
    print_matrix(activationlayer2,classes,batch_size);
    
    free(input);
    free(weights_i_h);
    free(weights_h_o);
    free(out);
    free(input2layer1);
    free(input2layer2);
    free(activationlayer1);
    free(activationlayer2);
    free(cost_deriv);
    free(outputact_deriv);
    free(error1);
    free(error2);
    free(dw2);
    free(dw1);
    free(w2transpose);
    free(w1transpose);
    free(acttrans1);
    free(learning_rate_w1);
    free(learning_rate_w2);
    free(inptrans);
    free(input_test);
 
    return 0;
}
