#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <QJsonObject>

class Serializable
{
protected:
    Serializable();
    virtual ~Serializable() = default;

public:
    virtual void fromJSON(const QJsonObject &object) = 0;
    virtual QJsonObject toJSON() const = 0;

};

#endif // SERIALIZABLE_H
