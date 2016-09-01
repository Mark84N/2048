/*
    Subclass current class and implement virtual function to retrieve record from any custom place.
*/

#ifndef IRECORDMANAGER_H
#define IRECORDMANAGER_H

#include <QIODevice>
#include <QFile>
#include <QDataStream>

class IRecordManager
{
public:

    virtual qint32 getPreviousRecord() = 0;
    virtual void writeNewRecord(qint32 score) = 0;

    virtual ~IRecordManager(){}
};

#endif // IRECORDMANAGER_H
