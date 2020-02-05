#ifndef DATA_H
#define DATA_H

#include "../interfaces/serializable.h"
#include "../interfaces/viewcustomizable.h"
#include <QString>
#include <QColor>

namespace Via::Model {

class Data : public Via::Interfaces::Serializable, public Via::Interfaces::ViewCustomizable
{
protected:
    virtual ~Data() = default;

    QString name;
    QColor currentColor;

public:

    QColor getColor() const;
    QString getName() const;
    void setName(const QString &value);

};

}

#endif // DATA_H
