/*
    Class that provides ability to read and write high score to .dat file. The path and name of the record file is passed
    into costructor.
*/

#ifndef FILERECORDMANAGER_H
#define FILERECORDMANAGER_H

#include <QString>
#include"interfaces\irecordmanager.h"

class FileRecordManager: public IRecordManager
{
public:

    FileRecordManager(const QString &fileName);
    virtual ~FileRecordManager();

    virtual qint32 getPreviousRecord()override;
    virtual void writeNewRecord(qint32 score)override;

private:

    QString fileName;
};

#endif // FILERECORDMANAGER_H
