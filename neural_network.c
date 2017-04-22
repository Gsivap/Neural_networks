#include<stdio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//for input file
#define MAXFLDS_INPUT 1000
#define MAXFLDSIZE_INPUT 32

//for one hot file
#define MAXFLDS_OUTPUT 100
#define MAXFLDSIZE_OUTPUT 32

#define MAXFLDS_WEIGHTS_1 1000

#define MAXFLDS_WEIGHTS_2 1000

#define HIDDEN_LAYER 30
#define INPUT_LAYER 784
#define CLASSES 10
#define BATCH_SIZE 1

#define DIM1 4
#define DIM2 3
#define DIM3 5
#define LEARNING_RATE 0.1

void matrix_multiply(int db1,int db2,double m_b[][db2],int da1,int da2,double m_a[][da2],double r[][da2])
{
    int i,j,k;
    double sum = 0;
    for (i = 0;i<db1;i++)
    {
        for(j = 0;j<da2;j++)
        {
            for(k = 0;k<da1;k++)
            {
                sum += m_b[i][k]*m_a[k][j];
            }
            r[i][j] = sum;
//            printf("%f\n",sum);
            sum = 0;
        }
    }
}
void matrix_e_multiply(int db1,int db2,double m_b[][db2],int da1,int da2,double m_a[][da2],double r[][da2])
{
    int i,j;
    for(i = 0;i < db1;i++)
    {
        for(j = 0;j < db2;j++)
        {
            r[i][j] = m_b[i][j] * m_a[i][j];
//            printf("element_wise--%f--%f--%f\n",r[i][j],m_a[i][j],m_b[i][j]);
        }
    }
}
void matrix_add(int db1,int db2,double m_b[][db2],int da1,int da2,double m_a[][da2],double r[][da2])
{
    int i,j;
    for(i = 0;i < db1;i++)
    {
        for(j = 0;j < db2;j++)
        {
            r[i][j] = m_b[i][j] + m_a[i][j];
//            printf("add--%f--%f--%f\n",r[i][j],m_a[i][j],m_b[i][j]);
        }
    }
}
void matrix_subtract(int db1,int db2,double m_b[][db2],int da1,int da2,double m_a[][da2],double r[][da2])
{
    int i,j;
    for(i = 0;i < db1;i++)
    {
        for(j = 0;j < db2;j++)
        {
            r[i][j] = m_b[i][j] - m_a[i][j];
//            printf("subtract--%f--%f--%f\n",r[i][j],m_a[i][j],m_b[i][j]);
        }
    }
}
void matrix_tranpose(int db1,int db2,double m_b[][db2],double r[][db1])
{
    int i,j;
    for(i = 0;i < db1;i++)
    {
        for(j = 0;j < db2;j++)
        {
            r[j][i] = m_b[i][j];
        }
    }
}
void print_matrix(int db1,int db2,double m_b[][db2])
{
    int i,j;
    for(i = 0;i < db1;i++)
    {
        for(j = 0;j < db2;j++)
        {
            printf("%f\n",m_b[i][j]);
        }
    }
}
void sigmoid_activation(int db1,int db2,double m_b[][db2],double r[][db2])
{
    int i,j;
    for(i = 0;i < db1;i++)
    {
        for(j = 0;j < db2;j++)
        {
            r[i][j] = 1/(1+exp(-m_b[i][j]));
        }
    }
}
void activation_derivative(int db1,int db2,double m_b[][db2],double r[][db2])
{
    int i,j;
    for(i = 0;i < db1;i++)
    {
        for(j = 0;j < db2;j++)
        {
            r[i][j] = (1/(1+exp(-m_b[i][j]))) * (1-(1/(1+exp(-m_b[i][j]))));
        }
    }
}
void fetch_matrix(int db1,int db2,double m_b[][db2],int fetch_index,double r[][1])
{
    int i,j;
        for(j = 0;j < db2;j++)
        {
            r[j][0] = m_b[fetch_index][j];
        }
}
void matrix_copy(int db1,int db2,double m_b[][db2],double r[][db2])
{
    int i,j;
    for(i = 0;i < db1;i++)
    {
        for(j = 0;j < db2;j++)
        {
            r[i][j] = m_b[i][j];
        }
    }
}
void matrix_create(int db1,int db2,double r[][db2],double learning_rate)
{
    int i,j;
    for(i = 0;i < db1;i++)
    {
        for(j = 0;j < db2;j++)
        {
            r[i][j] = learning_rate;
        }
    }
}
double reduce_sum(int db1,int db2,double m_b[][db2])
{
    int i,j;
    double sum = 0;
    for(i = 0;i < db1;i++)
    {
        for(j = 0;j < db2;j++)
        {
            sum += m_b[i][j];
        }
    }
    return sum;
}
void parse( char *record, char *delim, char arr[][MAXFLDSIZE_INPUT],int *fldcnt)
{
    char*p=strtok(record,delim);
    int fld=0;
    
    while(p)
    {
        strcpy(arr[fld],p);
        fld++;
        p=strtok('\0',delim);
    }
    *fldcnt=fld;
}
int main()
{
    double instance_loss = 0;
    static double input[10000][INPUT_LAYER] = {0};
    static double weights_i_h[INPUT_LAYER][HIDDEN_LAYER] = {0};
    static double weights_h_o[HIDDEN_LAYER][CLASSES] ={0};
    static double final_weights_h_o[CLASSES][HIDDEN_LAYER] = {0};
    static double final_weights_i_h[HIDDEN_LAYER][INPUT_LAYER] = {0};
    static double out[10000][CLASSES] = {0};
    static double instance_input[INPUT_LAYER][1] = {0};
    static double instance_input_T[1][INPUT_LAYER] = {0};
    static double instance_output[CLASSES][1] = {0};
    static double matrix_a[DIM2][DIM3] = {{1,2,3,1,2},{4,5,6,1,2},{7,8,9,1,2}};
    static double matrix_b[DIM1][DIM2] = {{10,11,12},{13,14,15},{16,17,18},{19,20,21}};
    static double matrix_c[DIM2][DIM2] = {{1,2,3},{4,5,6},{7,8,9}};
    static double matrix_d[DIM2][DIM2] = {{10,11,12},{13,14,15},{16,17,18}};
    static double result[DIM1][DIM3];
    static double result_1[DIM2][DIM2];
    static double result_3[DIM3][DIM2];
    static double result_4[DIM2][DIM3];
    
    static double input2layer1[HIDDEN_LAYER][1] = {0};
    static double activationlayer1[HIDDEN_LAYER][1] = {0};
    static double activationlayer1_T[1][HIDDEN_LAYER] = {0};
    static double input2layer2[CLASSES][1] = {0};
    static double activationlayer2[CLASSES][1] = {0};
    static double bias_1[HIDDEN_LAYER][1] = {0};
    static double bias_2[CLASSES][1] = {0};
    
    static double cost_deriv[CLASSES][1] = {0};
    static double outputact_deriv[CLASSES][1] = {0};
    static double error2[CLASSES][1] = {0};
    static double dbias_2[CLASSES][1] = {0};
    static double dw2[CLASSES][HIDDEN_LAYER] = {0};
    static double error1[HIDDEN_LAYER][1] = {0};
    static double dw1[HIDDEN_LAYER][INPUT_LAYER] = {0};
    static double dbias_1[HIDDEN_LAYER][1] = {0};
    
    static double learning_rate_w1[HIDDEN_LAYER][INPUT_LAYER] = {0};
    static double learning_rate_w2[CLASSES][HIDDEN_LAYER] = {0};
    static double intermediate_w1[HIDDEN_LAYER][INPUT_LAYER] = {0};
    static double intermediate_w2[CLASSES][HIDDEN_LAYER] = {0};
    
    static double learning_rate_b1[HIDDEN_LAYER][1] = {0};
    static double learning_rate_b2[CLASSES][1] = {0};
    static double intermediate_b1[HIDDEN_LAYER][1] = {0};
    static double intermediate_b2[CLASSES][1] = {0};
    
    //file_realted variables
    int count = 0;
    char tmp_input[4704]={0x0};
    char tmp_output[30]={0};
    char tmp_weights_1[18000]={0};
    char tmp_weights_2[720] = {0};
    int fldcnt=0;
    char arr_input[MAXFLDS_INPUT][MAXFLDSIZE_INPUT]={0x0};
    char arr_output[MAXFLDS_OUTPUT][MAXFLDSIZE_OUTPUT] = {0x0};
    char arr_weights_1[MAXFLDS_WEIGHTS_1][MAXFLDSIZE_OUTPUT] = {0x0};
    char arr_weights_2[MAXFLDS_WEIGHTS_2][MAXFLDSIZE_OUTPUT] = {0x0};
    int recordcnt=0;
    FILE *in=fopen("file.txt","r");
    FILE *output = fopen("onehot.txt","r");
    FILE *weights_1 = fopen("weights_1.txt","r");
    FILE *weights_2 = fopen("weights_2.txt","r");
    
    //file_read
    if(in==NULL)
    {
        perror("File open error");
        exit(EXIT_FAILURE);
    }
    while(fgets(tmp_input,sizeof(tmp_input),in)!=0) /* read a record */
    {
        int i=0;
        recordcnt++;
        parse(tmp_input," ",arr_input,&fldcnt);
        for(i=0;i<fldcnt-1;i++)
        {
            input[count][i] = (atof(arr_input[i]))/255;
            //printf("%f\n",input[i][count]);
        }
        count++;
    }
    fclose(in);
    
    //reading the output file
    recordcnt = 0;
    count = 0;
    fldcnt = 0;
    if(output==NULL)
    {
        perror("File open error");
        exit(EXIT_FAILURE);
    }
    while(fgets(tmp_output,sizeof(tmp_output),output)!=0) /* read a record */
    {
        int i=0;
        recordcnt++;
        printf("Record number: %d\n",recordcnt);
        parse(tmp_output," ",arr_output,&fldcnt);
        for(i=0;i<fldcnt-1;i++)
        {
            out[count][i] = atoi(arr_output[i]);
        }
        count++;
    }
    fclose(output);
    recordcnt = 0;
    count = 0;
    fldcnt = 0;
    if(weights_1==NULL)
    {
        perror("File open error");
        exit(EXIT_FAILURE);
    }
    while(fgets(tmp_weights_1,sizeof(tmp_weights_1),weights_1)!=0) /* read a record */
    {
        int i=0;
        recordcnt++;
        parse(tmp_weights_1," ",arr_weights_1,&fldcnt);
        for(i=0;i<fldcnt-1;i++)
        {
            weights_i_h[i][count] = atof(arr_weights_1[i]);
        }
        count++;
    }
    fclose(weights_1);
    matrix_tranpose(INPUT_LAYER,HIDDEN_LAYER,weights_i_h,final_weights_i_h);
    recordcnt = 0;
    count = 0;
    fldcnt = 0;
    if(weights_2==NULL)
    {
        perror("File open error");
        exit(EXIT_FAILURE);
    }
    while(fgets(tmp_weights_2,sizeof(tmp_weights_2),weights_2)!=0) /* read a record */
    {
        int i=0;
        recordcnt++;
        printf("Record number: %d\n",recordcnt);
        parse(tmp_weights_2," ",arr_weights_2,&fldcnt);
        for(i=0;i<fldcnt-1;i++)
        {
            weights_h_o[i][count] = atof(arr_weights_2[i]);
            printf("%d----%lf\n",i,weights_h_o[count][i]);
        }
        count++;
    }
    fclose(weights_2);
    matrix_tranpose(HIDDEN_LAYER,CLASSES,weights_h_o,final_weights_h_o);

    matrix_multiply(DIM1,DIM2,matrix_b,DIM2,DIM3,matrix_a,result);
    printf("matrix_multiply\n");
    print_matrix(DIM1,DIM3,result);
    matrix_e_multiply(DIM2,DIM2,matrix_d,DIM2,DIM2,matrix_c,result_1);
    printf("element_wise_multiply\n");
    print_matrix(DIM2,DIM2,result_1);
    matrix_add(DIM2,DIM2,matrix_d,DIM2,DIM2,matrix_c,result_1);
    printf("matrix_add\n");
    print_matrix(DIM2,DIM2,result_1);
    matrix_subtract(DIM2,DIM2,matrix_d,DIM2,DIM2,matrix_c,result_1);
    printf("matrix_subtract\n");
    print_matrix(DIM2,DIM2,result_1);
    matrix_tranpose(DIM2,DIM3,matrix_a,result_3);
    printf("matrix_tranpose\n");
    print_matrix(DIM3,DIM2,result_3);
    sigmoid_activation(DIM2,DIM3,matrix_a,result_4);
    printf("sigmoid_activation\n");
    print_matrix(DIM2,DIM3,result_4);
    activation_derivative(DIM2,DIM3,matrix_a,result_4);
    printf("acitvation_derivative\n");
    print_matrix(DIM2,DIM3,result_4);
    printf("---------------------------------weights_1---------------------------------\n");
//    print_matrix(HIDDEN_LAYER,INPUT_LAYER,final_weights_i_h);
    printf("---------------------------------weights_2---------------------------------\n");
//    print_matrix(CLASSES,HIDDEN_LAYER,final_weights_h_o);
    printf("---------------------------------input---------------------------------\n");
//    print_matrix(10000,INPUT_LAYER,input);
    printf("---------------------------------output---------------------------------\n");
//    print_matrix(10000,CLASSES,out);
    printf("---------------------------------fetching---------------------------------\n");
    for(int j = 0;j<20;j++)
    {
    for(int i = 0;i<10000;i++)
    {
    fetch_matrix(10000,INPUT_LAYER,input,i,instance_input);
    matrix_multiply(HIDDEN_LAYER,INPUT_LAYER,final_weights_i_h,INPUT_LAYER,1,instance_input,input2layer1);
    matrix_add(HIDDEN_LAYER,1,input2layer1,HIDDEN_LAYER,1,bias_1,input2layer1);
    sigmoid_activation(HIDDEN_LAYER,1,input2layer1,activationlayer1);
    matrix_multiply(CLASSES,HIDDEN_LAYER,final_weights_h_o,HIDDEN_LAYER,1,activationlayer1,input2layer2);
    matrix_add(CLASSES,1,input2layer2,CLASSES,1,bias_2,input2layer2);
    sigmoid_activation(CLASSES,1,input2layer2,activationlayer2);
    //forward pass
    
    fetch_matrix(10000,CLASSES,out,i,instance_output);
    matrix_subtract(CLASSES,1,activationlayer2,CLASSES,1,instance_output,cost_deriv);
    activation_derivative(CLASSES,1,input2layer2,outputact_deriv);
    matrix_e_multiply(CLASSES,1,cost_deriv,CLASSES,1,outputact_deriv,error2);
    matrix_copy(CLASSES,1,error2,dbias_2);
    matrix_tranpose(HIDDEN_LAYER,1,activationlayer1,activationlayer1_T);
    matrix_multiply(CLASSES,1,error2,1,HIDDEN_LAYER,activationlayer1_T,dw2);
    matrix_multiply(HIDDEN_LAYER,CLASSES,weights_h_o,CLASSES,1,error2,error1);
    activation_derivative(HIDDEN_LAYER,1,input2layer1,input2layer1);
    matrix_e_multiply(HIDDEN_LAYER,1,input2layer1,HIDDEN_LAYER,1,error1,error1);
    matrix_tranpose(INPUT_LAYER,1,instance_input,instance_input_T);
    matrix_multiply(HIDDEN_LAYER,1,error1,1,INPUT_LAYER,instance_input_T,dw1);
    matrix_copy(HIDDEN_LAYER,1,error1,dbias_1);
    
    matrix_create(HIDDEN_LAYER,INPUT_LAYER,learning_rate_w1,LEARNING_RATE);
    matrix_e_multiply(HIDDEN_LAYER,INPUT_LAYER,learning_rate_w1,HIDDEN_LAYER,INPUT_LAYER,dw1,intermediate_w1);
    matrix_subtract(HIDDEN_LAYER,INPUT_LAYER,final_weights_i_h,HIDDEN_LAYER,INPUT_LAYER,intermediate_w1,final_weights_i_h);
    
    matrix_create(CLASSES,HIDDEN_LAYER,learning_rate_w2,LEARNING_RATE);
    matrix_e_multiply(CLASSES,HIDDEN_LAYER,learning_rate_w2,CLASSES,HIDDEN_LAYER,dw2,intermediate_w2);
    matrix_subtract(CLASSES,HIDDEN_LAYER,final_weights_h_o,CLASSES,HIDDEN_LAYER,intermediate_w2,final_weights_h_o);
    
    matrix_create(HIDDEN_LAYER,1,learning_rate_b1,LEARNING_RATE);
    matrix_e_multiply(HIDDEN_LAYER,1,learning_rate_b1,HIDDEN_LAYER,1,dbias_1,intermediate_b1);
    matrix_subtract(HIDDEN_LAYER,1,bias_1,HIDDEN_LAYER,1,intermediate_b1,bias_1);
    
    matrix_create(CLASSES,1,learning_rate_b2,LEARNING_RATE);
    matrix_e_multiply(CLASSES,1,learning_rate_b2,CLASSES,1,dbias_2,intermediate_b2);
    matrix_subtract(CLASSES,1,bias_2,CLASSES,1,intermediate_b2,bias_2);
    
    matrix_subtract(CLASSES,1,activationlayer2,CLASSES,1,instance_output,activationlayer2);
    matrix_e_multiply(CLASSES,1,activationlayer2,CLASSES,1,activationlayer2,activationlayer2);
    
//    print_matrix(CLASSES,1,activationlayer2);
    instance_loss += reduce_sum(CLASSES,1,activationlayer2);
    }
        printf("loss:%lf\n",(instance_loss));
        instance_loss = 0;
    }
    return 0;
}
