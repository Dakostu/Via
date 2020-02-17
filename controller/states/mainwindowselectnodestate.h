#ifndef MAINWINDOWSELECTNODESTATE_H
#define MAINWINDOWSELECTNODESTATE_H

#include "mainwindowstate.h"

namespace Via::Control {

class MainWindowSelectNodeState : public MainWindowState
{
public:
    void setToggleButtons(Via::UI::MainWindow *window) override;
};

}

#endif // MAINWINDOWSELECTNODESTATE_H
