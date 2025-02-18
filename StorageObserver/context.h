#ifndef CONTEXT_H
#define CONTEXT_H

#include "byfoldercalculationstrategy.h"
#include "byfiletypecalculationstrategy.h"

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

private:
    CalculationStrategy* strategy;
};

#endif // CONTEXT_H
