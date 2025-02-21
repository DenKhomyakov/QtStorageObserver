#ifndef CALCULATION_H
#define CALCULATION_H

#include <QDir>
#include <QFileInfo>
#include <QMap>
#include <QString>

class CalculationStrategy {
public:
    virtual ~CalculationStrategy() {}

    virtual QMap<QString, qint64> calculationMethod(QString path) = 0;
};

class ByFolderCalculationStrategy : public CalculationStrategy {
public:
    QMap<QString, qint64> calculationMethod(QString path);

    qint64 getFolderSize(QString path, qint64 folderSize);
};

class ByFileTypeCalculationStrategy : public CalculationStrategy {
public:
    QMap<QString, qint64> calculationMethod(QString path);

    QMap<QString, qint64> getFileTypesSize(QString path, QMap<QString, qint64>& map);
};

class Context {
public:
    Context(CalculationStrategy* strategy) {
        this->strategy = strategy;
    }

    ~Context() {
        delete strategy;
    }

    QMap<QString, qint64> calculationMethod(QString path) {
        return strategy->calculationMethod(path);
    }

    void setStrategy(CalculationStrategy* strategy) {
        this->strategy = strategy;
    }

private:
    CalculationStrategy* strategy;
};

#endif // CALCULATION_H
