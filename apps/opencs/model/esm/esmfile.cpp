#include "esmfile.hpp"

EsmFile::EsmFile(QString fileName, DataItem *parent)
    : DataItem(parent)
{
     mFileName = fileName;
}

