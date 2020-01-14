#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
#include <memory>
#include <QMainWindow>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);    
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    std::unique_ptr<QGraphicsScene> currentScene;

    std::vector<std::unique_ptr<QAction>> actions;
    std::vector<std::unique_ptr<QMenu>> menus;

    void initializeMenus();

};
#endif // MAINWINDOW_H
