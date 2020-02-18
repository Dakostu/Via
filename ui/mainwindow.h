#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "colorgenerator.h"
#include "./ui_mainwindow.h"
#include "../controller/mainwindowcontroller.h"
#include <vector>
#include <memory>
#include <QButtonGroup>
#include <QListView>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QToolButton>

#include <QDebug>

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
    Q_OBJECT

    Via::Control::MainWindowController &controller;
    Ui::MainWindow *ui;

    ColorGenerator colorGenerator;
    std::unique_ptr<QGraphicsScene> currentScene;
    std::unique_ptr<QButtonGroup> quickButtonGroup;

    std::vector<std::unique_ptr<QAction>> actions;
    std::vector<std::unique_ptr<QMenu>> menus;

    int selectedRouteIndex;
    int selectedRouteNodeIndex;

    void initializeQuickButtons();
    void initializeMenus();
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
    void colorChangeEvent(Via::Model::Data *data);
    void routeNameChangeEvent(const QString &newName);
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
