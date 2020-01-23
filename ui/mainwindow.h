#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "../controller/mainwindowcontroller.h"
#include <vector>
#include <memory>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QToolButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

    MainWindowController &controller;

public:
    MainWindow(QWidget *parent, MainWindowController &newController);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    std::unique_ptr<QGraphicsScene> currentScene;

    std::vector<std::unique_ptr<QAction>> actions;
    std::vector<std::unique_ptr<QMenu>> menus;

    void initializeMenus();
    void initializeShapeSelections();

};
#endif // MAINWINDOW_H
