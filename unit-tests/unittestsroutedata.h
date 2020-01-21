#ifndef UNITTESTSROUTEDATA_H
#define UNITTESTSROUTEDATA_H

#include <QObject>
#include "../model/routedata.h"

class RouteDataUnitTests : public QObject {

    Q_OBJECT

    void checkRouteInsertion(size_t size);
    RouteData generateRoute(size_t size);

private slots:
    void indexOperationTestOddSize();
    void indexOperationTestEvenSize();
    void insertionTest();
    void removalTest();
    void changingTest();
};

#endif // UNITTESTSROUTEDATA_H
