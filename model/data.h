#ifndef DATA_H
#define DATA_H

#include "../interfaces/serializable.h"
#include "../interfaces/viewcustomizable.h"
#include <QString>
#include <QColor>

namespace Via::Model {

class Data : public Via::Interfaces::Serializable
{
protected:
    Data() = default;

public:
    virtual ~Data() = default;

};

}

#endif // DATA_H
