#ifndef AUTOMATICALLYSHRINKINGGRAPHICSSCENE_H
#define AUTOMATICALLYSHRINKINGGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <stack>

namespace Via::UI {

class AutomaticallyShrinkingGraphicsScene : public QGraphicsScene
{

    QRectF originalSceneRect;

public:
    AutomaticallyShrinkingGraphicsScene(QObject *parent = nullptr);

    QGraphicsPixmapItem* addPixmap(const QPixmap &pixmap);
    void addItem(QGraphicsItem *item);
    void removeItem(QGraphicsItem *item);
};


}

#endif // AUTOMATICALLYSHRINKINGGRAPHICSSCENE_H
