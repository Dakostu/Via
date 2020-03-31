#ifndef MAPVIEWSTATE_H
#define MAPVIEWSTATE_H

#include "uistate.h"
#include <QMouseEvent>

namespace Via::UI {
class MapView;
}

namespace Via::Control {

class MapViewState : public UIState
{
protected:
    MapViewState() = default;

public:
    virtual ~MapViewState() = default;

    virtual void mouseMoveEvent(Via::UI::MapView *view, QMouseEvent *mouseEvent);
    virtual void mousePressEvent(Via::UI::MapView *view, QMouseEvent *mouseEvent);
    virtual void mouseReleaseEvent(Via::UI::MapView *view, QMouseEvent *mouseEvent);
    virtual void mouseLeaveEvent(Via::UI::MapView *view, QEvent *mouseEvent);
};

}
#endif // MAPVIEWSTATE_H
