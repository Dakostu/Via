#include "diamond.h"
#include "hexagon.h"
#include "octagon.h"
#include "shapefactory.h"
#include "shapekeys.h"
#include "square.h"
#include "triangledown.h"
#include "triangleup.h"

#include "../ui/localizeduistrings.h"

using namespace Via::Interfaces;
using namespace Via::Shapes;
using namespace Via::UI;


ShapeFactory::ShapeFactory()
{

    shapeKeyTable = std::unordered_map<char, std::function<RouteNodeShape*(int, int, QColor)>>{
        {DIAMOND_KEY, [&](auto x, auto y, auto color) {return generateShape<Diamond>(x,y,color); }},
        {HEXAGON_KEY, [&](auto x, auto y, auto color) {return generateShape<Hexagon>(x,y,color); }},
        {OCTAGON_KEY, [&](auto x, auto y, auto color) {return generateShape<Octagon>(x,y,color); }},
        {SQUARE_KEY, [&](auto x, auto y, auto color) {return generateShape<Square>(x,y,color); }},
        {TRIANGLE_UP_KEY, [&](auto x, auto y, auto color) {return generateShape<TriangleUp>(x,y,color); }},
        {TRIANGLE_DOWN_KEY, [&](auto x, auto y, auto color) {return generateShape<TriangleDown>(x,y,color); }},
    };

    shapeUIStringTable = std::unordered_map<QString, std::function<RouteNodeShape*(int, int, QColor)>>{
        {LocalizedUIStrings::getUIString("DIAMOND"), [&](auto x, auto y, auto color) {return generateShape<Diamond>(x,y,color); }},
        {LocalizedUIStrings::getUIString("HEXAGON"), [&](auto x, auto y, auto color) {return generateShape<Hexagon>(x,y,color); }},
        {LocalizedUIStrings::getUIString("OCTAGON"), [&](auto x, auto y, auto color) {return generateShape<Octagon>(x,y,color); }},
        {LocalizedUIStrings::getUIString("SQUARE"), [&](auto x, auto y, auto color) {return generateShape<Square>(x,y,color); }},
        {LocalizedUIStrings::getUIString("TRIANGLE_UP"), [&](auto x, auto y, auto color) {return generateShape<TriangleUp>(x,y,color); }},
        {LocalizedUIStrings::getUIString("TRIANGLE_DOWN"), [&](auto x, auto y, auto color) {return generateShape<TriangleDown>(x,y,color); }},
    };

}


RouteNodeShape* ShapeFactory::generateNodeShape(char key, int x, int y, const QColor &color) {
    assert(shapeKeyTable.find(key) != shapeKeyTable.end());
    return shapeKeyTable[key](x,y,color);
}

RouteNodeShape* ShapeFactory::generateNodeShape(const QString &key, int x, int y, const QColor &color) {
    assert(shapeUIStringTable.find(key) != shapeUIStringTable.end());
    return shapeUIStringTable[key](x,y,color);
}
