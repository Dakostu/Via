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

#include "../shapes/routenode.h"
#include "../shapes/octagon.h"

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

    auto node = new RouteNode(new Octagon(500,500, QBrush(Qt::darkRed)), "1", "This is a text\nhey");
    node->setSize(22);
    node->setOpacity(0.5);
    currentScene->addItem(node);
    currentScene->addItem(node->getExtraText());
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

