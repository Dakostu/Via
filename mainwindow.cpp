#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->menuBar()->addMenu(tr("&File"));
    this->menuBar()->addMenu(tr("&Edit"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

