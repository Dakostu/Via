#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "./ui_mainwindow.h"
#include "../controller/mainwindowcontroller.h"
#include <vector>
#include <memory>
#include <QButtonGroup>
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

    std::unique_ptr<QGraphicsScene> currentScene;
    std::unique_ptr<QButtonGroup> quickButtonGroup;

    std::vector<std::unique_ptr<QAction>> actions;
    std::vector<std::unique_ptr<QMenu>> menus;

    void initializeQuickButtons();
    void initializeMenus();
    void initializeShapeSelections();    

public:
    MainWindow(QWidget *parent, MainWindowController &newController);
    ~MainWindow();


};
#endif // MAINWINDOW_H
