#include <QtTest/QtTest>

#include "unittestsroutedata.h"
#include "../model/routedata.h"
#include "../l10n/localizeduistrings.h"

using namespace Via::UnitTest;
using namespace Via::Model;
/*
void RouteDataUnitTests::checkRouteInsertion(int size) {
    auto route = generateRoute(size);

    for (auto i = 0; i < size; ++i) {
        auto node = route[i];
        QCOMPARE(node.getX(), i);
        QCOMPARE(node.getY(), i);
    }
}

RouteData RouteDataUnitTests::generateRoute(int size) {
    RouteData route;


    for (auto i = 0; i < size; ++i) {
        RouteNodeData tempNode(Qt::red);
        tempNode.setX(i);
        tempNode.setY(i);
        route.addNode(tempNode);
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

void RouteDataUnitTests::removalTest() {
    auto route = generateRoute(10);

    auto compareRoute = [&route](){
        for (auto i = 0; i < route.length(); ++i) {
            QCOMPARE(route[i].getName(), Via::UI::LocalizedUIStrings::getUIString("NODE_DEFAULT_NAME").arg(i + 1));
        }
    };

    route.eraseNode(0);
    compareRoute();
    route.eraseNode(3);
    compareRoute();
    route.eraseNode(6);
    compareRoute();
    route.eraseNode(6);
    compareRoute();
}

void RouteDataUnitTests::removalTestWithCustomNode() {
    auto route = generateRoute(10);
    const auto SIZE = 200;
    const QString NAME("Nami");

    route[4].setElementSize(SIZE);
    route[4].setDifferentStyleFromRoute(true);
    route[4].setNameChangedByUser(true);
    route[4].setName(NAME);
    route[4].setInvisible(true);

    auto checkNode = [&](size_t index) {
        QCOMPARE(route[index].getElementSize(), SIZE);
        QCOMPARE(route[index].isStyleDifferentFromRoute(), true);
        QCOMPARE(route[index].isNameChangedByUser(), true);
        QCOMPARE(route[index].getName(), NAME);
        QCOMPARE(route[index].getInvisible(), true);
    };

    route.eraseNode(8);
    checkNode(4);
    route.eraseNode(3);
    checkNode(3);
    route.eraseNode(0);
    checkNode(2);
    route.eraseNode(6);
    checkNode(2);
}


#include "unittestsroutedata.moc"
*/
