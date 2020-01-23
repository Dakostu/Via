#ifndef UIADDNODESTATE_H
#define UIADDNODESTATE_H

#include "uistate.h"

class UIAddNodeState : public UIState
{
public:

    virtual void setToggleButtons(QAbstractButton *quickButtonAutoAdd,
                                  QAbstractButton *quickButtonMove,
                                  QAbstractButton *quickButtonSelect) override;

};

#endif // UIADDNODESTATE_H
