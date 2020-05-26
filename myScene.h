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

// JOUER CONTRE UNE IA OU UN JOUEUR
/*
*   un menu avec un radio button pas réussi à transférer la valeur du radio sélectionner
*   ducoup c'est en dur :
*   1 pour jouer contre une ia
*   0 pour jouer à 2 joueurs
*   
*   Le niveau permet de controller à quelle vitesse l'ia peut se déplacer
*/
#define AI 0
#define AI_LEVEL 4

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