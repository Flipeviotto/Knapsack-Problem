#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>

#define MAX_CAP 500
#define NUM_ELE 100

struct Itens{
    int ItemTam;
    int ItemPri;
    long double ItemFat;
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
        if((vet+i)->ItemQuant>0)
            printf("tam.%d   pre.%d   fat.%Lf   qtd.%d\n",(vet+i)->ItemTam,(vet+i)->ItemPri, (vet+i)->ItemFat, (vet+i)->ItemQuant);
    }
}

void CalculaFator(struct Itens * vet){
    for(int i=0;i<NUM_ELE;i++)
        (vet+i)->ItemFat =(long double) (vet+i)->ItemPri/(vet+i)->ItemTam;
}

void OrdenaFator(struct Itens * vet){
    struct Itens aux;
    for(int i=NUM_ELE-2; i>=0;i--){
        for(int j=0; j<=i;j++){
            if((vet+j)->ItemFat<(vet+j+1)->ItemFat){
                aux = *(vet+j);
                *(vet+j) = *(vet+j+1);
                *(vet+j+1) = aux;
            }
        }
    }
}

void EncherMochila(struct Itens * vet, int * espaco, int posicao){
    for(int i=posicao;i<NUM_ELE;i++){
        while((vet+i)->ItemTam <= *espaco){
            (vet+i)->ItemQuant++;
            *espaco -= (vet+i)->ItemTam;
        }
    }
}

void SomaPrioridade(struct Itens * vet, int * soma){
    *soma = 0;
    for(int i=0;i<NUM_ELE;i++){
        if((vet+i)->ItemQuant>0)
            *soma += ((vet+i)->ItemQuant * (vet+i)->ItemPri);
    }
}

void CopyToBetter(struct Itens * vet,struct Itens * Better){
    for(int i=0;i<NUM_ELE;i++){
        *(Better+i) = *(vet+i);
    }
}

int BuscaNaoNulo(struct Itens * vet){
    for(int i=NUM_ELE-1;i>=0;i--){
        if((vet+i)->ItemQuant > 0){
            return i;
        }
    }
    return -1;
}

void Podar(struct Itens * vet, int posicao, int * espaco){
    *espaco += ((vet+posicao)->ItemQuant * (vet+posicao)->ItemTam);
    (vet+posicao)->ItemQuant = 0;
}


int main(){
    struct timeval start, end;
    gettimeofday(&start, NULL);

    struct dados inf;
    inf.espaco = MAX_CAP;

    struct Itens * vet = malloc(NUM_ELE * sizeof(struct Itens));
    struct Itens * Better = malloc(NUM_ELE * sizeof (struct Itens));
    if(vet==NULL || Better==NULL){
        printf("deu erro na alocacao");
        exit(1);
    }

    IniciaVetor(vet);

    OrdenaFator(vet);
    CalculaFator(vet);
    EncherMochila(vet,&inf.espaco,0);
    CopyToBetter(vet,Better);
    SomaPrioridade(vet, &inf.melhorsolucao);

    while(1){

        int posicao = BuscaNaoNulo(vet);

        if(posicao==-1){
            printf("\nMelhor solucao: %d\n\n",inf.melhorsolucao);
            break;
        }

        if(posicao==NUM_ELE-1){
            int soma;
            SomaPrioridade(vet, &soma);
            if(soma>inf.melhorsolucao){
                inf.melhorsolucao = soma;
                CopyToBetter(vet,Better);
            }
            Podar(vet,posicao,&inf.espaco);
        }
        else{
            int soma;
            SomaPrioridade(vet,&soma);
            long double f;
            f = (long double) soma - (vet+posicao)->ItemPri + (vet+posicao+1)->ItemFat * (inf.espaco+(vet+posicao)->ItemTam);
            int limitante = ceil((double)f);

            if(limitante > soma){
                (vet+posicao)->ItemQuant--;
                inf.espaco += (vet+posicao)->ItemTam;
                EncherMochila(vet,&inf.espaco,posicao+1);
                SomaPrioridade(vet,&soma);
                if(soma>inf.melhorsolucao){
                    CopyToBetter(vet,Better);
                    inf.melhorsolucao = soma;
                }
            }
            else{
                Podar(vet,posicao,&inf.espaco);
            }
        }
    }

    gettimeofday(&end, NULL);

    long seconds = (end.tv_sec - start.tv_sec);
    long micro = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);

    double tempo = (double) micro/1000000;
    printf("tempo: %f segundos\n", tempo);

    FILE *arq = fopen("BB.txt", "w");
    fprintf(arq,"%lf\n",tempo);
    fclose(arq);

    free(Better);
    free(vet);

    return 0;
}