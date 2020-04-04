#ifndef NAMEABLE_H
#define NAMEABLE_H

#include <QString>

namespace Via::Interfaces {

class Nameable
{

protected:
    Nameable() = default;

    QString name;

public:
    virtual QString getName() const;
    virtual void setName(const QString &value);
};

}
#endif // NAMEABLE_H
