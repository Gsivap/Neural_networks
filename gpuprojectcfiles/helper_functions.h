#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

void populate_matrix(double *matrix,int dim1,int dim2);
void print_matrix(double *matrix,int dim1,int dim2);
void matrix_multiply(double *matrix_a,double *matrix_b,double *matrix_c,int dim_a_1,int dim_a_2,int dim_b_1,int dim_b_2);
void matrix_transpose(double * matrix_a,double * matrix_b,int dim1,int dim2);
void matrix_subtract(double * matrix_a,double * matrix_b,double * matrix_c,int dim1,int dim2);
void matrix_add(double * matrix_a,double * matrix_b,double * matrix_c,int dim1,int dim2);
void matrix_e_multiply(double * matrix_a,double * matrix_b,double * matrix_c,int dim1,int dim2);
void matrix_divide(double * matrix_a,double * matrix_b,double * matrix_c,int dim1,int dim2);
void matrix_square(double * matrix_a,double* matrix_c,int dim1,int dim2);
void weight_initialize(double *weight,int dim1,int dim2);
double * norm_matrix(double *matrix,int dim1,int dim2,int axis);
void zero_initializer(double *matrix,int dim1,int dim2);
void sigmoid_activation(double *matrix,double*activation,int dim1,int dim2);
void relu_activation(double *matrix,int dim1,int dim2);
double max(double a,double b);
void activation_derivative( double * activation,double * derivative, int dim1 , int dim2);

#endif
