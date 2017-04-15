#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "helper_functions.h"

double max(double a,double b)
{
    if(a>b)
    return a;
    else
    return b;
}

void populate_matrix(double *matrix,int dim1,int dim2)
{
    int i,j,count = 0;
    for(i=0;i<dim2;i++)
    {
        for(j = 0;j<dim1;j++)
        {
            count++;
            matrix[j+dim1*i] = count;
        }
    }
}
void print_matrix(double *matrix,int dim1,int dim2)
{
    int i,j;
    for(i=0;i<dim2;i++)
    {
        for(j = 0;j<dim1;j++)
        {
            printf("%f\n",matrix[j+dim1*i]);
        }
    }
}
void matrix_multiply(double *matrix_a,double *matrix_b,double *matrix_c,int dim_a_1,int dim_a_2,int dim_b_1,int dim_b_2)
{
    int i,j,k;
    double sum = 0;
    for (i = 0;i<dim_a_1;i++)
    {
        for(j = 0;j<dim_b_2;j++)
        {
            for(k = 0;k<dim_b_1;k++)
            {
//                sum += matrix_a[k+dim_a_2*i]*matrix_b[j+dim_b_2*k];
                sum += matrix_b[k+dim_b_1*j]*matrix_a[i+dim_a_1*k];
//                printf("\ninside_header--%f",sum);
            }
            matrix_c[i+dim_a_1*j] = sum;
            sum = 0;
        }
    }
}
void weight_initialize(double *weight,int dim1,int dim2)
{
    int i,j;
    double temp = 0;
    int count = 1;
    for (i=0;i<dim2;i++)
    {
        for(j = 0;j<dim1;j++)
        {
               

               weight[j+dim1*i] =  (double)rand()/RAND_MAX*2.0-1.0;
           
        }
    }
    
}
double * norm_matrix(double *matrix,int dim1,int dim2,int axis)
{
    int i,j;
    double *norm_vector;
    double temp_sum = 0;
    if(axis == 0)
    {
        norm_vector = (double*)malloc(dim1 * sizeof(double));
        for(i = 0;i<dim1;i++)
        {
            temp_sum = 0;
            for(j = 0;j<dim2;j++)
            {
                temp_sum = temp_sum + pow(matrix[j+dim1*i],2);
            }
            norm_vector[i] = sqrt(temp_sum);
        }
    }
    else
    {
        norm_vector  = (double*)malloc(dim2 * sizeof(double));
        for(i = 0;i<dim1;i++)
        {
            temp_sum = 0;
            for(j = 0;j<dim2;j++)
            {
                temp_sum = temp_sum + pow(matrix[i+dim1*j],2);
            }
            norm_vector[i] = sqrt(temp_sum);
        }
    }
    
    return norm_vector;
}
void zero_initializer(double *matrix,int dim1,int dim2)
{
    int i,j;
    for (i = 0;i<dim1;i++)
    {
        for(j = 0;j<dim2;j++)
        {
            matrix[j+dim1*j] = 0.0;
        }
    }
   
}
void sigmoid_activation(double *matrix,double *activation,int dim1,int dim2)
{
    int i,j;
    for(i = 0;i<dim2;i++)
    {
        for(j = 0;j<dim1;j++)
        {
            activation[j+dim1*i] = 1/(1+exp(-(matrix[j+dim1*i])));
        }
    }
}
void relu_activation(double *matrix,int dim1,int dim2)
{
    int i,j;
    int result = 0;
    for(i = 0;i<dim2;i++)
    {
        for(j = 0;j<dim1;j++)
        {
            result = max(0,(1-matrix[j+dim1*i]));
            matrix[j+dim1*i] =result;
        }
    }
}
void matrix_transpose(double * matrix_a,double * matrix_b,int dim1,int dim2)
{
    
    int i,j;
    
    for(i = 0; i < dim1 ; i++)
    {
        
        for(j = 0 ; j < dim2 ; j++)
        {
            matrix_b[i +j*dim1] = matrix_a[ i*dim2 +j];
        }
        
    }
    
}
void matrix_subtract(double * matrix_a,double * matrix_b,double * matrix_c,int dim1,int dim2)
{
    int i,j;
    
    for(i = 0; i < dim1 ; i++)
    {
        
        for(j = 0 ; j < dim2 ; j++)
        {
            matrix_c[ i*dim2 +j] = matrix_a[ i*dim2 +j] - matrix_b[ i*dim2 +j];
        }
    }
}

void matrix_add(double * matrix_a,double * matrix_b,double * matrix_c,int dim1,int dim2)
{
    int i,j;
    
    for(i = 0; i < dim1 ; i++)
    {
        
        for(j = 0 ; j < dim2 ; j++)
        {
            matrix_c[ i*dim2 +j] = matrix_a[ i*dim2 +j] + matrix_b[ i*dim2 +j];
        }
    }
}

void matrix_square(double * matrix_a,double* matrix_c,int dim1,int dim2)
{
    int i,j;
    
    for(i = 0; i < dim1 ; i++)
    {
        
        for(j = 0 ; j < dim2 ; j++)
        {
            matrix_c[ i*dim2 +j] = matrix_a[ i*dim2 +j] * matrix_a[ i*dim2 +j];
        }
    }
}
void matrix_e_multiply(double * matrix_a,double * matrix_b,double * matrix_c,int dim1,int dim2)
{
    int i,j;
    
    for(i = 0; i < dim1 ; i++)
    {
        
        for(j = 0 ; j < dim2 ; j++)
        {
            matrix_c[ i*dim2 +j] = matrix_a[ i*dim2 +j] * matrix_b[ i*dim2 +j];
        }
    }
}
void matrix_divide(double * matrix_a,double * matrix_b,double * matrix_c,int dim1,int dim2)
{
    int i,j;
    for(i = 0; i < dim1 ; i++)
    {
        
        for(j = 0 ; j < dim2 ; j++)
        {
            matrix_c[ i*dim2 +j] = matrix_a[ i*dim2 +j] / matrix_b[ i*dim2 +j];
        }
    }
}
void activation_derivative( double * activation,double * derivative, int dim1 , int dim2)
{
    int i,j;
    for(i = 0;i<dim2;i++)
    {
        for(j = 0;j<dim1;j++)
        {
            derivative[j+dim1*i] = (1/(1+exp(-(activation[j+dim1*i]))))*(1-1/(1+exp(-(activation[j+dim1*i]))));
        }
    }
}

