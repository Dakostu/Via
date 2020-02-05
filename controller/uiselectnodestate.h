#ifndef UISELECTNODESTATE_H
#define UISELECTNODESTATE_H

#include "uistate.h"

class UISelectNodeState : public UIState
{
public:
    void setToggleButtons(QAbstractButton *quickButtonAutoAdd,
                          QAbstractButton *quickButtonMove,
                          QAbstractButton *quickButtonSelect) override;

    void mapViewMouseMoveEvent(MapView *view, QMouseEvent *mouseEvent) override;
    void mapViewMousePressEvent(MapView *view, QMouseEvent *mouseEvent) override;
    void mapViewMouseReleaseEvent(MapView *view, QMouseEvent *mouseEvent) override;
};

#endif // UISELECTNODESTATE_H
