// gcc main.c -o main -pthread
// ./main


#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>

#define t 4                 // Número de threads a ser criadas
#define n 10                 // Número de trapézios
#define a 0.0               // Limite inferior
#define b 10.0              // Limite superior
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

// Função que retorna o máximo divisor comum entre dois números
// Retirada daqui http://devfuria.com.br/logica-de-programacao/mdc/
int getMDC(int num1, int num2) {

    int resto;

    do {                        //Estranho que se mudar pra while(){} normal ele para de funcionar
        resto = num1 % num2;    //ver com bruninha se ela entende

        num1 = num2;
        num2 = resto;

    } while (resto != 0);

    return num1;
}

int main(int argc, char * argv[]){   
   
    if(0 == n%t){
         // Se n/t for inteiro
        for(int i=0; i < t; i++) q[i] = n/t; // Completa o array q com o valor n/t
    }else{
        // Caso o número de trapézios por thread seja decimal, 
        // teremos que mudar a distribuição de trapezios.
        int p = getMDC(n,t);
        for(int i=0; i < t; i++) {
            if(i != t-1){
                q[i] = p;               // Cada thread irá calcular a área de getMDC(t,n) trapézios
            }else{
                q[i] = n - i * p;       // Caso seja a ultima thread, fica com todo mundo que não "coube" nas outras threads
            }
        };
        // EXEMPLO: para t = 4 e n = 10
        // q[0]=2; q[1]=2; q[2]=2; q[3] = 4;
        // Ou seja, divide o mais igual possível, 
        // e joga o resto na ultima thread        
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
