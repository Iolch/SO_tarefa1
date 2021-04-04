#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "semaphore.h"

#define N 7
#define Q 5

#define DISPONIVEL 0

sem_t s[N];         // Um semáforo para cada região crítica.
sem_t mutex;        // Mutex.
sem_t cross[2];  // Um semáforo para cada região critica que passa mais de dois trens
int estado_rc[N];   // Estados das regiões críticas.
int trem_rc[Q];     // Região crítica que o trem está passando.


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);
    sem_init(&cross[0], 0, 2);
    sem_init(&cross[1], 0, 2);

    // Inicializa semáforos, mutex e arrays de estados.
    for(int i=0; i < N; i++){
        sem_init(&s[i], 0, 1);
        estado_rc[i] = DISPONIVEL;
        if(i < Q) trem_rc[i] = -1;
    }
    sem_init(&mutex, 0, 1);

    //Cria os trens com seus respectivos valores.
    trem1 = new Trem(1,60,90,(ui->slider1->maximum() - ui->slider1->value()), ui->slider1->maximum(), s, cross, &mutex, estado_rc, trem_rc);
    trem2 = new Trem(2,470,30,(ui->slider2->maximum() - ui->slider2->value()), ui->slider2->maximum(), s, cross, &mutex, estado_rc, trem_rc);
    trem3 = new Trem(3,870,90,(ui->slider3->maximum() - ui->slider3->value()), ui->slider3->maximum(), s, cross, &mutex, estado_rc, trem_rc);
    trem4 = new Trem(4,330,270,(ui->slider4->maximum() - ui->slider4->value()), ui->slider4->maximum(), s, cross, &mutex, estado_rc, trem_rc);
    trem5 = new Trem(5,600,270,(ui->slider5->maximum() - ui->slider5->value()), ui->slider5->maximum(), s, cross, &mutex, estado_rc, trem_rc);

    /*
     * Conecta o sinal UPDATEGUI à função UPDATEINTERFACE.
     * Ou seja, sempre que o sinal UPDATEGUI foi chamado, será executada a função UPDATEINTERFACE.
     * Os 3 parâmetros INT do sinal serão utilizados na função.
     * Trem1 e Trem2 são os objetos que podem chamar o sinal. Se um outro objeto chamar o
     * sinal UPDATEGUI, não haverá execução da função UPDATEINTERFACE
     */
    connect(trem1,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem2,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem3,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem4,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem5,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));

}

//Função que será executada quando o sinal UPDATEGUI for emitido
void MainWindow::updateInterface(int id, int x, int y){
    switch(id){
        case 1: //Atualiza a posição do objeto da tela (quadrado) que representa o trem1
            ui->label_trem1->setGeometry(x,y,21,17);
            break;
        case 2: //Atualiza a posição do objeto da tela (quadrado) que representa o trem2
            ui->label_trem2->setGeometry(x,y,21,17);
            break;
        case 3: //Atualiza a posição do objeto da tela (quadrado) que representa o trem3
            ui->label_trem3->setGeometry(x,y,21,17);
            break;
        case 4: //Atualiza a posição do objeto da tela (quadrado) que representa o trem3
            ui->label_trem4->setGeometry(x,y,21,17);
            break;
        case 5: //Atualiza a posição do objeto da tela (quadrado) que representa o trem3
            ui->label_trem5->setGeometry(x,y,21,17);
            break;
    default:
        break;
    }
}

MainWindow::~MainWindow() {
    delete ui;
    for(int i=0; i < N; i++){
        sem_destroy(&s[i]);
    }
    sem_destroy(&cross[0]);
    sem_destroy(&cross[1]);
    sem_destroy(&mutex);
}

// Ao clicar, trens começam execução.
void MainWindow::on_pushButton_clicked() {
    trem1->start();
    trem2->start();
    trem3->start();
    trem4->start();
    trem5->start();
}

// Ao clicar, trens param execução.
void MainWindow::on_pushButton_2_clicked() {
    trem1->terminate();
    trem2->terminate();
    trem3->terminate();
    trem4->terminate();
    trem5->terminate();
}

void MainWindow::on_slider1_sliderMoved(int position) {
    int max = trem1->getMaxVelocidade();
    trem1->setVelocidade(max-position);
}

void MainWindow::on_slider2_sliderMoved(int position) {
    int max = trem2->getMaxVelocidade();
    trem2->setVelocidade(max - position);
}

void MainWindow::on_slider3_sliderMoved(int position) {
    int max = trem3->getMaxVelocidade();
    trem3->setVelocidade(max - position);
}

void MainWindow::on_slider4_sliderMoved(int position) {
    int max = trem4->getMaxVelocidade();
    trem4->setVelocidade(max - position);
}

void MainWindow::on_slider5_sliderMoved(int position) {
    int max = trem5->getMaxVelocidade();
    trem5->setVelocidade(max - position);
}
