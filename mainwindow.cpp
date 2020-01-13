#include "localizable.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->menuBar()->addMenu(Localizable::getUIString("FILE"));
    this->menuBar()->addMenu(Localizable::getUIString("EDIT"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

