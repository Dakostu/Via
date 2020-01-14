#ifndef MAPVIEW_H
#define MAPVIEW_H
#include <QGraphicsView>

class MapView : public QGraphicsView
{

public:

    MapView(QWidget *parent);

    void wheelEvent(QWheelEvent *event) override;
};

#endif // MAPVIEW_H
