#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#define a 0.0
#define b 2.0*M_PI

typedef struct {
    int id;
    int num_trapezoids;
    float result;
} ThreadValues;

float h;

int sumT(int i){
    int total = 0;
    for(int j = 0; j < i; j++) total = total + i;
    return total;
}

float f(float x){
    return sin(2.0*x)+cos(5.0*x);
}

void * calculateArea(void * arg){

    ThreadValues *value = (ThreadValues *)arg;

    float localA = a + sumT(value->num_trapezoids) * h;
    float localB = value->num_trapezoids * h + localA;
    float totalArea = 0;

    for(int j = 0; j < value->num_trapezoids; j++){
        float bottom = localA + j*h;
        float top = bottom + h;

        totalArea = totalArea + h/2 * (f(bottom) + f(top));
    }

    value->result = totalArea;

    pthread_exit(NULL);
}

int getMDC(int num1, int num2) {
    int remainder;
    do {
        remainder = num1 % num2;
        num1 = num2;
        num2 = remainder;
    } while (remainder != 0);
    return num1;
}

int main(int argc, char * argv[]) {

    int t;
    printf("t=");
    scanf("%d", &t);

    int n;
    printf("n=");
    scanf("%d", &n);

    h = (b - a)/n;
    
    ThreadValues values[t];

    if(0 == n%t){
        for(int i=0; i < t; i++){
            values[i].id = i;
            values[i].num_trapezoids = n/t;
            values[i].result = 0.0;
        }
    }
    else{
        int p = getMDC(n,t);
        for(int i=0; i < t; i++) {
            values[i].id = i;
            values[i].result = 0.0;
            if(i != t-1){
                values[i].num_trapezoids = p;
            }else{
                values[i].num_trapezoids = n - i * p;
            }
        };     
    }

    pthread_t threads[t];

    for (int i=0; i < t; i++){
        printf("Processo principal criando thread %d\n", i);
        int status = pthread_create(&threads[i], NULL, calculateArea, &values[i]);

        if(status != 0){
            printf("Erro na criação da thread. Codigo de Erro: %d\n", status);
            return 1;
        }

    }

    void *thread_return;
    for (int i=0; i < t; i++){
        printf("Esperando thread %d finalizar... \n", i);
        pthread_join(threads[i], &thread_return); 
        printf("Thread %d finalizada\n", i);
    }

    float total;
    for(int i=0; i < t; i++){
        total = total + values[i].result;
    }
    printf("Processo pai finalizou e a área total é %.02f\n", total);

    return 0;
}