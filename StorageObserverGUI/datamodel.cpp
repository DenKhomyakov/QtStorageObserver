#include "datamodel.h"

DataModel::DataModel(QObject* parent, QList<TableModel> table) : QAbstractTableModel(parent) {
    dataModel = table;
}

int DataModel::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);

    return dataModel.count();
}

int DataModel::columnCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);

    return dataModel.count() + 1;
}
