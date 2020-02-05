#ifndef UNITTESTSROUTEDATA_H
#define UNITTESTSROUTEDATA_H

#include <QObject>
#include "../model/routedata.h"

namespace Via::UnitTest {

class RouteDataUnitTests : public QObject {

    Q_OBJECT

    void checkRouteInsertion(size_t size);
    Via::Model::RouteData generateRoute(size_t size);

private slots:
    void indexOperationTestOddSize();
    void indexOperationTestEvenSize();
    void insertionTest();
    void removalTest();
    void removalTestWithCustomNode();
};

}

#endif // UNITTESTSROUTEDATA_H
