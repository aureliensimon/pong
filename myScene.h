#ifndef MYSCENE_H
#define MYSCENE_H


#include <iostream>
#include <string>
#include <QtWidgets>

// CONSTANTES
#define BOARD_WIDTH 800
#define BOARD_HEIGHT 444
#define SENSI 35
#define SCORE_MAX 10
#define PADDLE_SIZE 80

class MyScene : public QGraphicsScene {
    Q_OBJECT
    public :
        MyScene(QObject * parent = 0);

    private:
        QTimer * timer;
        QGraphicsRectItem * board;
        QGraphicsRectItem * paddleP1;
        QGraphicsRectItem * paddleP2;
        QGraphicsTextItem * p1Score;
        QGraphicsTextItem * p2Score;
        QGraphicsTextItem * winner;
        QGraphicsPixmapItem * ball;
        
        // Configuration de la balle
        // Booléen de direction
        int goLeft = 1;
        int goDown = 1;
        // Vitesse horizontale et verticale
        float xSpeed = 3.0;
        float ySpeed = 3.0;
        
        int scoreP1 = 0;
        int scoreP2 = 0;

    public slots:
        void update();
        void keyPressEvent(QKeyEvent *);
};

#endif