# Trabalho 1.2 - THREADS

## Descrição do problema

Implementar um algoritmo que encontre a integral de uma curva em um determinado intervalo [a, b]. Para isso, deve ser utilizada a regra do trapézio com pthreads. O usuário deverá informar o número de threads *t > 1* a serem criadas e o número de trapézios *n*. Ambos os valores deverão ter inteiros.

Os testes deverão ser feitos em dois passos:

- Encontrar a integral da função f(x)=5 no intervalo [0, 10];
    - O resultado ideal é 50. O resultado esperado é 50. 
- Encontrar a integral da função f(x)=sen(2x)+cos(5x) no intervalo [0, 2*pi].
    - O resultado ideal é 0. O resultado esperado é um número próximo a 0.

Ambos irão utilizar como entrada os valores *t=6* e *n=120*, e *t=7* e *n=200*.

## Como executar

O código foi implementado com a linguagem C. Para compilar e executar em qualquer distribuição Linux, é necessário instalar o pacote `build-essential`, ou apenas o compilador `gcc`, e, por fim, utilizar os comandos abaixo:

```sh
$ gcc funcao1.c -o funcao1 -pthread && ./funcao1
$ gcc funcao2.c -o funcao2 -pthread -lm && ./funcao2
```

Os testes foram realizados utilizando a versão 7.5.0 e 9.3.0 do compilador.