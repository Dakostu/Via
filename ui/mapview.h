#ifndef MAPVIEW_H
#define MAPVIEW_H

#include "../controller/uistate.h"
#include "../shapes/route.h"
#include "../interfaces/nodeshapeable.h"
#include "../model/routedata.h"
#include <list>
#include <memory>
#include <QGraphicsView>

class UIState;
class RouteNode;
class Route;

class MapView : public QGraphicsView
{
    Q_OBJECT

    qreal currentDetailLevel;
    static constexpr qreal DETAIL_LEVEL_MIN = 0.05;
    static constexpr qreal DETAIL_LEVEL_MAX = 17;
    std::unique_ptr<UIState> *currentState;
    std::list<std::unique_ptr<Route>> drawnRoutes;
    Route* currentRoute;

public:

    MapView(QWidget *parent);

    void setUIState(std::unique_ptr<UIState> &state);

    void wheelEvent(QWheelEvent *event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

    void triggerParentMousePressEvent(QMouseEvent* event);
    void triggerParentMouseMoveEvent(QMouseEvent* event);
    void triggerParentMouseReleaseEvent(QMouseEvent* event);

    void addRoute(const RouteData &route);
    void addRoute(const QColor &color);
    void addNodeToCurrentRoute(int x, int y);

    Route *getCurrentRoute() const;

signals:
    void routeNodeAdded(int x, int y);
};

#endif // MAPVIEW_H
