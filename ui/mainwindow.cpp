#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QBrush>
#include <QComboBox>
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

#include "../shapes/routenode.h"
#include "../shapes/route.h"
#include "../shapes/octagon.h"
#include "../shapes/routeconnection.h"

#include "../controller/states/mainwindowaddnodestate.h"
#include "../controller/states/mainwindowmovenodestate.h"
#include "../controller/states/mainwindowselectnodestate.h"
#include "../controller/states/mapviewaddnodestate.h"
#include "../controller/states/mapviewmovenodestate.h"
#include "../controller/states/mapviewselectnodestate.h"
#include "../controller/states/routenodeaddnodestate.h"
#include "../controller/states/routenodemovenodestate.h"
#include "../controller/states/routenodeselectnodestate.h"

using namespace Via::UI;
using namespace Via::Control;
using namespace Via::Model;

MainWindow::MainWindow(QWidget *parent, MainWindowController &newController)
    : QMainWindow(parent),
      controller(newController),
      ui(new Ui::MainWindow),
      currentScene(std::make_unique<QGraphicsScene>()),
      quickButtonGroup(std::make_unique<QButtonGroup>()),
      selectedRouteIndex(0),
      selectedRouteNodeIndex(0)
{
    ui->setupUi(this);

    connect(this, &MainWindow::routeListChanged, this, &MainWindow::updateRouteList);
    connect(this, &MainWindow::routeNodeListChanged, this, &MainWindow::updateNodeList);
    connect(&controller, &MainWindowController::currentProjectChanged, this, &MainWindow::getDataFromCurrentProject);
    connect(ui->picture, &MapView::routeNodeAdded, this, &MainWindow::addRouteNode);

    initializeQuickButtons();
    initializeShapeSelections();
    initializeRouteBoxUI();
    initializeRouteSettingsUI();
    initializeNodeBoxUI();
    initializeNodeSettingsUI();

    ui->picture->setUIState(controller.getCurrentMapViewState());
    if (controller.amountOfOpenProjects() == 0) {
        setNoProjectsOpenMode(true);
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}

QAbstractButton* MainWindow::getQuickButtonMove() {
    return ui->quickButtonMove;
}

QAbstractButton* MainWindow::getQuickButtonAutoAdd() {
    return ui->quickButtonAutoAdd;
}

QAbstractButton* MainWindow::getQuickButtonSelect() {
    return ui->quickButtonSelect;
}

void MainWindow::initializeQuickButtons() {

    connect(ui->quickButtonOpen, &QPushButton::clicked, this, &MainWindow::loadProject);
    connect(ui->quickButtonSave, &QPushButton::clicked, this, &MainWindow::saveProject);
    connect(ui->quickButtonSaveAs, &QPushButton::clicked, this, &MainWindow::saveProjectAs);

    controller.getCurrentMainWindowState()->setToggleButtons(this);
    quickButtonGroup->addButton(ui->quickButtonAutoAdd);
    quickButtonGroup->addButton(ui->quickButtonMove);
    quickButtonGroup->addButton(ui->quickButtonSelect);
    connect(ui->quickButtonNew, &QPushButton::clicked, this, &MainWindow::createNewProject);
    connect(ui->quickButtonAutoAdd, &QAbstractButton::clicked, this, &MainWindow::activateAutoAddMode);
    connect(ui->quickButtonMove, &QAbstractButton::clicked, this, [&]() {
        ui->picture->removeTemporaryNode();
        controller.changeUIStates<MainWindowMoveNodeState, MapViewMoveNodeState, RouteNodeMoveNodeState>();
    });
    connect(ui->quickButtonSelect, &QAbstractButton::clicked, this, [&]() {
        ui->picture->removeTemporaryNode();
        controller.changeUIStates<MainWindowSelectNodeState, MapViewSelectNodeState, RouteNodeSelectNodeState>();
    });
}

void MainWindow::initializeShapeSelections() {
    QStringList availableStyles({LocalizedUIStrings::getUIString("SQUARE"),
                                 LocalizedUIStrings::getUIString("TRIANGLE_UP"),
                                 LocalizedUIStrings::getUIString("TRIANGLE_DOWN"),
                                 LocalizedUIStrings::getUIString("DIAMOND"),
                                 LocalizedUIStrings::getUIString("OCTAGON"),
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
        auto lineEditText = (dynamic_cast<QLineEdit*>(lineEdit))->text();
        auto &currentRoute = controller.getRouteOfCurrentProject(selectedRouteIndex);
        nameChangeEvent<RouteAction>(&currentRoute, lineEditText, std::bind(&MainWindow::updateRouteList, this));
    });
    connect(ui->routeBoxRouteList, &RouteDataView::changedSelection, this, &MainWindow::routeSelectionEvent);
}

void MainWindow::initializeNodeBoxUI() {
    connect(ui->nodeBoxButtonAddNode, &QPushButton::clicked, this, [&]() {
        ui->quickButtonAutoAdd->click();
        QCursor::setPos(this->pos() + ui->pictureLayout->geometry().center());
    });
    connect(ui->nodeBoxButtonDeleteNode, &QPushButton::clicked, this, &MainWindow::deleteSelectedRouteNode);
    connect(ui->nodeBoxButtonUp, &QPushButton::clicked, this, [&]() { moveNodeEvent(-1); });
    connect(ui->nodeBoxButtonDown, &QPushButton::clicked, this, [&]() { moveNodeEvent(1); });
    connect(ui->nodeBoxNodeList->itemDelegate(), &QAbstractItemDelegate::commitData, this, [&](QWidget* lineEdit){
        auto lineEditText = (dynamic_cast<QLineEdit*>(lineEdit))->text();
        auto &currentRouteNode = controller.getRouteNodeofCurrentProject(selectedRouteIndex, selectedRouteNodeIndex);
        nameChangeEvent<NodeAction>(&currentRouteNode, lineEditText, std::bind(&MainWindow::updateNodeList, this));
    });
    connect(ui->nodeBoxNodeList, &RouteDataView::changedSelection, this, &MainWindow::routeNodeSelectionEvent);
}

void MainWindow::initializeNodeSettingsUI() {

    connect(ui->nodeColorButton, &QPushButton::pressed, this, [&]() {
        auto currentRoute = ui->picture->getCurrentRoute();
        auto oldColor = (*currentRoute)[selectedRouteNodeIndex].getColors();
        colorChangeEvent<NodeAction>(oldColor);
    });
    connect(ui->nodeNameLineEdit, &QLineEdit::textEdited, this, [&](const QString &newName) {
        nameChangeEvent<NodeAction>(&(controller.getRouteNodeofCurrentProject(selectedRouteIndex, selectedRouteNodeIndex)),
                            newName, std::bind(&MainWindow::updateNodeList, this));
    });

    connect(ui->nodeLabelLineEdit, &QLineEdit::textEdited, this, &MainWindow::changeNodeExtraLabel);
    connect(ui->nodeStyleComboBox, &QComboBox::currentTextChanged, this, [&](const QString &newStyle) {
        styleChangeEvent<NodeAction>(newStyle);
    });


}

void MainWindow::initializeRouteSettingsUI() {
    connect(ui->routeColorButton, &QPushButton::pressed, this, [&]() {
        auto oldColor = ui->picture->getCurrentRoute()->getColors();
        colorChangeEvent<RouteAction>(oldColor);
    });
    connect(ui->routeNameLineEdit, &QLineEdit::textEdited, this, [&](const QString &newName) {
        nameChangeEvent<RouteAction>(&controller.getRouteOfCurrentProject(selectedRouteIndex),
                                     newName, std::bind(&MainWindow::updateRouteList, this));
    });
    connect(ui->routeStyleComboBox, &QComboBox::currentTextChanged, this, [&](const QString &newStyle) {
        styleChangeEvent<RouteAction>(newStyle);
    });
    connect(ui->routeNodeOrderCheckBox, &QCheckBox::toggled, this, &MainWindow::routeShowOrderChangeEvent);
}

void MainWindow::getDataFromCurrentProject() {
    currentScene.reset(new QGraphicsScene);
    auto currentProj = controller.getCurrentProject();
    currentScene->addPixmap(currentProj->getImagePixMap());    
    ui->picture->setScene(currentScene.get());

}

void MainWindow::addRoute() {
    ui->settingsBox->setEnabled(true);
    ui->routeColorButton->setFlat(false);

    auto color = colorGenerator();

    ui->picture->addRoute(color, ui->routeStyleComboBox->currentText(), controller.getCurrentRouteNodeState());
    controller.getCurrentProject()->addRoute(*ui->picture->getCurrentRoute());

    emit routeListChanged();

    auto newSelectedRow = static_cast<size_t>(ui->routeBoxRouteList->model()->rowCount() - 1);
    ui->routeBoxRouteList->moveSelectionTo(newSelectedRow);

    auto vBar = ui->routeBoxRouteList->verticalScrollBar();
    vBar->setValue(vBar->maximum());

}

void MainWindow::deleteSelectedRoute() {
    if (!ui->routeBoxRouteList->selectionModel()->hasSelection()) {
        return;
    }

    ui->picture->getCurrentRoute()->eraseAllNodes();

    emit routeListChanged();

    auto newRowCount = ui->routeBoxRouteList->model()->rowCount();
    if (newRowCount != 0) {
        ui->routeBoxRouteList->moveSelectionTo(selectedRouteIndex - (selectedRouteIndex == static_cast<size_t>(newRowCount)));
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
        for (const auto JSONRouteRef : controller.getCurrentProject()->getRoutesJSON()) {
            auto JSONRoute = JSONRouteRef.toObject();
            auto &currentNodeState = controller.getCurrentRouteNodeState();
            auto newRoute = new Route(JSONRoute, currentScene.get(), currentNodeState);
            ui->picture->addRoute(newRoute, currentNodeState);
            controller.getCurrentProject()->addRoute(*newRoute);
        }
        updateRouteList();

        if (ui->nodeBoxNodeList->model() && ui->nodeBoxNodeList->model()->rowCount() > 0) {
            ui->nodeBoxNodeList->removeAllRows();
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
    if (ui->routeBoxRouteList->model()->rowCount() == 0) {
        resetSettingsBox();
    }
}

void MainWindow::updateNodeList() {
    ui->nodeBoxNodeList->setModel(&controller.getNodeTitlesOfRoute(selectedRouteIndex));

    setNodeSettingsEnabled(ui->nodeBoxNodeList->model()->rowCount() != 0);
}

void MainWindow::routeSelectionEvent() {
    refreshIndex<RouteIndex>();

    auto lastRow = static_cast<size_t>(ui->routeBoxRouteList->model()->rowCount() - 1);
    ui->routeBoxButtonDeleteRoute->setEnabled(true);
    ui->routeBoxButtonUp->setEnabled(selectedRouteIndex != 0);
    ui->routeBoxButtonDown->setEnabled(selectedRouteIndex != lastRow);
    ui->currentRouteBox->setEnabled(true);
    ui->routeColorButton->setFlat(false);

    ui->nodeBox->setEnabled(true);

    auto &currentRoute = controller.getRouteOfCurrentProject(selectedRouteIndex);
    ui->routeNameLineEdit->setText(currentRoute.getName());
    ui->routeColorButton->changeColor(currentRoute.getColors());
    ui->routeStyleComboBox->setCurrentText(currentRoute.getRouteStyleAsUIString());
    ui->routeNodeOrderCheckBox->setChecked(currentRoute.getShowOrder());

    ui->picture->setCurrentRoute(selectedRouteIndex);

    updateNodeList();
}

void MainWindow::routeNodeSelectionEvent() {
    refreshIndex<RouteNodeIndex>();

    auto lastRow = static_cast<size_t>(ui->nodeBoxNodeList->model()->rowCount() - 1);
    ui->nodeBoxButtonDeleteNode->setEnabled(true);
    ui->nodeBoxButtonUp->setEnabled(selectedRouteNodeIndex != 0);
    ui->nodeBoxButtonDown->setEnabled(selectedRouteNodeIndex != lastRow);
    setNodeSettingsEnabled(true);

    auto &currentRouteNode = controller.getRouteNodeofCurrentProject(selectedRouteIndex, selectedRouteNodeIndex);
    ui->nodeNameLineEdit->setText(currentRouteNode.getName());
    ui->nodeLabelLineEdit->setText(currentRouteNode.getExtraLabel()->text());
    ui->nodeStyleComboBox->setCurrentText(ui->picture->getCurrentRoute()->getRouteNodeStyleAsUIString(selectedRouteNodeIndex));
    ui->nodeColorButton->changeColor(currentRouteNode.getColors());

}


void MainWindow::routeShowOrderChangeEvent(bool value) {
    ui->picture->getCurrentRoute()->setShowOrder(value);
}

void MainWindow::moveRouteEvent(int by) {
    auto newRouteIndex = selectedRouteIndex + by;

    controller.swapRoutesOfCurrentProject(selectedRouteIndex, newRouteIndex);

    emit routeListChanged();

    ui->routeBoxRouteList->moveSelectionTo(newRouteIndex);
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
    controller.changeUIStates<MainWindowAddNodeState, MapViewAddNodeState, RouteNodeAddNodeState>();

    if (!ui->routeBoxRouteList->selectionModel()->hasSelection() || ui->routeBoxRouteList->model()->rowCount() == 0) {
        addRoute();
    }
}

void MainWindow::addRouteNode() {
    selectedRouteNodeIndex = ui->nodeBoxNodeList->model()->rowCount();

    auto &newNode = controller.getRouteNodeofCurrentProject(selectedRouteIndex, selectedRouteNodeIndex);
    auto &currentRoute = controller.getRouteOfCurrentProject(selectedRouteIndex);
    newNode.setName(LocalizedUIStrings::getUIString("NODE_DEFAULT_NAME").arg(currentRoute.size()));

    emit routeNodeListChanged();

    auto vBar = ui->nodeBoxNodeList->verticalScrollBar();
    vBar->setValue(vBar->maximum());

    ui->nodeBoxNodeList->moveSelectionTo(static_cast<size_t>(ui->nodeBoxNodeList->model()->rowCount() - 1));
}

void MainWindow::deleteSelectedRouteNode() {
    if (!ui->routeBoxRouteList->selectionModel()->hasSelection()) {
        return;
    }

    ui->picture->getCurrentRoute()->eraseNode(selectedRouteNodeIndex);

    emit routeNodeListChanged();

    auto newRowCount = static_cast<size_t>(ui->nodeBoxNodeList->model()->rowCount());
    if (newRowCount != 0) {
        ui->nodeBoxNodeList->moveSelectionTo(selectedRouteNodeIndex - (selectedRouteNodeIndex == newRowCount));
    }
}

void MainWindow::setNodeSettingsEnabled(bool enabled) {
    ui->currentNodeBox->setEnabled(enabled);
    ui->nodeColorButton->setFlat(!enabled);
    if (!enabled) {
        ui->nodeNameLineEdit->setText("");
        ui->nodeLabelLineEdit->setText("");
    }
}

void MainWindow::moveNodeEvent(int by) {
    ui->picture->getCurrentRoute()->swapNodes(selectedRouteNodeIndex, selectedRouteNodeIndex + by);

    emit routeNodeListChanged();

    ui->nodeBoxNodeList->moveSelectionTo(selectedRouteNodeIndex + by);
}

void MainWindow::changeNodeExtraLabel(const QString &text) {
    auto &currentRouteNode = controller.getRouteNodeofCurrentProject(selectedRouteIndex, selectedRouteNodeIndex);
    currentRouteNode.setExtraLabelText(text);
}
