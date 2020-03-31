#ifndef MAPVIEWSELECTNODESTATE_H
#define MAPVIEWSELECTNODESTATE_H

#include "mapviewstate.h"

namespace Via::Control {

class MapViewSelectNodeState : public MapViewState
{
public:
    MapViewSelectNodeState() = default;

    void mouseMoveEvent(Via::UI::MapView *view, QMouseEvent *mouseEvent) override;
    void mousePressEvent(Via::UI::MapView *view, QMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(Via::UI::MapView *view, QMouseEvent *mouseEvent) override;
};

}

#endif // MAPVIEWSELECTNODESTATE_H
