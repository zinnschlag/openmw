/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef DATAFILESMODEL_HPP
#define DATAFILESMODEL_HPP

#include <QAbstractTableModel>
#include <QStringList>
#include <QString>
#include <QHash>


class EsmFile;

class DataFilesModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit DataFilesModel(QObject *parent = 0);
    virtual ~DataFilesModel();
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;

    bool moveRow(int oldrow, int row, const QModelIndex &parent = QModelIndex());

    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder);

    inline QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const
       { return QAbstractTableModel::index(row, column, parent); }

    void setEncoding(const QString &encoding);

    void addFile(EsmFile *file);

    void addMasters(const QString &path);
    void addPlugins(const QString &path);

    void uncheckAll();

    QStringList checkedItems();
    QStringList uncheckedItems();
    QStringList checkedItemsPaths();

    Qt::CheckState checkState(const QModelIndex &index);
    void setCheckState(const QModelIndex &index, Qt::CheckState state);

    QModelIndex indexFromItem(EsmFile *item) const;
    EsmFile* findItem(const QString &name);
    EsmFile* item(int row) const;

signals:
    void checkedItemsChanged(const QStringList checkedItems, const QStringList unCheckedItems);
    
public slots:
    void slotcheckedItemsChanged(const QStringList &checkedItems, const QStringList &unCheckedItems);
    
private:
    QList<EsmFile *> mFiles;
    QStringList mAvailableFiles;

    QHash<QString, QStringList> mDependencies;
    QHash<QString, Qt::CheckState> mCheckStates;

    QString mEncoding;

};

#endif // DATAFILESMODEL_HPP
