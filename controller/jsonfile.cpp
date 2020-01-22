#include "jsonfile.h"

#include <QIODevice>

JSONFile::JSONFile(const QString &fileName) : QFile(fileName) {


}

void JSONFile::add(const QJsonObject &obj) {
    savedJSONObjects += obj;
}

void JSONFile::writeToFile() {
    if (!this->open(QIODevice::WriteOnly)) {
        throw std::invalid_argument("File could not be saved");
    }

    doccy.setArray(savedJSONObjects);
    this->write(doccy.toBinaryData());

    this->close();
}

QJsonArray JSONFile::load() {
    if (!this->open(QIODevice::WriteOnly)) {
        throw std::invalid_argument("File could not be loaded");
    }

    auto data = this->readAll();
    this->close();

    doccy = QJsonDocument::fromBinaryData(data);
    savedJSONObjects = doccy.array();

    return savedJSONObjects;
}
