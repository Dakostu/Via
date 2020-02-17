#ifndef MAINWINDOWMOVENODESTATE_H
#define MAINWINDOWMOVENODESTATE_H

#include "mainwindowstate.h"

namespace Via::Control {

class MainWindowMoveNodeState : public MainWindowState
{
public:
    void setToggleButtons(Via::UI::MainWindow *window) override;
};

}
#endif // MAINWINDOWMOVENODESTATE_H
