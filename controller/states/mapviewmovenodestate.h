#ifndef MAPVIEWMOVENODESTATE_H
#define MAPVIEWMOVENODESTATE_H

#include "mapviewstate.h"

namespace Via::Control {

class MapViewMoveNodeState : public MapViewState
{
    static constexpr int BORDER_MOVE_PUFFER = 1;
public:
    MapViewMoveNodeState() = default;

    void mouseMoveEvent(Via::UI::MapView *view, QMouseEvent *mouseEvent) override;
    void mousePressEvent(Via::UI::MapView *view, QMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(Via::UI::MapView *view, QMouseEvent *mouseEvent) override;
};

}

#endif // MAPVIEWMOVENODESTATE_H
