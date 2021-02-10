// gcc main.c -o main -pthread
// ./main


#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define t 4                 // Número de threads a ser criadas
#define n 8                 // Número de trapézios
#define a 0.0               // Limite inferior
#define b 2.0               // Limite superior
int q[t];                   // Quantidade de trapézios em cada thread
float r[t];                 // Resultado de área de cada thread
float h = (b - a)/n;        // Largura de cada trapézio
float total;                // Área Total
pthread_t threads[t];       
void *thread_return;
int status;


// Retorna quantidade total de trapézios até o inicio da posição i
int sumT(int i){
    int total = 0;
    for(int j = 0; j < i; j++) total = total + q[i];
    return total;
}

// Retorna 1 quando i é inteiro e 0 quando não
int isInt(void * i){
    return 1;   //fazer
}

// Função f definida
float f(float x){
    return 5.0;
}

void * calculateArea(void * i){
    float localA = a + sumT((int)(size_t)i) * h;   
    float localB = q[(int)(size_t) i] * h + localA;  // b = q[i] * h + a
    float totalArea = 0;

    // Para cada trapézio, vamos calcular o h/2 *(f(limite inferior) + f(limite superior))
    for(int j = 0; j < q[(int)(size_t) i]; j++){
        float bottom = localA + j*h;    // Limite inferior
        float top = bottom + h;         // Limite superior

        totalArea = totalArea + h/2 * (f(bottom) + f(top));
    }

    // Agora que temos a área total dos trapézios dessa thread, 
    // adicionaremos no array de resultados
    r[(int)(size_t)i] = totalArea;

    pthread_exit(NULL); //finaliza execução da thread
}



int main(int argc, char * argv[]){
        

    // if(!isInt((void *)(size_t)(n/t))){
    if(0){
        // Caso o número de trapézios por thread seja decimal, 
        // teremos que mudar a distribuição de trapezios.
    }else{
        for(int i=0; i < t; i++) q[i] = n/t; // Completa o array q com o valor n/t
    }


    for (int i=0; i < t; i++){
        // cada thread i terá q[i] trapézios, assim, a distância entre o 'a' e o 'b'
        // local será a = x e b = q[i] * h + x
        printf("Processo principal criando thread %d\n", i);
        status = pthread_create(&threads[i], NULL, calculateArea, (void *)(size_t) i);

        if(status != 0){
            printf("Erro na criação da thread. Codigo de Erro: %d\n", status);
            return 1;
        }

    }

    // Esperar todas as threads finalizarem
    for (int i=0; i < t; i++){
        printf("Esperando thread %d finalizar... \n", i);
        pthread_join(threads[i], &thread_return); 
        printf("Thread %d finalizada\n", i);
    }

    // Somar as áreas totais de cada thread
    for(int i=0; i < t; i++){
        total = total + r[i];
    }

    printf("Processo pai finalizou e a área total é %f\n", total);

    return 0;

}