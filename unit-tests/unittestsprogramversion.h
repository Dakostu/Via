#ifndef PROJECTVERSIONUNITTESTS_H
#define PROJECTVERSIONUNITTESTS_H

#include <QObject>

namespace Via::UnitTest {

class ProgramVersionUnitTests : public QObject
{
    Q_OBJECT

private slots:

    void testProjectVersionOutput();
    void testStringParsing();

};

}

#endif // PRODUCTVERSIONUNITTESTS_H
