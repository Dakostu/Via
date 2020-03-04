#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "colorgenerator.h"
#include "./ui_mainwindow.h"
#include "../controller/mainwindowcontroller.h"
#include "../model/data.h"
#include <vector>
#include <memory>
#include <QButtonGroup>
#include <QColorDialog>
#include <QGraphicsScene>
#include <QListView>
#include <QMainWindow>
#include <QToolButton>
#include <type_traits>


QT_BEGIN_NAMESPACE
using namespace Via::UI;
using namespace Via::Model;
using namespace Via::Shapes;
using namespace Via::Control;
using namespace Via::Structures;
using namespace Via::Interfaces;
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

namespace Via::UI {

class MainWindow : public QMainWindow
{

    struct NodeAction : std::integral_constant<bool, true> {};
    struct RouteAction : std::integral_constant<bool, false> {};

    Q_OBJECT

    Via::Control::MainWindowController &controller;
    Ui::MainWindow *ui;

    ColorGenerator colorGenerator;
    std::unique_ptr<QGraphicsScene> currentScene;
    std::unique_ptr<QButtonGroup> quickButtonGroup;

    std::vector<std::unique_ptr<QAction>> actions;

    int selectedRouteIndex;
    int selectedRouteNodeIndex;

    void initializeQuickButtons();
    void initializeShapeSelections();
    void initializeRouteBoxUI();
    void initializeRouteSettingsUI();
    void initializeNodeBoxUI();
    void initializeNodeSettingsUI();

    void refreshSelectedRouteIndex();
    void refreshSelectedRouteNodeIndex();

public:
    MainWindow(QWidget *parent, Via::Control::MainWindowController &newController);
    ~MainWindow();

    QAbstractButton* getQuickButtonMove();
    QAbstractButton* getQuickButtonAutoAdd();
    QAbstractButton* getQuickButtonSelect();

    template <typename OnlyNode>
    void dataStyleChangeEvent(const QString &newStyle) {
        auto &currentRoute = *ui->picture->getCurrentRoute();

        if constexpr (OnlyNode::value == true) {
            currentRoute.setStyleOfNode(selectedRouteNodeIndex, newStyle);

            auto &currentNode = currentRoute[selectedRouteNodeIndex];
            auto newShapeKey = currentNode.getShapeKey();
            auto isDifferentNow = currentNode.getStyleDiffersFromRoute();
            controller.setStyleOfCurrentRouteNode(selectedRouteIndex, selectedRouteNodeIndex, newShapeKey, isDifferentNow);
        } else {
            currentRoute.setShapeKey(newStyle);
            (*controller.getCurrentProject())[selectedRouteIndex].setShapeKey(currentRoute.getShapeKey());
        }
    }


    template <typename OnlyNode>
    void colorChangeEvent(const QColor &oldColor) {
        auto newColor = QColorDialog::getColor(oldColor, this);
        if (!newColor.isValid()) {
            return;
        }
        auto &currentRoute = *ui->picture->getCurrentRoute();

        if constexpr (OnlyNode::value == true) {
            currentRoute.setColorsOfNode(selectedRouteNodeIndex, newColor);
            ui->nodeColorButton->changeColor(newColor);

            auto &currentNode = currentRoute[selectedRouteNodeIndex];
            auto isDifferentNow = currentNode.getStyleDiffersFromRoute();
            controller.setColorOfCurrentRouteNode(selectedRouteIndex, selectedRouteNodeIndex, newColor, isDifferentNow);
        } else {
            currentRoute.setColors(newColor);
            ui->routeColorButton->changeColor(newColor);
            controller.setColorOfCurrentRoute(selectedRouteIndex, newColor);
        }
        if (!ui->nodeColorButton->isFlat()) {
            auto currentSelectedNode = (*controller.getCurrentProject())[selectedRouteIndex][selectedRouteNodeIndex];
            ui->nodeColorButton->changeColor(currentSelectedNode.getColor());
        }
    }



public slots:
    void addRoute();    
    void deleteSelectedRoute();
    void createNewProject();
    void loadProject();
    void saveProject();
    void saveProjectAs();
    void setNoProjectsOpenMode(bool noProjectsOpen);
    void updateRouteList();
    void updateNodeList();
    void routeSelectionEvent();
    void routeNodeSelectionEvent();    
    void dataNameChangeEvent(Via::Model::Data &data, const QString &newName, std::function<void(void)> listUpdateFunc);
    void routeShowOrderChangeEvent(bool value);
    void moveRouteEvent(int by);
    void getDataFromCurrentProject();
    void resetSettingsBox();
    void activateAutoAddMode();
    void addRouteNode(int x, int y);
    void deleteSelectedRouteNode();
    void setNodeSettingsEnabled(bool enabled);
    void moveNodeEvent(int by);

};

}
#endif // MAINWINDOW_H
