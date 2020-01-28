#include "../interfaces/localizable.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QBrush>
#include <QFileDialog>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QGuiApplication>
#include <QImageReader>
#include <QPainterPath>
#include <QPen>
#include <QScreen>
#include <QScrollBar>
#include <QPushButton>
#include <QWheelEvent>

#include "../controller/uiaddnodestate.h"
#include "../controller/uimovenodesstate.h"
#include "../controller/uiselectnodestate.h"
#include "../shapes/routenode.h"
#include "../shapes/route.h"
#include "../shapes/octagon.h"
#include "../shapes/routeconnection.h"

MainWindow::MainWindow(QWidget *parent, MainWindowController &newController)
    : QMainWindow(parent),
      controller(newController),
      ui(new Ui::MainWindow),
      currentScene(std::make_unique<QGraphicsScene>()),
      quickButtonGroup(std::make_unique<QButtonGroup>())
{
    ui->setupUi(this);

    initializeQuickButtons();
    initializeMenus();
    initializeShapeSelections();

    connect(ui->quickButtonNew, &QPushButton::pressed, this, &MainWindow::createNewProject);
    connect(ui->routeBoxButtonAddRoute, &QPushButton::pressed, this, &MainWindow::addRoute);


    //QPixmap m("/home/dk/Documents/Code/C++/QT/Wegweiser/test/gtavc_vice_city_map_hq.jpg");
    //currentScene->addPixmap(m);
    //ui->picture->setScene(currentScene.get());
    ui->picture->setUIState(controller.getCurrentState());


    //ui->picture->addRoute(Qt::red);
    //ui->picture->addNodeToCurrentRoute(500,600);
    //ui->picture->addNodeToCurrentRoute(500,700);
    //ui->picture->addNodeToCurrentRoute(600,550);
    //ui->picture->addNodeToCurrentRoute(400,150);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeQuickButtons() {
    controller.getCurrentState()->setToggleButtons(ui->quickButtonAutoAdd,
                                   ui->quickButtonMove,
                                   ui->quickButtonSelect);


    quickButtonGroup->addButton(ui->quickButtonAutoAdd);
    quickButtonGroup->addButton(ui->quickButtonMove);
    quickButtonGroup->addButton(ui->quickButtonSelect);
    connect(ui->quickButtonAutoAdd, &QAbstractButton::pressed, this, [&]() { controller.changeUIState<UIAddNodeState>(); });
    connect(ui->quickButtonMove, &QAbstractButton::pressed, this, [&]() { controller.changeUIState<UIMoveNodesState>(); });
    connect(ui->quickButtonSelect, &QAbstractButton::pressed, this, [&]() { controller.changeUIState<UISelectNodeState>(); });
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


void MainWindow::addRoute() {
    auto color = Qt::red;
    controller.addNewRouteToCurrentProject(color);
    ui->picture->addRoute(color);
    ui->routeBoxRouteList->setModel(&controller.getCurrentRoutes());
    ui->nodeBoxNodeList->clearSelection();

    auto model = ui->routeBoxRouteList->model();
    auto index = model->index(model->rowCount() - 1, 0);
    ui->routeBoxRouteList->selectionModel()->select(index, QItemSelectionModel::ClearAndSelect);

    auto vBar = ui->routeBoxRouteList->verticalScrollBar();
    vBar->setValue(vBar->maximum());
}

void MainWindow::createNewProject() {

    this->setEnabled(false);

    QString newFileName = QFileDialog::getSaveFileName(
                this, Localizable::getUIString("CREATE_NEW_PROJECT_TITLE"),
                "",
                Localizable::getUIString("PROJECT_FILE_TYPES"));

    if (newFileName.isEmpty()) {
        this->setEnabled(true);
        return;
    }


    QString pictureFileName = QFileDialog::getOpenFileName(
                this,
                Localizable::getUIString("LOAD_IMAGE_FILE"),
                "",
                Localizable::getUIString("QPIXMAP_SUPPORTED_FILE_TYPES"));

    if (!pictureFileName.isEmpty()) {
        controller.addProject(Project(newFileName, pictureFileName));
        currentScene->addPixmap(pictureFileName);
        ui->picture->setScene(currentScene.get());
    }

    this->setEnabled(true);
}

void MainWindow::setNoProjectsOpenMode(bool noProjectsOpen) {
    this->setEnabled(!noProjectsOpen);
    ui->quickButtonNew->setEnabled(true);
    ui->quickButtonOpen->setEnabled(true);

}
