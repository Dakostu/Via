#ifndef DATA_H
#define DATA_H

#include "../interfaces/serializable.h"

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
