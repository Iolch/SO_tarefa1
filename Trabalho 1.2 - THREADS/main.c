// gcc main.c -o main -pthread
// ./main


#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

float a = 0.0;              // Limite inferior
float b = 2.0;              // Limite superior
float h;                    // Largura de cada trapézio
int t;                      // Número de threads a ser criadas
int n;                      // Número de trapézios


void * calculateArea(void * i){
//     if((int)(size_t)i > 0){
//         pthread_join(threads[(int)(size_t)i-1], &thread_return); 
//         printf("Esta é a thread %d. A thread %d terminou \n", (int)(size_t) i, (int)(size_t) i-1);
//     }else{
//         printf("Sou a primeira thread \n");
//     }
//     soma = soma + 1;
//     printf("sou %d a soma deu %d \n",(int)(size_t) i, soma);
//     sleep(1);
//     pthread_exit(NULL); //finaliza execução da thread
}

int isInt(void * i){
    return 1;
}

int main(int argc, char * argv[]){
    
    t = (int)(size_t) argv[1];  // Número de threads a ser criadas
    n = (int)(size_t) argv[2];  // Número de trapézios
    h = (b - a)/n;              // Largura de cada trapézio

    // Esses caras vão ficar na memória compartilhada
    int q[t];                   // Quantidade de trapézios em cada thread
    float r[t];                 // Resultado de cada thread
    pthread_t threads[t];
    void *thread_return;
    int status;
    //-----------------------------------------------
    

    // if(!isInt((void *)(size_t)(n/t))){
    if(0){
        // Caso o número de trapézios por thread seja decimal, 
        // teremos que mudar a distribuição de trapezios.
    }else{
        for(int i=0; i < t; i++) q[i] = n/t; // Completa o array q com o valor n/t
    }


    for (int i=0; i < n; i++){
        // cada thread i terá q[i] trapézios, assim, a distância entre o 'a' e o 'b'
        // local será a = x e b = q[i] * h + x
        printf("Processo principal criando thread %d\n", i);
        status = pthread_create(&threads[i], NULL, calculateArea, (void *)(size_t) i);

    }

    // for (i = 0; i < n; i ++){
    //     printf("Processo principal criando thread %d\n", i);
    //     status = pthread_create(&threads[i], NULL, sum, (void *)(size_t) i); //criando a tread

    //     if(status != 0){
    //         printf("Erro na criação da thread. Codigo de Erro: %d\n", status);
    //         return 1;
    //     }
    // }

    // printf("Esperando thread %d finalizar... \n", i-1);
    // pthread_join(threads[i-1], &thread_return); 
    // printf("Thread %d finalizada\n", i-1);

    // printf("Processo pai finalizar e soma é %d\n", soma);

    // return 0;

}