#include "mainwindowselectnodestate.h"

using namespace Via::UI;

void MainWindowSelectNodeState::setToggleButtons(MainWindow &window) {
    window.getQuickButtonAutoAdd()->setChecked(false);
    window.getQuickButtonMove()->setChecked(false);
    window.getQuickButtonSelect()->setChecked(true);
}
