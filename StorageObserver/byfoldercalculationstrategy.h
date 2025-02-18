#ifndef BYFOLDERCALCULATIONSTRATEGY_H
#define BYFOLDERCALCULATIONSTRATEGY_H

#include "calculationstrategy.h"

class ByFolderCalculationStrategy : public CalculationStrategy {
public:
    QMap<QString, qint64> calculationMethod(QString path);

private:
    qint64 getFolderSize(QString path, qint64 folderSize);
};

#endif // BYFOLDERCALCULATIONSTRATEGY_H
