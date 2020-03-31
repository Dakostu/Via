#ifndef MAPVIEW_H
#define MAPVIEW_H

#include "../data-structures/indexlist.h"
#include "../controller/states/mapviewstate.h"
#include "../controller/states/routenodestate.h"
#include "../shapes/route.h"
#include "../shapes/routenodeshape.h"
#include "../model/routedata.h"
#include <list>
#include <memory>
#include <QGraphicsView>

namespace Via::Control {
    class UIState;
}

namespace Via::UI {

class MapView : public QGraphicsView
{
    Q_OBJECT

    qreal currentDetailLevel;
    static constexpr qreal DETAIL_LEVEL_MIN = 0.05;
    static constexpr qreal DETAIL_LEVEL_MAX = 17;
    std::unique_ptr<Via::Control::MapViewState> *currentState;
    Via::Structures::IndexList<std::unique_ptr<Via::Shapes::Route>> drawnRoutes;
    Via::Shapes::Route* currentRoute;    

public:

    MapView(QWidget *parent);

    void setUIState(std::unique_ptr<Via::Control::MapViewState> &state);

    void wheelEvent(QWheelEvent *event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

    bool viewportEvent(QEvent *event) override;

    void triggerParentMousePressEvent(QMouseEvent* event);
    void triggerParentMouseMoveEvent(QMouseEvent* event);
    void triggerParentMouseReleaseEvent(QMouseEvent* event);

    void addRoute(const Via::Model::RouteData &route, std::unique_ptr<Via::Control::RouteNodeState> &routeNodeState);
    void addRoute(const QColor &color, const QString &selectedStyle, std::unique_ptr<Via::Control::RouteNodeState> &routeNodeState);
    void addRoute(const QColor &color, char selectedStyle, std::unique_ptr<Via::Control::RouteNodeState> &routeNodeState);
    void addNodeToCurrentRoute(int x, int y);
    void removeTemporaryNode();

    Via::Shapes::Route *getCurrentRoute() const;
    void setCurrentRoute(size_t routeIndex);

signals:
    void routeNodeAdded(int x, int y);
};

}

#endif // MAPVIEW_H
