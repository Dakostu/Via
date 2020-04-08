#include "diamond.h"
#include "hexagon.h"
#include "octagon.h"
#include "routenodeshapefactory.h"
#include "shapekeys.h"
#include "square.h"
#include "triangledown.h"
#include "triangleup.h"

#include "../l10n/localizeduistrings.h"

using namespace Via::Interfaces;
using namespace Via::L10n;
using namespace Via::Shapes;


RouteNodeShapeFactory::RouteNodeShapeFactory()
{

    shapeKeyTable = std::unordered_map<char, std::function<RouteNodeShape*(QPointF, QColor)>>{
        {DIAMOND_KEY, [&](auto point, auto color) {return generateShape<Diamond>(point, color); }},
        {HEXAGON_KEY, [&](auto point, auto color) {return generateShape<Hexagon>(point, color); }},
        {OCTAGON_KEY, [&](auto point, auto color) {return generateShape<Octagon>(point, color); }},
        {SQUARE_KEY, [&](auto point, auto color) {return generateShape<Square>(point, color); }},
        {TRIANGLE_UP_KEY, [&](auto point, auto color) {return generateShape<TriangleUp>(point, color); }},
        {TRIANGLE_DOWN_KEY, [&](auto point, auto color) {return generateShape<TriangleDown>(point, color); }}
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


char RouteNodeShapeFactory::getShapeKeyFromUIString(QString key) {
    if (key.length() > 1) {
        key = shapeStringKeyTable[key];
    }
    return key[0].toLatin1();
}

RouteNodeShape* RouteNodeShapeFactory::generateNodeShape(char key, const QPointF &point, const QColor &color) {
    assert(shapeKeyTable.find(key) != shapeKeyTable.end());
    return shapeKeyTable[key](point,color);
}
