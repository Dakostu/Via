#ifndef MAPVIEW_H
#define MAPVIEW_H
#include <QGraphicsView>

class MapView : public QGraphicsView
{

    qreal currentDetailLevel;
    static constexpr qreal DETAIL_LEVEL_MIN = 0.05;
    static constexpr qreal DETAIL_LEVEL_MAX = 17;
public:

    MapView(QWidget *parent);

    void wheelEvent(QWheelEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
};

#endif // MAPVIEW_H
