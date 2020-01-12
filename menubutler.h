#ifndef MENUBUTLER_H
#define MENUBUTLER_H

#include "mainwindow.h"
#include <QObject>

class MenuButler
{
    Q_OBJECT

    MainWindow* ui;
public:
    MenuButler(MainWindow* window);
};

#endif // MENUBUTLER_H
