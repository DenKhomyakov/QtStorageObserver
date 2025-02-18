#ifndef CALCULATIONSTRATEGY_H
#define CALCULATIONSTRATEGY_H

#include <iostream>
#include <QDir>
#include <QFileInfo>
#include <QMap>
#include <QString>

class CalculationStrategy {
public:
    virtual ~CalculationStrategy() {}

    virtual QMap<QString, qint64> calculationMethod(QString path) = 0;
};

#endif // CALCULATIONSTRATEGY_H
