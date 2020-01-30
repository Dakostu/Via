#include "routedataview.h"

#include <QMouseEvent>

RouteDataView::RouteDataView(QWidget *widget) : QListView(widget)
{

}


QModelIndexList RouteDataView::getSelectedRows() {
    return this->selectionModel()->selectedRows();
}

void RouteDataView::moveSelectionTo(int index) {
    auto modelIndex = model()->index(index, 0);
    selectionModel()->select(modelIndex, QItemSelectionModel::SelectCurrent);
}

