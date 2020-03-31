#include "programversion.h"

#include <QStringList>

using namespace Via::Control;

ProgramVersion::ProgramVersion(unsigned majorNum, unsigned minorNum) {

    if (minorNum >= 100) {
        throw std::invalid_argument("Minor program version is larger than 100");
    }

    major = majorNum;
    minor = minorNum;
}

ProgramVersion::ProgramVersion(const QString &version) {
    auto splitString = version.split(DELIMITER);
    major = splitString[0].toUInt();
    minor = splitString[1].toUInt();

    if (minor >= 100) {
        throw std::invalid_argument("Minor program version is larger than 100");
    }

}

ProgramVersion ProgramVersion::generateCurrentProgramVersion() {
    return ProgramVersion(CURRENT_MAJOR_VERSION, CURRENT_MINOR_VERSION);
}

QString ProgramVersion::operator()() {
    return QString("%1%2%3").arg(major).arg(DELIMITER).arg(minor, 2, 10, QChar('0'));
}

