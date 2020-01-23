#include <QPainter>
#include <QPixmap>
#include <QtTest/QtTest>
#include <QTemporaryFile>

#include "../controller/jsonfile.h"
#include "../model/project.h"
#include "../model/routenodedata.h"
#include "../model/routedata.h"
#include "unittestsjson.h"


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
    data.setElementSize(SIZE);
    data.setInvisible(INVISIBLE);
    data.setNodeName(NODE_NAME);
    data.setNodeLabel(NODE_LABEL);
    data.setColors(NODE_COLOR);
    data.setDifferentStyleFromRoute(IS_DIFFERENT);

    auto dataJSON = data.toJSON();

    RouteNodeData dataFromJSON(dataJSON);

    QCOMPARE(dataFromJSON, data);
}

void JSONUnitTests::testRouteSerialization() {
    RouteData data;
    const auto ROUTE_COLOR = QColor(Qt::blue);
    data.setColors(ROUTE_COLOR);
    data.setName("Check this");
    data.setShowDirection(true);

    data.addNode(600,200);
    data.getLastNode().setInvisible(true);

    data.addNode(200,400);
    data.getLastNode().setNodeLabel("Enemies here");

    data.addNode(500,-321);
    data.getLastNode().setDifferentStyleFromRoute(true);
    data.getLastNode().setElementSize(200);
    data.getLastNode().setColors(Qt::red);
    data.getLastNode().setNodeName("Very Important");
    data.getLastNode().setNameChangedByUser(true);

    data.addNode(600,223);

    auto dataJSON = data.toJSON();

    RouteData dataFromJSON(dataJSON);

    QCOMPARE(dataFromJSON, data);
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
    firstRoute.setColors(Qt::red);
    firstRoute.addNode(2,51);
    firstRoute.addNode(99,-69);
    firstRoute.addNode(999,123);
    proj.addRoute(firstRoute);

    RouteData secondRoute;
    secondRoute.setColors(Qt::blue);
    secondRoute.addNode(99,24);
    secondRoute.addNode(1425,2626);
    secondRoute.addNode(99,11);
    secondRoute.getLastNode().setColors(Qt::black);
    secondRoute.getLastNode().setElementSize(332);
    secondRoute.getLastNode().setDifferentStyleFromRoute(true);

    secondRoute.getFirstNode().setNameChangedByUser(true);
    secondRoute.getFirstNode().setNodeName("Secret");
    proj.addRoute(secondRoute);

    auto dataJSON = proj.toJSON();

    QVERIFY(dataJSON["image"].toString() != "");

    Project dataFromJSON(proj.toJSON());

    QCOMPARE(dataFromJSON, proj);
}

void JSONUnitTests::testJSONFileInterface() {
    QVector<Project> projects;

    projects.append(Project("Project1", QPixmap(200,500)));
    for (int i = 0; i < 3; ++i) {
        auto route = RouteData(Qt::red);
        projects.back().addRoute(route);
    }

    projects.append(Project("Project2", QPixmap(1500,900)));
    for (int i = 0; i < 7; ++i) {
        auto route = RouteData(Qt::blue);
        projects.back().addRoute(route);
    }

    QTemporaryFile tempFile;

    tempFile.open();
    JSONFile jsonFile(tempFile.fileName());
    tempFile.close();

    for (const auto &proj : projects) {
        jsonFile.add(proj.toJSON());
    }

    jsonFile.save();

    auto savedProjects = jsonFile.load();

    QCOMPARE(projects.size(), savedProjects.size());

    for (auto i = 0; i < savedProjects.size(); ++i) {
        auto originalProj = projects[i];
        auto loadedProj = Project(savedProjects[i].toObject());
        QCOMPARE(originalProj, loadedProj);
    }

}

#include "unittestsjson.moc"

