#include<stdio.h>

int main()
{
    FILE *fp;
    float temp;
    char buff[100];
    fp = fopen("x_train.txt","r");
    for(int i=0;i<300;i++)
    {
        fscanf(fp,"%f",&temp);
        printf("%f",temp);
    }
}
