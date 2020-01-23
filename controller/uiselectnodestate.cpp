#include "uiselectnodestate.h"


void UISelectNodeState::setToggleButtons(QAbstractButton *quickButtonAutoAdd, QAbstractButton *quickButtonMove, QAbstractButton *quickButtonSelect) {
    quickButtonAutoAdd->setChecked(false);
    quickButtonMove->setChecked(false);
    quickButtonSelect->setChecked(true);
}
