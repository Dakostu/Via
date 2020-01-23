#include "programversion.h"

#include <QStringList>


const QString ProgramVersion::DELIMITER = QString(".");

ProgramVersion::ProgramVersion(int majorNum, int minorNum) {
    major = majorNum;
    minor = minorNum;
}

ProgramVersion::ProgramVersion(const QString &version) {
    auto splitString = version.split(DELIMITER);
    major = splitString[0].toInt();
    minor = splitString[1].toInt();

}

ProgramVersion ProgramVersion::generateCurrentProgramVersion() {
    return ProgramVersion(CURRENT_MAJOR_VERSION, CURRENT_MINOR_VERSION);
}

QString ProgramVersion::operator()() {
    return QString("%1%2%3").arg(major).arg(DELIMITER).arg(minor, 2);
}

