#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <QJsonObject>

namespace Via::Interfaces {

class Serializable
{
protected:
    Serializable() = default;

public:
    virtual ~Serializable() = default;
    virtual void fromJSON(const QJsonObject &object) = 0;
    virtual QJsonObject toJSON() = 0;

};

}
#endif // SERIALIZABLE_H
