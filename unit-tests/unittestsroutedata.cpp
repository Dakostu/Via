#include <QtTest/QtTest>

#include "unittestsroutedata.h"
#include "../model/routedata.h"


void RouteDataUnitTests::checkRouteInsertion(size_t size) {
    auto route = generateRoute(size);

    for (size_t i = 0; i < size; ++i) {
        auto node = route[i];
        QCOMPARE(node.getX(), i);
        QCOMPARE(node.getY(), i);
    }
}

RouteData RouteDataUnitTests::generateRoute(size_t size) {
    RouteData route;

    for (int i = 0; i < size; ++i) {
        route.addNode(i,i);
    }

    return route;
}


void RouteDataUnitTests::indexOperationTestOddSize() {
    checkRouteInsertion(5);
    checkRouteInsertion(255);
}

void RouteDataUnitTests::indexOperationTestEvenSize() {
    checkRouteInsertion(6);
    checkRouteInsertion(128);
}

void RouteDataUnitTests::insertionTest() {
    auto route = generateRoute(10);

    route[5].setNodeName("Custom");
    route[5].setNameChangedByUser(true);

    route.addNode(10, 10, 0);

    QCOMPARE(route[0].getX(), 10);
    QCOMPARE(route[0].getY(), 10);
    QCOMPARE(route[0].getNodeName(), "1");

    QCOMPARE(route[1].getX(), 0);
    QCOMPARE(route[1].getY(), 0);
    QCOMPARE(route[1].getNodeName(), "2");

    QCOMPARE(route[6].getNodeName(), "Custom");

    route.addNode(11, 11, 3);
    QCOMPARE(route[3].getX(), 11);
    QCOMPARE(route[3].getY(), 11);
    QCOMPARE(route[3].getNodeName(), "4");

    QCOMPARE(route[2].getX(), 1);
    QCOMPARE(route[2].getY(), 1);
    QCOMPARE(route[2].getNodeName(), "3");

    QCOMPARE(route[4].getX(), 2);
    QCOMPARE(route[4].getY(), 2);
    QCOMPARE(route[4].getNodeName(), "5");

    QCOMPARE(route[7].getNodeName(), "Custom");

    route.addNode(12, 12, 9);
    QCOMPARE(route[9].getX(), 12);
    QCOMPARE(route[9].getY(), 12);
    QCOMPARE(route[9].getNodeName(), "10");

    QCOMPARE(route[8].getX(), 6);
    QCOMPARE(route[8].getY(), 6);
    QCOMPARE(route[8].getNodeName(), "9");

    QCOMPARE(route[10].getX(), 7);
    QCOMPARE(route[10].getY(), 7);
    QCOMPARE(route[10].getNodeName(), "11");

    QCOMPARE(route[7].getNodeName(), "Custom");

}

void RouteDataUnitTests::removalTest() {
    QVERIFY(false);
}

void RouteDataUnitTests::changingTest() {
    QVERIFY(false);
}


#include "unittestsroutedata.moc"
