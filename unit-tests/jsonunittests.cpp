#include <QObject>
#include <QtTest/QtTest>

class JSONUnitTests : public QObject
{
    Q_OBJECT


private slots:
    void testRouteNodeData();

};


void JSONUnitTests::testRouteNodeData() {
    QVERIFY(false);
}

QTEST_MAIN(JSONUnitTests)
#include "jsonunittests.moc"
