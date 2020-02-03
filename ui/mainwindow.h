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
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

    MainWindowController &controller;
    Ui::MainWindow *ui;

    ColorGenerator colorGenerator;
    std::unique_ptr<QGraphicsScene> currentScene;
    std::unique_ptr<QButtonGroup> quickButtonGroup;

    std::vector<std::unique_ptr<QAction>> actions;
    std::vector<std::unique_ptr<QMenu>> menus;

    int selectedRouteIndex;

    void initializeQuickButtons();
    void initializeMenus();
    void initializeShapeSelections();
    void initializeRouteBoxUI();
    void initializeRouteSettingsUI();
    void initializeNodeBoxUI();
    void initializeNodeSettingsUI();

    void refreshSelectedRouteIndex();

public:
    MainWindow(QWidget *parent, MainWindowController &newController);
    ~MainWindow();

public slots:
    void addRoute();
    void addRouteNode(int x, int y);
    void deleteSelectedRoute();
    void createNewProject();
    void loadProject();
    void saveProject();
    void saveProjectAs();
    void setNoProjectsOpenMode(bool noProjectsOpen);
    void updateRouteList();
    void updateNodeList();
    void routeSelectionEvent();
    void colorChangeEvent(Data *data);
    void routeNameChangeEvent(const QString &newName);
    void routeShowOrderChangeEvent(bool value);
    void moveRouteEvent(int by);
    void getDataFromCurrentProject();
    void resetSettingsBox();
    void activateAutoAddMode();



};
#endif // MAINWINDOW_H
