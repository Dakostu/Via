#ifndef COLORPREVIEWBUTTON_H
#define COLORPREVIEWBUTTON_H

#include <QPushButton>

namespace Via::UI {

class ColorPreviewButton : public QPushButton
{
public:
    ColorPreviewButton(QWidget *parent);

    void changeColor(const QColor &newColor);
};

}

#endif // COLORPREVIEWBUTTON_H
