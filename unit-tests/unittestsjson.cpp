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

    QVERIFY(dataFromJSON == data);
}

void JSONUnitTests::testRouteSerialization() {
    RouteData data;
    const auto ROUTE_COLOR = QColor(Qt::blue);
    data.setColor(ROUTE_COLOR);
    data.setName("Check this");
    data.setShowDirection(true);

    data.addNode(600,200);
    data.getLastNode().setInvisible(true);

    data.addNode(200,400);
    data.getLastNode().setNodeLabel("Enemies here");

    data.addNode(500,-321);
    data.getLastNode().setDifferentStyleFromRoute(true);
    data.getLastNode().setSize(200);
    data.getLastNode().setColor(Qt::red);
    data.getLastNode().setNodeName("Very Important");

    data.addNode(600,223);

    auto dataJSON = data.toJSON();

    RouteData dataFromJSON(dataJSON);

    QVERIFY(dataFromJSON == data);
}

QTEST_MAIN(JSONUnitTests)
#include "unittestsjson.moc"
