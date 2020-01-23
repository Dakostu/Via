#include "../interfaces/localizable.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QGuiApplication>
#include <QScreen>
#include <QGraphicsView>
#include <QWheelEvent>
#include <QPen>
#include <QBrush>
#include <QGraphicsRectItem>
#include <QPainterPath>

#include "../shapes/routenode.h"
#include "../shapes/route.h"
#include "../shapes/octagon.h"
#include "../shapes/routeconnection.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      currentScene(std::make_unique<QGraphicsScene>())
{
    ui->setupUi(this);

    initializeMenus();
    initializeShapeSelections();

    ui->picture->setBackgroundRole(QPalette::Base);


    QPixmap m("/home/dk/Documents/Code/C++/QT/Wegweiser/test/gtavc_vice_city_map_hq.jpg");
    currentScene->addPixmap(m);
    ui->picture->setScene(currentScene.get());

    Route route(Qt::red, currentScene.get());    
    //route.setElementSize(30);
    route.addNode(500,600);
    route.addNode(500,700);
    route.addNode(600,550);
    route.addNode(400,150);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::initializeMenus() {

    menus.emplace_back(std::make_unique<QMenu>(Localizable::getUIString("FILE")));
    menus[0]->addAction(Localizable::getUIString("OPEN"));
    menus[0]->addAction(Localizable::getUIString("SAVE"));
    menus[0]->addAction(Localizable::getUIString("SAVE_AS"));
    menus[0]->addAction(Localizable::getUIString("PRINT"));
    menus[0]->addAction(Localizable::getUIString("EXPORT"));
    menus[0]->addSeparator();
    menus[0]->addAction(Localizable::getUIString("QUIT"));

    menus.emplace_back(std::make_unique<QMenu>(Localizable::getUIString("EDIT")));
    menus[1]->addAction(Localizable::getUIString("UNDO"));
    menus[1]->addAction(Localizable::getUIString("REDO"));
    menus[1]->addSeparator();
    menus[1]->addAction(Localizable::getUIString("CUT"));
    menus[1]->addAction(Localizable::getUIString("COPY"));
    menus[1]->addAction(Localizable::getUIString("PASTE"));

    for (const auto &menu : menus) {
        this->menuBar()->addMenu(menu.get());
    }
}

void MainWindow::initializeShapeSelections() {
    QStringList availableStyles({Localizable::getUIString("SQUARE"),
                                 Localizable::getUIString("TRIANGLE_UP"),
                                 Localizable::getUIString("TRIANGLE_DOWN"),
                                 Localizable::getUIString("DIAMOND"),
                                 Localizable::getUIString("HEXAGON"),
                                });
    ui->nodeStyleComboBox->addItems(availableStyles);
    ui->routeStyleComboBox->addItems(availableStyles);
}

