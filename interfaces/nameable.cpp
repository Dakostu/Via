#include "nameable.h"

using namespace Via::Interfaces;

Nameable::Nameable()
    : name(""), nameChangedByUser(false) {

}


bool Nameable::isNameChangedByUser() const
{
    return nameChangedByUser;
}

void Nameable::setNameChangedByUser(bool value)
{
    nameChangedByUser = value;
}

QString Nameable::getName() const
{
    return name;
}

void Nameable::setName(const QString &value)
{
    name = value;
}

void Nameable::swapNamesWith(Nameable *other) {
    std::swap(this->name, other->name);
}
