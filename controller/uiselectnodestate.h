#ifndef UISELECTNODESTATE_H
#define UISELECTNODESTATE_H

#include "uistate.h"

class UISelectNodeState : public UIState
{
public:
    virtual void setToggleButtons(QAbstractButton *quickButtonAutoAdd,
                                  QAbstractButton *quickButtonMove,
                                  QAbstractButton *quickButtonSelect) override;

    virtual void mapViewMouseMoveEvent(MapView *view, QMouseEvent *mouseEvent) override;
    virtual void mapViewMousePressEvent(MapView *view, QMouseEvent *mouseEvent) override;
    virtual void mapViewMouseReleaseEvent(MapView *view, QMouseEvent *mouseEvent) override;
};

#endif // UISELECTNODESTATE_H
