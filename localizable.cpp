#include "localizable.h"


QString Localizable::getUIString(MapKey key) {

    static const StringMap map = {
        {"YES", tr("&Yes")},
        {"NO", tr("&No")},
        {"FILE", tr("&File")},
        {"OPEN", tr("New Project")},
        {"OPEN", tr("Open Project...")},
        {"SAVE", tr("Save Project")},
        {"SAVE_AS", tr("Save Project As...")},
        {"PRINT", tr("Print Current Project...")},
        {"EXPORT", tr("Export Current Project...")},
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
