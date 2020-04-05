#ifndef NAMEABLE_H
#define NAMEABLE_H

#include <QString>

namespace Via::Interfaces {

class Nameable
{

protected:
    Nameable();

    QString name;
    bool nameChangedByUser;

public:
    virtual ~Nameable() = default;

    virtual QString getName() const;
    virtual bool isNameChangedByUser() const;

    virtual void setName(const QString &value);
    virtual void setNameChangedByUser(bool value);

    virtual void swapNamesWith(Nameable* other);

};

}
#endif // NAMEABLE_H
