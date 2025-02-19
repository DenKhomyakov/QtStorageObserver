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

QVariant DataModel::data(const QModelIndex& index, int role) const {
    if (index.isValid() || dataModel.count() <= index.row() || (role != Qt::DisplayRole && role != Qt::EditRole)) {
        return QVariant();
    }

    switch (index.column()) {
    case NAME:
        return dataModel[index.row()].name;
        break;

    case SIZE:
        return dataModel[index.row()].size;
        break;

    case PERCENT:
        return dataModel[index.row()].percent;
        break;

    default:
        break;
    }

    return QVariant();
}

QVariant DataModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case NAME:
            return "Name";

        case SIZE:
            return "Size";

        case PERCENT:
            return "Percent";
        }
    }

    return QVariant();
}

void DataModel::setModel(QList<TableModel> model) {
    dataModel = model;

    emit layoutChanged();
}
