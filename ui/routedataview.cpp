#include "routedataview.h"

RouteDataView::RouteDataView(QWidget *widget) : QListView(widget)
{

}


QModelIndexList RouteDataView::getSelectedRows() {
    return this->selectionModel()->selectedRows();
}
