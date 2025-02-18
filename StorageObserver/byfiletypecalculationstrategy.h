#ifndef BYFILETYPECALCULATIONSTRATEGY_H
#define BYFILETYPECALCULATIONSTRATEGY_H

#include "calculationstrategy.h"

class ByFileTypeCalculationStrategy : public CalculationStrategy {
public:
    QMap<QString, qint64> calculationMethod(QString path);

private:
    QMap<QString, qint64> getFileTypesSize(QString path, QMap<QString, qint64>& map);
};

#endif // BYFILETYPECALCULATIONSTRATEGY_H
