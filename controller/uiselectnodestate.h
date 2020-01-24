#ifndef UISELECTNODESTATE_H
#define UISELECTNODESTATE_H

#include "uistate.h"

class UISelectNodeState : public UIState
{
public:
    virtual void setToggleButtons(QAbstractButton *quickButtonAutoAdd,
                                  QAbstractButton *quickButtonMove,
                                  QAbstractButton *quickButtonSelect) override;

    virtual void routeNodeMouseHoverEnterEvent(RouteNode *node, QGraphicsSceneHoverEvent *hoverEvent) override;
};

#endif // UISELECTNODESTATE_H
