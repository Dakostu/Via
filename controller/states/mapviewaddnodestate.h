#ifndef MAPVIEWADDNODESTATE_H
#define MAPVIEWADDNODESTATE_H

#include "mapviewstate.h"

namespace Via::Control {

class MapViewAddNodeState : public MapViewState
{
public:
    MapViewAddNodeState();

    void mouseMoveEvent(Via::UI::MapView &view, QMouseEvent *mouseEvent) override;
    void mousePressEvent(Via::UI::MapView &view, QMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(Via::UI::MapView &view, QMouseEvent *mouseEvent) override;
    void mouseLeaveEvent(Via::UI::MapView &view, QEvent *mouseEvent) override;
};

}

#endif // MAPVIEWADDNODESTATE_H
