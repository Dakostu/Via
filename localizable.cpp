#include "localizable.h"


#define LOCALIZED(key, string) {key, QObject::tr(string)}
QString Localizable::getUIString(MapKey key) {

    static const StringMap map = {
        LOCALIZED("YES", "&Yes"),
        LOCALIZED("NO", "&No"),
        LOCALIZED("FILE", "&File"),
        LOCALIZED("OPEN", "Open..."),
        LOCALIZED("SAVE", "Save"),
        LOCALIZED("SAVE_AS", "Save As..."),
        LOCALIZED("QUIT", "Quit"),
        LOCALIZED("EDIT", "&Edit"),
        LOCALIZED("UNDO", "Undo"),
        LOCALIZED("REDO", "Redo"),
    };

    QString result;

    try {
        result = map.at(key);
    }  catch (std::out_of_range) {
        result = QString("!!INVALID KEY \"%1\"!!").arg(key);
    }

    return result;
}
