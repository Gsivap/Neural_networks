

#include <stdio.h>
#include <stdlib.h>

double *matrix_a;
double *matrix_b;
double *matrix_c;


void matrix_square(double * matrix_a,double * matrix_c,int dim1,int dim2);
void populate_matrix(double *matrix,int dim1,int dim2);
void print_matrix(double *matrix,int dim1,int dim2);

void main()
{


int dim_a_1 = 3,dim_a_2 = 4;

matrix_a = (double*)malloc(dim_a_1 * dim_a_2 * sizeof(double));
matrix_b = (double*)malloc(dim_a_1 * dim_a_2 * sizeof(double));
matrix_c = (double*)malloc(dim_a_1 * dim_a_2 * sizeof(double));

populate_matrix( matrix_a,dim_a_1,dim_a_2);
populate_matrix(matrix_b,dim_a_1,dim_a_2);
matrix_square( matrix_a,matrix_c, dim_a_1,dim_a_2);


print_matrix(matrix_c,dim_a_1,dim_a_2);

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
/*
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
*/

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



