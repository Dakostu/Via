#ifndef PROJECT_H
#define PROJECT_H

#include "route.h"
#include <QString>


class Project
{
    QString fileName;
    QByteArray imageData;
    bool hasbeenModified;    
    QVector<Route> routes;

public:
    Project();
};

#endif // PROJECT_H
