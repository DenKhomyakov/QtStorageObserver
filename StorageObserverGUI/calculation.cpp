#include "calculation.h"

QMap<QString, qint64> ByFolderCalculationStrategy::calculationMethod(QString path) {
    QDir directory(path);

    if (!directory.exists()) {
        throw std::runtime_error("The specified directory doesn't exist");
    }

    QMap<QString, qint64> directoryMap;

    directory.setFilter(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::NoSymLinks);
    QFileInfoList list = directory.entryInfoList();

    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);

        if (fileInfo.isDir()) {
            qint64 currentFolderSize = 0;
            directoryMap[fileInfo.fileName()] = getFolderSize(fileInfo.absoluteFilePath(), currentFolderSize);
        } else {
            directoryMap["(Current folder)"] += fileInfo.size();
        }
    }

    return directoryMap;
}

qint64 ByFolderCalculationStrategy::getFolderSize(QString path, qint64 folderSize) {
    QDir directory(path);

    foreach (QFileInfo file, directory.entryInfoList(QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden | QDir::NoSymLinks)) {
        folderSize += file.size();
    }

    foreach (QFileInfo folder, directory.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::NoSymLinks)) {
        qint64 currentFolderSize = 0;
        folderSize += getFolderSize(folder.absoluteFilePath(), currentFolderSize);
    }

    return folderSize;
}

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
