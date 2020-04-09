#ifndef ROUTENODEDATA_H
#define ROUTENODEDATA_H

#include "data.h"

namespace Via::Model {

struct RouteNodeData : public Data
{
    static inline const char* NODE_NAME_KEY = "n";
    static inline const char* NODE_NAME_CHANGED_KEY = "g";
    static inline const char* NODE_LABEL_KEY = "l";
    static inline const char* NODE_X_KEY = "x";
    static inline const char* NODE_Y_KEY = "y";
    static inline const char* NODE_DIFFERENT_STYLE_KEY = "f";
    static inline const char* NODE_INVISIBLE_KEY = "i";
    static inline const char* NODE_COLOR_KEY = "c";
    static inline const char* NODE_SIZE_KEY = "s";
    static inline const char* NODE_SHAPE_KEY = "p";
};

}

#endif // ROUTENODEDATA_H
