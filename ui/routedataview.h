#ifndef ROUTEDATAVIEW_H
#define ROUTEDATAVIEW_H

#include <QListView>

class RouteDataView : public QListView
{
public:
    RouteDataView(QWidget *widget);

    QModelIndexList getSelectedRows();
};

#endif // ROUTEDATAVIEW_H
