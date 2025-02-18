#include "byfiletypecalculationstrategy.h"

QMap<QString, qint64> ByFileTypeCalculationStrategy::calculationMethod(QString path) {
    QDir directory(path);

    if (!directory.exists()) {
        throw std::runtime_error("The specified directory doesn't exist");
    }

    QMap<QString, qint64> directoryMap;
    directoryMap = getFileTypesSize(path, directoryMap);

    return directoryMap;
}

QMap<QString, qint64> ByFileTypeCalculationStrategy::getFileTypesSize(QString path, QMap<QString, qint64>& map) {
    QDir directory = QDir(path);

    foreach (QFileInfo file, directory.entryInfoList(QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden | QDir::NoSymLinks)) {
        if (map.contains(file.suffix())) {
            map[file.suffix()] += file.size();
        } else {
            map[file.suffix()] = file.size();
        }
    }

    foreach (QFileInfo folder, directory.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::NoSymLinks)) {
        getFileTypesSize(folder.absoluteFilePath(), map);
    }

    return map;
}
