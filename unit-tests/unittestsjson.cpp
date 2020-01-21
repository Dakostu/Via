#include <QObject>
#include <QtTest/QtTest>

#include "../model/routenodedata.h"

class JSONUnitTests : public QObject
{
    Q_OBJECT


private slots:
    void testRouteNodeData();

};


void JSONUnitTests::testRouteNodeData() {
    RouteNodeData data;

}

QTEST_MAIN(JSONUnitTests)
#include "jsonunittests.moc"
