#include "../ui/localizeduistrings.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QBrush>
#include <QColorDialog>
#include <QFileDialog>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QGuiApplication>
#include <QImageReader>
#include <QLineEdit>
#include <QListView>
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
    selectedRouteIndex = 0;
    ui->setupUi(this);

    connect(&controller, &MainWindowController::currentProjectChanged, this, &MainWindow::getDataFromCurrentProject);
    connect(&controller, &MainWindowController::routeListChanged, this, &MainWindow::updateRouteList);
    connect(&controller, &MainWindowController::routeListEmpty, this, &MainWindow::resetSettingsBox);
    connect(&controller, &MainWindowController::routeNodeListChanged, this, &MainWindow::updateNodeList);
    connect(ui->picture, &MapView::routeNodeAdded, this, &MainWindow::addRouteNode);

    initializeQuickButtons();
    initializeMenus();
    initializeShapeSelections();
    initializeRouteBoxUI();
    initializeRouteSettingsUI();
    initializeNodeBoxUI();
    initializeNodeSettingsUI();

    ui->picture->setUIState(controller.getCurrentState());
    if (controller.amountOfOpenProjects() == 0) {
        setNoProjectsOpenMode(true);
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeQuickButtons() {

    connect(ui->quickButtonOpen, &QPushButton::clicked, this, &MainWindow::loadProject);
    connect(ui->quickButtonSave, &QPushButton::clicked, this, &MainWindow::saveProject);
    connect(ui->quickButtonSaveAs, &QPushButton::clicked, this, &MainWindow::saveProjectAs);

    controller.getCurrentState()->setToggleButtons(ui->quickButtonAutoAdd,
                                   ui->quickButtonMove,
                                   ui->quickButtonSelect);
    quickButtonGroup->addButton(ui->quickButtonAutoAdd);
    quickButtonGroup->addButton(ui->quickButtonMove);
    quickButtonGroup->addButton(ui->quickButtonSelect);
    connect(ui->quickButtonNew, &QPushButton::clicked, this, &MainWindow::createNewProject);
    connect(ui->quickButtonAutoAdd, &QAbstractButton::clicked, this, [&]() { activateAutoAddMode(); });
    connect(ui->quickButtonMove, &QAbstractButton::clicked, this, [&]() { controller.changeUIState<UIMoveNodesState>(); });
    connect(ui->quickButtonSelect, &QAbstractButton::clicked, this, [&]() { controller.changeUIState<UISelectNodeState>(); });
}

void MainWindow::initializeMenus() {

    menus.emplace_back(std::make_unique<QMenu>(LocalizedUIStrings::getUIString("FILE")));
    menus[0]->addAction(LocalizedUIStrings::getUIString("OPEN"));
    menus[0]->addAction(LocalizedUIStrings::getUIString("SAVE"));
    menus[0]->addAction(LocalizedUIStrings::getUIString("SAVE_AS"));
    menus[0]->addAction(LocalizedUIStrings::getUIString("PRINT"));
    menus[0]->addAction(LocalizedUIStrings::getUIString("EXPORT"));
    menus[0]->addSeparator();
    menus[0]->addAction(LocalizedUIStrings::getUIString("QUIT"));

    menus.emplace_back(std::make_unique<QMenu>(LocalizedUIStrings::getUIString("EDIT")));
    menus[1]->addAction(LocalizedUIStrings::getUIString("UNDO"));
    menus[1]->addAction(LocalizedUIStrings::getUIString("REDO"));
    menus[1]->addSeparator();
    menus[1]->addAction(LocalizedUIStrings::getUIString("CUT"));
    menus[1]->addAction(LocalizedUIStrings::getUIString("COPY"));
    menus[1]->addAction(LocalizedUIStrings::getUIString("PASTE"));

    for (const auto &menu : menus) {
        this->menuBar()->addMenu(menu.get());
    }
}

void MainWindow::initializeShapeSelections() {
    QStringList availableStyles({LocalizedUIStrings::getUIString("SQUARE"),
                                 LocalizedUIStrings::getUIString("TRIANGLE_UP"),
                                 LocalizedUIStrings::getUIString("TRIANGLE_DOWN"),
                                 LocalizedUIStrings::getUIString("DIAMOND"),
                                 LocalizedUIStrings::getUIString("HEXAGON"),
                                });
    ui->nodeStyleComboBox->addItems(availableStyles);
    ui->routeStyleComboBox->addItems(availableStyles);
}

void MainWindow::initializeRouteBoxUI() {
    connect(ui->routeBoxButtonAddRoute, &QPushButton::clicked, this, &MainWindow::addRoute);
    connect(ui->routeBoxButtonDeleteRoute, &QPushButton::clicked, this, &MainWindow::deleteSelectedRoute);
    connect(ui->routeBoxButtonUp, &QPushButton::clicked, this, [&]() { moveRouteEvent(-1); });
    connect(ui->routeBoxButtonDown, &QPushButton::clicked, this, [&]() { moveRouteEvent(1); });
    connect(ui->routeBoxRouteList->itemDelegate(), &QAbstractItemDelegate::commitData, this, [&](QWidget* lineEdit){
        routeNameChangeEvent((static_cast<QLineEdit*>(lineEdit))->text());}
    );
    connect(ui->routeBoxRouteList, &RouteDataView::changedSelection, this, &MainWindow::routeSelectionEvent);
}

void MainWindow::initializeNodeBoxUI() {
    connect(ui->nodeBoxButtonAddNode, &QPushButton::clicked, this, [&]() {
        ui->quickButtonAutoAdd->click();
        QCursor::setPos(this->pos() + ui->pictureLayout->geometry().center());
    });
}

void MainWindow::initializeNodeSettingsUI() {

}

void MainWindow::refreshSelectedRouteIndex() {
    if (ui->routeBoxRouteList->selectionModel() && ui->routeBoxRouteList->selectionModel()->hasSelection()) {
        selectedRouteIndex = ui->routeBoxRouteList->getSelectedRows()[0].row();
    }
}

void MainWindow::initializeRouteSettingsUI() {
    connect(ui->routeColorButton, &QPushButton::pressed, this, [&]() {
        refreshSelectedRouteIndex();
        colorChangeEvent(&(*controller.getCurrentProject())[selectedRouteIndex]);
    });
    connect(ui->routeNameLineEdit, &QLineEdit::textEdited, this, &MainWindow::routeNameChangeEvent);
    // change shape
    connect(ui->routeNodeOrderCheckBox, &QCheckBox::toggled, this, &MainWindow::routeShowOrderChangeEvent);
}

void MainWindow::getDataFromCurrentProject() {
    currentScene.reset(new QGraphicsScene);
    auto currentProj = controller.getCurrentProject();
    currentScene->addPixmap(currentProj->getImagePixMap());
    updateRouteList();
    ui->picture->setScene(currentScene.get());

}

void MainWindow::addRoute() {
    ui->settingsBox->setEnabled(true);
    ui->routeColorButton->setFlat(false);

    auto color = colorGenerator();
    ui->picture->addRoute(color);
    controller.addNewRouteToCurrentProject(color);

    ui->routeBoxRouteList->moveSelectionTo(ui->routeBoxRouteList->model()->rowCount() - 1);

    auto vBar = ui->routeBoxRouteList->verticalScrollBar();
    vBar->setValue(vBar->maximum());
}

void MainWindow::addRouteNode(int x, int y) {
    refreshSelectedRouteIndex();
    controller.addNewNodeToRoute(x, y, ui->picture->getCurrentRoute()->getColors(), selectedRouteIndex);

    ui->nodeBoxNodeList->moveSelectionTo(ui->nodeBoxNodeList->model()->rowCount() - 1);

    auto vBar = ui->nodeBoxNodeList->verticalScrollBar();
    vBar->setValue(vBar->maximum());
}

void MainWindow::deleteSelectedRoute() {

    if (!ui->routeBoxRouteList->selectionModel()->hasSelection()) {
        return;
    }

    ui->picture->getCurrentRoute()->eraseAllNodes();
    refreshSelectedRouteIndex();
    controller.deleteRouteofCurrentProject(selectedRouteIndex);

    auto newRowCount = ui->routeBoxRouteList->model()->rowCount();
    if (newRowCount != 0) {
        ui->routeBoxRouteList->moveSelectionTo(selectedRouteIndex - (selectedRouteIndex == newRowCount));
    }
}

void MainWindow::createNewProject() {

    QString newFileName = QFileDialog::getSaveFileName(
                this,
                LocalizedUIStrings::getUIString("CREATE_NEW_PROJECT_TITLE"),
                "",
                LocalizedUIStrings::getUIString("PROJECT_FILE_TYPES"));

    if (newFileName.isEmpty()) {
        return;
    }


    QString pictureFileName = QFileDialog::getOpenFileName(
                this,
                LocalizedUIStrings::getUIString("LOAD_IMAGE_FILE"),
                "",
                LocalizedUIStrings::getUIString("QPIXMAP_SUPPORTED_FILE_TYPES"));

    if (!pictureFileName.isEmpty()) {
        controller.addProject(Project(newFileName, pictureFileName));
        setNoProjectsOpenMode(false);
    }
}

void MainWindow::loadProject() {
    QString newFileName = QFileDialog::getOpenFileName(
                this,
                LocalizedUIStrings::getUIString("LOAD_PROJECT_TITLE"),
                "",
                LocalizedUIStrings::getUIString("PROJECT_FILE_TYPES"));

    if (!newFileName.isEmpty()) {
        controller.loadCurrentProjectFromFile(newFileName);
        setNoProjectsOpenMode(false);
        for (const auto &route : controller.getCurrentProject()->getRoutes()) {
            ui->picture->addRoute(route);
        }
    }

}

void MainWindow::saveProject() {
    controller.saveCurrentProject();
}

void MainWindow::saveProjectAs() {
    QString fileName = QFileDialog::getSaveFileName(
                this, LocalizedUIStrings::getUIString("SAVE_PROJECT_AS_TITLE"),
                "",
                LocalizedUIStrings::getUIString("PROJECT_FILE_TYPES"));

    if (!fileName.isEmpty()) {
        controller.saveCurrentProjectAs(fileName);
    }
}


void MainWindow::setNoProjectsOpenMode(bool noProjectsOpen) {
    ui->nodeBox->setEnabled(!noProjectsOpen);
    ui->picture->setEnabled(!noProjectsOpen);
    ui->routeBox->setEnabled(!noProjectsOpen);
    ui->settingsBox->setEnabled(!noProjectsOpen);
    ui->quickButtonMove->setEnabled(!noProjectsOpen);
    ui->quickButtonRedo->setEnabled(!noProjectsOpen);
    ui->quickButtonSave->setEnabled(!noProjectsOpen);
    ui->quickButtonUndo->setEnabled(!noProjectsOpen);
    ui->quickButtonSaveAs->setEnabled(!noProjectsOpen);
    ui->quickButtonAutoAdd->setEnabled(!noProjectsOpen);
    ui->quickButtonSelect->setEnabled(!noProjectsOpen);

    ui->quickButtonNew->setEnabled(true);
    ui->quickButtonOpen->setEnabled(true);
}

void MainWindow::updateRouteList() {
    ui->routeBoxRouteList->setModel(&controller.getCurrentRouteTitles());
}

void MainWindow::updateNodeList() {
    refreshSelectedRouteIndex();

    ui->nodeBoxNodeList->setModel(&controller.getNodeTitlesOfRoute(selectedRouteIndex));
}

void MainWindow::routeSelectionEvent() {
    refreshSelectedRouteIndex();

    ui->routeBoxButtonDeleteRoute->setEnabled(true);
    ui->routeBoxButtonUp->setEnabled(selectedRouteIndex != 0);
    ui->routeBoxButtonDown->setEnabled(selectedRouteIndex != ui->routeBoxRouteList->model()->rowCount() - 1);
    ui->currentRouteBox->setEnabled(true);
    ui->currentNodeBox->setEnabled(true);
    ui->routeColorButton->setFlat(false);

    auto routeData = *(controller.getCurrentProject()->getRoutes()[selectedRouteIndex]);
    ui->routeNameLineEdit->setText(routeData.getName());
    ui->routeColorButton->changeColor(routeData.getColor());
    //shape
    ui->routeNodeOrderCheckBox->setChecked(routeData.getShowOrder());

    updateNodeList();
}

void MainWindow::colorChangeEvent(Data *data) {
    auto color = data->getColor();
    auto newColor = QColorDialog::getColor(color, this);
    if (!newColor.isValid()) {
        return;
    }
    data->setColors(newColor);
    ui->picture->getCurrentRoute()->setColors(newColor);
    ui->routeColorButton->changeColor(newColor);
}

void MainWindow::routeNameChangeEvent(const QString &newName) {
    refreshSelectedRouteIndex();

    (*controller.getCurrentProject())[selectedRouteIndex].setName(newName);
    updateRouteList();
    ui->routeBoxRouteList->moveSelectionTo(selectedRouteIndex);
}

void MainWindow::routeShowOrderChangeEvent(bool value) {
    auto selectedRows = ui->routeBoxRouteList->getSelectedRows();
    if (selectedRows.empty()) {
        return;
    }

    auto selectedRouteIndex = selectedRows[0].row();
    (*controller.getCurrentProject())[selectedRouteIndex].setShowOrder(value);
}

void MainWindow::moveRouteEvent(int by) {
    refreshSelectedRouteIndex();

    controller.swapCurrentProjectRoutes(selectedRouteIndex, selectedRouteIndex + by);
    ui->routeBoxRouteList->moveSelectionTo(selectedRouteIndex + by);
    routeSelectionEvent();
}

void MainWindow::resetSettingsBox() {
    ui->routeBoxButtonUp->setEnabled(false);
    ui->routeBoxButtonDown->setEnabled(false);
    ui->routeBoxButtonDeleteRoute->setEnabled(false);
    ui->nodeBox->setEnabled(false);
    ui->settingsBox->setEnabled(false);
    ui->routeNameLineEdit->clear();
    ui->routeColorButton->setFlat(true);
    ui->routeNodeOrderCheckBox->setChecked(false);
}

void MainWindow::activateAutoAddMode() {
    controller.changeUIState<UIAddNodeState>();

    if (!ui->routeBoxRouteList->selectionModel()->hasSelection() || ui->routeBoxRouteList->model()->rowCount() == 0) {
        addRoute();
    }
}
