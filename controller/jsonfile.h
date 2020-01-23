#ifndef JSONFILE_H
#define JSONFILE_H

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>

class JSONFile : protected QFile
{
    QJsonDocument doccy;
    QJsonArray savedJSONObjects;
public:
    JSONFile(const QString &fileName);

    void add(const QJsonObject &obj);
    void save();
    QJsonArray load();

    void operator+=(const QJsonObject &obj);
};

#endif // JSONFILE_H
