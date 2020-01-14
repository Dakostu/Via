#ifndef VIEWCUSTOMIZABLE_H
#define VIEWCUSTOMIZABLE_H

#include <QString>
#include <QColor>

struct ViewCustomizableStyle {
    QString name;
    QString label;
    QColor color;
    QString style;
    bool showNodeOrder;
};

class ViewCustomizable
{

    ViewCustomizableStyle style;
protected:
    ViewCustomizable();
};

#endif // VIEWCUSTOMIZABLE_H
