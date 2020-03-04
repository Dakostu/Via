#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H

#include "routenodeshape.h"
#include "shapekeys.h"
#include <functional>
#include <unordered_map>

namespace Via::Shapes {

class RouteNodeShapeFactory
{

    std::unordered_map<char, std::function<RouteNodeShape*(QPointF, QColor)>> shapeKeyTable;
    std::unordered_map<QString, char> shapeStringKeyTable;

    template<typename Shape>
    RouteNodeShape* generateShape(const QPointF &point, const QColor &color) {
        return new Shape(point, color);
    }

public:
    RouteNodeShapeFactory();
    char getShapeKeyFromUIString(QString key);
    RouteNodeShape* generateNodeShape(char key, const QPointF &point, const QColor &color);
};

}

#endif // SHAPEFACTORY_H
