#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QObject>
#include <QList>
#include <QString>
#include <QAbstractTableModel>

class TableModel {
public:
    TableModel(QString name = "Name", QString size = "Size", QString percent = "Percent") : name(name), size(size), percent(percent) {}

    QString name;
    QString size;
    QString percent;
};

class DataModel : public QAbstractTableModel {
    Q_OBJECT

public:
    DataModel(QObject* parent = nullptr, QList<TableModel> table = QList<TableModel>());

    int rowCount(const QModelIndex& parent) const;
    int columnCount(const QModelIndex& parent) const;

    QVariant data(const QModelIndex& index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    void setModel(QList<TableModel> model);

private:
    enum ColumnName {
        NAME = 0,
        SIZE,
        PERCENT
    };

    QList<TableModel> dataModel;
};

#endif // DATAMODEL_H
