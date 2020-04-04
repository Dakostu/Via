#include "nameable.h"

using namespace Via::Interfaces;

QString Nameable::getName() const
{
    return name;
}

void Nameable::setName(const QString &value)
{
    name = value;
}
