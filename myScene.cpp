#include "myScene.h"

MyScene::MyScene(QObject *parent) : QGraphicsScene(parent){

    // Création des différents éléments
    board = new QGraphicsRectItem(0, 0, BOARD_WIDTH, BOARD_HEIGHT);
    paddleP1 = new QGraphicsRectItem(0, BOARD_HEIGHT / 2 - 40, 10, PADDLE_SIZE);
    paddleP2 = new QGraphicsRectItem(BOARD_WIDTH, BOARD_HEIGHT / 2 - 40, 10, PADDLE_SIZE);
    p1Score = new QGraphicsTextItem(QString::number(scoreP1));
    p2Score = new QGraphicsTextItem(QString::number(scoreP2));
    winner = new QGraphicsTextItem("");
    ball = new QGraphicsPixmapItem(QPixmap("balle.png"));

    // Mise en couleur des textes et des raquettes en blanc
    paddleP1->setBrush(QBrush(Qt::white));
    paddleP2->setBrush(QBrush(Qt::white));
    p1Score->setDefaultTextColor(Qt::white);
    p2Score->setDefaultTextColor(Qt::white);
    winner->setDefaultTextColor(Qt::white);
    
    // Mettre la place au milieu du terrain
    ball->setPos(BOARD_WIDTH / 2, BOARD_HEIGHT / 2);
    
    // Mettre les scores sur les côtés supérieurs du terrain et l'affiche un peu au dessus du milieu
    p1Score->setPos(BOARD_WIDTH / 4, 0);
    p2Score->setPos(3 * BOARD_WIDTH / 4, 0);
    winner->setPos(BOARD_WIDTH / 2 - 30, BOARD_HEIGHT / 2 - 100);

    // Les ajouter à la scène
    this->addItem(board);
    this->addItem(winner);
    this->addItem(paddleP1);
    this->addItem(paddleP2);
    this->addItem(p1Score);
    this->addItem(p2Score);
    this->addItem(ball);

    // Lancement timer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(12);
}

void MyScene::update () {
    // Si gameOver (= score maximal atteint par l'un des joueurs)
    if (scoreP1 > SCORE_MAX || scoreP2 > SCORE_MAX) {
        // Affichage du nom de celui qui possède le score le plus élevé
        (scoreP1 > scoreP2) ? winner->setPlainText("P1 WINNER") : winner->setPlainText("P2 WINNER") ;
        // Stop le jeu
        timer->stop();
    }
    // Si la balle est rentrée dans un des buts
    if (ball->x() > BOARD_WIDTH || ball->x() < 0) {
        // Incrémentation du score du joueur qui a mit le but
        (ball->x() > BOARD_WIDTH - 10) ? scoreP1++ : scoreP2++;
        
        // Mettre à jour vers où la balle va allez pour le prochain engagement (du côté de celui qui vient de prendre un but)
        goLeft = (ball->x() > BOARD_WIDTH - 10) ? 1 : -1;

        // Mise à jour des scores
        p1Score->setPlainText(QString::number(scoreP1));
        p2Score->setPlainText(QString::number(scoreP2));
        
        // Remise au centre
        ball->setPos(BOARD_WIDTH / 2 , BOARD_HEIGHT / 2);
        // Remise à l'état initial de la vitesse de la balle
        xSpeed = 3;
        ySpeed = 3;
    }
    // Si la balle touche les bords supérieurs / inférieurs
    if (ball->y() < 0 || ball->y() > BOARD_HEIGHT - 20) {
        // Inversion de la direction verticale
        goDown *= -1;
    }
    // Si la balle touche une raquette
    if (ball->collidesWithItem(paddleP2) || ball->collidesWithItem(paddleP1)) {
        // Inversion de la direction horizontale
        goLeft *= -1;
        // Augmentation de la vitesse de la balle
        xSpeed += 0.25;
        ySpeed += 0.25;
    }
    // Mise à jour de la position de la balle
    ball->setPos(ball->x() + xSpeed * goLeft, ball->y() + ySpeed * goDown);

    // Si l'IA joue
    if (AI) {
        // Si la balle n'est plus dans le premier tier du terrain, permettre à l'ia de bouger (plus réaliste)
        if (ball->x() > BOARD_WIDTH / 3) {
            if (paddleP2->y() + BOARD_HEIGHT / 2 > ball->y()) {
                // bouger vers le haut
                if (paddleP2->y() > BOARD_HEIGHT / -2 + PADDLE_SIZE / 2) paddleP2->setPos(paddleP2->x(), paddleP2->y() - AI_LEVEL);
            } else {
                // bouger vers le bas
                if (paddleP2->y() < BOARD_HEIGHT / 2 - PADDLE_SIZE / 2) paddleP2->setPos(paddleP2->x(), paddleP2->y() + AI_LEVEL);
            }
        }
    }
}

void MyScene::keyPressEvent (QKeyEvent * e) {
    /*
    *   Chaque if vérifie si la raquette ne sort pas du terrain
    */
    switch (e->key()) {
        case Qt::Key_Up:
            if (paddleP2->y() > BOARD_HEIGHT / -2 + PADDLE_SIZE / 2 && !AI) paddleP2->setPos(paddleP2->x(), paddleP2->y() - SENSI);
            break;
        case Qt::Key_Down:
            if (paddleP2->y() < BOARD_HEIGHT / 2 - PADDLE_SIZE / 2 && !AI) paddleP2->setPos(paddleP2->x(), paddleP2->y() + SENSI);
            break;
        case Qt::Key_Shift:
            if (paddleP1->y() > BOARD_HEIGHT / -2 + PADDLE_SIZE / 2) paddleP1->setPos(paddleP1->x(), paddleP1->y() - SENSI);
            break;
        case Qt::Key_Control:
            if (paddleP1->y() < BOARD_HEIGHT / 2 - PADDLE_SIZE / 2) paddleP1->setPos(paddleP1->x(), paddleP1->y() + SENSI);
            break;
    }
}