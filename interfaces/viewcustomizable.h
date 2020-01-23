#ifndef VIEWCUSTOMIZABLE_H
#define VIEWCUSTOMIZABLE_H

#include <QAbstractGraphicsShapeItem>
#include <QBrush>

class ViewCustomizable
{

protected:
    qreal elementSize;
    static constexpr qreal FILLCOLOR_LIGHTNESS_THRESHOLD = 0.3;

    ViewCustomizable();
    virtual qreal sizeMultiplier(qreal val);

public:
    virtual void setColors(const QColor &color) = 0;
    virtual void setDefaultColors() = 0;

    virtual qreal getElementSize();
    virtual void setElementSize(qreal newSize);

};

#endif // VIEWCUSTOMIZABLE_H
