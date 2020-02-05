#ifndef UIADDNODESTATE_H
#define UIADDNODESTATE_H

#include "uistate.h"

class UIAddNodeState : public UIState
{
public:

    void setToggleButtons(QAbstractButton *quickButtonAutoAdd,
                          QAbstractButton *quickButtonMove,
                          QAbstractButton *quickButtonSelect) override;

    void mapViewMouseMoveEvent(MapView *view, QMouseEvent *mouseEvent) override;
    void mapViewMousePressEvent(MapView *view, QMouseEvent *mouseEvent) override;
    void mapViewMouseReleaseEvent(MapView *view, QMouseEvent *mouseEvent) override;
    void mapViewMouseLeaveEvent(MapView *view, QEvent *mouseEvent) override;
};

#endif // UIADDNODESTATE_H
