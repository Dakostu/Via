#ifndef ROUTEDATAVIEW_H
#define ROUTEDATAVIEW_H

#include <QListView>

namespace Via::UI {

class RouteDataView : public QListView
{
    Q_OBJECT

public:
    RouteDataView(QWidget *widget);

    QModelIndexList getSelectedRows();
    void moveSelectionTo(int index);

    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) override;


signals:
    void changedSelection();
};

}

#endif // ROUTEDATAVIEW_H
