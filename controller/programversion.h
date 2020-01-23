#ifndef PROGRAMVERSION_H
#define PROGRAMVERSION_H

#include <QString>

class ProgramVersion
{
    unsigned major;
    unsigned minor;

    static const auto CURRENT_MAJOR_VERSION = 1;
    static const auto CURRENT_MINOR_VERSION = 0;
    static const QString DELIMITER;

public:

    ProgramVersion(unsigned majorNum, unsigned minorNum);
    ProgramVersion(const QString &version);

    static ProgramVersion generateCurrentProgramVersion();

    QString operator()();
};

#endif // PROGRAMVERSION_H
