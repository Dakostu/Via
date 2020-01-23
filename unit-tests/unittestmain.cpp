#include "unittestsjson.h"
#include "unittestsprogramversion.h"
#include "unittestsroutedata.h"

#include <memory>
#include <QApplication>
#include <QtTest/QtTest>
#include <QTest>

template <typename TestClass>
int runTest(int argc, char **argv) {
    QApplication app(argc, argv);
    std::unique_ptr<TestClass> obj(new TestClass);
    return QTest::qExec(obj.get(), argc, argv);
}

int main(int argc, char **argv) {
    int status = 0;

    status += runTest<JSONUnitTests>(argc, argv);
    status += runTest<RouteDataUnitTests>(argc, argv);
    status += runTest<ProgramVersionUnitTests>(argc, argv);


    return status;
}
