#include "mainwindowmovenodestate.h"

using namespace Via::UI;

void MainWindowMoveNodeState::setToggleButtons(MainWindow &window) {
    window.getQuickButtonAutoAdd()->setChecked(false);
    window.getQuickButtonMove()->setChecked(true);
    window.getQuickButtonSelect()->setChecked(false);
}
