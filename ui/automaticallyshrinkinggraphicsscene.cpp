#include "automaticallyshrinkinggraphicsscene.h"

using namespace Via::UI;

AutomaticallyShrinkingGraphicsScene::AutomaticallyShrinkingGraphicsScene(QObject *parent) : QGraphicsScene(parent)
{

}

QGraphicsPixmapItem* AutomaticallyShrinkingGraphicsScene::addPixmap(const QPixmap &pixmap) {
    originalSceneRect = pixmap.rect();
    return QGraphicsScene::addPixmap(pixmap);
}


void AutomaticallyShrinkingGraphicsScene::addItem(QGraphicsItem *item) {
    QGraphicsScene::addItem(item);
    setSceneRect(originalSceneRect);
}


void AutomaticallyShrinkingGraphicsScene::removeItem(QGraphicsItem *item) {
    QGraphicsScene::removeItem(item);    
    setSceneRect(originalSceneRect);
}
