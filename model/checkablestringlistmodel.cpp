#include "checkablestringlistmodel.h"
#include <QColor>

using namespace Via::Model;

CheckableStringListModel::CheckableStringListModel(QObject *parent)
    : QStringListModel(parent), checkedItems{} {

}

CheckableStringListModel::CheckableStringListModel(const QStringList &strings, QObject* parent)
    : QStringListModel(strings, parent), checkedItems{} {

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
    } /*else if (role == Qt::DecorationRole) {
        return QColor("#ffffb2");
    }*/

    return QStringListModel::data(index, role);
}

bool CheckableStringListModel::setDataWithoutSignalEmissions(const QModelIndex &index, const QVariant &value, int role) {
    if (!index.isValid()) {
        return false;
    } else if (role != Qt::CheckStateRole) {
        return QStringListModel::setData(index, value, role);
    }

    auto isChecked = value == Qt::Checked;
    if (isChecked)  {
        checkedItems.insert(index);
    } else {
        checkedItems.remove(index);
    }

    return true;
}

bool CheckableStringListModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (setDataWithoutSignalEmissions(index, value, role) == false) {
        return false;
    }

    if (role == Qt::CheckStateRole) {
        emit rowCheckChanged(index.row(), value == Qt::Checked);
    }

    return true;
}


