#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>


#define MAX_CAP 500
#define NUM_ELE 1000

#define BILLION  1000000000.0

struct Itens{
    int ItemTam;
    int ItemPri;
    int ItemQuant;
};

struct dados{
    int espaco;
    int melhorsolucao;
};

void IniciaVetor(struct Itens * vet){
    FILE *arq = fopen("elementos.txt","r");
    for(int i=0;i<NUM_ELE;i++){
        fscanf(arq,"%d",&(vet+i)->ItemTam);
        fscanf(arq,"%d",&(vet+i)->ItemPri);
        (vet+i)->ItemQuant = 0;
    }
    fclose(arq);
}

void Escreve(struct Itens * vet){
    for(int i=0;i<NUM_ELE;i++){
        printf("tam.%d   pre.%d   qtd.%d\n",(vet+i)->ItemTam,(vet+i)->ItemPri, (vet+i)->ItemQuant);
    }
}

void OrdenaVet(struct Itens * vet){
    struct Itens aux;
    for(int i=NUM_ELE-2; i>=0;i--){
        for(int j=0; j<=i;j++){
            if((vet+j)->ItemTam>(vet+j+1)->ItemTam){
                aux = *(vet+j);
                *(vet+j) = *(vet+j+1);
                *(vet+j+1) = aux;
            }
        }
    }
}

void EncherMochila(struct Itens * vet, int * espaco){
    for(int i=0;i<NUM_ELE;i++){
        while((vet+i)->ItemTam <= *espaco){
            (vet+i)->ItemQuant++;
            *espaco -= (vet+i)->ItemTam;
        }
    }
}

void SomaPri(struct Itens * vet, int * soma){
    *soma = 0;
    for(int i=0;i<NUM_ELE;i++){
        if((vet+i)->ItemQuant>0)
            *soma += ((vet+i)->ItemQuant * (vet+i)->ItemPri);
    }
}

int main() {

    struct dados inf;
    inf.espaco = MAX_CAP;
    struct Itens *vet = malloc(NUM_ELE * sizeof(struct Itens));
    if(vet==NULL){
        printf("deu erro na alocacao");
        exit(1);
    }
    IniciaVetor(vet);

    struct timeval start, end;
    gettimeofday(&start, NULL);

    OrdenaVet(vet);
    EncherMochila(vet, &inf.espaco);

    SomaPri(vet, &inf.melhorsolucao);

    gettimeofday(&end, NULL);
    long seconds = (end.tv_sec - start.tv_sec);
    long micro = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);

    double tempo = (double) micro/1000000;
    printf("tempo: %f segundos\n", tempo);
    printf("melhor solucao %d\n",inf.melhorsolucao);

    FILE *arq = fopen("MOT.txt", "a");
    fprintf(arq,"%f\n",tempo);
    fclose(arq);


    free(vet);

    return 0;
}