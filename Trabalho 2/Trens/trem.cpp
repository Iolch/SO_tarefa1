#include "trem.h"
#include "semaphore.h"
#include <QtCore>

#define N 7     // Quantidade de regiões críticas.
#define Q 5     // Quantidade de trens.

#define AZUL 1
#define VERMELHO 2
#define VERDE 3
#define ROXO 4
#define LARANJA 5

#define i rc-1
#define t ID-1
#define OCUPADO 1
#define DISPONIVEL 0

Trem::Trem(int ID, int x, int y, int velocidade, int maxVelocidade, sem_t * s, sem_t* cross, int * estado_rc, int * trem_rc) {
    this->ID = ID;
    this->x = x;
    this->y = y;
    this->velocidade = velocidade;
    this->maxVelocidade = maxVelocidade;
    this->s = s;
    this->estado_rc = estado_rc;
    this->trem_rc = trem_rc;
    this->cross = cross;
}

void Trem::setVelocidade(int velocidade){
    this->velocidade = velocidade;
}

int Trem::getMaxVelocidade(){
    return this->maxVelocidade;
}

void Trem::in_rc(int rc){
    sem_wait(&s[i]);
    estado_rc[i] = OCUPADO;
    trem_rc[t] = rc;
}

void Trem::enter_rc(int rc){

    if(rc == 4) sem_wait(&cross[0]);
    if(rc == 5) sem_wait(&cross[1]);

    if(ID==AZUL && rc==1){
        if(estado_rc[2]==OCUPADO && estado_rc[3]==OCUPADO){
            sem_wait(&s[2]);
            sem_post(&s[2]);
        }
    }
    else if(ID==VERMELHO && rc==2){
        if(estado_rc[4]==OCUPADO && estado_rc[5]==OCUPADO){
            sem_wait(&s[4]);
            sem_post(&s[4]);
        }
        if(estado_rc[2]==OCUPADO && estado_rc[5]==OCUPADO && estado_rc[6]==OCUPADO){
            sem_wait(&s[5]);
            sem_post(&s[5]);
        }
    }
    else if(ID==VERDE && rc==6){
        if(estado_rc[1]==OCUPADO && estado_rc[4]==OCUPADO){
            sem_wait(&s[1]);
            sem_post(&s[1]);
        }
    }
    else if(ID==ROXO && rc==3){
        if(estado_rc[0]==OCUPADO && estado_rc[3]==OCUPADO){
            sem_wait(&s[0]);
            sem_post(&s[0]);
        }
        if(estado_rc[4]==OCUPADO && estado_rc[6]==OCUPADO){
            sem_wait(&s[6]);
            sem_post(&s[6]);
        }
    }
    else if(ID==LARANJA && rc==7){
        if(estado_rc[3]==OCUPADO && estado_rc[4]==OCUPADO){
            sem_wait(&s[4]);
            sem_post(&s[4]);
        }
    }

    in_rc(rc);
}

void Trem::out_rc(int rc){

    if(estado_rc[i] == OCUPADO && trem_rc[t] == rc){
//        if(ID == AZUL){
//            if(rc==1 && estado_rc[2] == OCUPADO){
//                sem_wait(&s[2]);
//                sem_post(&s[2]);
//            }
//        }
//        if(ID == VERMELHO){
//            if(rc == 2){
//                if(estado_rc[4] == OCUPADO){
//                    sem_wait(&s[4]);
//                    sem_post(&s[4]);
//                }
//                if(estado_rc[3] == OCUPADO && estado_rc[6] == OCUPADO){
//                    sem_wait(&s[6]);
//                    sem_post(&s[6]);
//                }
//                if(estado_rc[0]==OCUPADO && estado_rc[2]==OCUPADO && estado_rc[6]==OCUPADO){
//                    sem_wait(&s[6]);
//                    sem_post(&s[6]);
//                }
//            }
//            else if(rc == 5){
//                if(estado_rc[3] == OCUPADO){
//                    sem_wait(&s[3]);
//                    sem_post(&s[3]);
//                }
//                if(estado_rc[0] == OCUPADO && estado_rc[2] == OCUPADO){
//                    sem_wait(&s[2]);
//                    sem_post(&s[2]);
//                }
//            }
//            else if(rc == 4 && estado_rc[0] == OCUPADO){
//                sem_wait(&s[0]);
//                sem_post(&s[0]);
//            }
//        }
//        else if(ID == VERDE){
//            if(rc == 6 && estado_rc[1] == OCUPADO){
//                sem_wait(&s[1]);
//                sem_post(&s[1]);
//            }
//        }
//        else if(ID == ROXO){
//            if(rc == 3){
//                if(estado_rc[3] == OCUPADO){
//                    sem_wait(&s[3]);
//                    sem_post(&s[3]);
//                }
//                if(estado_rc[4] == OCUPADO && estado_rc[6] == OCUPADO){
//                    sem_wait(&s[6]);
//                    sem_post(&s[6]);
//                }
//            }
//            else if(rc == 4 && estado_rc[6] == OCUPADO){
//                sem_wait(&s[6]);
//                sem_post(&s[6]);
//            }
//        }
//        else if(ID == LARANJA){
//            if(rc == 7){
//                if(estado_rc[4] == OCUPADO){
//                    sem_wait(&s[4]);
//                    sem_post(&s[4]);
//                }
//                if(estado_rc[1] == OCUPADO && estado_rc[5] == OCUPADO){
//                    sem_wait(&s[1]);
//                    sem_post(&s[1]);
//                }
//            }
//            else if(rc == 5 && estado_rc[5] == OCUPADO){
//                sem_wait(&s[5]);
//                sem_post(&s[5]);
//            }
//        }

        sem_post(&s[i]);
        if(rc == 4) sem_post(&cross[0]);
        if(rc == 5) sem_post(&cross[1]);
        estado_rc[i] = DISPONIVEL;
        trem_rc[t] = -1;
    }
}

void Trem::run(){

    while(true){

        // Calcula o próximo passo do trem.
        switch(ID){
            case 1:
                if (y == 30 && x <330)
                    x+=10;
                else if (x == 330 && y < 150)
                    y+=10;
                else if (x > 60 && y == 150)
                    x-=10;
                else
                    y-=10;
                break;
            case 2:
                if (y == 30 && x <600)
                    x+=10;
                else if (x == 600 && y < 150)
                    y+=10;
                else if (x > 330 && y == 150)
                    x-=10;
                else
                    y-=10;
                break;
            case 3:
                if (y == 30 && x <870)
                    x+=10;
                else if (x == 870 && y < 150)
                    y+=10;
                else if (x > 600 && y == 150)
                    x-=10;
                else
                    y-=10;
                break;
            case 4:
                if (y == 150 && x <470)
                    x+=10;
                else if (x == 470 && y < 270)
                    y+=10;
                else if (x > 200 && y == 270)
                    x-=10;
                else
                    y-=10;
                break;
            case 5:
                if (y == 150 && x <740)
                    x+=10;
                else if (x == 740 && y < 270)
                    y+=10;
                else if (x > 470 && y == 270)
                    x-=10;
                else
                    y-=10;
                break;
        default:
            break;
        }

        // Verifica se o trem sairá de uma região crítica.
        if((x == 330 && y == 140 && ID==AZUL) || (x == 350 && y == 30 && ID==VERMELHO)){
            out_rc(1);
        }
        else if((x == 600 && y == 140 && ID==VERMELHO) || (x == 620 && y==30 && ID==VERDE)){
            out_rc(2);
        }
        else if((x==180 && y==150 && ID==AZUL) || (x==320 && y==150 && ID==ROXO)){
            out_rc(3);
        }
        else if((x==340 && y==150 && ID==VERMELHO) || (x==460 && y==150 && ID==ROXO)){
            out_rc(4);
        }
        else if((x==480 && y==150 && ID==VERMELHO) || (x==590 && y==150 && ID==LARANJA)){
            out_rc(5);
        }
        else if((x==610 && y==150 && ID==VERDE) || (x==740 && y==170 && ID==LARANJA)){
            out_rc(6);
        }
        else if((x==450 && y==270 && ID==ROXO) || (x==470 && y==160 && ID==LARANJA)){
            out_rc(7);
        }

        // Verifica se o trem entrará em uma região crítica.
        if((x == 320 && y == 30 && ID==AZUL) || (x == 340 && y == 150 && ID==VERMELHO)){
            enter_rc(1);
        }
        else if((x == 590 && y == 30 && ID==VERMELHO) || (x == 610 && y==150 && ID==VERDE)){
            enter_rc(2);
        }
        else if((x==330 && y==140 && ID==AZUL) || (x==200 && y==160 && ID==ROXO)){
            enter_rc(3);
        }
        else if((x==480 && y==150 && ID==VERMELHO) || (x==320 && y==150 && ID==ROXO)){
            enter_rc(4);
        }
        else if((x==600 && y==140 && ID==VERMELHO) || (x==470 && y==160 && ID==LARANJA)){
            enter_rc(5);
        }
        else if((x==750 && y==150 && ID==VERDE) || (x==590 && y==150 && ID==LARANJA)){
            enter_rc(6);
        }
        else if((x==460 && y==150 && ID==ROXO) || (x==480 && y==270 && ID==LARANJA)){
            enter_rc(7);
        }

        emit updateGUI(ID, x,y);
        msleep(velocidade);

    }
}
