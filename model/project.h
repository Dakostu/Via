#ifndef PROJECT_H
#define PROJECT_H

#include "../shapes/route.h"
#include <QString>
#include <QImage>

class Project
{    
    QString fileName;
    QByteArray imageData;
    QImage image;
    bool hasbeenModified;    
    QVector<Route> routes;

public:
    Project();
};

#endif // PROJECT_H
