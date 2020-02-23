#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H

#include "../interfaces/nodeshapeable.h"
#include "shapekeys.h"
#include <functional>
#include <unordered_map>

namespace Via::Shapes {

class ShapeFactory
{

    static std::unordered_map<char, std::function<Via::Interfaces::NodeShapeable*(int, int, QColor)>> shapeKeyTable;

    template<typename Shape>
    Via::Interfaces::NodeShapeable* generateShape(int x, int y, const QColor &color) {
        return new Shape(x, y, color);
    }

public:
    ShapeFactory();
    Via::Interfaces::NodeShapeable* generateNodeShapeFromKey(char key, int x, int y, const QColor &color);
};

}

#endif // SHAPEFACTORY_H
