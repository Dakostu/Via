#include "unittestsjson.h"
#include "unittestsroutedata.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QTest>

template <typename TestClass>
int runTest(int argc, char **argv) {
    QApplication app(argc, argv);
    return QTest::qExec(new TestClass, argc, argv);
}

int main(int argc, char **argv) {
    int status = 0;

    status |= runTest<JSONUnitTests>(argc, argv);
    status |= runTest<RouteDataUnitTests>(argc, argv);

    return status;
}
