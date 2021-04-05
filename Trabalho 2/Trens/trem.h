#ifndef TREM_H
#define TREM_H

#include "semaphore.h"
#include <QThread>

class Trem: public QThread {

    Q_OBJECT

    public:
        Trem(int,int,int,int,int,sem_t*,sem_t*,int*,int*);
        void run();
        void setVelocidade(int);
        int getMaxVelocidade();
        void enter_rc(int); // Função que analisa se o trem pode entrar na região crítica.
        void in_rc(int);    // Função que loca a região crítica para o trem.
        void out_rc(int);   // Função que analisa se o trem pode sair da região crítica.

    signals:
        void updateGUI(int,int,int);

    private:
       int x;
       int y;
       int ID;
       int velocidade;
       int maxVelocidade;
       sem_t * s;
       sem_t* cross;
       sem_t * mutex;
       int * estado_rc;
       int * trem_rc;
};

#endif // TREM_H
