/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include "esmfile.hpp"

EsmFile::EsmFile(QString fileName, ModelItem *parent)
    : ModelItem(parent)
{
     mFileName = fileName;
     mSize = 0;
     mVersion = 0.0f;
}

void EsmFile::setFileName(const QString &fileName)
{
    mFileName = fileName;
}

void EsmFile::setAuthor(const QString &author)
{
    mAuthor = author;
}

void EsmFile::setSize(const int size)
{
    mSize = size;
}

void EsmFile::setDates(const QDateTime &modified, const QDateTime &accessed)
{
    mModified = modified;
    mAccessed = accessed;
}

void EsmFile::setVersion(float version)
{
    mVersion = version;
}

void EsmFile::setPath(const QString &path)
{
    mPath = path;
}

void EsmFile::setMasters(const QStringList &masters)
{
    mMasters = masters;
}

void EsmFile::setDescription(const QString &description)
{
    mDescription = description;
}
