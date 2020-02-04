#ifndef UIADDNODESTATE_H
#define UIADDNODESTATE_H

#include "uistate.h"

class UIAddNodeState : public UIState
{
public:

    virtual void setToggleButtons(QAbstractButton *quickButtonAutoAdd,
                                  QAbstractButton *quickButtonMove,
                                  QAbstractButton *quickButtonSelect) override;

    virtual void mapViewMouseMoveEvent(MapView *view, QMouseEvent *mouseEvent) override;
    virtual void mapViewMousePressEvent(MapView *view, QMouseEvent *mouseEvent) override;
    virtual void mapViewMouseReleaseEvent(MapView *view, QMouseEvent *mouseEvent) override;
};

#endif // UIADDNODESTATE_H
