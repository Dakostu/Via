#ifndef UNITTESTSROUTEDATA_H
#define UNITTESTSROUTEDATA_H

#include <QObject>


class RouteDataUnitTests : public QObject {

    Q_OBJECT

    void checkRouteInsertion(size_t size);

private slots:
    void indexOperationTestOddSize();
    void indexOperationTestEvenSize();
    void insertionTest();
    void changingTest();
};

#endif // UNITTESTSROUTEDATA_H
