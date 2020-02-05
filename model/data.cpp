#include "data.h"

using namespace Via::Model;

void Data::setName(const QString &value)
{
    name = value;
}

QString Data::getName() const
{
    return name;
}

QColor Data::getColor() const
{
    return currentColor;
}
