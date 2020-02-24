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

    shapeKeyTable = std::unordered_map<QString, std::function<RouteNodeShape*(int, int, QColor)>>{
        {QString(DIAMOND_KEY), [&](auto x, auto y, auto color) {return generateShape<Diamond>(x,y,color); }},
        {QString(HEXAGON_KEY), [&](auto x, auto y, auto color) {return generateShape<Hexagon>(x,y,color); }},
        {QString(OCTAGON_KEY), [&](auto x, auto y, auto color) {return generateShape<Octagon>(x,y,color); }},
        {QString(SQUARE_KEY), [&](auto x, auto y, auto color) {return generateShape<Square>(x,y,color); }},
        {QString(TRIANGLE_UP_KEY), [&](auto x, auto y, auto color) {return generateShape<TriangleUp>(x,y,color); }},
        {QString(TRIANGLE_DOWN_KEY), [&](auto x, auto y, auto color) {return generateShape<TriangleDown>(x,y,color); }},
        {LocalizedUIStrings::getUIString("DIAMOND"), [&](auto x, auto y, auto color) {return generateShape<Diamond>(x,y,color); }},
        {LocalizedUIStrings::getUIString("HEXAGON"), [&](auto x, auto y, auto color) {return generateShape<Hexagon>(x,y,color); }},
        {LocalizedUIStrings::getUIString("OCTAGON"), [&](auto x, auto y, auto color) {return generateShape<Octagon>(x,y,color); }},
        {LocalizedUIStrings::getUIString("SQUARE"), [&](auto x, auto y, auto color) {return generateShape<Square>(x,y,color); }},
        {LocalizedUIStrings::getUIString("TRIANGLE_UP"), [&](auto x, auto y, auto color) {return generateShape<TriangleUp>(x,y,color); }},
        {LocalizedUIStrings::getUIString("TRIANGLE_DOWN"), [&](auto x, auto y, auto color) {return generateShape<TriangleDown>(x,y,color); }},
    };

}


RouteNodeShape* ShapeFactory::generateNodeShape(const QString &key, int x, int y, const QColor &color) {
    assert(shapeKeyTable.find(key) != shapeKeyTable.end());
    return shapeKeyTable[key](x,y,color);
}
