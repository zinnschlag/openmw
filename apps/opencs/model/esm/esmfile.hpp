#ifndef ESMFILE_HPP
#define ESMFILE_HPP

#include "../modelitem.hpp"

class EsmFile : public ModelItem
{
    Q_OBJECT

    Q_CLASSINFO("display.0", "objectName")

    Q_PROPERTY(QString filename READ filename)

public:
    EsmFile(QString fileName, ModelItem *parent);

    ~EsmFile()
    {}


    QString filename()
    {
        return mFileName;
    }

private:
    QString mFileName;
};


#endif
