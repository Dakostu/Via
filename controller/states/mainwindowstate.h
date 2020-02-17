#ifndef MAINWINDOWSTATE_H
#define MAINWINDOWSTATE_H

#include "../../ui/mainwindow.h"
#include <QAbstractButton>

namespace Via::Control {

class MainWindowState : public UIState
{
protected:
    MainWindowState();
public:    
    virtual ~MainWindowState();

    virtual void setToggleButtons(Via::UI::MainWindow &window);

};

}

#endif // MAINWINDOWSTATE_H
