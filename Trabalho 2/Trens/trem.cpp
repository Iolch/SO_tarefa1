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
#define OCUPADO 1
#define DISPONIVEL 0

//Construtor
Trem::Trem(int ID, int x, int y, int velocidade, int maxVelocidade, sem_t * s, sem_t * mutex, int * estado){
    this->ID = ID;
    this->x = x;
    this->y = y;
    this->velocidade = velocidade;
    this->maxVelocidade = maxVelocidade;
    this->s = s;
    this->mutex = mutex;
    this->estado = estado;
}

void Trem::setVelocidade(int velocidade){
    this->velocidade = velocidade;
}
int Trem::getMaxVelocidade(){
    return this->maxVelocidade;
}
void Trem::teste(int rc){
    if(estado[i] == DISPONIVEL){
        //entao pode entrar na area critica
        estado[i] = OCUPADO;
        sem_post(&s[i]);
    }
}
void Trem::enter_rc(int rc){
    sem_wait(mutex);    //entra na regiao critica
    teste(rc);
    sem_post(mutex);    //sai da regiao critica
    sem_wait(&s[i]);    //espera o semaforo i
}
void Trem::out_rc(int rc){
    sem_wait(mutex);    //entra na regiao critica
    estado[i] = DISPONIVEL;
    sem_wait(&s[i]);    //espera o semaforo i
}
//Função a ser executada após executar trem->START
void Trem::run(){
    while(true){
        switch(ID){
        case 1:     //Trem 1
            if (y == 30 && x <330)
                x+=10;
            else if (x == 330 && y < 150)
                y+=10;
            else if (x > 60 && y == 150)
                x-=10;
            else
                y-=10;
//            emit updateGUI(ID, x,y);    //Emite um sinal
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
//            emit updateGUI(ID, x,y);    //Emite um sinal
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
//            emit updateGUI(ID, x,y);    //Emite um sinal
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
//            emit updateGUI(ID, x,y);    //Emite um sinal
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
           /* emit updateGUI(ID, x,y);*/    //Emite um sinal
            break;
        default:
            break;
        }

        // Se está entrando na regiao critica
        if((x == 320 && y == 30 && ID==AZUL) || (x == 340 && y == 150 && ID==VERMELHO)){    // Tentando entrar na regiao critica 1
            enter_rc(1);
        }
        if((x == 590 && y == 30 && ID==VERMELHO) || (x == 610 && y==150 && ID==VERDE)){      // Tentando entrar na regiao critica 2
            enter_rc(2);
        }
        if((x==330 && y==140 && ID==AZUL) || (x==200 && y==160 && ID==ROXO)){               // Tentando entrar na regiao critica 3
            enter_rc(3);
        }
        if((x==480 && y==150 && ID==VERMELHO) || (x==320 && y==150 && ID==ROXO)){           // Tentando entrar na regiao critica 4
            enter_rc(4);
        }
        if((x==600 && y==140 && ID==VERMELHO) || (x==470 && y==160 && ID==LARANJA)){        // Tentando entrar na regiao critica 5
            enter_rc(5);
        }
        if((x==750 && y==150 && ID==VERDE) || (x==590 && y==150 && ID==LARANJA)){           // Tentando entrar na regiao critica 6
            enter_rc(6);
        }
        if((x==460 && y==150 && ID==ROXO) || (x==480 && y==270 && ID==LARANJA)){           // Tentando entrar na regiao critica 7
            enter_rc(7);
        }

        // Se está saindo na regiao critica
        if((x == 330 && y == 140 && ID==AZUL) || (x == 350 && y == 30 && ID==VERMELHO)){    // Tentando sair da regiao critica 1
            out_rc(1);
        }
        if((x == 600 && y == 140 && ID==VERMELHO) || (x == 620 && y==30 && ID==VERDE)){      // Tentando sair da regiao critica 2
            out_rc(2);
        }
        if((x==180 && y==150 && ID==AZUL) || (x==320 && y==150 && ID==ROXO)){           // Tentando sair da regiao critica 3
            out_rc(3);
        }
        if((x==340 && y==150 && ID==VERMELHO) || (x==460 && y==150 && ID==ROXO)){           // Tentando sair da regiao critica 4
            out_rc(4);
        }
        if((x==480 && y==150 && ID==VERMELHO) || (x==590 && y==150 && ID==LARANJA)){           // Tentando sair da regiao critica 5
            out_rc(5);
        }
        if((x==610 && y==150 && ID==VERDE) || (x==740 && y==170 && ID==LARANJA)){           // Tentando sair da regiao critica 6
            out_rc(6);
        }
        if((x==450 && y==270 && ID==ROXO) || (x==470 && y==160 && ID==LARANJA)){           // Tentando sair da regiao critica 7
            out_rc(7);
        }



        emit updateGUI(ID, x,y);
        msleep(velocidade);

    }
}




