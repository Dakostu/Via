#include "localizeduistrings.h"

using namespace Via::UI;

QString LocalizedUIStrings::getUIString(const MapKey &key) {

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
        {"TRIANGLE_UP", tr("Triangle (Up)")},
        {"TRIANGLE_DOWN", tr("Triangle (Down)")},
        {"DIAMOND", tr("Diamond")},
        {"SQUARE", tr("Square")},
        {"HEXAGON", tr("Hexagon")},
        {"OCTAGON", tr("Octagon")},
        {"CREATE_NEW_PROJECT_TITLE", tr("Save new project file")},
        {"LOAD_PROJECT_TITLE", tr("Open project file")},
        {"SAVE_PROJECT_AS_TITLE", tr("Save project as...")},
        {"PROJECT_FILE_TYPES", tr("ROU file(*.rou);")},
        {"LOAD_IMAGE_FILE", tr("Select image file for project background")},
        {"QPIXMAP_SUPPORTED_FILE_TYPES", tr("Supported image types "
         "(.bmp, .gif, .jpg, .jpeg, .png, .pbm, .pgm, .ppm, .xbm, .xpm)"
         "(*.bmp *.gif *.jpg *.jpeg *.png *.pbm *.pgm *.ppm *.xbm *.xpm);")},
        {"ROUTE_DEFAULT_NAME", tr("Route %1")},
        {"NODE_DEFAULT_NAME", tr("Node %1")}

    };

    QString result;

    try {
        result = map.at(key);
    }  catch (std::out_of_range&) {
        result = QString("!!INVALID KEY \"%1\"!!").arg(key);
    }

    return result;
}
