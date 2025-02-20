#include <QDebug>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QWidget(parent) {
    setWindowTitle("Storage Observer");
    this->strategy = new Context(new ByFolderCalculationStrategy);
    model = new DataModel(this);

    systemModel = new QFileSystemModel(this);
    systemModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    systemModel->setRootPath(QDir::homePath());

    treeView = new QTreeView(this);
    treeView->setModel(systemModel);

    tableView = new QTableView(this);
    tableView->setModel(model);

    strategyLabel = new QLabel("Select the typy of the review", this);
    strategyBox = new QComboBox(this);
    strategyBox->addItems({"By folder", "By file type"});

    panelLayout = new QHBoxLayout();
    if (panelLayout != nullptr) {
        panelLayout->addStretch(1);
        panelLayout->addWidget(strategyLabel);
        panelLayout->addWidget(strategyBox);
    }

    viewsLayout = new QHBoxLayout();
    if (viewsLayout != nullptr) {
        viewsLayout->addWidget(treeView);
        viewsLayout->addWidget(tableView);
        viewsLayout->setStretchFactor(tableView, 1);
    }

    mainLayout = new QVBoxLayout(this);
    if (mainLayout != nullptr) {
        mainLayout->addLayout(panelLayout);
        mainLayout->addLayout(viewsLayout);
    }

    connect(treeView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::selectedSlot);
    connect(strategyBox, qOverload<int>(&QComboBox::currentIndexChanged), this, &MainWindow::strategyBoxSlot);
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
        model->setModel(fillTable(strategy->calculationMethod(systemModel->filePath(index))));
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
    model->setModel(fillTable(this->strategy->calculationMethod(systemModel->filePath(index))));
}
