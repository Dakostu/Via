#ifndef UISTATE_H
#define UISTATE_H

#include <QAbstractButton>
#include <QDebug>

class UIState
{

public:

    virtual ~UIState();

    virtual void setToggleButtons(QAbstractButton *quickButtonAutoAdd,
                                  QAbstractButton *quickButtonMove,
                                  QAbstractButton *quickButtonSelect) = 0;   


};

#endif // UISTATE_H
