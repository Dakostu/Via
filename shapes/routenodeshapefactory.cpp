#include "diamond.h"
#include "hexagon.h"
#include "octagon.h"
#include "routenodeshapefactory.h"
#include "shapekeys.h"
#include "square.h"
#include "triangledown.h"
#include "triangleup.h"

#include "../ui/localizeduistrings.h"

using namespace Via::Interfaces;
using namespace Via::Shapes;
using namespace Via::UI;


RouteNodeShapeFactory::RouteNodeShapeFactory()
{

    shapeKeyTable = std::unordered_map<char, std::function<RouteNodeShape*(int, int, QColor)>>{
        {DIAMOND_KEY, [&](auto x, auto y, auto color) {return generateShape<Diamond>(x,y,color); }},
        {HEXAGON_KEY, [&](auto x, auto y, auto color) {return generateShape<Hexagon>(x,y,color); }},
        {OCTAGON_KEY, [&](auto x, auto y, auto color) {return generateShape<Octagon>(x,y,color); }},
        {SQUARE_KEY, [&](auto x, auto y, auto color) {return generateShape<Square>(x,y,color); }},
        {TRIANGLE_UP_KEY, [&](auto x, auto y, auto color) {return generateShape<TriangleUp>(x,y,color); }},
        {TRIANGLE_DOWN_KEY, [&](auto x, auto y, auto color) {return generateShape<TriangleDown>(x,y,color); }}
    };

    shapeStringKeyTable = std::unordered_map<QString, char> {
        {LocalizedUIStrings::getUIString("DIAMOND"), DIAMOND_KEY},
        {LocalizedUIStrings::getUIString("HEXAGON"), HEXAGON_KEY},
        {LocalizedUIStrings::getUIString("OCTAGON"), OCTAGON_KEY},
        {LocalizedUIStrings::getUIString("SQUARE"), SQUARE_KEY},
        {LocalizedUIStrings::getUIString("TRIANGLE_UP"), TRIANGLE_UP_KEY},
        {LocalizedUIStrings::getUIString("TRIANGLE_DOWN"), TRIANGLE_DOWN_KEY}
    };

}


RouteNodeShape* RouteNodeShapeFactory::generateNodeShape(QString key, int x, int y, const QColor &color) {
    if (key.length() > 1) {
        key = shapeStringKeyTable[key];
    }

    auto keyChar = key[0].toLatin1();

    assert(shapeKeyTable.find(keyChar) != shapeKeyTable.end());
    return shapeKeyTable[keyChar](x,y,color);
}
