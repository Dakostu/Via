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
        {"TRIANGLE_UP", tr("Triangle (Up)")},
        {"TRIANGLE_DOWN", tr("Triangle (Down)")},
        {"DIAMOND", tr("Diamond")},
        {"SQUARE", tr("Square")},
        {"HEXAGON", tr("Hexagon")},
        {"OCTAGON", tr("Octagon")},
        {"CREATE_NEW_PROJECT_TITLE", tr("Save new project file")},
        {"PROJECT_FILE_TYPES", tr("ROU file (*.rou);")},
        {"LOAD_IMAGE_FILE", tr("Select image file for project background")},
        {"QPIXMAP_SUPPORTED_FILE_TYPES", tr("BMP file (*.bmp);;"
         "GIF file (*.gif);;"
         "JPG/JPEG file (*.jpg *.jpeg);;"
         "PNG file (*.png);;"
         "PBM file (*.pbm);;"
         "PGM file (*.pgm);;"
         "PPM file (*.ppm);;"
         "XBM file (*.xbm);;"
         "XPM file (*.xpm);;")},

    };

    QString result;

    try {
        result = map.at(key);
    }  catch (std::out_of_range) {
        result = QString("!!INVALID KEY \"%1\"!!").arg(key);
    }

    return result;
}
