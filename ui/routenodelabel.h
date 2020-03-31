#ifndef ROUTENODELABEL_H
#define ROUTENODELABEL_H

#include "../interfaces/viewcustomizable.h"
#include <QGraphicsSimpleTextItem>

namespace Via::UI {

class RouteNodeLabel : public QGraphicsSimpleTextItem, public Via::Interfaces::ViewCustomizable
{
protected:
    static constexpr auto FONT_SIZE_SHRINKAGE_FACTOR = 2.0;
    static constexpr auto FONT_SIZE_OFFSET = 7;

public:
    RouteNodeLabel(const QString &text);

    void setElementSize(int newSize) override;
    void setColors(const QColor &color) override;
    void activateColors() override;


};

}

#endif // ROUTENODELABEL_H
