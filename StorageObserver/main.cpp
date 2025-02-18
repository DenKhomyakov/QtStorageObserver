#include <QCoreApplication>
#include <iostream>
#include "context.h"

QString getPersent(qint64 directorySize, qint64 currentSize) {
    double percent = static_cast<double>(currentSize) / static_cast<double>(directorySize) * 100;

    if (percent < 0.01) {
        return "< 0.01";
    } else {
        return QString::number(percent, 'f', 2);
    }
}

qint64 getDirectorySize(QMap<QString, qint64> map) {
    qint64 totalSize = 0;

    for (auto i = map.cbegin(); i != map.cend(); ++i) {
        totalSize += i.value();
    }

    return totalSize;
}

void printInfo(QMap<QString, qint64> map) {
    qint64 mapSize = getDirectorySize(map);

    for (auto i = map.cbegin(); i != map.cend(); ++i) {
        std::cout << qPrintable(i.key()) << ": " << qPrintable(getPersent(mapSize, i.value())) << " %" << std::endl;
    }
}

int main(int argc, char *argv[]) {
    QString path = "../Test";
    Context* context = new Context(new ByFileTypeCalculationStrategy);
    std::cout << "By file types calculation:" << std:: endl;
    printInfo(context->calculationMethod(path));
    delete context;

    std::cout << std::endl;

    context = new Context(new ByFolderCalculationStrategy);
    std::cout << "By folder calculation:" << std::endl;
    printInfo(context->calculationMethod(path));
    delete context;

    context = nullptr;

    return 0;
}
