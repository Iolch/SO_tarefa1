# Trabalho 1.1 - FORK

## Descrição do problema

Implementar uma execução da árvore de processos definida utilizando commandos FORK. Deve ser considerado que:

- 1 ano corresponde a 1 segundo;
- O pai morre aos 60 anos;
- O pai tem um filho aos 14 anos;
- O pai tem outro filho aos 16 anos;
- O pai é avô aos 26 anos (primeiro filho);
- O pai é avô novamente aos 30 anos (segundo filho);
- O primeiro e o segundo filho morrem ambos aos 30 anos;
- O primeiro neto morre aos 12 anos, enquanto que o segundo morre aos 18 anos;
- Em cada nascimento, informar o fato com a hora do nascimento;
- Em cada morte, informar o fato com a hora do nascimento, a hora da morte e quanto tempo viveu.

## Como executar

O código foi implementado com a linguagem C++. Para compilar e executar em qualquer distribuição Linux, é necessário instalar o pacote `build-essential`, ou apenas o compilador `g++`, e, por fim, utilizar o comando abaixo:

```sh
$ g++ -Wall -std=c++14 main.cpp -o main && ./main
```