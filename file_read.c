#include<stdio.h>

int main()
{
    FILE *fp;
    float temp;
    char buff[100];
    int rows = 100;
    int columns = 3;
    float x_train[rows][columns];
    fp = fopen("x_train.txt","r");
    for(int i = 0;i<rows;i++)
    {
        for(int j = 0;j<columns;j++)
        {
            //if(fscanf(fp,"%f",&temp)>0)
            fscanf(fp,"%f",&x_train[i][j]);
            printf("%f----%d\n",x_train[i][j],(j+3*i));
        }
    }
}
