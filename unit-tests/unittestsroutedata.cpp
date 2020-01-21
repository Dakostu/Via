#include <QtTest/QtTest>

#include "unittestsroutedata.h"
#include "../model/routedata.h"


void RouteDataUnitTests::checkRouteInsertion(size_t size) {
    RouteData route;

    for (int i = 0; i < size; ++i) {
        route.addNode(i,i);
    }

    for (size_t i = 0; i < size; ++i) {
        auto node = route[i];
        QCOMPARE(node.getX(), i);
        QCOMPARE(node.getY(), i);
    }
}


void RouteDataUnitTests::indexOperationTestOddSize() {
    checkRouteInsertion(5);
}

void RouteDataUnitTests::indexOperationTestEvenSize() {
    checkRouteInsertion(6);
}


void RouteDataUnitTests::insertionTest() {
    QVERIFY(false);
}

void RouteDataUnitTests::changingTest() {
    QVERIFY(false);
}

#include "unittestsroutedata.moc"
