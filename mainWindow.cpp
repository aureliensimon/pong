#include "mainWindow.h"

MainWindow::MainWindow() : QMainWindow() {
    // le widget dans lequel tout s'affiche
    widget_general = new QWidget;
    QHBoxLayout * qbl_general = new QHBoxLayout;
    widget_general->setLayout(qbl_general);
    this->setCentralWidget(widget_general);

    myscene = new MyScene(this);
    myview = new QGraphicsView(myscene, this);
    qbl_general->addWidget(myview);
    myview->setStyleSheet("background-color: black");
    myview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    myview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

MainWindow::~MainWindow() { }

QGroupBox * MainWindow::BuildGroupBoxControle() {
    QGroupBox * qgb = new QGroupBox(tr("Contrôle"));
    return qgb; 
} 