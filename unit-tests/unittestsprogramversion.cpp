#include "unittestsprogramversion.h"
#include "../controller/programversion.h"

#include <QtTest/QtTest>

using namespace Via::UnitTest;
using namespace Via::Control;

void ProgramVersionUnitTests::testProjectVersionOutput() {
    ProgramVersion ver(1,2);
    QCOMPARE(ver(), "1.02");

    ver = ProgramVersion(1,99);
    QCOMPARE(ver(), "1.99");
    QVERIFY_EXCEPTION_THROWN(ver = ProgramVersion(99,123), std::invalid_argument);
}


void ProgramVersionUnitTests::testStringParsing() {
    ProgramVersion ver("1.02");
    QCOMPARE(ver(), "1.02");

    ver = ProgramVersion("1.99");
    QCOMPARE(ver(), "1.99");

    QVERIFY_EXCEPTION_THROWN(ver = ProgramVersion("1.123"), std::invalid_argument);
}

