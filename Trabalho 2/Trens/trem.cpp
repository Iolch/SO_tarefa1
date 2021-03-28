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
Trem::Trem(int ID, int x, int y, int velocidade, int maxVelocidade, sem_t * s, sem_t * mutex, int * estado_rc, int * trem_rc){
    this->ID = ID;
    this->x = x;
    this->y = y;
    this->velocidade = velocidade;
    this->maxVelocidade = maxVelocidade;
    this->s = s;
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

    // Se o trem vem de outra região crítica.
//    if(trem_rc[t] != -1){
//        estado_rc[trem_rc[t]-1] = DISPONIVEL; // A região crítica anterior fica disponível.
//    }

    sem_wait(&s[i]);
    printf("O trem #%d vai ocupar o %d\n", trem_id, rc);
    estado_rc[i] = OCUPADO; // O trem irá passar pela nova região crítica, então ela ficará ocupada.
    trem_rc[t] = rc;

    //sem_post(&s[i]); // Fecha semáforo.

}

void Trem::enter_rc(int rc, int trem_id){

//    sem_wait(mutex); // Início da região crítica de verificação de entrada.

    if(trem_id==AZUL && rc==1){
        if((estado_rc[2]==OCUPADO) && (estado_rc[3]==OCUPADO)){
            sem_wait(&s[2]);
        }
    }
    else if(trem_id==VERMELHO && rc==2){
        if(estado_rc[4]==OCUPADO && estado_rc[5]==OCUPADO){
            sem_wait(&s[4]);
        }
    }
    else if(trem_id==VERDE && rc==6){
        if(estado_rc[1]==OCUPADO && estado_rc[4]==OCUPADO){
            sem_wait(&s[1]);
        }
    }
    else if(trem_id==ROXO && rc==3){
        if(estado_rc[0]==OCUPADO && estado_rc[3]==OCUPADO){
            sem_wait(&s[0]);
        }
    }
    else if(trem_id==LARANJA && rc==7){
        if(estado_rc[3]==OCUPADO && estado_rc[4]==OCUPADO){
            sem_wait(&s[4]);
        }
    }

    in_rc(rc, trem_id);

//    sem_post(mutex); // Final da região crítica de verificação de entrada.

}

void Trem::out_rc(int rc, int trem_id){


//    sem_wait(mutex); // Início da região crítica de verificação de saída.

    if(estado_rc[i] == OCUPADO && trem_rc[t] == rc){
        if(trem_id == AZUL){
            if(rc==1 && estado_rc[2] == OCUPADO){
                sem_wait(&s[2]);
            }
        }
        else if(trem_id == VERMELHO){
            if(rc == 2 && estado_rc[4] == OCUPADO){
                sem_wait(&s[4]);
            }
            else if(rc == 5 && estado_rc[3] == OCUPADO){
                sem_wait(&s[3]);
            }
            else if(rc == 4 && estado_rc[0] == OCUPADO){
                sem_wait(&s[0]);
            }
        }
        else if(trem_id == VERDE){
            if(rc == 6 && estado_rc[1] == OCUPADO){
                sem_wait(&s[1]);
            }
        }
        else if(trem_id == ROXO){
            if(rc == 3 && estado_rc[3] == OCUPADO){
                sem_wait(&s[3]);
            }
            else if(rc == 4 && estado_rc[6] == OCUPADO){
                sem_wait(&s[6]);
            }
        }
        else if(trem_id == LARANJA){
            if(rc == 7 && estado_rc[4] == OCUPADO){
                sem_wait(&s[4]);
            }
            else if(rc == 5 && estado_rc[5] == OCUPADO){
                sem_wait(&s[5]);
            }
        }


        estado_rc[i] = DISPONIVEL;
        //printf("A rc %d está disponivel\n", rc);
        trem_rc[t] = -1;
        sem_post(&s[i]);
        printf("O trem #%d liberou a rc %d\n", trem_id, rc);
    }
//    sem_post(mutex); // Final da região crítica de verificação de saída.
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
            printf("Trem #%d sai de 1\n", ID);
            out_rc(1, ID);
        }
        if((x == 600 && y == 140 && ID==VERMELHO) || (x == 620 && y==30 && ID==VERDE)){     // Região crítica 2
            printf("Trem #%d sai de 2\n", ID);
            out_rc(2, ID);
        }
        if((x==180 && y==150 && ID==AZUL) || (x==320 && y==150 && ID==ROXO)){               // Região crítica 3
            printf("Trem #%d sai de 3\n", ID);
            out_rc(3, ID);
        }
        if((x==340 && y==150 && ID==VERMELHO) || (x==460 && y==150 && ID==ROXO)){           // Região crítica 4
            printf("Trem #%d sai de 4\n", ID);
            out_rc(4, ID);
        }
        if((x==480 && y==150 && ID==VERMELHO) || (x==590 && y==150 && ID==LARANJA)){        // Região crítica 5
            printf("Trem #%d sai de 5\n", ID);
            out_rc(5, ID);
        }
        if((x==610 && y==150 && ID==VERDE) || (x==740 && y==170 && ID==LARANJA)){           // Região crítica 6
            printf("Trem #%d sai de 6\n", ID);
            out_rc(6, ID);
        }
        if((x==450 && y==270 && ID==ROXO) || (x==470 && y==160 && ID==LARANJA)){            // Região crítica 7
            printf("Trem #%d sai de 7\n", ID);
            out_rc(7, ID);
        }

        // Verifica se o trem entrará em uma região crítica.
        if((x == 320 && y == 30 && ID==AZUL) || (x == 340 && y == 150 && ID==VERMELHO)){    // Região crítica 1
            printf("Trem #%d entra em 1\n", ID);
            enter_rc(1, ID);
        }
        if((x == 590 && y == 30 && ID==VERMELHO) || (x == 610 && y==150 && ID==VERDE)){     // Região crítica 2
            printf("Trem #%d entra em 2\n", ID);
            enter_rc(2, ID);
        }
        if((x==330 && y==140 && ID==AZUL) || (x==200 && y==160 && ID==ROXO)){               // Região crítica 3
            printf("Trem #%d entra em 3\n", ID);
            enter_rc(3, ID);
        }
        if((x==480 && y==150 && ID==VERMELHO) || (x==320 && y==150 && ID==ROXO)){           // Região crítica 4
            printf("Trem #%d entra em 4\n", ID);
            enter_rc(4, ID);
        }
        if((x==600 && y==140 && ID==VERMELHO) || (x==470 && y==160 && ID==LARANJA)){        // Região crítica 5
            printf("Trem #%d entra em 5\n", ID);
            enter_rc(5, ID);
        }
        if((x==750 && y==150 && ID==VERDE) || (x==590 && y==150 && ID==LARANJA)){           // Região crítica 6
            printf("Trem #%d entra em 6\n", ID);
            enter_rc(6, ID);
        }
        if((x==460 && y==150 && ID==ROXO) || (x==480 && y==270 && ID==LARANJA)){            // Região crítica 7
            printf("Trem #%d entra em 7\n", ID);
            enter_rc(7, ID);
        }



        emit updateGUI(ID, x,y);
        msleep(velocidade);

    }
}
