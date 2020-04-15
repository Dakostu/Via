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

void RouteDataView::moveSelectionTo(size_t index) {
    auto modelIndex = model()->index(static_cast<int>(index), 0);
    selectionModel()->select(modelIndex, QItemSelectionModel::SelectCurrent);
}

void RouteDataView::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) {
    QListView::selectionChanged(selected, deselected);
    if (!getSelectedRows().empty()) {
        emit changedSelection();
    }
}

void RouteDataView::removeAllRows() {
    model()->removeRows(0, model()->rowCount());
}
