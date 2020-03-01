#ifndef VIEWCUSTOMIZABLE_H
#define VIEWCUSTOMIZABLE_H

#include <QAbstractGraphicsShapeItem>
#include <QBrush>

namespace Via::Interfaces {

class ViewCustomizable
{

protected:

    int elementSize;
    static constexpr qreal FILLCOLOR_LIGHTNESS_THRESHOLD = 0.3;

    ViewCustomizable();
    virtual qreal sizeMultiplier(qreal val);

public:
    virtual ~ViewCustomizable() = default;
    virtual void setColors(const QColor &color) = 0;
    virtual void activateColors() = 0;

    virtual int getElementSize() const;
    virtual void setElementSize(int newSize);

};

}

#endif // VIEWCUSTOMIZABLE_H
