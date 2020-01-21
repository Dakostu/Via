#include <QtTest/QtTest>

#include "unittestsroutedata.h"
#include "../model/routedata.h"


void RouteDataUnitTests::indexOperationTest() {
    RouteData route;

    for (int i = 0; i < 5; ++i) {
        route.addNode(i,i);
    }



}

#include "unittestsroutedata.moc"
