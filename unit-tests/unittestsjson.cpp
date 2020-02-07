#include <QPainter>
#include <QPixmap>
#include <QtTest/QtTest>
#include <QTemporaryFile>

#include "../controller/jsonfile.h"
#include "../model/project.h"
#include "../model/routenodedata.h"
#include "../model/routedata.h"
#include "unittestsjson.h"

using namespace Via::UnitTest;
using namespace Via::Model;
using namespace Via::Control;

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
    data.setName(NODE_NAME);
    data.setNodeLabel(NODE_LABEL);
    data.setColors(NODE_COLOR);
    data.setDifferentStyleFromRoute(IS_DIFFERENT);

    auto dataJSON = data.toJSON();

    RouteNodeData dataFromJSON(dataJSON);

    QCOMPARE(dataFromJSON, data);
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

