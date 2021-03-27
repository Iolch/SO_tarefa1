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
int ocupado[N] = {0};     // Quais regioes criticas tem um trem

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

// Verifica se o trem irá entrar em uma região crítica, retornando o número dela, de acordo com sua próxima coordenada (x, y)
int Trem::move(int train_id, int x, int y){
    switch (train_id) {
        case AZUL:
            if(x==320 && y==30) return 1;

            if(x==330 && y==140) return 3;
            break;
        case VERMELHO:
            if(x==340 && y==150)return 1;

            if(x==590 && y==30) return 2;

            if(x==480 && y==150) return 4;

            if(x==600 && y==140) return 5;
            break;
        case VERDE:
            if(x==610 && y==150) return 2;

            if(x==750 && y==150) return 6;
            break;
        case ROXO:
            if(x==200 && y==160)return 3;

            if(x==320 && y==150) return 4;

            if(x==460 && y==150) return 7;
            break;
        case LARANJA:
            if(x==470 && y==160)return 5;

            if(x==590 && y==150) return 6;

            if(x==480 && y==270) return 7;
            break;
    default:
        break;
    }
    return -1;
}

int Trem::moveOut(int train_id, int x, int y){
    switch (train_id) {
        case AZUL:
            if(x==330 && y==140) return 1;

            if(x==180 && y==150) return 3;
            break;
        case VERMELHO:
            if(x==350 && y==30)return 1;

            if(x==600 && y==140) return 2;

            if(x==340 && y==150) return 4;

            if(x==480 && y==150) return 5;
            break;
        case VERDE:
            if(x==620 && y==30) return 2;

            if(x==610 && y==150) return 6;
            break;
        case ROXO:
            if(x==320 && y==150)return 3;

            if(x==460 && y==150) return 4;

            if(x==450 && y==270) return 7;
            break;
        case LARANJA:
            if(x==590 && y==150)return 5;

            if(x==740 && y==170) return 6;

            if(x==470 && y==160) return 7;
            break;
    default:
        break;
    }
    return -1;
}

void lockUnlockRoads(int i, int rcritica, int rcout){

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


    if(rcout != -1 && estado[i] == CCIRCULANDO){

        if(i == AZUL){
            while(rcout == 1 && ocupado[2]);
        }
        if(i == VERMELHO){
            while(rcout == 2 && ocupado[4]);
            while(rcout == 5 && ocupado[3]);
            while(rcout == 4 && ocupado[0]);
        }
        if(i == VERDE){
            while(rcout == 6 && ocupado[1]);
        }
        if(i == ROXO){
            while(rcout == 3 && ocupado[3]);
            while(rcout == 4 && ocupado[6]);
        }
        if(i == LARANJA){
            while(rcout == 7 && ocupado[4]);
            while(rcout == 5 && ocupado[5]);
        }

        s[regiao[i]-1].unlock();
        ocupado[regiao[i]-1] = 0;
        estado[i] = CIRCULANDO;
        regiao[i] = 0;
        printf("Trem %d abre %d\n", i+1, regiao[i]);
    }

    if(rcritica != -1) {
        if((estado[i] == CCIRCULANDO && regiao[i] != rcritica) || estado[i] == CIRCULANDO){ // Caso o trem esteja entrando uma nova rcritica

            s[rcritica-1].lock();
            ocupado[regiao[i]-1] = 1;
            estado[i] = CCIRCULANDO;
            regiao[i] = rcritica;
            printf("Trem %d fecha %d\n", i+1, rcritica);
        }

    }
}

//Função a ser executada após executar trem->START
void Trem::run(){
    while(true){
        switch(ID){
        case 1:     //Trem 1
            if (y == 30 && x <330){
                int rcritica = move(0, x+10, y);  // Checa se o trem vai entrar em uma região critica
                int rcout = moveOut(0, x+10, y);
                lockUnlockRoads(0, rcritica, rcout);

                x+=10;
            }
            else if (x == 330 && y < 150){
                int rcritica = move(0, x, y+10);  // Checa se o trem vai entrar em uma região critica
                int rcout = moveOut(0, x, y+=10);
                lockUnlockRoads(0, rcritica, rcout);
                y+=10;
            }
            else if (x > 60 && y == 150){
                int rcritica = move(0, x-10, y);  // Checa se o trem vai entrar em uma região critica
                int rcout = move(0, x-10, y);
                lockUnlockRoads(0, rcritica, rcout);
                x-=10;
            }
            else{
                int rcritica = move(0, x, y-10);  // Checa se o trem vai entrar em uma região critica
                int rcout = move(0, x, y-10);
                lockUnlockRoads(0, rcritica, rcout);
                y-=10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 2: //Trem 2
            if (y == 30 && x <600){
                int rcritica = move(1, x+10, y);
                int rcout = move(1, x+10, y);
                lockUnlockRoads(1, rcritica, rcout);
                x+=10;
            }
            else if (x == 600 && y < 150){
                int rcritica = move(1, x, y+10);
                int rcout = move(1, x, y+10);
                lockUnlockRoads(1, rcritica, rcout);
                y+=10;
            }
            else if (x > 330 && y == 150){
                int rcritica = move(1, x-10, y);
                int rcout = move(1, x-10, y);
                lockUnlockRoads(1, rcritica, rcout);
                x-=10;
            }
            else{
                int rcritica = move(1, x, y-10);
                int rcout = move(1, x, y-10);
                lockUnlockRoads(1, rcritica, rcout);
                y-=10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 3: //Trem 3
            if (y == 30 && x <870){
                int rcritica = move(2, x+10, y);
                int rcout = move(2, x+10, y);
                lockUnlockRoads(2, rcritica, rcout);
                x+=10;
            }
            else if (x == 870 && y < 150){
                int rcritica = move(2, x, y+10);
                int rcout = move(2, x, y+10);
                lockUnlockRoads(2, rcritica, rcout);
                y+=10;
            }
            else if (x > 600 && y == 150){
                int rcritica = move(2, x-10, y);
                int rcout = move(2, x-10, y);
                lockUnlockRoads(2, rcritica, rcout);
                x-=10;
            }
            else{
                int rcritica = move(2, x, y-10);
                int rcout = move(2, x, y-10);
                lockUnlockRoads(2, rcritica, rcout);
                y-=10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 4: //Trem 4
            if (y == 150 && x <470){
                int rcritica = move(3, x+10, y);
                int rcout = move(3, x+10, y);
                lockUnlockRoads(3, rcritica, rcout);
                x+=10;
            }
            else if (x == 470 && y < 270){
                int rcritica = move(3, x, y+10);
                int rcout = move(3, x, y+10);
                lockUnlockRoads(3, rcritica, rcout);
                y+=10;
            }
            else if (x > 200 && y == 270){
                int rcritica = move(3, x-10, y);
                int rcout = move(3, x-10, y);
                lockUnlockRoads(3, rcritica, rcout);
                x-=10;
            }
            else{
                int rcritica = move(3, x, y-10);
                int rcout = move(3, x, y-10);
                lockUnlockRoads(3, rcritica, rcout);
                y-=10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 5: //Trem 5
            if (y == 150 && x <740){
                int rcritica = move(4, x+10, y);
                int rcout = move(4, x+10, y);
                lockUnlockRoads(4, rcritica, rcout);
                x+=10;
            }
            else if (x == 740 && y < 270){
                int rcritica = move(4, x, y+10);
                int rcout = move(4, x, y+10);
                lockUnlockRoads(4, rcritica, rcout);
                y+=10;
            }
            else if (x > 470 && y == 270){
                int rcritica = move(4, x-10, y);
                int rcout = move(4, x-10, y);
                lockUnlockRoads(4, rcritica, rcout);
                x-=10;
            }
            else{
                int rcritica = move(4, x, y-10);
                int rcout = move(4, x, y-10);
                lockUnlockRoads(4, rcritica, rcout);
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




