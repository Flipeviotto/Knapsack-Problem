#include <stdio.h>

void soma(FILE * arq){
    double num;
    double soma = 0;
    double x =0;
    while(1){
        fscanf(arq,"%lf",&num);

        if(feof(arq)){
            break;
        }
        soma += num;
        x++;
    }
    printf("%lf\n\n",soma/x);
}


int main(){
    FILE * arq = fopen("MOT.txt", "r");
    printf("mot: ");
    soma(arq);
    fclose(arq);

    FILE * arq2 = fopen("MOP.txt", "r");
    printf("mop: ");
    soma(arq2);
    fclose(arq2);

    FILE * arq1 = fopen("MOPT.txt", "r");
    printf("mopt: ");
    soma(arq1);
    fclose(arq1);

    FILE * arq4 = fopen("BB.txt", "r");
    printf("BB: ");
    soma(arq4);
    fclose(arq4);

    FILE * arq5 = fopen("BBRD.txt", "r");
    printf("BBRD: ");
    soma(arq5);
    fclose(arq5);

    return 0;
}