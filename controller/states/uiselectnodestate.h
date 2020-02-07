#ifndef UISELECTNODESTATE_H
#define UISELECTNODESTATE_H

#include "uistate.h"

namespace Via::Control {

class UISelectNodeState : public UIState
{
public:
    void setToggleButtons(QAbstractButton *quickButtonAutoAdd,
                          QAbstractButton *quickButtonMove,
                          QAbstractButton *quickButtonSelect) override;

    void mapViewMouseMoveEvent(Via::UI::MapView *view, QMouseEvent *mouseEvent) override;
    void mapViewMousePressEvent(Via::UI::MapView *view, QMouseEvent *mouseEvent) override;
    void mapViewMouseReleaseEvent(Via::UI::MapView *view, QMouseEvent *mouseEvent) override;
};

}

#endif // UISELECTNODESTATE_H
