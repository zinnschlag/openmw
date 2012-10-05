#include "esmfile.hpp"

#include <QFileInfo>

EsmFile::EsmFile(QString fileName, ModelItem *parent)
    : ModelItem(parent)
{
    mFileName = fileName;

    QFileInfo fileInfo(fileName);
    setObjectName(fileInfo.fileName());
}

