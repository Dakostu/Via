#ifndef UIADDNODESTATE_H
#define UIADDNODESTATE_H

#include "uistate.h"

class UIAddNodeState : public UIState
{
public:

    virtual void setToggleButtons(QAbstractButton *quickButtonAutoAdd,
                                  QAbstractButton *quickButtonMove,
                                  QAbstractButton *quickButtonSelect) override;

    virtual void routeNodeMouseHoverEnterEvent(RouteNode *node, QGraphicsSceneHoverEvent *hoverEvent) override;

};

#endif // UIADDNODESTATE_H
