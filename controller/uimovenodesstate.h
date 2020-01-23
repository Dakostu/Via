#ifndef UIMOVENODESSTATE_H
#define UIMOVENODESSTATE_H

#include "uistate.h"

class UIMoveNodesState : public UIState
{
public:
    virtual void setToggleButtons(QAbstractButton *quickButtonAutoAdd,
                                  QAbstractButton *quickButtonMove,
                                  QAbstractButton *quickButtonSelect) override;
};

#endif // UIMOVENODESSTATE_H
