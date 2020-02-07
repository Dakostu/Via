#ifndef UIADDNODESTATE_H
#define UIADDNODESTATE_H

#include "uistate.h"

namespace Via::Control {

class UIAddNodeState : public UIState
{
public:

    void setToggleButtons(QAbstractButton *quickButtonAutoAdd,
                          QAbstractButton *quickButtonMove,
                          QAbstractButton *quickButtonSelect) override;

    void mapViewMouseMoveEvent(Via::UI::MapView *view, QMouseEvent *mouseEvent) override;
    void mapViewMousePressEvent(Via::UI::MapView *view, QMouseEvent *mouseEvent) override;
    void mapViewMouseReleaseEvent(Via::UI::MapView *view, QMouseEvent *mouseEvent) override;
    void mapViewMouseLeaveEvent(Via::UI::MapView *view, QEvent *mouseEvent) override;
};

}
#endif // UIADDNODESTATE_H
