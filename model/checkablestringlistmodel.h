#ifndef CHECKABLESTRINGLISTMODEL_H
#define CHECKABLESTRINGLISTMODEL_H

#include <QSet>
#include <QStringListModel>

namespace Via::Model {

class CheckableStringListModel : public QStringListModel                
{
    QSet<QPersistentModelIndex> checkedItems;

public:
    CheckableStringListModel(QObject *parent = nullptr);
    CheckableStringListModel(const QStringList &strings, QObject* parent = nullptr);

    Qt::ItemFlags flags (const QModelIndex& index) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
};

}

#endif // CHECKABLESTRINGLISTMODEL_H
