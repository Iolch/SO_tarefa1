#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "trem.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {

    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    public slots:
        void updateInterface(int,int,int);

    private slots:
        void on_pushButton_clicked();
        void on_pushButton_2_clicked();
        void on_slider1_sliderMoved(int position);
        void on_slider2_sliderMoved(int position);
        void on_slider3_sliderMoved(int position);
        void on_slider4_sliderMoved(int position);
        void on_slider5_sliderMoved(int position);

    private:
        Ui::MainWindow *ui;
        Trem *trem1;
        Trem *trem2;
        Trem *trem3;
        Trem *trem4;
        Trem *trem5;
};

#endif // MAINWINDOW_H
