#include "routedataview.h"
#include <QItemSelectionModel>
#include <QMouseEvent>

using namespace Via::UI;

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

void RouteDataView::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) {
    QListView::selectionChanged(selected, deselected);
    if (!getSelectedRows().empty()) {
        emit changedSelection();
    }
}

