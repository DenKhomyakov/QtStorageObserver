#include <QDebug>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QWidget(parent) {
    // TODO
}

MainWindow::~MainWindow() {
    delete strategy;
}

QString getPercent(qint64 currentSize, qint64 directorySize) {
    double percent = static_cast<double>(currentSize) / static_cast<double>(directorySize) * 100;

    if (percent < 0.01) {
        return "< 0.01";
    } else {
        return QString::number(percent, 'f', 2) + " %";
    }
}

QString convertKiloBytes(qint64 size) {
    double kiloBytes = static_cast<double>(size) / 1024;

    return QString::number(kiloBytes, 'f', 2) + " Kb";
}

qint64 getDirectorySize(QMap<QString, qint64> map) {
    qint64 totalSize = 0;

    for (auto i = map.cbegin(); i != map.cend(); ++i) {
        totalSize += i.value();
    }

    return totalSize;
}

QList<TableModel> fillTable(QMap<QString, qint64> map) {
    qint64 totalSize = getDirectorySize(map);
    QList<TableModel> result;

    for (auto i = map.cbegin(); i != map.cend(); ++i) {
        result.append(TableModel(i.key(), convertKiloBytes(i.value()), getPercent(i.value(), totalSize)));
    }

    return result;
}

void MainWindow::selectedSlot(const QItemSelection& selected, const QItemSelection& deselected) {
    Q_UNUSED(selected);
    Q_UNUSED(deselected);

    QModelIndex index = treeView->selectionModel()->currentIndex();

    if (index.isValid()) {
        model.setModel(fillTable(strategy->calculationMethod(systemModel->filePath(index))));
    }
}

void MainWindow::strategyBoxSlot(int strategy) {
    switch (strategy) {
    case 0:
        this->strategy->setStrategy(new ByFolderCalculationStrategy);
        break;

    case 1:
        this->strategy->setStrategy(new ByFileTypeCalculationStrategy);
        break;
    }

    QModelIndex index = treeView->selectionModel()->currentIndex();
    model.setModel(fillTable(this->strategy->calculationMethod(systemModel->filePath(index))));
}
