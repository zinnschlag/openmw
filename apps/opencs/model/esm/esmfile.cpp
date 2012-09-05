#include "esmfile.hpp"

EsmFile::EsmFile(QString fileName, ModelItem *parent)
    : ModelItem(parent)
{
     mFileName = fileName;
}

