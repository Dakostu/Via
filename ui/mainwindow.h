#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "./ui_mainwindow.h"
#include "../controller/mainwindowcontroller.h"
#include "../controller/uistate.h"
#include <vector>
#include <memory>
#include <QMainWindow>
#include <QGraphicsScene>
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
    UIState *currentState;

    std::vector<std::unique_ptr<QAction>> actions;
    std::vector<std::unique_ptr<QMenu>> menus;

    void initializeMenus();
    void initializeShapeSelections();

    template <typename State>
    void changeUIState() {
        qDebug() << "Pressed";

        delete currentState;
        currentState = new State;
        //auto newState = std::make_unique<State>();
        //currentState.swap(*newState);
        currentState->setToggleButtons(ui->quickButtonAutoAdd,
                                       ui->quickButtonMove,
                                       ui->quickButtonSelect);
    }

public:
    MainWindow(QWidget *parent, MainWindowController &newController);
    ~MainWindow();


};
#endif // MAINWINDOW_H
