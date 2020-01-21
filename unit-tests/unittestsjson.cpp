#include <QObject>
#include <QtTest/QtTest>
#include <QPainter>
#include <QPixmap>

#include "../model/project.h"
#include "../model/routenodedata.h"
#include "../model/routedata.h"

class JSONUnitTests : public QObject
{
    Q_OBJECT


private slots:
    void testRouteNodeDataSerialization();
    void testRouteSerialization();
    void testProjectSerialization();
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

void JSONUnitTests::testProjectSerialization() {
    QPixmap picture(640,480);
    QPainter painter(&picture);
    painter.fillRect(0,0,640,480,QBrush(Qt::red));
    painter.drawText(QPoint{300,350}, "Hello");
    painter.save();

    const QString PROJECT_NAME = "Project.json";
    Project proj(PROJECT_NAME, picture);

    RouteData firstRoute;
    firstRoute.setColor(Qt::red);
    firstRoute.addNode(2,51);
    firstRoute.addNode(99,-69);
    firstRoute.addNode(999,123);
    proj.addRoute(firstRoute);

    RouteData secondRoute;
    secondRoute.setColor(Qt::blue);
    secondRoute.addNode(99,24);
    secondRoute.addNode(1425,2626);
    secondRoute.addNode(99,11);
    secondRoute.getLastNode().setColor(Qt::black);
    secondRoute.getLastNode().setSize(332);
    secondRoute.getLastNode().setDifferentStyleFromRoute(true);
    proj.addRoute(secondRoute);

    auto dataJSON = proj.toJSON();

    Project dataFromJSON(proj.toJSON());

    QVERIFY(dataFromJSON == proj);
}

QTEST_MAIN(JSONUnitTests)
#include "unittestsjson.moc"
