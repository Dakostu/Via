#ifndef JSONUNITTESTS_H
#define JSONUNITTESTS_H

#include <QObject>

namespace Via::UnitTest {

class JSONUnitTests : public QObject
{
    Q_OBJECT


private slots:
    void testRouteNodeDataSerialization();
    void testRouteSerialization();
    void testProjectSerialization();
    void testJSONFileInterface();
};

}

#endif // JSONUNITTESTS_H
