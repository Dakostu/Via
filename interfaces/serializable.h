#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <QJsonObject>

class Serializable
{
protected:
    Serializable();

public:
    virtual void fromJSON(const QJsonObject &object) = 0;
    virtual QJsonObject toJSON() = 0;

};

#endif // SERIALIZABLE_H
