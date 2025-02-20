#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTableView>
#include <QTreeView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileSystemModel>
#include <QLabel>
#include <QComboBox>
#include "calculation.h"
#include "datamodel.h"

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    DataModel* model;
    QTableView* tableView;
    QFileSystemModel* systemModel;
    QTreeView* treeView;

    QLabel* strategyLabel;
    QComboBox* strategyBox;

    QHBoxLayout* panelLayout;
    QHBoxLayout* viewsLayout;
    QVBoxLayout* mainLayout;

    Context* strategy;

private slots:
    void selectedSlot(const QItemSelection& selected, const QItemSelection& deselected);
    void strategyBoxSlot(int strategy);
};

#endif // MAINWINDOW_H
