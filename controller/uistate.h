#ifndef UISTATE_H
#define UISTATE_H

#include "../shapes/routenode.h"

#include <QAbstractButton>
#include <QDebug>
#include <QGraphicsSceneHoverEvent>

class RouteNode;

class UIState
{

public:

    virtual ~UIState();

    virtual void setToggleButtons(QAbstractButton *quickButtonAutoAdd,
                                  QAbstractButton *quickButtonMove,
                                  QAbstractButton *quickButtonSelect) = 0;   

    virtual void routeNodeMouseHoverEnterEvent(RouteNode *node, QGraphicsSceneHoverEvent *hoverEvent) = 0;


};

#endif // UISTATE_H
