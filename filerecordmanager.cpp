#include "filerecordmanager.h"

FileRecordManager::FileRecordManager(const QString &fileName)
    :fileName(fileName)
{
}

qint32 FileRecordManager::getPreviousRecord()
{
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly))
        return 0;

    qint32 rec = 0;

    QDataStream stream(&file);
    stream >> rec;

    file.close();

    return rec;
}

void FileRecordManager::writeNewRecord(qint32 score)
{
    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return;

    QDataStream stream(&file);
    stream << score;

    file.close();
}

FileRecordManager::~FileRecordManager()
{}
