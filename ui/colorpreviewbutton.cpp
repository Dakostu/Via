#include "colorpreviewbutton.h"

using namespace Via::UI;

ColorPreviewButton::ColorPreviewButton(QWidget *parent) : QPushButton(parent)
{

}

void ColorPreviewButton::changeColor(const QColor &newColor) {
    this->setStyleSheet(QString("QPushButton {background-color: %1}").arg(newColor.name()));
}
