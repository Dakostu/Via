#include "diamond.h"
#include "hexagon.h"
#include "octagon.h"
#include "shapefactory.h"
#include "shapekeys.h"
#include "square.h"
#include "triangledown.h"
#include "triangleup.h"

using namespace Via::Interfaces;
using namespace Via::Shapes;

ShapeFactory::ShapeFactory()
{

    shapeKeyTable = std::unordered_map<char, std::function<NodeShapeable*(int, int, QColor)>>{
        {DIAMOND_KEY, [&](auto x, auto y, auto color) {return generateShape<Diamond>(x,y,color); }},
        {HEXAGON_KEY, [&](auto x, auto y, auto color) {return generateShape<Hexagon>(x,y,color); }},
        {OCTAGON_KEY, [&](auto x, auto y, auto color) {return generateShape<Octagon>(x,y,color); }},
        {SQUARE_KEY, [&](auto x, auto y, auto color) {return generateShape<Square>(x,y,color); }},
        {TRIANGLE_UP_KEY, [&](auto x, auto y, auto color) {return generateShape<TriangleUp>(x,y,color); }},
        {TRIANGLE_DOWN_KEY, [&](auto x, auto y, auto color) {return generateShape<TriangleDown>(x,y,color); }},
    };

}


NodeShapeable* ShapeFactory::generateNodeShapeFromKey(char key, int x, int y, const QColor &color) {
    assert(shapeKeyTable.find(key) != shapeKeyTable.end());
    return shapeKeyTable[key](x,y,color);
}
