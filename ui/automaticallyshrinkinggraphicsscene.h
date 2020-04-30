#ifndef AUTOMATICALLYSHRINKINGGRAPHICSSCENE_H
#define AUTOMATICALLYSHRINKINGGRAPHICSSCENE_H

#include <QGraphicsScene>

namespace Via::UI {

class AutomaticallyShrinkingGraphicsScene : public QGraphicsScene
{
public:
    AutomaticallyShrinkingGraphicsScene(QObject *parent = nullptr);
};


}

#endif // AUTOMATICALLYSHRINKINGGRAPHICSSCENE_H
