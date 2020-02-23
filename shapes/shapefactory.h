#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H

#include "../interfaces/routenodeshape.h"
#include "shapekeys.h"
#include <functional>
#include <unordered_map>

namespace Via::Shapes {

class ShapeFactory
{

    std::unordered_map<char, std::function<RouteNodeShape*(int, int, QColor)>> shapeKeyTable;

    template<typename Shape>
    RouteNodeShape* generateShape(int x, int y, const QColor &color) {
        return new Shape(x, y, color);
    }

public:
    ShapeFactory();
    RouteNodeShape* generateNodeShapeFromKey(char key, int x, int y, const QColor &color);
};

}

#endif // SHAPEFACTORY_H
