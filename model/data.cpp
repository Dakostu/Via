#include "data.h"


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
