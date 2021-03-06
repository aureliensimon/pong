#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <iostream>

#include "myScene.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
    public:
        MainWindow();
        ~MainWindow();
        QGroupBox * BuildGroupBoxControle();
    
    private:
        QWidget * widget_general;
        QMenu * menuFichier;
        QGraphicsScene * myscene;
        QGraphicsView * myview;
    
    public slots:
};

#endif