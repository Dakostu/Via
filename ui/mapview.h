#ifndef MAPVIEW_H
#define MAPVIEW_H

#include "../controller/uistate.h"
#include <memory>
#include <QGraphicsView>

class UIState;

class MapView : public QGraphicsView
{

    qreal currentDetailLevel;
    static constexpr qreal DETAIL_LEVEL_MIN = 0.05;
    static constexpr qreal DETAIL_LEVEL_MAX = 17;
    std::unique_ptr<UIState> *currentState;

public:

    MapView(QWidget *parent);

    void setUIState(std::unique_ptr<UIState> &state);

    void wheelEvent(QWheelEvent *event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

    void triggerParentMouseMoveEvent(QMouseEvent* event);
};

#endif // MAPVIEW_H
