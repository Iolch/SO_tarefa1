#include "trem.h"
#include <QtCore>
#include <QMutex>
#include <QPair>

#define PARADO 0        // Estado quando o trem está parado
#define CIRCULANDO 1    // Estado quando o trem está circulando
#define ENTRANDO 2      // Estado quando o trem quer entrar em uma regiao critica
#define CCIRCULANDO 3   // Estado quando o trem está circulando uma região critica

#define AZUL 0
#define VERMELHO 1
#define VERDE 2
#define ROXO 3
#define LARANJA 4

#define N 7     // 7 regiões criticas
#define Q 5     // 5 trens

QMutex s[N];    // Um semaforo para cada região
int estado[Q];      // Um estado para cada trem
int regiao[Q];      // Em qual regiao critica o trem está

//Construtor
Trem::Trem(int ID, int x, int y, int velocidade, int maxVelocidade){
    this->ID = ID;
    this->x = x;
    this->y = y;
    this->velocidade = velocidade;
    this->maxVelocidade = maxVelocidade;
    estado[ID-1] = CIRCULANDO;
}
void Trem::setVelocidade(int velocidade){
    this->velocidade = velocidade;
}
int Trem::getMaxVelocidade(){
    return this->maxVelocidade;
}
int Trem::move(int a, int b){
    // Tenta se mover, só consegue se mover não vá entrar em uma região critica em que está ocupada.
    // a e b representam as coordenadas x e y.

    if(a == 330 && (b>=30 && b<=150-27)){
        // Regiao Critica 1
        return 1;
    }
    if(a == 600 && (b>=30 && b<=150)){
        // Regiao Critica 2
        return 2;
    }
    if((a>=200 && a<=330) && b==150){
        // Regiao Critica 3
        return 3;
    }
    if((a>=330 && a<=470) && b==150){
        // Regiao Critica 4
        return 4;
    }
    if((a>=470 && a<=600) && b==150){
        // Regiao Critica 5
        return 5;
    }
    if((a>=600 && a<=740) && b==150){
        // Regiao Critica 6
        return 6;
    }
    if(a == 470 && (b>=150 && b<=270)){
        // Regiao Critica 7
        return 7;
    }
    return -1;

}

void lockUnlockRoads(int i, int rcritica){

    if(i == AZUL){
        while(rcritica == 1 && regiao[ROXO] == 3 && regiao[VERMELHO] == 4);
    }
    if(i == VERMELHO){
        while(rcritica == 4 && regiao[ROXO] == 3);
    }
    if(i == VERDE){
        while(rcritica == 6 && regiao[LARANJA] == 5);
        while(rcritica == 2 && regiao[LARANJA] == 5 && regiao[2] == 6);
    }
    if(i == ROXO){
        while(rcritica == 3 && regiao[VERMELHO] == 4);
    }
    if(i == LARANJA){
        while(rcritica == 5 && regiao[VERDE] == 6 && regiao[VERMELHO] == 2);
        while(rcritica == 7 && regiao[VERMELHO] == 5 && regiao[ROXO] == 4);
    }

    if(rcritica != -1) {
        if((estado[i] == CCIRCULANDO && regiao[i] != rcritica) || estado[i] == CIRCULANDO){ // Caso o trem esteja entrando uma nova rcritica

            if(regiao[i] != 0){     // Se a regiao que ele estava ainda nao foi fechada
                 s[regiao[i]-1].unlock();
                 printf("Trem %d loca %d\n", i+1, regiao[i]);
                 regiao[i] = 0;
            }

            s[rcritica-1].lock();
            estado[i] = CCIRCULANDO;
            regiao[i] = rcritica;
            printf("Trem %d loca %d\n", i+1, rcritica);
        }

    }else{
        if(estado[i]==CCIRCULANDO){ //Se ele tava CCirculando, mas agora sai desse estado
            estado[i] = CIRCULANDO;
            s[regiao[i]-1].unlock();

            printf("Trem %d unloca %d\n", i+1, regiao[i]);
            regiao[i] = 0;
        }
    }
}

//Função a ser executada após executar trem->START
void Trem::run(){
    while(true){
        switch(ID){
        case 1:     //Trem 1
            if (y == 30 && x <330){
                int rcritica = move(x+10, y);  // Checa se o trem vai entrar em uma região critica
                lockUnlockRoads(0, rcritica);
                x+=10;
            }
            else if (x == 330 && y < 150){
                int rcritica = move(x, y+10);  // Checa se o trem vai entrar em uma região critica
                lockUnlockRoads(0, rcritica);
                y+=10;
            }
            else if (x > 60 && y == 150){
                int rcritica = move(x-10, y);  // Checa se o trem vai entrar em uma região critica
                lockUnlockRoads(0, rcritica);
                x-=10;
            }
            else{
                int rcritica = move(x, y-10);  // Checa se o trem vai entrar em uma região critica
                lockUnlockRoads(0, rcritica);
                y-=10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 2: //Trem 2
            if (y == 30 && x <600){
                int rcritica = move(x+10, y);
                lockUnlockRoads(1, rcritica);
                x+=10;
            }
            else if (x == 600 && y < 150){
                int rcritica = move(x, y+10);
                lockUnlockRoads(1, rcritica);
                y+=10;
            }
            else if (x > 330 && y == 150){
                int rcritica = move(x-10, y);
                lockUnlockRoads(1, rcritica);
                x-=10;
            }
            else{
                int rcritica = move(x, y-10);
                lockUnlockRoads(1, rcritica);
                y-=10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 3: //Trem 3
            if (y == 30 && x <870){
                int rcritica = move(x+10, y);
                lockUnlockRoads(2, rcritica);
                x+=10;
            }
            else if (x == 870 && y < 150){
                int rcritica = move(x, y+10);
                lockUnlockRoads(2, rcritica);
                y+=10;
            }
            else if (x > 600 && y == 150){
                int rcritica = move(x-10, y);
                lockUnlockRoads(2, rcritica);
                x-=10;
            }
            else{
                int rcritica = move(x, y-10);
                lockUnlockRoads(2, rcritica);
                y-=10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 4: //Trem 4
            if (y == 150 && x <470){
                int rcritica = move(x+10, y);
                lockUnlockRoads(3, rcritica);
                x+=10;
            }
            else if (x == 470 && y < 270){
                int rcritica = move(x, y+10);
                lockUnlockRoads(3, rcritica);
                y+=10;
            }
            else if (x > 200 && y == 270){
                int rcritica = move(x-10, y);
                lockUnlockRoads(3, rcritica);
                x-=10;
            }
            else{
                int rcritica = move(x, y-10);
                lockUnlockRoads(3, rcritica);
                y-=10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 5: //Trem 5
            if (y == 150 && x <740){
                int rcritica = move(x+10, y);
                lockUnlockRoads(4, rcritica);
                x+=10;
            }
            else if (x == 740 && y < 270){
                int rcritica = move(x, y+10);
                lockUnlockRoads(4, rcritica);
                y+=10;
            }
            else if (x > 470 && y == 270){
                int rcritica = move(x-10, y);
                lockUnlockRoads(4, rcritica);
                x-=10;
            }
            else{
                int rcritica = move(x, y-10);
                lockUnlockRoads(4, rcritica);
                y-=10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        default:
            break;
        }
        msleep(velocidade);
    }
}




