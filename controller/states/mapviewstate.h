#ifndef MAPVIEWSTATE_H
#define MAPVIEWSTATE_H

#include "../../ui/mapview.h"

namespace Via::Control {

class MapViewState : public UIState
{
protected:
    MapViewState();

public:
    virtual ~MapViewState();

    virtual void mouseMoveEvent(Via::UI::MapView &view, QMouseEvent *mouseEvent);
    virtual void mousePressEvent(Via::UI::MapView &view, QMouseEvent *mouseEvent);
    virtual void mouseReleaseEvent(Via::UI::MapView &view, QMouseEvent *mouseEvent);
    virtual void mouseLeaveEvent(Via::UI::MapView &view, QEvent *mouseEvent);
};

}
#endif // MAPVIEWSTATE_H
