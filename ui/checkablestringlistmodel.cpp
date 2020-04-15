#include "checkablestringlistmodel.h"

using namespace Via::UI;

CheckableStringListModel::CheckableStringListModel(QObject *parent)
    : QStringListModel(parent), checkedItems{{}} {

}

CheckableStringListModel::CheckableStringListModel(const QStringList &strings, QObject* parent)
    : QStringListModel(strings, parent), checkedItems{{}} {

}

Qt::ItemFlags CheckableStringListModel::flags(const QModelIndex &index) const {
    auto itemFlags = QStringListModel::flags(index);

    if (!index.isValid()) {
        return itemFlags;
    }

    return itemFlags | Qt::ItemIsUserCheckable;
}

QVariant CheckableStringListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }

    if (role == Qt::CheckStateRole) {
        return checkedItems.contains(index) ? Qt::Checked : Qt::Unchecked;
    }

    return QStringListModel::data(index, role);
}


bool CheckableStringListModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if(!index.isValid() || role != Qt::CheckStateRole)
            return false;

        if (value == Qt::Checked)
            checkedItems.insert(index);
        else
            checkedItems.remove(index);

        emit dataChanged(index, index);
        return true;
}


