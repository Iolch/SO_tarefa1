#include "trem.h"
#include "semaphore.h"
#include <QtCore>

#define N 7
#define Q 5

#define AZUL 1
#define VERMELHO 2
#define VERDE 3
#define ROXO 4
#define LARANJA 5

#define i rc-1
#define t trem_id-1
#define OCUPADO 1
#define DISPONIVEL 0

//Construtor
Trem::Trem(int ID, int x, int y, int velocidade, int maxVelocidade, sem_t * s, sem_t * cross, sem_t * mutex, int * estado_rc, int * trem_rc){
    this->ID = ID;
    this->x = x;
    this->y = y;
    this->velocidade = velocidade;
    this->maxVelocidade = maxVelocidade;
    this->s = s;
    this->cross = cross;
    this->mutex = mutex;
    this->estado_rc = estado_rc;
    this->trem_rc = trem_rc;
}

void Trem::setVelocidade(int velocidade){
    this->velocidade = velocidade;
}

int Trem::getMaxVelocidade(){
    return this->maxVelocidade;
}

void Trem::in_rc(int rc, int trem_id){
    sem_wait(&s[i]);
    estado_rc[i] = OCUPADO;
    trem_rc[t] = rc;
}

void Trem::enter_rc(int rc, int trem_id){

    if(rc == 4) sem_wait(&cross[0]);
    if(rc == 5) sem_wait(&cross[1]);

    if(ID==AZUL){
        if(rc == 1){
            if(trem_rc[VERMELHO-1]==4 && trem_rc[ROXO-1]==3){
                sem_wait(&s[3]);
                sem_post(&s[3]);
            }
        }
    }else if(ID == VERMELHO){
        if(rc == 2){
            if(trem_rc[LARANJA-1]==5 && trem_rc[VERDE-1]==6){
                sem_wait(&s[5]);
                sem_post(&s[5]);
            }
            if(trem_rc[VERDE-1]==6 && trem_rc[LARANJA-1]==7 && trem_rc[ROXO-1]==3){
                sem_wait(&s[5]);
                sem_post(&s[5]);
            }
        }
    }else if(ID == VERDE){
        if(rc == 6){
            if(trem_rc[VERMELHO-1]==2 && trem_rc[LARANJA-1]==5){
                sem_wait(&s[1]);
                sem_post(&s[1]);
            }
        }
    }else if(ID == ROXO){
        if(rc == 3){
            if(trem_rc[AZUL-1]==1 && trem_rc[VERMELHO-1]==4){
                sem_wait(&s[0]);
                sem_post(&s[0]);
            }
            if(trem_rc[LARANJA-1]==7 && trem_rc[VERMELHO-1]==5){
                sem_wait(&s[6]);
                sem_post(&s[6]);
            }
        }
    }else if(ID == LARANJA){
        if(rc == 7){
            if(trem_rc[ROXO-1]==4){
                sem_wait(&s[3]);
                sem_post(&s[3]);
            }
        }
    }
    in_rc(rc, trem_id);
}

void Trem::out_rc(int rc, int trem_id){
     if(estado_rc[i] == OCUPADO && trem_rc[t] == rc){
//        if(ID == AZUL){
//             if(rc==1 && estado_rc[2] == OCUPADO){
//                 sem_wait(&s[2]);
//                 sem_post(&s[2]);
//             }
//        }else if(ID == VERMELHO){
//            if(rc==2){
//                if(trem_rc[LARANJA-1]==7 && trem_rc[ROXO-1]==4){
//                    sem_wait(&s[6]);
//                    sem_post(&s[6]);
//                }else if(trem_rc[AZUL-1]==1 && trem_rc[ROXO-1]==3 && trem_rc[LARANJA-1]==7){
//                    sem_wait(&s[6]);
//                    sem_post(&s[6]);
//                }
//            }
//            if(rc==5){
//                if(trem_rc[AZUL-1]==1 && trem_rc[ROXO-1]==3){
//                    sem_wait(&s[0]);
//                    sem_post(&s[0]);
//                }
//            }
//            if(rc==4){
//                if(trem_rc[AZUL-1]==1){
//                    sem_wait(&s[0]);
//                    sem_post(&s[0]);
//                }
//            }
//        }else if(ID == VERDE){
//            if(rc == 6){
//                if(trem_rc[VERMELHO-1]==2){
//                    sem_wait(&s[1]);
//                    sem_post(&s[1]);
//                }
//            }
//        }else if(ID == ROXO){
//            if(rc == 3){
//                if(trem_rc[LARANJA-1]==7 && trem_rc[VERMELHO-1]==5){
//                    sem_wait(&s[6]);
//                    sem_post(&s[6]);
//                }
//            }
//            if(rc == 4){
//                if(trem_rc[LARANJA-1]==7){
//                    sem_wait(&s[6]);
//                    sem_post(&s[6]);
//                }
//            }
//        }else if(ID == LARANJA){
//            if(rc == 7){
//                if(trem_rc[VERMELHO-1]==2 && trem_rc[VERDE-1]==6){
//                    sem_wait(&s[1]);
//                    sem_post(&s[1]);
//                }
//            }
//            if(rc == 5){
//                if(trem_rc[VERDE-1]==6){
//                    sem_wait(&s[5]);
//                    sem_post(&s[5]);
//                }
//            }
//        }
        estado_rc[i] = DISPONIVEL;
        trem_rc[t] = -1;
        sem_post(&s[i]);
        if(rc==4) sem_post(&cross[0]);
        if(rc==5) sem_post(&cross[1]);
     }
}

void Trem::run(){

    // Calcula o próximo passo do trem.
    while(true){
        switch(ID){
            case 1: //Trem 1
                if (y == 30 && x <330)
                    x+=10;
                else if (x == 330 && y < 150)
                    y+=10;
                else if (x > 60 && y == 150)
                    x-=10;
                else
                    y-=10;
                break;
            case 2: //Trem 2
                if (y == 30 && x <600)
                    x+=10;
                else if (x == 600 && y < 150)
                    y+=10;
                else if (x > 330 && y == 150)
                    x-=10;
                else
                    y-=10;
                break;
            case 3: //Trem 3
                if (y == 30 && x <870)
                    x+=10;
                else if (x == 870 && y < 150)
                    y+=10;
                else if (x > 600 && y == 150)
                    x-=10;
                else
                    y-=10;
                break;
            case 4: //Trem 4
                if (y == 150 && x <470)
                    x+=10;
                else if (x == 470 && y < 270)
                    y+=10;
                else if (x > 200 && y == 270)
                    x-=10;
                else
                    y-=10;
                break;
            case 5: //Trem 5
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
        if((x == 330 && y == 140 && ID==AZUL) || (x == 350 && y == 30 && ID==VERMELHO)){    // Região crítica 1
            out_rc(1, ID);
        }
        if((x == 600 && y == 140 && ID==VERMELHO) || (x == 620 && y==30 && ID==VERDE)){     // Região crítica 2
            out_rc(2, ID);
        }
        if((x==180 && y==150 && ID==AZUL) || (x==320 && y==150 && ID==ROXO)){               // Região crítica 3
            out_rc(3, ID);
        }
        if((x==340 && y==150 && ID==VERMELHO) || (x==460 && y==150 && ID==ROXO)){           // Região crítica 4
            out_rc(4, ID);
        }
        if((x==480 && y==150 && ID==VERMELHO) || (x==590 && y==150 && ID==LARANJA)){        // Região crítica 5
            out_rc(5, ID);
        }
        if((x==610 && y==150 && ID==VERDE) || (x==740 && y==170 && ID==LARANJA)){           // Região crítica 6
            out_rc(6, ID);
        }
        if((x==450 && y==270 && ID==ROXO) || (x==470 && y==160 && ID==LARANJA)){            // Região crítica 7
            out_rc(7, ID);
        }

        // Verifica se o trem entrará em uma região crítica.
        if((x == 320 && y == 30 && ID==AZUL) || (x == 340 && y == 150 && ID==VERMELHO)){    // Região crítica 1
            enter_rc(1, ID);
        }
        if((x == 590 && y == 30 && ID==VERMELHO) || (x == 610 && y==150 && ID==VERDE)){     // Região crítica 2
            enter_rc(2, ID);
        }
        if((x==330 && y==140 && ID==AZUL) || (x==200 && y==160 && ID==ROXO)){               // Região crítica 3
            enter_rc(3, ID);
        }
        if((x==480 && y==150 && ID==VERMELHO) || (x==320 && y==150 && ID==ROXO)){           // Região crítica 4
            enter_rc(4, ID);
        }
        if((x==600 && y==140 && ID==VERMELHO) || (x==470 && y==160 && ID==LARANJA)){        // Região crítica 5
            enter_rc(5, ID);
        }
        if((x==750 && y==150 && ID==VERDE) || (x==590 && y==150 && ID==LARANJA)){           // Região crítica 6
            enter_rc(6, ID);
        }
        if((x==460 && y==150 && ID==ROXO) || (x==480 && y==270 && ID==LARANJA)){            // Região crítica 7
            enter_rc(7, ID);
        }

        emit updateGUI(ID, x,y);
        msleep(velocidade);

    }
}
