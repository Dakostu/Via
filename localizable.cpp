#include "localizable.h"


QString Localizable::getUIString(MapKey key) {

    static const StringMap map = {
        {"YES", tr("&Yes")},
        {"NO", tr("&No")},
        {"FILE", tr("&File")},
        {"NEW", tr("New")},
        {"OPEN", tr("Open...")},
        {"SAVE", tr("Save")},
        {"SAVE_AS", tr("Save As...")},
        {"PRINT", tr("Print...")},
        {"EXPORT", tr("Export...")},
        {"QUIT", tr("Quit")},
        {"EDIT", tr("&Edit")},
        {"UNDO", tr("Undo")},
        {"REDO", tr("Redo")},
        {"CUT", tr("Cut")},
        {"COPY", tr("Copy")},
        {"PASTE", tr("Paste")},
    };

    QString result;

    try {
        result = map.at(key);
    }  catch (std::out_of_range) {
        result = QString("!!INVALID KEY \"%1\"!!").arg(key);
    }

    return result;
}
