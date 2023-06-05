#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define NUM_ELE 1000
#define MAX_TAM 200
#define MIN_TAM 10
#define MAX_PRI 100
#define MIN_PRI 10

void gerarnums(){
    srand(time(NULL));
    FILE * arq = fopen("elementos.txt", "w");
    for(int i = 0; i < NUM_ELE;i++){

        fprintf(arq, "%d ", MIN_TAM + rand() % (MAX_TAM+1-MIN_TAM));
        fprintf(arq, "%d\n", MIN_PRI + rand() % (MAX_PRI - MIN_PRI+1));
    }
    fclose(arq);
}

int main(){
    gerarnums();
    return 0;
}