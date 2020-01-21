#include <QObject>
#include <QtTest/QtTest>

#include "../model/routenodedata.h"
#include "../model/routedata.h"

class JSONUnitTests : public QObject
{
    Q_OBJECT


private slots:
    void testRouteNodeDataSerialization();
    void testRouteSerialization();

};


void JSONUnitTests::testRouteNodeDataSerialization() {
    RouteNodeData data;

    const auto X = 0;
    const auto Y = 19;
    const auto SIZE = 25;
    const auto INVISIBLE = true;
    const auto IS_DIFFERENT = true;
    const QString NODE_NAME("TestNode");
    const QString NODE_LABEL("This is a test node.");
    QColor NODE_COLOR(Qt::red);

    data.setX(X);
    data.setY(Y);
    data.setSize(SIZE);
    data.setInvisible(INVISIBLE);
    data.setNodeName(NODE_NAME);
    data.setNodeLabel(NODE_LABEL);
    data.setColor(NODE_COLOR);
    data.setDifferentStyleFromRoute(IS_DIFFERENT);

    auto dataJSON = data.toJSON();

    RouteNodeData dataFromJSON(dataJSON);

    QVERIFY(dataFromJSON.getX() == X);
    QVERIFY(dataFromJSON.getY() == Y);
    QVERIFY(dataFromJSON.getSize() == SIZE);
    QVERIFY(dataFromJSON.getInvisible() == INVISIBLE);
    QVERIFY(dataFromJSON.getNodeName() == NODE_NAME);
    QVERIFY(dataFromJSON.getNodeLabel() == NODE_LABEL);
    QVERIFY(dataFromJSON.getColor() == NODE_COLOR);
    QVERIFY(dataFromJSON.isStyleDifferentFromRoute() == IS_DIFFERENT);
}

void JSONUnitTests::testRouteSerialization() {
    RouteData data;

}

QTEST_MAIN(JSONUnitTests)
#include "unittestsjson.moc"
