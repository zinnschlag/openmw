#ifndef ESMFILE_HPP
#define ESMFILE_HPP

#include "dataitem.hpp"

class EsmFile : public DataItem
{
    Q_OBJECT
    Q_PROPERTY(QString filename READ filename)

public:
    EsmFile(DataItem *parent = 0)
        : DataItem(parent)
    {
    }

    ~EsmFile()
    {
    }

    EsmFile(QString fileName, DataItem *parent);

    QString filename()
    {
        return mFileName;
    }

private:
    QString mFileName;
};


#endif
