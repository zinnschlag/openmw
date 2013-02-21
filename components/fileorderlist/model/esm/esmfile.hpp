/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ESMFILE_HPP
#define ESMFILE_HPP

#include <QDateTime>
#include <QStringList>

#include "../modelitem.hpp"

class EsmFile : public ModelItem
{
    Q_OBJECT
    Q_PROPERTY(QString filename READ fileName)

public:
    EsmFile(QString fileName = QString(), ModelItem *parent = 0);

    ~EsmFile()
    {}

    void setFileName(const QString &fileName);
    void setAuthor(const QString &author);
    void setSize(const int size);
    void setDates(const QDateTime &modified, const QDateTime &accessed);
    void setVersion(const float version);
    void setPath(const QString &path);
    void setMasters(const QStringList &masters);
    void setDescription(const QString &description);

    inline QString fileName() { return mFileName; }
    inline QString author() { return mAuthor; }
    inline int size() { return mSize; }
    inline QDateTime modified() { return mModified; }
    inline QDateTime accessed() { return mAccessed; }
    inline float version() { return mVersion; }
    inline QString path() { return mPath; }
    inline QStringList masters() { return mMasters; }
    inline QString description() { return mDescription; }


private:
    QString mFileName;
    QString mAuthor;
    int mSize;
    QDateTime mModified;
    QDateTime mAccessed;
    float mVersion;
    QString mPath;
    QStringList mMasters;
    QString mDescription;

};


#endif
