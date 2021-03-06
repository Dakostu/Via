#ifndef LOCALIZABLESTRINGS_H
#define LOCALIZABLESTRINGS_H

#include <unordered_map>
#include <QApplication>

namespace Via::L10n {

using MapKey = QString;
using MapValue = QString;
using StringMap = std::unordered_map<MapKey, MapValue>;

class LocalizedUIStrings
{

    Q_DECLARE_TR_FUNCTIONS(Localizable)

public:
    static QString getUIString(const MapKey &key);
};

}

#endif // LOCALIZABLESTRINGS_H
