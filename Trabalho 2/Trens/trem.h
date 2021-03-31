#ifndef TREM_H
#define TREM_H

#include "semaphore.h"
#include <QThread>

/*
 * Classe Trem herda QThread
 * Classe Trem passa a ser uma thread.
 * A função START inicializa a thread. Após inicializada, a thread irá executar a função RUN.
 * Para parar a execução da função RUN da thread, basta executar a função TERMINATE.
 *
*/
class Trem: public QThread {

    Q_OBJECT

    public:
        Trem(int, int, int, int, int, sem_t*, int*, int*); //construtor
        void run(); // função a ser executada pela thread
        void enter_rc(int); // função que gerencia a entrada de um trem na região crítica.
        void in_rc(int); // função que aloca uma região crítica para um trem.
        void out_rc(int); // função que gerencia a saída de um trem da região crítica.
        void setVelocidade(int);
        int getMaxVelocidade();

    signals:
        void updateGUI(int,int,int);

    private:
       int x;
       int y;
       int ID;
       int velocidade;
       int maxVelocidade;
       sem_t * s;
       int * estado_rc;
       int * trem_rc;
};

#endif // TREM_H
