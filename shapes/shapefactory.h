#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H

#include "routenodeshape.h"
#include "shapekeys.h"
#include <functional>
#include <unordered_map>

namespace Via::Shapes {

class ShapeFactory
{

    std::unordered_map<char, std::function<RouteNodeShape*(int, int, QColor)>> shapeKeyTable;
    std::unordered_map<QString, std::function<RouteNodeShape*(int, int, QColor)>> shapeUIStringTable;

    template<typename Shape>
    RouteNodeShape* generateShape(int x, int y, const QColor &color) {
        return new Shape(x, y, color);
    }

public:
    ShapeFactory();
    RouteNodeShape* generateNodeShape(char key, int x, int y, const QColor &color);
    RouteNodeShape* generateNodeShape(const QString &key, int x, int y, const QColor &color);
};

}

#endif // SHAPEFACTORY_H
