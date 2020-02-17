#ifndef MAINWINDOWADDNODESTATE_H
#define MAINWINDOWADDNODESTATE_H

#include "mainwindowstate.h"

namespace Via::Control {

class MainWindowAddNodeState : public MainWindowState
{
public:
    void setToggleButtons(Via::UI::MainWindow &window) override;
};

}
#endif // MAINWINDOWADDNODESTATE_H
