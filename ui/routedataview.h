#ifndef ROUTEDATAVIEW_H
#define ROUTEDATAVIEW_H

#include <QListView>

class RouteDataView : public QListView
{
public:
    RouteDataView(QWidget *widget);

    QModelIndexList getSelectedRows();
    void moveSelectionTo(int index);
};

#endif // ROUTEDATAVIEW_H
