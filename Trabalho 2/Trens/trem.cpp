#include "trem.h"
#include <QtCore>
#include <QSemaphore>
#include <QPair>

#define PARADO 0        // Estado quando o trem está parado
#define CIRCULANDO 1    // Estado quando o trem está circulando
#define ENTRANDO 2      // Estado quando o trem quer entrar em uma regiao critica
#define CCIRCULANDO 3   // Estado quando o trem está circulando uma região critica

#define N 7     // 7 regiões criticas
#define Q 5     // 5 trens

QSemaphore s[N];    // Um semaforo para cada região
int estado[Q];      // Um estado para cada trem
int regiao[Q];      // Em qual regiao critica o trem está

//Construtor
Trem::Trem(int ID, int x, int y, int velocidade, int maxVelocidade){
    this->ID = ID;
    this->x = x;
    this->y = y;
    this->velocidade = velocidade;
    this->maxVelocidade = maxVelocidade;
    estado[ID] = CIRCULANDO;
}
void Trem::setVelocidade(int velocidade){
    this->velocidade = velocidade;
}
int Trem::getMaxVelocidade(){
    return this->maxVelocidade;
}
void Trem::move(int a, int b){
    // Tenta se mover, só consegue se mover não vá entrar em uma região critica em que está ocupada.
    // a e b representam as coordenadas x e y.

    if(a == 330 && (b>=30 && b<=167)){
        // Regiao Critica 1
        if((estado[ID-1] == CCIRCULANDO && regiao[ID-1] != 1) || estado[ID-1] == CIRCULANDO){
            //Vai entrar na regiao critica
            printf("O trem %d vai entrar na regiao 1\n", ID);
        }
    }
    if(a == 600 && (b>=30 && b<=167)){
        // Regiao Critica 2
        if((estado[ID-1] == CCIRCULANDO && regiao[ID-1] != 2) || estado[ID-1] == CIRCULANDO){
            //Vai entrar na regiao critica
            printf("O trem %d vai entrar na regiao 2\n", ID);

        }
    }
    if((a>=200 && a<=351) && b==80){
        // Regiao Critica 3
        if((estado[ID-1] == CCIRCULANDO && regiao[ID-1] != 3) || estado[ID-1] == CIRCULANDO){
            //Vai entrar na regiao critica
            printf("O trem %d vai entrar na regiao 3\n", ID);
        }
    }
    if((a>=330 && a<=491) && b==80){
        // Regiao Critica 4
        if((estado[ID-1] == CCIRCULANDO && regiao[ID-1] != 4) || estado[ID-1] == CIRCULANDO){
            //Vai entrar na regiao critica
            printf("O trem %d vai entrar na regiao 4\n", ID);

        }
    }
    if((a>=470 && a<=621) && b==80){
        // Regiao Critica 5
        if((estado[ID-1] == CCIRCULANDO && regiao[ID-1] != 5) || estado[ID-1] == CIRCULANDO){
            //Vê se pode entrar na regiao critica
            printf("O trem %d vai entrar na regiao 5\n", ID);
        }
    }
    if((a>=600 && a<=761) && b==80){
        // Regiao Critica 6
        if((estado[ID-1] == CCIRCULANDO && regiao[ID-1] != 6) || estado[ID-1] == CIRCULANDO){
            //Vai entrar na regiao critica
            printf("O trem %d vai entrar na regiao 6\n", ID);
        }
    }
    if(a == 470 && (b>=150 && b<=287)){
        // Regiao Critica 7
        if((estado[ID-1] == CCIRCULANDO && regiao[ID-1] != 7) || estado[ID-1] == CIRCULANDO){
            //Vai entrar na regiao critica
            printf("O trem %d vai entrar na regiao 7\n", ID);


        }
    }

}
//Função a ser executada após executar trem->START
void Trem::run(){
    while(true){
        switch(ID){
        case 1:     //Trem 1
            if (y == 30 && x <330){
                move(x+10, y);  // Checa se o trem vai entrar em uma região critica

                x+=10;
            }
            else if (x == 330 && y < 150){
                move(x, y+10);  // Checa se o trem vai entrar em uma região critica
                y+=10;
            }
            else if (x > 60 && y == 150){
                move(x-10, y);  // Checa se o trem vai entrar em uma região critica
                x-=10;
            }
            else{
                move(x, y-10);  // Checa se o trem vai entrar em uma região critica
                y-=10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 2: //Trem 2
            if (y == 30 && x <600){
                move(x+10, y);
                x+=10;
            }
            else if (x == 600 && y < 150){
                move(x, y+10);
                y+=10;
            }
            else if (x > 330 && y == 150){
                move(x-10, y);
                x-=10;
            }
            else{
                move(x, y-10);
                y-=10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 3: //Trem 3
            if (y == 30 && x <870){
                move(x+10, y);
                x+=10;
            }
            else if (x == 870 && y < 150){
                move(x, y+10);
                y+=10;
            }
            else if (x > 600 && y == 150){
                move(x-10, y);
                x-=10;
            }
            else{
                move(x, y-10);
                y-=10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 4: //Trem 4
            if (y == 150 && x <470){
                move(x+10, y);
                x+=10;
            }
            else if (x == 470 && y < 270){
                move(x, y+10);
                y+=10;
            }
            else if (x > 200 && y == 270){
                move(x-10, y);
                x-=10;
            }
            else{
                move(x, y-10);
                y-=10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 5: //Trem 5
            if (y == 150 && x <740){
                move(x+10, y);
                x+=10;
            }
            else if (x == 740 && y < 270){
                move(x, y+10);
                y+=10;
            }
            else if (x > 470 && y == 270){
                move(x-10, y);
                x-=10;
            }
            else{
                move(x, y-10);
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




